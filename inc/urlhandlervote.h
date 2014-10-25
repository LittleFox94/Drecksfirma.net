#ifndef _URLHANDLERVOTE_H_INCLUDED
#define _URLHANDLERVOTE_H_INCLUDED

#include "urlhandler.h"

class URLHandlerVote : public URLHandler
{
    public:
		void run(Template* tpl, cgicc::Cgicc* cgi);
};

#endif
