#define _CRT_SECURE_NO_WARNINGS 

#include "Error.h"

namespace ict {
	Error::Error()
	{
		m_message = nullptr;
	}
	Error::Error(const char* errorMessage)
	{
		m_message = nullptr;
		message(errorMessage);
	}
	Error::~Error()
	{
		clear();
	}
	void Error::operator=(const char* errorMessage)
	{
		message(errorMessage);
	}
	void Error::clear()
	{
		if (m_message != nullptr)
		{
			delete[] m_message;
		}
		m_message = nullptr;
	}

	bool Error::isClear()const
	{
		return m_message == nullptr;
	}
	void Error::message(const char* value)
	{
		clear();
		m_message = new char[strlen(value) + 1];
		strcpy(m_message, value);
	}
	Error::operator const char*() const
	{
		return m_message;
	}
	Error::operator bool()const
	{
		return isClear();
	}

	std::ostream& operator<<(std::ostream& os, const Error& e)
	{
		if (!e.isClear())
		{
			os << (const char*)e;
		}
		return os;
	}
}