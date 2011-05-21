#ifndef _SERVERAPP_H_
#define _SERVERAPP_H_

#include <wx/app.h>


/* set server program debug level */
#define SERVER_DBG 1

class ServerApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // _SERVERAPP_H_
