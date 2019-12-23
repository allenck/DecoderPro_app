#include "spinnernumbermodel.h"
#include "exceptions.h"
#include <QVariant>

SpinnerNumberModel::SpinnerNumberModel(QObject *parent) :
    AbstractSpinnerModel(parent)
{
}
/**
 * A <code>SpinnerModel</code> for sequences of numbers.
 * The upper and lower bounds of the sequence are defined
 * by properties called <code>minimum</code> and
 * <code>maximum</code>. The size of the increase or decrease
 * computed by the <code>nextValue</code> and
 * <code>previousValue</code> methods is defined by a property called
 * <code>stepSize</code>.  The <code>minimum</code> and
 * <code>maximum</code> properties can be <code>null</code>
 * to indicate that the sequence has no lower or upper limit.
 * All of the properties in this class are defined in terms of two
 * generic types: <code>Number</code> and
 * <code>Comparable</code>, so that all Java numeric types
 * may be accommodated.  Internally, there's only support for
 * values whose type is one of the primitive <code>Number</code> types:
 * <code>Double</code>, <code>Float</code>, <code>Long</code>,
 * <code>Integer</code>, <code>Short</code>, or <code>Byte</code>.
 * <p>
 * To create a <code>SpinnerNumberModel</code> for the integer
 * range zero to one hundred, with
 * fifty as the initial value, one could write:
 * <pre>
 * Integer value = new Integer(50);
 * Integer min = new Integer(0);
 * Integer max = new Integer(100);
 * Integer step = new Integer(1);
 * SpinnerNumberModel model = new SpinnerNumberModel(value, min, max, step);
 * int fifty = model.getNumber().intValue();
 * </pre>
 * <p>
 * Spinners for integers and doubles are common, so special constructors
 * for these cases are provided.  For example to create the model in
 * the previous example, one could also write:
 * <pre>
 * SpinnerNumberModel model = new SpinnerNumberModel(50, 0, 100, 1);
 * </pre>
 * <p>
 * This model inherits a <code>ChangeListener</code>.
 * The <code>ChangeListeners</code> are notified
 * whenever the model's <code>value</code>, <code>stepSize</code>,
 * <code>minimum</code>, or <code>maximum</code> properties changes.
 *
 * @see JSpinner
 * @see SpinnerModel
 * @see AbstractSpinnerModel
 * @see SpinnerListModel
 * @see SpinnerDateModel
 *
 * @author Hans Muller
 * @since 1.4
*/
///*public*/ class SpinnerNumberModel extends AbstractSpinnerModel implements Serializable
//{

    /**
     * Constructs a <code>SpinnerModel</code> that represents
     * a closed sequence of
     * numbers from <code>minimum</code> to <code>maximum</code>.  The
     * <code>nextValue</code> and <code>previousValue</code> methods
     * compute elements of the sequence by adding or subtracting
     * <code>stepSize</code> respectively.  All of the parameters
     * must be mutually <code>Comparable</code>, <code>value</code>
     * and <code>stepSize</code> must be instances of <code>Integer</code>
     * <code>Long</code>, <code>Float</code>, or <code>Double</code>.
     * <p>
     * The <code>minimum</code> and <code>maximum</code> parameters
     * can be <code>null</code> to indicate that the range doesn't
     * have an upper or lower bound.
     * If <code>value</code> or <code>stepSize</code> is <code>null</code>,
     * or if both <code>minimum</code> and <code>maximum</code>
     * are specified and <code>mininum &gt; maximum</code> then an
     * <code>IllegalArgumentException</code> is thrown.
     * Similarly if <code>(minimum &lt;= value &lt;= maximum</code>) is false,
     * an <code>IllegalArgumentException</code> is thrown.
     *
     * @param value the current (non <code>null</code>) value of the model
     * @param minimum the first number in the sequence or <code>null</code>
     * @param maximum the last number in the sequence or <code>null</code>
     * @param stepSize the difference between elements of the sequence
     *
     * @throws IllegalArgumentException if stepSize or value is
     *     <code>null</code> or if the following expression is false:
     *     <code>minimum &lt;= value &lt;= maximum</code>
     */
    /*public*/ SpinnerNumberModel::SpinnerNumberModel(QVariant value, QVariant minimum, QVariant maximum, QVariant stepSize) {
    if ((value == QVariant()) || (stepSize == QVariant())) {
            throw  IllegalArgumentException("value and stepSize must be non-null");
        }
//    if (!(((minimum == QVariant()) || (minimum.compareTo(value) <= 0)) &&
//              ((maximum == null) || (maximum.compareTo(value) >= 0)))) {
//            throw new IllegalArgumentException("(minimum <= value <= maximum) is false");
//        }
        this->value = value;
        this->minimum = minimum;
        this->maximum = maximum;
        this->stepSize = stepSize;
    }

