#include "GlfwUtils.h"

namespace ME
{
namespace Utils
{
KeyCode ConvertGLFWKeycodeToHazelKeycode(int keycode)
{
    KeyCode res = KeyCode::Unknow;

    switch (keycode)
    {
        case GLFW_KEY_SPACE:
            res = KeyCode::Space;
            break;
        case GLFW_KEY_APOSTROPHE:
            res = KeyCode::Apostrophe;
            break;
        case GLFW_KEY_COMMA:
            res = KeyCode::Comma;
            break;
        case GLFW_KEY_MINUS:
            res = KeyCode::Minus;
            break;
        case GLFW_KEY_PERIOD:
            res = KeyCode::Period;
            break;
        case GLFW_KEY_SLASH:
            res = KeyCode::Slash;
            break;
        case GLFW_KEY_0:
            res = KeyCode::D0;
            break;
        case GLFW_KEY_1:
            res = KeyCode::D1;
            break;
        case GLFW_KEY_2:
            res = KeyCode::D2;
            break;
        case GLFW_KEY_3:
            res = KeyCode::D3;
            break;
        case GLFW_KEY_4:
            res = KeyCode::D4;
            break;
        case GLFW_KEY_5:
            res = KeyCode::D5;
            break;
        case GLFW_KEY_6:
            res = KeyCode::D6;
            break;
        case GLFW_KEY_7:
            res = KeyCode::D7;
            break;
        case GLFW_KEY_8:
            res = KeyCode::D8;
            break;
        case GLFW_KEY_9:
            res = KeyCode::D9;
            break;
        case GLFW_KEY_SEMICOLON:
            res = KeyCode::Semicolon;
            break;
        case GLFW_KEY_EQUAL:
            res = KeyCode::Equal;
            break;
        case GLFW_KEY_A:
            res = KeyCode::A;
            break;
        case GLFW_KEY_B:
            res = KeyCode::B;
            break;
        case GLFW_KEY_C:
            res = KeyCode::C;
            break;
        case GLFW_KEY_D:
            res = KeyCode::D;
            break;
        case GLFW_KEY_E:
            res = KeyCode::E;
            break;
        case GLFW_KEY_F:
            res = KeyCode::G;
            break;
        case GLFW_KEY_G:
            res = KeyCode::G;
            break;
        case GLFW_KEY_H:
            res = KeyCode::H;
            break;
        case GLFW_KEY_I:
            res = KeyCode::I;
            break;
        case GLFW_KEY_J:
            res = KeyCode::J;
            break;
        case GLFW_KEY_K:
            res = KeyCode::K;
            break;
        case GLFW_KEY_L:
            res = KeyCode::L;
            break;
        case GLFW_KEY_M:
            res = KeyCode::M;
            break;
        case GLFW_KEY_N:
            res = KeyCode::N;
            break;
        case GLFW_KEY_O:
            res = KeyCode::O;
            break;
        case GLFW_KEY_P:
            res = KeyCode::P;
            break;
        case GLFW_KEY_Q:
            res = KeyCode::Q;
            break;
        case GLFW_KEY_R:
            res = KeyCode::R;
            break;
        case GLFW_KEY_S:
            res = KeyCode::S;
            break;
        case GLFW_KEY_T:
            res = KeyCode::T;
            break;
        case GLFW_KEY_U:
            res = KeyCode::U;
            break;
        case GLFW_KEY_V:
            res = KeyCode::V;
            break;
        case GLFW_KEY_W:
            res = KeyCode::W;
            break;
        case GLFW_KEY_X:
            res = KeyCode::X;
            break;
        case GLFW_KEY_Y:
            res = KeyCode::Y;
            break;
        case GLFW_KEY_Z:
            res = KeyCode::Z;
            break;
        case GLFW_KEY_LEFT_BRACKET:
            res = KeyCode::LeftBracket;
            break;
        case GLFW_KEY_BACKSLASH:
            res = KeyCode::Backslash;
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            res = KeyCode::RightBracket;
            break;
        case GLFW_KEY_GRAVE_ACCENT:
            res = KeyCode::GraveAccent;
            break;
        case GLFW_KEY_WORLD_1:
            res = KeyCode::World1;
            break;
        case GLFW_KEY_WORLD_2:
            res = KeyCode::World2;
            break;
        case GLFW_KEY_ESCAPE:
            res = KeyCode::Escape;
            break;
        case GLFW_KEY_ENTER:
            res = KeyCode::Enter;
            break;
        case GLFW_KEY_TAB:
            res = KeyCode::Tab;
            break;
        case GLFW_KEY_BACKSPACE:
            res = KeyCode::Backspace;
            break;
        case GLFW_KEY_INSERT:
            res = KeyCode::Insert;
            break;
        case GLFW_KEY_DELETE:
            res = KeyCode::Delete;
            break;
        case GLFW_KEY_RIGHT:
            res = KeyCode::Right;
            break;
        case GLFW_KEY_LEFT:
            res = KeyCode::Left;
            break;
        case GLFW_KEY_DOWN:
            res = KeyCode::Down;
            break;
        case GLFW_KEY_UP:
            res = KeyCode::Up;
            break;
        case GLFW_KEY_PAGE_UP:
            res = KeyCode::PageUp;
            break;
        case GLFW_KEY_PAGE_DOWN:
            res = KeyCode::PageDown;
            break;
        case GLFW_KEY_HOME:
            res = KeyCode::Home;
            break;
        case GLFW_KEY_END:
            res = KeyCode::End;
            break;
        case GLFW_KEY_CAPS_LOCK:
            res = KeyCode::CapsLock;
            break;
        case GLFW_KEY_SCROLL_LOCK:
            res = KeyCode::ScrollLock;
            break;
        case GLFW_KEY_NUM_LOCK:
            res = KeyCode::NumLock;
            break;
        case GLFW_KEY_PRINT_SCREEN:
            res = KeyCode::PrintScreen;
            break;
        case GLFW_KEY_PAUSE:
            res = KeyCode::Pause;
            break;
        case GLFW_KEY_F1:
            res = KeyCode::F1;
            break;
        case GLFW_KEY_F2:
            res = KeyCode::F2;
            break;
        case GLFW_KEY_F3:
            res = KeyCode::F3;
            break;
        case GLFW_KEY_F4:
            res = KeyCode::F4;
            break;
        case GLFW_KEY_F5:
            res = KeyCode::F5;
            break;
        case GLFW_KEY_F6:
            res = KeyCode::F6;
            break;
        case GLFW_KEY_F7:
            res = KeyCode::F7;
            break;
        case GLFW_KEY_F8:
            res = KeyCode::F8;
            break;
        case GLFW_KEY_F9:
            res = KeyCode::F9;
            break;
        case GLFW_KEY_F10:
            res = KeyCode::F10;
            break;
        case GLFW_KEY_F11:
            res = KeyCode::F11;
            break;
        case GLFW_KEY_F12:
            res = KeyCode::F12;
            break;
        case GLFW_KEY_F13:
            res = KeyCode::F13;
            break;
        case GLFW_KEY_F14:
            res = KeyCode::F14;
            break;
        case GLFW_KEY_F15:
            res = KeyCode::F15;
            break;
        case GLFW_KEY_F16:
            res = KeyCode::F16;
            break;
        case GLFW_KEY_F17:
            res = KeyCode::F17;
            break;
        case GLFW_KEY_F18:
            res = KeyCode::F18;
            break;
        case GLFW_KEY_F19:
            res = KeyCode::F19;
            break;
        case GLFW_KEY_F20:
            res = KeyCode::F20;
            break;
        case GLFW_KEY_F21:
            res = KeyCode::F21;
            break;
        case GLFW_KEY_F22:
            res = KeyCode::F22;
            break;
        case GLFW_KEY_F23:
            res = KeyCode::F23;
            break;
        case GLFW_KEY_F24:
            res = KeyCode::F24;
            break;
        case GLFW_KEY_F25:
            res = KeyCode::F25;
            break;
        case GLFW_KEY_KP_0:
            res = KeyCode::KP0;
            break;
        case GLFW_KEY_KP_1:
            res = KeyCode::KP1;
            break;
        case GLFW_KEY_KP_2:
            res = KeyCode::KP2;
            break;
        case GLFW_KEY_KP_3:
            res = KeyCode::KP3;
            break;
        case GLFW_KEY_KP_4:
            res = KeyCode::KP4;
            break;
        case GLFW_KEY_KP_5:
            res = KeyCode::KP5;
            break;
        case GLFW_KEY_KP_6:
            res = KeyCode::KP6;
            break;
        case GLFW_KEY_KP_7:
            res = KeyCode::KP7;
            break;
        case GLFW_KEY_KP_8:
            res = KeyCode::KP8;
            break;
        case GLFW_KEY_KP_9:
            res = KeyCode::KP9;
            break;
        case GLFW_KEY_KP_DECIMAL:
            res = KeyCode::KPDecimal;
            break;
        case GLFW_KEY_KP_DIVIDE:
            res = KeyCode::KPDivide;
            break;
        case GLFW_KEY_KP_MULTIPLY:
            res = KeyCode::KPMultiply;
            break;
        case GLFW_KEY_KP_SUBTRACT:
            res = KeyCode::KPSubtract;
            break;
        case GLFW_KEY_KP_ADD:
            res = KeyCode::KPAdd;
            break;
        case GLFW_KEY_KP_ENTER:
            res = KeyCode::KPEnter;
            break;
        case GLFW_KEY_KP_EQUAL:
            res = KeyCode::KPEqual;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            res = KeyCode::LeftShift;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            res = KeyCode::LeftControl;
            break;
        case GLFW_KEY_LEFT_ALT:
            res = KeyCode::LeftAlt;
            break;
        case GLFW_KEY_LEFT_SUPER:
            res = KeyCode::LeftSuper;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            res = KeyCode::RightShift;
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            res = KeyCode::RightControl;
            break;
        case GLFW_KEY_RIGHT_ALT:
            res = KeyCode::RightAlt;
            break;
        case GLFW_KEY_RIGHT_SUPER:
            res = KeyCode::RightSuper;
            break;
        case GLFW_KEY_MENU:
            res = KeyCode::Menu;
            break;
        default:
            res = KeyCode::Unknow;
            break;
    }

    return res;
}

MouseCode ConvertGLFWMouseButtonToHazelMouseCode(int button)
{
    MouseCode res = MouseCode::Unkown;

    switch (button)
    {
        case GLFW_MOUSE_BUTTON_1:
            res = MouseCode::Button0;
            break;
        case GLFW_MOUSE_BUTTON_2:
            res = MouseCode::Button1;
            break;
        case GLFW_MOUSE_BUTTON_3:
            res = MouseCode::Button2;
            break;
        case GLFW_MOUSE_BUTTON_4:
            res = MouseCode::Button3;
            break;
        case GLFW_MOUSE_BUTTON_5:
            res = MouseCode::Button4;
            break;
        case GLFW_MOUSE_BUTTON_6:
            res = MouseCode::Button5;
            break;
        case GLFW_MOUSE_BUTTON_7:
            res = MouseCode::Button6;
            break;
        case GLFW_MOUSE_BUTTON_8:
            res = MouseCode::Button7;
            break;
        default:
            break;
    }

    return res;
}
}  //namespace Utils
}  //namespace ME
