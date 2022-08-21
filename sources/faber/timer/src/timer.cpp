#include <windows.h>
#include <faber/timer/timer.h>

namespace fbr
{
	Timer::Timer()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
		QueryPerformanceCounter((LARGE_INTEGER*)&m_base);
	}

	Timer::TTicks Timer::GetNow()
	{
		Timer::TTicks ret = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&ret);
		return ret;
	}

	double Timer::ToSeconds(TTicks time)
	{
		return (double)(time - m_base) / (double)m_freq;
	}

	double Timer::ToSecondsIntv(TTicks time)
	{
		return (double)(time) / (double)m_freq;
	}

	Timer Timer::st_instance;
}