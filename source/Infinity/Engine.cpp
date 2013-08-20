#include "Engine.h"
#include "TaskManager.h"
#include <thread>
#include <memory>

namespace Infinity
{
	class Engine::Impl
	{
		std::unique_ptr<TaskManager> mTicks;

		bool mLoop:1;
	public:
		Impl();

	public:
		bool Create(const Initialize &init);
		void Destroy();
		void Stop();
		int MainLoop();
	public:
		TaskManager &GetTask();
	};

	Engine::Impl::Impl()
		:mLoop(true)
	{}

	bool Engine::Impl::Create(const Initialize &init)
	{
		mTicks.reset(new TaskManager(init.NumTaskThreads));
		return false;
	}

	void Engine::Impl::Destroy()
	{
		mTicks->Destroy();
	}

	void Engine::Impl::Stop()
	{
		mLoop = false;
	}

	int Engine::Impl::MainLoop()
	{
		while(mLoop) {
			mTicks->Tick();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		return 0;
	}

	TaskManager &Engine::Impl::GetTask()
	{
		return *mTicks;
	}

	Engine::Engine()
		: mImpl(new Impl)
	{}

	Engine::~Engine()
	{}

	bool Engine::Create(const Initialize &init)
	{
		return mImpl->Create(init);
	}

	void Engine::Destroy()
	{
		mImpl->Destroy();
	}

	int Engine::MainLoop()
	{
		return mImpl->MainLoop();
	}

	void Engine::Stop()
	{
		mImpl->Stop();
	}

	TaskManager &Engine::GetTask()
	{
		return mImpl->GetTask();
	}
}
