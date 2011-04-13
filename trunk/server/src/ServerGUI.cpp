///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ServerGUI.h"

///////////////////////////////////////////////////////////////////////////

ServerGUI::ServerGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* SizerMain;
	SizerMain = new wxBoxSizer( wxVERTICAL );
	
	StaticTextStatus = new wxStaticText( this, wxID_ANY, wxT("Not Running"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	StaticTextStatus->Wrap( -1 );
	StaticTextStatus->SetFont( wxFont( 48, 74, 90, 90, false, wxEmptyString ) );
	
	SizerMain->Add( StaticTextStatus, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* SizerButton;
	SizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	SizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ButtonStart = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	ButtonStart->SetFont( wxFont( 24, 74, 90, 90, false, wxEmptyString ) );
	
	SizerButton->Add( ButtonStart, 0, wxALL, 5 );
	
	ButtonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	ButtonStop->SetFont( wxFont( 24, 74, 90, 90, false, wxEmptyString ) );
	
	SizerButton->Add( ButtonStop, 0, wxALL, 5 );
	
	
	SizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	SizerMain->Add( SizerButton, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* SizerLog;
	SizerLog = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Log") ), wxVERTICAL );
	
	TextCtrlLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	SizerLog->Add( TextCtrlLog, 1, wxALL|wxEXPAND, 5 );
	
	SizerMain->Add( SizerLog, 1, wxEXPAND, 5 );
	
	this->SetSizer( SizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
}

ServerGUI::~ServerGUI()
{
}
