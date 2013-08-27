#pragma once

#include <Infinity/Object.h>

namespace Infinity
{
	class Actor : public Object
	{
		OBJECT_DECLARE_DECLARE(Actor,Object,TICKGROUP_SINGLE);
	};
}