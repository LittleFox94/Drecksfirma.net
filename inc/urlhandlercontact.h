#ifndef _URLHANDLERCONTACT_H_INCLUDED
#define _URLHANDLERCONTACT_H_INCLUDED

#include "urlhandler.h"

class URLHandlerContact : public URLHandler
{
    public:
		void run(Template* tpl, cgicc::Cgicc* cgi);
};

#endif
