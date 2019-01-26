#include "Operator.h"
#include "memtrace.h"

Operand Operator::Calc(Operand& a, Operand& b) {

	if (this->getTokenString().length() == 1 && this->getType() != Helper::LogicOperator) {
		switch (this->getTokenString()[0])
		{
		case '+':
			return a + b;
			break;
		case '-':
			return a - b;
			break;
		case '/':
			return a / b;
			break;
		case '*':
			return a * b;
			break;
		case '^':
			return a ^ b;
			break;
		case '=':
			a = b;
			return a;
			break;
		case '%':
			return a % b;
			break;

		}
	}
	else if (this->getType() == Helper::LogicOperator) {
		float v = 0;

		std::string s = this->getTokenString();
		if (s == "==") v = a == b;
		else if (s == "!=") v = a != b;
		else if (s == "<") v = a < b;
		else if (s == ">") v = a > b;
		else if (s == "&&") v = a && b;
		else if (s == "||") v = a || b;
		else if (s == "<=") v = a <= b;
		else if (s == ">=") v = a >= b;


		return Operand(v);
	}
	else {
		float value = a.getValue();
		std::string s = this->getTokenString();
		if (s == "sqrt") return Operand(sqrtf(value));
		else if (s == "abs") return Operand(fabsf(value));
		else if (s == "log") return Operand(log10f(value));
		else {
			//trigonometric functions

			//value to degrees
			value = value * (3.14159265359 / 180.0);
			if (s == "sin") return Operand(sinf(value));
			else if (s == "cos") return Operand(cosf(value));
			else if (s == "tan") return Operand(tanf(value));
		}
	}



	return Operand(0);


}

