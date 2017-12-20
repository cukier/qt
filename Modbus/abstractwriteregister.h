#ifndef ABSTRACTWRITEREGISTER_H
#define ABSTRACTWRITEREGISTER_H


class AbstractWriteRegister
{
public:
    AbstractWriteRegister();
    virtual void setRegister(unsigned short value) = 0;
};

#endif // ABSTRACTWRITEREGISTER_H
