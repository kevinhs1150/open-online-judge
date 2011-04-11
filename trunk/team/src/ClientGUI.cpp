///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ClientGUI.h"

///////////////////////////////////////////////////////////////////////////

ClientGUI::ClientGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Team Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Logout"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL, 5 );

	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Problems && Submit Run") ), wxHORIZONTAL );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxVERTICAL );

	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer111->Add( m_choice1, 0, wxALL, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("Download"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_button2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	sbSizer2->Add( bSizer111, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_textCtrl1, 1, wxALL, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button5, 0, wxALL, 5 );

	bSizer12->Add( bSizer14, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	wxArrayString m_choice2Choices;
	m_choice2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	bSizer13->Add( m_choice2, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_button4, 0, wxALL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("Submit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_button3, 0, wxALL, 5 );

	bSizer12->Add( bSizer13, 1, wxALIGN_RIGHT, 5 );

	sbSizer2->Add( bSizer12, 1, wxEXPAND, 5 );

	bSizer11->Add( sbSizer2, 1, wxEXPAND, 5 );

	bSizer1->Add( bSizer11, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("View Runs") ), wxVERTICAL );

	m_listCtrl1 = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	sbSizer21->Add( m_listCtrl1, 1, wxALL|wxEXPAND, 5 );

	bSizer5->Add( sbSizer21, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Clarifications") ), wxVERTICAL );

	m_button6 = new wxButton( this, wxID_ANY, wxT("Ask"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_button6, 0, wxALL|wxEXPAND, 5 );

	m_listCtrl2 = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	sbSizer3->Add( m_listCtrl2, 1, wxALL|wxEXPAND, 5 );

	bSizer5->Add( sbSizer3, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Scoreboard") ), wxVERTICAL );

	m_listCtrl3 = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	sbSizer4->Add( m_listCtrl3, 1, wxALL|wxEXPAND, 5 );

	bSizer5->Add( sbSizer4, 1, wxEXPAND, 5 );

	bSizer1->Add( bSizer5, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

ClientGUI::~ClientGUI()
{
}
