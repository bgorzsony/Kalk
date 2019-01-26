#include "Expression.h"
#include "Registers.h"
#include "memtrace.h"





//Converting to postfix notation from infix using shunting yard
void Expression::infixToPostFix(std::vector<Token*> infix) {
	
	std::stack<Token*> stack;

	for (auto i : infix) {

		Helper::TokenType currentType = i->getType();

		if (currentType == Helper::Constant || currentType == Helper::Register) {
			this->tokens.push_back(i);
		}
		else if (currentType == Helper::ArithmeticOperator || currentType == Helper::LogicOperator) {

				while (!stack.empty() && ((stack.top()->getPrecedence() > i->getPrecedence()) || ( stack.top()->getPrecedence() == i->getPrecedence() && stack.top()->isLeftAssociative() )) ){
					this->tokens.push_back(stack.top());
					stack.pop();
			}
			stack.push(i);
		}
		else if (currentType == Helper::LeftbBracket) stack.push(i);
		else if (currentType == Helper::RightBracket) {
			//delete the right bracket token
			delete i;
			while (stack.top()->getType() != Helper::LeftbBracket) {
				this->tokens.push_back(stack.top());
				stack.pop();
			}
			//delete the leftbracket
			delete stack.top();
			stack.pop();
		}
	}

	while (!stack.empty()) {
		this->tokens.push_back(stack.top());
		stack.pop();
	}

}


float Expression::solve() {

	std::stack<Token*> stack;


	//created in the function,never using them again,gotta delete them at the end
	std::vector<Token*> tempTokens;

	for (auto i : this->tokens) {

		if (i->getType() == Helper::Constant || i->getType() == Helper::Register) { stack.push(i); }
		else if (i->getType() == Helper::ArithmeticOperator ||  i->getType() == Helper::LogicOperator) {

			Operator *opr = static_cast<Operator*>(i);

			if (opr->singleArg()) {
				Operand *op;

				if (stack.top()->getType() == Helper::Register) {
					op = &(RegisterCollection::getInstance()[stack.top()->getTokenString()[0]]);
					stack.pop();
				}
				else {
					op = static_cast<Operand*>(stack.top());
					stack.pop();
				}



				Operand * res = new Operand(opr->Calc(*op,*op));

				//for deleting later
				tempTokens.push_back(res);
				stack.push(res);

			}
			else {
				
				Operand *op2;
				Operand *op1;
				
				if (stack.top()->getType() == Helper::Register) {
					// if the token is a register we get it from the collection
					op2 = &(RegisterCollection::getInstance()[stack.top()->getTokenString()[0]]);
					stack.pop();
				}
				else {
					//if it's not a register then we can cast it into an operand
					op2 = static_cast<Operand*>(stack.top());
					stack.pop();
				}

				//if our operator is a minus sign the stack could be empty
				if (!stack.empty()) {
					//same with the other operand
					if (stack.top()->getType() == Helper::Register) {
						// if the token is a register we get it from the collection
						op1 = &(RegisterCollection::getInstance()[stack.top()->getTokenString()[0]]);
						stack.pop();
					}
					else {
						//if it's not a register then we can cast it into an operand
						op1 = static_cast<Operand*>(stack.top());
						stack.pop();
					}
				}
				else {
					//adding a zero as operand if the stack is empty
					op1 = new Operand(0);
					tempTokens.push_back(op1);
				}
				
				Operand *res = new Operand(opr->Calc(*op1, *op2));

				//for deleting later
				tempTokens.push_back(res);

				stack.push(res);


			}

		}

	}

	float result = 0;
	if (stack.size() == 1) {
		Token * top= stack.top();
		if (top->getType() == Helper::Register && RegisterCollection::validRegister(top->getTokenString()[0])) {
			char reg = top->getTokenString()[0];
			result = RegisterCollection::getInstance()[reg].getValue();
		}
		else {
			result = static_cast<Operand*>(top)->getValue();
		}

	}
	else {
		for (auto i : tempTokens) delete i;
		throw std::out_of_range("Can't solve the expression"); 
	}



	for (auto i : tempTokens) delete i;


	return result;
}



void Expression::clear() {

	for (size_t i = 0;i < this->tokens.size();i++) {
		delete this->tokens[i];
	}

}
