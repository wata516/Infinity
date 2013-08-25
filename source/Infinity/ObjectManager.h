#pragma once

#include "TaskManager.h"

namespace Infinity
{
	class ObjectManager
	{
		std::unique_ptr<TaskManager> mTasks;

	public:
		ObjectManager(size_t threadnum);
	};
}
