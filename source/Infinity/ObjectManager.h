#pragma once

#include "TaskManager.h"
#include <unordered_map>

namespace Infinity
{
	class Object;
	class ObjectManager
	{
		static std::unordered_map<Object *,Object *> mObjects;
	public:
		static void RegisterObjects(Object *obj);
		static void UnRegisterObjects(Object *obj);

	};
}
