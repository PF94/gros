
#include <hardwarecommunication/port.h>
using namespace gros::common; // not using it for some reason????
using namespace gros::hardwarecommunication;

Port::Port(gros::common::uint16_t portnumber)
{
	this->portnumber = portnumber;
}

Port::~Port()
{
}





Port8Bit::Port8Bit(gros::common::uint16_t portnumber)
	: Port(portnumber)
{
}

Port8Bit::~Port8Bit()
{
}

void Port8Bit::Write(gros::common::uint8_t data)
{
	Write8(portnumber, data);
}

gros::common::uint8_t Port8Bit::Read()
{
	return Read8(portnumber);
}





Port8BitSlow::Port8BitSlow(gros::common::uint16_t portnumber)
	: Port8Bit(portnumber)
{
}

Port8BitSlow::~Port8BitSlow()
{
}

void Port8BitSlow::Write(gros::common::uint8_t data)
{
	Write8Slow(portnumber, data);
}





Port16Bit::Port16Bit(gros::common::uint16_t portnumber)
	: Port(portnumber)
{
}

Port16Bit::~Port16Bit()
{
}

void Port16Bit::Write(gros::common::uint16_t data)
{
	Write16(portnumber, data);
}

gros::common::uint16_t Port16Bit::Read()
{
	return Read16(portnumber);
}





Port32Bit::Port32Bit(gros::common::uint16_t portnumber)
	: Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{
}

void Port32Bit::Write(gros::common::uint32_t data)
{
	Write32(portnumber, data);
}

gros::common::uint32_t Port32Bit::Read()
{
	return Read32(portnumber);
}
