#ifndef DIESEL3SOUND_H
#define DIESEL3SOUND_H
#include "enginesound.h"
#include <QMap>

class VSDFile;
class Logger;
class D3LoopThread;
class EnginePane;
class AudioBuffer;
class D3Notch;
class SoundBite;
class Diesel3Sound : public EngineSound
{
 Q_OBJECT
public:
 //explicit Diesel3Sound(QObject *parent = 0);
 /*public*/ Diesel3Sound(QString name,QObject *parent = 0);
 /*public*/ void setXml(QDomElement e, VSDFile* vf);
 /*private*/ void startThread();
 /*public*/ void play() ;
 /*public*/ void loop();
 /*public*/ void stop();
 /*public*/ void handleSpeedChange(float s, EnginePane* e);
 /*public*/ void changeThrottle(float s);
 /*public*/ D3Notch* getNotch(int n);
 /*public*/ void startEngine();
 /*public*/ void stopEngine() ;
 /*public*/ void shutdown();
 /*public*/ void mute(bool m) ;
 /*public*/ void setVolume(float v);
 /*public*/ void setPosition(PhysicalLocation* p) ;
 /*public*/ QDomElement getXml();

signals:

public slots:
private:
 QMap<int, D3Notch*> notch_sounds;
 SoundBite* _sound;
 QString _soundName;
 AudioBuffer* start_buffer;
 AudioBuffer* stop_buffer;
 AudioBuffer* transition_buf;

 // Common variables
 float throttle_setting; // used for handling speed changes
 EnginePane* engine_pane;

 int current_notch;// = 1;
 bool changing_speed;// = false;
 bool is_looping;// = false;
 D3LoopThread* _loopThread;// = null;

 QTimer* t;
 Logger* log;
protected:
 /*protected*/ QTimer* newTimer(long time, bool repeat, ActionListener* al);
 /*protected*/ void changeSpeed(float s, EnginePane* e);

};
/*private*/ /*static*/ class D3Notch  : public QObject
{
Q_OBJECT
    /*private*/ AudioBuffer* accel_buf;
    /*private*/ AudioBuffer* decel_buf;
    /*private*/ int my_notch, next_notch, prev_notch;
    /*private*/ float accel_limit, decel_limit;
    /*private*/ int loop_index;
    /*private*/ QList<AudioBuffer*>* loop_bufs;// = new ArrayList<AudioBuffer>();
    /*private*/ bool is_idle;
public:
    /*public*/ D3Notch() ;
    /*public*/ D3Notch(int notch, int next, int prev);
    /*public*/ D3Notch(int notch, int next, int prev, AudioBuffer* accel, AudioBuffer* decel, QList<AudioBuffer*>* loop);
    /*public*/ int getNextNotch() ;
    /*public*/ int getPrevNotch() ;
    /*public*/ int getNotch() ;
    /*public*/ AudioBuffer* getAccelBuffer() ;
    /*public*/ AudioBuffer* getDecelBuffer() ;
    /*public*/ float getAccelLimit();
    /*public*/ float getDecelLimit();
    /*public*/ bool isInLimits(float val) ;
    /*public*/ QList<AudioBuffer*>* getLoopBuffers();
    /*public*/ AudioBuffer* getLoopBuffer(int idx);
    /*public*/ long getLoopBufferLength(int idx);
    /*public*/ bool isIdleNotch();
    /*public*/ void setNextNotch(int n);
    /*public*/ void setNextNotch(QString s);
    /*public*/ void setPrevNotch(int p) ;
    /*public*/ void setPrevNotch(QString s) ;
    /*public*/ void setAccelLimit(float l);
    /*public*/ void setAccelLimit(QString s);
    /*public*/ void setDecelLimit(float l) ;
    /*public*/ void setDecelLimit(QString s);
    /*public*/ void setNotch(int n) ;
    /*public*/ void setAccelBuffer(AudioBuffer* b);
    /*public*/ void setDecelBuffer(AudioBuffer* b);
    /*public*/ void addLoopBuffer(AudioBuffer* b);
    /*public*/ void addLoopBuffers(QList<AudioBuffer*>* l);
    /*public*/ void setLoopBuffers(QList<AudioBuffer*>* l);
    /*public*/ void clearLoopBuffers();
    /*public*/ AudioBuffer* nextLoopBuffer();
    /*public*/ void setIdleNotch(bool i);
    /*public*/ int loopIndex() ;
    /*public*/ int incLoopIndex();
    static /*public*/ QList<AudioBuffer*>* getBufferList(VSDFile* vf, QString filename, QString sname, QString uname);
    static /*public*/ AudioBuffer* getBuffer(VSDFile* vf, QString filename, QString sname, QString uname);
    private:
    /*private*/ int setIntegerFromString(QString s);
    /*private*/ float setFloatFromString(QString s);

};
/*private*/ /*static*/ class D3LoopThread /*extends Thread*/ : public QObject
{
 Q_OBJECT
    /*private*/ bool is_running;// = false;
    /*private*/ bool is_looping;// = false;
    /*private*/ bool is_dying;// = false;
    Diesel3Sound* _parent;
    D3Notch* _notch;
    SoundBite* _sound;
    float _throttle;
    Logger* log;

    /*public*/ static /*final*/ int SLEEP_INTERVAL;// = 50;
    /*public*/ D3LoopThread(Diesel3Sound* p);
    /*public*/ D3LoopThread(Diesel3Sound* d, D3Notch* n, QString s, bool r) ;
    /*public*/ void setNotch(D3Notch* n);
    /*public*/ D3Notch* getNotch() ;
    /*public*/ void setSound(SoundBite* s);
    /*public*/ void setRunning(bool r) ;
    /*public*/ bool isRunning() ;
    /*public*/ void setThrottle(float t) ;
    /*public*/ void startEngine(AudioBuffer* start_buf) ;
    /*public*/ void stopEngine(AudioBuffer* stop_buf);
    /*public*/ void mute(bool m);
    /*public*/ void setVolume(float v) ;
    /*public*/ void setPosition(PhysicalLocation* p);
    /*public*/ void kill();

public slots:
    /*public*/ void process() ;
signals:
    void finished();
private:
    /*private*/ void changeNotch() ;
    friend class Diesel3Sound;
};
#endif // DIESEL3SOUND_H
