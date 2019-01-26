#ifndef COMMAND_H
#define COMMAND_H 

#include <iostream>
#include "Token.h"
#include "Expression.h"
#include "Registers.h"

enum CommandType{ Let,If,Goto,Print,Input };

class Command : public Token
{
	protected:
		CommandType commandType;

	public:
		Command(CommandType c,std::string s = "") :Token(s,Helper::Command), commandType(c) {};
		virtual ~Command(){}

		virtual void clear() = 0;
		virtual void Execute() = 0;

};


class SingleArgCommand : public Command {

	Expression expr;

	public:
		SingleArgCommand(CommandType c,Expression e):Command(c),expr(e){}

		void Execute() override;

		void clear() override { expr.clear(); }

};

class MultiArgCommand : public Command {

	Expression condition;
	SingleArgCommand cmd;

	public:
		MultiArgCommand(SingleArgCommand c, Expression le) :Command(If),condition(le),cmd(c){}


		void Execute() override;

		void clear() override { condition.clear();cmd.clear(); }


};

#endif // !COMMAND_H