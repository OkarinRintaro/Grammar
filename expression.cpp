#include "expression.h"
#include "CustomException.h"

Expression::Expression()
{
	ptr_con = Context::GetInstance();
}

Expression::~Expression(){}

FuncExp2nd::FuncExp2nd(op oper):operation(oper){}

FuncExp3nd::FuncExp3nd(){}


double FuncExp2nd::Calculate(const string &str, int& pos)
{
	string temp;
    if(str[pos] != '(')
    {
		throw CustomException(1);
    }
    shared_ptr<Expression> ptrExp = compare(str,++pos);
    if(ptrExp)
    {
        arg1 = ptrExp->Calculate(str,pos);
    }
    else
    {
        for(int i = pos; i<str.size(); ++i)
        {
			if (str[i] == ',')
			{
				arg1 = stod(temp);
				pos = i;
				break;
			}
			if ((str[i] >= 'A'&&str[i] <= 'Z') || (str[i] >= 'a'&&str[i] <= 'z'))
				temp += ptr_con->Varification(str[i]);
			if (str[i] >= '0'&&str[i] <= '9'|| str[i] == '-' || str[i] == '.')
				temp += str[i];
        }
    }
    //===========================================
    if(str[pos] != ',')
    {
		throw CustomException(1);
    }
	ptrExp = compare(str, ++pos);
    if(ptrExp)
    {
        arg2 = ptrExp->Calculate(str,pos);
    }
    else
    {
		temp.clear();
        for(int i = pos; i<str.size(); ++i)
        {
			if (str[i] == ')')
			{
				arg2 = stod(temp);
				pos = i;
				break;
			}
			if ((str[i] >= 'A'&&str[i] <= 'Z') || (str[i] >= 'a'&&str[i] <= 'z'))
				temp += ptr_con->Varification(str[i]);
			if (str[i] >= '0'&&str[i] <= '9' || str[i] == '-' || str[i] == '.')
				temp += str[i];
        }
    }
    //===========================================
    if(str[pos] != ')')
    {
		throw CustomException(1);
    }
    else
    {
		++pos;
        switch(operation)
        {
            case add_op: return arg1+arg2;
            case sub_op: return arg1-arg2;
            case mult_op: return arg1*arg2;
            case div_op: 
			{
				if (arg2 == 0)
					throw CustomException(3);
				return arg1 / arg2;
			}
        }
    }
}

double FuncExp3nd::Calculate(const string &str, int& pos)
{
	if (str[pos] != '(')
	{
		throw CustomException(1);
	}
	ptr_con->addbracklevel();
	++pos;
	if ((str[pos] >= 'A'&&str[pos] <= 'Z') || (str[pos] >= 'a'&&str[pos] <= 'z'))
	{
		arg1 = str[pos];
		string temp;
		if (str[++pos] != ',')
		{
			throw CustomException(1);
		}
		//=============================================
		shared_ptr<Expression> ptrExp = compare(str, ++pos);
		if (ptrExp)
		{
			arg2 = to_string(ptrExp->Calculate(str, pos));
		}
		else
		{
			for (int i = pos; i<str.size(); ++i)
			{
				if (str[i] >= '0'&&str[i] <= '9' || str[i] == '-' || str[i] == '.')
					temp += str[i];
				else if (str[i] != ',')
				{
					throw CustomException(1);
				}
				if (str[i] == ',')
				{
					arg2 = temp;
					pos = i;
					break;
				}
			}
		}
		ptr_con->SetVarible(arg1, arg2);
		//=================================================
		ptrExp = compare(str, ++pos);
		if (ptrExp)
		{
			arg3 = ptrExp->Calculate(str, pos);
		}
		else
		{
			throw CustomException(1);
		}
		if (str[pos] != ')')
		{
			throw CustomException(1);
		}
		ptr_con->subbracklevel();
		++pos;
	}
	else
	{
		throw CustomException(1);
	}
	return arg3;
}