#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"

extern "C"
{
	#include "serverproto.h"
	#include "proto_commondefine.h"
	#include "sqlite3.h"
	#include <stdlib.h>
	#include <string.h>
}

/* Server GUI class. */
class ServerFrame: public ServerGUI
{
	private:
		bool is_contest_start, is_contest_stop;
		/* Sqlite variable */
		sqlite3 *db;
		
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();

    private:
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
};

#endif // _SERVERMAIN_H_
