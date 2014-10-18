#include <fstream>
#include <string>
#include <streambuf>

#include "inc/template.h"

using namespace std;

Template::Template(std::string file)
{
	ifstream ifs(file.c_str());

	ifs.seekg(0, std::ios::end);
	_content.reserve(ifs.tellg());
	ifs.seekg(0, std::ios::beg);

	_content.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

std::string Template::toString()
{
	return _content;
}

void Template::setTitle(std::string title)
{
	replaceVariable("PAGETITLE", title);
}

void Template::setContent(std::string content)
{
	replaceVariable("CONTENT", content);
}

void Template::replaceVariable(std::string varName, std::string newContent)
{
	varName = "%_" + varName + "_%";

	size_t varNamePos;
	do
	{
		varNamePos = _content.find(varName);

		if(varNamePos == string::npos)
			break;

		_content.replace(varNamePos, varName.length(), newContent);
	}
	while(varNamePos != string::npos);
}
