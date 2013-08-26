#include "Object.h"
#include <mutex>

namespace Infinity
{
	std::unordered_map<Object *,Object *> Object::mObjects;

	Object::Object()
	{
		std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		mObjects.insert(std::make_pair(this, this));
	}
}
