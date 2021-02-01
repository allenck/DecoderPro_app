#include "stringutil.h"
#include <QLocale>
#include <QApplication>
#include "loggerfactory.h"

StringUtil::StringUtil()
{
}
/**
 * Common utility methods for working with Strings.
 * <P>
 * We needed a place to refactor common string-processing idioms in JMRI
 * code, so this class was created. It's more of a library of procedures
 * than a real class, as (so far) all of the operations have needed no state
 * information.
 * <P>
 * In some cases, these routines use a Java 1.3 or later method, falling
 * back to an explicit implementation when running on Java 1.1
 *
 * @author Bob Jacobsen  Copyright 2003
 * @version $Revision: 21621 $
 */

///*public*/ class StringUtil {

/*public*/ /*static*/ /*final*/ QString StringUtil::HTML_CLOSE_TAG = "</html>";
/*public*/ /*static*/ /*final*/ QString StringUtil::HTML_OPEN_TAG = "<html>";
/*public*/ /*static*/ /*final*/ QString StringUtil::LINEBREAK = "\n";


/**
 * Starting with two arrays, one of names and one of corresponding
 * numeric state values, find the state value that matches a
 * given name string
 * @return -1 if not found
 */
/*static*/ /*public*/ int StringUtil::getStateFromName(QString name, QVector<int> states, QVector<QString> names) {
    for (int i = 0; i < states.count(); i++)
        if (name==(names.at(i))) return states.at(i);
    return -1;
}

/**
 * Starting with three arrays, one of names, one of corresponding
 * numeric state values, and one of masks for the state values,
 * find the name string(s) that match a
 * given state value
 * @return empty array if none found
 */
/*static*/ /*public*/ QStringList StringUtil::getNamesFromStateMasked(int state, QVector<int> states, QVector<int> masks, QStringList names) {
    // first pass to count, get refs
    int count = 0;
   QVector<QString> temp = QVector<QString>(states.count());

    for (int i = 0; i < states.count(); i++)
        if ( ((state^states.at(i)) & masks.at(i)) == 0)
            temp.replace(count++, names.at(i));
    // second pas[i]s to create output array
    QVector<QString> output =  QVector<QString>(count);
    for (int i = 0; i < count; i++)
        output.replace(i, temp.at(i));
    return output.toList();
}

/**
 * Starting with two arrays, one of names and one of corresponding
 * numeric state values, find the name string that matches a
 * given state value. Only one may be returned.
 * @return null if not found
 */
/*static*/ /*public*/ QString StringUtil::getNameFromState(int state, QVector<int> states, QStringList names)
{
 for (int i = 0; i < states.count(); i++)
     if (state == states.at(i)) return names.at(i);
 return "";
}


//static /*final*/ char[] hexChars = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' } ;
QList<char> StringUtil::hexChars = QList<char>() <<  '0'<< '1'<< '2'<< '3'<< '4'<< '5'<< '6'<< '7'<< '8'<< '9'<< 'A'<< 'B'<< 'C'<< 'D'<< 'E'<< 'F' ;

/**
 * Convert an int to a exactly two hexadecimal characters
 * @param val
 * @return String exactly two characters long
 */
/*static*/ /*public*/ QString StringUtil::twoHexFromInt(int val) {
    QString sb;// = new StringBuffer() ;
    sb.append( hexChars[ (val&0xF0) >> 4 ] );
    sb.append( hexChars[ val & 0x0F ] ) ;
    return sb/*.toString() */;
}

/**
 * Quickly append an int to a String as exactly two hexadecimal characters
 * @param val Value to append in hex
 * @param inString String to be extended
 * @return String exactly two characters long
 */
/*static*/ /*public*/ QString StringUtil::appendTwoHexFromInt(int val, QString inString) {
    QString sb;// = new StringBuffer(inString) ;
    sb.append( hexChars[ (val&0xF0) >> 4 ] );
    sb.append( hexChars[ val & 0x0F ] );
    return sb/*.toString()*/ ;
}


/**
 * Convert a small number to eight 1/0 characters.
 * @param msbLeft the MSB is on the left of the display
 */
