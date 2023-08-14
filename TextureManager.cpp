#include "TextureManager.h"


void TextureManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
}


void TextureManager::End()
{
	CoUninitialize();
}