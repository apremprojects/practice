#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

enum class DAY {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

DAY increment(const DAY &day) {
	if (day == DAY::MONDAY) {
		return DAY::TUESDAY;
	}
	else if (day == DAY::TUESDAY) {
		return DAY::WEDNESDAY;
	}
	else if (day == DAY::WEDNESDAY) {
		return DAY::THURSDAY;
	}
	else if (day == DAY::THURSDAY) {
		return DAY::FRIDAY;
	}
	else if (day == DAY::FRIDAY) {
		return DAY::SATURDAY;
	}
	else if (day == DAY::SATURDAY) {
		return DAY::SUNDAY;
	}
	else if (day == DAY::SUNDAY) {
		return DAY::MONDAY;
	}
}

DAY increment(DAY day, const int amt) {
	for (int i = 0; i < (amt % 7); i++) {
		day = increment(day);
	}
	return day;
}

string disp_day(const DAY &day) {
	switch (day) {
	case DAY::MONDAY:
		return "Monday";
	case DAY::TUESDAY:
		return "Tuesday";
	case DAY::WEDNESDAY:
		return "Wednesday";
	case DAY::THURSDAY:
		return "Thursday";
	case DAY::FRIDAY:
		return "Friday";
	case DAY::SATURDAY:
		return "Saturday";
	case DAY::SUNDAY:
		return "Sunday";
	}
	return "-1";
}

int month_num_to_days(int month_num, const int year) {
	if (month_num == 1 || month_num == 3 || month_num == 5 || month_num == 7 || month_num == 8 || month_num == 10 || month_num == 12) {
		return 31;
	}
	else if (month_num == 4 || month_num == 6 || month_num == 9 || month_num == 11) {
		return 30;
	}
	else if(month_num == 2) {
		if (year % 100 == 0) {//century year
			if (year % 400 == 0) { //leap year
				return 29;
			}
		}
		else if (year % 4 == 0) {//leap year
			return 29;
		}
		return 28;
	}
	else {
		cout << "ERROR -> " << month_num << "\n";
		throw std::invalid_argument("month_num MUST be less than 12");
	}
	return -1;
}

class Date {
public:
	Date(const int _month_num, const DAY _day, const int _day_num, const int _year): month_num(_month_num), day(_day), day_num(_day_num), year(_year) {}
	void increment_day(const int amt) {
		day_num+=amt;
		day = increment(day, amt);
		int max_size = month_num_to_days(month_num, year);
		if (day_num > max_size) {
			month_num += day_num / max_size;
			day_num %= max_size;
		}
		if (month_num > 12) {
			year += month_num / 12;
			month_num %= 12;
		}
	}
	void increment_month(const int amt) {
		for (int i = 0; i < amt; i++) {
			day = increment(day, month_num_to_days(month_num, year));
			month_num++;
			if (month_num > 12) {
				month_num %= 12;
				year++;
			}
		}
	}
	void increment_year(const int amt) {
		year+=amt;
	}
	void disp() {
		cout << month_num << "/" << day_num << "/" << year << " -> " << disp_day(day) << "\n";
	}
	int month_num;
	DAY day;
	int day_num;
	int year;
};

bool operator<(const Date& a, const Date& b) {
	if (a.year < b.year) {
		return true;
	}
	else if(a.year == b.year){
		if (a.month_num < b.month_num) {
			return true;
		}
		else if (a.month_num == b.month_num) {
			return a.day_num < b.day_num;
		}
	}
	return false;
}

int main() {
	int N;
	cin >> N;
	Date date(1, DAY::SATURDAY, 13, 1900);//jan 13, 1900
	Date endDate(12, DAY::MONDAY, 31, 1900 + N - 1);
	int sat = 0;
	int sun = 0;
	int mon = 0;
	int tues = 0;
	int wed = 0;
	int thurs = 0;
	int fri = 0;
	while (date < endDate) {
		if (date.day == DAY::SATURDAY) {
			sat++;
		}
		else if (date.day == DAY::SUNDAY) {
			sun++;
		}
		else if (date.day == DAY::MONDAY) {
			mon++;
		}
		else if (date.day == DAY::TUESDAY) {
			tues++;
		}
		else if (date.day == DAY::WEDNESDAY) {
			wed++;
		}
		else if (date.day == DAY::THURSDAY) {
			thurs++;
		}
		else if (date.day == DAY::FRIDAY) {
			fri++;
		}
		date.increment_month(1);
	}
	cout << sat << " " << sun << " " << mon << " " << tues << " " << wed << " " << thurs << " " << fri << "\n";
}