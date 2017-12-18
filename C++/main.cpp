#include <iostream>
#include "expression.h"
#include "conio.h"
#include "CustomException.h"
#include <list>
#include <algorithm>

/* 
The basis is Interpreter pattern.
class Context store variables and its values.
class FuncExp2nd give analysise of string and calculate functions with two args.
class FuncExp3nd give analysise of string and calculate let function.
*/


using namespace std;

int main(int argc, char *argv[])
{
      if(argc < 2)
    {
        cout<<"Not enough arguments"<<endl;
    }
    else
    {
		try
		{
			string str(argv[1]);
			int pos = 0;
			shared_ptr<Expression> ptrExp = compare(str, pos);
			if (ptrExp)
			{
				cout << ptrExp->Calculate(str, pos) << endl;
			}
			else
			{
				throw CustomException(1);
			}
		}
		catch(CustomException& e)
		{
			std::cerr << "exception caught:" << e.what() << endl;
		}
		catch (std::exception& e)
		{
			std::cerr << "exception caught:" << e.what() << endl;
		}
    }
	_getch();
    return 0;
}
