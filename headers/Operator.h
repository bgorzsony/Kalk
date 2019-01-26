#ifndef OPERATOR_H
#define OPERATOR_H 


#include <cmath>
#include "Registers.h"
#include "Operand.h"


class Operator : public Token
{
	

	public:
		Operator(std::string s,int precedence,Helper::TokenType t,bool leftA):Token(s,t,precedence,leftA){}

		Operand Calc(Operand& a, Operand& b);

		bool singleArg() const { return this->getTokenString().length() > 1 && this->type != Helper::LogicOperator; }

		
};


#endif