/*static*/ /*public*/ QString StringUtil::to8Bits(int val, bool msbLeft) {
    QString result ="";
    for (int i=0; i<8; i++) {
        if (msbLeft)
            result = (((val&0x01) != 0) ? "1" : "0")+result;
        else
            result = result+(((val&0x01) != 0) ? "1" : "0");
        val = val>>1;
    }
    return result;
}

/**
 * Create a String containing hexadecimal values from a byte[].
 *
 * @param bytes byte array.  Can be zero length,
 *  but must not be null.
 * @return String of hex values, ala "01 02 0A B1 21 ".
 */
/*static*/ /*public*/ QString StringUtil::hexStringFromBytes(QVector<char>* bytes)
{
 QString sb;// = new StringBuffer();
 for (int i = 0; i<bytes->size(); i++)
 {
  sb.append( hexChars.at((bytes->at(i)&0xF0) >> 4 ) );
  sb.append( hexChars.at( bytes->at(i) & 0x0F ) );
  sb.append(' ');
 }
 return sb/*.toString()*/;
}
/*static*/ /*public*/ QString StringUtil::hexStringFromBytes(QByteArray bytes)
{
 QString sb;// = new StringBuffer();
 for (int i = 0; i<bytes.size(); i++)
 {
  sb.append( hexChars.at((bytes.at(i)&0xF0) >> 4 ) );
  sb.append( hexChars.at( bytes.at(i) & 0x0F ) );
  sb.append(' ');
 }
 return sb/*.toString()*/;
}

/**
 * Create a byte[] from a String containing hexadecimal values.
 *
 * @param s String of hex values, ala "01 02 0A B1 21".
 * @return byte array, with one byte for each pair.  Can be zero length,
 *  but will not be null.
 */
/*static*/ /*public*/ QByteArray StringUtil::bytesFromHexString(QString s)
{
 QString ts = s+"  "; // ensure blanks on end to make scan easier
 int len = 0;
 // scan for length
 for (int i= 0; i< s.length(); i++)
 {
  if (ts.at(i) != ' ')
  {
   // need to process char for number. Is this a single digit?
   if (ts.at(i+1) != ' ')
   {
    // 2 char value
    i++;
    len++;
   }
   else
   {
    // 1 char value
    len++;
   }
  }
 }
 QByteArray b = QByteArray(len, 0);
 // scan for content
 int saveAt = 0;
 for (int i= 0; i< s.length(); i++)
 {
  if (ts.at(i) != ' ')
  {
   // need to process char for number. Is this a single digit?
   if (ts.at(i+1) != ' ')
   {
    // 2 char value
    QString v = QString(QString(ts.at(i))+QString(ts.at(i+1)));
    b.replace(saveAt, v.toInt(0,16));
    i++;
    saveAt++;
   }
   else
   {
    // 1 char value
    QString v = QString(ts.at(i));
    b.replace(saveAt, v.toInt(0,16));
    saveAt++;
   }
  }
 }
 return b;
}

/**
 * This is a lexagraphic sort; lower case goes to the end.
 * Identical entries are retained, so the output length is the same
 * as the input length.
 * @param values
 */
