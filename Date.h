#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace aid
{
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;
	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int DAY_ERROR = 2;
	const int MON_ERROR = 3;
	const int YEAR_ERROR = 4;
	const int PAST_ERROR = 5;

	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int error_state;
		int mdays(int, int)const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);
		int errCode() const;
		bool bad() const;
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}
#endif


