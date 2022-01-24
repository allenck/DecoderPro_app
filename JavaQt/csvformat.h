#ifndef CSVFORMAT_H
#define CSVFORMAT_H

#include <QObject>
#include <QTextStream>

class CSVPrinter;
class QuoteMode
{

};

class CSVFormat : public QObject
{
  Q_OBJECT
 public:
  /*public*/ enum QuoteMode {
      ALL, ALL_NON_NULL, MINIMAL, NON_NUMERIC, NONE

//      private QuoteMode() {
//          // compiled code
//      }
  };
  Q_ENUM(QuoteMode)
  explicit CSVFormat(QObject *parent = nullptr);
  /*public*/ static /*final*/ CSVFormat* DEFAULT;// = new CSVFormat(COMMA, DOUBLE_QUOTE_CHAR, null, null, null, false, true, CRLF, null, null, null, false, false, false,
//             false, false, false, true);
  /*public*/ CSVPrinter* print(/*final*/ QTextStream* out) /*throws IOException*/;
  /*public*/ void println(/*final*/ QTextStream* appendable) /*throws IOException*/;
  /*public*/ bool getTrailingDelimiter();
  /*public*/ QString getDelimiterString();
  /*public*/ QChar getEscapeCharacter();
  /*public*/ void print(/*final*/ QVariant value, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/ ;
  /*public*/ bool isQuoteCharacterSet();
  /*public*/ QChar getQuoteCharacter();
  /*public*/ QuoteMode getQuoteMode();
  /*public*/ bool isEscapeCharacterSet();
  /*public*/ bool getAutoFlush();

 signals:

 private:
  /*private*/ CSVFormat(/*final*/  QString delimiter, /*final*/ QChar quoteChar, /*final*/ QuoteMode quoteMode, /*final*/  QChar commentStart, /*final*/  QChar escape,
             /*final*/  bool ignoreSurroundingSpaces, /*final*/  bool ignoreEmptyLines, /*final*/  QString recordSeparator, /*final*/  QString nullString,
             /*final*/  QVariantList headerComments, /*final*/  QStringList header, /*final*/  bool skipHeaderRecord, /*final*/  bool allowMissingColumnNames,
             /*final*/  bool ignoreHeaderCase, /*final*/  bool trim, /*final*/  bool trailingDelimiter, /*final*/  bool autoFlush,
             /*final*/  bool allowDuplicateHeaderNames, QObject* parent=nullptr);
  /*private*/ /*final*/ bool allowDuplicateHeaderNames;

  /*private*/ /*final*/  bool allowMissingColumnNames;

  /*private*/ /*final*/  bool autoFlush;

  /*private*/ /*final*/  QChar commentMarker; // null if commenting is disabled

  /*private*/ /*final*/  QString delimiter;

  /*private*/ /*final*/  QChar escapeCharacter; // null if escaping is disabled

  /*private*/ /*final*/  QStringList header; // array of header column names

  /*private*/ /*final*/  QStringList headerComments; // array of header comment lines

  /*private*/ /*final*/  bool ignoreEmptyLines;

  /*private*/ /*final*/  bool ignoreHeaderCase; // should ignore header names case

  /*private*/ /*final*/  bool ignoreSurroundingSpaces; // Should leading/trailing spaces be ignored around values?

  /*private*/ /*final*/  QString nullString; // the string to be used for null values

  /*private*/ /*final*/  QChar quoteCharacter; // null if quoting is disabled

  /*private*/ /*final*/  QString quotedNullString;

  /*private*/ /*final*/  QuoteMode quoteMode;

  /*private*/ /*final*/  QString recordSeparator; // for outputs

  /*private*/ /*final*/  bool skipHeaderRecord;

  /*private*/ /*final*/  bool trailingDelimiter;

  /*private*/ /*final*/  bool trim;
  QChar CR = '\r';
  QChar LF = '\n';
  QChar SP = ' ';
  QChar COMMENT = '#';
  static QStringList toStringArray(/*final*/ QVariantList values);
  /*private*/ void validate() /*throws IllegalArgumentException*/;
  /*private*/ static bool contains(/*final*/ QString source, /*final*/ QChar searchCh);
  /*private*/ static bool containsLineBreak(/*final*/ QString source);
  /*private*/ void append(/*final*/ QChar c, /*final*/ QTextStream* appendable) /*throws IOException*/;
  /*private*/ void append(/*final*/ QString csq, /*final*/ QTextStream* appendable) /*throws IOException*/;
  /*private*/ void print(/*final*/ QVariant object, /*final*/ QString value, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/;
  /*private*/ void printWithQuotes(/*final*/ QVariant object, /*final*/ QString charSeq, /*final*/ QTextStream* out, /*final*/ bool newRecord) /*throws IOException*/;
  /*private*/ void printWithEscapes(/*final*/ QString charSeq, /*final*/ QTextStream* appendable) /*throws IOException*/;
  /*private*/ bool isDelimiter(/*final*/ QChar ch, /*final*/ /*CharSequence*/QString charSeq, /*final*/ int startIndex, /*final*/ QString delimiter, /*final*/ int delimiterLength);

};


#endif // CSVFORMAT_H
