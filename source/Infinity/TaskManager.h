#pragma once
#include "Object.h"

#include <memory>
#include <array>
#include <unordered_map>

namespace Infinity
{
	class Task;
	class TaskManager
	{
	public:
		typedef std::unordered_map<Object *,Object *> ValueType;
	private:
		static std::array<ValueType,Object::TICKGROUP_MAX> mTasks;
		static std::mutex mTaskMutex;
	public:
		static std::mutex &getTaskMutex() { return mTaskMutex; }
		static void RegistTask(Object*obj);


	public:
		TaskManager(size_t threadnum);
		virtual ~TaskManager();

		void Tick();
		void Destroy();
	private:
		class Impl;
		std::unique_ptr<Impl> mImpl;
	};
}
