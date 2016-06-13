#include "wavbuffer.h"
#include "file.h"
#include <QFile>
#include <QDataStream>
#include <QVector>
#include "logger.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QBuffer>
#include <QEventLoop>

//WavBuffer::WavBuffer(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Wrap a byte array to provide WAV file functionality
 *
 * @author	Bob Jacobsen Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
///*public*/ class WavBuffer {

/**
 * Create from already existing byte array. The array is expected to be in
 * .wav format, starting with a RIFF header.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "EI_EXPOSE_REP2") // OK until Java 1.6 allows cheap array copy
/*public*/ WavBuffer::WavBuffer(QVector<char>* content, QObject *parent)
 :  QObject(parent)
{
 buffer = content;
 log = new Logger("WavBuffer");
 loop = NULL;

 initFmt();
 initData();
}

/**
 * Create from contents of file. The file contents are expected to be in
 * .wav format, starting with a RIFF header.
 */
/*public*/ WavBuffer::WavBuffer(File* file, QObject *parent)  /*throws java.io.IOException*/
{
 log = new Logger("WavBuffer");

 if (file == NULL)
 {
//        throw new java.io.IOException("Null file during ctor");
 }
//    java.io.InputStream s = new java.io.BufferedInputStream(
//            new java.io.FileInputStream(file));
 QFile f(file->getPath());
 if(!f.open(QIODevice::ReadOnly))
 {
  return;
 }
 QDataStream* s = new QDataStream(&f);
//    try {
 buffer = new QVector<char>(file->length());
 s->readRawData(buffer->data(), file->length());

 initFmt();
 initData();
//    } catch (java.io.IOException e1) {
//        log->error("error reading file", e1);
//        throw e1;
//    } finally {
//        try {
//            s.close();
//        } catch (java.io.IOException e2) {
//            log->error("Exception closing file", e2);
//        }
//    }
 f.close();
}

/**
 * Find a specific header in the .wav fragment
 *
 * @return offset of the 1st byte of the header in the buffer
 */
/*public*/ int WavBuffer::findHeader(int i1, int i2, int i3, int i4) {
    // find chunk and set offset
 int index = 12; // skip RIFF header
 while (index < buffer->size())
 {
  // new chunk
  if (buffer->at(index) == i1
          && buffer->at(index + 1) == i2
          && buffer->at(index + 2) == i3
          && buffer->at(index + 3) == i4)
  {
      // found it, header in place
      return index;
  }
  else
  {
   // skip
   index = index + 8
           + fourByte(index + 4);
  }
 }
 log->error("Didn't find chunk");
 return 0;
}

/**
 * Cache info from (first) "fmt " header
 */
/*private*/ void WavBuffer::initFmt()
{
    fmtOffset = findHeader(0x66, 0x6D, 0x74, 0x20);
    if (fmtOffset > 0) {
        return;
    }
    log->error("Didn't find fmt chunk");
}

/**
 * Cache info from (first) "data" header
 */
/*private*/ void WavBuffer::initData() {
    dataOffset = findHeader(0x64, 0x61, 0x74, 0x61);
    if (dataOffset > 0) {
        return;
    }
    log->error("Didn't find data chunk");
}

/*public*/ float WavBuffer::getSampleRate() {
    return fourByte(fmtOffset + 12);
}

/*public*/ int WavBuffer::getSampleSizeInBits() {
    return twoByte(fmtOffset + 22);
}

/*public*/ int WavBuffer::getChannels() {
    return twoByte(fmtOffset + 10);
}

/*public*/ bool WavBuffer::getBigEndian() {
    return false;
}

/*public*/ bool WavBuffer::getSigned() {
    return (getSampleSizeInBits() > 8);
}

/**
 * Offset to the first data byte in the buffer
 */
/*public*/ int WavBuffer::getDataStart() {
    return dataOffset + 8;
}

/**
 * Size of the data segment in bytes
 */
/*public*/ int WavBuffer::getDataSize() {
    return fourByte(dataOffset + 4);
}

/**
 * Offset to the last data byte in the buffer. One more than this points to
 * the next header.
 */
/*public*/ int WavBuffer::getDataEnd() {
    return dataOffset + 8 + getDataSize() - 1;
}

int WavBuffer::twoByte(int index) {
    return buffer->at(index) + buffer->at(index + 1) * 256;
}

int WavBuffer::fourByte(int index)
{
 return (buffer->at(index) & 0xFF)
            + (buffer->at(index + 1) & 0xFF) * 256
            + (buffer->at(index + 2) & 0xFF) * 256 * 256
            + (buffer->at(index + 3) & 0xFF) * 256 * 256 * 256;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<char>* WavBuffer::getByteArray() {
    return buffer;
}

void WavBuffer::play()
{
 QAudioFormat format;

 format.setSampleSize(getSampleSizeInBits());
 format.setSampleRate((int)getSampleRate());
 format.setChannelCount(getChannels());
 format.setCodec("audio/pcm");
 format.setByteOrder(getBigEndian()?QAudioFormat::BigEndian: QAudioFormat::LittleEndian);
 format.setSampleType(getSigned()? QAudioFormat::SignedInt:QAudioFormat::UnSignedInt);

 QAudioOutput output(format);
 QByteArray data(buffer->mid(getDataStart(),getDataSize()).data(), getDataSize());
 QBuffer buf(&data);
 buf.open(QIODevice::ReadOnly);
 loop = new QEventLoop;
 output.start(&buf);
 //QObject::connect(&output, SIGNAL(stateChanged(QAudio::State)), &loop, SLOT(quit()));
 connect(&output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(onStateChanged(QAudio::State)));
 do {
     loop->exec();
 } while(loop->isRunning() && output.state() == QAudio::ActiveState);
 buf.close();
 output.reset();
}
void WavBuffer::onStateChanged(QAudio::State s)
{
 if(s == QAudio::ActiveState) return;
 QAudio::State state = s;
 loop->quit();
}
