#include "wavfilereader.h"
#include <QFile>
#include <QVector>
#include <QDebug>
#include <QtEndian>
#include <QDataStream>
#include "audioformat.h"
#include "logger.h"
#include <QAudioDeviceInfo>
#include <QBuffer>
#include <QAudioOutput>
#include <QEventLoop>

WavFileReader::WavFileReader(QObject *parent) :
  AudioFileReader(parent)
{
 f = QAudioFormat();
 log = new Logger("WavFileReader");
}
void WavFileReader::readWAV(QString wavFile)
{
 QFile m_WAVFile;
 m_WAVFile.setFileName(wavFile);
 m_WAVFile.open(QIODevice::ReadWrite);

 char* strm = NULL;
 QVector<double> m_DATA;

 /*qDebug()<<*/
 QByteArray hdr = m_WAVFile.read(4);//RIFF
 // m_WAVHeader.RIFF = m_WAVFile.read(4).data();

 m_WAVFile.read(strm,4);//chunk size
 /*qDebug()<<*/
 qint32 chunkSize = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,4);//format
 /*qDebug()<<*/
 char* format = strm;

 m_WAVFile.read(strm,4);//subchunk1 id
 /*qDebug()<<strm;*/
 char* subChunk1Id = strm;

 m_WAVFile.read(strm,4);//subchunk1 size
 /*qDebug()<<*/
 quint32 subChunk1Size = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,2);//audio format
 /*qDebug()<<*/
 quint32 audioFormat = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,2);//NumChannels
 quint32 numChannels = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,4);//Sample rate
 /*qDebug()<<*/
 quint32 sampleRate = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,4);//Byte rate
 /*qDebug()<<*/
 quint32 byteRate = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,2);//Block Allign
 /*qDebug()<<*/
 quint32 blockAlign = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,2);//BPS
 /*qDebug()<<*/
 quint32 bps = qFromLittleEndian<quint32>((uchar*)strm);

 m_WAVFile.read(strm,4);//subchunk2 id
 //qDebug()<<strm;
 char* subChunk2Id = strm;

 m_WAVFile.read(strm,4);//subchunk2 size
 /*qDebug()<<*/
 quint32 subChunk2Size = qFromLittleEndian<quint32>((uchar*)strm);

 while(!m_WAVFile.atEnd())
 {
  m_WAVFile.read(strm,2);
  if(qFromLittleEndian<short>((uchar*)strm))
  m_DATA << (qFromLittleEndian<short>((uchar*)strm));
 }
 // populate QAudioFormat
 f.setByteOrder(QAudioFormat::LittleEndian);
 f.setChannelCount(numChannels);
 f.setCodec("audio/pcm");
 f.setSampleRate(sampleRate);
 f.setSampleSize(bps);
 f.setSampleType(bps > 8? QAudioFormat::SignedInt:QAudioFormat::UnSignedInt);
}

/*public*/ AudioFileFormat* WavFileReader::getAudioFileFormat(File* file)
{
 QFile* qfile = new QFile(file->getPath());
 if(!qfile->open(QIODevice::ReadOnly))
 {
  log->error("unable to open audio file: "+file->getPath());
  return NULL;
 }
 QDataStream* stream = new QDataStream(qfile);
 return getAudioFileFormat(stream);
}

