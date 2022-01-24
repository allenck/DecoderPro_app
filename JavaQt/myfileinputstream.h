#ifndef MYFILEINPUTSTREAM_H
#define MYFILEINPUTSTREAM_H

#include <QObject>
#include "file.h"
#include <QFile>
#include "exceptions.h"

class MyFileInputStream : public QObject
{
 Q_OBJECT
public:
 explicit MyFileInputStream(File *file, QObject *parent = nullptr);
 /*public*/ char read() /*throw (IOException)*/;
 /*public*/ void close() /*throw (IOException)*/;

signals:

public slots:
private:
 QFile* f =nullptr;
 QDataStream* stream = nullptr;
 /*private*/ void open(QString name) throw (FileNotFoundException);
 /*private*/ /*native*/ int read0() /*throw (IOException)*/;

};

#endif // MYFILEINPUTSTREAM_H
