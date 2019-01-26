#include "Tokenizer.h"



#include "Operand.h"
#include "Operator.h"
#include "Command.h"
#include "memtrace.h"

	
namespace Tokenizer {


	//private stuff
	namespace {

		bool isDigit(char ch) {
			return (ch >= '0' && ch <= '9') || ch == '.';
		}

		bool isLetter(char ch) {
			ch = tolower(ch);
			return ch >= 'a' && ch <= 'z';
		}
		bool isLeftBracket(char ch) {
			return ch == '(';
		}
		bool isRightBracket(char ch) {
			return ch == ')';
		}
		bool isArithmeticOperator(char ch) {
			return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||ch == '%';
		}

		bool isCommand(std::string s) {
			return s == "let" || s == "if" || s == "goto" || s == "input" || s == "print";
		}

		bool isLogicOperator(char c) {
			return c == '&' || c == '<' || c == '>' || c == '|' || c == '=' || c == '!';
		}

		bool isLogicOperator(std::string s) {
			return s == "==" || s == "!=" || s == "<=" || s == ">=" || s == "&&" || s == "||";
		}

		CommandType stringToType(std::string s) {
			if (s == "let")
				return Let;
			else if (s == "if")
				return If;
			else if (s == "goto")
				return Goto;
			else if (s == "input")
				return Input;
			else if (s == "print")
				return Print;

			return Let;
		}



		std::map<std::string, int> opPrecednce = {
			{"+",2},
			{ "-",2 },
			{ "*",3 },
			{ "/",3 },
			{ "%",3 },
			{ "^",4 },
			{ "sqrt",4 },
			{ "abs",4 },
			{ "log",4 },
			{ "sin",4 },
			{ "cos",4 },
			{ "tan",4 },
			{"=",1},
			{ "<",1},
			{ ">",1 },
			{ "==",1 },
			{ "&&",1 },
			{ "||",1 },
			{ "<=",1 },
			{ ">=",1 },
			{ "!=",1 }
		};

		std::map < std::string, bool> associativity = {
			{ "+",false },
			{ "-",true },
			{ "*",false },
			{ "/",true },
			{ "%",true},
			{ "^",true},
			{ "sqrt",false },
			{ "abs",false},
			{ "log",false},
			{ "sin",false},
			{ "cos",false},
			{ "tan",false},
			{ "=",true },
			{ "<",true},
			{ ">",true },
			{ "==",false },
			{ "&&",false },
			{ "||",false},
			{ "<=",true},
			{ ">=",true},
			{ "!=",false }
		};


		void emptyCharBuffer(std::string &s,std::vector<Token*> &res) {

			

			//check if there is a register
			if (s.length() == 1) {
				res.push_back(new Token(s, Helper::Register));
				s = "";
			}
			//check for the command
			else if (isCommand(s)) {
				res.push_back(new Token(s, Helper::Command));
				s = "";
			}

			//check for function
			else if (s.length() > 0 && !isCommand(s)) {
				res.push_back(new Operator(s, opPrecednce[s],Helper::ArithmeticOperator,associativity[s]));
				s = "";
			}

		}

		void emptyNumberBuffer(std::string &s,std::vector<Token*> &res){
			//check if there's numbers to unload
			if (s.length() > 0) {
				res.push_back(new Operand(s));
				s = "";
			}
		}

		void emptyLogicOpBuffer(std::string &s, std::vector<Token*> &res) {
			//if its length is only one it's one of these: '=' '<' '>'
			if (s.length() == 1) {

				Helper::TokenType t = s == "=" ? Helper::ArithmeticOperator : Helper::LogicOperator;

				res.push_back(new Operator(s, opPrecednce[s],t,associativity[s]));
				s = "";

			}


			if (isLogicOperator(s)) {

				res.push_back(new Operator(s, opPrecednce[s],Helper::LogicOperator,associativity[s]));
				s = "";

			}

		}


	}


