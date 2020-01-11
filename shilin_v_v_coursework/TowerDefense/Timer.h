#ifndef TD_TIMER_H
#define TD_TIMER_H

#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//! \brief Таймер.
class Timer {
public:

  //! \brief Умолчательный конструктор.
	Timer();

  //! \brief Деструктор.
  ~Timer() = default;

  //! \brief Запускает таймер.
	void start();

  //! \brief Останавливает таймер.
	void stop();

  //! \brief Количество миллисекунд с момента начала игры.
	double elapsedMilliseconds();

  //! \brief Количество секунд с момента начала игры.
	double elapsedSeconds();

  //! \brief Количество тиков с момента начала игры.
	double elapsedTicks();

  //! \brief Возвращает true, если таймер запущен.
	bool isRunning();

  //! \brief Возвращает true, если был совершен еще один тик.
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
