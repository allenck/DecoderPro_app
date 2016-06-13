#include "number.h"

Number::Number(QObject *parent) :
    QObject(parent)
{
}
/**
 * The abstract class <code>Number</code> is the superclass of classes
 * <code>BigDecimal</code>, <code>BigInteger</code>,
 * <code>Byte</code>, <code>Double</code>, <code>Float</code>,
 * <code>Integer</code>, <code>Long</code>, and <code>Short</code>.
 * <p>
 * Subclasses of <code>Number</code> must provide methods to convert
 * the represented numeric value to <code>byte</code>, <code>double</code>,
 * <code>float</code>, <code>int</code>, <code>long</code>, and
 * <code>short</code>.
 *
 * @author      Lee Boynton
 * @author      Arthur van Hoff
 * @see     java.lang.Byte
 * @see     java.lang.Double
 * @see     java.lang.Float
 * @see     java.lang.Integer
 * @see     java.lang.Long
 * @see     java.lang.Short
 * @since   JDK1.0
 */
///*public*/ abstract class Number implements java.io.Serializable {
/**
 * Returns the value of the specified number as an <code>int</code>.
 * This may involve rounding or truncation.
 *
 * @return  the numeric value represented by this object after conversion
 *          to type <code>int</code>.
 */
/*public*/ /*abstract*/ int intValue();

/**
 * Returns the value of the specified number as a <code>long</code>.
 * This may involve rounding or truncation.
 *
 * @return  the numeric value represented by this object after conversion
 *          to type <code>long</code>.
 */
/*public*/ /*abstract*/ long longValue();

/**
 * Returns the value of the specified number as a <code>float</code>.
 * This may involve rounding.
 *
 * @return  the numeric value represented by this object after conversion
 *          to type <code>float</code>.
 */
/*public*/ /*abstract*/ float floatValue();

    /**
     * Returns the value of the specified number as a <code>byte</code>.
     * This may involve rounding or truncation.
     *
     * @return  the numeric value represented by this object after conversion
     *          to type <code>byte</code>.
     * @since   JDK1.1
     */
    /*public*/ short Number::byteValue() {
        return (short)intValue();
    }

    /**
     * Returns the value of the specified number as a <code>short</code>.
     * This may involve rounding or truncation.
     *
     * @return  the numeric value represented by this object after conversion
     *          to type <code>short</code>.
     * @since   JDK1.1
     */
    /*public*/ short Number::shortValue() {
        return (short)intValue();
    }
