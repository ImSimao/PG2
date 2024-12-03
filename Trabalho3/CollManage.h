
#ifndef COLLMANAGE_H
#define COLLMANAGE_H

#include "SLib.h"



DynCollection *dynCollCreate( void );

int dynCollAddBook( const char *line, void *context );

void dynCollFill( DynCollection *coll, FILE *f ); 

void dynCollFree( DynCollection *coll );



#endif