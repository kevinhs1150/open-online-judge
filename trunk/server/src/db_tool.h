#ifndef DB_TOOL_H_
#define DB_TOOL_H_

#include "sqlite3.h"

/* create/destroy functions */
void createPrepareStatement( sqlite3 *db );
void destroyPrepareStatement( sqlite3 *db );

/* string disposal callback */
void strdis_cb( void *mem );

/* string dynamic copy method */
char *dyn_strcpy( const unsigned char *src );


#endif