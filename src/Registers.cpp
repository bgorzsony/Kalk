#include "Registers.h"
#include "memtrace.h"

const int RegisterCollection::regNumber = 5;

Register RegisterCollection::regArray[] = {
	Register('a', Operand(0, Helper::Register)),
	Register('b', Operand(0, Helper::Register)),
	Register('c', Operand(0, Helper::Register)),
	Register('i', Operand(0, Helper::Register)),
	Register('j', Operand(0, Helper::Register)),
};


Operand& RegisterCollection::operator[](char which) {

	int i = 0;
	while (regArray[i].name != which && i<regNumber) i++;
	if (i == regNumber) throw std::out_of_range("Invalid referenced register");

	return regArray[i].storage;

}
const Operand& RegisterCollection::operator[](char which) const {

	return RegisterCollection::getInstance()[which];
}