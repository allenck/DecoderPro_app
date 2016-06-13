#ifndef QTSOUNDAUDIOCLIP_H
#define QTSOUNDAUDIOCLIP_H
#include "clip.h"
#include <QAudioFormat>

class FloatControl;
class QEventLoop;
class Logger;
class QAudioOutput;
class QBuffer;
class QtSoundAudioBuffer;
class QtSoundAudioClip : public Clip
{
 Q_OBJECT
public:
 explicit QtSoundAudioClip(QtSoundAudioBuffer* buffer, QObject *parent);
 /*public*/bool open(QAudioFormat *format, QByteArray *data, int offset, int bufferSize);
 /*public*/ void loop(int count);
 Control* getControl(Control::Type *control);
 bool isControlSupported(Control::Type *control);
 bool isRunning();
 bool isOpen();
signals:

public slots:

private:
 QtSoundAudioBuffer* buffer;
 QAudioFormat* format;
 QByteArray *data;
 int offset;
 int bufferSize;
 int loopCount;
 bool _running;
 bool _open;

 QByteArray* ba;
 QBuffer* buf;
 QAudioOutput* audioOut;
 Logger* log;
 QEventLoop* _loop;
};

#endif // QTSOUNDAUDIOCLIP_H
