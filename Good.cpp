#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>
#include "Good.h"
#include "Error.h"
using namespace aid;
using namespace std;

namespace aid
{
	Good::Good(const char n)
	{
		m_type = n;
		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		goodNumber = 0;
		goodNeed = 0;
		unit_price = 0.0;
		good_status = true;		
	}

	Good::Good(const char* n_sku, const char* n_name, const char* n_unit, bool n_status, double n_price, int n_number, int n_itemsNeed)
	{
		if (n_sku != nullptr && n_sku != '\0')
		{
			strncpy(m_sku, n_sku, max_sku_length);
			m_sku[max_sku_length] = '\0';
		}
		else
		{
			*this = Good();
		}

		name(n_name);		

		if (n_unit != nullptr &&n_unit != '\0')
		{
			strncpy(m_unit, n_unit, max_unit_length);
			m_unit[max_unit_length] = '\0';
		}
		else
		{
			*this = Good();
		}

		if (n_number > 0)
		{
			goodNumber = n_number;
		}
		else
		{
			goodNumber = 0;
		}

		good_status = n_status;

		if (n_price > 0.0)
		{
			unit_price = n_price;
		}
		else
		{
			unit_price = 0.0;
		}

		if (n_itemsNeed > 0)
		{
			goodNeed = n_itemsNeed;
		}
		else
		{
			goodNeed = 0;
		}
	}

	Good::Good(const Good& m_Good)
	{
		m_name = nullptr;
		*this = m_Good;
	}

	Good& Good::operator=(const Good& m_Good)
	{
		if (this != &m_Good)
		{
			e_error.clear();

			if (m_Good.m_type == 'P' || m_Good.m_type == 'N')
			{
				m_type = m_Good.m_type;
			}

			strncpy(m_sku, m_Good.m_sku, max_sku_length);
			m_sku[max_sku_length] = '\0';
			strncpy(m_unit, m_Good.m_unit, max_unit_length);
			m_unit[max_unit_length] = '\0';
			goodNumber = m_Good.goodNumber;
			goodNeed = m_Good.goodNeed;
			unit_price = m_Good.unit_price;
			good_status = m_Good.good_status;

			delete[] m_name;

			if (m_Good.m_name != nullptr)
			{
				m_name = new char[strlen(m_Good.m_name) + 1];
				strcpy(m_name, m_Good.m_name);
			}
			else
			{
				m_name = nullptr;
			}
		}

		return *this;
	}

	Good::~Good()
	{
		delete[] m_name;
	}

	fstream& Good::store(std::fstream& file, bool newLine) const
	{
		if (file.is_open())
		{
			file << m_type << ",";
			file << m_sku << ",";
			file << m_name << ",";
			file << m_unit << ",";
			file << good_status << ",";
			file << unit_price << ",";
			file << goodNumber << ",";
			file << goodNeed;

			if (newLine == true)
			{
				file << std::endl;
			}
		}

		return file;
	}

	std::fstream& Good::load(std::fstream& file)
	{
		char t_type;
		char t_sku[max_sku_length + 1];
		char t_name[max_name_length + 1];
		char t_unit[max_unit_length + 1];
		int t_quantity;
		int t_qtyNeeded;
		double t_price;
		bool t_status;

		if (file.is_open())
		{
			file.getline(t_sku, max_sku_length, ',');
			t_sku[strlen(t_sku)] = '\0';

			file.getline(t_name, max_name_length, ',');
			t_name[strlen(t_name)] = '\0';

			file.getline(t_unit, max_unit_length, ',');
			t_unit[strlen(t_unit)] = '\0';

			file >> t_type;

			if (t_type == '1')
			{
				t_status = true;
			}
			else if (t_type == '0')
			{
				t_status = false;
			}

			file.ignore();

			file >> t_price;
			file.ignore();

			file >> t_quantity;
			file.ignore();

			file >> t_qtyNeeded;
			file.ignore();

			Good tgood = Good(t_sku, t_name, t_unit, t_status, t_price, t_quantity, t_qtyNeeded);
			*this = tgood;
		}

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (linear)
		{
			if (!e_error.isClear())
			{
				os << e_error.message();
			}
			else
			{
				os.setf(std::ios::left);
				os.width(max_sku_length);
				os << m_sku << '|';
				os.width(20);
				os << m_name << '|';
				os.unsetf(std::ios::left);
				os.setf(std::ios::fixed);
				os.width(7);
				os.precision(2);
				os << itemCost() << '|';
				os.width(4);
				os << goodNumber << '|';
				os.setf(std::ios::left);
				os.width(10);
				os << m_unit << '|';
				os.unsetf(std::ios::left);
				os.setf(std::ios::fixed);
				os.width(4);
				os << goodNeed << '|';
			}
		}
		else
		{
			os << " Sku: " << m_sku << std::endl;
			os << " Name (no spaces): ";

			int nameLength = (strlen(m_name) > max_name_length) ? max_name_length : strlen(m_name);
			for (int i = 0; i < nameLength; i++)
			{
				os << m_name[i];
			}

			os << std::endl;
			os << " Price: " << unit_price << std::endl;

			if (good_status)
			{
				os << " Price after tax: " << itemCost() << std::endl;
			}
			else
			{
				os << " Price after tax:  N/A" << std::endl;
			}

			os << " Quantity on Hand: " << goodNumber << ' ' << m_unit << std::endl;
			os << " Quantity needed: " << goodNeed;
		}

		return os;
	}

