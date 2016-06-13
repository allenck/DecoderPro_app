#include "steamsound.h"
#include "logger.h"
#include <QTimer>
#include "soundbite.h"
#include <qmath.h>

//SteamSound::SteamSound()
//{
//}
// Usage:
// SteamSound() : constructor
// play() : plays short horn pop
// loop() : starts extended sustain horn
// stop() : ends extended sustain horn (plays end sound)
//class SteamSound extends EngineSound {

    // Inner class for handling steam RPM sounds
    //class RPMSound {

//        /*public*/ SoundBite sound;
//        /*public*/ int min_rpm;
//        /*public*/ int max_rpm;
//        /*public*/ boolean use_chuff;
//        private javax.swing.Timer t;

        /*public*/ RPMSound::RPMSound(SoundBite* sb, int min_r, int max_r, bool chuff, SteamSound* parent)
{
 this->parent = parent;
            sound = sb;
            min_rpm = min_r;
            max_rpm = max_r;
            use_chuff = chuff;
            if (use_chuff)
            {
                sound->setLooped(false);
//                t = newTimer(1000, true, new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        doChuff();
//                    }
//                });
                t = new QTimer();
                t->setInterval(1000);
                connect(t, SIGNAL(timeout()), this, SLOT(doChuff()));
            }
        }

        /*private*/ void RPMSound::doChuff() {
            sound->play();
        }

        /*public*/ void RPMSound::setRPM(int rpm) {
            if (use_chuff) {
                t->setInterval(parent->calcChuffInterval(rpm));
            }
        }

        /*public*/ void RPMSound::startChuff() {
            if (!t->isActive()) {
                t->start();
            }
        }

        /*public*/ void RPMSound::stopChuff() {
            t->stop();
        }
    //};


    /*public*/ SteamSound::SteamSound(QString name, QObject* parent)
     : EngineSound(name, parent){
        //super(name);
      log = new Logger("SteamSound");
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    //@Override
    /*public*/ void SteamSound::play() {
        log->debug("EngineSound Play");
        if (engine_started || auto_start_engine) {
            current_rpm_sound->sound->play();
            is_playing = true;
        }
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    //@Override
    /*public*/ void SteamSound::loop() {
        if ((engine_started || auto_start_engine)) {
            current_rpm_sound->sound->play();
            is_playing = true;
        }
    }

    //@Override
    /*public*/ void SteamSound::stop() {
        current_rpm_sound->sound->stop();
        is_playing = false;
    }

    /*public*/ void SteamSound::startEngine() {
        log->debug("Starting Engine");
        current_rpm_sound = getRPMSound(0);
        current_rpm_sound->sound->loop();
        engine_started = true;
    }

    /*public*/ void SteamSound::stopEngine() {
        current_rpm_sound->sound->fadeOut();
        engine_started = false;
    }

    /*private*/ RPMSound* SteamSound::getRPMSound(int rpm) {
        foreach (RPMSound* rps, rpm_sounds) {
            if ((rps->min_rpm <= rpm) && (rps->max_rpm >= rpm)) {
                return (rps);
            }
        }
        // Didn't find anything
        return (NULL);
    }

    /*private*/ int SteamSound::calcRPM(float t) {
        // Speed = % of top_speed (mph)
        // RPM = speed * ((inches/mile) / (minutes/hour)) / (pi * driver_diameter)
        double rpm_f = speedCurve(t) * top_speed * 1056 / (3.1415 * driver_diameter);
        log->debug("RPM Calculated: " + QString::number(rpm_f) + " (int) " + (int) qRound(rpm_f));
        return ((int) qRound(rpm_f));
    }

    /*private*/ double SteamSound::speedCurve(float t) {
        return (qPow(t, 2.0) / 1.0);
    }

    /*private*/ int SteamSound::calcChuffInterval(int rpm) {
        return (1000 * num_cylinders / rpm);
    }
#if 0
    @Override
    /*public*/ void changeThrottle(float t) {
        RPMSound rps;
        // Yes, I'm checking to see if rps and current_rpm_sound are the *same object*
        if (((rps = getRPMSound(calcRPM(t))) != null) && (rps != current_rpm_sound)) {
            // Stop the current sound
            if ((current_rpm_sound != null) && (current_rpm_sound.sound != null)) {
                current_rpm_sound.sound.fadeOut();
                if (current_rpm_sound.use_chuff) {
                    current_rpm_sound.stopChuff();
                }
            }
            // Start the new sound.
            current_rpm_sound = rps;
            if (rps.use_chuff) {
                rps.setRPM(calcRPM(t));
                rps.startChuff();
            }
            rps.sound.fadeIn();
        }
        log->debug("RPS = " + rps + " RPM = " + calcRPM(t) + " current_RPM = " + current_rpm_sound);
    }

    @Override
    /*public*/ void shutdown() {
        for (RPMSound rps : rpm_sounds) {
            rps.sound.stop();
        }
    }

    @Override
    /*public*/ void mute(boolean m) {
        for (RPMSound rps : rpm_sounds) {
            rps.sound.mute(m);
        }
    }

    @Override
    /*public*/ void setVolume(float v) {
        for (RPMSound rps : rpm_sounds) {
            rps.sound.setVolume(v);
        }
    }

    @Override
    /*public*/ void setPosition(PhysicalLocation p) {
        for (RPMSound rps : rpm_sounds) {
            rps.sound.setPosition(p);
        }
    }

    /*public*/ Element getXml() {
        // OUT OF DATE
        return (super.getXml());
    }
#endif
   // @Override
    /*public*/ void SteamSound::setXml(QDomElement e, VSDFile* vf) {
        QDomElement el;
        //int num_rpms;
        QString fn;
        SoundBite* sb;

        EngineSound::setXml(e, vf);

        log->debug("Steam EngineSound: " + e.attribute("name"));
        QString n = e.firstChildElement("top-speed").text();
        if (n != "") {
            top_speed = n.toInt();
            //log->debug("Top speed: " + top_speed + " MPH");
        }
        n = e.firstChildElement("driver-diameter").text();
        if (n != "") {
            driver_diameter = n.toInt();
            //log->debug("Driver diameter: " + driver_diameter + " inches");
        }
        n = e.firstChildElement("cylinders").text();
        if (n != "") {
            num_cylinders = n.toInt();
            //log->debug("Num Cylinders: " + num_cylinders);
        }
        // For now, num_rpms is not used.
 /*
         n = e.getChild("rpm-steps");
         if (n != null) {
         num_rpms = Integer.parseInt(n);
         //log->debug("Number of rpm steps: " + num_rpms);
         }
         */

        rpm_sounds = QList<RPMSound*>();

        // Get the RPM steps
        //Iterator<Element> itr = (e.getChildren("rpm-step")).iterator();
        QDomNodeList nl = e.elementsByTagName("rpm-step");
        //int i = 0;
        //while (itr.hasNext()) {
        for(int i = 0; i < nl.count(); i++)
        {

            el = nl.at(i).toElement(); //itr.next();
            fn = el.firstChildElement("file").text();
            int min_r = el.firstChildElement("min-rpm").text().toInt();
            int max_r =el.firstChildElement("max-rpm").text().toInt();
            //log->debug("Notch: " + nn + " File: " + fn);
            sb = new SoundBite(vf, fn, "Steam_n" + i, "Steam_" + i);
            sb->setLooped(true);
            sb->setFadeTimes(100, 100);
            sb->setGain(setXMLGain(el));
            // Store in the list.
            bool chuff = false;
            QDomElement c;
            if (!(c = el.firstChildElement("use-chuff-gen")).isNull()) {
                log->debug("Use Chuff Generator " + c.tagName());
                chuff = true;
            }

            rpm_sounds.append(new RPMSound(sb, min_r, max_r, chuff, this));
            //i++;
        }

        /*
         // Get the start and stop sounds
         el = e.getChild("start-sound");
         if (el != null) {
         fn = el.getChild("file");
         log->debug("Start sound: " + fn);
         start_sound = new SoundBite(vf, fn, "Engine_start",
         "Engine_Start");
         // Handle gain
         start_sound.setGain(setXMLGain(el));
         start_sound.setLooped(false);
         }
         */
    }

