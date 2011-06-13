#ifndef _TEAMMAIN_H_
#define _TEAMMAIN_H_

#include <wx/wx.h>
#include "TeamApp.h"
#include "gui.h"

class TeamFrame: public TeamGUI
{
    private:


        void OnButtonClickChangePassword( wxCommandEvent& event );
        void OnButtonClickLogout( wxCommandEvent& event );
		void OnButtonClickDownload( wxCommandEvent& event );
		void OnButtonClickTest( wxCommandEvent& event );
		void OnButtonClickSubmit( wxCommandEvent& event );
		void OnButtonClickAsk( wxCommandEvent& event );

		void OnTimerEvent(wxTimerEvent &event);
		void TimerCall(wxCommandEvent &event);
		DECLARE_EVENT_TABLE()

	public:
        TeamFrame(wxFrame *frame);
        ~TeamFrame();
        wxTimer m_timer;
        unsigned int m_timeleft;

};

class ChangePassDialog : public ChangePassGUI
{
	private:
		virtual void OnButtonClickOK( wxCommandEvent& event );
		virtual void OnButtonClickCancel( wxCommandEvent& event );

	public:
		ChangePassDialog(wxFrame *frame);
		~ChangePassDialog();

		void ChangeSuccess();
};

class SubmitConfirmDialog : public SubmitConfirmGUI
{
	private:
		void OnButtonClickYes( wxCommandEvent& event );
		void OnButtonClickNo( wxCommandEvent& event );


	public:
		SubmitConfirmDialog(wxFrame *frame);
		~SubmitConfirmDialog();

};

class ClarDialog : public ClarDialogGUI
{
	private:
		void OnButtonClickYes( wxCommandEvent& event );
		void OnButtonClickNo( wxCommandEvent& event );


	public:
		ClarDialog(wxFrame *frame);
		~ClarDialog();

};

class ClarConfirmDialog : public ClarConfirmGUI
{
	private:
		void OnButtonClickYes( wxCommandEvent& event );
		void OnButtonClickNo( wxCommandEvent& event );

	public:
		ClarConfirmDialog(wxFrame *frame);
		~ClarConfirmDialog();

};

#endif // _TEAMMAIN_H_
