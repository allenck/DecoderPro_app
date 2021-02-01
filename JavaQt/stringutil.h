#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <QVector>
#include <QString>
#include <QStringList>
#include "javaqt_global.h"
#include <QTranslator>

class Logger;
class JAVAQTSHARED_EXPORT StringUtil
{
public:
  /*public*/ static /*final*/ QString HTML_CLOSE_TAG;// = "</html>";
  /*public*/ static /*final*/ QString HTML_OPEN_TAG;// = "<html>";
  /*public*/ static /*final*/ QString LINEBREAK;// = "\n";
    StringUtil();
    static /*public*/ int getStateFromName(QString name, QVector<int> states, QVector<QString> names);
    static /*public*/ QStringList getNamesFromStateMasked(int state, QVector<int> states, QVector<int> masks, QStringList names) ;
    static /*public*/ QString getNameFromState(int state, QVector<int> states, QStringList names);
    static /*public*/ QString parenQuote(QString in);
    static QString parenUnQuote(QString in);
    static /*final*/ QList<char> hexChars;// = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' } ;
    static /*public*/ QString twoHexFromInt(int val);
    static /*public*/ QString appendTwoHexFromInt(int val, QString inString);
    static /*public*/ QString to8Bits(int val, bool msbLeft);
    static /*public*/ QString hexStringFromBytes(QVector<char>* bytes) ;
    static /*public*/ QString hexStringFromBytes(QByteArray bytes);
    static /*public*/ void sort(QStringList values);
    static /*public*/ QByteArray bytesFromHexString(QString s);
    static /*public*/ void numberSort(QStringList values);// //throws NumberFormatException
    /*public*/ static QString stringFormat(QLocale locale, QString in );
    static /*public*/ QString escapeString(QString s);
    static /*public*/ QString unescapeString(QString s);
    /*public*/ static QString concatTextHtmlAware(QString baseText, QString extraText);

private:
    /*private*/ static QTranslator* translator;// = QTranslator();
 static Logger* log;
};

#endif // STRINGUTIL_H
