#ifndef BORDER_H
#define BORDER_H
#include <QObject>
#include <QPainter>
#include "insets.h"

/**
 * Interface describing an object capable of rendering a border
 * around the edges of a swing component.
 * For examples of using borders see
 * <a href="https://docs.oracle.com/javase/tutorial/uiswing/components/border.htmll">How to Use Borders</a>,
 * a section in <em>The Java Tutorial.</em>
 * <p>
 * In the Swing component set, borders supercede Insets as the
 * mechanism for creating a (decorated or plain) area around the
 * edge of a component.
 * <p>
 * Usage Notes:
 * <ul>
 * <li>Use EmptyBorder to create a plain border (this mechanism
 *     replaces its predecessor, <code>setInsets</code>).
 * <li>Use CompoundBorder to nest multiple border objects, creating
 *     a single, combined border.
 * <li>Border instances are designed to be shared. Rather than creating
 *     a new border object using one of border classes, use the
 *     BorderFactory methods, which produces a shared instance of the
 *     common border types.
 * <li>Additional border styles include BevelBorder, SoftBevelBorder,
 *     EtchedBorder, LineBorder, TitledBorder, and MatteBorder.
 * <li>To create a new border class, subclass AbstractBorder.
 * </ul>
 *
 * @author David Kloba
 * @author Amy Fowler
 * @see javax.swing.BorderFactory
 * @see EmptyBorder
 * @see CompoundBorder
 */
/*public*/ /*interface*/class Border : public QObject
{
public:
 Border(QObject* parent = 0) : QObject(parent) {}
    /**
     * Paints the border for the specified component with the specified
     * position and size.
     * @param c the component for which this border is being painted
     * @param g the paint graphics
     * @param x the x position of the painted border
     * @param y the y position of the painted border
     * @param width the width of the painted border
     * @param height the height of the painted border
     */
    virtual void paintBorder(QWidget* c, QPainter* g, int x, int y, int width, int height) {}

    /**
     * Returns the insets of the border.
     * @param c the component for which this border insets value applies
     */
    virtual Insets* getBorderInsets(QWidget* c) {return NULL;}

    /**
     * Returns whether or not the border is opaque.  If the border
     * is opaque, it is responsible for filling in it's own
     * background when painting.
     */
    virtual bool isBorderOpaque() {return false;}
    virtual /*public*/ int lineWidth() {return 1;}
    virtual /*public*/ QColor color() {return QColor(Qt::black);}
    virtual /*public*/ bool roundedCorners() {return false;}


};
#endif // BORDER_H
