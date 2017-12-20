#ifndef MODBUSOBJECT_H
#define MODBUSOBJECT_H


class ModbusObject
{
    unsigned short addr;
    unsigned short crc;
    unsigned short *data;
public:
    ModbusObject();
    ModbusObject(unsigned short addr = 1);
};

#endif // MODBUSOBJECT_H
