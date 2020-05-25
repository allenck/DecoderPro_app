#ifndef CSVRECORD_H
#define CSVRECORD_H

#include <QObject>
#include "exceptions.h"

class CSVParser;
class CSVRecord : public QObject
{
 Q_OBJECT
public:
 CSVRecord(/*final*/ CSVParser* parser, /*final*/ QStringList values, /*final*/ QString comment, /*final*/ long recordNumber,
         /*final*/ long characterPosition, QObject* parent = nullptr);
 /*public*/ QString get(/*final*/ int i);
 /*public*/ QString get(/*final*/ QString name);
 /*public*/ long getCharacterPosition();
 /*public*/ QString getComment();


signals:

public slots:

private:
 /*private*/ static /*final*/ long serialVersionUID;// = 1L;
 /*private*/ /*static*/ /*final*/ QStringList EMPTY_STRING_ARRAY;// = QStringList;

 /*private*/ /*final*/ long characterPosition;

 /** The accumulated comments (if any) */
 /*private*/ /*final*/ QString comment;

 /** The record number. */
 /*private*/ /*final*/ long recordNumber;

 /** The values of the record */
 /*private*/ /*final*/ QStringList values;

 /** The parser that originates this record. This is not serialized. */
 /*private*/ /*final*/ /*transient*/ CSVParser* parser;
 /*private*/ QMap<QString, int>* getHeaderMapRaw();

 friend class CSVParser;
};

#endif // CSVRECORD_H
