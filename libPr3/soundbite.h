#ifndef SOUNDBITE_H
#define SOUNDBITE_H
#include "vsdsound.h"

class Logger;
class VSDFile;
class AudioBuffer;
class AudioSource;
class SoundBite : public VSDSound
{
 Q_OBJECT
public:
 //explicit SoundBite(QObject *parent = 0);
 /*public*/ /*static*/ enum BufferMode {

     BOUND_MODE, QUEUE_MODE
 };
 /*public*/ SoundBite(QString name,QObject *parent = 0) ;
 // Constructor to replace QueueSoundBite, really.
 /*public*/ SoundBite(QString name, BufferMode mode, QObject *parent=0) ;
 // Constructor for backward compatibility
 /*public*/ SoundBite(VSDFile* vf, QString filename, QString sname, QString uname,QObject *parent=0) ;
 /*public*/ SoundBite(BufferMode mode, VSDFile* vf, QString filename, QString sname, QString uname,QObject *parent=0);
 /*public*/ QString getFileName() ;
 /*public*/ QString getSystemName();
 /*public*/ QString getUserName();
 /*public*/ bool isInitialized();
 /*public*/ /*final*/ bool init(VSDFile* vf, BufferMode mode);
 /*public*/ void queueBuffer(AudioBuffer* b);
 /*public*/ void unqueueBuffers();
 /*public*/ int numQueuedBuffers();
 // Direct access to the underlying source.  use with caution.
 /*public*/ AudioSource* getSource();
 // WARNING: This will go away when we go to shared buffers... or at least it will
 // have to do the name lookup on behalf of the caller...
 /*public*/ AudioBuffer* getBuffer() ;
 // These can(?) be used to get the underlying AudioSource and AudioBuffer objects
 // from the DefaultAudioManager.
 /*public*/ QString getSourceSystemName() ;
 /*public*/ QString getSourceUserName() ;
 /*public*/ QString getBufferSystemName();
 /*public*/ QString getBufferUserName();
 /*public*/ void setLooped(bool loop, int minloops, int maxloops);
 /*public*/ void setLooped(bool loop);
 /*public*/ bool isLooped();
 /*public*/ int getFadeInTime();
 /*public*/ int getFadeOutTime() ;
 /*public*/ void setFadeInTime(int t);
 /*public*/ void setFadeOutTime(int t) ;
 /*public*/ void setFadeTimes(int in, int out);
 /*public*/ void shutdown() ;
 /*public*/ void mute(bool m);
 /*public*/ void setVolume(float v);
 /*public*/ void play();
 /*public*/ void loop();
 /*public*/ void stop() ;
 /*public*/ void pause();
 /*public*/ void rewind();
 /*public*/ void fadeOut();
 /*public*/ void fadeIn();
 /*public*/ void setPosition(PhysicalLocation* v);
 /*public*/ void setURL(QString filename);
 /*public*/ long getLength() ;
 /*public*/ int getLengthAsInt();
 /*public*/ void setLength(long p) ;
 /*public*/ void setLength();
 /*public*/ static long calcLength(SoundBite* s) ;
 /*public*/ static long calcLength(AudioBuffer* buf);

signals:

public slots:
private:
 QString filename, system_name, user_name;
 AudioBuffer* sound_buf;
 AudioSource* sound_src;
 bool initialized;// = false;
 bool looped;// = false;
 bool buf_loaded;// = false;
 int minloops;
 int maxloops;
 long length;
 BufferMode bufferMode;
 QList<AudioBuffer*> loopBufferList;// = new ArrayList<AudioBuffer>();
 void common();
 Logger* log;
 friend class NotchTransition;
};

#endif // SOUNDBITE_H
