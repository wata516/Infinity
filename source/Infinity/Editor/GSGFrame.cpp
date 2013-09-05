#include <Infinity/Editor/GSGFrame.h>
#include "wx/wxsf/wxShapeFramework.h"

namespace Infinity
{
	namespace Editor
	{
		class GSGFrame::Impl : public wxFrame
		{
			// create wxSF diagram manager
			wxSFDiagramManager m_Manager;
			// create pointer to wxSF shape canvas
			wxSFShapeCanvas* m_pCanvas;

		public:
			Impl(const wxString& title, const wxPoint& pos, const wxSize& size);
			virtual ~Impl();

			DECLARE_EVENT_TABLE()
		};

		BEGIN_EVENT_TABLE(GSGFrame::Impl, wxFrame)
		END_EVENT_TABLE()

		GSGFrame::Impl::Impl(const wxString& title, const wxPoint& pos, const wxSize& size)
			: wxFrame(NULL, -1, title, pos, size)
		{
		}

		GSGFrame::Impl::~Impl()
		{ }

		wxFrame *GSGFrame::get()
		{
			return static_cast<wxFrame*>(mImpl.get());
		}
		GSGFrame::GSGFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
			: mImpl(new Impl(title,pos,size))
		{
		}
		GSGFrame::~GSGFrame()
		{ }
	}
}
