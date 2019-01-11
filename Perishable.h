// Final Project - Milestone 5
// Name: Qirong Fu
// Student #: 158899179
// Course: OOP244 Fall 2018
// File: Perishable.h

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H

#include <iostream>
#include <fstream>
#include "Good.h"
#include "Date.h"

namespace aid
{
	class Perishable : public Good {
		Date expiryDate;

	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream&, bool linear) const;
		std::istream& read(std::istream&);
		const Date& expiry() const;
	};
}
#endif

