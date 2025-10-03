#pragma once
#include <Windows.h>
#include "imgui/imgui.h"
#include "custom.h"


class Render {
private:
	static bool isOpened;
public:
	static bool IsOpened();
	static void KeyManager();
	static void UI();
	static void Extra();
};
