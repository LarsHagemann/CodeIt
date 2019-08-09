#include "scanner.hpp"

Token Scanner::make_token(ETokenType type)
{
	Token t;
	if (type != T_EOF)
		t.lexeme = read_from_input(
			m_begin,
			static_cast<unsigned>(m_input.tellg()) - m_begin
		);
	t.type = type;
	return t;
}

std::string Scanner::read_from_input(unsigned begin, unsigned length)
{
	auto c = current();
	std::string str;
	str.resize(length);
	m_input.seekg(begin);
	m_input.read((char*)str.data(), length);
	m_input.seekg(c);
	return str;
}

char Scanner::advance()
{
	return static_cast<char>(m_input.get());
}

char Scanner::peek()
{
	return static_cast<char>(m_input.peek());
}

Token Scanner::make_comment()
{
	while (peek() != '\n' && !m_input.eof())
		advance();
	return scanToken();
}

Token Scanner::make_multiline_comment()
{
	while (true)
	{
		if (m_input.eof())
			break;
		auto c = advance();
		if (c == '*' && peek() == '/')
		{
			advance();
			break;
		}
	}
	return scanToken();
}

Token Scanner::make_number()
{
	while (std::isdigit(peek()))
		advance();
	return make_token(T_NUMBER);
}

Token Scanner::make_identifier()
{
	char c = peek();
	while (
		(isalnum(c) || c == '_')
		&& !m_input.eof())
	{
		advance();
		c = peek();
	}
	return make_token(T_IDENTIFIER);
}

void Scanner::skip_whitespace()
{
	while (true)
	{
		auto c = peek();
		if (c >= 33 && c <= 126)
			break;
		if (m_input.eof())
			break;
		advance();
	}
}

Scanner::Scanner(std::ifstream& input):
	m_input(input),
	m_begin(0)
{
}

Token Scanner::scanToken()
{
	skip_whitespace();
	if (m_input.eof())
		return make_token(T_EOF);

	m_begin = current();

	auto c = advance();
	if (isdigit(c) || c == '-')
		return make_number();
	if (isalpha(c))
		return make_identifier();

	switch (c)
	{
	case '#': return make_comment();
	case '{': return make_token(T_CBRACKET_LEFT);
	case '}': return make_token(T_CBRACKET_RIGHT);
	case '[': return make_token(T_SBRACKET_LEFT);
	case ']': return make_token(T_SBRACKET_RIGHT);
	case '(': return make_token(T_PAREN_LEFT);
	case ')': return make_token(T_PAREN_RIGHT);
	case ',': return make_token(T_COMMA);
	case '/': if (peek() == '*') return make_multiline_comment();
	default:
		break;
	}

	return make_token(T_INVALID);
}
