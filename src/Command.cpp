#include "Command.h"
#include "Program.h"
#include "memtrace.h"

void SingleArgCommand::Execute(){
	char reg;
	switch (commandType)
	{
	case Let:
		//it works itself yay;
		this->expr.solve();
		break;
	case Print:
		std::cout << this->expr.solve() << std::endl;
		break;
	case Input:
		reg = this->expr.getFirstToken()->getTokenString()[0];
		float input;
		std::cout << reg << "= ";
		std::cin >> input;
		RegisterCollection::getInstance()[reg].setValue(input);
		break;
	case Goto:
		Program::getInstance().setCmdPtr((int)this->expr.solve());
		break;
	case If:
		//thanks jporta
		break;
		
	}


}

void MultiArgCommand::Execute() {

	if (condition.solve())
		this->cmd.Execute();


}