#ifndef EMPTYBORDER_H
#define EMPTYBORDER_H
#include "abstractborder.h"

class EmptyBorder : public AbstractBorder
{
public:
 /*public*/ EmptyBorder(int top, int left, int bottom, int right, QWidget *parent = 0);
 /*public*/ EmptyBorder(Insets* borderInsets, QWidget *parent = 0);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ Insets* getBorderInsets();
 /*public*/ bool isBorderOpaque();
 /*public*/ void paintBorder(QWidget* c, QPainter*  g, int x, int y, int width,
                         int height);

 QWidget* self() {return (QWidget*)this;}

protected:
 /*protected*/ int left, right, top, bottom;

};

#endif // EMPTYBORDER_H
