#ifndef SETTINGS_H
#define SETTINGS_H

#include <assert.h>

class Settings
{
public:
	Settings();
	
	static void setScale(float& newScale);
	static float& getScale();

	static void setFontSize(float& newFontSize);
	static float& getFontSize();
private:

	static Settings* sInstance;

	static float scale;
	static float fontSize;
};
#endif