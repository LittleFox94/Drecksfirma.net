#include "inc/urlhandleradd.h"

#include "inc/datamanager.h"

using namespace cgicc;
using namespace std;

void URLHandlerAdd::run(Template* tpl, cgicc::Cgicc* cgi)
{
	CgiEnvironment env = cgi->getEnvironment();
	
	string path = env.getPathInfo();

	tpl->setTitle("Firma hinzufügen - ");

	if(path == "/Add")
	{
		tpl->setContent("<h3>Firma hinzufügen</h3>"
			"<p>Hier kann eine neue Firma hinzugefügt werden. Bitte den vollen Firmennamen verwenden um Duplikate zu vermeiden (Duplikate können per Mail gemeldet werden, danke! :)).</p>"
			"<form action=\"/index.bla/Add/Submit\" method=\"post\">"
			"Name der Firma (bitte den vollständigen Namen angeben):<br>"
			"<input type=\"text\" name=\"name\" size=\"30\"><br><br>"
			"<input type=\"submit\" value=\"Eintragen!\">");
	}
	else if(path == "/Add/Submit")
	{
		string name = (*cgi)("name");
		DataManager::insertCompany(name);

		tpl->setContent("<h3>Firma hinzufügen</h3>"
			"Die Firma '" + name + "' wurde erfolgreich hinzugefügt. Sie startet mit einer Punktzahl von 1, du musst also nicht noch abstimmen.");
	}
}
