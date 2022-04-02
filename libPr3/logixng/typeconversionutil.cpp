#include "typeconversionutil.h"
#include "loggerfactory.h"
#include  <QRegularExpression>

#include <QRegularExpressionMatch>
/**
 * Converts between java types, for example String to Double and double to boolean.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
// /*public*/  final class TypeConversionUtil {

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
    /*public*/  /*static*/ bool TypeConversionUtil::isIntegerNumber(QVariant object) {
//        return (object instanceof java.util.concurrent.atomic.AtomicInteger)
//                || (object instanceof java.util.concurrent.atomic.AtomicLong)
//                || (object instanceof java.math.BigInteger)
//                || (object instanceof Byte)
//                || (object instanceof Short)
//                || (object instanceof Integer)
//                || (object instanceof Long);
//      return object.canConvert<char>() || object.canConvert<short>() || object.canConvert<int>()
//        || object.canConvert<long>() || object.canConvert<qint64>();
     return object.type() == QMetaType::LongLong ||
       object.type() == QMetaType::Short ||
       object.type() == QMetaType::Long ||
       object.type() == QMetaType::Int ||
       object.type() == QMetaType::Char;
    }

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
    /*public*/  /*static*/ bool TypeConversionUtil::isFloatingNumber(QVariant object) {
//        return object.canConvert<int>()
//                || (object instanceof java.math.BigDecimal)
//                || (object.canConvert<float>())
//                || (object.canConvert<double>());
     return object.type() == QMetaType::Int
       || object.type() == QMetaType::UInt
       || object.type() == QMetaType::Long
       || object.type() == QMetaType::ULong
       || object.type() == QMetaType::LongLong
       || object.type() == QMetaType::ULongLong
       || object.type() == QMetaType::Short
       || object.type() == QMetaType::UShort
       || object.type() == QMetaType::Float
       || object.type() == QMetaType::Double;
    }

    /**
     * Is this object a String?
     * @param object the object to check
     * @return true if the object is a String, false otherwise
     */
    /*public*/  /*static*/ bool TypeConversionUtil::isString(QVariant object) {
        return object.canConvert<QString>();
    }


    /*private*/ /*static*/ bool TypeConversionUtil::convertStringToBoolean(/*@Nonnull*/ QString str, bool do_i18n) {
        // try to parse the string as a number
        try {
        bool ok;
            double number;
//            if (do_i18n) {
//                number = IntlUtilities.doubleValue(str);
//            } else {
                number =/* Double.parseDouble*/(str.toDouble(&ok));
                if(!ok) throw new NumberFormatException();
//            }
//                System.err.format("The string: '%s', result: %1.4f%n", str, (float)number);
            return ! ((-0.5 < number) && (number < 0.5));
        } catch (NumberFormatException /* ParseException*/* ex) {
            log->debug(tr("The string '%1' cannot be parsed as a number").arg(str));
        }

//            System.err.format("The string: %s, %s%n", str, value.getClass().getName());
        QRegularExpression pattern("^0(\\.0+)?$");
        //Pattern pattern = Pattern.compile(patternString, Pattern.CASE_INSENSITIVE);
        QRegularExpressionMatch matcher = pattern.match(str);
        if (matcher.hasMatch()) {
//                System.err.format("The string: '%s', result: %b%n", str, false);
            return false;
        }
//            System.err.format("The string: '%s', result: %b%n", str, !str.isEmpty());
        return !str.isEmpty();
    }

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
    /*public*/  /*static*/ bool TypeConversionUtil::convertToBoolean(/*@CheckForNull*/ QVariant value, bool do_i18n) {
        if (value == QVariant()) {
            return false;
        }
#if 0 // TODO:
        if (value instanceof Map) {
            Map map = ((Map)value);
            return !map.isEmpty();
        }

        if (value instanceof Collection) {
            Collection collection = ((Collection)value);
            return !collection.isEmpty();
        }

        if (value instanceof Reportable) {
            value = ((Reportable)value).toReportString();
        }
#endif
        if (value.canConvert<int>()) {
            double number = (value).toDouble();
            return ! ((-0.5 < number) && (number < 0.5));
        } else if (value.canConvert<bool>()) {
            return value.toBool();
        } else {
            if (value == QVariant()) return false;
            return convertStringToBoolean(value.toString(), do_i18n);
        }
    }

    /*private*/ /*static*/ long TypeConversionUtil::convertStringToLong(/*@Nonnull*/ QString str) {
        QString patternString = "(\\-?\\d+)";
        QRegularExpression re(patternString, QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch matcher = re.match(str);
        // Only look at the beginning of the string
        if (matcher.hasMatch()) {
            QString theNumber = matcher.captured(1);
            long number = (theNumber.toLong());
//            System.err.format("Number: %1.5f%n", number);
            log->debug(tr("the string %1 is converted to the number %2").arg(str).arg(number));
            return number;
        } else {
            log->warn(tr("the string \"%1\" cannot be converted to a number").arg(str));
            return 0;
        }
    }

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
    /*public*/  /*static*/ long TypeConversionUtil::convertToLong(/*@CheckForNull*/ QVariant value) {
        if (value == QVariant()) {
            log->warn("the object is null and the returned number is therefore 0.0");
            return 0;
        }
#if 0
        if (value instanceof Reportable) {
            value = ((Reportable)value).toReportString();
        }
#endif
        if (value.canConvert<long>()) {
//            System.err.format("Number: %1.5f%n", ((Number)value).doubleValue());
            return (value).toInt();
        } else if (value.canConvert<bool>()) {
            return (value.toBool()) ? 1 : 0;
        } else {
            if (value == QVariant()) return 0;
            return convertStringToLong(value.toString());
        }
    }
#if 1
    /*private*/ /*static*/ double TypeConversionUtil::convertStringToDouble(/*@Nonnull*/ QString str, bool do_i18n) {
        QString patternString = "(\\-?\\d+(\\.\\d+)?(e\\-?\\d+)?)";
        QRegularExpression pattern(patternString, QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch matcher = pattern.match(str);
        // Only look at the beginning of the string
        if (matcher.hasMatch()) {
            QString theNumber = matcher.captured(1);
            double number = (theNumber.toDouble());
//            System.err.format("Number: %1.5f%n", number);
            log->debug(tr("the string %1 is converted to the number %2").arg(str).arg(number));
            return number;
        } else {
            log->warn(tr("the string \"{}\" cannot be converted to a number").arg(str));
            return 0.0;
        }
    }

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
    /*public*/  /*static*/ double TypeConversionUtil::convertToDouble(/*@CheckForNull*/ QVariant value, bool do_i18n) {
        if (value == QVariant()) {
            log->warn("the object is null and the returned number is therefore 0.0");
            return 0.0;
        }
#if 0
        if (value instanceof Reportable) {
            value = ((Reportable)value).toReportString();
        }
#endif
        if (value.canConvert<double>()) {
//            System.err.format("Number: %1.5f%n", ((Number)value).doubleValue());
            return (value).toDouble();
        } else if (value.canConvert<bool>()) {
            return (value.toBool()) ? 1 : 0;
        } else {
            if (value == QVariant()) return 0.0;

            if (do_i18n) {
                // try to parse the string as a number
                try {
#if 0
                    double number = IntlUtilities.doubleValue(value.toString());
//                    System.err.format("The string: '%s', result: %1.4f%n", value, (float)number);
                    return number;
#endif
                } catch (ParseException ex) {
                    log->debug(tr("The string '%1' cannot be parsed as a number").arg(value.toString()));
                }
            }
            return convertStringToDouble(value.toString(), do_i18n);
        }
    }
#endif
    /**
     * Convert a value to a String.
     *
     * @param value the value to convert
     * @param do_i18n true if internationalization should be done, false otherwise
     * @return the String value
     */
    //@Nonnull
    /*public*/  /*static*/ QString TypeConversionUtil::convertToString(/*@CheckForNull*/ QVariant value, bool do_i18n) {
        if (value == QVariant()) {
            return "";
        }
#if 0
        if (value instanceof Reportable) {
            return ((Reportable)value).toReportString();
        }

        if (value.canConvert<long>() {
            if (do_i18n) {
                return IntlUtilities.valueOf(((Number)value).doubleValue());
            }
        }
#endif
        return value.toString();
    }

    /*private*/ /*final*/ /*static*/ Logger* TypeConversionUtil::log = LoggerFactory::getLogger("TypeConversionUtil");
