#include <iostream>
#include <iomanip>


class Time {
	int sec_ = 0;
public:
	enum {
		MINUTE = 60,
		HOUR = 60 * MINUTE,
		DAY = 24 * HOUR
	};
	Time() {}
	explicit Time(int sec) :
		sec_(sec)
	{
	}
	Time(short mins) :
		sec_(mins * MINUTE)
	{
	}
	Time(int mins, int secs) :
		sec_(mins * MINUTE + secs)
	{
	}
	Time(int hours, short mins) :
		sec_(hours * HOUR + mins * MINUTE)
	{
	}
	Time(int hours, int mins, int secs) :
		sec_(hours * HOUR + mins * MINUTE + secs)
	{
	}
	Time(const Time & time) :
		sec_(time.sec_)
	{
	}
	Time(Time&& time) :
		sec_(std::move(time.sec_))
	{
		time.sec_ = 0;
	}
	~Time() {}
	
	int getOnlySec() const {
		return sec_ % MINUTE;
	}
	int getAllSec() const {
		return sec_;
	}
	int getOnlyMin() const {
		return sec_ % HOUR / MINUTE;
	}
	int getAllMin() const {
		return sec_ / MINUTE;
	}
	int getHour() const {
		return sec_ / HOUR;
	}
	void setSec(const int sec) {
		sec_ = sec;
	}
	void setSecFromMin(const int min) {
		sec_ = min * MINUTE;
	}
	void setSecFromHour(const int hour) {
		sec_ = hour * HOUR;
	}

	Time& operator=(const Time& time) {
		sec_ = time.sec_;
		return *this;
	}
	Time& operator=(Time&& time) {
		sec_ = std::move(time.sec_);
		return *this;
		std::cout << "operator =" << std::endl;
	}

	Time operator-();
	Time operator+(const Time& t);
	Time operator+(const int& t);
	Time operator-(const Time& t);
	Time operator-(const int& t);
	Time& operator+=(const Time& t);
	Time& operator+=(const int& t);
	Time& operator-=(const Time& t);
	Time& operator-=(const int& t);
	Time& operator++();
	Time& operator--();
	Time operator++(int);
	Time operator--(int);
};

Time Time::operator-() {
	Time tmp;
	tmp.sec_ = -sec_;
	return tmp;
}
Time Time::operator+(const Time& t) {
	Time tmp;
	tmp.sec_ = sec_ + t.sec_;
	return tmp;
}
Time Time::operator+(const int& t) {
	Time tmp;
	tmp.sec_ = sec_ + t;
	return tmp;
}
Time Time::operator-(const Time& t) {
	Time tmp;
	tmp.sec_ = sec_ - t.sec_;
	return tmp;
}
Time Time::operator-(const int& t) {
	Time tmp;
	tmp.sec_ = sec_ - t;
	return tmp;
}
Time& Time::operator+=(const Time& t) {
	sec_ = sec_ + t.sec_;
	return *this;
}
Time& Time::operator+=(const int& t) {
	sec_ = sec_ + t;
	return *this;
}
Time& Time::operator-=(const Time& t) {
	sec_ = sec_ - t.sec_;
	return *this;
}
Time& Time::operator-=(const int& t) {
	sec_ = sec_ - t;
	return *this;
}
Time& Time::operator++() {
	++sec_;
	return *this;
}
Time Time::operator++(int) {
	Time tmp = *this; // Time tmp(*this);
					  // Time tmp(this->sec_);
	++sec_;
	return tmp;
}
Time& Time::operator--() {
	--sec_;
	return *this;
}
Time Time::operator--(int) {
	Time tmp = *this;
	--sec_;
	return tmp;
}

std::ostream& operator<<(std::ostream& os, const Time& obj)
{
	bool am = obj.getHour() < 12 ? true : false;
	os << std::setw(2) << std::setfill('0') 
		<< ((obj.getHour() % 12 == 0) ? 12 : obj.getHour() % 12) << ':'
		<< std::setw(2) << std::setfill('0') << obj.getOnlyMin() << ' '
		<< ((am == true) ? "AM" : "PM");
	return os;
}

