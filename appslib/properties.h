#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QObject>
#include <QHash>
#include "exceptions.h"
#include "javaqt_global.h"
#include <QVariant>

class Reader;
class FileInputStream;
class LineReader;
class QTextStream;
class JAVAQTSHARED_EXPORT Properties : public QObject
{
   // Q_OBJECT
public:
    explicit Properties(QObject *parent = 0);
    /*public*/ Properties(Properties* defaults,QObject *parent = 0);
    /*public*/ /*synchronized*/ void setProperty(QString key, QString value);
    /*public*/ void storeToXML(QTextStream* os, QString comment);
    /*public*/ void storeToXML(QTextStream* os, QString comment, QString encoding)
    /*throw (IOException)*/;
    QMap<QString, QVariant> getHash();
    /*public*/ /*synchronized*/ void loadFromXML(QTextStream* in);
    /*public*/ QString getProperty(QString key);
    /*public*/ bool containsKey(QString key);
    /*public*/ /*synchronized*/ void load(QTextStream* inStream); //throws IOException
    /*public*/ QString getProperty(QString key, QString defaultValue);
    void put(QVariant key, QVariant value);
    QVariant get(QVariant key);
    /*public*/ void remove(QString);
    /*public*/ QStringListIterator propertyNames();
    /*public*/ void store(QTextStream* writer, QString comments) /*throw (IOException)*/;
    /*public*/  void load(FileInputStream* inStream); //throws IOException


signals:

public slots:
private:
    static QMap<QString, QVariant>* _hashTable;
    /*private*/ /*synchronized*/ void enumerate(QMap<QString,QVariant>* h);

    /*private*/ /*static*/ class XmlSupport
    {
#if 0
     /*private*/ static XmlPropertiesProvider loadProviderFromProperty(ClassLoader cl);
     /*private*/ static XmlPropertiesProvider loadProviderAsService(ClassLoader cl);
     /*private*/ static XmlPropertiesProvider loadProvider();
     /*private*/ static /*final*/ XmlPropertiesProvider PROVIDER = loadProvider();
   #endif
     static void load(Properties* props, QTextStream* in)
     /*throw (IOException, InvalidPropertiesFormatException)*/;
     static void save(Properties* props, QTextStream* os, QString comment,
                         QString encoding) /*throw (IOException)*/;
     friend class Properties;
    };
    /*private*/ void load0 (LineReader* lr); //throws IOException

    /*private*/ QString loadConvert (QByteArray in, int off, int len, QByteArray convtBuf);
    /*private*/ void store0(QTextStream* bw, QString comments, bool escUnicode)/*throw (IOException)*/;
    /*private*/ static void writeComments(QTextStream* bw, QString comments) /*throw (IOException)*/;
    /*private*/ QString saveConvert(QString theString,
                                    bool escapeSpace,
                                    bool escapeUnicode);

protected:
    /**
     * A property list that contains default values for any keys not
     * found in this property list.
     *
     * @serial
     */
    /*protected*/ Properties* defaults;
//    static QHash<QString, QString> hash;
    friend class Preferences;
};

//class Reader;
class LineReader : public QObject
{
 Q_OBJECT
public:
 /*public*/ LineReader(QTextStream* inStream);
 /*public*/ LineReader(QDataStream *reader);

// /*public*/ LineReader(Reader* reader) ;

private:
 //char inByteBuf[8192];
 QByteArray inByteBuf;
 char inCharBuf[1];
 //char lineBuf[] = new char[1024];
 //char lineBuf[1024];
 int inLimit;// = 0;
 int inOff;// = 0;
 QTextStream* inStream;
 //QDataStream* reader;
public:
 QByteArray lineBuf;
 int readLine();// throws IOException
 void common();

};

#endif // PROPERTIES_H
