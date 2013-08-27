#include <wx/wx.h>
#include "Infinity/Editor/MainFrame.h"

namespace InfinityEditor
{
	class MyApp: public wxApp
	{
	public:
		virtual bool OnInit();
	};

	IMPLEMENT_APP(MyApp)

	bool MyApp::OnInit()
	{
		Infinity::Editor::MainFrame *frame = new Infinity::Editor::MainFrame( _(""), wxDefaultPosition, wxSize(900, 700) );
		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
}
