#include "mimetypeparameterlist.h"
#include <limits.h>
#include <QStringList>

//MimeTypeParameterList::MimeTypeParameterList(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * An object that encapsualtes the parameter list of a MimeType
 * as defined in RFC 2045 and 2046.
 *
 * @author jeff.dunn@eng.sun.com
 */
//class MimeTypeParameterList implements Cloneable {

/**
 * Default constructor.
 */
/*public*/ MimeTypeParameterList::MimeTypeParameterList(QObject *parent) :
QObject(parent) {
    log = new Logger("MimeTypeParameterList");
    parameters = new QHash<QString, QString>();
}

/*public*/ MimeTypeParameterList::MimeTypeParameterList(QString rawdata)
throw (MimeTypeParseException)
{
    log = new Logger("MimeTypeParameterList");
    parameters = new QHash<QString, QString>();

    //    now parse rawdata
    parse(rawdata);
}
#if 0
/*public*/ int MimeTypeParameterList::hashCode() {
    int code = /*Integer.MAX_VALUE*/__LONG_MAX__/45; // "random" value for empty lists
    QString paramName = "";
    QStringListIterator enum_ (this->getNames());

    while (enum_.hasNext()) {
        paramName = enum_.next();
        code += paramName.hashCode();
        code += this.get(paramName).hashCode();
    }

    return code;
} // hashCode()
#endif
/**
 * Two parameter lists are considered equal if they have exactly
 * the same set of parameter names and associated values. The
 * order of the parameters is not considered.
 */
/*public*/ bool MimeTypeParameterList::equals(QObject* thatObject)
{
    //System.out.println("MimeTypeParameterList.equals("+this+","+thatObject+")");
    //if (!(thatObject instanceof MimeTypeParameterList))
 if(qobject_cast<MimeTypeParameterList*>(thatObject) == NULL)
 {
        return false;
    }
    MimeTypeParameterList* that = (MimeTypeParameterList*)thatObject;
    if (this->size() != that->size()) {
        return false;
    }
    QString name = "";
    QString thisValue = "";
    QString thatValue = "";
//    Set entries = parameters->entrySet();
//    Iterator iterator = entries.iterator();
//    Map.Entry entry = null;
    QHashIterator<QString, QString> iterator(*parameters);
    while (iterator.hasNext()) {
        //entry = (Map.Entry)iterator.next();
        iterator.next();
        name = iterator.key();
        thisValue = iterator.value();
        thatValue = that->parameters->value(name);
        if ((thisValue == "") || (thatValue == "")) {
            // both null -> equal, only one null -> not equal
            if (thisValue != thatValue) {
                return false;
            }
        } else if (thisValue!=(thatValue)) {
            return false;
        }
    } // while iterator

    return true;
} // equals()

/**
 * A routine for parsing the parameter list out of a String.
 */
