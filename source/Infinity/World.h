#pragma once

#include <Infinity/Object.h>
#include <list>
#include <memory>

namespace Infinity
{
	class Level;
	class World : public Object
	{
		OBJECT_DECLARE_DECLARE(World,Object,TICKGROUP_PARALLEL);
		
		void Construct() {}
		void Destruct() {}
	public:
		void AddLevel( );

	private:
		std::list<std::shared_ptr<Level>> mLevels;
	};
}
