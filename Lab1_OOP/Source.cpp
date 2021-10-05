#include "PriorityQueue.h"   
#include "Date.h"
#include <queue>
void custonTest();
void autoTest();
int main()
{
	autoTest();
	//customTest();
	return 0;
}

void customTest()
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
	while (!B.empty())
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
		switch (dayOfWeek)
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


void autoTest()
{
	srand(time(NULL));
	//PriorityQueue
	{
		//test 1
		{
			priority_queue<int> testQ1;
			PriorityQueue<int> myQ1;
			for (int i = 0; i < 10; ++i)
			{
				int buf = rand() % 100 - 50;
				testQ1.push(buf);
				myQ1.push(buf);
			}
			while (!testQ1.empty())
			{
				if (testQ1.top() != myQ1.top())
				{
					std::cout << "PriorityQueue Test1 Failed\n";
					break;
				}
				testQ1.pop();
				myQ1.pop();
			}
		}

		//test 2
		{
			priority_queue<std::string> testQ1;
			PriorityQueue<std::string> myQ1;
			std::string buff;
			for (int i = 0; i < 10; ++i)
			{
				char bb = char(i + 48);
				buff = bb + bb;

				testQ1.push(buff);
				myQ1.push(buff);
			}
			while (!testQ1.empty())
			{
				if (testQ1.top() != myQ1.top())
				{
					std::cout << "PriorityQueue Test2 Failed\n";
					break;
				}
				testQ1.pop();
				myQ1.pop();
			}
		}

		//test 3
		{
			priority_queue<Date> testQ1;
			PriorityQueue<Date> myQ1;
			for (int i = 0; i < 10; ++i)
			{
				Date buff(rand() % 1000, rand() % 20, rand() % 30, rand() % 100, rand() % 100, rand() % 100);

				testQ1.push(buff);
				myQ1.push(buff);
			}
			while (!testQ1.empty())
			{
				if (!(testQ1.top() == myQ1.top()))
				{
					std::cout << "PriorityQueue Test3 Failed\n";
					break;
				}
				testQ1.pop();
				myQ1.pop();
			}
		}
	}
	
	//Date
	{
		//test 1
		{
			Date a(2021, 10, 5, 0, 0, 0), b(2021,1,1,0,0,0);
			if(a.getWeekInYear() != 40)
			{
				std::cout << "Date Test1 Failed\n";
			}
			if (b.getWeekInYear() != 53)
			{
				std::cout << "Date Test1 Failed\n";
			}
		}
		//test 2
		{
			Date a(2021, 10, 5, 0, 0, 0), b(2020, 12, 31, 0, 0, 0);
			if (a.getWeekInMonth() != 2)
			{
				std::cout << "Date Test2 Failed\n";
			}
			if (b.getWeekInMonth() != 5)
			{
				std::cout << "Date Test2 Failed\n";
			}
		}
		//test 3
		{
			Date a(2021, 10, 5, 0, 0, 0), b(2020, 12, 32, 0, 0, 0), c(2020,2,29,0,0,0),d(2020,2,28,24,13,3),e(2020,2,2,12,61,61);
			if (!a.isCorrectDate())
			{
				std::cout << "Date Test3 Failed\n";
			}
			if (b.isCorrectDate())
			{
				std::cout << "Date Test3 Failed\n";
			}
			if (!c.isCorrectDate())
			{
				std::cout << "Date Test3 Failed\n";
			}
			if (d.isCorrectDate())
			{
				std::cout << "Date Test3 Failed\n";
			}
			if (e.isCorrectDate())
			{
				std::cout << "Date Test3 Failed\n";
			}

		}
		//test 4
		{
			Date a(2021, 10, 5, 0, 0, 0), c(2020, 2, 29, 0, 0, 0), d(2020, 2, 28, 23, 13, 3);
			if (a.getDayOfWeek() != 1)//Thuesday
			{
				std::cout << "Date Test4 Failed\n";
			}
			if (c.getDayOfWeek() != 5)//Saturday
			{
				std::cout << "Date Test4 Failed\n";
			}
			if (d.getDayOfWeek() != 4)//Friday
			{
				std::cout << "Date Test4 Failed\n";
			}
		}
		//test 5
		{
			Date a(2021, 10, 5, 12, 30, 15), c(2020, 2, 29, 22, 59, 15);
			const Date d(1, 7, 5, 13, 31, 0);
			a = a - c;
			if (!(d == a))
			{
				std::cout << "Date test5 failed\n";
			}
		}
		//test 6
		{
			Date a(2021, 10, 5, 12, 30, 15), c(2020, 2, 29, 22, 59, 15);
			Date d(1, 7, 4, 13, 31, 0);
			c = c + d;
			if (!(c == a))
			{
				std::cout << "Date test6 failed\n";
			}
		}
	}
	std::cout << "Testing was successful";
}