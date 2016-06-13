#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <QObject>
#include "libPr3_global.h"

class QuaZip;
class File;
class LIBPR3SHARED_EXPORT ZipFile : public QObject
{
 Q_OBJECT
public:
 explicit ZipFile(QObject *parent = 0);
 ZipFile(File*, QObject* parent = 0);
 ZipFile(QString name, QObject* parent = 0);
 /*public*/ ZipFile(File* file,int mode, QObject* parent = 0);
 /*public*/QString getName();

signals:

public slots:
private:
 QString name;
 QuaZip* zipper;
 friend class VSDFile;
 void common();
 int mode;
};

#endif // ZIPFILE_H
