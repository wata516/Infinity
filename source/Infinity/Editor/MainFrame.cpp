#include <Infinity/Editor/MainFrame.h>

namespace Infinity
{
	namespace Editor
	{
		MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
			: wxFrame(NULL, -1, title, pos, size)
		{
			wxMenu *menuFile = new wxMenu;
			wxMenu *menuHelp = new wxMenu;

			menuFile->Append( ID_Quit, _("�I��") );
			menuHelp->Append( ID_About, _("�o�[�W����...") );

			wxMenuBar *menuBar = new wxMenuBar;
			menuBar->Append( menuFile, _("�t�@�C��") );
			menuBar->Append( menuHelp, _("�w���v") );

			SetMenuBar( menuBar );

			CreateStatusBar();
			SetStatusText( _("") );
		}

		void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
		{
			Close(true);
		}

		void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
		{
			wxMessageBox( _("Version 0.01"),
				_("About Editor"),
				wxOK | wxICON_INFORMATION, this );
		}
		BEGIN_EVENT_TABLE(MainFrame, wxFrame)
			EVT_MENU(ID_Quit,  MainFrame::OnQuit)
			EVT_MENU(ID_About, MainFrame::OnAbout)
		END_EVENT_TABLE()
	}
}