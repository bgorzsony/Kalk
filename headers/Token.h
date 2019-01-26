#ifndef TOKEN_H
#define TOKEN_H 


#include <string>


namespace Helper {
	enum TokenType { None = 0, Command = 1, Operator = 2, Constant = 3, LeftbBracket = 4, RightBracket = 5,Register= 6,ArithmeticOperator,LogicOperator };
}

/* Base class for each type of token*/
class Token
{
	private:
		std::string tokenString;
		int precedence;
		bool leftAssociative;
	protected:
		Helper::TokenType type;

	public:
		Token():tokenString(""),type(Helper::None){}

		Token(std::string s,Helper::TokenType t = Helper::None,int p = -1,bool lA = false):tokenString(s),precedence(p),leftAssociative(lA),type(t)
		{
		}

		virtual ~Token()
		{

		}

		Helper::TokenType getType() const { return this->type; }
		std::string getTokenString() const { return this->tokenString; }
		int getPrecedence() const { return this->precedence; }
		bool isLeftAssociative() const { return leftAssociative; }
};

#endif