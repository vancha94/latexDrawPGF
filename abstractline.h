#ifndef ABSTRACTLINE_H
#define ABSTRACTLINE_H


#include "abstractitem.h"

class AbstractLine : public AbstractItem
{
public:
    AbstractLine();
protected:// methods
    virtual QString paramToText();
};

#endif // ABSTRACTLINE_H
