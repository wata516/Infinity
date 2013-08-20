#pragma once

#include <chrono>

namespace Infinity
{
	class CpuDuration
	{
		std::chrono::system_clock::time_point mBegin;
	public:
		CpuDuration() {
			mBegin = std::chrono::system_clock::now();
		}
		template<class T>
		void GetDuration(T &time) const {
			time = std::chrono::duration_cast<T>(std::chrono::system_clock::now() - mBegin);
		}
	};
}
