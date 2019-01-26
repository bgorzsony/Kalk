

#include <iostream>
#include <fstream>
#include "Token.h"
#include "Registers.h"
#include "Operator.h"
#include "Tokenizer.h"
#include "Expression.h"
#include "Program.h"
#include "memtrace.h"


using std::cout;
using std::endl;

#define CPORTA

int main(int argc, char** argv) {
	
	/*cout << sizeof(Token) << endl;
	cout << sizeof(Operand) << endl;
	cout << sizeof(Operator) << endl;
	cout << sizeof(Command) << endl;
	cout << sizeof(Expression) << endl;*/


#ifdef CPORTA
	std::istream& is = std::cin;
#endif // CPORTA

#ifndef  CPORTA

	if (argc < 2) {
		std::cout << "Filename expected" << std::endl;
		return 1;
	}

	std::ifstream fs;

	fs.open(argv[1]);
	if (!fs.is_open()) { std::cerr << "Can't open file" << std::endl;return 1; }

	std::istream& is = fs;
#endif // ! CPORTA


	std::string line;
	Program p = Program::getInstance();


	try {
		while (getline(is, line)) {
			if (line == "") continue;
			std::vector<Token*> tokens = Tokenizer::tokenize(line);
			Command* cmd = Tokenizer::buildCommand(tokens);
			p.addNewCommand(cmd);
		}
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}


	std::cin.clear();

	try {
		p.Run();
	}
	catch(std::exception e){
		std::cerr << e.what() << std::endl;
	}


#ifndef  CPORTA
	fs.close();
#endif // ! CPORTA


	return 0;
}