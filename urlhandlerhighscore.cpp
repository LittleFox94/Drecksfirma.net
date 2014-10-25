#include "inc/urlhandlerhighscore.h"
#include "inc/datamanager.h"

#include <string>

using namespace std;

void URLHandlerHighscore::run(Template* tpl, cgicc::Cgicc* cgi)
{
	tpl->setTitle("Highscore - ");

	string content = "<h3>Highscore</h3>"
		"<table id=\"highscoreTable\"><th>Firma</th><th>Punkte</th>";

	unsigned long long numEntries;
	HighscoreEntry* entries;

	DataManager::getHighscore(&numEntries, &entries);

	for(unsigned long long i = 0; i < numEntries; i++)
	{
		content += "<tr><td>" + entries[i].CompanyName + "</td>"
			"<td>" + to_string(entries[i].Votes) + 
			"<form action=\"/index.bla/Vote\" method=\"post\">"
			"<input type=\"hidden\" name=\"id\" value=\"" + to_string(entries[i].Key) + "\">"
			"<input type=\"submit\" value=\"Abstimmen\">"
			"</form></td></tr>";
	}

	content += "</table>";
	tpl->setContent(content);
}
