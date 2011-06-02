#include "TeamMain.h"
void cb_login_confirm( int confirm_code, unsigned int account_id );
void cb_logout_confirm( int confirm_code );
void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds );
void cb_contest_start( void );
void cb_contest_stop( void );
void cb_run_reply( unsigned int run_id, wchar_t *result_string );
void cb_clar_reply( unsigned int clar_id, wchar_t *result_string );
void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
void cb_pu_request( wchar_t **path_description );
void cb_pu_request_dlfin( wchar_t *path_description );

TeamFrame::TeamFrame(wxFrame *frame)
    : TeamGUI(frame)
{
    teamproto_cbreg_login_confirm( cb_login_confirm );
    teamproto_cbreg_logout_confirm( cb_logout_confirm );
    teamproto_cbreg_timer_set( cb_timer_set );
    teamproto_cbreg_contest_start( cb_contest_start );
    teamproto_cbreg_contest_stop( cb_contest_stop );
    teamproto_cbreg_run_reply( cb_run_reply );
    teamproto_cbreg_clar_reply( cb_clar_reply );
    teamproto_cbreg_sb_update( cb_sb_update );
    teamproto_cbreg_pu_request( cb_pu_request );
    teamproto_cbreg_pu_request_dlfin( cb_pu_request_dlfin );

    teamproto_listen("0.0.0.0");

    LoginDialog *loginDialog = new LoginDialog();


}

TeamFrame::~TeamFrame()
{

}

void OnButtonClickLogout( wxCommandEvent& event )
{

}

void OnButtonClickDownload( wxCommandEvent& event )
{

}

void OnButtonClickBrowse( wxCommandEvent& event )
{

}

void OnButtonClickTest( wxCommandEvent& event )
{

}

void OnButtonClickSubmit( wxCommandEvent& event )
{

}

void OnButtonClickAsk( wxCommandEvent& event )
{

}



void cb_login_confirm( int confirm_code, unsigned int account_id )
{

}
void cb_login_confirm( int confirm_code, unsigned int account_id );
{

}

void cb_logout_confirm( int confirm_code )
{

}

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds )
{

}

void cb_contest_start( void )
{

}

void cb_contest_stop( void )
{

}

void cb_run_reply( unsigned int run_id, wchar_t *result_string )
{

}

void cb_clar_reply( unsigned int clar_id, wchar_t *result_string )
{

}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{

}

void cb_pu_request( wchar_t **path_description )
{

}

void cb_pu_request_dlfin( wchar_t *path_description )
{

}
