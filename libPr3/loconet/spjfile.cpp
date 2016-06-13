#include "spjfile.h"
#include "file.h"
#include "logger.h"
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QStringList>
#include "sdfbuffer.h"
#include "logger.h"

//SpjFile::SpjFile(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Provide tools for reading, writing and accessing Digitrax SPJ files.
 * <p>
 * Four-byte quantities in SPJ files are little-endian.
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2009
 * @version $Revision: 28771 $
 */
///*public*/ class SpjFile {

/*public*/ SpjFile::SpjFile(File* file, QObject *parent) :
  QObject(parent)
{
 this->file = file;
 mapCache = QStringList();
 log = new Logger("SpjFile");
 sdfBuffer = NULL;
 headers = NULL;
}

/**
 * Number of headers present in the file.
 *
 * @return -1 if error
 */
/*public*/ int SpjFile::numHeaders() {
    if (headers != NULL && h0 != NULL) {
        return h0->numHeaders();
    } else {
        return -1;
    }
}

/*public*/ QString SpjFile::getComment()
{
 return h0->getComment();
}

/*public*/ Header* SpjFile::getHeader(int index)
{
 return headers->at(index);
}

/*public*/ Header* SpjFile::findSdfHeader()
{
 int n = numHeaders();
 for (int i = 1; i < n; i++)
 {
  if (headers->at(i)->isSDF())
  {
   return headers->at(i);
  }
 }
 return NULL;
}

/**
 * Find the map entry (character string) that corresponds to a particular
 * handle number
 */
/*public*/ QString SpjFile::getMapEntry(int i)
{
 if (log->isDebugEnabled())
 {
  log->debug("getMapEntry(" + QString::number(i) + ")");
 }
 loadMapCache();
 QString wanted = QString::number(i);
 for (int j = 0; j < mapCache.length(); j++)
 {
  if (mapCache.at(j).startsWith(wanted))
  {
   return mapCache.at(j).mid(wanted.length());
  }
 }
 return NULL;
}


void SpjFile::loadMapCache()
{
 if (!mapCache.isEmpty())
 {
  return;
 }

 // find the map entries
 log->debug("loading map cache");
 int map;
 for (map = 1; map < numHeaders(); map++)
 {
  if (headers->at(map)->isMap())
  {
   break;
  }
 }
 // map holds the map index, hopefully
 if (map > numHeaders())
 {
  log->error("Did not find map data");
  return;
 }

 // here found it, count lines
 QVector<char>* buffer = headers->at(map)->getByteArray();
 log->debug("map buffer length " + buffer->size());
 int count = 0;
 for (int i = 0; i < buffer->size(); i++)
 {
  if (buffer->at(i) == 0x0D)
  {
   count++;
  }
 }
 QVector<QString>* l = new QVector<QString>(count,"");
 mapCache = l->toList();

 log->debug("found " + QString::number(count) + " map entries");

 int start = 0;
 int end = 0;
 int index = 0;

 // loop through the string, look for each line
 if (log->isDebugEnabled())
 {
  log->debug("start loop over map with buffer length = " + buffer->size());
 }
 while ((++end) < buffer->size())
 {
  if (buffer->at(end) == 0x0D || buffer->at(end) == 0x0A)
  {
   // sound end; make string
   //QString next = new QString(buffer, start, end - start);
   QString next = QString::fromLocal8Bit(buffer->mid(start, end-start).data());
   next.resize(end-start);
   // increment pointers
   start = ++end;
   if (log->isDebugEnabled())
   {
    log->debug("new start value is " + QString::number(start));
   }
   if (log->isDebugEnabled())
   {
    log->debug("new end value is   " + QString::number(end));
   }

   // if another linefeed or newline is present, skip it too
   if ((buffer->at(end - 1) == 0x0D || ((end < buffer->size()) && buffer->at(end) == 0x0A))
       || (buffer->at(end - 1) == 0x0A || ((end < buffer->size()) && buffer->at(end) == 0x0D)))
   {
    start++;
    end++;
   }
   // store entry
   if (log->isDebugEnabled())
   {
    log->debug(" store entry " + index);
   }
   mapCache.replace(index++, next);
  }
 }
}

