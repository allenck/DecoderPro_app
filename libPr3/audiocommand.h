#ifndef AUDIOCOMMAND_H
#define AUDIOCOMMAND_H

#include <QObject>
#include "libPr3_global.h"

class Audio;
class LIBPR3SHARED_EXPORT AudioCommand : public QObject
{
 Q_OBJECT
public:
 //explicit AudioCommand(QObject *parent = 0);
 /*public*/ AudioCommand(Audio* audio, int command, QObject *parent = 0);
 /*public*/ /*synchronized*/ Audio* getAudio();
 /*public*/ /*synchronized*/ int getCommand();
 /*public*/ QString toString();

signals:

public slots:
private:
 /**
  * Private variables containing command parameters
  */
 /*private*/ Audio* audio;

 /*private*/ int command;
 /*private*/ QString commandString();

};

#endif // AUDIOCOMMAND_H
