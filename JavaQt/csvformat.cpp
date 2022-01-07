#include "csvformat.h"
#include <QVariant>
#include "exceptions.h"
#include "csvprinter.h"
#include "uncheckedioexception.h"

/**
 * Creates a customized CSV format.
 *
 * @param delimiter               the char used for value separation, must not be a line break character.
 * @param quoteChar               the Character used as value encapsulation marker, may be {@code null} to disable.
 * @param quoteMode               the quote mode.
 * @param commentStart            the Character used for comment identification, may be {@code null} to disable.
 * @param escape                  the Character used to escape special characters in values, may be {@code null} to disable.
 * @param ignoreSurroundingSpaces {@code true} when whitespaces enclosing values should be ignored.
 * @param ignoreEmptyLines        {@code true} when the parser should skip empty lines.
 * @param recordSeparator         the line separator to use for output.
 * @param nullString              the line separator to use for output.
 * @param headerComments          the comments to be printed by the Printer before the actual CSV data.
 * @param header                  the header
 * @param skipHeaderRecord        TODO Doc me.
 * @param allowMissingColumnNames TODO Doc me.
 * @param ignoreHeaderCase        TODO Doc me.
 * @param trim                    TODO Doc me.
 * @param trailingDelimiter       TODO Doc me.
 * @param autoFlush               TODO Doc me.
 * @param allowDuplicateHeaderNames TODO Doc me.
 * @throws IllegalArgumentException if the delimiter is a line break character.
 */

/*private*/ CSVFormat::CSVFormat(/*final*/ QString delimiter, /*final*/ QChar quoteChar, /*final*/ QuoteMode quoteMode, /*final*/  QChar commentStart, /*final*/  QChar escape,
           /*final*/  bool ignoreSurroundingSpaces, /*final*/  bool ignoreEmptyLines, /*final*/  QString recordSeparator, /*final*/  QString nullString,
           /*final*/  QVariantList headerComments, /*final*/  QStringList header, /*final*/  bool skipHeaderRecord, /*final*/  bool allowMissingColumnNames,
           /*final*/  bool ignoreHeaderCase, /*final*/  bool trim, /*final*/  bool trailingDelimiter, /*final*/  bool autoFlush,
           /*final*/  bool allowDuplicateHeaderNames, QObject* parent) {
       this->delimiter = delimiter;
       this->quoteCharacter = quoteChar;
       this->quoteMode = quoteMode;
       this->commentMarker = commentStart;
       this->escapeCharacter = escape;
       this->ignoreSurroundingSpaces = ignoreSurroundingSpaces;
       this->allowMissingColumnNames = allowMissingColumnNames;
       this->ignoreEmptyLines = ignoreEmptyLines;
       this->recordSeparator = recordSeparator;
       this->nullString = nullString;
       this->headerComments = toStringArray(headerComments);
       this->header = QStringList(header); //clone(header);
       this->skipHeaderRecord = skipHeaderRecord;
       this->ignoreHeaderCase = ignoreHeaderCase;
       this->trailingDelimiter = trailingDelimiter;
       this->trim = trim;
       this->autoFlush = autoFlush;
       this->quotedNullString = quoteCharacter + nullString + quoteCharacter;
       this->allowDuplicateHeaderNames = allowDuplicateHeaderNames;
       validate();
   }

/*public*/ /*static*/ /*final*/ CSVFormat* CSVFormat::DEFAULT = new CSVFormat(/*COMMA*/",", /*DOUBLE_QUOTE_CHAR*/'"', QuoteMode(),
           QChar(), QChar(), false, true, /*CRLF*/"\r\n", nullptr, QVariantList(), QStringList(),
           false, false, false,
           false, false, false, true);

/*static*/ QStringList CSVFormat::toStringArray(/*final*/ QVariantList values) {
    if (values.isEmpty()) {
        return QStringList();
    }
    /*final*/ QStringList strings = QStringList();//[values.length];
    for (int i = 0; i < values.length(); i++) {
        strings.append( values[i].toString());
    }
    return strings;
}

