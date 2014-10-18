#ifndef _TEMPLATE_H_INCLUDED
#define _TEMPLATE_H_INCLUDED

#include <string>

//! Template-Engine
class Template
{
	private:
		//! Current transformation-state of the template
		std::string _content;

		/**
		 * Replaces a variable with the given value.
		 * @param variable std::string Name of the variable to replace.
		 * @param newContent std::string New content of the variable.
		 */
		void replaceVariable(std::string variable, std::string newContent);

	public:
		/**
		 * Initializes a new instance of the Template-class.
		 * @param file std::string Path to the template-file.
		 */
		Template(std::string file);

		/**
		 * Set the title of the current page.
		 * @param title std::string Title of the page.
		 */
		void setTitle(std::string title);
		
		/**
		 * Set the content of the current page.
		 * @param content std::string Content of the page.
		 */
		void setContent(std::string content);

		/**
		 * Returns the current state of the template.
		 * @return std::string Current state of the template.
		 */
		std::string toString();
};

#endif
