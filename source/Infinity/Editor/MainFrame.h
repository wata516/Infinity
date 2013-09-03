#pragma once

#include <wx/wx.h>
#include <memory>

namespace Infinity
{
	namespace Editor
	{
		class MainFrame
		{
		public:
			MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
			virtual ~MainFrame();

			wxFrame *get();
		private:
			class Impl;
			std::unique_ptr<Impl> mImpl;
		};
	}
}
