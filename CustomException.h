#pragma once

#include <exception>

using namespace std;

class CustomException : public exception
{
	unsigned int error_code;
public:
	explicit CustomException(unsigned int num):error_code(num){}
	virtual const char* what() const noexcept
	{
		switch (error_code)
		{
		case 1:
		{
			return "Syntax error!";
			break;
		}
		case 2:
		{
			return "Undefined variable!";
			break;
		}
		case 3:
		{
			return "Division by zero!";
			break;
		}
		default:
		{
			return "Error!";
		}
		}
	}
};