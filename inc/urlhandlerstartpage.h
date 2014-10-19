#ifndef _URLHANDLERSTARTPAGE_H_INCLUDED
#define _URLHANDLERSTARTPAGE_H_INCLUDED

#include "urlhandler.h"

class URLHandlerStartpage : public URLHandler
{
	public:
		void run(Template* tpl, cgicc::Cgicc* cgi);
};

#endif