/**
 * Save this file. It lays the file out again, changing the record start
 * addresses into a sequential series
 *
 * @throws java.io.IOException if anything goes wrong
 */
/*public*/ void SpjFile::save(QString name) /*throws java.io.IOException*/
{
    if (name == NULL)
    {
     //throw new IOException("Null name during write");
     emit error("Null name during write");
     return;
    }
    //OutputStream s = new java.io.BufferedOutputStream(
//            new java.io.FileOutputStream(new java.io.File(name)));
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly))
    {
     emit error("File open failed");
     return;
    }
    QDataStream* s = new QDataStream(&file);
    s->setByteOrder(QDataStream::LittleEndian);


    // find size of output file
    int length = Header::HEADERSIZE * h0->numHeaders();  // allow header space at start
    for (int i = 1; i < h0->numHeaders(); i++)
    {
     length += headers->at(i)->getRecordLength();
    }
    QVector<char>* buffer = new QVector<char>(length,0);
//     for (int i = 0; i < length; i++)
//     {
//        buffer[i] = 0;
//     }

    // start with first header
    int index = 0;
    index = h0->store(buffer, index);

    if (index != Header::HEADERSIZE)
    {
        log->error("Unexpected 1st header length: " + QString::number(index));
    }

    int datastart = index * h0->numHeaders(); //index is the length of the 1st header

    // rest of the headers
    for (int i = 1; i < h0->numHeaders(); i++)
    {  // header 0 already done
        // Update header pointers.
     headers->at(i)->updateStart(datastart);
     datastart += headers->at(i)->getRecordLength();

     // copy contents into output buffer
     index = headers->at(i)->store(buffer, index);
    }

    // copy the chunks; skip the first header, with no data
    for (int i = 1; i < h0->numHeaders(); i++)
    {
        int start = headers->at(i)->getRecordStart();
        int count = headers->at(i)->getRecordLength();  // stored one long

        QVector<char>* content = headers->at(i)->getByteArray();
        if (count != content->size()) {
            log->error("header count " + QString::number(count) + " != content length " + QString::number(content->size()));
        }
        for (int j = 0; j < count; j++) {
         buffer->replace(start + j, content->at(j));
        }
    }

    // write out the buffer
    s->writeBytes(buffer->data(), buffer->count());

    // purge buffers
    s->device()->close();

}

/**
 * Read the file whose name was provided earlier
 */
