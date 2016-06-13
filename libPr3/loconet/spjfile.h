#ifndef SPJFILE_H
#define SPJFILE_H

#include <QObject>
#include <QStringList>

class Logger;
class SpjFile;
class SdfBuffer;
/**
 * Class representing a header record
 */
/*public*/ class Header  : public QObject
{
Q_OBJECT
    /*final*/ static int HEADERSIZE;// = 128; // bytes

    int type;
    int handle;

    // Offset in overall buffer where the complete record
    // associated with this header is found
    int recordStart;

    // Offset in overall buffer where the data part of the
    // record associated with this header is found
    int dataStart;

    // Length of the data in the associated record
    int dataLength;
    // Length of the associated record
    int recordLength;

    int time;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare1;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare2;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare3;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare4;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare5;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare6;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
    int spare7;

    QString filename;
    /*private*/ void setDataLength(int i) ;
    QVector<char>* bytes;
    /*private*/ void setByteArray(QVector<char>* a);
    SdfBuffer* sdfBuffer;// = NULL;
    SpjFile* f;
    /*private*/ int readInt4(QDataStream* s) /*throws java.io.IOException*/;
    /*private*/ int copyInt4(QVector<char>* buffer, int index, int i);
    /*private*/ int readInt2(QDataStream* s) ;
    void updateStart(int newRecordStart);
    int store(QVector<char>* buffer, int index);
    void store(QDataStream* s) /*throws java.io.IOException*/;
    void load(QDataStream* s) /*throws java.io.IOException*/;
    Logger* log;
public:
    Header(SpjFile* f, QObject* parent = 0);

    /*public*/ int getType();
    /*public*/ int getHandle();
    /*public*/ int getDataStart();
    /*public*/ void setDataStart(int i) ;
    /*public*/ int getDataLength() ;
    /*public*/ int getRecordStart();
    /*public*/ void setRecordStart(int i);
    /*public*/ int getRecordLength() ;
    /*public*/ void setRecordLength(int i);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    /*public*/ QVector<char>* getByteArray() ;
    /*public*/ SdfBuffer* getSdfBuffer();
    /*public*/ void setContent(QByteArray* array, int start, int length);
    /*public*/ QString toString();
    /*public*/ bool isWAV() ;
    /*public*/ bool isSDF() ;
    /*public*/ bool isMap();
    /*public*/ bool isTxt() ;
    /*private*/ void writeInt4(QDataStream* s, int i) /*throws java.io.IOException */;
    /*public*/ QString typeAsString();
    /*public*/ void setContent(QVector<char>* array, int start, int length);

 friend class SpjFile;
 friend class FirstHeader;
};

/**
 * Class representing first header
 */
class FirstHeader : public Header
{
Q_OBJECT
    int numHeaders();
    float version();
    QString getComment() ;
public:
    FirstHeader(SpjFile* f, QObject* parent = 0);
    /*public*/ QString toString();
    friend class SpjFile;
};


/* @(#)SpjFile.java */

class Logger;
class File;
class SpjFile : public QObject
{
 Q_OBJECT
public:
 //explicit SpjFile(QObject *parent = 0);
 /*public*/ SpjFile(File* file, QObject *parent = 0);
 /*public*/ int numHeaders();
 /*public*/ QString getComment();
 /*public*/ Header* getHeader(int index);
 /*public*/ Header* findSdfHeader();
 /*public*/ QString getMapEntry(int i);
 /*public*/ void save(QString name); /*throws java.io.IOException*/
 /*public*/ void read(); /*throws java.io.IOException*/
 /*public*/ void writeSubFiles() /*throws IOException*/;
 void writeSubFile(int i, QString name); /*throws IOException*/
 /*public*/ void dispose();

signals:
 void error(QString);

public slots:
private:
 QStringList mapCache;// = null;
 void loadMapCache();
 Logger* log;
 File* file;
 FirstHeader* h0;
 QList<Header*>* headers;
 SdfBuffer* sdfBuffer;// = NULL;

};

#endif // SPJFILE_H
