#include "emptyborder.h"
#include <QLayout>

//EmptyBorder::EmptyBorder()
//{

//}
/**
 * A class which provides an empty, transparent border which
 * takes up space but does no drawing.
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
//@SuppressWarnings("serial")
///*public*/ class EmptyBorder extends AbstractBorder implements Serializable
//{

    /**
     * Creates an empty border with the specified insets->
     * @param top the top inset of the border
     * @param left the left inset of the border
     * @param bottom the bottom inset of the border
     * @param right the right inset of the border
     */
    /*public*/ EmptyBorder::EmptyBorder(int top, int left, int bottom, int right, QWidget* parent)
 : AbstractBorder(parent){
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->left = left;
    }

    /**
     * Creates an empty border with the specified insets->
     * @param borderInsets the insets of the border
     */
    //@ConstructorProperties({"borderInsets"})
    /*public*/ EmptyBorder::EmptyBorder(Insets* borderInsets, QWidget* parent)
 : AbstractBorder(parent)
{
        this->top = borderInsets->top;
        this->right = borderInsets->right;
        this->bottom = borderInsets->bottom;
        this->left = borderInsets->left;
    }
#if 0
    /**
     * Does no drawing by default.
     */
    /*public*/ void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
    }
#endif
    /**
     * Reinitialize the insets parameter with this Border's current Insets.
     * @param c the component for which this border insets value applies
     * @param insets the object to be reinitialized
     */
    /*public*/ Insets* EmptyBorder::getBorderInsets(QWidget* c, Insets* insets) {
        insets->left = left;
        insets->top = top;
        insets->right = right;
        insets->bottom = bottom;
        return insets;
    }

    /**
     * Returns the insets of the border.
     * @since 1.3
     */
    /*public*/ Insets* EmptyBorder::getBorderInsets() {
        return new Insets(top, left, bottom, right);
    }

    /**
     * Returns whether or not the border is opaque.
     * Returns false by default.
     */
    /*public*/ bool EmptyBorder::isBorderOpaque() { return false; }

/*public*/ void EmptyBorder::paintBorder(QWidget* c, QPainter*  g, int x, int y, int width,
                        int height)
{}

/*public*/ void EmptyBorder::adjustLayout(QLayout *layout)
{
 // called by JPanel::setBorder
 int left,top, right, bottom;

 layout->getContentsMargins(&left,&top, &right, &bottom);
 left+= this->left;
 right += this->right;
 top += this->top;
 bottom += this->bottom;
 layout->setContentsMargins(left,top, right, bottom);

}
