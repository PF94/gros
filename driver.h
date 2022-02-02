#ifndef __DRIVER_H
#define __DRIVER_H

	class Driver
	{
	public:
		Driver();
		~Driver();

		void Activate();
		void Reset();
		void Deactivate();
	};

	class DriverManager
	{
	private:
		Driver* drivers[255];
		int numDrivers;

	public:
		DriverManager();
		void addDriver(Driver*);

		void ActivateAll();
	};

#endif
