#include "csvparser.h"
#include "file.h"
#include <QTextStream>
#include <QFile>

/**
 * Parses CSV files according to the specified format.
 *
 * Because CSV appears in many different dialects, the parser supports many formats by allowing the
 * specification of a {@link CSVFormat}.
 *
 * The parser works record wise. It is not possible to go back, once a record has been parsed from the input stream.
 *
 * <h2>Creating instances</h2>
 * <p>
 * There are several static factory methods that can be used to create instances for various types of resources:
 * </p>
 * <ul>
 *     <li>{@link #parse(java.io.File, Charset, CSVFormat)}</li>
 *     <li>{@link #parse(String, CSVFormat)}</li>
 *     <li>{@link #parse(java.net.URL, java.nio.charset.Charset, CSVFormat)}</li>
 * </ul>
 * <p>
 * Alternatively parsers can also be created by passing a {@link Reader} directly to the sole constructor.
 *
 * For those who like fluent APIs, parsers can be created using {@link CSVFormat#parse(java.io.Reader)} as a shortcut:
 * </p>
 * <pre>
 * for(CSVRecord record : CSVFormat.EXCEL.parse(in)) {
 *     ...
 * }
 * </pre>
 *
 * <h2>Parsing record wise</h2>
 * <p>
 * To parse a CSV input from a file, you write:
 * </p>
 *
 * <pre>
 * File csvData = new File(&quot;/path/to/csv&quot;);
 * CSVParser parser = CSVParser.parse(csvData, CSVFormat.RFC4180);
 * for (CSVRecord csvRecord : parser) {
 *     ...
 * }
 * </pre>
 *
 * <p>
 * This will read the parse the contents of the file using the
 * <a href="http://tools.ietf.org/html/rfc4180" target="_blank">RFC 4180</a> format.
 * </p>
 *
 * <p>
 * To parse CSV input in a format like Excel, you write:
 * </p>
 *
 * <pre>
 * CSVParser parser = CSVParser.parse(csvData, CSVFormat.EXCEL);
 * for (CSVRecord csvRecord : parser) {
 *     ...
 * }
 * </pre>
 *
 * <p>
 * If the predefined formats don't match the format at hands, custom formats can be defined. More information about
 * customising CSVFormats is available in {@link CSVFormat CSVFormat Javadoc}.
 * </p>
 *
 * <h2>Parsing into memory</h2>
 * <p>
 * If parsing record wise is not desired, the contents of the input can be read completely into memory.
 * </p>
 *
 * <pre>
 * Reader in = new StringReader(&quot;a;b\nc;d&quot;);
 * CSVParser parser = new CSVParser(in, CSVFormat.EXCEL);
 * List&lt;CSVRecord&gt; list = parser.getRecords();
 * </pre>
 *
 * <p>
 * There are two constraints that have to be kept in mind:
 * </p>
 *
 * <ol>
 *     <li>Parsing into memory starts at the current position of the parser. If you have already parsed records from
 *     the input, those records will not end up in the in memory representation of your CSV data.</li>
 *     <li>Parsing into memory may consume a lot of system resources depending on the input. For example if you're
 *     parsing a 150MB file of CSV data the contents will be read completely into memory.</li>
 * </ol>
 *
 * <h2>Notes</h2>
 * <p>
 * Internal parser state is completely covered by the format and the reader-state.
 * </p>
 *
 * @see <a href="package-summary.html">package documentation for more details</a>
 */
///*public*/ final class CSVParser implements Iterable<CSVRecord>, Closeable {

