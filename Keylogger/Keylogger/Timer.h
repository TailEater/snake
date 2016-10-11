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

	void SleepAndRun();
	void ThreadFunc();
public:
	static const long Infinite = -1L;
	Timer() {};
	Timer(const std::function<void(void)>& f);
	Timer(const std::function<void(void)>& f,
		const unsigned long& i,
		const long repeat = Timer::Infinite);
	void Start(bool asynch = true);
	void Stop();
	void SetFunction(const std::function<void(void)>& f);
	bool IsAlive() const;
	void RepeatCount(const long r);
	long GetLeftCount() const;
	long RepeatCount() const;
	void SetInterval(const unsigned long& i);
	auto Interval() const;
	const std::function<void(void)>& Function() const;
};