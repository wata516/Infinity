#pragma once

#include <memory>

namespace Infinity
{
	class TaskManager;
	class World;

	class Engine
	{
	public:
		struct Initialize
		{
			size_t NumTaskThreads;
		};
	public:
		Engine();
		virtual ~Engine();
		bool Create( const Initialize &init );
		void Destroy();
		void Stop();
		int MainLoop();

	public:
		TaskManager &GetTask();

	private:
		class Impl;
		std::unique_ptr<Impl> mImpl;
	};
}