//    class CSVRecordIterator implements Iterator<CSVRecord> {
//        /*public*/ CSVRecord current;

        /*public*/ CSVRecord* CSVRecordIterator::getNextRecord() {
            try {
                return CSVParser.this.nextRecord();
            } catch (/*final*/ IOException e) {
                throw new IllegalStateException(
                        e.getClass().getSimpleName() + " reading next record: " + e.toString(), e);
            }
        }

        //@Override
        /*public*/ bool CSVRecordIterator::hasNext() {
            if (CSVParser.this.isClosed()) {
                return false;
            }
            if (this.current == null) {
                this.current = this.getNextRecord();
            }

            return this.current != null;
        }

        //@Override
        /*public*/ CSVRecord* CSVRecordIterator::next() {
            if (CSVParser.this.isClosed()) {
                throw new NoSuchElementException("CSVParser has been closed");
            }
            CSVRecord next = this.current;
            this.current = null;

            if (next == null) {
                // hasNext() wasn't called before
                next = this.getNextRecord();
                if (next == null) {
                    throw new NoSuchElementException("No more CSV records available");
                }
            }

            return next;
        }

        //@Override
        /*public*/ void CSVRecordIterator::remove() {
            throw new UnsupportedOperationException();
        }
//    }
#if 0
    /**
     * Creates a parser for the given {@link File}.
     *
     * @param file
     *            a CSV file. Must not be null.
     * @param charset
     *            A Charset
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new parser
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either file or format are null.
     * @throws IOException
     *             If an I/O error occurs
     */
    @SuppressWarnings("resource")
    /*public*/ /*static*/ CSVParser::CSVParser parse(/*final*/ File* file, /*final*/ Charset charset, /*final*/ CSVFormat* format, QObject *parent) throw (IOException) {
//        Assertions.notNull(file, "file");
//        Assertions.notNull(format, "format");
        QFile* f = QFile(file->getPath());
        if(!f->open(QIODevice::ReadOnly))
         throw FileNotFoundException(tr("error opening file '%1'").arg(file->getPath()));
        return new CSVParser(new QTextStream(f/*new FileInputStream(file), charset), format*/));
    }

    /**
     * Creates a CSV parser using the given {@link CSVFormat}.
     *
     * <p>
     * If you do not read all records from the given {@code reader}, you should call {@link #close()} on the parser,
     * unless you close the {@code reader}.
     * </p>
     *
     * @param inputStream
     *            an InputStream containing CSV-formatted input. Must not be null.
     * @param charset
     *            a Charset.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new CSVParser configured with the given reader and format.
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either reader or format are null.
     * @throws IOException
     *             If there is a problem reading the header or skipping the first record
     * @since 1.5
     */
    //@SuppressWarnings("resource")
    /*public*/ /*static*/ CSVParser parse(/*final*/ QTextStream inputStream, /*final Charset charset, final CSVFormat* format*/)
            throw (IOException) {
//        Assertions.notNull(inputStream, "inputStream");
//        Assertions.notNull(format, "format");
        return parse(new InputStreamReader(inputStream, charset), format);
    }

    /**
     * Creates a parser for the given {@link Path}.
     *
     * @param path
     *            a CSV file. Must not be null.
     * @param charset
     *            A Charset
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new parser
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either file or format are null.
     * @throws IOException
     *             If an I/O error occurs
     * @since 1.5
     */
    /*public*/ static CSVParser parse(final Path path, final Charset charset, final CSVFormat format) throws IOException {
        Assertions.notNull(path, "path");
        Assertions.notNull(format, "format");
        return parse(Files.newInputStream(path), charset, format);
    }

    /**
     * Creates a CSV parser using the given {@link CSVFormat}
     *
     * <p>
     * If you do not read all records from the given {@code reader}, you should call {@link #close()} on the parser,
     * unless you close the {@code reader}.
     * </p>
     *
     * @param reader
     *            a Reader containing CSV-formatted input. Must not be null.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new CSVParser configured with the given reader and format.
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either reader or format are null.
     * @throws IOException
     *             If there is a problem reading the header or skipping the first record
     * @since 1.5
     */
    /*public*/ static CSVParser parse(final Reader reader, final CSVFormat format) throws IOException {
        return new CSVParser(reader, format);
    }

    /**
     * Creates a parser for the given {@link String}.
     *
     * @param string
     *            a CSV string. Must not be null.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new parser
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either string or format are null.
     * @throws IOException
     *             If an I/O error occurs
     */
    /*public*/ static CSVParser parse(final String string, final CSVFormat format) throws IOException {
        Assertions.notNull(string, "string");
        Assertions.notNull(format, "format");

        return new CSVParser(new StringReader(string), format);
    }

    // the following objects are shared to reduce garbage

    /**
     * Creates a parser for the given URL.
     *
     * <p>
     * If you do not read all records from the given {@code url}, you should call {@link #close()} on the parser, unless
     * you close the {@code url}.
     * </p>
     *
     * @param url
     *            a URL. Must not be null.
     * @param charset
     *            the charset for the resource. Must not be null.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @return a new parser
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either url, charset or format are null.
     * @throws IOException
     *             If an I/O error occurs
     */
    /*public*/ static CSVParser parse(final URL url, final Charset charset, final CSVFormat format) throws IOException {
        Assertions.notNull(url, "url");
        Assertions.notNull(charset, "charset");
        Assertions.notNull(format, "format");

        return new CSVParser(new InputStreamReader(url.openStream(), charset), format);
    }


