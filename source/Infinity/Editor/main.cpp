#include <wx/wx.h>
#include "MainFrame.h"

namespace Infinity
{
	namespace Editor
	{
		class MyApp: public wxApp
		{
		public:
			virtual bool OnInit();
		};

		IMPLEMENT_APP(MyApp)

		bool MyApp::OnInit()
		{
			MainFrame *frame = new MainFrame( _(""), wxDefaultPosition, wxSize(900, 700) );
			frame->Show(true);
			SetTopWindow(frame);
			return true;
		}
	}
}
