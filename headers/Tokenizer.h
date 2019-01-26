#ifndef TOKENIZER_H
#define TOKENIZER_H 



#include <cctype>
#include <map>
#include <algorithm>
#include <string>
#include<vector>
#include <stdexcept>
#include "Token.h"
#include "Command.h"


namespace Tokenizer {


	std::vector<Token*> tokenize(std::string s);

	Command* buildCommand(std::vector<Token*> tokens);

}

#endif