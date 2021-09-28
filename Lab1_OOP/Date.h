#pragma once

#include <iostream>


const int dayInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

class Date
{
	int year, month, day, hour, minute, second;

	bool isLeapYear();
	int getDaysInMonth();
public:
	Date();
	Date(int, int, int , int , int , int );
	bool isCorrectDate();
	int getDayOfWeek();//0 - monday,..., 6 - sunday
	int getWeekInMonth();
	int getWeekInYear();
	Date& operator= (const Date& d);
	friend Date operator+ (const Date&, const Date&);
	friend Date operator- (const Date&, const Date&);
	friend bool operator< (const Date& a, const Date& b);
	friend bool operator== (const Date& a, const Date& b);
	friend bool operator<= (const Date& a, const Date& b);
	friend std::istream& operator>> (std::istream& in, Date& input);
	friend std::ostream& operator<< (std::ostream& out, const Date& output);
};

