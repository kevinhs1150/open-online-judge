#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"

extern "C"
{
	#include "serverproto.h"
	#include "sqlite3.h"
	#include <stdlib.h>
	#include <string.h>
}

/* Server GUI class. */
class ServerFrame: public ServerGUI
{
	private:
		/* Sqlite variable */
		sqlite3 *db;
		/* "CREATE TABLE" SQL */
		char *create_user = "CREATE TABLE user("
			"account_id   INTEGER PRIMARY KEY,"
			"account      VARCHAR(25),"
			"password     VARCHAR(25),"
			"account_type INTEGER,"
			"ipaddress    VARCHAR(20),"
			"logged_in    VARCHAR(5));";
			
		char *create_problem = "CREATE TABLE problem("
			"problem_id					INTEGER PRIMARY KEY,"
			"path_description			VARCHAR(50),"
			"correct_input_filename     VARCHAR(50),"
			"correct_output_filename    VARCHAR(50),"
			"time_limit					INTEGER);";

		char *create_submission = "CREATE TABLE submission("
			"run_id      INTEGER PRIMARY KEY,"
			"account_id  INTEGER,"
			"problem_id  INTEGER,"
			"lang        VARCHAR(10),"
			"path_code	 VARCHAR(50),"
			"judge_result VARCHAR(25),"
			"FOREIGN KEY(account_id) REFERENCES user(account_id),"
			"FOREIGN KEY(problem_id) REFERENCES problem(problem_id));";

		char *create_clarification = "CREATE TABLE clarification("
			"clar_id       INTEGER PRIMARY KEY,"
			"account_id    INTEGER,"
			"msg           VARCHAR(100),"
			"result        VAECHAR(100),"
			"private_byte  INTEGER,"
			"FOREIGN KEY(account_id) REFERENCES user(account_id));";

		char *create_scoreboard = "CREATE TABLE scoreboard("
			"score_id		INTEGER PRIMARY KEY,"
			"account_id		INTEGER,"
			"time			INTEGER,"
			"score			INTEGER,"
			"FOREIGN KEY(account_id) REFERENCES user(account_id));";
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();

    private:
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
};

#endif // _SERVERMAIN_H_
