#ifndef COMPOUNDBORDER_H
#define COMPOUNDBORDER_H
#include "abstractborder.h"

class CompoundBorder : public AbstractBorder
{
public:
 CompoundBorder(QWidget *parent = nullptr);
 /*public*/ CompoundBorder(Border* outsideBorder, Border* insideBorder, QWidget* parent = nullptr);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ bool isBorderOpaque();
 /*public*/ Border* getOutsideBorder();
 /*public*/ Border* getInsideBorder();
 /*public*/ void paintBorder(QWidget* c, QPainter* g, int x, int y, int width, int height);

 QWidget* self() {return (QWidget*)this;}

private:

protected:
 /*protected*/ Border* outsideBorder;
 /*protected*/ Border* insideBorder;

};

#endif // COMPOUNDBORDER_H
