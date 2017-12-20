#ifndef ABSTRACTREADREGISTER_H
#define ABSTRACTREADREGISTER_H


class AbstractReadRegister
{
public:
    AbstractReadRegister();
    virtual unsigned short getRegister() = 0;
};

#endif // ABSTRACTREADREGISTER_H
