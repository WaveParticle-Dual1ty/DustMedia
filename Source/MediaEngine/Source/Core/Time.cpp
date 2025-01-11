#pragma once
#include <string>
#include "MediaEngine/Include/Core/Time.h"
#include "ThirdParty/glfw/include/GLFW/glfw3.h"

namespace ME
{
double Time::GetCurrentTimeInSecond()
{
    double time = glfwGetTime();
    return time;
}

}  //namespace ME
