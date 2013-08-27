#pragma once

#include <Infinity/Object.h>

namespace Infinity
{
	class Task : public Object
	{
	public:
		OBJECT_DECLARE_DECLARE(Task,Object,TICKGROUP_PARALLEL);

	public:
		void Construct();
		void Destruct();
		virtual void Tick() { }
	};
}
