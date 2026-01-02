#pragma once
#include "GUI.h"
#include "definitions.h"

#include "imgui_impl_win32.h"
// #include "imgui_impl_dx12.h"

// #pragma comment(lib, "d3d12.lib")
// #pragma comment(lib, "dxgi.lib")






class DirectWindow12
{
private:
	static inline HMODULE applicationModule = nullptr;
public:
	static HMODULE GetApplicationModule()
	{
		return applicationModule;
	}
	static void SetApplicationModule(const HMODULE& newApplicationModule)
	{
		applicationModule = newApplicationModule;
	}




public:
	static void Create();
};