/*public*/ void SpjFile::read() /*throws java.io.IOException*/
{
 if (file == NULL)
 {
  //throw new java.io.IOException("Null file during read");
  emit error("Null file during read");
 }
 QFile f(file->getPath());
 if(!f.open(QIODevice::ReadOnly))
 {
  emit error("Error opening file " + f.errorString());
  return;
 }
 //QDataStream s = new java.io.BufferedInputStream(new java.io.FileInputStream(file));
 QDataStream* s = new QDataStream(&f);
 s->setByteOrder(QDataStream::LittleEndian);

 // get first header record
 h0 = new FirstHeader(this);
 h0->load(s);
 if (log->isDebugEnabled())
 {
  log->debug(h0->toString());
 }
 int n = h0->numHeaders();
 headers = new QList<Header*>();
 for(int i = 0; i < n; i++) headers->append(NULL);
 headers->replace(0, h0);

 for (int i = 1; i < n; i++)
 {  // header 0 already read
  headers->replace(i, new Header(this));
  headers->at(i)->load(s);
  if (log->isDebugEnabled())
  {
   log->debug("Header " + QString::number(i) + " " + headers->at(i)->toString());
  }
 }

 // now read the rest of the file, loading bytes
 // first, scan for things we can't handle
 for (int i = 1; i < n; i++)
 {
  if (log->isDebugEnabled())
  {
   log->debug("Header " + QString::number(i) + " length " + QString::number(headers->at(i)->getDataLength()) + " type " + QString::number(headers->at(i)->getType()));
  }
  if (headers->at(i)->getDataLength() > headers->at(i)->getRecordLength())
  {
   log->error("header " + QString::number(i) + " has data length " + QString::number(headers->at(i)->getDataLength())
              + " greater than record length " + QString::number(headers->at(i)->getRecordLength()));
  }

  for (int j = 1; j < i; j++)
  {
   if (headers->at(i)->getHandle() == headers->at(j)->getHandle()
           && headers->at(i)->getType() == 1
           && headers->at(j)->getType() == 1)
   {
    log->error(tr("Duplicate handle number in records ") + i + "(" + QString::number(headers->at(i)->getHandle()) + ") and "
               + QString::number(j) + "(" + QString::number(headers->at(j)->getHandle()) + ")");
   }
  }
  if (headers->at(i)->getType() > 6)
  {
   log->error("Type field unexpected value: " + QString::number(headers->at(i)->getType()));
  }
  if (headers->at(i)->getType() == 0) {
      log->error("Type field unexpected value: " + QString::number(headers->at(i)->getType()));
  }
  if (headers->at(i)->getType() < -1)
  {
   log->error("Type field unexpected value: " + QString::number(headers->at(i)->getType()));
  }
 }

 // find end of last part
 int length = 0;
 for (int i = 1; i < n; i++)
 {
  if (length < headers->at(i)->getRecordStart() + headers->at(i)->getRecordLength())
  {
   length = headers->at(i)->getRecordStart() + headers->at(i)->getRecordLength();
  }
 }

 if (log->isDebugEnabled())
 {
  log->debug("Last byte at " + QString::number(length));
 }

 // inefficient way to read, because of all the skips (instead
 // of seeks)  But it handles non-consecutive and overlapping definitions.
 for (int i = 1; i < n; i++)
 {
  if(s->device() != NULL && s->device()->isOpen())
   s->device()->close();
  //s = new java.io.BufferedInputStream(new java.io.FileInputStream(file));
  //QFile f(file->getPath());
  if(!f.open(QIODevice::ReadOnly))
  {
   emit error("Error opening file");
   break;
  }
  s = new QDataStream(&f);
  s->setByteOrder(QDataStream::LittleEndian);
  s->skipRawData(headers->at(i)->getRecordStart());

  QVector<char>* array = new QVector<char>(headers->at(i)->getRecordLength());
  int read = s->readRawData(array->data(), array->count());
  if (read != headers->at(i)->getRecordLength())
  {
   log->error("header " + QString::number(i) + " read " + QString::number(read) + ", expected " + QString::number(headers->at(i)->getRecordLength()));
  }

  headers->at(i)->setByteArray(array);
 }
 if(s->device() != NULL && s->device()->isOpen())
  s->device()->close();
}

/**
 * Write data from headers into separate files.
 *
 * Normally, we just work with the data within this file. This method allows
 * us to extract the contents of the file for external use.
 */
/*public*/ void SpjFile::writeSubFiles() /*throws IOException*/
{
 // write data from WAV headers into separate files
 int n = numHeaders();
 for (int i = 1; i < n; i++)
 {
  if (headers->at(i)->isWAV()) {
      writeSubFile(i, QString::number(i) + ".wav");
  } else if (headers->at(i)->isSDF()) {
      writeSubFile(i, QString::number(i) + ".sdf");
  } else if (headers->at(i)->getType() == 3) {
      writeSubFile(i, QString::number(i) + ".cv");
  } else if (headers->at(i)->getType() == 4) {
      writeSubFile(i, QString::number(i) + ".txt");
  } else if (headers->at(i)->isMap()) {
      writeSubFile(i, QString::number(i) + ".map");
  } else if (headers->at(i)->getType() == 6) {
      writeSubFile(i, QString::number(i) + ".uwav");
  }
 }
}