/**
     * Verifies the validity and consistency of the attributes, and throws an IllegalArgumentException if necessary.
     *
     * @throws IllegalArgumentException Throw when any attribute is invalid or inconsistent with other attributes.
     */
    /*private*/ void CSVFormat::validate() /*throws IllegalArgumentException*/ {

        if (containsLineBreak(delimiter)) {
            throw new IllegalArgumentException("The delimiter cannot be a line break");
        }
#if 0
        if (quoteCharacter != null && contains(delimiter, quoteCharacter.charValue())) {
            throw new IllegalArgumentException("The quoteChar character and the delimiter cannot be the same ('" + quoteCharacter + "')");
        }

        if (escapeCharacter != null && contains(delimiter, escapeCharacter.charValue())) {
            throw new IllegalArgumentException("The escape character and the delimiter cannot be the same ('" + escapeCharacter + "')");
        }

        if (commentMarker != null && contains(delimiter, commentMarker.charValue())) {
            throw new IllegalArgumentException("The comment start character and the delimiter cannot be the same ('" + commentMarker + "')");
        }

        if (quoteCharacter != null && quoteCharacter.equals(commentMarker)) {
            throw new IllegalArgumentException("The comment start character and the quoteChar cannot be the same ('" + commentMarker + "')");
        }

        if (escapeCharacter != null && escapeCharacter.equals(commentMarker)) {
            throw new IllegalArgumentException("The comment start and the escape character cannot be the same ('" + commentMarker + "')");
        }

        if (escapeCharacter == null && quoteMode == QuoteMode.NONE) {
            throw new IllegalArgumentException("No quotes mode set but no escape character is set");
        }

        // validate header
        if (header != null && !allowDuplicateHeaderNames) {
            final Set<String> dupCheck = new HashSet<>();
            for (final String hdr : header) {
                if (!dupCheck.add(hdr)) {
                    throw new IllegalArgumentException("The header contains a duplicate entry: '" + hdr + "' in " + Arrays.toString(header));
                }
            }
        }
#endif
}

/**
 * Returns true if the given string contains the search char.
 *
 * @param source the string to check.
 * @param searchCh the character to search.
 *
 * @return true if {@code c} contains a line break character
 */
/*private*/ /*static*/ bool CSVFormat::contains(/*final*/ QString source, /*final*/ QChar searchCh) {
    //return Objects.requireNonNull(source, "source").indexOf(searchCh) >= 0;
 return source.contains(searchCh);
}

/**
 * Returns true if the given string contains a line break character.
 *
 * @param source the string to check.
 *
 * @return true if {@code c} contains a line break character.
 */
/*private*/ /*static*/ bool CSVFormat::containsLineBreak(/*final*/ QString source) {
    return contains(source, /*CR*/'\r') || contains(source, /*LF*/'\n');
}

/**
 * Prints to the specified output.
 *
 * <p>
 * See also {@link CSVPrinter}.
 * </p>
 *
 * @param out the output.
 * @return a printer to an output.
 * @throws IOException thrown if the optional header cannot be printed.
 */
/*public*/ CSVPrinter* CSVFormat::print(/*final*/ QTextStream* out) /*throws IOException*/ {
    return new CSVPrinter(out, this);
}
/**
 * Outputs the trailing delimiter (if set) followed by the record separator (if set).
 *
 * @param appendable where to write
 * @throws IOException If an I/O error occurs.
 * @since 1.4
 */
/*public*/ void CSVFormat::println(/*final*/ QTextStream* appendable) /*throws IOException*/ {
    if (getTrailingDelimiter()) {
        append(getDelimiterString(), appendable);
    }
    if (recordSeparator != "") {
        append(recordSeparator, appendable);
    }
}
/**
 * Returns whether to add a trailing delimiter.
 *
 * @return whether to add a trailing delimiter.
 * @since 1.3
 */
