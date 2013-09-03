#include <Infinity/Editor/MainFrame.h>
#include <Infinity/Editor/MainPanel.h>
#include <Infinity/Editor/GSGFrame.h>
#include <Infinity/Renderer/IRenderer.h>
#include <Infinity/Renderer/RendererFactory.h>

namespace Infinity
{
	namespace Editor
	{
		class MainFrame::Impl : public wxFrame
		{
			enum
			{
				ID_Quit = 1,
				ID_GameSeqGraph,
				ID_About,
			};

			Infinity::Renderer::IRenderer *mRenderer;
			std::unique_ptr<Infinity::Editor::MainPanel> mMainPanel;
			std::unique_ptr<Infinity::Editor::GSGFrame> mGSGFrame;

		public:
			void OnQuit(wxCommandEvent& event);
			void OnGameSeqGraph(wxCommandEvent& event);
			void OnAbout(wxCommandEvent& event);

			DECLARE_EVENT_TABLE()
		public:
			Impl(const wxString& title, const wxPoint& pos, const wxSize& size);
			virtual ~Impl() {}
		};

		BEGIN_EVENT_TABLE(MainFrame::Impl, wxFrame)
			EVT_MENU(ID_Quit,  MainFrame::Impl::OnQuit)
			EVT_MENU(ID_GameSeqGraph,  MainFrame::Impl::OnGameSeqGraph)
			EVT_MENU(ID_About, MainFrame::Impl::OnAbout)
		END_EVENT_TABLE()

		MainFrame::Impl::Impl(const wxString& title, const wxPoint& pos, const wxSize& size)
			: wxFrame(NULL, -1, title, pos, size)
		{
			wxMenu *menuFile = new wxMenu;
			wxMenu *menuWindow = new wxMenu;
			wxMenu *menuHelp = new wxMenu;

			menuFile->Append( ID_Quit, _("終了") );
			menuWindow->Append( ID_GameSeqGraph, _("Game Sequence Graph") );
			menuHelp->Append( ID_About, _("バージョン...") );

			wxMenuBar *menuBar = new wxMenuBar;
			menuBar->Append( menuFile, _("ファイル") );
			menuBar->Append( menuWindow, _("ウィンドウ") );
			menuBar->Append( menuHelp, _("ヘルプ") );

			SetMenuBar( menuBar );

			CreateStatusBar();
			SetStatusText( _("") );

			Infinity::Renderer::RendererFactory::Create("SDL",&mRenderer);
			mMainPanel.reset(new Infinity::Editor::MainPanel(this, mRenderer->CreateSurface(size.GetWidth(),size.GetHeight())));
		}

		void MainFrame::Impl::OnQuit(wxCommandEvent& WXUNUSED(event))
		{
			mMainPanel.reset();
			mGSGFrame.reset();
			mRenderer->Destroy();
			Infinity::Renderer::RendererFactory::Destroy(&mRenderer);
			Close(true);
		}

		void MainFrame::Impl::OnGameSeqGraph(wxCommandEvent& event)
		{
			mGSGFrame.reset(new Infinity::Editor::GSGFrame(_(""), wxDefaultPosition, wxSize(900,700)));
			mGSGFrame->get()->Show(true);
		}

		void MainFrame::Impl::OnAbout(wxCommandEvent& WXUNUSED(event))
		{
			wxMessageBox( _("Version 0.01"),
				_("About Editor"),
				wxOK | wxICON_INFORMATION, this );
		}

		MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
		: mImpl(new Impl(title,pos,size))
		{
		}
		
		MainFrame::~MainFrame()
		{

		}

		wxFrame *MainFrame::get()
		{
			return static_cast<wxFrame*>(mImpl.get());
		}

	}
}
