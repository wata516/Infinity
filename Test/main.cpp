#define BOOST_TEST_MODULE boost_unit_test
#include <boost/test/unit_test.hpp>


#include <Infinity/TaskManager.h>
#include <Infinity/Task.h>

#include <Infinity/Actor.h>

BOOST_AUTO_TEST_SUITE( my_suite1 )

BOOST_AUTO_TEST_CASE( tc1 )
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

	BOOST_CHECK(false);
}
BOOST_AUTO_TEST_SUITE_END()
