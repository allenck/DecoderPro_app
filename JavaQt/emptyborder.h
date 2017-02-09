#ifndef EMPTYBORDER_H
#define EMPTYBORDER_H
#include "border.h"

class EmptyBorder : public Border //temp use Border rather than AbstractBorder
{
public:
 /*public*/ EmptyBorder(int top, int left, int bottom, int right, QObject* parent = 0);
 /*public*/ EmptyBorder(Insets* borderInsets, QObject* parent = 0);

protected:
 /*protected*/ int left, right, top, bottom;

};

#endif // EMPTYBORDER_H
