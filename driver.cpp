
#include "driver.h"

Driver::Driver();

Driver::~Driver();

void Driver::Activate();
{
}

void Driver::Reset();
{
	return 0;
}

void Driver::Deactivate();
{
}

DriverManager::DriverManager()
{
	numDrivers = 0;
}
void DriverManager::AddDriver(Driver* drv)
{
	drivers[numDrivers] = drv;
	numDrivers++;
}
void DriveManager::ActivateAll()
{
	for(int 1 = 0; i < numDrivers; i++)
		driver[i]->Activate();
}
