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
/*public*/ LineBorder::LineBorder(QColor color, QWidget *parent) {
    common(color, 1, false);
}

/**
 * Creates a line border with the specified color and thickness.
 * @param color the color of the border
 * @param thickness the thickness of the border
 */
/*public*/ LineBorder::LineBorder(QColor color, int thickness, QWidget* parent)  {
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
/*public*/ LineBorder::LineBorder(QColor color, int thickness, bool roundedCorners, QWidget *parent)
{
 common(color, thickness, roundedCorners);
}

void LineBorder::common(QColor color, int thickness, bool roundedCorners)
{
    this->lineColor = color;
    this->thickness = thickness;
    this->_roundedCorners = roundedCorners;
}

/*public*/ LineBorder::LineBorder(int top, int left, int bottom, int right, QWidget* parent)
: AbstractBorder(parent){
    this->top = top;
    this->right = right;
    this->bottom = bottom;
    this->left = left;
}

/*public*/ LineBorder::LineBorder(Insets* borderInsets, QWidget* parent)
: AbstractBorder(parent)
{
    this->top = borderInsets->top;
    this->right = borderInsets->right;
    this->bottom = borderInsets->bottom;
    this->left = borderInsets->left;
}


/*public*/ int LineBorder::lineWidth() { return thickness;}
/*public*/ QColor LineBorder::color() { return lineColor;}
/*public*/ bool LineBorder::roundedCorners() { return _roundedCorners;}


/**
 * Paints the line border around a given Component.
 *
 * @param c the component whose border is to be painted.
 * @param g the graphics for painting.
 * @param x the horizontal position for painting the border.
 * @param y the vertical position for painting the border.
 * @param width the width of the available area for painting the border.
 * @param height the height of the available area for painting the border.
 */
/*public*/ void LineBorder::paintBorder(QWidget* c, /*QPainter  g,*/
                        int x, int y, int width, int height)
{
 QPainter  g(c);
  QColor oldColor = g.pen().color();

  //try
  {
    //g.setColor(lineColor);
   g.setPen(lineColor);

    // If width and height were not adjusted, the border would
    // appear one pixel too large in both directions.
    width -= 1;
    height -= 1;

    // Blurred, too large appearance
    // -----------------------------
    // While Java 2D has introduced line strokes of arbitrary width,
    // it seems desirable to keep this code independent of Java 2D.
    // Therefore, multiple nested rectangles (or rounded rectangles)
    // are drawn in order to simulate a line whose thickness is
    // greater than one pixel.
    //
    // This hack causes a blurred appearance when anti-aliasing is
    // on. Interestingly enough, though, the Sun JDK 1.3.1 (at least
    // on MacOS X 10.1.5) shows exactly the same appearance under
    // this condition. It thus seems likely that Sun does the same
    // hack for simulating thick lines.  For this reason, the
    // blurred appearance seems acceptable -- especially since GNU
    // Classpath tries to be compatible with the Sun reference
    // implementation.
    for (int i = 0; i < thickness; i++)
    {
      if (_roundedCorners)
        g.drawRoundRect(x, y, width, height, thickness, thickness);
      else
        g.drawRect(x, y, width, height);

      x += 1;
      y += 1;
      width -= 2;
      height -= 2;
    }
  }
//  finally
  {
    //g.setColor(oldColor);
   g.setPen(oldColor);
  }
}

//void LineBorder::paintEvent(QPaintEvent *event)
//{
// QPainter* g = (QPainter*)this;
// QRect r = rect();
// paintBorder(this, g, r.x(), r.y(), r.width(), r.height());

//}
