#include "abstractborder.h"
#include "exceptions.h"
#include <QPaintEvent>

AbstractBorder::AbstractBorder(QWidget* parent) : QWidget(parent)
{

}
/**
 * A class that implements an empty border with no size.
 * This provides a convenient base class from which other border
 * classes can be easily derived.
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
#if 0
//@SuppressWarnings("serial")
///*public*/ abstract class AbstractBorder implements Border, Serializable
//{
/**
 * This default implementation does no painting.
 * @param c the component for which this border is being painted
 * @param g the paint graphics
 * @param x the x position of the painted border
 * @param y the y position of the painted border
 * @param width the width of the painted border
 * @param height the height of the painted border
 */
/*public*/ void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
}
#endif
/**
 * This default implementation returns a new {@link Insets} object
 * that is initialized by the {@link #getBorderInsets(Component,Insets)}
 * method.
 * By default the {@code top}, {@code left}, {@code bottom},
 * and {@code right} fields are set to {@code 0}.
 *
 * @param c  the component for which this border insets value applies
 * @return a new {@link Insets} object
 */
/*public*/ Insets* AbstractBorder::getBorderInsets(QWidget* c)       {
    return getBorderInsets(c, new Insets(0, 0, 0, 0));
}

/**
 * Reinitializes the insets parameter with this Border's current Insets.
 * @param c the component for which this border insets value applies
 * @param insets the object to be reinitialized
 * @return the <code>insets</code> object
 */
/*public*/ Insets* AbstractBorder::getBorderInsets(QWidget* c, Insets* insets) {
 if(insets == nullptr)
  insets = new Insets(0, 0, 0, 0);
 insets->left = insets->top = insets->right = insets->bottom = 0;
 return insets;
}

/**
 * This default implementation returns false.
 * @return false
 */
/*public*/ bool AbstractBorder::isBorderOpaque() { return false; }

/**
 * This convenience method calls the static method.
 * @param c the component for which this border is being computed
 * @param x the x position of the border
 * @param y the y position of the border
 * @param width the width of the border
 * @param height the height of the border
 * @return a <code>Rectangle</code> containing the interior coordinates
 */
/*public*/ QRect AbstractBorder::getInteriorRectangle(QWidget* c, int x, int y, int width, int height) {
    return getInteriorRectangle(c, (Border*)this, x, y, width, height);
}

/**
 * Returns a rectangle using the arguments minus the
 * insets of the border. This is useful for determining the area
 * that components should draw in that will not intersect the border.
 * @param c the component for which this border is being computed
 * @param b the <code>Border</code> object
 * @param x the x position of the border
 * @param y the y position of the border
 * @param width the width of the border
 * @param height the height of the border
 * @return a <code>Rectangle</code> containing the interior coordinates
 */
/*public*/ /*static*/ QRect AbstractBorder::getInteriorRectangle(QWidget* c, Border* b, int x, int y, int width, int height) {
    Insets* insets;
    if(b != NULL)
        insets = b->getBorderInsets(c);
    else
        insets = new Insets(0, 0, 0, 0);
    return QRect(x + insets->left,
                                y + insets->top,
                                width - insets->right - insets->left,
                                height - insets->top - insets->bottom);
}

/**
 * Returns the baseline.  A return value less than 0 indicates the border
 * does not have a reasonable baseline.
 * <p>
 * The default implementation returns -1.  Subclasses that support
 * baseline should override appropriately.  If a value &gt;= 0 is
 * returned, then the component has a valid baseline for any
 * size &gt;= the minimum size and <code>getBaselineResizeBehavior</code>
 * can be used to determine how the baseline changes with size.
 *
 * @param c <code>Component</code> baseline is being requested for
 * @param width the width to get the baseline for
 * @param height the height to get the baseline for
 * @return the baseline or &lt; 0 indicating there is no reasonable
 *         baseline
 * @throws IllegalArgumentException if width or height is &lt; 0
 * @see java.awt.Component#getBaseline(int,int)
 * @see java.awt.Component#getBaselineResizeBehavior()
 * @since 1.6
 */
/*public*/ int AbstractBorder::getBaseline(QWidget c, int width, int height) {
    if (width < 0 || height < 0) {
        throw IllegalArgumentException(
                "Width and height must be >= 0");
    }
    return -1;
}
#if 0
/**
 * Returns an enum indicating how the baseline of a component
 * changes as the size changes.  This method is primarily meant for
 * layout managers and GUI builders.
 * <p>
 * The default implementation returns
 * <code>BaselineResizeBehavior.OTHER</code>, subclasses that support
 * baseline should override appropriately.  Subclasses should
 * never return <code>NULL</code>; if the baseline can not be
 * calculated return <code>BaselineResizeBehavior.OTHER</code>.  Callers
 * should first ask for the baseline using
 * <code>getBaseline</code> and if a value &gt;= 0 is returned use
 * this method.  It is acceptable for this method to return a
 * value other than <code>BaselineResizeBehavior.OTHER</code> even if
 * <code>getBaseline</code> returns a value less than 0.
 *
 * @param c <code>Component</code> to return baseline resize behavior for
 * @return an enum indicating how the baseline changes as the border is
 *         resized
 * @see java.awt.Component#getBaseline(int,int)
 * @see java.awt.Component#getBaselineResizeBehavior()
 * @since 1.6
 */
/*public*/ Component.BaselineResizeBehavior getBaselineResizeBehavior(
        Component c) {
    if (c == NULL) {
        throw new NullPointerException("Component must be non-NULL");
    }
    return Component.BaselineResizeBehavior.OTHER;
}

/*
 * Convenience function for determining ComponentOrientation.
 * Helps us avoid having Munge directives throughout the code.
 */
static bool isLeftToRight( Component c ) {
    return c.getComponentOrientation().isLeftToRight();
}
#endif
