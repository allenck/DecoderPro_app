#ifndef DATALINE_H
#define DATALINE_H

#include <QObject>
#include "line.h"

class AudioFormat;
class DataLine : public Line
{
 Q_OBJECT
public:
 explicit DataLine(QObject *parent = 0);
 virtual /*public*/ void drain();
 virtual /*public*/ void flush();
 virtual /*public*/ void start();
 virtual /*public*/ void stop();
 virtual /*public*/ bool isRunning();
 virtual /*public*/ bool isActive();
 virtual /*public*/ AudioFormat* getFormat();
 virtual /*public*/ int getBufferSize();
 virtual /*public*/ int available();
 virtual /*public*/ int getFramePosition();
 virtual /*public*/ long getLongFramePosition();
 virtual /*public*/ long getMicrosecondPosition();
 virtual /*public*/ float getLevel();
 /*public*/ /*static*/ class Info : public Line::Info {

     /*private*/ /*final*/ QList<AudioFormat*> formats;
     /*private*/ /*final*/ int minBufferSize;
     /*private*/ /*final*/ int maxBufferSize;
 public:
     /*public*/ Info(/*Class<?>*/QString lineClass, QList<AudioFormat*> formats, int minBufferSize, int maxBufferSize);
     /*public*/ Info(/*Class<?>*/QString lineClass, AudioFormat* format, int bufferSize);
     /*public*/ Info(/*Class<?>*/QString lineClass, AudioFormat* format);
     /*public*/ QList<AudioFormat*> getFormats();
     /*public*/ bool isFormatSupported(AudioFormat* format);
     /*public*/ int getMinBufferSize() ;
     /*public*/ int getMaxBufferSize() ;
     /*public*/ bool matches(Line::Info* info);
     /*public*/ QString toString();
 }; // class Info

signals:

public slots:

};

#endif // DATALINE_H