std::istream& operator >> (std::istream& is, Time& obj)
{
	int newHour;
	is >> newHour;
	int newMin;
	is >> newMin;
	int newSec;
	is >> newSec;
	if (newHour >= 0 && newHour <= 23 && newMin >= 0 && newMin <= 59 && newSec >= 0 && newSec <= 59) {
		obj.setSec(newHour * Time::HOUR + newMin * Time::MINUTE + newSec);
	}
	else {
		std::cout << "Error time's data" << std::endl;
	}
	return is;
}


void printResTestForConstructors(const Time& t, const int value) {
	if (t.getAllSec() == value) {
		std::cout << "\tOK" << std::endl;
	}
	else { std::cout << "\tError" << std::endl; }
}


void printResTestForOverloadedOperators(Time t, const int res) {
	if (t.getAllSec() == res) {
		std::cout << "\tOK" << std::endl;
	}
	else { std::cout << "\tError" << std::endl; }
}


void printTestStreamExtraction(Time t) {
	std::cout << std::setw(2) << std::setfill('0') << t.getHour() << '.' 
		<< std::setw(2) << std::setfill('0') << t.getOnlyMin() << '.'
		<< std::setw(2) << std::setfill('0') << t.getOnlySec() << "\t->\t" << t << std::endl;
}


int main() {
	
	std::cout << "Test for constructors: " << std::endl;
	Time t1;
	printResTestForConstructors(t1, 0);
	Time t2(10);
	printResTestForConstructors(t2, 10);
	Time t3(10, 10);
	printResTestForConstructors(t3, 610);
	Time t4(2, 20, 20);
	printResTestForConstructors(t4, 8420);
	Time t5 = t4;
	printResTestForConstructors(t5, 8420);
	Time t6 = std::move(t5);
	printResTestForConstructors(t6, 8420);
	printResTestForConstructors(t5, 0);
	short t = 12;
	Time t06(t);
	printResTestForConstructors(t06, 720);
	std::cout << std::endl;
	
	std::cout << "Test for overloaded operators: " << std::endl;
	const int x = 10;
	const int y = 5;
	Time t7(x);
	Time t8(y);
	printResTestForOverloadedOperators(-t7, -x);
	printResTestForOverloadedOperators(t7 + t8, x + y);
	printResTestForOverloadedOperators(t7 - t8, x - y);
	printResTestForOverloadedOperators(t8 - t7, y - x);
	int a = x;
	int b = y;
	printResTestForOverloadedOperators(t7 += t8, a += b);
	printResTestForOverloadedOperators(t7 -= t8, a -= b);
	printResTestForOverloadedOperators(t8 -= t7, b -= a);
	printResTestForOverloadedOperators(t7 = t8, a = b);
	std::cout << std::endl;
	
	std::cout << "Test for overloaded operators \n (increment and decrement): " << std::endl;
	int k = 10;
	Time t9(k);
	printResTestForOverloadedOperators(++t9, ++k);
	printResTestForOverloadedOperators((++(++(++t9))), (++(++(++k))));
	printResTestForOverloadedOperators(--t9, --k);
	printResTestForOverloadedOperators((--(--(--t9))), (--(--(--k))));
	
	k = 4;
	Time t0(k);
	printResTestForOverloadedOperators(t0++, k++);
	printResTestForOverloadedOperators(t0--, k--);
	std::cout << std::endl;
	
	std::cout << "Test for stream extraction: " << std::endl;
	Time time0(0, 20, 20);
	printTestStreamExtraction(time0);
	Time time1(8430);
	printTestStreamExtraction(time1);
	Time time2(11, 59, 20);
	printTestStreamExtraction(time2);
	Time time3(14, 32, 20);
	printTestStreamExtraction(time3);
	Time time4(23, 40, 20);
	printTestStreamExtraction(time4);
	std::cout << std::endl;

	std::cout << "Test for stream insertion: " << std::endl;
	Time time5;
	std::cin >> time5; 
	std::cout << time5 << std::endl;
	std::cout << std::endl;
	
	system("pause");
	return 0;
}