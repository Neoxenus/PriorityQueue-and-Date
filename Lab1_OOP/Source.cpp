#include "PriorityQueue.h"   
#include "Date.h"
int main()
{

	using std::cout;
	using std::cin;

	PriorityQueue<Date> B;
	Date d;
	cout << "Enter number of dates: ";
	int numberOfDates = 0;
	cin >> numberOfDates;
	for (int i = 0; i < numberOfDates; ++i)
	{
		cout << "Enter new date in format y/m/d/h/m/s: ";
		cin >> d;
		B.push(d);
	}
	cout << '\n';
	while(!B.empty())
	{
		d = B.top();
		cout << d;
		if (!d.isCorrectDate())
		{
			cout << "Incorrect date\n";
			B.pop();
			continue;
		}
		int dayOfWeek = d.getDayOfWeek();
		switch(dayOfWeek)
		{
		case 0:
			cout << "Monday\n";
			break;
		case 1:
			cout << "Thusday\n";
			break;
		case 2:
			cout << "Wednesday\n";
			break;
		case 3:
			cout << "Thursday\n";
			break;
		case 4:
			cout << "Friday\n";
			break;
		case 5:
			cout << "Saturday\n";
			break;
		case 6:
			cout << "Sunday\n";
			break;
		default:
			cout << "Incorrect input, can't find day of week\n";
			break;
		}
		cout << "Week in year: " << d.getWeekInYear() << '\n';
		cout << "Week in month: " << d.getWeekInMonth() << "\n\n";
		B.pop();
	}
	cout << "\nEnter 2 dates to sum and diff:\n";
	for (int i = 0; i < 2; ++i)
	{
		cout << "Enter new date in format y/m/d/h/m/s: ";
		cin >> d;
		B.push(d);
	}

	cout << '\n';
	Date sum, diff;
	sum = diff = B.top();
	B.pop();
	sum = sum + B.top();
	diff = diff - B.top();
	cout << "Sum: " << sum << "Diff: " << diff;
}


