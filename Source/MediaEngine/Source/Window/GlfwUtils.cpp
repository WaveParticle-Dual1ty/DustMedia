#include "GlfwUtils.h"

namespace ME
{
namespace Utils
{
KeyCode ConvertGLFWKeycodeToMEKeycode(int keycode)
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

MouseCode ConvertGLFWMouseButtonToMEMouseCode(int button)
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

int ConvertMEKeycodeToGLFWKeycode(KeyCode keycode)
{
    int res = -1;

    switch (keycode)
    {
        case KeyCode::Unknow:
            res = -1;
            break;
        case KeyCode::Space:
            res = GLFW_KEY_SPACE;
            break;
        case KeyCode::Apostrophe:
            res = GLFW_KEY_APOSTROPHE;
            break;
        case KeyCode::Comma:
            res = GLFW_KEY_COMMA;
            break;
        case KeyCode::Minus:
            res = GLFW_KEY_MINUS;
            break;
        case KeyCode::Period:
            res = GLFW_KEY_PERIOD;
            break;
        case KeyCode::Slash:
            res = GLFW_KEY_SLASH;
            break;
        case KeyCode::D0:
            res = GLFW_KEY_0;
            break;
        case KeyCode::D1:
            res = GLFW_KEY_1;
            break;
        case KeyCode::D2:
            res = GLFW_KEY_2;
            break;
        case KeyCode::D3:
            res = GLFW_KEY_3;
            break;
        case KeyCode::D4:
            res = GLFW_KEY_4;
            break;
        case KeyCode::D5:
            res = GLFW_KEY_5;
            break;
        case KeyCode::D6:
            res = GLFW_KEY_6;
            break;
        case KeyCode::D7:
            res = GLFW_KEY_7;
            break;
        case KeyCode::D8:
            res = GLFW_KEY_8;
            break;
        case KeyCode::D9:
            res = GLFW_KEY_9;
            break;
        case KeyCode::Semicolon:
            res = GLFW_KEY_SEMICOLON;
            break;
        case KeyCode::Equal:
            res = GLFW_KEY_EQUAL;
            break;
        case KeyCode::A:
            res = GLFW_KEY_A;
            break;
        case KeyCode::B:
            res = GLFW_KEY_B;
            break;
        case KeyCode::C:
            res = GLFW_KEY_C;
            break;
        case KeyCode::D:
            res = GLFW_KEY_D;
            break;
        case KeyCode::E:
            res = GLFW_KEY_E;
            break;
        case KeyCode::F:
            res = GLFW_KEY_F;
            break;
        case KeyCode::G:
            res = GLFW_KEY_G;
            break;
        case KeyCode::H:
            res = GLFW_KEY_H;
            break;
        case KeyCode::I:
            res = GLFW_KEY_I;
            break;
        case KeyCode::J:
            res = GLFW_KEY_J;
            break;
        case KeyCode::K:
            res = GLFW_KEY_K;
            break;
        case KeyCode::L:
            res = GLFW_KEY_L;
            break;
        case KeyCode::M:
            res = GLFW_KEY_M;
            break;
        case KeyCode::N:
            res = GLFW_KEY_N;
            break;
        case KeyCode::O:
            res = GLFW_KEY_O;
            break;
        case KeyCode::P:
            res = GLFW_KEY_P;
            break;
        case KeyCode::Q:
            res = GLFW_KEY_Q;
            break;
        case KeyCode::R:
            res = GLFW_KEY_R;
            break;
        case KeyCode::S:
            res = GLFW_KEY_S;
            break;
        case KeyCode::T:
            res = GLFW_KEY_T;
            break;
        case KeyCode::U:
            res = GLFW_KEY_U;
            break;
        case KeyCode::V:
            res = GLFW_KEY_V;
            break;
        case KeyCode::W:
            res = GLFW_KEY_W;
            break;
        case KeyCode::X:
            res = GLFW_KEY_X;
            break;
        case KeyCode::Y:
            res = GLFW_KEY_Y;
            break;
        case KeyCode::Z:
            res = GLFW_KEY_Z;
            break;
        case KeyCode::LeftBracket:
            res = GLFW_KEY_LEFT_BRACKET;
            break;
        case KeyCode::Backslash:
            res = GLFW_KEY_BACKSLASH;
            break;
        case KeyCode::RightBracket:
            res = GLFW_KEY_RIGHT_BRACKET;
            break;
        case KeyCode::GraveAccent:
            res = GLFW_KEY_GRAVE_ACCENT;
            break;
        case KeyCode::World1:
            res = GLFW_KEY_WORLD_1;
            break;
        case KeyCode::World2:
            res = GLFW_KEY_WORLD_2;
            break;
        case KeyCode::Escape:
            res = GLFW_KEY_ESCAPE;
            break;
        case KeyCode::Enter:
            res = GLFW_KEY_ENTER;
            break;
        case KeyCode::Tab:
            res = GLFW_KEY_TAB;
            break;
        case KeyCode::Backspace:
            res = GLFW_KEY_BACKSPACE;
            break;
        case KeyCode::Insert:
            res = GLFW_KEY_INSERT;
            break;
        case KeyCode::Delete:
            res = GLFW_KEY_DELETE;
            break;
        case KeyCode::Right:
            res = GLFW_KEY_RIGHT;
            break;
        case KeyCode::Left:
            res = GLFW_KEY_LEFT;
            break;
        case KeyCode::Down:
            res = GLFW_KEY_DOWN;
            break;
        case KeyCode::Up:
            res = GLFW_KEY_UP;
            break;
        case KeyCode::PageUp:
            res = GLFW_KEY_PAGE_UP;
            break;
        case KeyCode::PageDown:
            res = GLFW_KEY_PAGE_DOWN;
            break;
        case KeyCode::Home:
            res = GLFW_KEY_HOME;
            break;
        case KeyCode::End:
            res = GLFW_KEY_END;
            break;
        case KeyCode::CapsLock:
            res = GLFW_KEY_CAPS_LOCK;
            break;
        case KeyCode::ScrollLock:
            res = GLFW_KEY_SCROLL_LOCK;
            break;
        case KeyCode::NumLock:
            res = GLFW_KEY_NUM_LOCK;
            break;
        case KeyCode::PrintScreen:
            res = GLFW_KEY_PRINT_SCREEN;
            break;
        case KeyCode::Pause:
            res = GLFW_KEY_PAUSE;
            break;
        case KeyCode::F1:
            res = GLFW_KEY_F1;
            break;
        case KeyCode::F2:
            res = GLFW_KEY_F2;
            break;
        case KeyCode::F3:
            res = GLFW_KEY_F3;
            break;
        case KeyCode::F4:
            res = GLFW_KEY_F4;
            break;
        case KeyCode::F5:
            res = GLFW_KEY_F5;
            break;
        case KeyCode::F6:
            res = GLFW_KEY_F6;
            break;
        case KeyCode::F7:
            res = GLFW_KEY_F7;
            break;
        case KeyCode::F8:
            res = GLFW_KEY_F8;
            break;
        case KeyCode::F9:
            res = GLFW_KEY_F9;
            break;
        case KeyCode::F10:
            res = GLFW_KEY_F10;
            break;
        case KeyCode::F11:
            res = GLFW_KEY_F11;
            break;
        case KeyCode::F12:
            res = GLFW_KEY_F12;
            break;
        case KeyCode::F13:
            res = GLFW_KEY_F13;
            break;
        case KeyCode::F14:
            res = GLFW_KEY_F14;
            break;
        case KeyCode::F15:
            res = GLFW_KEY_F15;
            break;
        case KeyCode::F16:
            res = GLFW_KEY_F16;
            break;
        case KeyCode::F17:
            res = GLFW_KEY_F17;
            break;
        case KeyCode::F18:
            res = GLFW_KEY_F18;
            break;
        case KeyCode::F19:
            res = GLFW_KEY_F19;
            break;
        case KeyCode::F20:
            res = GLFW_KEY_F20;
            break;
        case KeyCode::F21:
            res = GLFW_KEY_F21;
            break;
        case KeyCode::F22:
            res = GLFW_KEY_F22;
            break;
        case KeyCode::F23:
            res = GLFW_KEY_F23;
            break;
        case KeyCode::F24:
            res = GLFW_KEY_F24;
            break;
        case KeyCode::F25:
            res = GLFW_KEY_F25;
            break;
        case KeyCode::KP0:
            res = GLFW_KEY_KP_0;
            break;
        case KeyCode::KP1:
            res = GLFW_KEY_KP_1;
            break;
        case KeyCode::KP2:
            res = GLFW_KEY_KP_2;
            break;
        case KeyCode::KP3:
            res = GLFW_KEY_KP_3;
            break;
        case KeyCode::KP4:
            res = GLFW_KEY_KP_4;
            break;
        case KeyCode::KP5:
            res = GLFW_KEY_KP_5;
            break;
        case KeyCode::KP6:
            res = GLFW_KEY_KP_6;
            break;
        case KeyCode::KP7:
            res = GLFW_KEY_KP_7;
            break;
        case KeyCode::KP8:
            res = GLFW_KEY_KP_8;
            break;
        case KeyCode::KP9:
            res = GLFW_KEY_KP_9;
            break;
        case KeyCode::KPDecimal:
            res = GLFW_KEY_KP_DECIMAL;
            break;
        case KeyCode::KPDivide:
            res = GLFW_KEY_KP_DIVIDE;
            break;
        case KeyCode::KPMultiply:
            res = GLFW_KEY_KP_MULTIPLY;
            break;
        case KeyCode::KPSubtract:
            res = GLFW_KEY_KP_SUBTRACT;
            break;
        case KeyCode::KPAdd:
            res = GLFW_KEY_KP_ADD;
            break;
        case KeyCode::KPEnter:
            res = GLFW_KEY_KP_ENTER;
            break;
        case KeyCode::KPEqual:
            res = GLFW_KEY_KP_EQUAL;
            break;
        case KeyCode::LeftShift:
            res = GLFW_KEY_LEFT_SHIFT;
            break;
        case KeyCode::LeftControl:
            res = GLFW_KEY_LEFT_CONTROL;
            break;
        case KeyCode::LeftAlt:
            res = GLFW_KEY_LEFT_ALT;
            break;
        case KeyCode::LeftSuper:
            res = GLFW_KEY_LEFT_SUPER;
            break;
        case KeyCode::RightShift:
            res = GLFW_KEY_RIGHT_SHIFT;
            break;
        case KeyCode::RightControl:
            res = GLFW_KEY_RIGHT_CONTROL;
            break;
        case KeyCode::RightAlt:
            res = GLFW_KEY_RIGHT_ALT;
            break;
        case KeyCode::RightSuper:
            res = GLFW_KEY_RIGHT_SUPER;
            break;
        case KeyCode::Menu:
            res = GLFW_KEY_MENU;
            break;
        default:
            res = -1;
            break;
    }

    return res;
}

int ConvertMEMouseCodeGLFWMouseButton(MouseCode button)
{
    int res = -1;

    switch (button)
    {
        case MouseCode::Unkown:
            res = -1;
            break;
        case MouseCode::Button0:
            res = GLFW_MOUSE_BUTTON_1;
            break;
        case MouseCode::Button1:
            res = GLFW_MOUSE_BUTTON_2;
            break;
        case MouseCode::Button2:
            res = GLFW_MOUSE_BUTTON_3;
            break;
        case MouseCode::Button3:
            res = GLFW_MOUSE_BUTTON_4;
            break;
        case MouseCode::Button4:
            res = GLFW_MOUSE_BUTTON_5;
            break;
        case MouseCode::Button5:
            res = GLFW_MOUSE_BUTTON_6;
            break;
        case MouseCode::Button6:
            res = GLFW_MOUSE_BUTTON_7;
            break;
        case MouseCode::Button7:
            res = GLFW_MOUSE_BUTTON_8;
            break;
        default:
            res = -1;
            break;
    }

    return res;
}

}  //namespace Utils
}  //namespace ME
