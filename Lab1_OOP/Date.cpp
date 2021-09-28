#include "Date.h"


Date::Date()
{
	year = hour = minute = second = 0;
	month = day = 0;
}

Date::Date(int year, int month, int day, int hour, int minute, int second)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

bool Date::isLeapYear()
{
	return (!(year % 4) && (year % 100) || !(year % 100));
}

int Date::getDaysInMonth()
{
	if (month <= 0 || month > 12)
		return -1;
	if (month == 2 && isLeapYear())
		return (dayInMonth[1] + 1);
	else
		return dayInMonth[month-1];
}

int Date::getDayOfWeek()
{
	if (!isCorrectDate())
		return -1;
	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	int res = ((day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7);//0 - monday, 6- sunday
	res--;
	if (res < 0)
		res = 6;
	return res;
}

bool Date::isCorrectDate() 
{
	if ((second >= 0) && (second < 60) && (minute >= 0) && (minute < 60) && (hour >= 0)
		&& (hour < 24) && (day > 0) && (year > 0) && (month > 0) && (month <= 12) && day<=getDaysInMonth())
		return true;
	return false;
}

int Date::getWeekInMonth()
{
	if (!isCorrectDate())
		return -1;
	Date copy(year, month, day, hour, minute, second);
	int ans = 0;
	if (getDayOfWeek() != 6)
	{
		ans++;
		copy.day -= (static_cast<int>(getDayOfWeek()) + 1);
	}
	while (copy.day > 0)
	{
		ans++;
		copy.day -= 7;
	}
	return ans;
}
int Date::getWeekInYear()
{
	if (!isCorrectDate())
		return -1;
	Date copy(year, 1, 4, 0, 0, 0);
	const Date c_copy(year, month, day, hour, minute, second), week(0,0,7,0,0,0);
	if (month == 1 && day < 4)
		copy.year--;
	int ans = 0;
	while (copy <= c_copy)
	{
		copy = copy + week;
		/*if (copy.month == 6)
		{
			
		}*/
		ans++;
	}
	return ans;
}

bool operator< (const Date& a, const Date& b)
{
	if ((a.year < b.year)
		|| ((a.year == b.year) && ((a.month < b.month)
			|| ((a.month == b.month) && ((a.day < b.day)
				|| ((a.day == b.day) && ((a.hour < b.hour)
					|| ((a.hour == b.hour) && ((a.minute < b.minute)
						|| (a.minute == b.minute && a.second < b.second))))))))))
		return true;
	else
		return false;
}

bool operator== (const Date& a, const Date& b)
{
	if (a.year == b.year && a.month == b.month && a.day == b.day && a.hour == b.hour && a.minute == b.minute && a.second == b.second)
		return true;
	return false;
}
bool operator<= (const Date& a, const Date& b)
{
	if ((a.year < b.year)
		|| ((a.year == b.year) && ((a.month < b.month)
			|| ((a.month == b.month) && ((a.day < b.day)
				|| ((a.day == b.day) && ((a.hour < b.hour)
					|| ((a.hour == b.hour) && ((a.minute < b.minute)
						|| (a.minute == b.minute && a.second <= b.second))))))))))
		return true;
	else
		return false;
}
std::istream& operator>> (std::istream& in, Date& input)
{
	in >> input.year;
	in >> input.month;
	in >> input.day;
	in >> input.hour;
	in >> input.minute;
	in >> input.second;
	return in;
}

std::ostream& operator<< (std::ostream& out, const Date& output)
{
	out << "Year: " << output.year << " month: " << output.month << " day: " << output.day
		<< " hour: " << output.hour << " minute: " << output.minute << " second: " << output.second << '\n';
	return out;
}

Date& Date::operator= (const Date& d)
{
	if (this == &d)
		return *this;
	year = d.year;
	month = d.month;
	day = d.day;
	hour = d.hour;
	minute = d.minute;
	second = d.second;

	return *this;
}
Date operator+ (const Date& d1, const Date& d2)
{
	Date ans;
	ans = d1;
	if (!ans.isCorrectDate())
		std::cout << "Left operand is not correct date\n";
	ans.second += d2.second;

	ans.minute += (d2.minute + ans.second/60);
	ans.second %= 60;

	ans.hour += (d2.hour + ans.minute/60);
	ans.minute %= 60;
	
	ans.day += (d2.day + ans.hour / 24);
	ans.hour %= 24;

	int pmonth = ans.day / ans.getDaysInMonth();
	ans.day %= ans.getDaysInMonth();
	ans.month += (d2.month + pmonth);

	ans.year += (d2.year + ans.month / 12);
	ans.month %= 12;
	return ans;
}
Date operator- (const Date& d1, const Date& d2)
{
	Date ans;
	ans = d1;
	if (d1 < d2)
	{
		std::cout << "Incorrect input. Left operand less than right, result of operarion will be left operand\n";
		return d1;
	}

	if (!ans.isCorrectDate())
		std::cout << "Left operand is not correct date\n";
	//seconds
	ans.second -= d2.second;
	int buf = 0;
	while (ans.second < 0)
	{
		ans.second += 60;
		buf++;
	}
	//minutes
	ans.minute -= (d2.minute + buf);

	buf = 0;
	while (ans.minute < 0)
	{
		ans.minute += 60;
		buf++;
	}
	//hours
	ans.hour -= (d2.hour + buf);

	int bufday = 0;
	while (ans.hour < 0)
	{
		ans.hour += 24;
		bufday++;
	}
	//mb months?
	ans.month -= (d2.month);
	int bufYear = 0;
	while (ans.month <= 0)
	{
		ans.month += 12;
		bufYear++;
	}


	//days
	ans.day -= (d2.day + bufday);


	buf = 0;
	while (ans.day <= 0)
	{
		ans.month--;
		if (ans.month <= 0)
		{
			ans.month += 12;
			bufYear++;
		}
		ans.day += ans.getDaysInMonth();
	}

	

	

	ans.year -= (d2.year + bufYear);

	
	return ans;
}