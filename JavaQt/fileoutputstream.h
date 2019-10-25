#ifndef FILEOUTPUTSTREAM_H
#define FILEOUTPUTSTREAM_H
#include "exceptions.h"
#include <QTextStream>

class File;
class QFile;
class FileOutputStream : public QTextStream
{
public:
 FileOutputStream();
 /*public*/ FileOutputStream(File* file, bool append = false) throw (FileNotFoundException);
 /*public*/ void write(int b) throw (IOException);
 /*public*/ void close() throw (IOException);

private:
 bool append = false;
 /*private*/ /*native*/ void open(QString name, bool append)
     throw (FileNotFoundException);
 QFile* qf;
 bool isOpen;
 /*private*/ /*native*/ void write(int b, bool append) throw (IOException);

};

#endif // FILEOUTPUTSTREAM_H
