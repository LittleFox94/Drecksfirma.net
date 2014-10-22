#include "inc/urlhandlerstartpage.h"

void URLHandlerStartpage::run(Template* tpl, cgicc::Cgicc* cgi)
{
	tpl->setTitle("");
	tpl->setContent("<h3>Willkommen auf Drecksfirma.net</h3>"
		"<p>Hier wird basisdemokratisch darüber abgestimmt, welche Firma die allerschlimmste ist.</p>"
		"<h4>So funktionierts:</h4>"
		"<p>Sie ärgern sich gerade über eine Firma? Dann schnell im aktuellen Highscore für diese Firma abstimmen. "
		"Gibt es diese Firma im Highscore noch nicht, muss diese erst hinzugefügt werden - damit ist dann automatisch abgestimmt.</p>"
		"<p>Die Zähler werden jeden Monat zurückgesetzt, die schlimmste Firma des Monats landet jeweils in der Hall of Shame.</p>");
}
