///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ClientGUI__
#define __ClientGUI__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ClientGUI
///////////////////////////////////////////////////////////////////////////////
class ClientGUI : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		
		wxStaticText* m_staticText2;
		wxButton* m_button1;
		wxChoice* m_choice1;
		wxButton* m_button2;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_button5;
		wxChoice* m_choice2;
		wxButton* m_button4;
		wxButton* m_button3;
		wxListCtrl* m_listCtrl1;
		wxButton* m_button6;
		wxListCtrl* m_listCtrl2;
		wxListCtrl* m_listCtrl3;
	
	public:
		
		ClientGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OOJ Client"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~ClientGUI();
	
};

#endif //__ClientGUI__
