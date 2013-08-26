#include <gtest/gtest.h>

#include <Infinity/TaskManager.h>
#include <Infinity/Task.h>

#include <Infinity/Actor.h>

TEST(TaskManager, CreateDestroy )
{
	class TestTask : public Infinity::Task
	{
		int mValue;
		int mMax;
	public:
		TestTask(int max) : mValue(0), mMax(max) {}
		virtual void Tick() {
			mValue += mMax;
		}
	};
	Infinity::TaskManager taskman(10);

	for( int i = 0 ; i < 100 ; ++ i ) {
		taskman.AddBack( Infinity::TaskManager::GROUP_PARALLEL, new TestTask(i) );
	}
	taskman.Tick();

	taskman.Destroy();

	ASSERT_EQ(2, 2);
}
