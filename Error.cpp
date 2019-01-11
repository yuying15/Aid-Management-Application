#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include "Error.h"
using namespace std;
using namespace aid;

namespace aid
{
	Error::Error(const char* errorMessage)
	{
		if (errorMessage != nullptr && errorMessage != '\0')
		{
			m_message = new char[strlen(errorMessage) + 1];
			strcpy(m_message, errorMessage);
		}
		else
		{
			m_message = nullptr;
		}
	}

	Error::~Error()
	{
		delete[] m_message;
	}

	void Error::clear()
	{
		delete[] m_message;
		m_message = nullptr;
	}

	bool Error::isClear() const
	{
		return (m_message == nullptr || m_message[0] == '\0');
	}

	void Error::message(const char* str)
	{
		delete[] m_message;

		if (str != nullptr && str != '\0')
		{
			m_message = new char[strlen(str) + 1];
			strcpy(m_message, str);
		}
		else
		{
			m_message = nullptr;
		}
	}

	const char* Error::message() const
	{
		return m_message;
	}

	std::ostream& operator<<(std::ostream& os, const Error& em)
	{
		if (!em.isClear())
		{
			os << em.message();
		}

		return os;
	}
}


