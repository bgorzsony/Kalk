#ifndef PROGRAM_H
#define PROGRAM_H 

#include <vector>
#include "Command.h"



class Program
{
	private:
		std::vector<Command*> commands;
		 static size_t cmdPtr;
		 Program(){}

	public:
		void addNewCommand(Command * cmd);

		void Run();

		static void setCmdPtr(int v);

		static Program& getInstance() {
			static Program p;
			return p;
		}


		~Program();

};

#endif