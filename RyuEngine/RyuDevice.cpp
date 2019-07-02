#include "RyuDevice.h"

int RyuDevice::NumOfDevices = 0;

RyuDevice::RyuDevice()
{
}

RyuDevice::~RyuDevice()
{
	DestroyDevice();
}

RyuDevice* RyuDevice::Get()
{
	if (NumOfDevices == 1)
	{
		return nullptr;
	}
	else if (NumOfDevices == 0)
	{
		NumOfDevices += 1;
		return Get_Internal();
	}
	else
	{
		throw std::runtime_error("Invalid number of devices present");
	}

	return nullptr;
}

bool RyuDevice::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

	DWORD createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&D3D11Device,
		&featureLevel,
		&D3D11Context);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void RyuDevice::DestroyDevice()
{
}

RyuDevice* RyuDevice::Get_Internal()
{
	RyuDevice* Device = new RyuDevice;
	if (Device)
	{
		bool bCreateSuccess = Device->CreateDevice();
		if (bCreateSuccess)
		{
			return Device;
		}
		else
		{
			delete Device;
		}
	}
	return nullptr;
}
