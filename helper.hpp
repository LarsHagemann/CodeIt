#pragma once
#include <random>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
using uuid = unsigned long long;

static uuid generateUnique()
{
	static std::random_device rd;
	static std::mt19937_64 gen(rd());

	return gen();
}

template<size_t Length = 1024, class ...Args>
static std::string sprint(const char* format, Args... args)
{
	char buffer[Length];
	auto size = sprintf_s(buffer, format, args...);
	return std::string(buffer, static_cast<unsigned>(size));
}

template<class T>
static std::string tostring(const T& string)
{
	std::ostringstream oss;
	oss << string;
	return oss.str();
}
