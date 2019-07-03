#pragma once

#include "RyuLib.h"
#include <stdexcept>
#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

const int MIN_WINDOW_WIDTH = 1280;
const int MIN_WINDOW_HEIGHT = 720;

class RyuDevice
{
public:

	RyuDevice();
	virtual ~RyuDevice();

	static RyuDevice* Get();

	virtual bool CreateDevice();
	virtual void DestroyDevice();

protected:

	bool bEnableMsaaa;

private:

	static RyuDevice* Get_Internal();

private:

	HWND MainWindow;

	static int NumOfDevices;
	Microsoft::WRL::ComPtr<ID3D11Device> D3D11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D11Context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> D3D11SwapChain;


};
