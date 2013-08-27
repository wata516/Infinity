#pragma once

#include <string>

namespace Infinity
{
	namespace Renderer
	{
		class IRenderer;
		class RendererFactory
		{
			static bool Create( const std::string &name, IRenderer **ppRenderer );
		};
	}
}