/*protected*/ void MimeTypeParameterList::parse(QString rawdata) throw (MimeTypeParseException) {
    int length = rawdata.length();
    if(length > 0) {
        int currentIndex = skipWhiteSpace(rawdata, 0);
        int lastIndex = 0;

        if(currentIndex < length) {
            QChar currentChar = rawdata.at(currentIndex);
            while ((currentIndex < length) && (currentChar == ';')) {
                QString name;
                QString value;
                bool foundit;

                //    eat the ';'
                ++currentIndex;

                //    now parse the parameter name

                //    skip whitespace
                currentIndex = skipWhiteSpace(rawdata, currentIndex);

                if(currentIndex < length) {
                    //    find the end of the token char run
                    lastIndex = currentIndex;
                    currentChar = rawdata.at(currentIndex);
                    while((currentIndex < length) && isTokenChar(currentChar)) {
                        ++currentIndex;
                        currentChar = rawdata.at(currentIndex);
                    }
                    name = rawdata.mid(lastIndex, currentIndex-lastIndex).toLower();

                    //    now parse the '=' that separates the name from the value

                    //    skip whitespace
                    currentIndex = skipWhiteSpace(rawdata, currentIndex);

                    if((currentIndex < length) && (rawdata.at(currentIndex) == '='))  {
                        //    eat it and parse the parameter value
                        ++currentIndex;

                        //    skip whitespace
                        currentIndex = skipWhiteSpace(rawdata, currentIndex);

                        if(currentIndex < length) {
                            //    now find out whether or not we have a quoted value
                            currentChar = rawdata.at(currentIndex);
                            if(currentChar == '"') {
                                //    yup it's quoted so eat it and capture the quoted string
                                ++currentIndex;
                                lastIndex = currentIndex;

                                if(currentIndex < length) {
                                    //    find the next unescqped quote
                                    foundit = false;
                                    while((currentIndex < length) && !foundit) {
                                        currentChar = rawdata.at(currentIndex);
                                        if(currentChar == '\\') {
                                            //    found an escape sequence so pass this and the next character
                                            currentIndex += 2;
                                        } else if(currentChar == '"') {
                                            //    foundit!
                                            foundit = true;
                                        } else {
                                            ++currentIndex;
                                        }
                                    }
                                    if(currentChar == '"') {
                                        value = unquote(rawdata.mid(lastIndex, currentIndex-lastIndex));
                                        //    eat the quote
                                        ++currentIndex;
                                    } else {
                                        log->error("Encountered unterminated quoted parameter value.");
                                        throw new MimeTypeParseException("Encountered unterminated quoted parameter value.");
                                    }
                                } else {
                                    log->error("Encountered unterminated quoted parameter value.");
                                    throw new MimeTypeParseException("Encountered unterminated quoted parameter value.");
                                }
                            } else if(isTokenChar(currentChar)) {
                                //    nope it's an ordinary token so it ends with a non-token char
                                lastIndex = currentIndex;
                                foundit = false;
                                while((currentIndex < length) && !foundit) {
                                    currentChar = rawdata.at(currentIndex);

                                    if(isTokenChar(currentChar)) {
                                        ++currentIndex;
                                    } else {
                                        foundit = true;
                                    }
                                }
                                value = rawdata.mid(lastIndex, currentIndex-lastIndex);
                            } else {
                                //    it ain't a value
                                log->error("Unexpected character encountered at index " + currentIndex);
                                throw new MimeTypeParseException("Unexpected character encountered at index " + currentIndex);
                            }

                            //    now put the data into the hashtable
                            parameters->insert(name, value);
                        } else {
                            log->error("Couldn't find a value for parameter named " + name);
                            throw new MimeTypeParseException("Couldn't find a value for parameter named " + name);
                        }
                    } else {
                        log->error("Couldn't find the '=' that separates a parameter name from its value.");
                        throw new MimeTypeParseException("Couldn't find the '=' that separates a parameter name from its value.");
                    }
                } else {
                    log->error("Couldn't find parameter name");
                    throw new MimeTypeParseException("Couldn't find parameter name");
                }

                //    setup the next iteration
                currentIndex = skipWhiteSpace(rawdata, currentIndex);
                if(currentIndex < length) {
                    currentChar = rawdata.at(currentIndex);
                }
            }
            if(currentIndex < length) {
                log->error("More characters encountered in input than expected.");
//                throw new MimeTypeParseException("More characters encountered in input than expected.");
            }
        }
    }
}

/**
 * return the number of name-value pairs in this list.
 */
/*public*/ int MimeTypeParameterList::size() {
    return parameters->size();
}

/**
 * Determine whether or not this list is empty.
 */
/*public*/ bool MimeTypeParameterList::isEmpty() {
    return parameters->isEmpty();
}

/**
 * Retrieve the value associated with the given name, or null if there
 * is no current association.
 */
/*public*/ QString MimeTypeParameterList::get(QString name) {
    return parameters->value(name.trimmed().toLower());
}

/**
 * Set the value to be associated with the given name, replacing
 * any previous association.
 */
/*public*/ void MimeTypeParameterList::set(QString name, QString value) {
    parameters->insert(name.trimmed().toLower(), value);
}

/**
 * Remove any value associated with the given name.
 */
