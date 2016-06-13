#ifndef NUMBER_H
#define NUMBER_H

#include <QObject>

class Number : public QObject
{
    Q_OBJECT
public:
    explicit Number(QObject *parent = 0);

signals:

public slots:
private:
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
     * Returns the value of the specified number as a <code>double</code>.
     * This may involve rounding.
     *
     * @return  the numeric value represented by this object after conversion
     *          to type <code>double</code>.
     */
    /*public*/ /*abstract*/ double doubleValue();
    /*public*/ short byteValue();
    /*public*/ short shortValue();

};

#endif // NUMBER_H
