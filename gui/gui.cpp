///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

LoginGUI::LoginGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTitle;
	bSizerTitle = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTitle = new wxStaticText( this, wxID_ANY, wxT("Open Online Judge"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextTitle->Wrap( -1 );
	m_staticTextTitle->SetFont( wxFont( 20, 74, 90, 92, false, wxEmptyString ) );
	
	bSizerTitle->Add( m_staticTextTitle, 1, wxALL, 5 );
	
	bSizerMain->Add( bSizerTitle, 0, wxEXPAND, 5 );
	
	m_staticlineTop = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineTop, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerID;
	bSizerID = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextID = new wxStaticText( this, wxID_ANY, wxT("Login ID:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticTextID->Wrap( -1 );
	m_staticTextID->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerID->Add( m_staticTextID, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlID->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerID->Add( m_textCtrlID, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerID->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerID, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerPassword;
	bSizerPassword = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextPassword = new wxStaticText( this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticTextPassword->Wrap( -1 );
	m_staticTextPassword->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerPassword->Add( m_staticTextPassword, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	m_textCtrlPassword->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerPassword->Add( m_textCtrlPassword, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerPassword->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerPassword, 0, wxEXPAND, 5 );
	
	m_staticlineMid = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineMid, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonOK = new wxButton( this, wxID_ANY, wxT("Login"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_buttonOK->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerButton->Add( m_buttonOK, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_buttonCancel->SetFont( wxFont( 14, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerButton->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerButton, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LoginGUI::OnClose ) );
	m_textCtrlPassword->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( LoginGUI::OnTextEnterPassword ), NULL, this );
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginGUI::OnButtonClickLogin ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginGUI::OnButtonClickExit ), NULL, this );
}

LoginGUI::~LoginGUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LoginGUI::OnClose ) );
	m_textCtrlPassword->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( LoginGUI::OnTextEnterPassword ), NULL, this );
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginGUI::OnButtonClickLogin ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginGUI::OnButtonClickExit ), NULL, this );
	
}

AdminGUI::AdminGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTitle;
	bSizerTitle = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, wxT("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	bSizerTitle->Add( m_staticTextTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTitle->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextName = new wxStaticText( this, wxID_ANY, wxT("AdminName"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextName->Wrap( -1 );
	bSizerTitle->Add( m_staticTextName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonLogout = new wxButton( this, wxID_ANY, wxT("Logout"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonLogout, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerMain->Add( bSizerTitle, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerNotebook;
	bSizerNotebook = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelAccounts = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerAccountPage;
	bSizerAccountPage = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerAccount;
	bSizerAccount = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerAdminJudge;
	bSizerAdminJudge = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerAdmin;
	sbSizerAdmin = new wxStaticBoxSizer( new wxStaticBox( m_panelAccounts, wxID_ANY, wxT("Admin") ), wxVERTICAL );
	
	m_listCtrlAdmin = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST );
	sbSizerAdmin->Add( m_listCtrlAdmin, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAdminJudge->Add( sbSizerAdmin, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerJudge;
	sbSizerJudge = new wxStaticBoxSizer( new wxStaticBox( m_panelAccounts, wxID_ANY, wxT("Judge") ), wxVERTICAL );
	
	m_listCtrlJudge = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST );
	sbSizerJudge->Add( m_listCtrlJudge, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAdminJudge->Add( sbSizerJudge, 1, wxEXPAND, 5 );
	
	bSizerAccount->Add( bSizerAdminJudge, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerTeam;
	sbSizerTeam = new wxStaticBoxSizer( new wxStaticBox( m_panelAccounts, wxID_ANY, wxT("Team") ), wxVERTICAL );
	
	m_listCtrlTeam = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST );
	sbSizerTeam->Add( m_listCtrlTeam, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAccount->Add( sbSizerTeam, 1, wxEXPAND, 5 );
	
	bSizerAccountPage->Add( bSizerAccount, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerAccountButton;
	bSizerAccountButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAccountNew = new wxButton( m_panelAccounts, wxID_ANY, wxT("New Account"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAccountButton->Add( m_buttonAccountNew, 2, wxALL, 5 );
	
	m_buttonAccountRefresh = new wxButton( m_panelAccounts, wxID_ANY, wxT("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAccountButton->Add( m_buttonAccountRefresh, 1, wxALL, 5 );
	
	m_buttonAccountApply = new wxButton( m_panelAccounts, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAccountButton->Add( m_buttonAccountApply, 1, wxALL, 5 );
	
	bSizerAccountPage->Add( bSizerAccountButton, 0, wxEXPAND, 5 );
	
	m_panelAccounts->SetSizer( bSizerAccountPage );
	m_panelAccounts->Layout();
	bSizerAccountPage->Fit( m_panelAccounts );
	m_notebook->AddPage( m_panelAccounts, wxT("Accounts"), true );
	m_panelContestInfo = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerContestInfoPage;
	bSizerContestInfoPage = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerContestTitle;
	bSizerContestTitle = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextContestTitle = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("Contest Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextContestTitle->Wrap( -1 );
	bSizerContestTitle->Add( m_staticTextContestTitle, 0, wxALL, 5 );
	
	m_textCtrlContestTitle = new wxTextCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerContestTitle->Add( m_textCtrlContestTitle, 0, wxALL, 5 );
	
	bSizerContestInfoPage->Add( bSizerContestTitle, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerContestInfoTime;
	sbSizerContestInfoTime = new wxStaticBoxSizer( new wxStaticBox( m_panelContestInfo, wxID_ANY, wxT("Time") ), wxVERTICAL );
	
	wxBoxSizer* bSizerTimeSchedule;
	bSizerTimeSchedule = new wxBoxSizer( wxVERTICAL );
	
	m_radioBtnTimeSchedule = new wxRadioButton( m_panelContestInfo, wxID_ANY, wxT("Schedule"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizerTimeSchedule->Add( m_radioBtnTimeSchedule, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTimeScheduleFromTo;
	bSizerTimeScheduleFromTo = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeScheduleFrom = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("From"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleFrom->Wrap( -1 );
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleFrom, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleFromHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 24, 0 );
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleFromHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleColonFrom = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleColonFrom->Wrap( -1 );
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleColonFrom, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleFromMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleFromMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleTo = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("To"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTo->Wrap( -1 );
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleTo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleToHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 24, 0 );
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleToHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleColonTo = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleColonTo->Wrap( -1 );
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleColonTo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleToMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleToMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeSchedule->Add( bSizerTimeScheduleFromTo, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTimeScheduleTotal;
	bSizerTimeScheduleTotal = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeScheduleTotal = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("Total"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotal->Wrap( -1 );
	bSizerTimeScheduleTotal->Add( m_staticTextTimeScheduleTotal, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 99, 0 );
	bSizerTimeScheduleTotal->Add( m_spinCtrlTimeScheduleTotalHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleTotalColon = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotalColon->Wrap( -1 );
	bSizerTimeScheduleTotal->Add( m_staticTextTimeScheduleTotalColon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizerTimeScheduleTotal->Add( m_spinCtrlTimeScheduleTotalMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTimeScheduleTotal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonTimeScheduleSet = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTimeScheduleTotal->Add( m_buttonTimeScheduleSet, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeSchedule->Add( bSizerTimeScheduleTotal, 0, wxEXPAND, 5 );
	
	sbSizerContestInfoTime->Add( bSizerTimeSchedule, 0, wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( m_panelContestInfo, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sbSizerContestInfoTime->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizerTimeManual;
	bSizerTimeManual = new wxBoxSizer( wxVERTICAL );
	
	m_radioBtnTimeManual = new wxRadioButton( m_panelContestInfo, wxID_ANY, wxT("Manual"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTimeManual->Add( m_radioBtnTimeManual, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTimeManualTotal;
	bSizerTimeManualTotal = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeScheduleTotal1 = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("Total"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotal1->Wrap( -1 );
	bSizerTimeManualTotal->Add( m_staticTextTimeScheduleTotal1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalHr1 = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 99, 0 );
	bSizerTimeManualTotal->Add( m_spinCtrlTimeScheduleTotalHr1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleTotalColon1 = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotalColon1->Wrap( -1 );
	bSizerTimeManualTotal->Add( m_staticTextTimeScheduleTotalColon1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalMin1 = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizerTimeManualTotal->Add( m_spinCtrlTimeScheduleTotalMin1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTimeManualTotal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonTimeScheduleSet1 = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTimeManualTotal->Add( m_buttonTimeScheduleSet1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeManual->Add( bSizerTimeManualTotal, 1, wxEXPAND, 5 );
	
	sbSizerContestInfoTime->Add( bSizerTimeManual, 0, wxEXPAND, 5 );
	
	bSizerContestInfoPage->Add( sbSizerContestInfoTime, 1, wxEXPAND, 5 );
	
	m_panelContestInfo->SetSizer( bSizerContestInfoPage );
	m_panelContestInfo->Layout();
	bSizerContestInfoPage->Fit( m_panelContestInfo );
	m_notebook->AddPage( m_panelContestInfo, wxT("Contest Info"), false );
	m_panelProblems = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerProblemsPage;
	bSizerProblemsPage = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerProblemList;
	bSizerProblemList = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextProblems = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Problems:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblems->Wrap( -1 );
	bSizerProblemList->Add( m_staticTextProblems, 0, wxALL, 5 );
	
	m_listCtrlProblems = new wxListCtrl( m_panelProblems, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST );
	bSizerProblemList->Add( m_listCtrlProblems, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemsButton;
	bSizerProblemsButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonProblemAdd = new wxButton( m_panelProblems, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemsButton->Add( m_buttonProblemAdd, 1, wxALL, 5 );
	
	m_buttonProblemDel = new wxButton( m_panelProblems, wxID_ANY, wxT("Del"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemsButton->Add( m_buttonProblemDel, 1, wxALL, 5 );
	
	bSizerProblemList->Add( bSizerProblemsButton, 0, wxEXPAND, 5 );
	
	bSizerProblemsPage->Add( bSizerProblemList, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText39 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Problem Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer54->Add( m_staticText39, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlProblemName = new wxTextCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer54->Add( m_textCtrlProblemName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer51->Add( bSizer54, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox1 = new wxCheckBox( m_panelProblems, wxID_ANY, wxT("Problem File:"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( m_checkBox1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker1 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer55->Add( m_filePicker1, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer51->Add( bSizer55, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText47 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Time Limit:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	bSizer64->Add( m_staticText47, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrl13 = new wxSpinCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer64->Add( m_spinCtrl13, 0, wxALL, 5 );
	
	m_staticText48 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	bSizer64->Add( m_staticText48, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer51->Add( bSizer64, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( m_panelProblems, wxID_ANY, wxT("Sample Data") ), wxVERTICAL );
	
	m_checkBox2 = new wxCheckBox( m_panelProblems, wxID_ANY, wxT("Offering sample data"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( m_checkBox2, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTestingInput;
	bSizerTestingInput = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText40 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizerTestingInput->Add( m_staticText40, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker2 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerTestingInput->Add( m_filePicker2, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizer12->Add( bSizerTestingInput, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTestingInput1;
	bSizerTestingInput1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	bSizerTestingInput1->Add( m_staticText401, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker21 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerTestingInput1->Add( m_filePicker21, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizer12->Add( bSizerTestingInput1, 0, wxEXPAND, 5 );
	
	bSizer51->Add( sbSizer12, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer121;
	sbSizer121 = new wxStaticBoxSizer( new wxStaticBox( m_panelProblems, wxID_ANY, wxT("Official Data") ), wxVERTICAL );
	
	wxBoxSizer* bSizerTestingInput2;
	bSizerTestingInput2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText402 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText402->Wrap( -1 );
	bSizerTestingInput2->Add( m_staticText402, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker22 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerTestingInput2->Add( m_filePicker22, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizer121->Add( bSizerTestingInput2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTestingInput11;
	bSizerTestingInput11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4011 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4011->Wrap( -1 );
	bSizerTestingInput11->Add( m_staticText4011, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker211 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerTestingInput11->Add( m_filePicker211, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizer121->Add( bSizerTestingInput11, 0, wxEXPAND, 5 );
	
	bSizer51->Add( sbSizer121, 0, wxEXPAND, 5 );
	
	
	bSizer51->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer65->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button27 = new wxButton( m_panelProblems, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( m_button27, 0, wxALL, 5 );
	
	bSizer51->Add( bSizer65, 0, wxEXPAND, 5 );
	
	bSizerProblemsPage->Add( bSizer51, 2, wxEXPAND, 5 );
	
	m_panelProblems->SetSizer( bSizerProblemsPage );
	m_panelProblems->Layout();
	bSizerProblemsPage->Fit( m_panelProblems );
	m_notebook->AddPage( m_panelProblems, wxT("Problems"), false );
	m_panel4 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook->AddPage( m_panel4, wxT("a page"), false );
	
	bSizerNotebook->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	bSizerMain->Add( bSizerNotebook, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
}

AdminGUI::~AdminGUI()
{
}

NewAccount::NewAccount( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerAccType;
	sbSizerAccType = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Account Type") ), wxHORIZONTAL );
	
	m_radioBtnAdmin = new wxRadioButton( this, wxID_ANY, wxT("Admin"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerAccType->Add( m_radioBtnAdmin, 0, wxALL, 5 );
	
	m_radioBtnJudge = new wxRadioButton( this, wxID_ANY, wxT("Judge"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerAccType->Add( m_radioBtnJudge, 0, wxALL, 5 );
	
	m_radioBtnTeam = new wxRadioButton( this, wxID_ANY, wxT("Team"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerAccType->Add( m_radioBtnTeam, 0, wxALL, 5 );
	
	bSizerMain->Add( sbSizerAccType, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerLoginInfo;
	sbSizerLoginInfo = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Login Info") ), wxVERTICAL );
	
	wxBoxSizer* bSizerID;
	bSizerID = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextID = new wxStaticText( this, wxID_ANY, wxT("ID:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticTextID->Wrap( -1 );
	bSizerID->Add( m_staticTextID, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerID->Add( m_textCtrlID, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerLoginInfo->Add( bSizerID, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerPassword;
	bSizerPassword = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextPassword = new wxStaticText( this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticTextPassword->Wrap( -1 );
	bSizerPassword->Add( m_staticTextPassword, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizerPassword->Add( m_textCtrlPassword, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerLoginInfo->Add( bSizerPassword, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonOK, 1, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonCancel, 1, wxALL, 5 );
	
	sbSizerLoginInfo->Add( bSizerButton, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( sbSizerLoginInfo, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewAccount::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewAccount::OnButtonClickCancel ), NULL, this );
}

NewAccount::~NewAccount()
{
	// Disconnect Events
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewAccount::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewAccount::OnButtonClickCancel ), NULL, this );
	
}

TeamGUI::TeamGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTitle;
	bSizerTitle = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, wxT("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	bSizerTitle->Add( m_staticTextTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTitle->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextTeamName = new wxStaticText( this, wxID_ANY, wxT("Team Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTeamName->Wrap( -1 );
	bSizerTitle->Add( m_staticTextTeamName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonLogout = new wxButton( this, wxID_ANY, wxT("Logout"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonLogout, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerTitle, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerMid;
	sbSizerMid = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Problems && Submit Run") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizerProblem;
	bSizerProblem = new wxBoxSizer( wxVERTICAL );
	
	wxArrayString m_choiceProblemChoices;
	m_choiceProblem = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceProblemChoices, 0 );
	m_choiceProblem->SetSelection( 0 );
	bSizerProblem->Add( m_choiceProblem, 0, wxALL, 5 );
	
	m_buttonDownload = new wxButton( this, wxID_ANY, wxT("Download"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblem->Add( m_buttonDownload, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );
	
	sbSizerMid->Add( bSizerProblem, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerSubmit;
	bSizerSubmit = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerBrowse;
	bSizerBrowse = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlFilePath = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerBrowse->Add( m_textCtrlFilePath, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonBrowse = new wxButton( this, wxID_ANY, wxT("..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerBrowse->Add( m_buttonBrowse, 0, wxALL, 5 );
	
	bSizerSubmit->Add( bSizerBrowse, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerLangSubmit;
	bSizerLangSubmit = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_choiceLangChoices;
	m_choiceLang = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceLangChoices, 0 );
	m_choiceLang->SetSelection( 0 );
	bSizerLangSubmit->Add( m_choiceLang, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonTest = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerLangSubmit->Add( m_buttonTest, 0, wxALL, 5 );
	
	m_buttonSubmit = new wxButton( this, wxID_ANY, wxT("Submit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerLangSubmit->Add( m_buttonSubmit, 0, wxALL, 5 );
	
	bSizerSubmit->Add( bSizerLangSubmit, 1, wxALIGN_RIGHT, 5 );
	
	sbSizerMid->Add( bSizerSubmit, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( sbSizerMid, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerDown;
	bSizerDown = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerRuns;
	sbSizerRuns = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("View Runs") ), wxVERTICAL );
	
	m_listCtrlRuns = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizerRuns->Add( m_listCtrlRuns, 1, wxALL|wxEXPAND, 5 );
	
	bSizerDown->Add( sbSizerRuns, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerClars;
	sbSizerClars = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Clarifications") ), wxVERTICAL );
	
	m_buttonAsk = new wxButton( this, wxID_ANY, wxT("Ask"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerClars->Add( m_buttonAsk, 0, wxALL|wxEXPAND, 5 );
	
	m_listCtrlClars = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizerClars->Add( m_listCtrlClars, 1, wxALL|wxEXPAND, 5 );
	
	bSizerDown->Add( sbSizerClars, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerScoreboard;
	sbSizerScoreboard = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Scoreboard") ), wxVERTICAL );
	
	m_listCtrlScore = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizerScoreboard->Add( m_listCtrlScore, 1, wxALL|wxEXPAND, 5 );
	
	bSizerDown->Add( sbSizerScoreboard, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerDown, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonLogout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickLogout ), NULL, this );
	m_buttonDownload->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickDownload ), NULL, this );
	m_buttonBrowse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickBrowse ), NULL, this );
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickTest ), NULL, this );
	m_buttonSubmit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickSubmit ), NULL, this );
	m_buttonAsk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickAsk ), NULL, this );
}

TeamGUI::~TeamGUI()
{
	// Disconnect Events
	m_buttonLogout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickLogout ), NULL, this );
	m_buttonDownload->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickDownload ), NULL, this );
	m_buttonBrowse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickBrowse ), NULL, this );
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickTest ), NULL, this );
	m_buttonSubmit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickSubmit ), NULL, this );
	m_buttonAsk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickAsk ), NULL, this );
	
}

SubmitConfirmGUI::SubmitConfirmGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextTitle = new wxStaticText( this, wxID_ANY, wxT("Confirm Submission"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextTitle->Wrap( -1 );
	m_staticTextTitle->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );
	
	bSizerMain->Add( m_staticTextTitle, 0, wxALL|wxEXPAND, 5 );
	
	m_staticlineUp = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineUp, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerProblem;
	bSizerProblem = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblem = new wxStaticText( this, wxID_ANY, wxT("Problem:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblem->Wrap( -1 );
	m_staticTextProblem->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerProblem->Add( m_staticTextProblem, 0, wxALL, 5 );
	
	m_staticTextProblemVal = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemVal->Wrap( -1 );
	m_staticTextProblemVal->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerProblem->Add( m_staticTextProblemVal, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerProblem, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizeLang;
	bSizeLang = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextLang = new wxStaticText( this, wxID_ANY, wxT("Language:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLang->Wrap( -1 );
	m_staticTextLang->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizeLang->Add( m_staticTextLang, 0, wxALL, 5 );
	
	m_staticTextLangVal = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLangVal->Wrap( -1 );
	m_staticTextLangVal->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizeLang->Add( m_staticTextLangVal, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizeLang, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerFilePath;
	bSizerFilePath = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextFilePath = new wxStaticText( this, wxID_ANY, wxT("File Path:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFilePath->Wrap( -1 );
	m_staticTextFilePath->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerFilePath->Add( m_staticTextFilePath, 0, wxALL, 5 );
	
	m_textCtrlFilePathVal = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER );
	m_textCtrlFilePathVal->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	m_textCtrlFilePathVal->SetBackgroundColour( wxColour( 171, 171, 171 ) );
	
	bSizerFilePath->Add( m_textCtrlFilePathVal, 1, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerFilePath, 1, wxEXPAND, 5 );
	
	m_staticlineDown = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineDown, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerbutton;
	bSizerbutton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerbutton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonYes = new wxButton( this, wxID_ANY, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerbutton->Add( m_buttonYes, 0, wxALL, 5 );
	
	m_buttonNo = new wxButton( this, wxID_ANY, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerbutton->Add( m_buttonNo, 0, wxALL, 5 );
	
	
	bSizerbutton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerbutton, 0, wxBOTTOM|wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubmitConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubmitConfirmGUI::OnButtonClickNo ), NULL, this );
}

SubmitConfirmGUI::~SubmitConfirmGUI()
{
	// Disconnect Events
	m_buttonYes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubmitConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubmitConfirmGUI::OnButtonClickNo ), NULL, this );
	
}

ClarDialogGUI::ClarDialogGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTitle;
	bSizerTitle = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextTitle = new wxStaticText( this, wxID_ANY, wxT("Clarification"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTitle->Wrap( -1 );
	m_staticTextTitle->SetFont( wxFont( 16, 74, 90, 92, false, wxEmptyString ) );
	
	bSizerTitle->Add( m_staticTextTitle, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	bSizerMain->Add( bSizerTitle, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblem;
	bSizerProblem = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblem = new wxStaticText( this, wxID_ANY, wxT("Problem:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblem->Wrap( -1 );
	m_staticTextProblem->SetFont( wxFont( 16, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerProblem->Add( m_staticTextProblem, 0, wxALL, 5 );
	
	wxArrayString m_choice3Choices;
	m_choice3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	bSizerProblem->Add( m_choice3, 1, wxALL, 5 );
	
	bSizerMain->Add( bSizerProblem, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerQuestion;
	bSizerQuestion = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextQuestion = new wxStaticText( this, wxID_ANY, wxT("Question:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextQuestion->Wrap( -1 );
	m_staticTextQuestion->SetFont( wxFont( 16, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerQuestion->Add( m_staticTextQuestion, 0, wxALL, 5 );
	
	m_textCtrlFileQuestion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER );
	m_textCtrlFileQuestion->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerQuestion->Add( m_textCtrlFileQuestion, 1, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerQuestion, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonYes = new wxButton( this, wxID_ANY, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonYes, 0, wxALL, 5 );
	
	m_buttonNo = new wxButton( this, wxID_ANY, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonNo, 0, wxALL, 5 );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerButton, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarDialogGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarDialogGUI::OnButtonClickNo ), NULL, this );
}

ClarDialogGUI::~ClarDialogGUI()
{
	// Disconnect Events
	m_buttonYes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarDialogGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarDialogGUI::OnButtonClickNo ), NULL, this );
	
}

ClarConfirmGUI::ClarConfirmGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextTitle = new wxStaticText( this, wxID_ANY, wxT("Confirm Clarification"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextTitle->Wrap( -1 );
	m_staticTextTitle->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );
	
	bSizerMain->Add( m_staticTextTitle, 0, wxALL|wxEXPAND, 5 );
	
	m_staticlineUp = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineUp, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerProblem;
	bSizerProblem = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblem = new wxStaticText( this, wxID_ANY, wxT("Problem:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblem->Wrap( -1 );
	m_staticTextProblem->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerProblem->Add( m_staticTextProblem, 0, wxALL, 5 );
	
	m_staticTextProblemVal = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemVal->Wrap( -1 );
	m_staticTextProblemVal->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerProblem->Add( m_staticTextProblemVal, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerProblem, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerQuestion;
	bSizerQuestion = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextQuestion = new wxStaticText( this, wxID_ANY, wxT("Question:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextQuestion->Wrap( -1 );
	m_staticTextQuestion->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerQuestion->Add( m_staticTextQuestion, 0, wxALL, 5 );
	
	m_textCtrlFileQuestion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER );
	m_textCtrlFileQuestion->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	m_textCtrlFileQuestion->SetBackgroundColour( wxColour( 171, 171, 171 ) );
	
	bSizerQuestion->Add( m_textCtrlFileQuestion, 1, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerQuestion, 1, wxEXPAND, 5 );
	
	m_staticlineDown = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineDown, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonYes = new wxButton( this, wxID_ANY, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonYes, 0, wxALL, 5 );
	
	m_buttonNo = new wxButton( this, wxID_ANY, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonNo, 0, wxALL, 5 );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerButton, 0, wxBOTTOM|wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarConfirmGUI::OnButtonClickNo ), NULL, this );
}

ClarConfirmGUI::~ClarConfirmGUI()
{
	// Disconnect Events
	m_buttonYes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ClarConfirmGUI::OnButtonClickNo ), NULL, this );
	
}

JudgeGUI::JudgeGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTitle;
	bSizerTitle = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, wxT("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	bSizerTitle->Add( m_staticTextTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTitle->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextName = new wxStaticText( this, wxID_ANY, wxT("Judge Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextName->Wrap( -1 );
	bSizerTitle->Add( m_staticTextName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonLogout = new wxButton( this, wxID_ANY, wxT("Logout"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonLogout, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerTitle, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRunsAndClars;
	bSizerRunsAndClars = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerRuns;
	sbSizerRuns = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Runs") ), wxVERTICAL );
	
	wxBoxSizer* bSizerFilter;
	bSizerFilter = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_choiceFilterChoices;
	m_choiceFilter = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceFilterChoices, 0 );
	m_choiceFilter->SetSelection( 0 );
	bSizerFilter->Add( m_choiceFilter, 0, wxALL, 5 );
	
	m_checkBoxAutoJudge = new wxCheckBox( this, wxID_ANY, wxT("AutoJudge"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerFilter->Add( m_checkBoxAutoJudge, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerFilter->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextNewUnjudgeCount = new wxStaticText( this, wxID_ANY, wxT("UNJudgeNum"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextNewUnjudgeCount->Wrap( -1 );
	m_staticTextNewUnjudgeCount->SetFont( wxFont( 9, 74, 90, 92, false, wxT("Arial") ) );
	m_staticTextNewUnjudgeCount->SetForegroundColour( wxColour( 255, 0, 0 ) );
	
	bSizerFilter->Add( m_staticTextNewUnjudgeCount, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerRuns->Add( bSizerFilter, 0, wxEXPAND, 5 );
	
	m_listCtrlRuns = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizerRuns->Add( m_listCtrlRuns, 1, wxALL|wxEXPAND, 5 );
	
	bSizerRunsAndClars->Add( sbSizerRuns, 3, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerClars;
	sbSizerClars = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Clarifications") ), wxVERTICAL );
	
	m_listCtrlClars = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizerClars->Add( m_listCtrlClars, 1, wxALL|wxEXPAND, 5 );
	
	bSizerRunsAndClars->Add( sbSizerClars, 2, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerRunsAndClars, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonLogout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickLogout ), NULL, this );
}

JudgeGUI::~JudgeGUI()
{
	// Disconnect Events
	m_buttonLogout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickLogout ), NULL, this );
	
}

JudgementConfirmGUI::JudgementConfirmGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextTitle = new wxStaticText( this, wxID_ANY, wxT("Confirm Clarification"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextTitle->Wrap( -1 );
	m_staticTextTitle->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );
	
	bSizerMain->Add( m_staticTextTitle, 0, wxALL|wxEXPAND, 5 );
	
	m_staticlineUp = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineUp, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerJudgement;
	bSizerJudgement = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextJudgement = new wxStaticText( this, wxID_ANY, wxT("Judgement:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextJudgement->Wrap( -1 );
	m_staticTextJudgement->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerJudgement->Add( m_staticTextJudgement, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextJudgementVal = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextJudgementVal->Wrap( -1 );
	m_staticTextJudgementVal->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizerJudgement->Add( m_staticTextJudgementVal, 0, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerJudgement, 0, wxEXPAND, 5 );
	
	m_staticlineDown = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticlineDown, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonYes = new wxButton( this, wxID_ANY, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonYes, 0, wxALL, 5 );
	
	m_buttonNo = new wxButton( this, wxID_ANY, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonNo, 0, wxALL, 5 );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerButton, 0, wxBOTTOM|wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgementConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgementConfirmGUI::OnButtonClickNo ), NULL, this );
}

JudgementConfirmGUI::~JudgementConfirmGUI()
{
	// Disconnect Events
	m_buttonYes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgementConfirmGUI::OnButtonClickYes ), NULL, this );
	m_buttonNo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgementConfirmGUI::OnButtonClickNo ), NULL, this );
	
}

JudgeSubmission::JudgeSubmission( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerProblem;
	bSizerProblem = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblemNumber = new wxStaticText( this, wxID_ANY, wxT("Problem:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemNumber->Wrap( -1 );
	bSizerProblem->Add( m_staticTextProblemNumber, 0, wxALL, 5 );
	
	m_staticTextProblemNumberValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemNumberValue->Wrap( -1 );
	bSizerProblem->Add( m_staticTextProblemNumberValue, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerProblem, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTeam;
	bSizerTeam = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTeam = new wxStaticText( this, wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTeam->Wrap( -1 );
	bSizerTeam->Add( m_staticTextTeam, 0, wxALL, 5 );
	
	m_staticTextTeamValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTeamValue->Wrap( -1 );
	bSizerTeam->Add( m_staticTextTeamValue, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerTeam, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerSubmissionNumber;
	bSizerSubmissionNumber = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextSubmission = new wxStaticText( this, wxID_ANY, wxT("Submission Number:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSubmission->Wrap( -1 );
	bSizerSubmissionNumber->Add( m_staticTextSubmission, 0, wxALL, 5 );
	
	m_staticTextSubmissionValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSubmissionValue->Wrap( -1 );
	bSizerSubmissionNumber->Add( m_staticTextSubmissionValue, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerSubmissionNumber, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerInput;
	bSizerInput = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextInputStatus = new wxStaticText( this, wxID_ANY, wxT("Input Data Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextInputStatus->Wrap( -1 );
	bSizerInput->Add( m_staticTextInputStatus, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticTextInputStatusValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextInputStatusValue->Wrap( -1 );
	bSizerInput->Add( m_staticTextInputStatusValue, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerInput->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonShowInputData = new wxButton( this, wxID_ANY, wxT("Show"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerInput->Add( m_buttonShowInputData, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bSizerMain->Add( bSizerInput, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerSourceCode;
	bSizerSourceCode = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextSourceStatus = new wxStaticText( this, wxID_ANY, wxT("Source Code Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSourceStatus->Wrap( -1 );
	bSizerSourceCode->Add( m_staticTextSourceStatus, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticTextSourceStatusValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSourceStatusValue->Wrap( -1 );
	bSizerSourceCode->Add( m_staticTextSourceStatusValue, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerSourceCode->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonShowSource = new wxButton( this, wxID_ANY, wxT("Show"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerSourceCode->Add( m_buttonShowSource, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bSizerMain->Add( bSizerSourceCode, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRunAndStop;
	bSizerRunAndStop = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerRunAndStop->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonRun = new wxButton( this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxSize( 150,50 ), 0 );
	m_buttonRun->SetFont( wxFont( 12, 74, 90, 92, false, wxEmptyString ) );
	
	bSizerRunAndStop->Add( m_buttonRun, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxSize( 150,50 ), 0 );
	m_buttonStop->SetFont( wxFont( 12, 74, 90, 92, false, wxEmptyString ) );
	
	bSizerRunAndStop->Add( m_buttonStop, 0, wxALL, 5 );
	
	
	bSizerRunAndStop->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerRunAndStop, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizerRunStatus;
	bSizerRunStatus = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextRunStatus = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextRunStatus->Wrap( -1 );
	m_staticTextRunStatus->SetFont( wxFont( 12, 74, 90, 90, false, wxEmptyString ) );
	
	bSizerRunStatus->Add( m_staticTextRunStatus, 0, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerRunStatus, 0, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer69->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextResult = new wxStaticText( this, wxID_ANY, wxT("Result:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextResult->Wrap( -1 );
	bSizer69->Add( m_staticTextResult, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString m_choiceJudgementChoices;
	m_choiceJudgement = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 150,-1 ), m_choiceJudgementChoices, 0 );
	m_choiceJudgement->SetSelection( 0 );
	bSizer69->Add( m_choiceJudgement, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_button35 = new wxButton( this, wxID_ANY, wxT("Show Output"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( m_button35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer69->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizer69, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerJudgement;
	bSizerJudgement = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerJudgement->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonJudge = new wxButton( this, wxID_ANY, wxT("Judge"), wxDefaultPosition, wxSize( 150,-1 ), 0 );
	bSizerJudgement->Add( m_buttonJudge, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize( 150,-1 ), 0 );
	bSizerJudgement->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerJudgement->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerJudgement, 0, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
}

JudgeSubmission::~JudgeSubmission()
{
}

JudgeCompare::JudgeCompare( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerInputOutput;
	bSizerInputOutput = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerOfficialOutput;
	sbSizerOfficialOutput = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Official Output") ), wxVERTICAL );
	
	m_textCtrlOfficialOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,400 ), wxTE_MULTILINE );
	sbSizerOfficialOutput->Add( m_textCtrlOfficialOutput, 0, wxALL, 5 );
	
	bSizerInputOutput->Add( sbSizerOfficialOutput, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerUserOutput;
	sbSizerUserOutput = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("User Output") ), wxVERTICAL );
	
	m_textCtrlUserOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,400 ), wxTE_MULTILINE );
	sbSizerUserOutput->Add( m_textCtrlUserOutput, 0, wxALL, 5 );
	
	bSizerInputOutput->Add( sbSizerUserOutput, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerInputOutput, 1, wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMain->Add( m_buttonClose, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
}

JudgeCompare::~JudgeCompare()
{
}

ServerGUI::ServerGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	StaticTextStatus = new wxStaticText( this, wxID_ANY, wxT("Not Running"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	StaticTextStatus->Wrap( -1 );
	StaticTextStatus->SetFont( wxFont( 36, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizer34->Add( StaticTextStatus, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer35->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ButtonStart = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	ButtonStart->SetFont( wxFont( 24, 74, 90, 90, false, wxEmptyString ) );
	
	bSizer35->Add( ButtonStart, 0, wxALL, 5 );
	
	ButtonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	ButtonStop->SetFont( wxFont( 24, 74, 90, 90, false, wxEmptyString ) );
	
	bSizer35->Add( ButtonStop, 0, wxALL, 5 );
	
	
	bSizer35->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer34->Add( bSizer35, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Log") ), wxVERTICAL );
	
	TextCtrlLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	sbSizer7->Add( TextCtrlLog, 1, wxALL|wxEXPAND, 5 );
	
	bSizer34->Add( sbSizer7, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer34 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ButtonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ServerGUI::OnButtonClickStart ), NULL, this );
	ButtonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ServerGUI::OnButtonClickStop ), NULL, this );
}

ServerGUI::~ServerGUI()
{
	// Disconnect Events
	ButtonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ServerGUI::OnButtonClickStart ), NULL, this );
	ButtonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ServerGUI::OnButtonClickStop ), NULL, this );
	
}