/**
 * Write the content from a specific header as a new "subfile"
 *
 * @param i    index of the specific header
 * @param name filename
 */
void SpjFile::writeSubFile(int i, QString name) /*throws IOException*/
{
 QFile outfile(name);
 if(!outfile.open(QIODevice::WriteOnly))
 {
  emit error("Cannot open output file");
  return;
 }
 QDataStream* ostream = new QDataStream(&outfile);
 ostream->setByteOrder(QDataStream::LittleEndian);

 //try {
     ostream->writeBytes(headers->at(i)->getByteArray()->data(), headers->at(i)->getByteArray()->count());
//    } finally {
     ostream->device()->close();
//    }
}

/*public*/ void SpjFile::dispose() {
}


/**
 * Class representing a header record
 */
///*public*/ class Header {

/*final*/ /*static*/ int Header::HEADERSIZE = 128; // bytes

//    int type;
//    int handle;

//    // Offset in overall buffer where the complete record
//    // associated with this header is found
//    int recordStart;

//    // Offset in overall buffer where the data part of the
//    // record associated with this header is found
//    int dataStart;

//    // Length of the data in the associated record
//    int dataLength;
//    // Length of the associated record
//    int recordLength;

//    int time;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare1;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare2;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare3;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare4;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare5;

//    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare6;

//   //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "URF_UNREAD_FIELD") // we maintain this, but don't use it for anything yet
//    int spare7;

//    QString filename;
Header::Header(SpjFile* f, QObject* parent)
{
 this->f = f;
 sdfBuffer = NULL;
 log = new Logger("Header");
}

/*public*/ int Header::getType() {
    return type;
}

/*public*/ int Header::getHandle() {
    return handle;
}

/*public*/ int Header::getDataStart() {
    return dataStart;
}

/*public*/ void Header::setDataStart(int i) {
    dataStart = i;
}

/*public*/ int Header::getDataLength() {
    return dataLength;
}

/*private*/ void Header::setDataLength(int i) {
    dataLength = i;
}

/*public*/ int Header::getRecordStart() {
    return recordStart;
}

/*public*/ void Header::setRecordStart(int i) {
    recordStart = i;
}

/**
 * This method, in addition to returning the needed record size, will
 * also pull a SdfBuffer back into the record if one exists
 */
/*public*/ int Header::getRecordLength()
{
 if (sdfBuffer != NULL)
 {
  sdfBuffer->loadByteArray();
  QVector<char>* a = sdfBuffer->getByteArray();
  setByteArray(a);
  dataLength = bytes->size();
  recordLength = bytes->size();
 }
 return recordLength;
}

/*public*/ void Header::setRecordLength(int i) {
    recordLength = i;
}

/*public*/ QString Header::getName() {
    return filename;
}

/*public*/ void Header::setName(QString name)
{
 if (name.length() > 72)
 {
  log->error("new filename too long: " + QString::number(filename.length()));
 }
 filename = name;
}


/**
 * Copy new data into the local byte array
 */
