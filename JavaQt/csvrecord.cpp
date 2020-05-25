#include "csvrecord.h"
#include "csvparser.h"

/**
 * A CSV record parsed from a CSV file.
 *
 * <p>
 * Note: Support for {@link Serializable} is scheduled to be removed in version 2.0.
 * In version 1.8 the mapping between the column header and the column index was
 * removed from the serialised state. The class maintains serialization compatibility
 * with versions pre-1.8 for the record values; these must be accessed by index
 * following deserialization. There will be loss of any functionally linked to the header
 * mapping when transferring serialised forms pre-1.8 to 1.8 and vice versa.
 * </p>
 */
// /*public*/ final class CSVRecord implements Serializable, Iterable<String> {


    CSVRecord::CSVRecord(/*final*/ CSVParser* parser, /*final*/ QStringList values, /*final*/ QString comment, /*final*/ long recordNumber,
            /*final*/ long characterPosition, QObject *parent) : QObject(parent) {
        this->recordNumber = recordNumber;
        this->values = !values.isEmpty() ? values : EMPTY_STRING_ARRAY;
        this->parser = parser;
        this->comment = comment;
        this->characterPosition = characterPosition;
    }
#if 0
    /**
     * Returns a value by {@link Enum}.
     *
     * @param e
     *            an enum
     * @return the String at the given enum String
     */
    /*public*/ QString get(final Enum<?> e) {
        return get(Objects.toString(e, null));
    }
#endif
    /**
     * Returns a value by index.
     *
     * @param i
     *            a column index (0-based)
     * @return the String at the given index
     */
    /*public*/ QString CSVRecord::get(/*final*/ int i) {
        return values[i];
    }

    /**
     * Returns a value by name.
     *
     * <p>
     * Note: This requires a field mapping obtained from the original parser.
     * A check using {@link #isMapped(String)} should be used to determine if a
     * mapping exists from the provided {@code name} to a field index. In this case an
     * exception will only be thrown if the record does not contain a field corresponding
     * to the mapping, that is the record length is not consistent with the mapping size.
     * </p>
     *
     * @param name
     *            the name of the column to be retrieved.
     * @return the column value, maybe null depending on {@link CSVFormat#getNullString()}.
     * @throws IllegalStateException
     *             if no header mapping was provided
     * @throws IllegalArgumentException
     *             if {@code name} is not mapped or if the record is inconsistent
     * @see #isMapped(String)
     * @see #isConsistent()
     * @see #getParser()
     * @see CSVFormat#withNullString(String)
     */
    /*public*/ QString CSVRecord::get(/*final*/ QString name) {
        /*final*/ QMap<QString, int>* headerMap = getHeaderMapRaw();
        if (headerMap == nullptr) {
            throw  IllegalStateException(
                "No header mapping was specified, the record values can't be accessed by name");
        }
        /*final*/ int index = headerMap->value(name);
        if (index == 0) {
            throw  IllegalArgumentException(tr("Mapping for %1 not found, expected one of %2").arg(name).arg(
                headerMap->keys().join('|')));
        }
        try {
            return values[index/*.intValue()*/];
        } catch (/*final*/ ArrayIndexOutOfBoundsException e) {
            throw  IllegalArgumentException(tr(
                "Index for header '%1' is %2 but CSVRecord only has %3 values!").arg(name).arg(index).arg(
                values.length()));
        }
    }

    /**
     * Returns the start position of this record as a character position in the source stream. This may or may not
     * correspond to the byte position depending on the character set.
     *
     * @return the position of this record in the source stream.
     */
    /*public*/ long CSVRecord::getCharacterPosition() {
        return characterPosition;
    }

    /**
     * Returns the comment for this record, if any.
     * Note that comments are attached to the following record.
     * If there is no following record (i.e. the comment is at EOF)
     * the comment will be ignored.
     *
     * @return the comment for this record, or null if no comment for this record is available.
     */
    /*public*/ QString CSVRecord::getComment() {
        return comment;
    }

    /*private*/ QMap<QString, int>* CSVRecord::getHeaderMapRaw() {
        return parser == nullptr ? nullptr : parser->getHeaderMapRaw();
    }
