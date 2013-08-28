#pragma once

#include <string>

namespace Infinity
{
	namespace Renderer
	{
		class IRenderer;
		class RendererFactory
		{
		public:
			static bool Create( const std::string &name, IRenderer **ppRenderer );
			static void Destroy( IRenderer **ppRenderer );
		};
	}
}