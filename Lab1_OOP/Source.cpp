#include "PriorityQueue.h"   
#include "Date.h"
int main()
{

	using std::cout;
	//PriorityQueue<int> A;
	//A.push(100);
	//for (int i = 0; i < 10; i++)
	//	A.push(i);
	//while (!A.empty())
	//{
	//	//A.print();
	//	cout << A.top()<<' ';
	//	A.pop();
	//}
	PriorityQueue<Date> B;
	Date d;
	for (int i = 0; i < 1; i++)
	{
		cin >> d;
		B.push(d);
	}
	d = B.top();
	
	//cout<<d.getDayOfWeek();
//	cout << d.getWeekInMonth();
	//cout << d.getWeekInYear();
	/*d = B.top(); B.pop();
	d = d - B.top();
	cout << d;*/
	//while (!B.empty())
	//	{
	//		//B.print();
	//		cout << B.top();
	//		B.pop();
	//	}
}


