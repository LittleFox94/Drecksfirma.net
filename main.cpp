#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiEnvironment.h>
#include <string>

#include "inc/template.h"
#include "inc/urlhandler.h"
#include "inc/datamanager.h"

#include "inc/urlhandlerstartpage.h"
#include "inc/urlhandlercontact.h"
#include "inc/urlhandlerhighscore.h"

using namespace cgicc;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		DataManager::connect();

		Cgicc cgi;
		CgiEnvironment environment = cgi.getEnvironment();

		Template tpl("../data/templates/main.tpl");
		URLHandler* handler = NULL;

		string path = environment.getPathInfo();

		if(path == "" || path == "/")
		{
			DataManager::insertCompany("Microsoft");
			DataManager::insertCompany("Apple");
			DataManager::insertCompany("Canonical");

			handler = new URLHandlerStartpage();
		}
		else if(path.find("/Highscore") == 0)
		{
			handler = new URLHandlerHighscore();
		}
		else if(path.find("/Add") == 0)
		{
		}
		else if(path.find("/HallOfShame") == 0)
		{
		}
		else if(path.find("/Contact") == 0)
		{
			handler = new URLHandlerContact();
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
		cout << cgicc::HTTPHTMLHeader();

		cout << tpl.toString();
	}
	catch(exception* e)
	{
		cout << "Status: 500 Server error" << endl;
		cout << "Content-Type: text/plain" << endl << endl;
		cout << "There was an error." << endl;
		cout << e->what();
	}

	return 0;
}
