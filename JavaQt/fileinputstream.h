#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H
#include <QDataStream>
#include "exceptions.h"

class File;
class FileInputStream : public QDataStream
{
public:
 /*public*/ FileInputStream(QString name, QObject* parent = nullptr) throw (FileNotFoundException);
 /*public*/ FileInputStream(File* file, QObject* parent = nullptr) throw (FileNotFoundException);
 /*public*/ QChar read() throw (IOException);
 /*public*/ void close() throw (IOException) ;
private:
 void common(File*);
 /* File Descriptor - handle to the open file */
// /*private*/ /*final*/ FileDescriptor fd;
 /*private*/ /*native*/ int read0() throw (IOException);

 /**
  * The path of the referenced file
  * (null if the stream is created with a file descriptor)
  */
 /*private*/ /*final*/ QString path;

// /*private*/ FileChannel channel;// = null;

 /*private*/ /*final*/ QObject* closeLock;// = new Object();
 /*private*/ volatile bool _close;//d = false;
 /*private*/ void open(QString name) throw (FileNotFoundException) ;
};

#endif // FILEINPUTSTREAM_H