/*private*/ void Header::setByteArray(QVector<char>* a)
{
 bytes = new QVector<char>(a->size());
 for (int i = 0; i < a->size(); i++)
 {
     //bytes[i] = a[i];
  bytes->replace(i, a->at(i));
 }
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
/*public*/ QVector<char>* Header::getByteArray() {
    return bytes;
}

/**
 * Get as a SDF buffer. This buffer then becomes associated, and a later
 * write will use the buffer's contents
 */
/*public*/ SdfBuffer* Header::getSdfBuffer() {
    sdfBuffer = new SdfBuffer(getByteArray());
    return sdfBuffer;
}


/**
 * Data record associated with this header is being being repositioned
 */
void Header::updateStart(int newRecordStart) {
    //int oldRecordStart = getRecordStart();
    int dataStartOffset = getDataStart() - getRecordStart();
    setRecordStart(newRecordStart);
    setDataStart(newRecordStart + dataStartOffset);
}

/**
 * Provide new content. The data start and data length values are
 * computed from the arguments, and stored relative to the length.
 *
 * @param array  New byte array; copied into header
 * @param start  data start location within array
 * @param length data length in bytes (not record length)
 */
/*public*/ void Header::setContent(QVector<char>* array, int start, int length) {
    log->debug("setContent length = 0x" + QString::number(length,0,16));
    setByteArray(array);
    setDataStart(getRecordStart() + start);
    setDataLength(length);
    setRecordLength(array->size());
}

int Header::store(QVector<char>* buffer, int index) {
    index = copyInt4(buffer, index, type);
    index = copyInt4(buffer, index, handle);
    index = copyInt4(buffer, index, recordStart);
    index = copyInt4(buffer, index, dataStart);
    index = copyInt4(buffer, index, dataLength);
    index = copyInt4(buffer, index, recordLength);
    index = copyInt4(buffer, index, time);

    index = copyInt4(buffer, index, 0); // spare 1
    index = copyInt4(buffer, index, 0); // spare 2
    index = copyInt4(buffer, index, 0); // spare 3
    index = copyInt4(buffer, index, 0); // spare 4
    index = copyInt4(buffer, index, 0); // spare 5
    index = copyInt4(buffer, index, 0); // spare 6
    index = copyInt4(buffer, index, 0); // spare 7

    // name is written in zero-filled array
    QByteArray name = filename.toLocal8Bit();
    if (name.size() > 72)
    {
     log->error("Name too long: " + QString::number(name.size()));
    }
    for (int i = 0; i < name.size(); i++)
    {
     buffer->replace(index + i, name.at(i));
    }

    return index + 72;
}

void Header::store(QDataStream* s) /*throws java.io.IOException*/ {
    writeInt4(s, type);
    writeInt4(s, handle);
    writeInt4(s, recordStart);
    writeInt4(s, dataStart);
    writeInt4(s, dataLength);
    writeInt4(s, recordLength);
    writeInt4(s, time);

    writeInt4(s, 0);  // spare 1
    writeInt4(s, 0);  // spare 2
    writeInt4(s, 0);  // spare 3
    writeInt4(s, 0);  // spare 4
    writeInt4(s, 0);  // spare 5
    writeInt4(s, 0);  // spare 6
    writeInt4(s, 0);  // spare 7

    // name is written in zero-filled array
    QByteArray name = filename.toLocal8Bit();
    if (name.length() > 72) {
     log->error("Name too long: " + QString::number(name.length()));
    }
    QVector<char>* buffer = new QVector<char>(72);
    for (int i = 0; i < 72; i++) {
        buffer->replace(i, 0);
    }
    for (int i = 0; i < name.length(); i++) {
     buffer->replace(i, name.at(i));
    }
    s->writeBytes(buffer->data(), buffer->size());
}

void Header::load(QDataStream* s) /*throws java.io.IOException*/ {
    type = readInt4(s);
    handle = readInt4(s);
    recordStart = readInt4(s);
    dataStart = readInt4(s);
    dataLength = readInt4(s);
    recordLength = readInt4(s);
    time = readInt4(s);

    spare1 = readInt4(s);
    spare2 = readInt4(s);
    spare3 = readInt4(s);
    spare4 = readInt4(s);
    spare5 = readInt4(s);
    spare6 = readInt4(s);
    spare7 = readInt4(s);

    char* name = new char[72];
    int readLength = s->readRawData(name,72);
    // name is zero-terminated, so we have to truncate that array
    int len = 0;
    for (len = 0; len < readLength; len++)
    {
     if (name[len]== 0)
     {
         break;
     }
    }
    char* shortname = new char[len + 1];
    int i;
    for ( i = 0; i < len; i++) {
     shortname[i] =  name[i];
    }
    shortname[i] = 0;
    filename = QString(shortname);
    delete shortname;
}

/*public*/ QString Header::toString() {
    return "type= " + typeAsString() + ", handle= " + handle + ", rs= " + recordStart + ", ds= " + dataStart
            + ", ds-rs = " + (dataStart - recordStart)
            + ", dl = " + dataLength + ", rl= " + recordLength
            + ", rl-dl = " + (recordLength - dataLength)
            + ", filename= " + filename;
}

/*public*/ bool Header::isWAV() {
    return (getType() == 1);
}

/*public*/ bool Header::isSDF() {
    return (getType() == 2);
}

/*public*/ bool Header::isMap() {
    return (getType() == 5);
}

/*public*/ bool Header::isTxt() {
    return (getType() == 4);
}

/**
 * Read a 4-byte integer, handling endian-ness of SPJ files
 */
/*private*/ int Header::readInt4(QDataStream* s) /*throws java.io.IOException*/ {
//    int i1 = s.read() & 0xFF;
//    int i2 = s.read() & 0xFF;
//    int i3 = s.read() & 0xFF;
//    int i4 = s.read() & 0xFF;
//    return i1 + (i2 << 8) + (i3 << 16) + (i4 << 24);
 qint32 i;
 *s >> i;
 return (int)i;
}

/**
 * Write a 4-byte integer, handling endian-ness of SPJ files
 */
/*private*/ void Header::writeInt4(QDataStream* s, int i) /*throws java.io.IOException*/ {
//    byte i1 = (byte) (i & 0xFF);
//    byte i2 = (byte) ((i >> 8) & 0xFF);
//    byte i3 = (byte) ((i >> 16) & 0xFF);
//    byte i4 = (byte) ((i >> 24) & 0xFF);

//    s.write(i1);
//    s.write(i2);
//    s.write(i3);
//    s.write(i4);
 *s << (qint32)i;
}

/**
 * Copy a 4-byte integer to byte buffer, handling little-endian-ness of
 * SPJ files
 */
/*private*/ int Header::copyInt4(QVector<char>* buffer, int index, int i) {
    buffer->replace(index++, (char) (i & 0xFF));
    buffer->replace(index++, (char) ((i >> 8) & 0xFF));
    buffer->replace(index++, (char) ((i >> 16) & 0xFF));
    buffer->replace(index++, (char) ((i >> 24) & 0xFF));
    return index;
}

/**
 * Read a 2-byte integer, handling little-endian-ness of SPJ files
 */
//@SuppressWarnings("unused")
/*private*/ int Header::readInt2(QDataStream* s) /*throws java.io.IOException*/ {
//    int i1 = s.read() & 0xFF;
//    int i2 = s.read() & 0xFF;
//    return i1 + (i2 << 8);
 qint16 i;
 *s >> i;
 return i;
}

/*public*/ QString Header::typeAsString() {
    if (type == -1) {
        return " initial ";
    }
    if ((type >= 0) && (type < 7)) {
     QStringList names = QStringList() <<"(unused) "<<
            "WAV      "<<
            "SDF      "<<
            " CV data "<<
            " comment "<<
            ".map file"<<
            "WAV (mty)";
        return names[type];
    }
    // unexpected answer
    log->warn("Unexpected type = " + QString::number(type));
    return "Uknown " + QString::number(type);
}
//};

/**
* Class representing first header
*/
//class FirstHeader : public  Header {

/**
 * Number of headers, including the initial system header.
 */
int FirstHeader::numHeaders() {
    return (dataStart / 128);
}

float FirstHeader::version() {
    return recordStart / 100.f;
}

QString FirstHeader::getComment() {
    return filename;
}
FirstHeader::FirstHeader(SpjFile* f, QObject* parent)
 : Header(f,parent) {}


/*public*/ QString FirstHeader::toString() {
    return "initial record, version=" + QString::number(version()) + " num headers = " + QString::number(numHeaders())
            + ", comment= " + filename;
}
//};


/* @(#)SpjFile.java */
