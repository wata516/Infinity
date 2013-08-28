#include <Infinity/Editor/MainFrame.h>
#include <Infinity/Editor/MainPanel.h>

#include <Infinity/Renderer/IRenderer.h>
#include <Infinity/Renderer/RendererFactory.h>

namespace Infinity
{
	namespace Editor
	{
		MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
			: wxFrame(NULL, -1, title, pos, size)
		{
			wxMenu *menuFile = new wxMenu;
			wxMenu *menuHelp = new wxMenu;

			menuFile->Append( ID_Quit, _("終了") );
			menuHelp->Append( ID_About, _("バージョン...") );

			wxMenuBar *menuBar = new wxMenuBar;
			menuBar->Append( menuFile, _("ファイル") );
			menuBar->Append( menuHelp, _("ヘルプ") );

			SetMenuBar( menuBar );

			CreateStatusBar();
			SetStatusText( _("") );

			Infinity::Renderer::RendererFactory::Create("SDL",&mRenderer);
			mMainPanel.reset(new Infinity::Editor::MainPanel(this, mRenderer->CreateSurface(size.GetWidth(),size.GetHeight())));

		}

		void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
		{
			mMainPanel.reset();
			mRenderer->Destroy();
			Infinity::Renderer::RendererFactory::Destroy(&mRenderer);
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
