#ifndef _TEAMMAIN_H_
#define _TEAMMAIN_H_

#include <wx/wx.h>
#include "TeamApp.h"
#include "gui.h"

struct runListNode
{
	unsigned int run_id;
	unsigned int problem_id;
	struct runListNode *nextPtr;
};
typedef struct runListNode RunListNode;
typedef RunListNode *RunListNodePtr;

class RunLinkedList
{
	private:
		RunListNodePtr headPtr;
		RunListNodePtr tailPtr;

		unsigned int items;

		unsigned int tgt_pid;
		int searchIndex;
		RunListNodePtr searchPtr;

	public:
		RunLinkedList( void );
		~RunLinkedList( void );

		void Insert( unsigned int run_id, unsigned int problem_id );

		/* search function */
		void SetSearchProblemID( unsigned int problem_id );
		void ResetSearch( void );

		int SearchNext( void );  /* return index to next result, -1 for no result */

		unsigned int &operator[]( unsigned int index );  /* get run_id of index */
};

class TeamFrame: public TeamGUI
{
    private:
        void OnButtonClickChangePassword( wxCommandEvent& event );
        void OnButtonClickLogout( wxCommandEvent& event );
		void OnButtonClickDownload( wxCommandEvent& event );
		void OnButtonClickTest( wxCommandEvent& event );
		void OnButtonClickSubmit( wxCommandEvent& event );
		void OnButtonClickAsk( wxCommandEvent& event );
		void OnListItemActivatedClar( wxListEvent& event );

		void OnTimerEvent(wxTimerEvent &event);
		void TimerCall(wxCommandEvent &event);
		DECLARE_EVENT_TABLE()

	public:
        TeamFrame(wxFrame *frame);
        ~TeamFrame();
        wxTimer m_timer;
        unsigned int m_timeleft;
		
		RunLinkedList runlist;
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

class ShowClarDialog: public ShowClarGUI
{
    public:
        ShowClarDialog(wxFrame *frame);
        ~ShowClarDialog();

    private:
		void OnButtonClickClose( wxCommandEvent& event );
};


#endif // _TEAMMAIN_H_
