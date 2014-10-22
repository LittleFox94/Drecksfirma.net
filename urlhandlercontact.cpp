#include "inc/urlhandlercontact.h"

void URLHandlerContact::run(Template* tpl, cgicc::Cgicc* cgi)
{
	tpl->setTitle("Kontakt - ");
	tpl->setContent("<h3>Kontakt</h3>"
		"<p>Sie können mich am besten per E-Mail erreichen. Nutzen Sie dafür bitte die Adresse littlefox@fsfe.org.</p>"
		"<p>Bitte sehen Sie davon ab, mich darum zu bitten, Ihre Firma aus der Liste zu entfernen. Dem kann ich nur nachgehen, wenn sie beweisen können, dass eine hohe \"Punktzahl\" durch einen Mitbewerber, oder was auch immer, generiert wurde. Wenn Sie eine gute Firma haben, werden Sie hier nichts zu befürchten haben.</p>"
		"<p>Ich behalte mir außerdem vor, jeden Kontakt mit Firmen auf dieser Internetseite zu veröffentlichen, selbstverständlich ohne dabei Personenrechte zu verletzen.</p>"
		"<h4>Verantwortlich für den Inhalt</h4>"
		"Moritz Grosch<br>"
		"Hermannstraße 14<br>"
		"09111 Chemnitz<br>"
		"+4917631625032<br>"
		"littlefox@fsfe.org / 0x97FC6451");
}
