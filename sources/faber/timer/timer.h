#pragma once
namespace fbr
{
	class Timer
	{
	public:
		typedef unsigned __int64 TTicks;

		Timer();

		TTicks GetNow();
		double ToSeconds(TTicks time);
		double ToSecondsIntv(TTicks time);

		static inline Timer& GetInstance()
		{
			return st_instance;
		}

	private:
		TTicks		m_base;
		TTicks		m_freq;

		static Timer st_instance;
	};

	/// scoped timing block
	class ScopedTimer
	{
	public:
		inline ScopedTimer()
			: m_startTime(Timer::GetInstance().GetNow())
		{}

		inline double GetElaspedTime() const
		{
			const auto delta = (Timer::GetInstance().GetNow() - m_startTime);
			return Timer::GetInstance().ToSecondsIntv(delta);
		}

	private:
		Timer::TTicks		m_startTime;
	};
}