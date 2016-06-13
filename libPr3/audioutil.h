#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include <QObject>
#include "libPr3_global.h"

class AudioByteBuffer;
class AudioBuffer;
class LIBPR3SHARED_EXPORT AudioUtil : public QObject
{
 Q_OBJECT
public:
 explicit AudioUtil(QObject *parent = 0);
 /*public*/ static QList<AudioBuffer*>* getAudioBufferList(QString prefix, QDataStream* stream, int max_time, int min_time);
 static /*public*/ QList<AudioBuffer*>* getAudioBufferList(QString prefix, QList<AudioByteBuffer>* blist);

signals:
private:
 static /*private*/ QList<AudioByteBuffer>* splitInputStream(QDataStream* stream, int max_time, int min_time);

public slots:

};
/*private*/ /*static*/ class AudioByteBuffer
{
    /*public*/ QByteArray data;
    /*public*/ int format;
    /*public*/ int frequency;
    //@SuppressWarnings("unused")
    /*public*/ int loop;

    /*public*/ AudioByteBuffer(QByteArray d, int fmt, int freq, int lp);
 friend class AudioUtil;
};
#endif // AUDIOUTIL_H
