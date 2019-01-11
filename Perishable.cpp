// Final Project - Milestone 5
// Name: Qirong Fu
// Student #: 158899179
// Course: OOP244 Fall 2018
// File: Perishable.cpp

#include <iostream>
#include <fstream>
#include "Perishable.h"
using namespace std;
using namespace aid;

namespace aid
{
	Perishable::Perishable() :Good('P')
	{
		Date expiry_date;
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{

		Good::store(file, newLine = false);
		file << ',' << expiryDate << endl;

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		expiryDate.read(file);
		file.ignore();
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Good::write(os, linear);

		if (isClear() && !isEmpty())
		{
			if (linear)
			{
				os << expiryDate;
			}
			else {
				os << endl;
				os << " Expiry date: " << expiryDate;
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		Good::read(is);

		cout << " Expiry date (YYYY/MM/DD): ";
		expiryDate.read(is);

		if (expiryDate.errCode() == CIN_FAILED)
		{
			message("Invalid Date Entry");
			is.setstate(std::ios::failbit);
		}
		else if (expiryDate.errCode() == YEAR_ERROR)
		{
			message("Invalid Year in Date Entry");
			is.setstate(std::ios::failbit);
		}
		else if (expiryDate.errCode() == MON_ERROR)
		{
			message("Invalid Month in Date Entry");
			is.setstate(std::ios::failbit);
		}
		else if (expiryDate.errCode() == DAY_ERROR)
		{
			message("Invalid Day in Date Entry");
			is.setstate(std::ios::failbit);
		}
		else if (expiryDate.errCode() == PAST_ERROR)
		{
			message("Invalid Expiry in Date Entry");
			is.setstate(std::ios::failbit);
		}

		return is;
	}

	const Date& Perishable::expiry() const
	{
		return expiryDate;
	}
}

