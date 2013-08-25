//
//  TickManager.cpp
//  Infinity
//
//  Created by Koichiro on 2013/08/25.
//  Copyright (c) 2013年 Koichiro. All rights reserved.
//

#include "ObjectManager.h"

namespace Infinity
{
	ObjectManager::ObjectManager(size_t threadnum)
	{
		mTasks.reset(new TaskManager(threadnum));
	}
}
