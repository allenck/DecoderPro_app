#include "myfileinputstream.h"
#include <QDataStream>

MyFileInputStream::MyFileInputStream(File* file, QObject *parent) : QObject(parent)
{
 open(file->getPath());
 stream = new QDataStream(f);
}

/*private*/ void MyFileInputStream::open(QString name) throw (FileNotFoundException)
{
 f = new QFile(name);
 if(!f->open(QIODevice::ReadOnly))
  throw new FileNotFoundException("Invalid file path");
}

/**
 * Reads a byte of data from this input stream. This method blocks
 * if no input is yet available.
 *
 * @return     the next byte of data, or <code>-1</code> if the end of the
 *             file is reached.
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ char MyFileInputStream::read() throw (IOException) {
// if(this->atEnd())
//  return -1;

    return read0();
}

/*private*/ /*native*/ int MyFileInputStream::read0() throw (IOException)
{
 char* buf = new char[2];
 if(stream->readRawData(buf, 1) < 0)
  return -1;
 return buf[0];

}
/**
 * Closes this file input stream and releases any system resources
 * associated with the stream.
 *
 * <p> If this stream has an associated channel then the channel is closed
 * as well.
 *
 * @exception  IOException  if an I/O error occurs.
 *
 * @revised 1.4
 * @spec JSR-51
 */
/*public*/ void MyFileInputStream::close() throw (IOException) {
 if(f->isOpen())
  f->close();
 stream = nullptr;
}
