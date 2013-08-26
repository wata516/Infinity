#include "Object.h"
#include "TaskManager.h"

namespace Infinity
{
	Object::Object()
		: mName("Object")
		, mTickGroup( TICKGROUP_MAX )
	{
	}

	Object::~Object()
	{
	}

	void Object::Create(const std::string &name, TICKGROUP group)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mName = name;
		mTickGroup = group;
	}

	bool Object::IsCreate()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mTickGroup != TICKGROUP_MAX;
	}
}
