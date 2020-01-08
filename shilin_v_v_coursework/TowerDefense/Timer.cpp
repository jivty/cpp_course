#include "Timer.h"

Timer::Timer() {
  m_StartTime = {};
	m_bRunning = false;
	m_EndTime = {};
	lastTick = -1;
}

void Timer::start() {
	this->m_StartTime = std::chrono::system_clock::now();
	this->m_bRunning = true;
	this->starts.push_back(m_StartTime);
}

void Timer::stop() {
	this->m_EndTime = std::chrono::system_clock::now();
	this->m_bRunning = false;
	this->ends.push_back(m_EndTime);
}

double Timer::elapsedMilliseconds() {
	double elapsed = 0;
	std::chrono::time_point<std::chrono::system_clock> endTime;
	if (this->m_bRunning) {
		endTime = std::chrono::system_clock::now();
		elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(
				endTime - this->m_StartTime).count();
	}

	for (int i = 0, end_size = ends.size(); i < end_size; i++) {
		elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(
				this->ends[i] - this->starts[i]).count();
	}
	return elapsed;
}

double Timer::elapsedSeconds() {
	return elapsedMilliseconds() / 1000.0;
}

double Timer::elapsedTicks() {
	return floor(elapsedMilliseconds() / 10);
}

bool Timer::isRunning() {
	return this->m_bRunning;
}

bool Timer::newTick(){
	if(elapsedTicks() > lastTick){
		this->lastTick = elapsedTicks();
		return true;
	}
	return false;
}

bool Timer::saveData(const std::string path) {
  bool success(false);
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  if (fout.is_open()
    && fout.write((char*)& m_StartTime, sizeof(m_StartTime))
    && fout.write((char*)& m_EndTime, sizeof(m_EndTime))
    && fout.write((char*)& starts, sizeof(starts))
    && fout.write((char*)& ends, sizeof(ends))
    && fout.write((char*)& lastTick, sizeof(lastTick))) {
    success = true;
  }
  fout.close();
  return success;
}

bool Timer::loadData(const std::string path) {
  bool success(false);
  std::ifstream fin;
  fin.open(path, std::ofstream::binary | std::ofstream::in);
  if (fin.is_open()
    && fin.read((char*)& m_StartTime, sizeof(m_StartTime))
    && fin.read((char*)& m_EndTime, sizeof(m_EndTime))
    && fin.read((char*)& starts, sizeof(starts))
    && fin.read((char*)& ends, sizeof(ends))
    && fin.read((char*)& lastTick, sizeof(lastTick))) {
    success = true;
  }
  fin.close();
  if (!success) {
    std::cerr << "loading timer data failed" << std::endl;
  }
  return success;
}

void Timer::setDefault() {
  m_StartTime = {};
  m_bRunning = false;
  m_EndTime = {};
  lastTick = -1;
  starts.clear();
  ends.clear();
}
