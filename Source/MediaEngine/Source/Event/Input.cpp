#include "MediaEngine/Include/Event/Input.h"
#include "MediaEngine/Include/Application/Application.h"

namespace ME
{
bool Input::IsKeyPressed(KeyCode keycode)
{
    Window& wnd = Application::Get().GetWindow();
    return wnd.IsKeyPressed(keycode);
}

bool Input::IsMouseButtonPressed(MouseCode button)
{
    Window& wnd = Application::Get().GetWindow();
    return wnd.IsMouseButtonPressed(button);
}

float Input::GetMouseX()
{
    Window& wnd = Application::Get().GetWindow();
    return wnd.GetMouseX();
}

float Input::GetMouseY()
{
    Window& wnd = Application::Get().GetWindow();
    return wnd.GetMouseY();
}

}  //namespace ME