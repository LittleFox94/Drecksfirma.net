#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiEnvironment.h>
#include <string>

#include "inc/template.h"
#include "inc/urlhandler.h"
#include "inc/datamanager.h"
#include "inc/FCgiIO.h"

#include "inc/urlhandlerstartpage.h"
#include "inc/urlhandlercontact.h"
#include "inc/urlhandlerhighscore.h"
#include "inc/urlhandleradd.h"
#include "inc/urlhandlervote.h"

using namespace cgicc;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		DataManager::connect();

		FCGX_Request request;

		FCGX_Init();
		FCGX_InitRequest(&request, 0, 0);

		while(FCGX_Accept_r(&request) == 0)
		{
			FCgiIO cgiIO(request);

			try
			{
				Cgicc cgi(&cgiIO);
				CgiEnvironment environment = cgi.getEnvironment();

				Template tpl("../data/templates/main.tpl");
				URLHandler* handler = NULL;

				string path = environment.getPathInfo();

				if(path == "" || path == "/")
				{
					handler = new URLHandlerStartpage();
				}
				else if(path.find("/Highscore") == 0)
				{
					handler = new URLHandlerHighscore();
				}
				else if(path.find("/Add") == 0)
				{
					handler = new URLHandlerAdd();
				}
				else if(path.find("/Vote") == 0)
				{
					handler = new URLHandlerVote();
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
					cgiIO << "Statuscode: 404 Not found" << endl;
				}

				if(handler != NULL)
					handler->run(&tpl, &cgi);

				cgiIO << "X-Bla: Written in C++" << endl;
				cgiIO << cgicc::HTTPHTMLHeader();

				cgiIO << tpl.toString();
			}
			catch(exception* e)
			{
				DataManager::disconnect();

				cgiIO << "Status: 500 Server error" << endl;
				cgiIO << "Content-Type: text/plain" << endl << endl;
				cgiIO << "There was an error." << endl;
				cgiIO << e->what();
			}

			FCGX_Finish_r(&request);
		}

		DataManager::disconnect();
	}
	catch(exception* e)
	{
		return -1;
	}

	return 0;
}
