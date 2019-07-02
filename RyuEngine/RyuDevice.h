#pragma once

#include "RyuLib.h"
#include <stdexcept>
#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

class RyuDevice
{
public:

	RyuDevice();
	virtual ~RyuDevice();

	static RyuDevice* Get();

	virtual bool CreateDevice();
	virtual void DestroyDevice();

private:

	static RyuDevice* Get_Internal();

private:

	static int NumOfDevices;
	Microsoft::WRL::ComPtr<ID3D11Device> D3D11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D11Context;


};
