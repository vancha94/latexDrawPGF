#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H


#include <abstractitem.h>
#include <abstractline.h>

class AbstractShape : public AbstractLine
{
public:
    AbstractShape();

    virtual QString prepareText();
protected:
    virtual QString paramToText();
};

#endif // ABSTRACTSHAPE_H


