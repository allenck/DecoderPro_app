#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <QVector>
#include <QString>
#include <QStringList>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT StringUtil
{
public:
    StringUtil();
    static /*public*/ int getStateFromName(QString name, QVector<int> states, QVector<QString> names);
    static /*public*/ QStringList getNamesFromStateMasked(int state, QVector<int> states, QVector<int> masks, QStringList names) ;
    static /*public*/ QString getNameFromState(int state, QVector<int> states, QStringList names);
    static /*public*/ QString parenQuote(QString in);
    static QString parenUnQuote(QString in);
    static /*final*/ QList<char> hexChars;// = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' } ;
    static /*public*/ QString twoHexFromInt(int val);
    static /*public*/ QString appendTwoHexFromInt(int val, QString inString);
    static /*public*/ QString hexStringFromBytes(QVector<char>* bytes) ;
    static /*public*/ void sort(QStringList values);
    static /*public*/ QByteArray bytesFromHexString(QString s);
    static /*public*/ void numberSort(QStringList values);// //throws NumberFormatException

};

#endif // STRINGUTIL_H