	std::istream& Good::read(std::istream& is)
	{
		char t_sku[max_sku_length + 1];
		char t_name[max_name_length + 1];
		char t_unit[max_unit_length + 1];
		int t_quantity, t_qtyNeeded;
		double t_price;
		char t_tax;
		bool t_status;
		
		e_error.clear();

		std::cout << " Sku: ";
     	is >> t_sku;
		std::cout << " Name (no spaces): ";
		is >> t_name;
		std::cout << " Unit: ";
		is >> t_unit;
		std::cout << " Taxed? (y/n): ";
		is >> t_tax;
		switch (t_tax)
		{
		case 'y':
		case 'Y':
			t_status = true;
			break;
		case 'n':
		case 'N':
			t_status = false;
			break;
		default:
			is.setstate(std::ios::failbit);
			message("Only (Y)es or (N)o are acceptable");
		}

		if (!is.fail())
		{
			std::cout << " Price: ";
			is >> t_price;

			if (is.fail())
			{
				message("Invalid Price Entry");
			}
		}

		if (!is.fail())
		{
			std::cout << " Quantity on hand: ";
			is >> t_quantity;
			if (is.fail())
			{
				message("Invalid Quantity Entry");
			}
		}

		if (!is.fail())
		{

			std::cout << " Quantity needed: ";
			is >> t_qtyNeeded;
			if (is.fail())
			{
				message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail())
		{
			Good tgood = Good(t_sku, t_name, t_unit, t_status, t_price, t_quantity, t_qtyNeeded);
			*this = tgood;
		}

		cin.ignore(1000, '\n');

		return is;
	}

	bool Good::operator==(const char* n_sku) const
	{
		return strcmp(m_sku, n_sku) == 0;
	}

	double Good::total_cost() const
	{
		if (good_status)
		{
			return goodNumber * unit_price*(1 + taxRate);
		}
		else
		{
			return goodNumber * unit_price;
		}
	}

	void Good::quantity(int num)
	{
		if (num > 0)
		{
			goodNumber = num;
		}
	}

	bool Good::isEmpty() const
	{
		return  m_name == nullptr || m_name == '\0';
	}

	int Good::qtyNeeded() const
	{
		return goodNeed;
	}

	int Good::quantity() const
	{
		return goodNumber;
	}

	bool Good::operator > (const char* good_sku) const
	{
		if (strcmp(good_sku, m_sku) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Good::operator>(const iGood& n_Good) const
	{
		if (strcmp(m_name, n_Good.name()) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int Good::operator += (int unitsNum)
	{
		if (unitsNum > 0)
		{
			return (goodNumber + unitsNum);
		}
		else
		{
			return goodNumber;
		}
	}


	std::ostream& operator<<(std::ostream& os, const iGood& n_Good)
	{
		n_Good.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, iGood& n_Good)
	{
		n_Good.read(is);
		return is;
	}

	double operator+=(double& cost, const iGood& n_Good)
	{
		return (n_Good.total_cost() + cost);
	}

	void Good::name(const char* nameGood)
	{
		if (nameGood == nullptr || nameGood == '\0')
		{
			m_name = nullptr;
		}
		else
		{
			m_name = new char[strlen(nameGood) + 1];
			strcpy(m_name, nameGood);
		}
	}

	const char* Good::name() const
	{
		if (m_name != nullptr && m_name != '\0')
		{
			return m_name;
		}
		else
		{
			return nullptr;
		}
	}

	const char* Good::sku() const
	{
		return m_sku;
	}

	const char* Good::unit() const
	{
		return m_unit;
	}

	bool Good::taxed() const
	{
		return good_status;
	}

	double Good::itemPrice() const
	{
		return unit_price;
	}

	double Good::itemCost() const
	{
		if (good_status)
		{
			return itemPrice() * (1 + taxRate);
		}
		else
		{
			return itemPrice();
		}
	}

	void Good::message(const char* errorMessage)
	{
		if (errorMessage != nullptr && errorMessage != '\0')
		{
			e_error.clear();
			e_error.message(errorMessage);
		}
		else
		{
			e_error.clear();
		}
	}

	bool Good::isClear() const
	{
		return e_error.isClear();
	}
}
