#ifndef STEAMSOUND_H
#define STEAMSOUND_H
#include "enginesound.h"

class Logger;
class VSDFile;
class SoundBite;
class SteamSound;
// Inner class for handling steam RPM sounds
class RPMSound : public QObject
{
 Q_OBJECT
 /*private*/ QTimer* t;
 SteamSound* parent;
public:
    /*public*/ SoundBite* sound;
    /*public*/ int min_rpm;
    /*public*/ int max_rpm;
    /*public*/ bool use_chuff;

    /*public*/ RPMSound(SoundBite* sb, int min_r, int max_r, bool chuff, SteamSound* parent);
    /*public*/ void setRPM(int rpm);
    /*public*/ void startChuff() ;
    /*public*/ void stopChuff();

private slots:
 /*private*/ void doChuff();
};
class SteamSound : public EngineSound
{
 Q_OBJECT
public:
 /*public*/ SteamSound(QString name, QObject* parent = 0);
 /*public*/ void setXml(QDomElement e, VSDFile* vf);
 /*public*/ void play();
 /*public*/ void loop() ;
 /*public*/ void stop();
 /*public*/ void startEngine() ;
 /*public*/ void stopEngine();

private:
 // Engine Sounds
 QList<RPMSound*> rpm_sounds;
 SoundBite* idle_sound;
 int top_speed;
 int driver_diameter;
 int num_cylinders;
 RPMSound* current_rpm_sound;
 int current_chuff_time;
 Logger* log;
 /*private*/ int calcChuffInterval(int rpm);
 /*private*/ RPMSound* getRPMSound(int rpm);
 /*private*/ int calcRPM(float t);
 /*private*/ double speedCurve(float t);

 friend class RPMSound;

};

#endif // STEAMSOUND_H