/*static*/ /*public*/ void StringUtil::sort(QStringList values) {
//    try {
//        java.util.Arrays.sort(values);
//    } catch (Throwable e1) {  // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//        bubblesort(values);
//    }
 qSort(values.begin(), values.end());
}
#if 0
static void StringUtil::bubblesort(QStringList values)
{
    // no Java sort, so ugly bubble sort
    for (int i=0; i<=values.length-2; i++) { // stop sort early to save time!
        for (int j=values.length-2; j>=i; j--) {
            // check that the jth value is smaller than j+1th,
            // else swap
            if (0 < values[j].compareTo(values[j+1])) {
                // swap
                String temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
}

static void bubblesort(Object[] values) {
    for (int i=0; i<=values.length-2; i++) { // stop sort early to save time!
        for (int j=values.length-2; j>=i; j--) {
            // check that the jth value is smaller than j+1th,
            // else swap
            if (0 < (values[j].toString()).compareTo(values[j+1].toString())) {
                // swap
                Object temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
}

/**
 * This is a lexagraphic sort; lower case goes to the end.
 * Identical entries are retained, so the output length is the same
 * as the input length.
 * @param values
 */
static /*public*/ void sort(Object[] values) {
    try {
        java.util.Arrays.sort(values);
    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
        // no Java sort, so ugly bubble sort
        bubblesort(values);
    }
}

static void bubblesortUpper(Object[] values) {
    for (int i=0; i<=values.length-2; i++) { // stop sort early to save time!
        for (int j=values.length-2; j>=i; j--) {
            // check that the jth value is smaller than j+1th,
            // else swap
            if (0 < (values[j].toString().toUpperCase()).compareTo(values[j+1].toString().toUpperCase())) {
                // swap
                Object temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
}

/**
 * This is a case-independent lexagraphic sort.
 * Identical entries are retained, so the output length is the same
 * as the input length.
 * @param values
 */
static /*public*/ void sortUpperCase(Object[] values) {
    // no Java sort, so ugly bubble sort
    bubblesortUpper(values);
}
#endif
/**
 * Sort String[] representing numbers, in ascending order.
 * @param values
 * @throws NumberFormatException
 */
/*static*/ /*public*/ void StringUtil::numberSort(QStringList values) //throws NumberFormatException
{
    for (int i=0; i<=values.length()-2; i++) { // stop sort early to save time!
        for (int j=values.length()-2; j>=i; j--) {
            // check that the jth value is larger than j+1th,
            // else swap
            if (values[j].toInt()>values[j+1].toInt()) {
                // swap
                QString temp = values[j];
                values.replace(j,values[j+1]);
                values[j+1] = temp;
            }
        }
    }
}
#if 0

/**
 * Join a collection of strings, separated by a delimiter
 * @param s	collection of strings
 * @param delimiter
 * @return e.g. join({"abc","def,"ghi"}, ".") ==> "abc.def.ghi"
 */
/*public*/ static String join(Collection<String> s, String delimiter) {
    StringBuffer buffer = new StringBuffer();
    Iterator<String> iter = s.iterator();
    while (iter.hasNext()) {
        buffer.append(iter.next());
        if (iter.hasNext()) {
            buffer.append(delimiter);
        }
    }
    return buffer.toString();
}

/**
 * Join an array of strings, separated by a delimiter
 * @param s	collection of strings
 * @param delimiter
 * @return e.g. join({"abc","def,"ghi"}, ".") ==> "abc.def.ghi"
 */
/*public*/ static String join(String[] s, String delimiter) {
    StringBuffer buffer = new StringBuffer();
    for (int i=0; i<s.length; i++) {
        buffer.append(s[i]);
        if (i<s.length-1) {
            buffer.append(delimiter);
        }
    }
    return buffer.toString();
}

/**
 * Split a string into an array of Strings, at a particular
 * divider.  This is similar to the new String.split method,
 * except that this does not provide regular expression
 * handling; the divider string is just a string.
 * @param input String to split
 * @param divider Where to divide the input; this does not appear in output
 */
static /*public*/ String[] split(String input, String divider) {
    int size = 0;
    String temp = input;

    // count entries
    while (temp.length() > 0) {
        size++;
        int index = temp.indexOf(divider);
        if (index < 0) break;    // break not found
        temp = temp.substring(index+divider.length());
        if (temp.length() == 0) {  // found at end
            size++;
            break;
        }
    }

    String[] result = new String[size];

    // find entries
    temp = input;
    size = 0;
    while (temp.length() > 0) {
        int index = temp.indexOf(divider);
        if (index < 0) break;    // done with all but last
        result[size] = temp.substring(0,index);
        temp = temp.substring(index+divider.length());
        size++;
    }
    result[size] = temp;

    return result;
}
#endif
/**
 * If there's an unmatched ), quote it with \,
 * and quote \ with \ too.
 */
/*static*/ /*public*/ QString StringUtil::parenQuote(QString in) {
    if (in==("")) return "";
    QString result = "";
    int level = 0;
    for (int i = 0; i < in.length(); i++) {
        QChar c = in.at(i);
        if (c == '(') level++;
        else if (c == '\\') result.append('\\');
        else if (c ==')') {
            level--;
            if (level < 0) {
                level = 0;
                result.append('\\');
            }
        }
        result.append(c);
    }
    return QString(result);
}

/**
 * Undo parenQuote
 */
/*static*/ QString StringUtil::parenUnQuote(QString in) {
    if (in==("")) return "";
    QString result = "";
    for (int i = 0; i < in.length(); i++) {
        QChar c = in.at(i);
        if (c == '\\') {
            i++;
            c = in.at(i);
            if (c != '\\' && c != ')') {
                // if none of those, just leave both in place
                result.append('\\');
            }
        }
        result.append(c);
    }
    return  QString(result);
}
#if 0
static /*public*/ java.util.List<String> splitParens(String in) {
    java.util.ArrayList<String> result = new java.util.ArrayList<String>();
    if (in==("")) return result;
    int level = 0;
    String temp = "";
    for (int i = 0; i < in.length(); i++) {
        char c = in.charAt(i);
        if (c == '(') {
            level++;
        } else if (c == '\\') {
            temp+=c;
            i++;
            c = in.charAt(i);
        } else if (c ==')') {
            level--;
        }
        temp+=c;
        if (level == 0) {
            result.add(temp);
            temp = "";
        }
    }
    return result;
}
#endif
/**
 * Return String after replacing various special characters with their "escaped" counterpart, to facilitate use with web servers.
 *
 * @param  s String to escape
 * @return String with escaped values
 */
/*static*/ /*public*/ QString StringUtil::escapeString(QString s) {
    return s.replace(" ","%20").replace("#","%23").replace("&","%26").replace("'","%27").replace("\"","%22").replace("<","%3C").replace(">","%3E");
}

/**
 * Return String after replacing various escaped character with their "regular" counterpart, to facilitate use with web servers.
 *
 * @param s String to unescape
 * @return String with escaped values replaced with regular values
 */
/*static*/ /*public*/ QString StringUtil::unescapeString(QString s) {
    return s.replace("%20"," ").replace("%23","#").replace("%26","&").replace("%27","'").replace("%22","\"").replace("%3C","<").replace("%3E",">");
}


/*private*/ /*static*/ QTranslator* StringUtil::translator = new QTranslator();
/*public*/ /*static*/ QString StringUtil::stringFormat(QLocale /*locale*/,  QString in)
{
 // Doesn't really do anything yet. Placeholder for actual translator to be done later.
 return in;
}

/**
 * Concatenates text Strings where either could possibly be in HTML format
 * (as used in many Swing components).
 * <p>
 * Ensures any appended text is added within the {@code <html>...</html>}
 * element, if there is any.
 *
 * @param baseText  original text
 * @param extraText text to be appended to original text
 * @return Combined text, with a single enclosing {@code <html>...</html>}
 * element (only if needed).
 */
/*public*/ /*static*/ QString StringUtil::concatTextHtmlAware(QString baseText, QString extraText) {
    if (baseText == "" && extraText == "") {
        return QString();
    }
    if (baseText == "") {
        return extraText;
    }
    if (extraText == "null") {
        return baseText;
    }
    bool hasHtml = false;
    QString result = baseText + extraText;
    result = result.replace("(?i)" + HTML_OPEN_TAG, "");
    result = result.replace("(?i)" + HTML_CLOSE_TAG, "");
    if (result != (baseText + extraText)) {
        hasHtml = true;
        log->debug(QString("\n\nbaseText:\n\"%1\"\nextraText:\n\"%2\"\n").arg(baseText).arg(extraText));
    }
    if (hasHtml) {
        result = HTML_OPEN_TAG + result + HTML_CLOSE_TAG;
        log->debug(QString("\nCombined String:\n\"%1\"\n").arg(result));
    }
    return result;
}

/*private*/ /*final*/ /*static*/ Logger* StringUtil::log = LoggerFactory::getLogger("StringUtil");
