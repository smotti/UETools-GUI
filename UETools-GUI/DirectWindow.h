#pragma once
#include "GUI.h"

#include "definitions.h"

#include "dwmapi.h"
#include "d3d11.h"

#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"






extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);






class DirectWindow
{
private:
	/* @brief
	* Win32 window procedure for the overlay window. Forwards messages to ImGui's Win32 handler, 
	* handles resize/system/quit, and defers all other messages to DefWindowProc.
	* @param hWnd   Overlay window handle.
	* @param msg    Message identifier.
	* @param wParam Message-specific WPARAM.
	* @param lParam Message-specific LPARAM.
	* @output LRESULT: Non-zero if handled; otherwise the result of DefWindowProc. 
	*/
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




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




private:
	static inline ID3D11RenderTargetView* renderTargetView = nullptr;
public:
	static ID3D11RenderTargetView* GetRenderTargetView()
	{
		return renderTargetView;
	}
	static void InvalidateRenderTargetView()
	{
		if (renderTargetView)
		{
			renderTargetView->Release();
			renderTargetView = nullptr;
		}
	}
private:
	/**
	* @brief Creates (or recreates) the render target for the current swap chain back buffer.
	* @details Typically retrieves the back-buffer texture and creates a render-target view (RTV) from it.
	*/
	static bool CreateRenderTargetView();




private:
	static inline ID3D11DeviceContext* deviceContext = nullptr;
public:
	static ID3D11DeviceContext* GetDeviceContext()
	{
		return deviceContext;
	}
	static void SetDeviceContext(ID3D11DeviceContext* newDeviceContext)
	{
		deviceContext = newDeviceContext;
	}
	static void InvalidateDeviceContext()
	{
		if (deviceContext)
		{
			deviceContext->Release();
			deviceContext = nullptr;
		}
	}




private:
	static inline IDXGISwapChain* swapChain = nullptr;
public:
	static IDXGISwapChain* GetSwapChain()
	{
		return swapChain;
	}
	static void SetSwapChain(IDXGISwapChain* newSwapChain)
	{
		swapChain = newSwapChain;
	}
	static void InvalidateSwapChain()
	{
		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
	}




private:
	static inline ID3D11Device* device = nullptr;
public:
	static ID3D11Device* GetDevice()
	{
		return device;
	}
	static void SetDevice(ID3D11Device* newDevice)
	{
		device = newDevice;
	}
	static void InvalidateDevice()
	{
		device->Release();
		device = nullptr;
	}
private:
	/**
	* @brief Initializes a Direct3D device, device context, and swap chain for the given window.
	* @param hWnd - Handle to the target window that will own the Direct3D swap chain.
	* @return true on successful device/swap-chain creation; false if initialization fails.
	*/
	static bool CreateDevice(HWND hWnd, const bool& HDR = false);
	/**
	* @brief Releases all Direct3D resources created by CreateDeviceD3D().
	* @details Safely releases the device, device context, swap chain, and any associated COM objects.
	*/
	static void CleanupDevice();




private:
	static inline bool bInit = false;
	static inline HWND hTargetWindow = nullptr;
	static inline BOOL bTargetSet = FALSE;
	static inline DWORD dTargetPID = 0;

private:
	/**
	* @brief : Setter function used to define the target window from the window picker.
	* 		 This is used only when the overlay is build as an EXE.
	* @param hWindow : target window.
	*/
	static void SetTargetWindow(const HWND& hWindow);
	/**
	* @brief : Callback function that retrive the main window of the process.
			 This function is only called when the overlay is build as DLL.
			 (https://learn.microsoft.com/fr-fr/windows/win32/api/winuser/nf-winuser-enumwindows)

	*/
	static BOOL EnumWind(HWND hWindow, LPARAM lParam);
	/**
	* @brief : Function that retrieve the main window of the process.
			 This function is only called when the overlay is build as DLL.
	*/
	static void GetWindow();
	/**
	* @brief : Function that move the overlay on top of the targeted window.
	* @param hWindow: Window of the overlay.
	*/
	static void MoveWindow(const HWND& hWindow, const bool& forceInvalidSize = false);
	/**
	* @brief : Function that check if the overlay window or the targeted window is focus.
	* @param  hWindow: Window of the overlay.
	* @retval : TRUE if one of the window is focus else FALSE.
	*/
	static BOOL IsWindowFocus(const HWND& hWindow);
	/**
	* @brief : Function that check if a window is valid.
	* @param  hWindow : window to be tested.
	* @retval : TRUE if the window is valid else FALSE.
	*/
	static BOOL IsWindowValid(const HWND& hWindow);
	/**
	* @brief : Function that check if a window is cloacked.
	* @param  hWindow : window to be tested.
	* @retval : TRUE if the window is cloacked else FALSE.
	*/
	static BOOL IsWindowCloaked(const HWND& hWindow);
	/**
	* @brief : Function that look if the targeted window has been closed.
	* @retval : TRUE if the function is still up else FALSE.
	*/
	static BOOL IsWindowAlive();

	

public:
	/**
	* @brief : Function that create the overlay window and more.
	*/
	static void Create();
};

