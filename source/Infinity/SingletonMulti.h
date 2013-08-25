#pragma once

#include <memory>
#include <thread>

namespace Infinity
{
	template<class T>
	class SingletonMulti
	{
		T *mSingleton;
		std::mutex mMutex;
		
	public:
		void Create(T *ptr)
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mSingleton = ptr;
		}

		T &GetInstance()
		{
			std::lock_guard<std::mutex> lock(mMutex);
			return *mSingleton;
		}
	};
#define SINGLETON_MULTI_DECLARE(classname) \
private: \
	static SingletonMulti<classname> mSingleton; \
public: \
	static classname &GetInstance() \
	{ \
		return mSingleton.GetInstance(); \
	}
}
