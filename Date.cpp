// Final Project - Milestone 5
// Name: Qirong Fu
// Student #: 158899179
// Course: OOP244 Fall 2018
// File: Date.cpp

// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "Date.h"
using namespace aid;

namespace aid
{

	Date::Date()
	{
		year = 0;
		month = 0;
		day = 0;
		comparator = 0;
		error_state = NO_ERROR;
	}

	Date::Date(int m_year, int m_month, int m_day)
	{
		if ((m_year >= min_year) && (m_year <= max_year) && (m_month >= 1 && m_month <= 12) && (m_day >= 1) && (m_day <= mdays(m_month, m_year)))
		{
			year = m_year;
			month = m_month;
			day = m_day;
			error_state = NO_ERROR;
			comparator = m_year * 372 + m_month * 31 + m_day;
		}
		else
		{
			if (m_year<min_year || m_year>max_year)
			{
				error_state = YEAR_ERROR;
			}
			else if (m_month < 1 || m_month>12)
			{
				error_state = MON_ERROR;
			}
			else if (m_day<1 || m_day>mdays(m_month, m_year))
			{
				error_state = DAY_ERROR;
			}

			*this = Date();
		}
	}

	// number of days in month mon and year year
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode)
	{
		error_state = errorCode;
	}

	int Date::errCode() const
	{
		return error_state;
	}

	bool Date::bad() const
	{
		return !NO_ERROR;
	}

	bool Date::operator==(const Date& rhs) const
	{
		return (comparator == rhs.comparator);
	}

	bool Date::operator!=(const Date& rhs) const
	{
		return (comparator != rhs.comparator);
	}

	bool Date::operator<(const Date& rhs) const
	{
		return (comparator < rhs.comparator);
	}

	bool Date::operator>(const Date& rhs) const
	{
		return (comparator > rhs.comparator);
	}

	bool Date::operator<=(const Date& rhs) const
	{
		return (comparator <= rhs.comparator);
	}

	bool Date::operator>=(const Date& rhs) const
	{
		return (comparator >= rhs.comparator);
	}

	std::istream& Date::read(std::istream& istr)
	{
		char a;
		int year, month, day;

		istr.clear();

		istr >> year >> a >> month >> a >> day;
		
		errCode(NO_ERROR);

		if (istr.fail())
		{
			errCode(CIN_FAILED);
		}
		else if (year<min_year || year>max_year)
		{
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (month < 1 || month>12)
		{
			*this = Date();
			errCode(MON_ERROR);
		}
		else if (day<1 || day>mdays(month, year))
		{
			*this = Date();
			errCode(DAY_ERROR);
		}
		else if ((year * 372 + month * 31 + day) < min_date)
		{
			*this = Date();
			errCode(PAST_ERROR);
		}
		else
		{
			*this = Date(year, month, day);
		}

		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const
	{
		ostr << year << "/" << std::setfill('0') << std::setw(2) << month << "/" << std::setfill('0') << std::setw(2) << day<<std::setfill(' ');
		return ostr;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		d.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& d)
	{
		d.read(is);
		return is;
	}
}

