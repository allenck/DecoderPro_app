#ifndef CLIP_H
#define CLIP_H

#include <QObject>
#include "dataline.h"
#include "libPr3_global.h"

class AudioInputStream;
class QAudioFormat;
class LIBPR3SHARED_EXPORT Clip : public DataLine
{
 Q_OBJECT
public:
 explicit Clip(QObject *parent = 0);
 /*public*/ static /*final*/ int LOOP_CONTINUOUSLY;// = -1;
 virtual /*public*/ bool open(QAudioFormat* format, QByteArray* data, int offset, int bufferSize) /*throws LineUnavailableException*/;
 virtual     /*public*/ void open(AudioInputStream* stream) /*throws LineUnavailableException, IOException*/;
 virtual     /*public*/ int getFrameLength();
 virtual /*public*/ long getMicrosecondLength();
 virtual /*public*/ void setFramePosition(int frames);
 virtual /*public*/ void setMicrosecondPosition(long microseconds);
 virtual /*public*/ void setLoopPoints(int start, int end);
 virtual /*public*/ void loop(int count);
signals:

public slots:

};

#endif // CLIP_H
