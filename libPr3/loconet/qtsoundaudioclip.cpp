#include "qtsoundaudioclip.h"
#include "qtsoundaudiobuffer.h"
#include <QAudioOutput>
#include "logger.h"
#include <qtsoundaudiosource.h>
#include <QBuffer>
#include <QEventLoop>

QtSoundAudioClip::QtSoundAudioClip(QtSoundAudioBuffer* buffer, QObject *parent) :
  Clip(parent)
{
 this->buffer = buffer;
 log = new Logger("QtSoundAudioClip");
 log->setDebugEnabled(true);
 _loop = NULL;
 _running = false;
 _open = false;
}

// Implemetation of Clip interface for Qt.
/*public*/bool QtSoundAudioClip::open(QAudioFormat *format, QByteArray *data, int offset, int bufferSize)
{
 this->format = format;
 this->data = data;
 this->offset = offset;
 this->bufferSize = bufferSize;

 if(buffer !=NULL && buffer->getState() == AudioBuffer::STATE_LOADED)
 {
  QByteArray newBa = buffer->getDataStorageBuffer()->mid(offset, bufferSize);
  ba = new QByteArray(newBa);
  buf = new QBuffer(ba);
  if(!buf->open(QIODevice::ReadOnly))
   log->error("Error opening sound buffer");

  QAudioFormat qFormat = *buffer->getAudioFormat();
  log->debug(QString("qFormat(bind): channnels %1, codec: %2, sampleRate: %3, sampleSize: %4, bufferSize: %5").arg(qFormat.channelCount()).arg(qFormat.codec()).arg(qFormat.sampleRate()).arg(qFormat.sampleSize()).arg(ba->size()));
  audioOut = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(),QAudioFormat(*buffer->getAudioFormat()), this);
#if 0 // Test code
  if(_loop == NULL)
   _loop = new QEventLoop;
  connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChanged(QAudio::State)));
  audioOut->start(buf);
  do
  {
   _loop->exec();
  } while(_loop->isRunning() && audioOut->state() == QAudio::ActiveState);
  audioOut->reset();
#endif// end test code
  if (log->isDebugEnabled())
  {
   log->debug("Bind QtSoundAudioSource (" + ((QtSoundAudioSource*)parent())->getSystemName()
              + ") to QtSoundAudioBuffer (" +buffer->getSystemName() + ")");
  }

  ((QtSoundAudioSource*)parent())->setBound(true);

  _open = true;
  return true;
 }
 else
 {
  log->warn("AudioBuffer not loaded error when binding QtSoundSource (" + ((QtSoundAudioSource*)parent())->getSystemName()
          + ") to AudioBuffer (" + ((QtSoundAudioSource*)parent())->getAssignedBufferName() + ")");
  return false;
 }
}

void QtSoundAudioClip::loop(int count)
{
 this->loopCount = count;

 while (loopCount > 0)
 {
  QtSoundAudioBuffer* audioBuffer = (QtSoundAudioBuffer*)buffer;
  if(log->isDebugEnabled()) log->debug(QString("play sound: buffersize = %1").arg(buf->size()));
  QAudioFormat* qFormat = buffer->getAudioFormat();
  log->debug(QString("qFormat(doResume): channnels %1, codec: %2, sampleRate: %3, sampleSize: %4, bufferSize: %5").arg(qFormat->channelCount()).arg(qFormat->codec()).arg(qFormat->sampleRate()).arg(qFormat->sampleSize()).arg(buf->size()));

  if(!buf->isOpen())
  {
   if(!buf->open(QIODevice::ReadOnly))
   {
    log->error("error opening sound buffer");
    return;
   }
  }
  buf->seek(0);
  if(_loop == NULL)
   _loop = new QEventLoop;
  connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChanged(QAudio::State)));
#if QT_VERSION >= 0x050000
  audioOut->setVolume(((QtSoundAudioSource*)parent())->getGain());
#endif
  audioOut->start(buf);
  ((QtSoundAudioSource*)parent())->setState(Audio::STATE_PLAYING);

  _running = true;
  do
  {
   _loop->exec();
   if(audioOut->error() != QAudio::NoError)
    _loop->quit();
  } while(_loop->isRunning() && audioOut->state() == QAudio::ActiveState);

  if (log->isDebugEnabled())
  {
   log->debug("Resume QtSoundAudioSource (" + ((QtSoundAudioSource*)parent())->getSystemName()
              + ") to QtSoundAudioBuffer (" + audioBuffer->getSystemName() + ")");
  }
  audioOut->reset();
  _running = false;
  loopCount--;
 }
 ((QtSoundAudioSource*)parent())->setState(Audio::STATE_STOPPED);
}

Control* QtSoundAudioClip::getControl(Control::Type *control)
{
 return NULL; // temp stub code
}
bool QtSoundAudioClip::isControlSupported(Control::Type *control)
{
 return false; // for now, not supported.
}
bool QtSoundAudioClip::isRunning()
{
 return _running;
}
bool QtSoundAudioClip::isOpen()
{
 return _open;
}
