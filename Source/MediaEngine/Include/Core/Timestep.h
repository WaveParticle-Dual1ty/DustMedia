#pragma once

namespace ME
{
class Timestep
{
public:
    Timestep() = default;

    Timestep(float timeInSec)
        : m_TimeInSec(timeInSec)
    {
    }

    float GetSeconds() const { return m_TimeInSec; }

    float GetMilliseconds() const { return m_TimeInSec * 1000; }

private:
    float m_TimeInSec = 0.f;
};
}  //namespace ME