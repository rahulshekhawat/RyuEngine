#include "RyuDevice.h"

int RyuDevice::NumOfDevices = 0;

RyuDevice::RyuDevice() :
	bEnableMsaaa(true),
	MainWindow(NULL),
	D3D11Device(nullptr),
	D3D11Context(nullptr),
	D3D11SwapChain(nullptr)
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

	// Create D3D11 device
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

	// Check for 4x MSAAA quality support
	UINT MsaaaQuality;
	D3D11Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MsaaaQuality);
	assert(MsaaaQuality > 0);

	// Swap chain
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc.Width = MIN_WINDOW_WIDTH;
	SwapChainDesc.BufferDesc.Height = MIN_WINDOW_HEIGHT;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	if (bEnableMsaaa)
	{
		SwapChainDesc.SampleDesc.Count = 4;
		SwapChainDesc.SampleDesc.Quality = MsaaaQuality - 1;
	}
	else
	{
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
	}

	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = MainWindow;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;

	// Microsoft::WRL::ComPtr<IDXGIDevice> DxgiDevice = nullptr;
	IDXGIDevice* DxgiDevice = nullptr;
	D3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)& DxgiDevice);

	// Microsoft::WRL::ComPtr<IDXGIAdapter> DxgiAdapter = nullptr;
	IDXGIAdapter* DxgiAdapter = nullptr;
	DxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)& DxgiAdapter);

	// Microsoft::WRL::ComPtr<IDXGIFactory> DxgiFactory = nullptr;
	IDXGIFactory* DxgiFactory = nullptr;
	DxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)& DxgiFactory);

	hr = DxgiFactory->CreateSwapChain(D3D11Device.Get(), &SwapChainDesc, &D3D11SwapChain);

	DxgiDevice->Release();
	DxgiAdapter->Release();
	DxgiFactory->Release();
	
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