#endif
    /**
     * Customized CSV parser using the given {@link CSVFormat}
     *
     * <p>
     * If you do not read all records from the given {@code reader}, you should call {@link #close()} on the parser,
     * unless you close the {@code reader}.
     * </p>
     *
     * @param reader
     *            a Reader containing CSV-formatted input. Must not be null.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either reader or format are null.
     * @throws IOException
     *             If there is a problem reading the header or skipping the first record
     */
    /*public*/ CSVParser(/*final*/ QTextStream reader, /*final*/ CSVFormat format) throw (IOException) {
        this(reader, format, 0, 1);
    }
#endif
    /**
     * Customized CSV parser using the given {@link CSVFormat}
     *
     * <p>
     * If you do not read all records from the given {@code reader}, you should call {@link #close()} on the parser,
     * unless you close the {@code reader}.
     * </p>
     *
     * @param reader
     *            a Reader containing CSV-formatted input. Must not be null.
     * @param format
     *            the CSVFormat used for CSV parsing. Must not be null.
     * @param characterOffset
     *            Lexer offset when the parser does not start parsing at the beginning of the source.
     * @param recordNumber
     *            The next record number to assign
     * @throws IllegalArgumentException
     *             If the parameters of the format are inconsistent or if either reader or format are null.
     * @throws IOException
     *             If there is a problem reading the header or skipping the first record
     * @since 1.1
     */
    //@SuppressWarnings("resource")
    /*public*/ CSVParser::CSVParser(/*final*/ QTextStream* reader, /*final*/ CSVFormat format, /*final*/ long characterOffset, /*final*/ long recordNumber)
        throw (IOException) {
//        Assertions.notNull(reader, "reader");
//        Assertions.notNull(format, "format");

        this->format = format;
//        this.lexer = new Lexer(format, new ExtendedBufferedReader(reader));
        this->csvRecordIterator = new CSVRecordIterator();
        /*final*/ Headers headers = createHeaders();
        this->headerMap = headers.headerMap;
        this->headerNames = headers.headerNames;
        this->characterOffset = characterOffset;
        this->recordNumber = recordNumber - 1;
    }