#if 0
    /**
     * Constructs a <code>SpinnerNumberModel</code> with the specified
     * <code>value</code>, <code>minimum</code>/<code>maximum</code> bounds,
     * and <code>stepSize</code>.
     *
     * @param value the current value of the model
     * @param minimum the first number in the sequence
     * @param maximum the last number in the sequence
     * @param stepSize the difference between elements of the sequence
     * @throws IllegalArgumentException if the following expression is false:
     *     <code>minimum &lt;= value &lt;= maximum</code>
     */
    /*public*/ SpinnerNumberModel::SpinnerNumberModel(int value, int minimum, int maximum, int stepSize) {
        //this(Integer.valueOf(value), Integer.valueOf(minimum), Integer.valueOf(maximum), Integer.valueOf(stepSize));
    this->value = value;
    this->minimum = minimum;
    this->maximum = maximum;
    this->stepSize = stepSize;
    }


    /**
     * Constructs a <code>SpinnerNumberModel</code> with the specified
     * <code>value</code>, <code>minimum</code>/<code>maximum</code> bounds,
     * and <code>stepSize</code>.
     *
     * @param value the current value of the model
     * @param minimum the first number in the sequence
     * @param maximum the last number in the sequence
     * @param stepSize the difference between elements of the sequence
     * @throws IllegalArgumentException   if the following expression is false:
     *     <code>minimum &lt;= value &lt;= maximum</code>
     */
    /*public*/ SpinnerNumberModel::SpinnerNumberModel(double value, double minimum, double maximum, double stepSize) {
        //this(new Double(value), new Double(minimum), new Double(maximum), new Double(stepSize));
    }


    /**
     * Constructs a <code>SpinnerNumberModel</code> with no
     * <code>minimum</code> or <code>maximum</code> value,
     * <code>stepSize</code> equal to one, and an initial value of zero.
     */
//    /*public*/ SpinnerNumberModel() {
//        this(Integer.valueOf(0), null, null, Integer.valueOf(1));
//    }

