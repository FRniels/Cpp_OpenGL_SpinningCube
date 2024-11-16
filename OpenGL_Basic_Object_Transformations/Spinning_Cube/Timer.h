#ifndef TIMER_H
#define TIMER_H

#include "GLFW/glfw3.h"
#include "Window.h"

#define FPS_60_PERIOD 1.0 / 60.0 

struct Time_t
{
private:
	double previous_s = 0.0;
	double current_s  = 0.0;
	double delta_s    = 0.0;

public:
	void Init()
	{
		current_s = previous_s = glfwGetTime();
	}

	void Update() 
	{
		current_s  = glfwGetTime();
		delta_s    = current_s - previous_s;
		previous_s = current_s;
	}

	double GetDeltaTime() const { return delta_s; }
};


class Timer 
{
public:
	double  period_s    = 0.0;

private:
	const Time_t& window_time;
	double  time_to_run = 0.0;

public:
	Timer(const Time_t& window_time, double period_s) : window_time(window_time), period_s(period_s), time_to_run(period_s) { }
	
	bool IsTimerExpired() { return (GetTimeToRun() <= 0.0); }

	void Reset() { time_to_run = period_s; }

private:
	double GetTimeToRun()
	{
		time_to_run -= window_time.GetDeltaTime();
		return time_to_run;
	}
};


#endif // TIMER_H
