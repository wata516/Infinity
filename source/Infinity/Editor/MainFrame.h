#pragma once

#include <wx/wx.h>
#include <memory>

namespace Infinity
{
	namespace Renderer
	{
		class IRenderer;
	}

	namespace Editor
	{
		class MainPanel;
		class MainFrame: public wxFrame
		{
			enum
			{
				ID_Quit = 1,
				ID_About,
			};
			Infinity::Renderer::IRenderer *mRenderer;
			std::unique_ptr<Infinity::Editor::MainPanel> mMainPanel;

		public:
			MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

			void OnQuit(wxCommandEvent& event);
			void OnAbout(wxCommandEvent& event);

			DECLARE_EVENT_TABLE()
		};
	}
}
