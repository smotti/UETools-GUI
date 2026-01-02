#pragma once
#include "GUI.h"
#include "definitions.h"

#include "imgui_impl_win32.h"
// #include "imgui_impl_vulkan.h"

// #include <vulkan.h>






class VulkanWindow
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