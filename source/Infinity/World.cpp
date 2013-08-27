#include <Infinity/World.h>
#include <Infinity/Level.h>

namespace Infinity
{
	void World::AddLevel()
	{
		std::shared_ptr<Level> NewLevel(new Level);
		mLevels.push_back(NewLevel);
	}
}
