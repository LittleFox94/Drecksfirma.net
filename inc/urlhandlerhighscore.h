#ifndef _URLHANDLERHIGHSCORE_H_INCLUDED
#define _URLHANDLERHIGHSCORE_H_INCLUDED

#include "urlhandler.h"

class URLHandlerHighscore : public URLHandler
{
    public:
		void run(Template* tpl, cgicc::Cgicc* cgi);
};

#endif
