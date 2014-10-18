#ifndef _TEMPLATE_H_INCLUDED
#define _TEMPLATE_H_INCLUDED

#include <string>

class Template
{
	private:
		std::string _content;

		void replaceVariable(std::string variable, std::string newContent);

	public:
		Template(std::string file);

		void setTitle(std::string title);
		void setContent(std::string content);

		std::string toString();
};

#endif
