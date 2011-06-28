#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"

#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

extern "C"
{
	#include "serverproto.h"
	#include "proto_commondefine.h"
}

/* Server GUI class. */
class ServerFrame: public ServerGUI
{
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();

		/* callback_submission_request{_dlfin}() protection */
		wxMutex m_mutexSubmissionRequest;

    private:
		wxTimer m_timer;
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );

		void OnTimerEvent(wxTimerEvent &event);
		void TimerCall(wxCommandEvent &event);
		DECLARE_EVENT_TABLE()

};

#endif // _SERVERMAIN_H_
