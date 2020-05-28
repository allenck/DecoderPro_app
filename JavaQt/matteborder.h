#ifndef MATTEBORDER_H
#define MATTEBORDER_H
#include <QColor>
#include <QIcon>
#include "emptyborder.h"
#include <QPaintEvent>

class MatteBorder : public EmptyBorder
{
public:
 /*public*/ MatteBorder(int top, int left, int bottom, int right, QColor matteColor, QWidget* parent = 0);
 /*public*/ MatteBorder(Insets* borderInsets, QColor matteColor, QWidget* parent = 0);
 /*public*/ MatteBorder(int top, int left, int bottom, int right, QIcon tileIcon, QWidget *parent = 0);
 /*public*/ MatteBorder(Insets* borderInsets, QIcon tileIcon, QWidget* parent = 0);
 /*public*/ MatteBorder(QIcon tileIcon, QObject* parent = 0);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ Insets* getBorderInsets();
 /*public*/ QColor getMatteColor();
 /*public*/ QIcon getTileIcon();
 /*public*/ bool isBorderOpaque();
 /*public*/ void paintBorder(QWidget* c, QPainter* g, int x, int y, int width, int height);
 QWidget* self() {return (QWidget*)this;}

private:
 /*private*/ Insets* computeInsets(Insets* insets);
 /*private*/ void paintEdge(QWidget* c, QPainter* g, int x, int y, int width, int height, int tileW, int tileH);

protected:
 /*protected*/ QColor color;
 /*protected*/ QIcon tileIcon;

};

#endif // MATTEBORDER_H
