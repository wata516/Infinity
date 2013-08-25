#include "World.h"
#include "Level.h"

namespace Infinity
{
	void World::AddLevel()
	{
		std::shared_ptr<Level> NewLevel(new Level);
		mLevels.push_back(NewLevel);
	}
}
