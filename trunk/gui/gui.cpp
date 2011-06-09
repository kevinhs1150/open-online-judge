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
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, wxT("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	m_staticTextTime->SetFont( wxFont( 12, 74, 90, 92, false, wxEmptyString ) );
	
	bSizerTitle->Add( m_staticTextTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTitle->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextName = new wxStaticText( this, wxID_ANY, wxT("AdminName"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextName->Wrap( -1 );
	bSizerTitle->Add( m_staticTextName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonChangePassword = new wxButton( this, wxID_ANY, wxT("Change Password"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonChangePassword, 0, wxALL, 5 );
	
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
	
	m_listCtrlAdmin = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	sbSizerAdmin->Add( m_listCtrlAdmin, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAdminJudge->Add( sbSizerAdmin, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerJudge;
	sbSizerJudge = new wxStaticBoxSizer( new wxStaticBox( m_panelAccounts, wxID_ANY, wxT("Judge") ), wxVERTICAL );
	
	m_listCtrlJudge = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	sbSizerJudge->Add( m_listCtrlJudge, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAdminJudge->Add( sbSizerJudge, 1, wxEXPAND, 5 );
	
	bSizerAccount->Add( bSizerAdminJudge, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerTeam;
	sbSizerTeam = new wxStaticBoxSizer( new wxStaticBox( m_panelAccounts, wxID_ANY, wxT("Team") ), wxVERTICAL );
	
	m_listCtrlTeam = new wxListCtrl( m_panelAccounts, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	sbSizerTeam->Add( m_listCtrlTeam, 1, wxALL|wxEXPAND, 5 );
	
	bSizerAccount->Add( sbSizerTeam, 1, wxEXPAND, 5 );
	
	bSizerAccountPage->Add( bSizerAccount, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerAccountButton;
	bSizerAccountButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAccountNew = new wxButton( m_panelAccounts, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAccountButton->Add( m_buttonAccountNew, 1, wxALL, 5 );
	
	m_buttonAccountDelete = new wxButton( m_panelAccounts, wxID_ANY, wxT("Del"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAccountButton->Add( m_buttonAccountDelete, 1, wxALL, 5 );
	
	bSizerAccountPage->Add( bSizerAccountButton, 0, wxEXPAND, 5 );
	
	m_panelAccounts->SetSizer( bSizerAccountPage );
	m_panelAccounts->Layout();
	bSizerAccountPage->Fit( m_panelAccounts );
	m_notebook->AddPage( m_panelAccounts, wxT("Accounts"), false );
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
	m_radioBtnTimeSchedule->Enable( false );
	
	bSizerTimeSchedule->Add( m_radioBtnTimeSchedule, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTimeScheduleFromTo;
	bSizerTimeScheduleFromTo = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeScheduleFrom = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("From"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleFrom->Wrap( -1 );
	m_staticTextTimeScheduleFrom->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleFrom, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleFromHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 24, 0 );
	m_spinCtrlTimeScheduleFromHr->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleFromHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleColonFrom = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleColonFrom->Wrap( -1 );
	m_staticTextTimeScheduleColonFrom->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleColonFrom, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleFromMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	m_spinCtrlTimeScheduleFromMin->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleFromMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleTo = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("To"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTo->Wrap( -1 );
	m_staticTextTimeScheduleTo->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleTo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleToHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 24, 0 );
	m_spinCtrlTimeScheduleToHr->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleToHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleColonTo = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleColonTo->Wrap( -1 );
	m_staticTextTimeScheduleColonTo->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_staticTextTimeScheduleColonTo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleToMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	m_spinCtrlTimeScheduleToMin->Enable( false );
	
	bSizerTimeScheduleFromTo->Add( m_spinCtrlTimeScheduleToMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeSchedule->Add( bSizerTimeScheduleFromTo, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTimeScheduleTotal;
	bSizerTimeScheduleTotal = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeScheduleTotal = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("Total"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotal->Wrap( -1 );
	m_staticTextTimeScheduleTotal->Enable( false );
	
	bSizerTimeScheduleTotal->Add( m_staticTextTimeScheduleTotal, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 99, 0 );
	m_spinCtrlTimeScheduleTotalHr->Enable( false );
	
	bSizerTimeScheduleTotal->Add( m_spinCtrlTimeScheduleTotalHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeScheduleTotalColon = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeScheduleTotalColon->Wrap( -1 );
	m_staticTextTimeScheduleTotalColon->Enable( false );
	
	bSizerTimeScheduleTotal->Add( m_staticTextTimeScheduleTotalColon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeScheduleTotalMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	m_spinCtrlTimeScheduleTotalMin->Enable( false );
	
	bSizerTimeScheduleTotal->Add( m_spinCtrlTimeScheduleTotalMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTimeScheduleTotal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonTimeScheduleSet = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonTimeScheduleSet->Enable( false );
	
	bSizerTimeScheduleTotal->Add( m_buttonTimeScheduleSet, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeSchedule->Add( bSizerTimeScheduleTotal, 0, wxEXPAND, 5 );
	
	sbSizerContestInfoTime->Add( bSizerTimeSchedule, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTimeManual;
	bSizerTimeManual = new wxBoxSizer( wxVERTICAL );
	
	m_radioBtnTimeManual = new wxRadioButton( m_panelContestInfo, wxID_ANY, wxT("Manual"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnTimeManual->SetValue( true ); 
	bSizerTimeManual->Add( m_radioBtnTimeManual, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTimeManualTotal;
	bSizerTimeManualTotal = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeManualTotal = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT("Total"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeManualTotal->Wrap( -1 );
	bSizerTimeManualTotal->Add( m_staticTextTimeManualTotal, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeManualTotalHr = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 99, 0 );
	bSizerTimeManualTotal->Add( m_spinCtrlTimeManualTotalHr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextTimeManualTotalColon = new wxStaticText( m_panelContestInfo, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeManualTotalColon->Wrap( -1 );
	bSizerTimeManualTotal->Add( m_staticTextTimeManualTotalColon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeManualTotalMin = new wxSpinCtrl( m_panelContestInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizerTimeManualTotal->Add( m_spinCtrlTimeManualTotalMin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerTimeManualTotal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonTimeManualSet = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTimeManualTotal->Add( m_buttonTimeManualSet, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerTimeManual->Add( bSizerTimeManualTotal, 1, wxEXPAND, 5 );
	
	sbSizerContestInfoTime->Add( bSizerTimeManual, 0, wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( m_panelContestInfo, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sbSizerContestInfoTime->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerContestCtrl;
	sbSizerContestCtrl = new wxStaticBoxSizer( new wxStaticBox( m_panelContestInfo, wxID_ANY, wxT("Contest Control") ), wxHORIZONTAL );
	
	
	sbSizerContestCtrl->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonContestStart = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerContestCtrl->Add( m_buttonContestStart, 0, wxALL, 5 );
	
	m_buttonContestStop = new wxButton( m_panelContestInfo, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerContestCtrl->Add( m_buttonContestStop, 0, wxALL, 5 );
	
	
	sbSizerContestCtrl->Add( 0, 0, 1, wxEXPAND, 5 );
	
	sbSizerContestInfoTime->Add( sbSizerContestCtrl, 0, wxEXPAND, 5 );
	
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
	
	m_listCtrlProblems = new wxListCtrl( m_panelProblems, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizerProblemList->Add( m_listCtrlProblems, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemButton;
	bSizerProblemButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonProblemAdd = new wxButton( m_panelProblems, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemButton->Add( m_buttonProblemAdd, 1, wxALL, 5 );
	
	m_buttonProblemDel = new wxButton( m_panelProblems, wxID_ANY, wxT("Del"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemButton->Add( m_buttonProblemDel, 1, wxALL, 5 );
	
	bSizerProblemList->Add( bSizerProblemButton, 0, wxEXPAND, 5 );
	
	bSizerProblemsPage->Add( bSizerProblemList, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemInfo;
	bSizerProblemInfo = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerProblemName;
	bSizerProblemName = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblemID = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Problem ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemID->Wrap( -1 );
	bSizerProblemName->Add( m_staticTextProblemID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlProblemID = new wxTextCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_textCtrlProblemID->SetValidator( wxTextValidator( wxFILTER_NUMERIC, &IDFilter ) );
	
	bSizerProblemName->Add( m_textCtrlProblemID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticTextProblemName = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Problem Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemName->Wrap( -1 );
	bSizerProblemName->Add( m_staticTextProblemName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlProblemName = new wxTextCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemName->Add( m_textCtrlProblemName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerProblemInfo->Add( bSizerProblemName, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemFile;
	bSizerProblemFile = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxProblemFile = new wxCheckBox( m_panelProblems, wxID_ANY, wxT("Problem File:"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemFile->Add( m_checkBoxProblemFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePickerProblemFile = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select problem file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerProblemFile->Add( m_filePickerProblemFile, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerProblemInfo->Add( bSizerProblemFile, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemTimeLimit;
	bSizerProblemTimeLimit = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTimeLimit = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Time Limit:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeLimit->Wrap( -1 );
	bSizerProblemTimeLimit->Add( m_staticTextTimeLimit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlTimeLimitVal = new wxSpinCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 1 );
	bSizerProblemTimeLimit->Add( m_spinCtrlTimeLimitVal, 0, wxALL, 5 );
	
	m_staticTextTimeLimitUnit = new wxStaticText( m_panelProblems, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTimeLimitUnit->Wrap( -1 );
	bSizerProblemTimeLimit->Add( m_staticTextTimeLimitUnit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerProblemInfo->Add( bSizerProblemTimeLimit, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerProblemSampleData;
	sbSizerProblemSampleData = new wxStaticBoxSizer( new wxStaticBox( m_panelProblems, wxID_ANY, wxT("Sample Data") ), wxVERTICAL );
	
	m_checkBoxProblemSampleData = new wxCheckBox( m_panelProblems, wxID_ANY, wxT("Offering sample data"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxProblemSampleData->Enable( false );
	
	sbSizerProblemSampleData->Add( m_checkBoxProblemSampleData, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerTestingInput;
	bSizerTestingInput = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblemSampleDataInput = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemSampleDataInput->Wrap( -1 );
	m_staticTextProblemSampleDataInput->Enable( false );
	
	bSizerTestingInput->Add( m_staticTextProblemSampleDataInput, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker2 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	m_filePicker2->Enable( false );
	
	bSizerTestingInput->Add( m_filePicker2, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerProblemSampleData->Add( bSizerTestingInput, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTestingInput1;
	bSizerTestingInput1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	m_staticText401->Enable( false );
	
	bSizerTestingInput1->Add( m_staticText401, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePicker21 = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	m_filePicker21->Enable( false );
	
	bSizerTestingInput1->Add( m_filePicker21, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerProblemSampleData->Add( bSizerTestingInput1, 0, wxEXPAND, 5 );
	
	bSizerProblemInfo->Add( sbSizerProblemSampleData, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerProblemData;
	sbSizerProblemData = new wxStaticBoxSizer( new wxStaticBox( m_panelProblems, wxID_ANY, wxT("Official Data") ), wxVERTICAL );
	
	wxBoxSizer* bSizerProblemInput;
	bSizerProblemInput = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblemInputData = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemInputData->Wrap( -1 );
	bSizerProblemInput->Add( m_staticTextProblemInputData, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePickerProblemInputData = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerProblemInput->Add( m_filePickerProblemInputData, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerProblemData->Add( bSizerProblemInput, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemOutput;
	bSizerProblemOutput = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextProblemOutputData = new wxStaticText( m_panelProblems, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProblemOutputData->Wrap( -1 );
	bSizerProblemOutput->Add( m_staticTextProblemOutputData, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_filePickerProblemOutputData = new wxFilePickerCtrl( m_panelProblems, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerProblemOutput->Add( m_filePickerProblemOutputData, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerProblemData->Add( bSizerProblemOutput, 0, wxEXPAND, 5 );
	
	bSizerProblemInfo->Add( sbSizerProblemData, 0, wxEXPAND, 5 );
	
	
	bSizerProblemInfo->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerProblemInfoButton;
	bSizerProblemInfoButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerProblemInfoButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonProblemApply = new wxButton( m_panelProblems, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerProblemInfoButton->Add( m_buttonProblemApply, 0, wxALL, 5 );
	
	bSizerProblemInfo->Add( bSizerProblemInfoButton, 0, wxEXPAND, 5 );
	
	bSizerProblemsPage->Add( bSizerProblemInfo, 2, wxEXPAND, 5 );
	
	m_panelProblems->SetSizer( bSizerProblemsPage );
	m_panelProblems->Layout();
	bSizerProblemsPage->Fit( m_panelProblems );
	m_notebook->AddPage( m_panelProblems, wxT("Problems"), false );
	m_panelClar = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerClarPage;
	bSizerClarPage = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerClarList;
	bSizerClarList = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerClarListTop;
	bSizerClarListTop = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText62 = new wxStaticText( m_panelClar, wxID_ANY, wxT("Clarifications:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	bSizerClarListTop->Add( m_staticText62, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString m_choice6Choices;
	m_choice6 = new wxChoice( m_panelClar, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice6Choices, 0 );
	m_choice6->SetSelection( 0 );
	bSizerClarListTop->Add( m_choice6, 0, wxALL, 5 );
	
	bSizerClarList->Add( bSizerClarListTop, 0, wxEXPAND, 5 );
	
	m_listCtrlClars = new wxListCtrl( m_panelClar, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT );
	bSizerClarList->Add( m_listCtrlClars, 1, wxALL|wxEXPAND, 5 );
	
	bSizerClarPage->Add( bSizerClarList, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerClarInfo;
	bSizerClarInfo = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerClarID;
	bSizerClarID = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextClarID = new wxStaticText( m_panelClar, wxID_ANY, wxT("ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextClarID->Wrap( -1 );
	bSizerClarID->Add( m_staticTextClarID, 0, wxALL, 5 );
	
	m_staticTextClarIDVal = new wxStaticText( m_panelClar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextClarIDVal->Wrap( -1 );
	bSizerClarID->Add( m_staticTextClarIDVal, 0, wxALL, 5 );
	
	bSizerClarInfo->Add( bSizerClarID, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerQuestion;
	sbSizerQuestion = new wxStaticBoxSizer( new wxStaticBox( m_panelClar, wxID_ANY, wxT("Question") ), wxVERTICAL );
	
	m_textCtrlQuestion = new wxTextCtrl( m_panelClar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	sbSizerQuestion->Add( m_textCtrlQuestion, 1, wxALL|wxEXPAND, 5 );
	
	bSizerClarInfo->Add( sbSizerQuestion, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerAnswer;
	sbSizerAnswer = new wxStaticBoxSizer( new wxStaticBox( m_panelClar, wxID_ANY, wxT("Answer") ), wxVERTICAL );
	
	m_textCtrlAnswer = new wxTextCtrl( m_panelClar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	sbSizerAnswer->Add( m_textCtrlAnswer, 1, wxALL|wxEXPAND, 5 );
	
	bSizerClarInfo->Add( sbSizerAnswer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerClarBtn;
	bSizerClarBtn = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxClarPrivate = new wxCheckBox( m_panelClar, wxID_ANY, wxT("Private"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerClarBtn->Add( m_checkBoxClarPrivate, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerClarBtn->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonClarReply = new wxButton( m_panelClar, wxID_ANY, wxT("Reply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerClarBtn->Add( m_buttonClarReply, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerClarInfo->Add( bSizerClarBtn, 0, wxEXPAND, 5 );
	
	bSizerClarPage->Add( bSizerClarInfo, 2, wxEXPAND, 5 );
	
	m_panelClar->SetSizer( bSizerClarPage );
	m_panelClar->Layout();
	bSizerClarPage->Fit( m_panelClar );
	m_notebook->AddPage( m_panelClar, wxT("Clarifications"), true );
	m_panelSB = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerSBMain;
	bSizerSBMain = new wxBoxSizer( wxVERTICAL );
	
	m_listCtrlSB = new wxListCtrl( m_panelSB, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT );
	bSizerSBMain->Add( m_listCtrlSB, 1, wxALL|wxEXPAND, 5 );
	
	m_panelSB->SetSizer( bSizerSBMain );
	m_panelSB->Layout();
	bSizerSBMain->Fit( m_panelSB );
	m_notebook->AddPage( m_panelSB, wxT("Scoreborad"), false );
	
	bSizerNotebook->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	bSizerMain->Add( bSizerNotebook, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonChangePassword->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickLogout ), NULL, this );
	m_listCtrlAdmin->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedAdmin ), NULL, this );
	m_listCtrlAdmin->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedAdmin ), NULL, this );
	m_listCtrlJudge->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedJudge ), NULL, this );
	m_listCtrlJudge->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedJudge ), NULL, this );
	m_listCtrlTeam->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedTeam ), NULL, this );
	m_listCtrlTeam->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedTeam ), NULL, this );
	m_buttonAccountNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickNewAccount ), NULL, this );
	m_buttonAccountDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickDeleteAccount ), NULL, this );
	m_buttonTimeManualSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickManualTimeSet ), NULL, this );
	m_buttonContestStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickStart ), NULL, this );
	m_buttonContestStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickStop ), NULL, this );
	m_listCtrlProblems->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( AdminGUI::OnListItemDeselectedProblem ), NULL, this );
	m_listCtrlProblems->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedProblem ), NULL, this );
	m_buttonProblemAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickAddProblem ), NULL, this );
	m_buttonProblemDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickDelProblem ), NULL, this );
	m_buttonProblemApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickProblemApply ), NULL, this );
}

AdminGUI::~AdminGUI()
{
	// Disconnect Events
	m_buttonChangePassword->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickLogout ), NULL, this );
	m_listCtrlAdmin->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedAdmin ), NULL, this );
	m_listCtrlAdmin->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedAdmin ), NULL, this );
	m_listCtrlJudge->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedJudge ), NULL, this );
	m_listCtrlJudge->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedJudge ), NULL, this );
	m_listCtrlTeam->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AdminGUI::OnListItemActivatedTeam ), NULL, this );
	m_listCtrlTeam->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedTeam ), NULL, this );
	m_buttonAccountNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickNewAccount ), NULL, this );
	m_buttonAccountDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickDeleteAccount ), NULL, this );
	m_buttonTimeManualSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickManualTimeSet ), NULL, this );
	m_buttonContestStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickStart ), NULL, this );
	m_buttonContestStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickStop ), NULL, this );
	m_listCtrlProblems->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( AdminGUI::OnListItemDeselectedProblem ), NULL, this );
	m_listCtrlProblems->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AdminGUI::OnListItemSelectedProblem ), NULL, this );
	m_buttonProblemAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickAddProblem ), NULL, this );
	m_buttonProblemDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickDelProblem ), NULL, this );
	m_buttonProblemApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AdminGUI::OnButtonClickProblemApply ), NULL, this );
	
}

ChangePassGUI::ChangePassGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerOld;
	bSizerOld = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextOldPass = new wxStaticText( this, wxID_ANY, wxT("Old Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOldPass->Wrap( -1 );
	bSizerOld->Add( m_staticTextOldPass, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlOldPass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 140,-1 ), wxTE_PASSWORD );
	bSizerOld->Add( m_textCtrlOldPass, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerMain->Add( bSizerOld, 1, wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizerNew;
	bSizerNew = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextNewPass = new wxStaticText( this, wxID_ANY, wxT("New Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextNewPass->Wrap( -1 );
	bSizerNew->Add( m_staticTextNewPass, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlNewPass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 140,-1 ), wxTE_PASSWORD );
	bSizerNew->Add( m_textCtrlNewPass, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizerMain->Add( bSizerNew, 1, wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizerRep;
	bSizerRep = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextConfirmPass = new wxStaticText( this, wxID_ANY, wxT("Confirm Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextConfirmPass->Wrap( -1 );
	bSizerRep->Add( m_staticTextConfirmPass, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlConfirmPass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 140,-1 ), wxTE_PASSWORD );
	bSizerRep->Add( m_textCtrlConfirmPass, 0, wxALL, 5 );
	
	bSizerMain->Add( bSizerRep, 1, wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonOK, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizerButton->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizerMain->Add( bSizerButton, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangePassGUI::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangePassGUI::OnButtonClickCancel ), NULL, this );
}

ChangePassGUI::~ChangePassGUI()
{
	// Disconnect Events
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangePassGUI::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangePassGUI::OnButtonClickCancel ), NULL, this );
	
}

AccountGUI::AccountGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextName = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticTextName->Wrap( -1 );
	bSizerName->Add( m_staticTextName, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerName->Add( m_textCtrlID, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizerLoginInfo->Add( bSizerName, 0, wxEXPAND, 5 );
	
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
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AccountGUI::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AccountGUI::OnButtonClickCancel ), NULL, this );
}

AccountGUI::~AccountGUI()
{
	// Disconnect Events
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AccountGUI::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AccountGUI::OnButtonClickCancel ), NULL, this );
	
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
	
	m_buttonChangePassword = new wxButton( this, wxID_ANY, wxT("Change Password"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonChangePassword, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
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
	
	m_filePicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select your source code file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerSubmit->Add( m_filePicker, 0, wxALL|wxEXPAND, 5 );
	
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
	m_buttonChangePassword->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickLogout ), NULL, this );
	m_buttonDownload->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickDownload ), NULL, this );
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickTest ), NULL, this );
	m_buttonSubmit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickSubmit ), NULL, this );
	m_buttonAsk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickAsk ), NULL, this );
}

TeamGUI::~TeamGUI()
{
	// Disconnect Events
	m_buttonChangePassword->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickLogout ), NULL, this );
	m_buttonDownload->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TeamGUI::OnButtonClickDownload ), NULL, this );
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
	
	wxBoxSizer* bSizerQuestion;
	bSizerQuestion = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextQuestion = new wxStaticText( this, wxID_ANY, wxT("Question:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextQuestion->Wrap( -1 );
	m_staticTextQuestion->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );
	
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
	
	m_buttonChangePassword = new wxButton( this, wxID_ANY, wxT("Change Password"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTitle->Add( m_buttonChangePassword, 0, wxALL, 5 );
	
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
	m_buttonChangePassword->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickLogout ), NULL, this );
	m_checkBoxAutoJudge->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( JudgeGUI::OnCheckBoxAutoJudge ), NULL, this );
	m_listCtrlRuns->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( JudgeGUI::OnListItemActivatedRuns ), NULL, this );
	m_listCtrlClars->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( JudgeGUI::OnListItemActivatedClar ), NULL, this );
}

JudgeGUI::~JudgeGUI()
{
	// Disconnect Events
	m_buttonChangePassword->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickChangePassword ), NULL, this );
	m_buttonLogout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeGUI::OnButtonClickLogout ), NULL, this );
	m_checkBoxAutoJudge->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( JudgeGUI::OnCheckBoxAutoJudge ), NULL, this );
	m_listCtrlRuns->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( JudgeGUI::OnListItemActivatedRuns ), NULL, this );
	m_listCtrlClars->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( JudgeGUI::OnListItemActivatedClar ), NULL, this );
	
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

JudgeSubmissionGUI::JudgeSubmissionGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	// Connect Events
	m_buttonShowInputData->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowInput ), NULL, this );
	m_buttonShowSource->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowSource ), NULL, this );
	m_buttonRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickRun ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickStop ), NULL, this );
	m_button35->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowOutput ), NULL, this );
	m_buttonJudge->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickJudge ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickCancel ), NULL, this );
}