#if 0
    /**
     * Returns the parser.
     *
     * <p>
     * Note: The parser is not part of the serialized state of the record. A null check
     * should be used when the record may have originated from a serialized form.
     * </p>
     *
     * @return the parser.
     * @since 1.7
     */
    /*public*/ CSVParser getParser() {
        return parser;
    }

    /**
     * Returns the number of this record in the parsed CSV file.
     *
     * <p>
     * <strong>ATTENTION:</strong> If your CSV input has multi-line values, the returned number does not correspond to
     * the current line number of the parser that created this record.
     * </p>
     *
     * @return the number of this record.
     * @see CSVParser#getCurrentLineNumber()
     */
    /*public*/ long getRecordNumber() {
        return recordNumber;
    }

    /**
     * Checks whether this record has a comment, false otherwise.
     * Note that comments are attached to the following record.
     * If there is no following record (i.e. the comment is at EOF)
     * the comment will be ignored.
     *
     * @return true if this record has a comment, false otherwise
     * @since 1.3
     */
    /*public*/ boolean hasComment() {
        return comment != null;
    }

    /**
     * Tells whether the record size matches the header size.
     *
     * <p>
     * Returns true if the sizes for this record match and false if not. Some programs can export files that fail this
     * test but still produce parsable files.
     * </p>
     *
     * @return true of this record is valid, false if not
     */
    /*public*/ boolean isConsistent() {
        final Map<String, Integer> headerMap = getHeaderMapRaw();
        return headerMap == null || headerMap.size() == values.length;
    }

    /**
     * Checks whether a given column is mapped, i.e. its name has been defined to the parser.
     *
     * @param name
     *            the name of the column to be retrieved.
     * @return whether a given column is mapped.
     */
    /*public*/ boolean isMapped(final String name) {
        final Map<String, Integer> headerMap = getHeaderMapRaw();
        return headerMap != null && headerMap.containsKey(name);
    }

    /**
     * Checks whether a given columns is mapped and has a value.
     *
     * @param name
     *            the name of the column to be retrieved.
     * @return whether a given columns is mapped and has a value
     */
    /*public*/ boolean isSet(final String name) {
        return isMapped(name) && getHeaderMapRaw().get(name).intValue() < values.length;
    }

    /**
     * Checks whether a column with given index has a value.
     *
     * @param index
     *         a column index (0-based)
     * @return whether a column with given index has a value
     */
    /*public*/ boolean isSet(final int index) {
        return 0 <= index && index < values.length;
    }

    /**
     * Returns an iterator over the values of this record.
     *
     * @return an iterator over the values of this record.
     */
    @Override
    /*public*/ Iterator<String> iterator() {
        return toList().iterator();
    }

    /**
     * Puts all values of this record into the given Map.
     *
     * @param map
     *            The Map to populate.
     * @return the given map.
     * @since 1.9
     */
    /*public*/ <M extends Map<String, String>> M putIn(final M map) {
        if (getHeaderMapRaw() == null) {
            return map;
        }
        for (final Entry<String, Integer> entry : getHeaderMapRaw().entrySet()) {
            final int col = entry.getValue().intValue();
            if (col < values.length) {
                map.put(entry.getKey(), values[col]);
            }
        }
        return map;
    }

    /**
     * Returns the number of values in this record.
     *
     * @return the number of values.
     */
    /*public*/ int size() {
        return values.length;
    }

    /**
     * Converts the values to a List.
     *
     * TODO: Maybe make this /*public*/?
     *
     * @return a new List
     */
    /*private*/ List<String> toList() {
        return Arrays.asList(values);
    }

    /**
     * Copies this record into a new Map of header name to record value.
     *
     * @return A new Map. The map is empty if the record has no headers.
     */
    /*public*/ Map<String, String> toMap() {
        return putIn(new LinkedHashMap<String, String>(values.length));
    }

    /**
     * Returns a string representation of the contents of this record. The result is constructed by comment, mapping,
     * recordNumber and by passing the internal values array to {@link Arrays#toString(Object[])}.
     *
     * @return a String representation of this record.
     */
    @Override
    /*public*/ String toString() {
        return "CSVRecord [comment='" + comment + "', recordNumber=" + recordNumber + ", values=" +
            Arrays.toString(values) + "]";
    }

    String[] values() {
        return values;
    }

#endif
