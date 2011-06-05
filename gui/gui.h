///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/radiobut.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/choice.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class LoginGUI
///////////////////////////////////////////////////////////////////////////////
class LoginGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTitle;
		wxStaticLine* m_staticlineTop;
		wxStaticText* m_staticTextID;
		wxTextCtrl* m_textCtrlID;
		
		wxStaticText* m_staticTextPassword;
		wxTextCtrl* m_textCtrlPassword;
		
		wxStaticLine* m_staticlineMid;
		
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTextEnterPassword( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickLogin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickExit( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		LoginGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU );
		~LoginGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AdminGUI
///////////////////////////////////////////////////////////////////////////////
class AdminGUI : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTime;
		
		wxStaticText* m_staticTextName;
		wxButton* m_buttonChangePassword;
		wxButton* m_buttonLogout;
		wxNotebook* m_notebook;
		wxPanel* m_panelAccounts;
		wxButton* m_buttonAccountNew;
		wxButton* m_buttonAccountDelete;
		wxPanel* m_panelContestInfo;
		wxStaticText* m_staticTextContestTitle;
		wxTextCtrl* m_textCtrlContestTitle;
		wxRadioButton* m_radioBtnTimeSchedule;
		wxStaticText* m_staticTextTimeScheduleFrom;
		wxSpinCtrl* m_spinCtrlTimeScheduleFromHr;
		wxStaticText* m_staticTextTimeScheduleColonFrom;
		wxSpinCtrl* m_spinCtrlTimeScheduleFromMin;
		wxStaticText* m_staticTextTimeScheduleTo;
		wxSpinCtrl* m_spinCtrlTimeScheduleToHr;
		wxStaticText* m_staticTextTimeScheduleColonTo;
		wxSpinCtrl* m_spinCtrlTimeScheduleToMin;
		wxStaticText* m_staticTextTimeScheduleTotal;
		wxSpinCtrl* m_spinCtrlTimeScheduleTotalHr;
		wxStaticText* m_staticTextTimeScheduleTotalColon;
		wxSpinCtrl* m_spinCtrlTimeScheduleTotalMin;
		
		wxButton* m_buttonTimeScheduleSet;
		wxRadioButton* m_radioBtnTimeManual;
		wxStaticText* m_staticTextTimeScheduleTotal1;
		wxSpinCtrl* m_spinCtrlTimeScheduleTotalHr1;
		wxStaticText* m_staticTextTimeScheduleTotalColon1;
		wxSpinCtrl* m_spinCtrlTimeScheduleTotalMin1;
		
		wxButton* m_buttonTimeScheduleSet1;
		wxStaticLine* m_staticline8;
		
		wxButton* m_buttonContestStart;
		wxButton* m_buttonContestStop;
		
		wxPanel* m_panelProblems;
		wxStaticText* m_staticTextProblems;
		wxListCtrl* m_listCtrlProblems;
		wxButton* m_buttonProblemAdd;
		wxButton* m_buttonProblemDel;
		wxStaticText* m_staticTextProblemName;
		wxTextCtrl* m_textCtrlProblemName;
		wxCheckBox* m_checkBoxProblemFile;
		wxFilePickerCtrl* m_filePickerProblemFile;
		wxStaticText* m_staticTextTimeLimit;
		wxSpinCtrl* m_spinCtrlTimeLimitVal;
		wxStaticText* m_staticTextTimeLimitUnit;
		wxCheckBox* m_checkBoxProblemSampleData;
		wxStaticText* m_staticTextProblemSampleDataInput;
		wxFilePickerCtrl* m_filePicker2;
		wxStaticText* m_staticText401;
		wxFilePickerCtrl* m_filePicker21;
		wxStaticText* m_staticTextProblemInputData;
		wxFilePickerCtrl* m_filePickerProblemInputData;
		wxStaticText* m_staticTextProblemOutputData;
		wxFilePickerCtrl* m_filePickerProblemOutputData;
		
		
		wxButton* m_buttonProblemApply;
		wxPanel* m_panelClar;
		wxStaticText* m_staticText62;
		wxChoice* m_choice6;
		wxListCtrl* m_listCtrl10;
		wxStaticText* m_staticTextClarID;
		wxStaticText* m_staticTextClarIDVal;
		wxStaticText* m_staticTextClarProblem;
		wxStaticText* m_staticTextClarProblemVal;
		wxTextCtrl* m_textCtrl17;
		wxTextCtrl* m_textCtrl18;
		wxButton* m_button42;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickChangePassword( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickLogout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListItemActivatedAdmin( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemSelectedAdmin( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemActivatedJudge( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemSelectedJudge( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemActivatedTeam( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemSelectedTeam( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonClickNewAccount( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteAccount( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListItemDeselectedProblem( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemSelectedProblem( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonClickAddProblem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDelProblem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickProblemApply( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxListCtrl* m_listCtrlAdmin;
		wxListCtrl* m_listCtrlJudge;
		wxListCtrl* m_listCtrlTeam;
		
		AdminGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 753,553 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~AdminGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ChangePassGUI
///////////////////////////////////////////////////////////////////////////////
class ChangePassGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextOldPass;
		wxTextCtrl* m_textCtrlOldPass;
		wxStaticText* m_staticTextNewPass;
		wxTextCtrl* m_textCtrlNewPass;
		wxStaticText* m_staticTextConfirmPass;
		wxTextCtrl* m_textCtrlConfirmPass;
		
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ChangePassGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~ChangePassGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AccountGUI
///////////////////////////////////////////////////////////////////////////////
class AccountGUI : public wxDialog 
{
	private:
	
	protected:
		wxRadioButton* m_radioBtnAdmin;
		wxRadioButton* m_radioBtnJudge;
		wxRadioButton* m_radioBtnTeam;
		wxStaticText* m_staticTextName;
		wxTextCtrl* m_textCtrlID;
		wxStaticText* m_staticTextPassword;
		wxTextCtrl* m_textCtrlPassword;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AccountGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~AccountGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TeamGUI
///////////////////////////////////////////////////////////////////////////////
class TeamGUI : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTime;
		
		wxStaticText* m_staticTextTeamName;
		wxButton* m_buttonChangePassword;
		wxButton* m_buttonLogout;
		wxChoice* m_choiceProblem;
		wxButton* m_buttonDownload;
		wxFilePickerCtrl* m_filePicker;
		wxChoice* m_choiceLang;
		wxButton* m_buttonTest;
		wxButton* m_buttonSubmit;
		wxListCtrl* m_listCtrlRuns;
		wxButton* m_buttonAsk;
		wxListCtrl* m_listCtrlClars;
		wxListCtrl* m_listCtrlScore;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickChangePassword( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickLogout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDownload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickSubmit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickAsk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TeamGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OOJ Team"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 641,480 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~TeamGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SubmitConfirmGUI
///////////////////////////////////////////////////////////////////////////////
class SubmitConfirmGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTitle;
		wxStaticLine* m_staticlineUp;
		wxStaticText* m_staticTextProblem;
		wxStaticText* m_staticTextProblemVal;
		wxStaticText* m_staticTextLang;
		wxStaticText* m_staticTextLangVal;
		wxStaticText* m_staticTextFilePath;
		wxTextCtrl* m_textCtrlFilePathVal;
		wxStaticLine* m_staticlineDown;
		
		wxButton* m_buttonYes;
		wxButton* m_buttonNo;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickYes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickNo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SubmitConfirmGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Confirm"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SubmitConfirmGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ClarDialogGUI
///////////////////////////////////////////////////////////////////////////////
class ClarDialogGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTitle;
		wxStaticText* m_staticTextProblem;
		wxChoice* m_choiceProblem;
		wxStaticText* m_staticTextQuestion;
		wxTextCtrl* m_textCtrlFileQuestion;
		
		wxButton* m_buttonYes;
		wxButton* m_buttonNo;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickYes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickNo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ClarDialogGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,300 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ClarDialogGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ClarConfirmGUI
///////////////////////////////////////////////////////////////////////////////
class ClarConfirmGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTitle;
		wxStaticLine* m_staticlineUp;
		wxStaticText* m_staticTextProblem;
		wxStaticText* m_staticTextProblemVal;
		wxStaticText* m_staticTextQuestion;
		wxTextCtrl* m_textCtrlFileQuestion;
		wxStaticLine* m_staticlineDown;
		
		wxButton* m_buttonYes;
		wxButton* m_buttonNo;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickYes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickNo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ClarConfirmGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Confirm"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ClarConfirmGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class JudgeGUI
///////////////////////////////////////////////////////////////////////////////
class JudgeGUI : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTime;
		
		wxStaticText* m_staticTextName;
		wxButton* m_buttonChangePassword;
		wxButton* m_buttonLogout;
		wxChoice* m_choiceFilter;
		wxCheckBox* m_checkBoxAutoJudge;
		
		wxStaticText* m_staticTextNewUnjudgeCount;
		wxListCtrl* m_listCtrlRuns;
		wxListCtrl* m_listCtrlClars;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickChangePassword( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickLogout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxAutoJudge( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		JudgeGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 643,468 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~JudgeGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class JudgementConfirmGUI
///////////////////////////////////////////////////////////////////////////////
class JudgementConfirmGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextTitle;
		wxStaticLine* m_staticlineUp;
		wxStaticText* m_staticTextJudgement;
		wxStaticText* m_staticTextJudgementVal;
		wxStaticLine* m_staticlineDown;
		
		wxButton* m_buttonYes;
		wxButton* m_buttonNo;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickYes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickNo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		JudgementConfirmGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~JudgementConfirmGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class JudgeSubmissionGUI
///////////////////////////////////////////////////////////////////////////////
class JudgeSubmissionGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextProblemNumber;
		wxStaticText* m_staticTextProblemNumberValue;
		wxStaticText* m_staticTextTeam;
		wxStaticText* m_staticTextTeamValue;
		wxStaticText* m_staticTextSubmission;
		wxStaticText* m_staticTextSubmissionValue;
		wxStaticText* m_staticTextInputStatus;
		wxStaticText* m_staticTextInputStatusValue;
		
		wxButton* m_buttonShowInputData;
		wxStaticText* m_staticTextSourceStatus;
		wxStaticText* m_staticTextSourceStatusValue;
		
		wxButton* m_buttonShowSource;
		
		wxButton* m_buttonRun;
		wxButton* m_buttonStop;
		
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticTextRunStatus;
		wxStaticLine* m_staticline2;
		
		wxStaticText* m_staticTextResult;
		wxChoice* m_choiceJudgement;
		wxButton* m_button35;
		
		
		wxButton* m_buttonJudge;
		wxButton* m_buttonCancel;
		
		wxStaticLine* m_staticline3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickShowInput( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickShowSource( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickShowOutput( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickJudge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		JudgeSubmissionGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Judge"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~JudgeSubmissionGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class JudgeCompareGUI
///////////////////////////////////////////////////////////////////////////////
class JudgeCompareGUI : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrlOfficialOutput;
		wxTextCtrl* m_textCtrlUserOutput;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		JudgeCompareGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Compare Outputs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~JudgeCompareGUI();
	
};

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
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickStop( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ServerGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Open Online Judge (Server)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~ServerGUI();
	
};

#endif //__gui__
