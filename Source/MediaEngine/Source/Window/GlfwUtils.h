#pragma once
#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"
#include "MediaEngine/Include/Event/KeyCodes.h"
#include "MediaEngine/Include/Event/MouseCodes.h"

namespace ME
{
namespace Utils
{
KeyCode ConvertGLFWKeycodeToMEKeycode(int keycode);
MouseCode ConvertGLFWMouseButtonToMEMouseCode(int button);
int ConvertMEKeycodeToGLFWKeycode(KeyCode keycode);
int ConvertMEMouseCodeGLFWMouseButton(MouseCode button);

}  //namespace Utils
}  //namespace ME