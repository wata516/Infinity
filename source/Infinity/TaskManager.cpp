#include "TaskManager.h"
#include "Task.h"
#include "ThreadWorker.h"
#include <thread>
#include <vector>
#include <array>
#include <memory>
#include <condition_variable>

namespace Infinity {

	struct TaskTickArgment{
		std::vector<Infinity::Task*> *mTasks;
		std::vector<Infinity::Task*>::iterator mIterator;
	};

	struct TaskTickFunction {
		bool operator()(int id, TaskTickArgment &argment) {
			Infinity::Task *task = nullptr;
			{
				std::mutex mtx;
				std::lock_guard<std::mutex> lock(mtx);
				if( argment.mIterator == argment.mTasks->end() ) {
					return false;
				}
				task = *(argment.mIterator);
				++ argment.mIterator;
			}
			task->Tick();

			return true;
		}
	};

	class TaskManager::Impl {
		std::unique_ptr< std::thread > mWorker;
		std::array< std::vector< Infinity::Task * >, TaskManager::GROUP_MAX > mTasks;
		std::unique_ptr<ThreadPool<ThreadWorker<TaskTickArgment>>> mWorkers;
		TaskTickArgment mWorkArgment;

	public:
		Impl(size_t threadnum);
		void Tick();
		void Destroy();
		void AddBack(TaskManager::GROUP &group, Task *task);
	};

	TaskManager::Impl::Impl(size_t threadnum) 
	{
		mWorkers.reset( new ThreadPool<ThreadWorker<TaskTickArgment>>( threadnum, TaskTickFunction(), mWorkArgment ) );
	}

	void TaskManager::Impl::Tick()
	{
		mWorkArgment.mTasks = &mTasks[TaskManager::GROUP::GROUP_PARALLEL];
		mWorkArgment.mIterator = mTasks[TaskManager::GROUP::GROUP_PARALLEL].begin();
		mWorkers->Run();
		for( auto *x : mTasks[ TaskManager::GROUP::GROUP_SINGLE ] ) {
			x->Tick();
		}
	}

	void TaskManager::Impl::Destroy()
	{
		mWorkers->Destroy();
	}

	void TaskManager::Impl::AddBack(TaskManager::GROUP &group, Task *task)
	{
		mTasks[group].push_back(task);
	}

	TaskManager::TaskManager(size_t threadnum)
		: mImpl(new Impl(threadnum))
	{}

	TaskManager::~TaskManager()
	{}

	void TaskManager::AddBack(GROUP group, Task *task)
	{ mImpl->AddBack(group,task); }

	void TaskManager::Tick()
	{ mImpl->Tick(); }

	void TaskManager::Destroy()
	{ mImpl->Destroy(); }

}
