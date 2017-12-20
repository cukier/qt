#include "modbusobject.h"

ModbusObject::ModbusObject()
{
    ModbusObject(1);
}

ModbusObject::ModbusObject(unsigned short addr)
{
    this->addr = addr;
    this->crc = 0;
    this->data = new unsigned short [50];
}
