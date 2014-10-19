#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiEnvironment.h>
#include <string>

#include "inc/template.h"
#include "inc/urlhandler.h"

#include "inc/urlhandlerstartpage.h"

using namespace cgicc;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Cgicc cgi;
		CgiEnvironment environment = cgi.getEnvironment();

		Template tpl("../data/templates/main.tpl");
		URLHandler* handler = NULL;

		string path = environment.getPathInfo();

		if(path == "" || path == "/")
		{
			handler = new URLHandlerStartpage();
		}
		else if(path.find("/Add") == 0)
		{
		}
		else if(path.find("/HallOfShame") == 0)
		{
		}
		else if(path.find("/Contact") == 0)
		{
		}
		else
		{
			tpl.setTitle("Fehler - ");
			tpl.setContent("404 - Unbekannter Pfad '" + path + "'!");
			cout << "Statuscode: 404 Not found" << endl;
		}

		if(handler != NULL)
			handler->run(&tpl, &cgi);

		cout << "X-Bla: Written in C++" << endl;
		cout << cgicc::HTTPHTMLHeader() << endl;

		cout << tpl.toString();
	}
	catch(exception& e)
	{

	}

	return 0;
}
