#ifndef EMPTYBORDER_H
#define EMPTYBORDER_H
#include "abstractborder.h"

class EmptyBorder : public AbstractBorder
{
public:
 /*public*/ EmptyBorder(int top, int left, int bottom, int right, QObject* parent = 0);
 /*public*/ EmptyBorder(Insets* borderInsets, QObject* parent = 0);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ Insets* getBorderInsets();
 /*public*/ bool isBorderOpaque();

protected:
 /*protected*/ int left, right, top, bottom;

};

#endif // EMPTYBORDER_H
