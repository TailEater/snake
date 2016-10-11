#include "Timer.h"
#include <thread>
#include <chrono>
using namespace std;

void Timer::SleepAndRun()
{
	this_thread::sleep_for(interval);
	if (alive)
		Function()();
}

void Timer::ThreadFunc()
{
	if (call_number == Infinite)
		while (alive)
			SleepAndRun();
	else
		while (repeat_count--)
			SleepAndRun();
}

Timer::Timer(const function<void(void)>& f) : funct(f) {}
Timer::Timer(
	const function<void(void)>& f,
	const unsigned long& i,
	const long repeat
) : funct(f), interval(chrono::milliseconds(i)), call_number(repeat) {}

void Timer::Start(bool asynch)
{
	if (IsAlive())
		return;
	alive = true;
	repeat_count = call_number;
	if (asynch)
		t_thread = thread(&Timer::ThreadFunc, this);
	else
		this->ThreadFunc();
}

void Timer::Stop()
{
	alive = false;
	t_thread.join();
}

void Timer::SetFunction(const function<void(void)>& f)
{
	funct = f;
}

bool Timer::IsAlive() const
{
	return alive;
}

void Timer::RepeatCount(const long r)
{
	if (alive)
		return;
	call_number = r;
}
long Timer::GetLeftCount() const { return repeat_count; }
long Timer::RepeatCount() const { return call_number; }
void Timer::SetInterval(const unsigned long& i)
{
	if (alive)
		return;
	interval = chrono::milliseconds(i);
}
auto Timer::Interval() const
{
	return interval.count();
}

const function<void(void)>& Timer::Function() const
{
	return funct;
}