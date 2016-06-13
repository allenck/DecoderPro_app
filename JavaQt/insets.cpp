#include "insets.h"

Insets::Insets(QObject *parent) :
    QObject(parent)
{
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
}
/**
 * An <code>Insets</code> object is a representation of the borders
 * of a container. It specifies the space that a container must leave
 * at each of its edges. The space can be a border, a blank space, or
 * a title.
 *
 * @author      Arthur van Hoff
 * @author      Sami Shaio
 * @see         java.awt.LayoutManager
 * @see         java.awt.Container
 * @since       JDK1.0
 */
// /*public*/ class Insets implements Cloneable, java.io.Serializable {


/*
 * JDK 1.1 serialVersionUID
 */
//private static final long serialVersionUID = -2272572637695466749L;

//static {
//    /* ensure that the necessary native libraries are loaded */
//    Toolkit.loadLibraries();
//    if (!GraphicsEnvironment.isHeadless()) {
//        initIDs();
//    }
//}

/**
 * Creates and initializes a new <code>Insets</code> object with the
 * specified top, left, bottom, and right insets.
 * @param       top   the inset from the top.
 * @param       left   the inset from the left.
 * @param       bottom   the inset from the bottom.
 * @param       right   the inset from the right.
 */
/*public*/ Insets::Insets(int top, int left, int bottom, int right, QObject* parent) : QObject(parent)
{
    this->top = top;
    this->left = left;
    this->bottom = bottom;
    this->right = right;
}

/**
 * Set top, left, bottom, and right to the specified values
 *
 * @param       top   the inset from the top.
 * @param       left   the inset from the left.
 * @param       bottom   the inset from the bottom.
 * @param       right   the inset from the right.
 * @since 1.5
 */
/*public*/ void Insets::set(int top, int left, int bottom, int right)
{
    this->top = top;
    this->left = left;
    this->bottom = bottom;
    this->right = right;
}

/**
 * Checks whether two insets objects are equal. Two instances
 * of <code>Insets</code> are equal if the four integer values
 * of the fields <code>top</code>, <code>left</code>,
 * <code>bottom</code>, and <code>right</code> are all equal.
 * @return      <code>true</code> if the two insets are equal;
 *                          otherwise <code>false</code>.
 * @since       JDK1.1
 */
/*public*/ bool Insets::equals(QObject* obj)
{
    //if (obj instanceof Insets) {
    if(qobject_cast<Insets*>(obj) != NULL)
    {
        Insets* insets = (Insets*)obj;
        return ((top == insets->top) && (left == insets->left) &&
                (bottom == insets->bottom) && (right == insets->right));
    }
    return false;
}

/**
 * Returns the hash code for this Insets.
 *
 * @return    a hash code for this Insets.
 */
/*public*/ int Insets::hashCode() {
    int sum1 = left + bottom;
    int sum2 = right + top;
    int val1 = sum1 * (sum1 + 1)/2 + left;
    int val2 = sum2 * (sum2 + 1)/2 + top;
    int sum3 = val1 + val2;
    return sum3 * (sum3 + 1)/2 + val2;
}

/**
 * Returns a string representation of this <code>Insets</code> object.
 * This method is intended to be used only for debugging purposes, and
 * the content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not be
 * <code>null</code>.
 *
 * @return  a string representation of this <code>Insets</code> object.
 */
/*public*/ QString Insets::toString() {
    return  /*getClass().getName()*/QString("Insets") + "[top="  + QString::number(top) + ",left=" + QString::number(left) + ",bottom=" + QString::number(bottom) + ",right=" + QString::number(right) + "]";
}

/**
 * Create a copy of this object.
 * @return     a copy of this <code>Insets</code> object.
 */
/*public*/ QObject* Insets::clone() {
//    try {
//        return super.clone();
//    } catch (CloneNotSupportedException e) {
//        // this shouldn't happen, since we are Cloneable
//        throw new InternalError();
//    }
 return  (QObject*) new Insets(top, left, bottom, right);
}