/*public*/ bool CSVFormat::getTrailingDelimiter() {
    return trailingDelimiter;
}

/**
 * Returns the character delimiting the values (typically ";", "," or "\t").
 *
 * @return the delimiter.
 */
/*public*/ QString CSVFormat::getDelimiterString() {
    return delimiter;
}
/**
 * Returns whether to flush on close.
 *
 * @return whether to flush on close.
 * @since 1.6
 */
/*public*/ bool CSVFormat::getAutoFlush() {
    return autoFlush;
}
/**
 * Returns the escape character.
 *
 * @return the escape character, may be {@code null}
 */
/*public*/ QChar CSVFormat::getEscapeCharacter() {
    return escapeCharacter;
}

/*private*/ void CSVFormat::append(/*final*/ QChar c, /*final*/ QTextStream* appendable) /*throws IOException*/ {
    try {
        //appendable.append(c);
    *appendable << c;
    } catch (/*final*/ IOException* e) {
        throw new UncheckedIOException(e);
    }
}
/*private*/ void CSVFormat::append(/*final*/ QString csq, /*final*/ QTextStream* appendable) /*throws IOException*/ {
//       try {
        //appendable.append(csq);
    *appendable << csq;
    //} catch (final IOException e) {
    //    throw new UncheckedIOException(e);
    //}
}

/**
 * Prints the {@code value} as the next value on the line to {@code out}. The value will be escaped or encapsulated as needed. Useful when one wants to
 * avoid creating CSVPrinters. Trims the value if {@link #getTrim()} is true.
 *
 * @param value     value to output.
 * @param out       where to print the value.
 * @param newRecord if this a new record.
 * @throws IOException If an I/O error occurs.
 * @since 1.4
 */
