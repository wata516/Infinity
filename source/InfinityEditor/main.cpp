#include <wx/wx.h>
#include "Infinity/Editor/MainFrame.h"
#include "Infinity/Editor/MainPanel.h"

namespace InfinityEditor
{
	class MyApp: public wxApp
	{
		Infinity::Editor::MainFrame *mFrame;
	public:
		virtual bool OnInit();
	};

	IMPLEMENT_APP(MyApp)

	bool MyApp::OnInit()
	{
		mFrame = new Infinity::Editor::MainFrame( _(""), wxDefaultPosition, wxSize(900,700));
		mFrame->get()->Show(true);
		SetTopWindow(mFrame->get());
		return true;
	}

}