/*public*/ void MimeTypeParameterList::remove(QString name) {
    parameters->remove(name.trimmed().toLower());
}

/**
 * Retrieve an enumeration of all the names in this list.
 */
/*public*/ QStringList MimeTypeParameterList::getNames() {
    return parameters->keys();
}

/*public*/ QString MimeTypeParameterList::toString() {
    // Heuristic: 8 characters per field
    //StringBuilder buffer = new StringBuilder(parameters.size() * 16);
    QString buffer = "";

    QStringListIterator _keys(parameters->keys());
    while(_keys.hasNext())
    {
        buffer.append("; ");

        QString key = _keys.next();
        buffer.append(key);
        buffer.append('=');
           buffer.append(quote(parameters->value(key)));
    }

    return buffer;
}

/**
 * @return a clone of this object
 */

 /*public*/ QObject* MimeTypeParameterList::clone() {
     MimeTypeParameterList* newObj = NULL;
//     try {
//         newObj = (MimeTypeParameterList*)clone();
     newObj = new MimeTypeParameterList();
//     } catch (CloneNotSupportedException cannotHappen) {
//     }
     newObj->parameters = /*(QHash<QString, QString>*)parameters->clone();*/new QHash<QString, QString>(*parameters);
     QHashIterator<QString, QString> iter(*parameters);
     while(iter.hasNext())
     {
      iter.next();
      newObj->parameters->insert(iter.key(),iter.value());
     }
     return newObj;
 }


//    below here be scary parsing related things

/**
 * Determine whether or not a given character belongs to a legal token.
 */
/*private*/ /*static*/ bool MimeTypeParameterList::isTokenChar(QChar c) {
    QString _TSPECIALS = "()<>@,;:\\\"/[]?=";
    return ((c > 040) && (c < 0177)) && (_TSPECIALS.indexOf(c) < 0);
}

/**
 * return the index of the first non white space character in
 * rawdata at or after index i.
 */
/*private*/ /*static*/ int MimeTypeParameterList::skipWhiteSpace(QString rawdata, int i) {
    int length = rawdata.length();
    if (i < length) {
        QChar c =  rawdata.at(i);
        while ((i < length) && c.isSpace()) {
            ++i;
            c = rawdata.at(i);
        }
    }

    return i;
}

/**
 * A routine that knows how and when to quote and escape the given value.
 */
/*private*/ /*static*/ QString MimeTypeParameterList::quote(QString value) {
    bool needsQuotes = false;

    //    check to see if we actually have to quote this thing
    int length = value.length();
    for(int i = 0; (i < length) && !needsQuotes; ++i) {
        needsQuotes = !isTokenChar(value.at(i));
    }

    if(needsQuotes) {
        //StringBuilder buffer = new StringBuilder((int)(length * 1.5));
        QString buffer = "";

        //    add the initial quote
        buffer.append('"');

        //    add the properly escaped text
        for(int i = 0; i < length; ++i) {
            QChar c = value.at(i);
            if((c == '\\') || (c == '"')) {
                buffer.append('\\');
            }
            buffer.append(c);
        }

        //    add the closing quote
        buffer.append('"');

        return buffer/*.toString()*/;
    }
    else
    {
        return value;
    }
}

/**
 * A routine that knows how to strip the quotes and escape sequences from the given value.
 */
/*private*/ /*static*/ QString MimeTypeParameterList::unquote(QString value) {
    int valueLength = value.length();
    //StringBuilder buffer = new StringBuilder(valueLength);
    QString buffer;

    bool escaped = false;
    for(int i = 0; i < valueLength; ++i) {
        QChar currentChar = value.at(i);
        if(!escaped && (currentChar != '\\')) {
            buffer.append(currentChar);
        } else if(escaped) {
            buffer.append(currentChar);
            escaped = false;
        } else {
            escaped = true;
        }
    }

    return buffer/*.toString()*/;
}

/**
 * A string that holds all the special chars.
 */
/*private*/ /*static*/ /*final*/ QString MimeTypeParameterList::TSPECIALS = "()<>@,;:\\\"/[]?=";
