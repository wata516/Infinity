#pragma once

#include "ThreadPool.h"

namespace Infinity {
	template<class Argment>
	class ThreadWorker
	{
	public:
		typedef Argment ArgmentType;
		typedef std::function<bool(int, ArgmentType &)> TickFunc;

	protected:
		typedef ThreadPool<ThreadWorker<Argment>> TPool;
		size_t mId;
		TPool &mPool;
		TickFunc mFunc;
		Argment &mArgment;

	public:
		ThreadWorker(size_t id, TPool &pool, TickFunc func, Argment &argment)
			: mId(id)
			, mPool(pool)
			, mFunc(func)
			, mArgment(argment)
		{}

		void operator()(){
			for(;;) {
				mPool.mWorkersCondition.Wait();

				{
					std::mutex mtx;
					std::lock_guard<std::mutex> lock(mtx);
					if( mPool.mStatus[TPool::STATUS_STOP] ) {
						return;
					}
				}

				while( mFunc(mId, mArgment) ){
					std::this_thread::yield();
				}
			}
		}
	};
}
