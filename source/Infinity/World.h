#pragma once

#include "Object.h"
#include <list>
#include <memory>

namespace Infinity
{
	class Level;
	class World : public Object
	{
		OBJECT_DECLARE_DECLARE(World,Object,TaskManager::GROUP_PARALLEL);
		
		void Construct() {}
	public:
		void AddLevel( );

	private:
		std::list<std::shared_ptr<Level>> mLevels;
	};
}
