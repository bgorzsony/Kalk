#include <cmath>
#include "Operand.h"
#include "memtrace.h"

Operand::Operand(std::string s, Helper::TokenType t) : Token(s,t)
{
	this->value = std::stof(s);
}
Operand::Operand(float v,Helper::TokenType t):Token(std::to_string(v),t) {
	this->value = v;
}

//soo much operator overloading
Operand Operand::operator+(const Operand& rhs) {

	return Operand(this->value + rhs.getValue());
}

Operand Operand::operator-(const Operand& rhs) {

	return Operand(this->value - rhs.getValue());
}

Operand Operand::operator/(const Operand& rhs) {
	return Operand(this->value / rhs.getValue());
}
Operand Operand::operator*(const Operand& rhs) {

	return Operand(this->value * rhs.getValue());
}
Operand Operand::operator^(const Operand& rhs) {

	return Operand(powf(this->value, rhs.getValue()));
}
Operand Operand::operator%(const Operand& rhs) {

	return Operand((int)this->value % (int)rhs.getValue());
}

Operand& Operand::operator=(const Operand& rhs) {

	if (&rhs == this) return *this;

	

	this->value = rhs.getValue();

	return *this;

}

bool Operand::operator==(const Operand& rhs) const {
	return this->value == rhs.getValue();
}

bool Operand::operator!=(const Operand& rhs) const {
	return this->value != rhs.getValue();
}

bool Operand::operator<(const Operand& rhs) const {
	return this->getValue() < rhs.getValue();
}
bool Operand::operator>(const Operand& rhs) const {
	return this->getValue() > rhs.getValue();
}

bool Operand::operator&&(const Operand& rhs) const {
	return this->value && rhs.getValue();
}
bool Operand::operator||(const Operand& rhs) const {
	return this->value || rhs.getValue();
}
bool Operand::operator<=(const Operand& rhs) const {
	return this->value <= rhs.getValue();
}
bool Operand::operator>=(const Operand& rhs) const {
	return this->value >= rhs.getValue();
}