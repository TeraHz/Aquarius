/*
 * g++ -Wall -std=c++11 SchedulerTesting.cpp -o SchedulerTesting -pthread
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <ctime>

// schedule something at a specific time. use makeTimePoint to define a chrono timepoint
template <typename Clock, typename Duration, typename F, typename D>
void run_at(std::chrono::time_point<Clock, Duration> const& when, F func, D data)
{
	if ( when < std::chrono::system_clock::now() ){
		printf("In the past. Ignornig\n");
	}else{
	  	std::async(std::launch::async, [=]{ std::this_thread::sleep_until(when), func(data);});
	}
}


// schedule something to run X amount of times every Y
template <typename Rep, typename Period, typename F, typename D>
void run_series(unsigned iterations, std::chrono::duration<Rep, Period> const& how_often, F func, D data)
{
	std::thread([=]() mutable {
		while (iterations--) {
			// flip the next two lines to make the first execution right away
			std::this_thread::sleep_for(how_often);
			func(data);
		 }
	 }).detach();
}

// some test function that prints a string
void test(char * data){
  printf("%s\n", data);
}

std::chrono::system_clock::time_point
makeTimePoint (int year, int mon, int day,
		int hour, int min, int sec=0)
{
	struct std::tm t;
	t.tm_sec = sec;        // second of minute (0 .. 59 and 60 for leap seconds)
	t.tm_min = min;        // minute of hour (0 .. 59)
	t.tm_hour = hour;      // hour of day (0 .. 23)
	t.tm_mday = day;       // day of month (0 .. 31)
	t.tm_mon = mon-1;      // month of year (0 .. 11)
	t.tm_year = year-1900; // year since 1900
	t.tm_isdst = -1;       // determine whether daylight saving time
	std::time_t tt = std::mktime(&t);
	if (tt == -1) {
		throw "no valid system time";
	}
	return std::chrono::system_clock::from_time_t(tt);
}

int main()
{
	std::chrono::seconds dura1(1); // one second
	std::chrono::seconds dura2(5); // five seconds
	char text1[] = "Every second";
	char text2[] = "Every 5 seconds";
	char text3[] = "September 17th, 2013 00:27:00";
	auto when = makeTimePoint(2013, 9, 17, 0, 27, 0); 
	
	run_series(5,dura1, test, text1); // run test(text1) five times every second
	run_series(2,dura2, test, text2); // run test(text2) two times every 5 seconds


	run_at(when, test, text3); // run test(text3) at the given time above

	std::this_thread::sleep_for(std::chrono::minutes(10)); // wait for things
}
