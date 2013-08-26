//
//  Test case for Google Test
//
#include <gtest/gtest.h>

int add(int x, int y)
{
	// do nothing.
	return x + y;
}

// 1 + 1 の結果は 2 になるはず（..だけど、このコードは失敗する）
TEST(AddTest, Test1)
{
	ASSERT_EQ(2, add(1, 1));
}
#if 0
#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>

#include <Infinity/TaskManager.h>
#include <Infinity/Task.h>

#include <Infinity/Actor.h>

TEST(AddTest, Test1 )
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
#endif