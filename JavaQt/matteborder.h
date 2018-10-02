#ifndef MATTEBORDER_H
#define MATTEBORDER_H
#include <QColor>
#include <QIcon>
#include "emptyborder.h"

class MatteBorder : public EmptyBorder
{
public:
 /*public*/ MatteBorder(int top, int left, int bottom, int right, QColor matteColor, QObject* parent = 0);
 /*public*/ MatteBorder(Insets* borderInsets, QColor matteColor, QObject* parent = 0);
 /*public*/ MatteBorder(int top, int left, int bottom, int right, QIcon tileIcon, QObject* parent = 0);
 /*public*/ MatteBorder(Insets* borderInsets, QIcon tileIcon, QObject* parent = 0);
 /*public*/ MatteBorder(QIcon tileIcon, QObject* parent = 0);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ Insets* getBorderInsets();
 /*public*/ QColor getMatteColor();
 /*public*/ QIcon getTileIcon();
 /*public*/ bool isBorderOpaque();

private:
 /*private*/ Insets* computeInsets(Insets* insets);


protected:
 /*protected*/ QColor color;
 /*protected*/ QIcon tileIcon;

};

#endif // MATTEBORDER_H
