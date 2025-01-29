#pragma once

namespace ME
{
class Timestep
{
public:
    Timestep() = default;

    Timestep(double timeInSec)
        : m_TimeInSec(timeInSec)
    {
    }

    double GetSeconds() const { return m_TimeInSec; }

    double GetMilliseconds() const { return m_TimeInSec * 1000; }

private:
    double m_TimeInSec = 0.f;
};
}  //namespace ME