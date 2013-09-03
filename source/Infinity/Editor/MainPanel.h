#pragma once

#include <wx/wx.h>

namespace Infinity
{
	namespace Renderer
	{
		class ISurface;
	}

	namespace Editor
	{
		class MainPanel : public wxPanel
		{
			DECLARE_CLASS(MainPanel)
			DECLARE_EVENT_TABLE()
			Infinity::Renderer::ISurface *mSurface;

		public:
			MainPanel(wxWindow *parent, Infinity::Renderer::ISurface *surface);
		protected:
			void OnPaint(wxPaintEvent &event);
			void OnIdle(wxIdleEvent &event);
		};
	}
}