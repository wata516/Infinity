#pragma once
#include <memory>

namespace Infinity
{
	class Task;
	class TaskManager
	{
	public:
		enum GROUP {
			GROUP_PARALLEL,
			GROUP_SINGLE,
			GROUP_MAX
		};

	public:
		TaskManager(size_t threadnum);
		virtual ~TaskManager();

		void AddBack(GROUP group, Task *task);
		void Tick();
		void Destroy();
	private:
		class Impl;
		std::unique_ptr<Impl> mImpl;
	};
}