#if 0
    /*public*/ void addRecordValue(final boolean lastRecord) {
        final String input = this.reusableToken.content.toString();
        final String inputClean = this.format.getTrim() ? input.trim() : input;
        if (lastRecord && inputClean.isEmpty() && this.format.getTrailingDelimiter()) {
            return;
        }
        final String nullString = this.format.getNullString();
        this.recordList.add(inputClean.equals(nullString) ? null : inputClean);
    }

    /**
     * Closes resources.
     *
     * @throws IOException
     *             If an I/O error occurs
     */
    //@Override
    /*public*/ void close() throw IOException {
//        if (this.lexer != null) {
//            this.lexer.close();
//        }
    }

    /*public*/ Map<String, Integer> createEmptyHeaderMap() {
        return this.format.getIgnoreHeaderCase() ?
                new TreeMap<>(String.CASE_INSENSITIVE_ORDER) :
                new LinkedHashMap<>();
    }

    /**
     * Header information based on name and position.
     */
    /*public*/ static final class Headers {
        /**
         * Header column positions (0-based)
         */
        final Map<String, Integer> headerMap;

        /**
         * Header names in column order
         */
        final List<String> headerNames;

        Headers(final Map<String, Integer> headerMap, final List<String> headerNames) {
            this.headerMap = headerMap;
            this.headerNames = headerNames;
        }
    }

    /**
     * Creates the name to index mapping if the format defines a header.
     *
     * @return null if the format has no header.
     * @throws IOException if there is a problem reading the header or skipping the first record
     */
    /*public*/ Headers createHeaders() throws IOException {
        Map<String, Integer> hdrMap = null;
        List<String> headerNames = null;
        final String[] formatHeader = this.format.getHeader();
        if (formatHeader != null) {
            hdrMap = createEmptyHeaderMap();
            String[] headerRecord = null;
            if (formatHeader.length == 0) {
                // read the header from the first line of the file
                final CSVRecord nextRecord = this.nextRecord();
                if (nextRecord != null) {
                    headerRecord = nextRecord.values();
                }
            } else {
                if (this.format.getSkipHeaderRecord()) {
                    this.nextRecord();
                }
                headerRecord = formatHeader;
            }

            // build the name to index mappings
            if (headerRecord != null) {
                for (int i = 0; i < headerRecord.length; i++) {
                    final String header = headerRecord[i];
                    final boolean emptyHeader = header == null || header.trim().isEmpty();
                    if (emptyHeader && !this.format.getAllowMissingColumnNames()) {
                        throw new IllegalArgumentException(
                            "A header name is missing in " + Arrays.toString(headerRecord));
                    }
                    // Note: This will always allow a duplicate header if the header is empty
                    final boolean containsHeader = header != null && hdrMap.containsKey(header);
                    if (containsHeader && !emptyHeader && !this.format.getAllowDuplicateHeaderNames()) {
                        throw new IllegalArgumentException(
                            String.format(
                                "The header contains a duplicate name: \"%s\" in %s. If this is valid then use CSVFormat.withAllowDuplicateHeaderNames().",
                                header, Arrays.toString(headerRecord)));
                    }
                    if (header != null) {
                        hdrMap.put(header, Integer.valueOf(i));
                        if (headerNames == null) {
                            headerNames = new ArrayList<>(headerRecord.length);
                        }
                        headerNames.add(header);
                    }
                }
            }
        }
        if (headerNames == null) {
            headerNames = Collections.emptyList(); //immutable
        } else {
            headerNames = Collections.unmodifiableList(headerNames);
        }
        return new Headers(hdrMap, headerNames);
    }

    /**
     * Returns the current line number in the input stream.
     *
     * <p>
     * <strong>ATTENTION:</strong> If your CSV input has multi-line values, the returned number does not correspond to
     * the record number.
     * </p>
     *
     * @return current line number
     */
    /*public*/ long getCurrentLineNumber() {
        return this.lexer.getCurrentLineNumber();
    }

    /**
     * Gets the first end-of-line string encountered.
     *
     * @return the first end-of-line string
     * @since 1.5
     */
    /*public*/ String getFirstEndOfLine() {
        return lexer.getFirstEol();
    }

    /**
     * Returns a copy of the header map.
     * <p>
     * The map keys are column names. The map values are 0-based indices.
     * </p>
     * <p>
     * Note: The map can only provide a one-to-one mapping when the format did not
     * contain null or duplicate column names.
     * </p>
     *
     * @return a copy of the header map.
     */
    /*public*/ Map<String, Integer> getHeaderMap() {
        if (this.headerMap == null) {
            return null;
        }
        final Map<String, Integer> map = createEmptyHeaderMap();
        map.putAll(this.headerMap);
        return map;
    }
#endif
    /**
     * Returns the header map.
     *
     * @return the header map.
     */
    QMap<QString, int>* CSVParser::getHeaderMapRaw() {
        return this->headerMap;
    }
