#include "ObjectManager.h"
#include <mutex>

namespace Infinity
{
	std::unordered_map<Object *,Object *> ObjectManager::mObjects;

	void ObjectManager::RegisterObjects(Object *obj)
	{
		std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		mObjects.insert(std::make_pair(obj, obj));
	}

	void ObjectManager::UnRegisterObjects(Object *obj)
	{
		std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		mObjects.erase(obj);
	}

}
