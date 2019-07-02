#pragma once

#include "CoreMinimal.h"

class RyuDevice;

class ApplicationBase
{
public:

	ApplicationBase();
	virtual ~ApplicationBase();

	virtual int Run();

protected:
	
	virtual bool Initialize();
	virtual int MainLoop();
	virtual void Destroy();

private:

	bool bIsActive;
	RyuDevice* Device;

};
