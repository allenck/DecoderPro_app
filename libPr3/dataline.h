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

signals:

public slots:

};

#endif // DATALINE_H
