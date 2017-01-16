#include <Windows.h>

#include "HPTimer.h"


HPTimer::HPTimer()
{
	m_n64StartTime = 0;
	m_n64LastUpdateTime = 0;
	m_n64CurrentUpdateTime = 0;
	m_n64Frequency = 0;

	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	m_n64Frequency = t.QuadPart;

	ResetFramestate();
}

void HPTimer::ResetFramestate()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_n64StartTime = t.QuadPart;
	m_n64CurrentUpdateTime = t.QuadPart;
	m_n64LastUpdateTime = t.QuadPart;
}

void HPTimer::UpdateFramestate()
{
	m_n64LastUpdateTime = m_n64CurrentUpdateTime;
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_n64CurrentUpdateTime = t.QuadPart;
}

double HPTimer::GetTimeTotal()
{
	double d = (double)m_n64CurrentUpdateTime - (double)m_n64StartTime;
	return d / m_n64Frequency;
}

double HPTimer::GetTimeDelta()
{
	double d = (double)m_n64CurrentUpdateTime - (double)m_n64LastUpdateTime;
	return d / m_n64Frequency;
}