/*public*/ void CSVFormat::print(/*final*/ QVariant value, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/ {
    // null values are considered empty
    // Only call CharSequence.toString() if you have to, helps GC-free use cases.
#if 0
    CharSequence charSequence;
    if (value == null) {
        // https://issues.apache.org/jira/browse/CSV-203
        if (null == nullString) {
            charSequence = EMPTY;
        } else if (QuoteMode.ALL == quoteMode) {
            charSequence = quotedNullString;
        } else {
            charSequence = nullString;
        }
    } else if (value instanceof CharSequence) {
        charSequence = (CharSequence) value;
    } else if (value instanceof Reader) {
        print((Reader) value, out, newRecord);
        return;
    } else {
        charSequence = value.toString();
    }
    charSequence = getTrim() ? trim(charSequence) : charSequence;
    print(value, charSequence, out, newRecord);
#else
 print(QVariant(), value.toString().trimmed(), out, newRecord);
#endif
}

/*private*/ void CSVFormat::print(/*final*/ QVariant object, /*final*/ QString value, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/ {
    /*final*/ int offset = 0;
    /*final*/ int len = value.length();
    if (!newRecord) {
        //out.append(getDelimiterString());
     *out << getDelimiterString();
    }
    if (object.isNull()) {
       // out.append(value);
     *out << value;
    }
    else if (isQuoteCharacterSet()) {
        // the original object is needed so can check for Number
        printWithQuotes(object, value, out, newRecord);
    } else if (isEscapeCharacterSet()) {
        printWithEscapes(value, out);
    } else {
        //out.append(value, offset, len);
        *out << value.mid(offset, len);
    }
}

/**
 * Returns whether a quoteChar has been defined.
 *
 * @return {@code true} if a quoteChar is defined
 */
/*public*/ bool CSVFormat::isQuoteCharacterSet() {
    return !quoteCharacter.isNull();
}

/**
 * Returns whether escape are being processed.
 *
 * @return {@code true} if escapes are processed
 */
/*public*/ bool CSVFormat::isEscapeCharacterSet() {
    return !escapeCharacter.isNull();
}

/**
 * Returns the character used to encapsulate values containing special characters.
 *
 * @return the quoteChar character, may be {@code null}
 */
/*public*/ QChar CSVFormat::getQuoteCharacter() {
    return quoteCharacter;
}

/**
 * Returns the quote policy output fields.
 *
 * @return the quote policy
 */
/*public*/ CSVFormat::QuoteMode CSVFormat::getQuoteMode() {
    return quoteMode;
}


/*
 * Note: Must only be called if escaping is enabled, otherwise will generate NPE.
 */
/*private*/ void CSVFormat::printWithEscapes(/*final*/ QString charSeq, /*final*/ QTextStream* appendable) /*throws IOException*/ {
    int start = 0;
    int pos = 0;
    /*final*/ int end = charSeq.length();

    /*final*/ QByteArray delim = getDelimiterString().toLocal8Bit();
    /*final*/ int delimLength = delim.length();
    /*final*/ char escape = getEscapeCharacter().toLatin1();

    while (pos < end) {
        QChar c = charSeq.at(pos);
        /*final*/ bool isDelimiterStart = isDelimiter(c, charSeq, pos, delim, delimLength);
        if (c == CR || c == LF || c == escape || isDelimiterStart) {
            // write out segment up until this char
            if (pos > start) {
                //appendable.append(charSeq, start, pos);
             *appendable << charSeq.mid(start, pos-start +1);
            }
            if (c == LF) {
                c = 'n';
            } else if (c == CR) {
                c = 'r';
            }

            //appendable.append(escape);
            *appendable << escape;
            //appendable.append(c);
            *appendable << c;

            if (isDelimiterStart) {
                for (int i = 1; i < delimLength; i++) {
                    pos++;
                    c = charSeq.at(pos);
                    //appendable.append(escape);
                    *appendable << escape;
                    //appendable.append(c);
                    *appendable << c;
                }
            }

            start = pos + 1; // start on the current char after this one
        }
        pos++;
    }

    // write last segment
    if (pos > start) {
        //appendable.append(charSeq, start, pos);
     *appendable << charSeq.mid(start, pos - start +1);
    }
}
#if 0
/*private*/ void printWithEscapes(final Reader reader, final Appendable appendable) throws IOException {
    int start = 0;
    int pos = 0;

    @SuppressWarnings("resource") // Temp reader on input reader.
    final ExtendedBufferedReader bufferedReader = new ExtendedBufferedReader(reader);
    final char[] delim = getDelimiterString().toCharArray();
    final int delimLength = delim.length;
    final char escape = getEscapeCharacter().charValue();
    final StringBuilder builder = new StringBuilder(IOUtils.DEFAULT_BUFFER_SIZE);

    int c;
    while (-1 != (c = bufferedReader.read())) {
        builder.append((char) c);
        final boolean isDelimiterStart = isDelimiter((char) c, builder.toString() + new String(bufferedReader.lookAhead(delimLength - 1)), pos, delim,
                delimLength);
        if (c == CR || c == LF || c == escape || isDelimiterStart) {
            // write out segment up until this char
            if (pos > start) {
                append(builder.substring(start, pos), appendable);
                builder.setLength(0);
                pos = -1;
            }
            if (c == LF) {
                c = 'n';
            } else if (c == CR) {
                c = 'r';
            }

            append(escape, appendable);
            append((char) c, appendable);

            if (isDelimiterStart) {
                for (int i = 1; i < delimLength; i++) {
                    c = bufferedReader.read();
                    append(escape, appendable);
                    append((char) c, appendable);
                }
            }

            start = pos + 1; // start on the current char after this one
        }
        pos++;
    }

    // write last segment
    if (pos > start) {
        append(builder.substring(start, pos), appendable);
    }
}
#endif
/*
 * Note: must only be called if quoting is enabled, otherwise will generate NPE
 */
// the original object is needed so can check for Number
/*private*/ void CSVFormat::printWithQuotes(/*final*/ QVariant object, /*final*/ QString charSeq, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/ {
    bool quote = false;
    int start = 0;
    int pos = 0;
    /*final*/ int len = charSeq.length();

    /*final*/ QByteArray delim = getDelimiterString().toLocal8Bit();
    /*final*/ int delimLength = delim.length();
    /*final*/ char quoteChar = getQuoteCharacter().toLatin1();
    // If escape char not specified, default to the quote char
    // This avoids having to keep checking whether there is an escape character
    // at the cost of checking against quote twice
    /*final*/ QChar escapeChar = isEscapeCharacterSet() ? getEscapeCharacter()/*.charValue()*/ : quoteChar;

    QuoteMode quoteModePolicy = getQuoteMode();
    if (!quoteModePolicy) {
        quoteModePolicy = QuoteMode::MINIMAL;
    }
    switch (quoteModePolicy) {
    case ALL:
    case ALL_NON_NULL:
        quote = true;
        break;
    case NON_NUMERIC:
        quote = !object.canConvert<int>();//!(object instanceof Number);
        break;
    case NONE:
        // Use the existing escaping code
        printWithEscapes(charSeq, out);
        return;
    case MINIMAL:
        if (len <= 0) {
            // always quote an empty token that is the first
            // on the line, as it may be the only thing on the
            // line. If it were not quoted in that case,
            // an empty line has no tokens.
            if (newRecord) {
                quote = true;
            }
        } else {
            QChar c = charSeq.at(pos);

            if (c <= COMMENT) {
                // Some other chars at the start of a value caused the parser to fail, so for now
                // encapsulate if we start in anything less than '#'. We are being conservative
                // by including the default comment char too.
                quote = true;
            } else {
                while (pos < len) {
                    c = charSeq.at(pos);
                    if (c == LF || c == CR || c == quoteChar || c == escapeChar || isDelimiter(c, charSeq, pos, delim, delimLength)) {
                        quote = true;
                        break;
                    }
                    pos++;
                }

                if (!quote) {
                    pos = len - 1;
                    c = charSeq.at(pos);
                    // Some other chars at the end caused the parser to fail, so for now
                    // encapsulate if we end in anything less than ' '
                    if (c <= SP) {
                        quote = true;
                    }
                }
            }
        }

        if (!quote) {
            // no encapsulation needed - write out the original value
            //out.append(charSeq, start, len);
         *out << charSeq.mid(start);
            return;
        }
        break;
    default:
        throw new IllegalStateException("Unexpected Quote value: " + quoteModePolicy);
    }

    if (!quote) {
        // no encapsulation needed - write out the original value
        //out.append(charSeq, start, len);
     *out << charSeq.mid(start);
        return;
    }

    // we hit something that needed encapsulation
    //out.append(quoteChar);
    *out << quoteChar;

    // Pick up where we left off: pos should be positioned on the first character that caused
    // the need for encapsulation.
    while (pos < len) {
        /*final*/ QChar c = charSeq.at(pos);
        if (c == quoteChar || c == escapeChar) {
            // write out the chunk up until this point
            //out.append(charSeq, start, pos);
         *out << charSeq.mid(start, pos-start +1);
            //out.append(escapeChar); // now output the escape
         *out << escapeChar;
            start = pos; // and restart with the matched char
        }
        pos++;
    }

    // write the last segment
    //out.append(charSeq, start, pos);
    *out << charSeq.mid(start, pos-start +1);
    //out.append(quoteChar);
    *out << quoteChar;
}

/*private*/ bool CSVFormat::isDelimiter(/*final*/ QChar ch, /*final*/ /*CharSequence*/QString charSeq, /*final*/ int startIndex, /*final*/ QString delimiter, /*final*/ int delimiterLength) {
    if (ch != delimiter[0]) {
        return false;
    }
    /*final*/ int len = charSeq.length();
    if (startIndex + delimiterLength > len) {
        return false;
    }
    for (int i = 1; i < delimiterLength; i++) {
        if (charSeq.at(startIndex + i) != delimiter[i]) {
            return false;
        }
    }
    return true;
}