	std::vector<Token*> tokenize(std::string s) {

		std::vector<Token*> result;

		std::string charBuffer = "";
		std::string numberBuffer = "";
		std::string logicOpBuffer = "";


		for (size_t i = 0;i < s.length();i++) {

			char ch = s[i];
			if (isDigit(ch)) {
				//check for =
				emptyLogicOpBuffer(logicOpBuffer,result);

				numberBuffer += ch;
			}
			else if (isLetter(ch)) {
				//check for =
				emptyLogicOpBuffer(logicOpBuffer, result);

				charBuffer += ch;
			}
			else if (isLogicOperator(ch)) {

				emptyCharBuffer(charBuffer, result);
				emptyNumberBuffer(numberBuffer, result);

				logicOpBuffer += ch;
			}
			else if (isArithmeticOperator(ch)) {

				emptyCharBuffer(charBuffer, result);
				emptyNumberBuffer(numberBuffer, result);

				//add the operator to the result
				std::string s1(1, ch);
				result.push_back(new Operator(s1, opPrecednce[s1],Helper::ArithmeticOperator,associativity[s1]));
			}
			else if (isLeftBracket(ch)) {
				emptyCharBuffer(charBuffer, result);

				result.push_back( new Token(std::string(1,ch), Helper::LeftbBracket, 0));
			}
			else if (isRightBracket(ch)) {
				
				emptyCharBuffer(charBuffer, result);
				emptyNumberBuffer(numberBuffer, result);


				std::string s1(1, ch);
				result.push_back(  new Token(s1, Helper::RightBracket, 0));
			}
			else if (ch == ' ') {


				emptyCharBuffer(charBuffer, result);
				emptyNumberBuffer(numberBuffer, result);

				emptyLogicOpBuffer(logicOpBuffer, result);

			}

		}
		emptyNumberBuffer(numberBuffer, result);
		emptyCharBuffer(charBuffer, result);
		emptyLogicOpBuffer(logicOpBuffer, result);


		return result;


	}



	Command* buildCommand(std::vector<Token*> tokens) {

		Command * res;


		//the first token should be a command
		if (!isCommand(tokens[0]->getTokenString())) {
			std::string err = "Invalid Command:" + tokens[0]->getTokenString();
			for (auto i : tokens) delete i;

			throw std::out_of_range(err.c_str());
		}

		if (tokens[0]->getTokenString() == "if") {


			std::vector<Token*>::iterator rightBracket;
			//search for the condition's end;
			int bracketCounter = 0;
			for (std::vector<Token*>::iterator i = tokens.begin() + 1;i != tokens.end();i++) {
				if ((*i)->getType() == Helper::LeftbBracket) bracketCounter++;
				else if ((*i)->getType() == Helper::RightBracket) bracketCounter--;


				if (bracketCounter == 0) {
					rightBracket = i;
					break;
				}
			}


			//get the condition tokens excluding the brackets
			std::vector<Token*> conditionTokens(tokens.begin() + 2, rightBracket);
			Expression lE(conditionTokens);




			//get the other command token
			std::string cmdString = (*(rightBracket + 1))->getTokenString();
			if (!isCommand(cmdString)) { 

				for (auto i : tokens) delete i;

				throw std::out_of_range("Invalid command in if statement"); 
			}
			CommandType c = stringToType(cmdString);


			//delete the extra brackets
			delete *(tokens.begin() + 1);
			delete *(rightBracket);

			//delete the command token
			delete *(rightBracket + 1);

			//get the expression
			std::vector<Token*> otherCommand(rightBracket + 2, tokens.end());
			Expression e(otherCommand);
			//SingleArgCommand cmd(c,e);


			res = new MultiArgCommand(SingleArgCommand(c,e), lE);





		}
		else {
			CommandType c = stringToType(tokens[0]->getTokenString());
			//everything after the command is an expression
			std::vector<Token*> exprTokens(tokens.begin()+1,tokens.end());
			Expression e(exprTokens);

			res = new SingleArgCommand(c, e);

		}

		//never really use it anymore
		delete tokens[0];

		return res;


	}



}