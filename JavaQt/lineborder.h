#ifndef LINEBORDER_H
#define LINEBORDER_H
#include "abstractborder.h"

class LineBorder : public  AbstractBorder
{
public:
 /**
 * Creates a line border with the specified color and a
 * thickness = 1.
 * @param color the color for the border
 */
 /*public*/ LineBorder(QColor color, QWidget* parent = 0);
 /*public*/ LineBorder(QColor color, int thickness, QWidget *parent = 0);
 /*public*/ LineBorder(QColor color, int thickness, bool roundedCorners, QWidget* parent = 0) ;
 LineBorder(int top, int left, int bottom, int right, QWidget *parent = 0);
 LineBorder(Insets* borderInsets, QWidget *parent = 0);
 /*public*/ int lineWidth();
 /*public*/ QColor color();
 /*public*/ bool roundedCorners();
 /*public*/ void paintBorder(QWidget* c, /*QPainter g,*/
                         int x, int y, int width, int height);
 QWidget* self() {return (QWidget*)this;}

private:
 /*private*/ static Border* blackLine;
 /*private*/ static Border* grayLine;
 void common(QColor color, int thickness, bool roundedCorners);
// void paintEvent(QPaintEvent *event);
 /*protected*/ int thickness;
 /*protected*/ QColor lineColor;
 /*protected*/ bool _roundedCorners;
 /*protected*/ int left, right, top, bottom;

};

#endif // LINEBORDER_H
