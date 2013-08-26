#include "Object.h"
#include <mutex>

namespace Infinity
{
	std::unordered_map<Object *,Object *> Object::mObjects;

	void Object::RegisterObjects(Object *obj)
	{
		std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		mObjects.insert(std::make_pair(obj, obj));
	}

	void Object::UnRegisterObjects(Object *obj)
	{
		std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		mObjects.insert(std::make_pair(obj, obj));
	}

	Object::Object()
	{
		RegisterObjects(this);
	}

	Object::~Object()
	{
		UnRegisterObjects(this);
	}
}
