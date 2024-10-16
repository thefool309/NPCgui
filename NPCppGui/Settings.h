#pragma once
#include "wx/wx.h"
enum ThemeChoice {
	Light,
	Dark
};

struct Settings {
	ThemeChoice currentThemeChoice = ThemeChoice::Light;
};
