#pragma once
#include <wx/wx.h>

namespace Infinity
{
	namespace Editor
	{
		class MainFrame: public wxFrame
		{
			enum
			{
				ID_Quit = 1,
				ID_About,
			};

		public:
			MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

			void OnQuit(wxCommandEvent& event);
			void OnAbout(wxCommandEvent& event);

			DECLARE_EVENT_TABLE()
		};
	}
}
