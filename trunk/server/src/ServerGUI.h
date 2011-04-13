///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ServerGUI__
#define __ServerGUI__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ServerGUI
///////////////////////////////////////////////////////////////////////////////
class ServerGUI : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* StaticTextStatus;
		
		wxButton* ButtonStart;
		wxButton* ButtonStop;
		
		wxTextCtrl* TextCtrlLog;
	
	public:
		
		ServerGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Open Online Judge (Server)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~ServerGUI();
	
};

#endif //__ServerGUI__
