#ifndef __GROS__HARDWARECOMMUNICATION__PCI_H
#define __GROS__HARDWARECOMMUNICATION__PCI_H

/** @file pci.h
 *  @brief Header file for the Peripheral Component Interconnect Controller
 *
 *  @author Gamerappa
 *  @date Feburary 3rd 2022
 */

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
namespace gros
{
	namespace hardwarecommunication
	{
		enum BaseAddressRegisterType
		{
			MemoryMapping = 0,
			InputOutput = 1
		};

		class BaseAddressRegister
		{
		public:
			bool prefetchable;
			gros::common::uint8_t* address;
			gros::common::uint32_t size;
			BaseAddressRegisterType type;
		};

		class PeripheralComponentInterconnectDeviceDescriptor
		{
		public:
			gros::common::uint32_t portBase;
			gros::common::uint32_t interrupt;

			gros::common::uint16_t bus;
			gros::common::uint16_t device;
			gros::common::uint16_t function;

			gros::common::uint16_t vendor_id;
			gros::common::uint16_t device_id;

			gros::common::uint8_t class_id;
			gros::common::uint8_t subclass_id;
			gros::common::uint8_t interface_id;

			gros::common::uint8_t revision;

			PeripheralComponentInterconnectDeviceDescriptor();
			~PeripheralComponentInterconnectDeviceDescriptor();
		};

		class PeripheralComponentInterconnectController
		{

			Port32Bit dataPort;
			Port32Bit commandPort;

		public:
			PeripheralComponentInterconnectController();
			~PeripheralComponentInterconnectController();

			common::uint32_t Read(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset);
			void Write(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset, common::uint32_t value);
			bool DeviceHasFunctions(common::uint16_t bus, common::uint16_t device);

			void SelectDrivers(gros::drivers::DriverManager* driverManager, gros::hardwarecommunication::InterruptManager* interrupts);
			gros::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, gros::hardwarecommunication::InterruptManager* interrupts);
			PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(gros::common::uint16_t bus, gros::common::uint16_t device, gros::common::uint16_t function);
			BaseAddressRegister GetBaseAddressRegister(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint16_t bar);
		};
	}
}

#endif
