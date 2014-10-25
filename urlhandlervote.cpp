#include "inc/urlhandlervote.h"

#include <string>

#include "inc/datamanager.h"

using namespace cgicc;
using namespace std;

void URLHandlerVote::run(Template* tpl, Cgicc* cgi)
{
	tpl->setTitle("Abstimmen - ");

	string idString = (*cgi)("id");
	unsigned long long id = stoull(idString);

	DataManager::insertVote(id);

	tpl->setContent("<h3>Abstimmen</h3>"
		"<p>Abstimmung erfolgreich! :)</p>");
}

