#pragma once
#include <GLFW/glfw3.h>

namespace Spoonity {

	//Enumeration class that creates aliases for GLFW key codes
	enum class KeyCode {

		//Letter Keys
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,

		//Number Keys (NOT numpad)
		Num1 = GLFW_KEY_1,
		Num2 = GLFW_KEY_2,
		Num3 = GLFW_KEY_3,
		Num4 = GLFW_KEY_4,
		Num5 = GLFW_KEY_5,
		Num6 = GLFW_KEY_6,
		Num7 = GLFW_KEY_7,
		Num8 = GLFW_KEY_8,
		Num9 = GLFW_KEY_9,
		Num0 = GLFW_KEY_0,

		//Symbol Keys
		Backtick = GLFW_KEY_GRAVE_ACCENT,
		Minus = GLFW_KEY_MINUS,
		Equal = GLFW_KEY_EQUAL,
		OpenBracket = GLFW_KEY_LEFT_BRACKET,
		CloseBracket = GLFW_KEY_RIGHT_BRACKET,
		Semicolon = GLFW_KEY_SEMICOLON,
		Apostrophe = GLFW_KEY_APOSTROPHE,
		Comma = GLFW_KEY_COMMA,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,
		Space = GLFW_KEY_SPACE,


		//Utility Keys
		Escape = GLFW_KEY_ESCAPE,
		Backspace = GLFW_KEY_BACKSPACE,
		Tab = GLFW_KEY_TAB,
		Enter = GLFW_KEY_ENTER,
		Capslock = GLFW_KEY_CAPS_LOCK,

		LeftShift = GLFW_KEY_LEFT_SHIFT,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		
		Alt = GLFW_KEY_LEFT_ALT,
		AltGr = GLFW_KEY_RIGHT_ALT,
		
		LeftSuper = GLFW_KEY_LEFT_SUPER,
		RightSuper = GLFW_KEY_RIGHT_SUPER,
		Windows = LeftSuper,
		Command = LeftSuper,

		//Arrow Keys
		Up = GLFW_KEY_UP,
		Down = GLFW_KEY_DOWN,
		Left = GLFW_KEY_LEFT,
		Right = GLFW_KEY_RIGHT,

		//Numpad Keys
		NumLock = GLFW_KEY_NUM_LOCK,
		NumpadEnter = GLFW_KEY_KP_ENTER,

		Decimal = GLFW_KEY_KP_DECIMAL,
		Divide = GLFW_KEY_KP_DIVIDE,
		Multiply = GLFW_KEY_KP_MULTIPLY,
		Subtract = GLFW_KEY_KP_SUBTRACT,
		Add = GLFW_KEY_KP_ADD,

		Numpad0 = GLFW_KEY_KP_0,
		Numpad1 = GLFW_KEY_KP_1,
		Numpad2 = GLFW_KEY_KP_2,
		Numpad3 = GLFW_KEY_KP_3,
		Numpad4 = GLFW_KEY_KP_4,
		Numpad5 = GLFW_KEY_KP_5,
		Numpad6 = GLFW_KEY_KP_6,
		Numpad7 = GLFW_KEY_KP_7,
		Numpad8 = GLFW_KEY_KP_8,
		Numpad9 = GLFW_KEY_KP_9,

		//Navigation and Editing Keys
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		ScrollLock = GLFW_KEY_SCROLL_LOCK,
		PauseBreak = GLFW_KEY_PAUSE,
		
		Home = GLFW_KEY_HOME,
		End = GLFW_KEY_END,
		Insert = GLFW_KEY_INSERT,
		Delete = GLFW_KEY_DELETE,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,

		//Function Keys
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
	};
}