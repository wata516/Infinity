#pragma once

#include <wx/wx.h>
#include <memory>

namespace Infinity
{
	namespace Editor
	{
		class GSGFrame
		{
		public:
			GSGFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
			virtual ~GSGFrame();

			wxFrame *get();
		private:
			class Impl;
			std::unique_ptr<Impl> mImpl;
		};
	}
}
