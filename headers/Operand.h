#ifndef OPERAND_H
#define OPERAND_H 

#include "Token.h"

class Operand :public Token
{
	private:
		float value;

	public:
		Operand(){}
		Operand(std::string s,Helper::TokenType t = Helper::Constant);
		Operand(float v,Helper::TokenType t = Helper::Constant);

		float getValue() const { return this->value; }
		void setValue(float newValue) { 
			this->value = newValue; 
		}

		Operand operator+(const Operand& rhs);
		Operand operator-(const Operand& rhs);
		Operand operator/(const Operand& rhs);
		Operand operator*(const Operand& rhs);
		Operand operator^(const Operand& rhs);

		Operand operator%(const Operand& rhs);

		Operand& operator=(const Operand& rhs);

		bool operator==(const Operand& rhs) const;
		bool operator!=(const Operand& rhs) const;
		bool operator<(const Operand& rhs) const;
		bool operator>(const Operand& rhs) const;
		bool operator&&(const Operand& rhs) const;
		bool operator||(const Operand& rhs) const;
		bool operator<=(const Operand& rhs) const;
		bool operator>=(const Operand& rhs) const;
};

#endif