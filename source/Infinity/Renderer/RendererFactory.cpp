#include <Infinity/Renderer/RendererFactory.h>
#include <Infinity/Renderer/IRenderer.h>
#include <Infinity/Renderer/SDL/SDLRenderer.h>

#include <unordered_map>
#include <functional>

namespace Infinity
{
	namespace Renderer
	{
		bool CreateSDLRenderer( IRenderer **ppRenderer )
		{
			*ppRenderer = new SDL::Renderer;
			return true;
		}

		bool RendererFactory::Create( const std::string &name, IRenderer **ppRenderer )
		{
			std::unordered_map< std::string, std::function< bool( IRenderer **) > > functions;

			functions["SDL"] = std::bind(CreateSDLRenderer, ppRenderer);

			if( functions.find( name ) == functions.end() ) {
				return false;
			}

			if( functions[ name ]( ppRenderer ) == false ) {
				return false;
			}

			return true;
		}

		void RendererFactory::Destroy( IRenderer **ppRenderer )
		{
			delete *ppRenderer;
			*ppRenderer = nullptr;
		}
	}
}
