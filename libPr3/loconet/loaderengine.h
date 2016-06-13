#ifndef LOADERENGINE_H
#define LOADERENGINE_H

#include <QObject>

class LocoNetMessage;
class Logger;
class LocoNetSystemConnectionMemo;
class SpjFile;
class LnTrafficController;
class LoaderEngine : public QObject
{
 Q_OBJECT
public:
 //explicit LoaderEngine(QObject *parent = 0);
 /*public*/ LoaderEngine(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);
 /*public*/ void runDownload(/*SpjFile* file*/);
 /*public*/ void setFile(SpjFile* file);
 /*public*/ void dispose();
 /*public*/ void sendOneWav(int index) /*throws DelayException*/;
 /*public*/ LocoNetMessage* nextTransfer();

signals:
 void finished();
 void error(QString err);
 void notify(QString);

public slots:
 void process();

private:
 LnTrafficController* controller;// = null;
 static /*final*/ int CMD_START;// = 0x04;
 static /*final*/ int CMD_ADD;// = 0x08;

 static /*final*/ int TYPE_SDF;// = 0x01;
 static /*final*/ int TYPE_WAV;// = 0x00;

 static /*final*/ int SENDPAGESIZE;// = 256;
 static /*final*/ int SENDDATASIZE;// = 128;
 SpjFile* spjFile;
 void sendSDF() /*throws DelayException*/;
 LocoNetSystemConnectionMemo* memo;
 void initController();
 void sendAllWAV() /*throws DelayException*/;
 void throttleOutbound(LocoNetMessage* m) /*throws DelayException*/;
 Logger* log;
 LocoNetMessage* initTransfer(int type, int handle, QString name, QVector<char>* contents);
 /*private*/ bool transferStart;
 /*private*/ int transferType;
 /*private*/ int transferHandle;
 /*private*/ QString transferName;
 /*private*/ QVector<char>* transferContents;
 /*private*/ int transferIndex;
 LocoNetMessage* getStartDataMessage(int type, int handle, int length);
 LocoNetMessage* getSendDataMessage(int type, int handle, QVector<char>* contents);
 LocoNetMessage* getEraseMessage();
 LocoNetMessage* getInitMessage();
 LocoNetMessage* getExitMessage();


};

#endif // LOADERENGINE_H
