#pragma once

class HPTimer
{
	__int64  m_n64StartTime;
	__int64  m_n64LastUpdateTime;
	__int64  m_n64CurrentUpdateTime;
	__int64  m_n64Frequency;
public:
	HPTimer();
	
	void ResetFramestate();
	void UpdateFramestate();
	double GetTimeTotal();
	double GetTimeDelta();
};