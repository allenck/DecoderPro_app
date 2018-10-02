#ifndef COMPOUNDBORDER_H
#define COMPOUNDBORDER_H
#include "abstractborder.h"

class CompoundBorder : public AbstractBorder
{
public:
 CompoundBorder(QObject* parent = nullptr);
 /*public*/ CompoundBorder(Border* outsideBorder, Border* insideBorder, QObject* parent = nullptr);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ bool isBorderOpaque();
 /*public*/ Border* getOutsideBorder();
 /*public*/ Border* getInsideBorder();

protected:
 /*protected*/ Border* outsideBorder;
 /*protected*/ Border* insideBorder;

};

#endif // COMPOUNDBORDER_H
