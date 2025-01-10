#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace ME
{
class Input
{
public:
    static bool IsKeyPressed(KeyCode keycode);
    static bool IsMouseButtonPressed(MouseCode button);
    static float GetMouseX();
    static float GetMouseY();
};

}  //namespace ME