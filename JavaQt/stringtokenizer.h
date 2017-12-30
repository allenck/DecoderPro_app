#ifndef QSTRINGTOKENIZER_H
#define QSTRINGTOKENIZER_H

#include <QObject>
#include <QVector>

class StringTokenizer : public QObject
{
 Q_OBJECT
public:
    //explicit QStringTokenizer(QObject *parent = 0);
    /*public*/ StringTokenizer(QString str, QString delim = " \t\n\r\f", bool returnDelims = false/*, QObject *parent = 0*/);
 ~StringTokenizer() {}
 StringTokenizer(const StringTokenizer&) {}
    /*public*/ bool hasMoreTokens();
    /*public*/ QString nextToken();
    /*public*/ QString nextToken(QString delim);
    /*public*/ bool hasMoreElements();
    /*public*/ QVariant nextElement();
    /*public*/ int countTokens();

signals:

public slots:
private:
    /*private*/ int currentPosition;
    /*private*/ int newPosition;
    /*private*/ int maxPosition;
    /*private*/ QString str;
    /*private*/ QString delimiters;
    /*private*/ bool retDelims;
    /*private*/ bool delimsChanged;
    /**
     * maxDelimCodePoint stores the value of the delimiter character with the
     * highest value. It is used to optimize the detection of delimiter
     * characters.
     *
     * It is unlikely to provide any optimization benefit in the
     * hasSurrogates case because most string characters will be
     * smaller than the limit, but we keep it so that the two code
     * paths remain similar.
     */
    /*private*/ QChar maxDelimCodePoint;

    /**
     * If delimiters include any surrogates (including surrogate
     * pairs), hasSurrogates is true and the tokenizer uses the
     * different code path. This is because String.indexOf(int)
     * doesn't handle unpaired surrogates as a single character.
     */
    /*private*/ bool hasSurrogates;// = false;

    /**
     * When hasSurrogates is true, delimiters are converted to code
     * points and isDelimiter(int) is used to determine if the given
     * codepoint is a delimiter.
     */
    /*private*/ QVector<int> delimiterCodePoints;
    /*private*/ void setMaxDelimCodePoint();
    /*private*/ int skipDelimiters(int startPos);
    /*private*/ int scanToken(int startPos);
    /*private*/ bool isDelimiter(int codePoint);


};

#endif // QSTRINGTOKENIZER_H
