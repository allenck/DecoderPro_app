#include "zipfile.h"
#include "file.h"
#include "quazip.h"
#include "file.h"

ZipFile::ZipFile(QObject *parent) :
  QObject(parent)
{
 common();
}

ZipFile::ZipFile(File* file, QObject* parent)  :
  QObject(parent)
{
 common();
 zipper = new QuaZip(file->getPath());
 zipper->open((QuaZip::Mode)mode);
 name = file->getPath();
}

ZipFile::ZipFile(QString name, QObject* parent) : QObject(parent)
{
 common();
 this->name =name;
 zipper = new QuaZip(name);
zipper->open((QuaZip::Mode)mode);
}

/*public*/ ZipFile::ZipFile(File* file, int mode, QObject* parent) : QObject(parent) //throws IOException
{
        //this(file, mode, StandardCharsets.UTF_8);
 common();
 zipper = new QuaZip(file->getPath());
 name = file->getPath();
 zipper->open((QuaZip::Mode)mode);
}
void ZipFile::common()
{
 zipper = NULL;
 mode = QuaZip::mdUnzip;
}

/*public*/QString ZipFile::getName()
{
 return name;
}

/*public*/void  ZipFile::close()
{
 zipper->close();
}
