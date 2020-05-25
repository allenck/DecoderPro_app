#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include "exceptions.h"

class CSVRecord;
enum CSVFormat
{
 DEFAULT,
 EXCEL,
 INFORMIX_UNLOAD,
 INFORMIX_UNLOAD_CSV,
 MONGODB_CSV,
 MONGODB_TSV,
 MYSQL,
 ORACLE,
 POSTGRESQL_CSV,
 POSTGRESQL_TEXT,
 RFC4180
};
class CSVRecordIterator //implements Iterator<CSVRecord>
{
    /*private*/ CSVRecord current;

    /*private*/ CSVRecord getNextRecord();
public:
    //@Override
    /*public*/ bool hasNext();
    /*public*/ CSVRecord* next();
    /*public*/ void remove();
};

class CSVParser : public QObject
{
 Q_OBJECT
public:
// /*public*/ static CSVParser parse(/*final*/ File* file, /*final*/ Charset charset, /*final*/ CSVFormat* format, QObject *parent) throw (IOException);
// /*public*/ static CSVParser parse(/*final*/ QTextStream inputStream, /*final Charset charset, final CSVFormat* format*/) throw (IOException);
 /*public*/ /*final*/ CSVFormat format;

 /** A mapping of column names to column indices */
 /*public*/ /*final*/ QMap<QString, int>* headerMap =nullptr;

 /** The column order to avoid re-computing it. */
 /*public*/ /*final*/ QList<QString> headerNames;

// /*public*/ final Lexer lexer;

 /*public*/ /*final*/ CSVRecordIterator* csvRecordIterator;

 /** A record buffer for getRecord(). Grows as necessary and is reused. */
 /*public*/ /*final*/ QList<QString> recordList;// = new ArrayList<>();

 /**
  * The next record number to assign.
  */
 /*public*/ long recordNumber;

 /**
  * Lexer offset when the parser does not start parsing at the beginning of the source. Usually used in combination
  * with {@link #recordNumber}.
  */
 /*public*/ /*final*/ long characterOffset;

// /*public*/ /*final*/ Token reusableToken = new Token();
 /*public*/ CSVParser(/*final*/ QTextStream *reader, /*final*/ CSVFormat format, /*final*/ long characterOffset = 0, /*final*/ long recordNumber =0)
     throw (IOException);
 /*public*/ QList<CSVRecord*> getRecords() throw (IOException);
 CSVRecord* nextRecord() throw (IOException);

signals:

public slots:

private:
 QMap<QString, int> *getHeaderMapRaw();
 QTextStream* reader;

 friend class CSVRecord;
};

/*public*/ /*static*/ /*final*/ class Headers {
    /**
     * Header column positions (0-based)
     */
    /*final*/ QMap<QString, int> headerMap;

    /**
     * Header names in column order
     */
    /*final*/ QList<QString> headerNames;
public:
    Headers(/*final*/ QMap<QString, int> headerMap, /*final*/ QList<QString> headerNames) {
        this->headerMap = headerMap;
        this->headerNames = headerNames;
    }
};

#endif // CSVPARSER_H
