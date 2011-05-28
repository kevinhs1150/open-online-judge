#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"

/* Server GUI class. */
class ServerFrame: public ServerGUI
{
	private:
		/* Sqlite variable */
		sqlite3 *db;
		char *errMsg = NULL;
		/* SQL DDL "create table" */
		char *create_user = "create table user("
			"account_id   int,"
			"account      varchar(20),"
			"password     varchar(10),"
			"account_type int"
			"ipaddress    varchar(20)"
			"logged_in    varchar(5),"
			"primary key(account_id));";
			
		char *create_problem = "create table problem("
			"problem_id					int,"
			"description				blob(5MB),"
			"correct_input_filename     varchar(10),"
			"correct_output_filename    varchar(10),"
			"primary key(problem_id));";

		char *create_submission = "create table submission("
			"run_id      int,"
			"account_id  int,"
			"problem_id  int,"
			"lang        varchar(10),"
			"path_code	 varchar(50),"
			"judge_id	 char(5)"
			"primary key(run_id),"
			"foreign key(account_id) references user,"
			"foreign key(problem_id) references problem,"
			"foreign key(judge_id) references judge_type);";

		char *create_clarification = "create table clarification("
			"clar_id       int,"
			"msg         varchar(50),"
			"primary key(clar_id));";

		char *create_scoreboard = "create table scoreboard("
			"account_id		int,"
			"time			int,"
			"score			int,"
			"primary key(account_id),"
			"foreign key(account_id) references user);";

		char *create_judge_type = "create table judge_type("
			"judge_id		int,"
			"sentence		varchar(20),"
			"primary key(judge_id));"		
	
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();

    private:
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
};

#endif // _SERVERMAIN_H_
