#include "inc/urlhandlerhighscore.h"
#include "inc/datamanager.h"

#include <string>
#include <string.h>
#include <stdio.h>

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
		char buffer[100];
		memset(buffer, 0, 100);
		snprintf(buffer, 100, "%d", entries[i].Votes);

		content += "<tr><td>" + entries[i].CompanyName + "</td><td>" + string(buffer) + "</td></tr>";
	}

	content += "</table>";
	tpl->setContent(content);
}