/*public*/ AudioFileFormat* WavFileReader::getAudioFileFormat(QDataStream* stream)
{
 stream->setByteOrder(QDataStream::LittleEndian);
 char hdr[4];
 uint len=0;
 len = stream->readRawData(hdr,4);
 if(memcmp(hdr,"RIFF", 4) != 0)
 {
  log->debug("RIFF hdr not found!");
  return NULL;
 }
 qint32 chunkSize;
 *stream >> chunkSize;
 char format[4];
 len = stream->readRawData(format, 4);
 if(memcmp(format, "WAVE", 4) != 0)
 {
  log->debug("format not \"WAVE\"");
  return NULL;
 }
 char subChunk1Id[4];
 len = stream->readRawData(subChunk1Id, 4);
 qint32 subChunk1Size;
 *stream >> subChunk1Size;  // fmt chunk size;
 quint16 audioFormat;
 *stream >> audioFormat;
 quint16 numChannels;
 *stream >> numChannels;
 quint32 sampleRate;
 *stream >> sampleRate;
 quint32 byteRate ;
 *stream >> byteRate;
 quint16 blockAlign;
 *stream >> blockAlign;
 quint16 bps;
 qint16 fmtExtra;
 *stream >> bps;
 if(subChunk1Size == 18)
  *stream >> fmtExtra;
 char subChunk2Id[4];
 qint32 factSize;
 qint32 dwSampleSize;
 quint32 subChunk2Size;

 len = stream->readRawData(subChunk2Id, 4);
 while (memcmp(subChunk2Id, "data",4)!= 0)
 {
  if(stream->atEnd())
  {
   log->debug("EOF data chunk not found");
   return NULL;
  }

  if(memcmp(subChunk2Id, "fact", 4) == 0)
  {
   *stream >> factSize;
   *stream >> dwSampleSize;
  }
  else
  {
   *stream >> subChunk2Size;
   stream->skipRawData(subChunk2Size);
  }
  len = stream->readRawData(subChunk2Id, 4);
 }
// if(memcmp(subChunk2Id, "data",4)!= 0)
// {
//  log->debug("data chunk not found");
//  return NULL;
// }
 qint64 pos = stream->device()->pos();
 ba = new QByteArray;
 int i = 0;
 while (!(stream->atEnd()))
 {
  qint8 c;
  *stream >> c;
  ba->insert(i++, c);
 }
 stream->device()->seek(pos);

 log->debug(QString("Wave file buffer subChunk2ize = %1, QByteArray size = %2").arg(subChunk2Size).arg(ba->size()));
 QStringList l = QAudioDeviceInfo::defaultOutputDevice(). supportedCodecs();
 f = QAudioDeviceInfo::defaultOutputDevice().preferredFormat();
 f.setByteOrder(QAudioFormat::LittleEndian);
 f.setChannelCount(numChannels);
 f.setCodec("audio/pcm");
 f.setSampleRate(sampleRate);
 f.setSampleSize(bps);
 f.setSampleType(bps > 8? QAudioFormat::SignedInt:QAudioFormat::UnSignedInt);

#if 0 // test code
 // test code
 QAudioFormat fmt;
 fmt.setSampleSize(bps);
 fmt.setSampleRate(sampleRate);
 fmt.setChannelCount(numChannels);
 fmt.setCodec("audio/pcm");
 fmt.setByteOrder(QAudioFormat::LittleEndian);
 fmt.setSampleType(bps > 8? QAudioFormat::SignedInt:QAudioFormat::UnSignedInt);

  QBuffer* buf = new QBuffer(ba);
 if(!buf->open(QIODevice::ReadOnly))
  log->error("Error opening sound buffer");
 buf->seek(0);
 QAudioOutput*  audioOut = new QAudioOutput(fmt);
 loop = new QEventLoop;
 audioOut->start(buf);
 connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(onStateChanged(QAudio::State)));
 do {
     loop->exec();
 } while(loop->isRunning() && audioOut->state() == QAudio::ActiveState);
 buf->close();
 audioOut->reset();
#endif
// TODO: fix encoding parameter
 return new AudioFileFormat(new AudioFileFormat::Type("Wave", "wav"),new AudioFormat(nullptr,(float)sampleRate,bps,numChannels,0,(float)0.0,false), 0);
}

void WavFileReader::onStateChanged(QAudio::State s)
{
 if(s == QAudio::ActiveState) return;
 QAudio::State state = s;
 loop->quit();
}

/*public*/ AudioInputStream* WavFileReader::getAudioInputStream(File *file)
{
 AudioFileFormat* f = getAudioFileFormat(file);
 if(f == NULL)
  return NULL;
 AudioInputStream* as = new AudioInputStream(new QDataStream(ba, QIODevice::ReadOnly),&this->f,ba->size()/2);
 return as;
}

/*public*/ AudioInputStream* WavFileReader::getAudioInputStream(QDataStream* stream)
{
 AudioFileFormat* f = getAudioFileFormat(stream);
 if(f == NULL)
  return NULL;
 AudioInputStream* as = new AudioInputStream(new QDataStream(ba, QIODevice::ReadOnly),&this->f,ba->size()/2);
 return as;
}
