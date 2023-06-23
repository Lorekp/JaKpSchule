#ifndef SETTINGS_H
#define SETTINGS_H

#include <assert.h>

class Settings
{
public:
	Settings();
	
	static void setScale(float& newScale);
	static float& getScale();
private:

	static Settings* sInstance;

	static float scale;
};
#endif