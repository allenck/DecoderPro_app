#include "lineborder.h"

/**
 * A class which implements a line border of arbitrary thickness
 * and of a single color.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author David Kloba
 */
/*private*/ /*static*/ Border* LineBorder::blackLine = NULL;
/*private*/ /*static*/ Border* LineBorder::grayLine = NULL;

/**
 * Creates a line border with the specified color and a
 * thickness = 1.
 * @param color the color for the border
 */
/*public*/ LineBorder::LineBorder(QColor color, QObject* parent) {
    common(color, 1, false);
}

/**
 * Creates a line border with the specified color and thickness.
 * @param color the color of the border
 * @param thickness the thickness of the border
 */
/*public*/ LineBorder::LineBorder(QColor color, int thickness, QObject* parent)  {
    common(color, thickness, false);
}

/**
 * Creates a line border with the specified color, thickness,
 * and corner shape.
 * @param color the color of the border
 * @param thickness the thickness of the border
 * @param roundedCorners whether or not border corners should be round
 * @since 1.3
 */
//@ConstructorProperties({"lineColor", "thickness", "roundedCorners"})
/*public*/ LineBorder::LineBorder(QColor color, int thickness, bool roundedCorners, QObject* parent)
{
 common(color, thickness, roundedCorners);
}

void LineBorder::common(QColor color, int thickness, bool roundedCorners)
{
    this->lineColor = color;
    this->thickness = thickness;
    this->_roundedCorners = roundedCorners;
}
#if 0
/*public*/ LineBorder::LineBorder(int top, int left, int bottom, int right, QObject* parent)
: Border(parent){
    this->top = top;
    this->right = right;
    this->bottom = bottom;
    this->left = left;
}

/*public*/ LineBorder::LineBorder(Insets* borderInsets, QObject* parent)
: Border(parent)
{
    this->top = borderInsets->top;
    this->right = borderInsets->right;
    this->bottom = borderInsets->bottom;
    this->left = borderInsets->left;
}
#endif

/*public*/ int LineBorder::lineWidth() { return thickness;}
/*public*/ QColor LineBorder::color() { return lineColor;}
/*public*/ bool LineBorder::roundedCorners() { return _roundedCorners;}
