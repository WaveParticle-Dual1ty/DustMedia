#pragma once
#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"
#include "MediaEngine/Include/Event/KeyCodes.h"
#include "MediaEngine/Include/Event/MouseCodes.h"

namespace ME
{
namespace Utils
{
KeyCode ConvertGLFWKeycodeToHazelKeycode(int keycode);
MouseCode ConvertGLFWMouseButtonToHazelMouseCode(int button);
}  //namespace Utils
}  //namespace ME