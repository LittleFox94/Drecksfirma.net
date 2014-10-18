#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiEnvironment.h>
#include <string>

#include "inc/template.h"

using namespace cgicc;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Cgicc cgi;
		CgiEnvironment environment = cgi.getEnvironment();

		Template tpl("../data/templates/main.tpl");

		string path = environment.getPathInfo();

		if(path == "" || path == "/")
		{
		}
		else if(path == "/list")
		{
		}
		else if(path.find("/vote") == 0)
		{
		}
		else
		{
			tpl.setTitle("Fehler - ");
			tpl.setContent("404 - Unbekannter Pfad!");
			cout << "Statuscode: 404 Not found" << endl;
		}

		cout << "X-Bla: Written in C++" << endl;
		cout << cgicc::HTTPHTMLHeader() << endl;

		cout << tpl.toString();
	}
	catch(exception& e)
	{

	}

	return 0;
}
