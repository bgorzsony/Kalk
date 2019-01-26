#include "Program.h"
#include "memtrace.h"

size_t Program::cmdPtr = 0;

void Program::addNewCommand(Command * cmd) {
	this->commands.push_back(cmd);
}

void Program::setCmdPtr(int v) {
	v = v - 2;
	if (v < -1) {
		throw std::out_of_range("Wrong tag at Goto");
	}
	cmdPtr = v;
}


void Program::Run() {
	
	while (this->cmdPtr != this->commands.size()) {

		Command* a = this->commands[this->cmdPtr];
		a->Execute();

		this->cmdPtr++;


	}




}


Program::~Program() {
	for (auto i : this->commands) {
		i->clear();
		delete i;
	}
}