#pragma once

#include <Infinity/Renderer/IRenderer.h>
#include <memory>

namespace Infinity
{
	namespace Renderer
	{
		namespace SDL
		{
			class Renderer : public Infinity::Renderer::IRenderer
			{
			public:
				Renderer();

				virtual bool Create();
				virtual void Destroy();
				virtual ISurface * CreateSurface(int width, int height);

			private:
				class Impl;
				std::unique_ptr<Impl> mImpl;
			};
		}
	}
}
