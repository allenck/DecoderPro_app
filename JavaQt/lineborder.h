#ifndef LINEBORDER_H
#define LINEBORDER_H
#include "border.h"

class LineBorder : public Border //temp use Border rather than AbstractBorder
{
public:
 /**
 * Creates a line border with the specified color and a
 * thickness = 1.
 * @param color the color for the border
 */
 /*public*/ LineBorder(QColor color, QObject* parent = 0);
 /*public*/ LineBorder(QColor color, int thickness, QObject* parent = 0);
 /*public*/ LineBorder(QColor color, int thickness, bool roundedCorners, QObject* parent = 0) ;
#if 0
 LineBorder(int top, int left, int bottom, int right, QObject* parent = 0);
 LineBorder(Insets* borderInsets, QObject* parent = 0);
#endif
 /*public*/ int lineWidth();
 /*public*/ QColor color();
 /*public*/ bool roundedCorners();

private:
 /*private*/ static Border* blackLine;
 /*private*/ static Border* grayLine;
 void common(QColor color, int thickness, bool roundedCorners);

protected:
 /*protected*/ int thickness;
 /*protected*/ QColor lineColor;
 /*protected*/ bool _roundedCorners;
#if 0
 /*protected*/ int left, right, top, bottom;
#endif

};

#endif // LINEBORDER_H
