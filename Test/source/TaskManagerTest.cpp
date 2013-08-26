#include <gtest/gtest.h>

#include <Infinity/TaskManager.h>
#include <Infinity/Task.h>

#include <Infinity/Actor.h>

#include <thread>
#include <mutex>

// TaskManagerを作成して破棄するを断続的に行うテスト
TEST(TaskManager, CreateDestroy )
{
#if 1
	for( size_t i = 0 ; i < 10 ; ++ i ) {
		std::unique_ptr< Infinity::TaskManager>taskman(new Infinity::TaskManager(1));
	}
#endif
	ASSERT_TRUE(true);
}

// タスクのTickをしながら他のThreadからタスクを追加するテスト
TEST(TaskManager, AddTaskMultiThread )
{
	static int incliment = 0;
	static std::mutex incmtx;
	class TestTask : public Infinity::Task
	{
	public:
		OBJECT_DECLARE_DECLARE(TestTask,Infinity::Task,TICKGROUP_PARALLEL);
		int mUse;
	public:
		void Construct(){
			mUse = false;
		}
		virtual void Tick() {
			std::lock_guard<std::mutex> lock(incmtx);
			if( !mUse ) {
				incliment++;
				mUse = true;
			}
		}
	};
	Infinity::TaskManager taskman(10);
	static bool loop = true;
	static std::mutex loopmutex;
	static const int loopmax = 0xFFF;
	std::thread p =	std::thread([](){
		for(size_t i = 0 ; i < loopmax ; ++ i) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			TestTask *task = Infinity::Object::Allocate<TestTask>();
		}
		{
			std::lock_guard<std::mutex> lock(loopmutex);
			loop = false;
		}
	});

	bool testloop = true;
	while(testloop ) {
		taskman.Tick();
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		{
			std::lock_guard<std::mutex> lock(loopmutex);
			testloop = loop;
		}
	}

	p.join();

	taskman.Tick();

	taskman.Destroy();

	ASSERT_EQ(incliment, loopmax);
}
