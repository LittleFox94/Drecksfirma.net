#ifndef _URLHANDLERADD_H_INCLUDED
#define _URLHANDLERADD_H_INCLUDED

#include "urlhandler.h"

class URLHandlerAdd : public URLHandler
{
    public:
		void run(Template* tpl, cgicc::Cgicc* cgi);
};

#endif
