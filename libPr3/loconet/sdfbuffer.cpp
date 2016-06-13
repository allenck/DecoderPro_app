#include "sdfbuffer.h"
#include "file.h"
#include <QFile>
#include <QDataStream>
#include <QVector>
#include "sdfmacro.h"
#include "logger.h"

//SdfBuffer::SdfBuffer(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Provide tools for reading, writing and accessing Digitrax SPJ files.
 * <P>
 * Maintains several representations:
 * <UL>
 * <LI>A byte array of the SDF contents after assembly. This is not complete, as
 * it can't contain information like contents, labels, etc. Nor can it
 * distinguish certain options with identical values (e.g. several constants
 * that boil down to a zero value)
 * <LI>An array of nested SdfMacro objects. These contain more detailed
 * representations of the macro source, in the limit containing the entire
 * thing.
 * </UL>
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008, 2010
 * @version $Revision: 28746 $
 */
///*public*/ class SdfBuffer {

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "EI_EXPOSE_REP2") // OK until Java 1.6 allows cheap array copy
/*public*/ SdfBuffer::SdfBuffer(QVector<char>* buffer, QObject *parent) :
  QObject(parent)
{
 log = new Logger("SdfBuffer");
 this->buffer = buffer;
 loadMacroList();
}

/*public*/ SdfBuffer::SdfBuffer(QString name, QObject *parent) :
  QObject(parent) /*throws IOException*/
{
 log = new Logger("SdfBuffer");
 File file(name);
 int length = (int) file.length();
 QFile f(file.getPath());
 if(!f.open(QIODevice::ReadOnly))
 {
  emit error(f.errorString());
  return;
 }

 //QDataStream* s = new java.io.BufferedInputStream(new java.io.FileInputStream(file));
 QDataStream* s = new QDataStream(&f);
 s->setByteOrder(QDataStream::LittleEndian);

 //try {
     // Assume we can get all this in memory
  buffer = new QVector<char>(length);

  for (int i = 0; i < length; i++)
  {
   char c;
   int cnt = s->readRawData(&c, 1);
   if(cnt != 1)
   {
    emit error("Error reading file");
    return;
   }
   buffer->replace(i, c & 0xFF);
  }
  loadMacroList();
//    } catch (java.io.IOException e1) {
//        log->error("error reading file", e1);
//        throw e1;
//    } finally {
//        try {
   s->device()->close();
//        } catch (java.io.IOException e2) {
//            log->error("Exception closing file", e2);
//        }
//    }
}


/*public*/ void SdfBuffer::resetIndex() {
    index = 0;
}

/*public*/ int SdfBuffer::getAtIndex() {
    return buffer->at(index) & 0xFF;
}

/*public*/ int SdfBuffer::getAtIndexAndInc() {
    return buffer->at(index++) & 0xFF;
}

/*public*/ bool SdfBuffer::moreData() {
 return index < buffer->size();
}

/*public*/ void SdfBuffer::setAtIndex(int data) {
    buffer->replace(index, (char) (data & 0xFF));
}

/*public*/ void SdfBuffer::setAtIndexAndInc(int data) {
    buffer->replace(index++, (char) (data & 0xFF));
}

/**
 * Reload the byte buffer from the contained instruction objects
 */
/*public*/ void SdfBuffer::loadByteArray() {
    // first get length of new array
    int length = 0;
    for (int i = 0; i < ops->size(); i++) {
        length += ops->at(i)->totalLength();
    }
    buffer = new QVector<char>(length);
    log->debug("create buffer of length " + QString::number(length));
    resetIndex();
    // recurse to store bytes
    for (int i = 0; i < ops->size(); i++) {
        ops->at(i)->loadByteArray(this);
    }
    if (index != length) {
        log->error("Lengths did not match: " + QString::number(index) + " " + QString::number(length));
    }
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ QString SdfBuffer::toString()
{
 QString out = "";
 for (int i = 0; i < ops->size(); i++)
 {
  SdfMacro* m = ops->at(i);

  out += m->allInstructionString("    ");
 }
 return out;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
/*public*/ QVector<char>* SdfBuffer::getByteArray() {
    return buffer;
}

/*public*/ QList<SdfMacro*>* SdfBuffer::getMacroList() {
    return ops;
}

void SdfBuffer::loadMacroList() {
    resetIndex();
    ops = new QList<SdfMacro*>();
    while (moreData()) {
        SdfMacro* m = SdfMacro::decodeInstruction(this);
        ops->append(m);
    }
}

