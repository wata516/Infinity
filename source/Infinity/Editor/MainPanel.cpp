#include <Infinity/Editor/MainPanel.h>
#include <Infinity/Renderer/ISurface.h>

#include <wx/dcbuffer.h>

namespace Infinity
{
	namespace Editor
	{
		BEGIN_EVENT_TABLE(MainPanel, wxPanel)
			EVT_PAINT(MainPanel::OnPaint)
			EVT_IDLE(MainPanel::OnIdle)
		END_EVENT_TABLE()

		IMPLEMENT_CLASS(MainPanel, wxPanel)

		MainPanel::MainPanel(wxWindow *parent, Infinity::Renderer::ISurface *surface)
			: wxPanel(parent, wxID_ANY)
		{
			mSurface = surface;
		}

		void MainPanel::OnPaint(wxPaintEvent &event)
		{
			struct UpdateSurface{
				wxWindow *mWindow;
				UpdateSurface( wxWindow *window ) :mWindow(window) { }
				void operator()(Infinity::Renderer::ISurface *surface, char *bitmap,int width, int height)
				{
					wxBitmap bmp(wxImage(width, height, reinterpret_cast<unsigned char *>(bitmap), true));

					wxBufferedPaintDC dc(mWindow, bmp);
				}
			};

			mSurface->Present(UpdateSurface(this));

		}

		void MainPanel::OnIdle(wxIdleEvent &event)
		{
			mSurface->Clear(96,110,125);

			Refresh(false);
		}
	}
}
