#pragma once

namespace Infinity
{
	namespace Renderer
	{
		class ISurface;

		class IRenderer
		{
		public:
			virtual bool Create() = 0;
			virtual void Destroy() = 0;
			virtual ISurface * CreateSurface(int width, int height) = 0;
		};
	}
}
