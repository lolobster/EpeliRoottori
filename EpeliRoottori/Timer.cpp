#include "Timer.h"

Timer::Timer()
{
	startTime = 0.0f;
	stopTime = 0.0f;
	pauseTime = 0.0f;
	localTime = 0.0f;

	started = false;
	paused = false;
}

Timer::~Timer()
{

}

GLfloat Timer::GetGlobalTime()
{
	return static_cast<GLfloat>(glfwGetTime());
}

void Timer::SetTimer()
{
	glfwSetTime(0.0);
}

GLfloat Timer::GetLocalTime()
{
	localTime = 0.0f;
	if (started)
	{
		if (paused)
		{
			localTime = pauseTime;
		}
		else
		{
			localTime = GetGlobalTime() - startTime;
		}
	}
	return localTime;
}

GLfloat Timer::Start()
{
	started = true;
	paused = false;

	startTime = GetGlobalTime();
	pauseTime = 0.0f;
	return startTime;
}

GLfloat Timer::Stop()
{
	started = false;
	paused = false;

	stopTime = GetGlobalTime();

	startTime = 0.0f;
	pauseTime = 0.0f;
	return stopTime;
}

GLfloat Timer::Pause()
{
	if (started && paused) // Jatka
	{
		paused = false;
		startTime = GetGlobalTime() - pauseTime;
		pauseTime = 0.0f;
		return startTime;
	}
	else if (started == true && paused == false) // Pysäytä
	{
		paused = true;

		pauseTime = GetGlobalTime() - startTime;
		return pauseTime;
	}
	else
	{
		return pauseTime;
	}
}

bool Timer::IsStarted()
{
	return started;
}

bool Timer::IsPaused()
{
	return paused && started;
}