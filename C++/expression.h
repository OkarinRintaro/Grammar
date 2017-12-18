#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Context.h"

enum op{add_op,sub_op,mult_op,div_op};

using namespace std;
class Expression
{
protected:
	Context* ptr_con;
public:
    Expression();
    virtual double Calculate(const string& str,int& pos)=0;
    virtual ~Expression();
};


class FuncExp2nd:public Expression
{
    double arg1,arg2;
    op operation;
public:
    explicit FuncExp2nd(op);
	double Calculate(const string& str,int& pos);
};

class FuncExp3nd :public Expression
{
	char arg1; 
	string arg2;
	double arg3;
	op operation;
public:
	FuncExp3nd();
	double Calculate(const string& str, int& pos);
};

inline shared_ptr<Expression> compare(const string &str, int& pos)
{
	shared_ptr<Expression> ptrExp;
    string add("add");
    string mult("mult");
    string div_("div");
    string sub("sub");
	string let("let");
    if(!str.compare(pos,3,add))
    {
        ptrExp = make_shared<FuncExp2nd>(add_op);
        pos += 3;
		return ptrExp;
    }
    if(!str.compare(pos,4,mult))
    {
        ptrExp = make_shared<FuncExp2nd>(mult_op);
        pos += 4;
		return ptrExp;
    }
    if(!str.compare(pos,3,div_))
    {
        ptrExp = make_shared<FuncExp2nd>(div_op);
        pos += 3;
		return ptrExp;
    }
    if(!str.compare(pos,3,sub))
    {
        ptrExp = make_shared<FuncExp2nd>(sub_op);
        pos += 3;
		return ptrExp;
    }
	if (!str.compare(pos, 3, let))
	{
		ptrExp = make_shared<FuncExp3nd>();
		pos += 3;
		return ptrExp;
	}
    return ptrExp;
}
#endif // EXPRESSION_H
