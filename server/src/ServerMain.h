#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"
#include "sqlite3.h"

/*
extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}
*/

/* Server GUI class. */
class ServerFrame: public ServerGUI
{
	private:
		/* Sqlite variable */
		sqlite3 *db;
		char *errMsg = NULL;
		/* SQL DDL "CREATE TABLE" char string */
		char *create_user = "CREATE TABLE user("
			"account_id   INTEGER PRIMARY KEY,"
			"account      VARCHAR(20),"
			"password     VARCHAR(25),"
			"account_type INTEGER,"
			"ipaddress    VARCHAR(20),"
			"logged_in    VARCHAR(5));"
			
		char *create_problem = "CREATE TABLE problem("
			"problem_id					INTEGER PRIMARY KEY,"
			"path_description			VARCHAR(50),"
			"correct_input_filename     VARCHAR(10),"
			"correct_output_filename    VARCHAR(10));"

		char *create_submission = "CREATE TABLE submission("
			"run_id      INTEGER PRIMARY KEY,"
			"account_id  INTEGER,"
			"problem_id  INTEGER,"
			"lang        VARCHAR(10),"
			"path_code	 VARCHAR(50),"
			"judge_id	 INTEGER,"
			"FOREIGN KEY(account_id) REFERENCES user(account_id),"
			"FOREIGN KEY(problem_id) REFERENCES problem(problem_id),"
			"FOREIGN KEY(judge_id) REFERENCES judge_type(judge_id));";

		char *create_clarification = "CREATE TABLE clarification("
			"clar_id       INTEGER PRIMARY KEY,"
			"account_id    INTEGER,"
			"msg           VARCHAR(100),"
			"private_byte  INTEGER),"
			"FOREIGN KEY(account_id) REFERENCES user(account_id);";

		char *create_scoreboard = "CREATE TABLE scoreboard("
			"account_id		INTEGER PRIMARY KEY,"
			"time			INTEGER,"
			"score			INTEGER,"
			"FOREIGN KEY(account_id) REFERENCES user(account_id));";

		char *create_judge_type = "CREATE TABLE judge_type("
			"judge_id		INTEGER PRIMARY KEY,"
			"sentence		VARCHAR(20));";
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();

    private:
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
};

#endif // _SERVERMAIN_H_
