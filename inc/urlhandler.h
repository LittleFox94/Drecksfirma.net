#ifndef _URLHANDLER_H_INCLUDED
#define _URLHANDLER_H_INCLUDED

#include <cgicc/Cgicc.h>

#include "template.h"

class URLHandler
{
	public:
		/**
		 * Run the URL-Handler
		 * @param tpl Template Instance of the Template-class to modify the content of the page.
		 * @param cgi cgicc::Cgicc Instance of the Cgicc class to access CGI stuff.
		 */
		virtual void run(Template* tpl, cgicc::Cgicc* cgi) = 0;
};

#endif
