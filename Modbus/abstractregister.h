#ifndef ABSTRACTREGISTER_H
#define ABSTRACTREGISTER_H

#include "abstractreadregister.h"
#include "abstractwriteregister.h"

class AbstractRegister : public AbstractReadRegister, AbstractWriteRegister
{
public:
    AbstractRegister();
};

#endif // ABSTRACTREGISTER_H
