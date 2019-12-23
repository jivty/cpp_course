#ifndef TD_TIMER_H
#define TD_TIMER_H
#include <chrono>
#include <vector>

class Timer {
public:
	Timer();
	void start();
	void stop();
	double elapsedMilliseconds();
	double elapsedSeconds();
	double elapsedTicks();
	bool isRunning();
	bool newTick();

private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::time_point<std::chrono::system_clock> m_EndTime;
	bool m_bRunning;
	std::vector<std::chrono::time_point<std::chrono::system_clock>> starts;
	std::vector<std::chrono::time_point<std::chrono::system_clock>> ends;
	double lastTick;
};

#endif
