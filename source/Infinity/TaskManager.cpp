#include <Infinity/TaskManager.h>
#include <Infinity/Task.h>
#include <Infinity/ThreadWorker.h>
#include <thread>
#include <vector>
#include <array>
#include <memory>
#include <condition_variable>
#include <stdio.h>

namespace Infinity {

	std::array<TaskManager::ValueType,Object::TICKGROUP_MAX> TaskManager::mTasks;
	std::mutex TaskManager::mTaskMutex;

	void TaskManager::RegistTask(Object*obj)
	{
		mTasks[obj->GetTickGroup()].insert(std::make_pair(obj,obj));
	}

	struct TaskTickArgment{
		std::mutex mtx;
		TaskManager::ValueType *mTasks;
		TaskManager::ValueType::iterator mIterator;
	};

	struct TaskTickFunction {
		bool operator()(int id, TaskTickArgment &argment) {
			Infinity::Object *task = nullptr;
			{
				std::lock_guard<std::mutex> lock(argment.mtx);
				if( argment.mIterator == argment.mTasks->end() ) {
					return false;
				}
				task = (argment.mIterator)->second;
				++ argment.mIterator;
			}
			task->Tick();

			return true;
		}
	};

	class TaskManager::Impl {
		std::unique_ptr< std::thread > mWorker;
		std::unique_ptr<ThreadPool<ThreadWorker<TaskTickArgment>>> mWorkers;
		TaskTickArgment mWorkArgment;

	public:
		Impl(size_t threadnum);
		void Tick();
		void Destroy();
	};

	TaskManager::Impl::Impl(size_t threadnum) 
	{
		mWorkers.reset( new ThreadPool<ThreadWorker<TaskTickArgment>>( threadnum, TaskTickFunction(), mWorkArgment ) );
	}

	void TaskManager::Impl::Tick()
	{
		{
			std::lock_guard<std::mutex> lock(mTaskMutex);
			mWorkArgment.mTasks = &mTasks[Object::TICKGROUP_PARALLEL];
			mWorkArgment.mIterator = mTasks[Object::TICKGROUP_PARALLEL].begin();
			mWorkers->Run();
		}

		TaskManager::ValueType &single = mTasks[ Object::TICKGROUP_SINGLE ];
		for( std::pair<Object*const,Object*> &x : single ) {
			x.second->Tick();
		}
	}

	void TaskManager::Impl::Destroy()
	{
		mWorkers->Destroy();
	}

	TaskManager::TaskManager(size_t threadnum)
		: mImpl(new Impl(threadnum))
	{}

	TaskManager::~TaskManager()
	{}

	void TaskManager::Tick()
	{ mImpl->Tick(); }

	void TaskManager::Destroy()
	{ mImpl->Destroy(); }

}
