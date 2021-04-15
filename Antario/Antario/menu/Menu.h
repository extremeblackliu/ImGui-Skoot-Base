#pragma once

#include "..\SDK\singleton.h"

class Menu
{
public:
	void Render();
	void Shutdown();
	bool bMenuOpened;
private:
	void ColorPicker(const char* name, float* color, bool alpha);

	void Legit();
	void Aimbot();
	void Antiaim();
	void Visuals();
	void Misc();
	void Skins();
	void Players();
};
extern Menu g_Menu;