JudgeSubmissionGUI::~JudgeSubmissionGUI()
{
	// Disconnect Events
	m_buttonShowInputData->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowInput ), NULL, this );
	m_buttonShowSource->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowSource ), NULL, this );
	m_buttonRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickRun ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickStop ), NULL, this );
	m_button35->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickShowOutput ), NULL, this );
	m_buttonJudge->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickJudge ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeSubmissionGUI::OnButtonClickCancel ), NULL, this );
	
}

JudgeCompareGUI::JudgeCompareGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	// Connect Events
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeCompareGUI::OnButtonClickClose ), NULL, this );
}

JudgeCompareGUI::~JudgeCompareGUI()
{
	// Disconnect Events
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( JudgeCompareGUI::OnButtonClickClose ), NULL, this );
	
}

ShowClarGUI::ShowClarGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerQuestion;
	sbSizerQuestion = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Question") ), wxVERTICAL );
	
	m_textCtrlQuestion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	sbSizerQuestion->Add( m_textCtrlQuestion, 1, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( sbSizerQuestion, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerAnswer;
	sbSizerAnswer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Answer") ), wxVERTICAL );
	
	m_textCtrlAnswer = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	sbSizerAnswer->Add( m_textCtrlAnswer, 1, wxALL|wxEXPAND, 5 );
	
	bSizerMain->Add( sbSizerAnswer, 1, wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMain->Add( m_buttonClose, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ShowClarGUI::OnButtonClickClose ), NULL, this );
}

ShowClarGUI::~ShowClarGUI()
{
	// Disconnect Events
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ShowClarGUI::OnButtonClickClose ), NULL, this );
	
}

ServerGUI::ServerGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	StaticTextStatus = new wxStaticText( this, wxID_ANY, wxT("Not Running"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
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
