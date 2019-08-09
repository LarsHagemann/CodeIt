#pragma once
#include <string>
#include <fstream>

enum ETokenType
{
	T_NUMBER = 0,
	T_CBRACKET_LEFT = 1,
	T_CBRACKET_RIGHT = 2,
	T_SBRACKET_LEFT = 3,
	T_SBRACKET_RIGHT = 4,
	T_PAREN_LEFT = 5,
	T_PAREN_RIGHT = 6,
	T_HASH = 7,
	T_COMMA = 8,
	T_IDENTIFIER = 9,
	T_EOF = 10,
	T_INVALID = 11
};

struct Token
{
	std::string lexeme;
	ETokenType type;
};

class Scanner
{
private:
	std::ifstream& m_input;
	unsigned m_begin;
private:
	std::string read_from_input(unsigned begin, unsigned length);
	unsigned current() const { return static_cast<unsigned>(m_input.tellg()); }

	Token make_token(ETokenType type);
	Token make_comment();
	Token make_multiline_comment();
	Token make_number();
	Token make_identifier();

	char advance();
	char peek();

	void skip_whitespace();
public:
	Scanner(std::ifstream& input);
	Token scanToken();
};
