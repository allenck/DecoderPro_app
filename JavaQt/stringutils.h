#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <QtCore>

class IndexOutOfBoundsException;
class StringUtils
{
public:
 /*public*/ static QString repeat(QString str, int repeat);
 /*public*/ static /*final*/ QString EMPTY;// = "";
 /*public*/ static /*final*/ int INDEX_NOT_FOUND;// = -1;
 /*public*/ static QString repeat(QString str, QString separator, int repeat);
 /*public*/ static QString removeEnd(QString str, QString remove);
 /*public*/ static bool isEmpty(QString str);
 /*public*/ static QString deleteWhitespace(QString str);

private:
 StringUtils();
 /*private*/ static /*final*/ int PAD_LIMIT;// = 8192;
 /*private*/ static QString padding(int repeat, char padChar) throw (IndexOutOfBoundsException);

};

#endif // STRINGUTILS_H
