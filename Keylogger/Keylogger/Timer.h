#pragma once
#include <thread>
#include <chrono>

class Timer
{
private:
	std::thread t_thread;
	bool alive = false;
	long call_number = -1L;
	long repeat_count = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	std::function<void(void)> funct = nullptr;

	void SleepAndRun()
	{
		std::this_thread::sleep_for(interval);
		if (alive)
		{
			Function()();
		}
	}
	void ThreadFunc()
	{
		if (call_number == Infinite)
		{
			while (alive)
			{
				SleepAndRun();
			}
		}
		else
		{
			while (repeat_count--)
			{
				SleepAndRun();
			}
		}
	}
public:
	static const long Infinite = -1L;
	Timer() {};
	Timer(const std::function<void(void)>& f) : funct(f) {}
	Timer(const std::function<void(void)>& f,
		const unsigned long& i,
		const long repeat = Timer::Infinite)
		: funct(f), interval(std::chrono::milliseconds(i)), call_number(repeat)
	{}
	void Start(bool Asynch = true)
	{
		if (IsAlive())
		{
			return;
		}
		alive = true;
		repeat_count = call_number;
		if (Asynch)
		{
			t_thread = std::thread(&Timer::ThreadFunc, this);
		}
		else
		{
			this->ThreadFunc();
		}
	}
	void Stop()
	{
		alive = false;
		t_thread.join();
	}
	void SetFunction(const std::function<void(void)>& f)
	{
		funct = f;
	}
	bool IsAlive() const { return alive; }
	void RepeatCount(const long r)
	{
		if (alive)
			return;
		call_number = r;
	}
	long GetLeftCount() const { return repeat_count; }
	long RepeatCount() const { return call_number; }
	void SetInterval(const unsigned long& i)
	{
		if (alive)
			return;
		interval = std::chrono::milliseconds(i);
	}
	auto Interval() const { return interval.count(); }
	const std::function<void(void)>& Function() const
	{
		return funct;
	}
};