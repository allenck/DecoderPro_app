#include "urisyntaxexception.h"

/**
 * Checked exception thrown to indicate that a string could not be parsed as a
 * URI reference.
 *
 * @author Mark Reinhold
 * @see URI
 * @since 1.4
 */

///*public*/ class URISyntaxException
//    extends Exception
//{
//    /*private*/ static final long serialVersionUID = 2137979680897488891L;


    /**
     * Constructs an instance from the given input string, reason, and error
     * index.
     *
     * @param  input   The input string
     * @param  reason  A string explaining why the input could not be parsed
     * @param  index   The index at which the parse error occurred,
     *                 or {@code -1} if the index is not known
     *
     * @throws  NullPointerException
     *          If either the input or reason strings are {@code null}
     *
     * @throws  IllegalArgumentException
     *          If the error index is less than {@code -1}
     */
    /*public*/ URISyntaxException::URISyntaxException(QString input, QString reason, int index) : Exception(reason){
        //super(reason);
        if ((input == "") || (reason == ""))
            throw  NullPointerException();
        if (index < -1)
            throw  IllegalArgumentException();
        this->input = input;
        this->index = index;
    }

    /**
     * Constructs an instance from the given input string and reason.  The
     * resulting object will have an error index of {@code -1}.
     *
     * @param  input   The input string
     * @param  reason  A string explaining why the input could not be parsed
     *
     * @throws  NullPointerException
     *          If either the input or reason strings are {@code null}
     */
    /*public*/ URISyntaxException::URISyntaxException(QString input, QString reason) : Exception(reason)
{
 if ((input == "") || (reason == ""))
     throw  NullPointerException();
 if (index < -1)
     throw  IllegalArgumentException();
 this->input = input;
 this->index = -1;

    }

    /**
     * Returns the input string.
     *
     * @return  The input string
     */
    /*public*/ QString URISyntaxException::getInput() {
        return input;
    }

    /**
     * Returns a string explaining why the input string could not be parsed.
     *
     * @return  The reason string
     */
    /*public*/ QString URISyntaxException::getReason() {
        return Exception::getMessage();
    }

    /**
     * Returns an index into the input string of the position at which the
     * parse error occurred, or {@code -1} if this position is not known.
     *
     * @return  The error index
     */
    /*public*/ int URISyntaxException::getIndex() {
        return index;
    }

    /**
     * Returns a string describing the parse error.  The resulting string
     * consists of the reason string followed by a colon character
     * ({@code ':'}), a space, and the input string.  If the error index is
     * defined then the string {@code " at index "} followed by the index, in
     * decimal, is inserted after the reason string and before the colon
     * character.
     *
     * @return  A string describing the parse error
     */
    /*public*/ QString URISyntaxException::getMessage() {
        QString sb;// = new StringBuffer();
        sb.append(getReason());
        if (index > -1) {
            sb.append(" at index ");
            sb.append(index);
        }
        sb.append(": ");
        sb.append(input);
        return sb/*.toString()*/;
    }
