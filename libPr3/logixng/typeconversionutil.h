#ifndef TYPECONVERSIONUTIL_H
#define TYPECONVERSIONUTIL_H
#include <QVariant>

class Logger;
/**
 * Converts between java types, for example String to Double and double to boolean.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*final*/ class TypeConversionUtil {
 Q_OBJECT
 public:
    /**
     * Is this object an integer number?
     * <P>
     * The method returns true if the object is any of these classes:
     * <ul>
     *   <li>AtomicInteger</li>
     *   <li>AtomicLong</li>
     *   <li>BigInteger</li>
     *   <li>Byte</li>
     *   <li>Short</li>
     *   <li>Integer</li>
     *   <li>Long</li>
     * </ul>
     * @param object the object to check
     * @return true if the object is an object that is an integer, false otherwise
     */
    /*public*/ static bool isIntegerNumber(QVariant object);

    /**
     * Is this object an integer or a floating point number?
     * <P>
     * The method returns true if the object is any of these classes:
     * <ul>
     *   <li>AtomicInteger</li>
     *   <li>AtomicLong</li>
     *   <li>BigInteger</li>
     *   <li>Byte</li>
     *   <li>Short</li>
     *   <li>Integer</li>
     *   <li>Long</li>
     *   <li>BigDecimal</li>
     *   <li>Float</li>
     *   <li>Double</li>
     * </ul>
     * @param object the object to check
     * @return true if the object is an object that is either an integer or a
     * float, false otherwise
     */
    /*public*/ static bool isFloatingNumber(QVariant object);

    /**
     * Is this object a String?
     * @param object the object to check
     * @return true if the object is a String, false otherwise
     */
    /*public*/ static bool isString(QVariant object) ;


    /*private*/ static bool convertStringToBoolean(/*@Nonnull*/ QString str, bool do_i18n);

    /**
     * Convert a value to a boolean.
     * <P>
     * Rules:
     * null is converted to false
     * empty string is converted to false
     * "0" string is converted to false
     * "0.000" string is converted to false, if the number of decimals is &gt; 0
     * empty map is converted to false
     * empty collection is converted to false
     * An integer number is converted to false if the number is 0
     * A floating number is converted to false if the number is -0.5 &lt; x &lt; 0.5
     * Everything else is converted to true
     * <P>
     * For objects that implement the Reportable interface, the value is fetched
     * from the method toReportString().
     *
     * @param value the value to convert
     * @param do_i18n true if internationalization should be done, false otherwise
     * @return the boolean value
     */
    /*public*/ static bool convertToBoolean(/*@CheckForNull*/ QVariant value, bool do_i18n) ;


    /**
     * Convert a value to a long.
     * <P>
     * Rules:
     * null is converted to 0
     * empty string is converted to 0
     * empty collection is converted to 0
     * an instance of the interface Number is converted to the number
     * a string that can be parsed as a number is converted to that number.
     * a string that doesn't start with a digit is converted to 0
     * <P>
     * For objects that implement the Reportable interface, the value is fetched
     * from the method toReportString() before doing the conversion.
     *
     * @param value the value to convert
     * @return the long value
     */
    /*public*/ static long convertToLong(/*@CheckForNull*/ QVariant value);

    /**
     * Convert a value to a double.
     * <P>
     * Rules:
     * null is converted to 0
     * empty string is converted to 0
     * empty collection is converted to 0
     * an instance of the interface Number is converted to the number
     * a string that can be parsed as a number is converted to that number.
     * if a string starts with a number AND do_i18n is false, it's converted to that number
     * a string that doesn't start with a digit is converted to 0
     * <P>
     * For objects that implement the Reportable interface, the value is fetched
     * from the method toReportString() before doing the conversion.
     *
     * @param value the value to convert
     * @param do_i18n true if internationalization should be done, false otherwise
     * @return the double value
     */
    /*public*/ static double convertToDouble(/*@CheckForNull*/ QVariant value, bool do_i18n);

    /**
     * Convert a value to a String.
     *
     * @param value the value to convert
     * @param do_i18n true if internationalization should be done, false otherwise
     * @return the String value
     */
    //@Nonnull
    /*public*/ static QString convertToString(/*@CheckForNull*/ QVariant value, bool do_i18n);
 private:
  static Logger* log;
  /*private*/ static long convertStringToLong(/*@Nonnull*/ QString str);
  /*private*/ static double convertStringToDouble(/*@Nonnull*/ QString str, bool do_i18n);

    };
#endif // TYPECONVERSIONUTIL_H