#endif
    /**
     * Changes the lower bound for numbers in this sequence.
     * If <code>minimum</code> is <code>null</code>,
     * then there is no lower bound.  No bounds checking is done here;
     * the new <code>minimum</code> value may invalidate the
     * <code>(minimum &lt;= value &lt= maximum)</code>
     * invariant enforced by the constructors.  This is to simplify updating
     * the model, naturally one should ensure that the invariant is true
     * before calling the <code>getNextValue</code>,
     * <code>getPreviousValue</code>, or <code>setValue</code> methods.
     * <p>
     * Typically this property is a <code>Number</code> of the same type
     * as the <code>value</code> however it's possible to use any
     * <code>Comparable</code> with a <code>compareTo</code>
     * method for a <code>Number</code> with the same type as the value.
     * For example if value was a <code>Long</code>,
     * <code>minimum</code> might be a Date subclass defined like this:
     * <pre>
     * MyDate extends Date {  // Date already implements Comparable
     *     public int compareTo(Long o) {
     *         long t = getTime();
     *         return (t < o.longValue() ? -1 : (t == o.longValue() ? 0 : 1));
     *     }
     * }
     * </pre>
     * <p>
     * This method fires a <code>ChangeEvent</code>
     * if the <code>minimum</code> has changed.
     *
     * @param minimum a <code>Comparable</code> that has a
     *     <code>compareTo</code> method for <code>Number</code>s with
     *     the same type as <code>value</code>
     * @see #getMinimum
     * @see #setMaximum
     * @see SpinnerModel#addChangeListener
     */
    /*public*/ void SpinnerNumberModel::setMinimum(QVariant minimum) {
        if ((minimum == QVariant()) ? (this->minimum != QVariant()) : minimum!=(this->minimum)) {
            this->minimum = minimum;
            fireStateChanged();
        }
    }


    /**
     * Returns the first number in this sequence.
     *
     * @return the value of the <code>minimum</code> property
     * @see #setMinimum
     */
    /*public*/ QVariant SpinnerNumberModel::getMinimum() {
        return minimum;
    }


    /**
     * Changes the upper bound for numbers in this sequence.
     * If <code>maximum</code> is <code>null</code>, then there
     * is no upper bound.  No bounds checking is done here; the new
     * <code>maximum</code> value may invalidate the
     * <code>(minimum <= value < maximum)</code>
     * invariant enforced by the constructors.  This is to simplify updating
     * the model, naturally one should ensure that the invariant is true
     * before calling the <code>next</code>, <code>previous</code>,
     * or <code>setValue</code> methods.
     * <p>
     * Typically this property is a <code>Number</code> of the same type
     * as the <code>value</code> however it's possible to use any
     * <code>Comparable</code> with a <code>compareTo</code>
     * method for a <code>Number</code> with the same type as the value.
     * See <a href="#setMinimum(java.lang.Comparable)">
     * <code>setMinimum</code></a> for an example.
     * <p>
     * This method fires a <code>ChangeEvent</code> if the
     * <code>maximum</code> has changed.
     *
     * @param maximum a <code>Comparable</code> that has a
     *     <code>compareTo</code> method for <code>Number</code>s with
     *     the same type as <code>value</code>
     * @see #getMaximum
     * @see #setMinimum
     * @see SpinnerModel#addChangeListener
     */
    /*public*/ void SpinnerNumberModel::setMaximum(QVariant maximum) {
        if ((maximum == QVariant()) ? (this->maximum != QVariant()) : maximum!=(this->maximum)) {
            this->maximum = maximum;
            fireStateChanged();
        }
    }


    /**
     * Returns the last number in the sequence.
     *
     * @return the value of the <code>maximum</code> property
     * @see #setMaximum
     */
    /*public*/ QVariant SpinnerNumberModel::getMaximum() {
        return maximum;
    }


    /**
     * Changes the size of the value change computed by the
     * <code>getNextValue</code> and <code>getPreviousValue</code>
     * methods.  An <code>IllegalArgumentException</code>
     * is thrown if <code>stepSize</code> is <code>null</code>.
     * <p>
     * This method fires a <code>ChangeEvent</code> if the
     * <code>stepSize</code> has changed.
     *
     * @param stepSize the size of the value change computed by the
     *     <code>getNextValue</code> and <code>getPreviousValue</code> methods
     * @see #getNextValue
     * @see #getPreviousValue
     * @see #getStepSize
     * @see SpinnerModel#addChangeListener
     */
    /*public*/ void SpinnerNumberModel::setStepSize(QVariant stepSize) {
        if (stepSize == 0) {
            throw new IllegalArgumentException("null stepSize");
        }
        if (stepSize!=(this->stepSize)) {
            this->stepSize = stepSize;
            fireStateChanged();
        }
    }


    /**
     * Returns the size of the value change computed by the
     * <code>getNextValue</code>
     * and <code>getPreviousValue</code> methods.
     *
     * @return the value of the <code>stepSize</code> property
     * @see #setStepSize
     */
    /*public*/ QVariant SpinnerNumberModel::getStepSize() {
        return stepSize;
    }


    /*private*/ QVariant SpinnerNumberModel::incrValue(int dir)
    {
        QVariant newValue;
        //if ((value instanceof Float) || (value instanceof Double))
        if(value.type() == QVariant::Double)
        {
            double v = value.toDouble() + (stepSize.toDouble() * (double)dir);
//            if (value instanceof Double) {
//                newValue = new Double(v);
//            }
//            else {
//                newValue = new Float(v);
//            }
            newValue = QVariant((int)v);
        }
        else {
            long v = value.toInt() + (stepSize.toInt() * (long)dir);

//            if (value instanceof Long)
//            {
//                newValue = Long.valueOf(v);
//            }
//            else if (value instanceof Integer) {
//                newValue = Integer.valueOf((int)v);
//            }
//            else if (value instanceof Short) {
//                newValue = Short.valueOf((short)v);
//            }
//            else {
//                newValue = Byte.valueOf((byte)v);
//            }
            newValue = QVariant((int)v);
        }

        //if ((maximum != QVariant()) && (maximum.compareTo(newValue) < 0))
        if((maximum != QVariant()) && maximum.toFloat() < newValue.toFloat())
        {
            return 0;
        }
        //if ((minimum != null) && (minimum.compareTo(newValue) > 0))
        if ((minimum != QVariant()) && minimum.toFloat() > 0)
        {
            return 0;
        }
        else {
            return newValue;
        }
    }


    /**
     * Returns the next number in the sequence.
     *
     * @return <code>value + stepSize</code> or <code>null</code> if the sum
     *     exceeds <code>maximum</code>.
     *
     * @see SpinnerModel#getNextValue
     * @see #getPreviousValue
     * @see #setStepSize
     */
    /*public*/ QVariant SpinnerNumberModel::getNextValue() {
        return incrValue(+1);
    }


    /**
     * Returns the previous number in the sequence.
     *
     * @return <code>value - stepSize</code>, or
     *     <code>null</code> if the sum is less
     *     than <code>minimum</code>.
     *
     * @see SpinnerModel#getPreviousValue
     * @see #getNextValue
     * @see #setStepSize
     */
    /*public*/ QVariant SpinnerNumberModel::getPreviousValue() {
        return incrValue(-1);
    }


    /**
     * Returns the value of the current element of the sequence.
     *
     * @return the value property
     * @see #setValue
     */
    /*public*/ QVariant SpinnerNumberModel::getNumber() {
        return value;
    }


    /**
     * Returns the value of the current element of the sequence.
     *
     * @return the value property
     * @see #setValue
     * @see #getNumber
     */
    /*public*/ QVariant SpinnerNumberModel::getValue() {
        return value;
    }


    /**
     * Sets the current value for this sequence.  If <code>value</code> is
     * <code>null</code>, or not a <code>Number</code>, an
     * <code>IllegalArgumentException</code> is thrown.  No
     * bounds checking is done here; the new value may invalidate the
     * <code>(minimum &lt;= value &lt;= maximum)</code>
     * invariant enforced by the constructors.   It's also possible to set
     * the value to be something that wouldn't naturally occur in the sequence,
     * i.e. a value that's not modulo the <code>stepSize</code>.
     * This is to simplify updating the model, and to accommodate
     * spinners that don't want to restrict values that have been
     * directly entered by the user. Naturally, one should ensure that the
     * <code>(minimum &lt;= value &lt;= maximum)</code> invariant is true
     * before calling the <code>next</code>, <code>previous</code>, or
     * <code>setValue</code> methods.
     * <p>
     * This method fires a <code>ChangeEvent</code> if the value has changed.
     *
     * @param value the current (non <code>null</code>) <code>Number</code>
     *         for this sequence
     * @throws IllegalArgumentException if <code>value</code> is
     *         <code>null</code> or not a <code>Number</code>
     * @see #getNumber
     * @see #getValue
     * @see SpinnerModel#addChangeListener
     */
    /*public*/ void SpinnerNumberModel::setValue(QVariant value) {
        if ((value == QVariant()) || ((value.type() != QVariant::Double && value.type() != QVariant::Int))) {
            throw new IllegalArgumentException("illegal value");
        }
        if (value!=(this->value)) {
            this->value = value;
            fireStateChanged();
        }
    }
//}
