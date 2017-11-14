#include "Context.h"
#include "CustomException.h"

Context::Context():level(0)
{
}


Context* Context::GetInstance()
{
	static Context con;
	return &con;
}

const string& Context::Varification(char ch) const
{
	int temp_level = level;
	while (temp_level)
	{
		if (check[temp_level].name_var == ch)
			return check[temp_level].val_var;
		temp_level--;
	}
	throw CustomException(2);
}

void Context::SetVarible(char ch, const string& num)
{
	if (level > check.size())
		check.resize(2 * level);
	check[level].name_var = ch;
	check[level].val_var = num;
}

void Context::addbracklevel()
{
	level++;
}

void Context::subbracklevel()
{
	level--;
}