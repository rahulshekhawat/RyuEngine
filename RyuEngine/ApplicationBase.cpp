#include "ApplicationBase.h"
#include "RyuDevice.h"

ApplicationBase::ApplicationBase() :
	bIsActive(false),
	Device(nullptr)
{
}

ApplicationBase::~ApplicationBase()
{
}

int ApplicationBase::Run()
{
	rlog("Starting app execution!");
	if (!Initialize())
	{
		rlog_error("Failed to initialize the game app!");
		return 1;
	}

	int loopReturn = MainLoop();
	Destroy();

	rlog("Finishing app execution!");
	return loopReturn;
}

bool ApplicationBase::Initialize()
{
	RyuDevice* Device = RyuDevice::Get();
	if (!Device)
	{
		rlog_error("Failed to create device!");
		return false;
	}

	return true;
}

int ApplicationBase::MainLoop()
{
	rlog("Entering Mainloop\n");
	while (true)
	{
		if (!bIsActive)
		{
			Sleep(10);
		}
	}

	return 0;
}

void ApplicationBase::Destroy()
{
	if (Device)
	{
		delete Device;
	}
}
