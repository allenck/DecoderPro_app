#ifndef OPSESSIONLOG_H
#define OPSESSIONLOG_H

#include <QObject>

class QFile;
class QTextStream;
class OpSessionLog : public QObject
{
 Q_OBJECT
public:
 //explicit OpSessionLog(QObject *parent = 0);
 /*public*/ static OpSessionLog* getInstance();
 /*synchronized*/ /*public*/ void writeLn(QString text);
 /*synchronized*/ /*public*/ void close();
 /*public*/ /*synchronized*/ bool showFileChooser(QObject* parent);

signals:

public slots:
private:
 /*private*/ static OpSessionLog* _instance;
 QTextStream* _outBuff;
 /*private*/ OpSessionLog(QObject *parent = 0);
 void writeHeader(QString fileName);
 QFile* qFile;
};

#endif // OPSESSIONLOG_H