#if 0
    /**
     * Returns a read-only list of header names that iterates in column order.
     * <p>
     * Note: The list provides strings that can be used as keys in the header map.
     * The list will not contain null column names if they were present in the input
     * format.
     * </p>
     *
     * @return read-only list of header names that iterates in column order.
     * @see #getHeaderMap()
     * @since 1.7
     */
    /*public*/ List<String> getHeaderNames() {
        return headerNames;
    }

    /**
     * Returns the current record number in the input stream.
     *
     * <p>
     * <strong>ATTENTION:</strong> If your CSV input has multi-line values, the returned number does not correspond to
     * the line number.
     * </p>
     *
     * @return current record number
     */
    /*public*/ long getRecordNumber() {
        return this.recordNumber;
    }
#endif
    /**
     * Parses the CSV input according to the given format and returns the content as a list of
     * {@link CSVRecord CSVRecords}.
     *
     * <p>
     * The returned content starts at the current parse-position in the stream.
     * </p>
     *
     * @return list of {@link CSVRecord CSVRecords}, may be empty
     * @throws IOException
     *             on parse error or input read-failure
     */
    /*public*/ QList<CSVRecord*> CSVParser::getRecords() throw (IOException) {
        CSVRecord* rec;
        /*final*/ QList<CSVRecord*> records = QList<CSVRecord*>();
        while ((rec = this->nextRecord()) != nullptr) {
            records.append(rec);
        }
        return records;
    }
#if 0
    /**
     * Gets whether this parser is closed.
     *
     * @return whether this parser is closed.
     */
    /*public*/ boolean isClosed() {
        return this.lexer.isClosed();
    }

    /**
     * Returns an iterator on the records.
     *
     * <p>
     * An {@link IOException} caught during the iteration are re-thrown as an
     * {@link IllegalStateException}.
     * </p>
     * <p>
     * If the parser is closed a call to {@link Iterator#next()} will throw a
     * {@link NoSuchElementException}.
     * </p>
     */
    @Override
    /*public*/ Iterator<CSVRecord> iterator() {
        return csvRecordIterator;
    }
#endif
    /**
     * Parses the next record from the current point in the stream.
     *
     * @return the record as an array of values, or {@code null} if the end of the stream has been reached
     * @throws IOException
     *             on parse error or input read-failure
     */
    CSVRecord* CSVParser::nextRecord() throw (IOException) {
        CSVRecord* result = nullptr;
        this->recordList.clear();
        QString sb = QString();
#if 0
        final long startCharPosition = lexer.getCharacterPosition() + this.characterOffset;
        do {
            this.reusableToken.reset();
            this.lexer.nextToken(this.reusableToken);
            switch (this.reusableToken.type) {
            case TOKEN:
                this.addRecordValue(false);
                break;
            case EORECORD:
                this.addRecordValue(true);
                break;
            case EOF:
                if (this.reusableToken.isReady) {
                    this.addRecordValue(true);
                }
                break;
            case INVALID:
                throw new IOException("(line " + this.getCurrentLineNumber() + ") invalid parse sequence");
            case COMMENT: // Ignored currently
                if (sb == null) { // first comment for this record
                    sb = new StringBuilder();
                } else {
                    sb.append(Constants.LF);
                }
                sb.append(this.reusableToken.content);
                this.reusableToken.type = TOKEN; // Read another token
                break;
            default:
                throw new IllegalStateException("Unexpected Token type: " + this.reusableToken.type);
            }
        } while (this.reusableToken.type == TOKEN);

        if (!this.recordList.isEmpty()) {
            this.recordNumber++;
            final String comment = sb == null ? null : sb.toString();
            result = new CSVRecord(this, this.recordList.toArray(new String[this.recordList.size()]),
                comment, this.recordNumber, startCharPosition);
        }
#else
        sb = reader->readLine();
        QStringList values = sb.split(',');
        result = new CSVRecord(this, values, "", 0, 0);

#endif
        return result;
    }

#endif


