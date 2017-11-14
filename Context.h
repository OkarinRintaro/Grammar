#pragma once
#include <vector>
#include <string>

using namespace std;

struct var_info
{
	char name_var;
	string val_var;
};

class Context 
{
	vector<var_info> check;
	int level;
	Context();
public:
	static Context* GetInstance();
	void SetVarible(char, const string&);
	const string& Varification(char) const;
	void addbracklevel();
	void subbracklevel();
};

