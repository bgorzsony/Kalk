#ifndef EXPRESSION_H
#define EXPRESSION_H 

#include <vector>
#include <stack>
#include <iostream>
#include "Token.h"
#include "Operand.h"
#include "Operator.h"


class Expression
{
	protected:
		std::vector<Token*> tokens;
	private:
		void infixToPostFix(std::vector<Token*> infix);

	public:
		Expression(std::vector<Token*> infix) {
			infixToPostFix(infix);

		}


		std::vector<Token*> getTokens() const { return this->tokens; }

		Token* getFirstToken() const {
			return this->tokens[0];
		}

		float solve();

		void clear();

		virtual ~Expression(){
			
		}
};


#endif