#ifndef REGISTERS_H
#define REGISTERS_H


#include <stdexcept>
#include "Operand.h"

struct Register {
	char name;
	Operand storage;
	Register(char c, Operand o) :name(c), storage(o) {};
};

//Singleton collection of registers
class RegisterCollection
{

	private:
		RegisterCollection() {};
		const static int regNumber;
		static Register regArray[5];

	public:
		static RegisterCollection& getInstance() {
			static RegisterCollection instance;

			return instance;
		}

		static bool validRegister(char c) {
			return c == 'a' || c == 'b' || c == 'c' || c == 'i' || c == 'j';
		}

		Operand& operator[](char which);
		const Operand& operator[](char which) const;

};

#endif