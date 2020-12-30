#include "configurablesound.h"
#include "logger.h"
#include "soundbite.h"
#include <QTimer>

//ConfigurableSound::ConfigurableSound(QObject *parent) :
//  VSDSound(parent)
//{
//}
// Usage:
// HornSound() : constructor
// play() : plays short horn pop
// loop() : starts extended sustain horn
// stop() : ends extended sustain horn (plays end sound)
//class ConfigurableSound extends VSDSound {


/*public*/ ConfigurableSound::ConfigurableSound(QString name, QObject *parent) :
VSDSound(name, parent) {
    //super(name);
    start_sound_duration = 136;
    use_start_sound = false;
    use_mid_sound = false;
    use_end_sound = false;
    use_short_sound = false;
    is_playing = false;
    log = new Logger("ConfigurableSound");
}

/*public*/ bool ConfigurableSound::init() {
    return (this->init(NULL ));
}

/*public*/ bool ConfigurableSound::init(VSDFile* vf) {

    if (!initialized) {
        if (use_start_sound) {
            start_sound = new SoundBite(vf, start_file, name + "_Start", name + "_Start");
            start_sound->setLooped(false);
            start_sound->setGain(gain);
        }
        if (use_mid_sound) {
            mid_sound = new SoundBite(vf, mid_file, name + "_Mid", name + "_Mid");
            mid_sound->setLooped(false);
            mid_sound->setGain(gain);
        }
        if (use_end_sound) {
            end_sound = new SoundBite(vf, end_file, name + "_End", name + "_End");
            end_sound->setLooped(false);
            end_sound->setGain(gain);
        }
        if (use_short_sound) {
            short_sound = new SoundBite(vf, short_file, name + "_Short", name + "_Short");
            short_sound->setLooped(false);
            short_sound->setGain(gain);
        }

    }
    return (true);
}

//@Override
/*public*/ bool ConfigurableSound::isPlaying() {
    return (is_playing);
}

/*public*/ void ConfigurableSound::play() {
    if (use_short_sound) {
        short_sound->play();
        is_playing = false; // short sound, won't be playing long...
    } else {
        if (use_start_sound) {
//                t = newTimer(start_sound->getLengthAsInt(), false,
//                        new ActionListener() {
//                            /*public*/ void actionPerformed(ActionEvent e) {
//                                handleTimerPop(e);
//                            }
//                        });
         t = new QTimer();
         t->setInterval(start_sound->getLengthAsInt());
         connect(t, SIGNAL(timeout()), this, SLOT(handleTimerPop()));
            start_sound->play();
            if (use_mid_sound) {
                t->start();
                is_playing = true;
            }
        } else if (use_mid_sound) {
            mid_sound->setLooped(true);
            mid_sound->play();
        }
    }
}

/*public*/ void ConfigurableSound::loop() {
    if (use_start_sound) {
        start_sound->setLooped(false);
        start_sound->play();
        t = new QTimer();
        t->setInterval(start_sound->getLengthAsInt() - 100);
//            t = newTimer(start_sound->getLengthAsInt() - 100, false,
//                    new ActionListener() {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            handleTimerPop(e);
//                        }
//                    });
        t->setSingleShot(true); // timer pop only once to trigger the sustain sound.
        connect(t, SIGNAL(timeout()), this, SLOT(handleTimerPop()));
        t->start();
    } else if (use_mid_sound) {
        mid_sound->setLooped(true);
        mid_sound->play();
    }
    is_playing = true;
}

// Catch the timer pop after the start sound is played and trigger the (looped) sustain sound.
/*protected*/ void ConfigurableSound::handleTimerPop(JActionEvent* /*e*/) {
    log->info("Received timer pop after start sound played.");
    //TODO: Need to validate that this is the timer pop
    if (use_mid_sound) {
        mid_sound->setLooped(true);
        mid_sound->play();
    }
    t->stop();
}

/*public*/ void ConfigurableSound::stop() {
    log->warn("Stopping");
    // make sure the start sound is killed
    if (use_start_sound) {
        start_sound->stop();
    }

    // If the mid sound is used, turn off the looping.
    // this will allow it to naturally die.
    if (use_mid_sound) {
        mid_sound->setLooped(false);
        mid_sound->fadeOut();
    }

    // If the timer is running, stop it.
    if (t != NULL ) {
        t->stop();
    }

    // If we're using the end sound, stop the mid sound
    // and play the end sound.
    if (use_end_sound) {
        if (use_mid_sound) {
            mid_sound->stop();
        }
        end_sound->setLooped(false);
        end_sound->play();
    }
    is_playing = false;
}

/*public*/ void ConfigurableSound::fadeIn() {
    this->play();
}

/*public*/ void ConfigurableSound::fadeOut() {
    this->stop();
}

/*public*/ void ConfigurableSound::shutdown() {
    if (use_start_sound) {
        start_sound->stop();
    }
    if (use_mid_sound) {
        mid_sound->stop();
    }
    if (use_end_sound) {
        end_sound->stop();
    }
    if (use_short_sound) {
        short_sound->stop();
    }
}

//@Override
/*public*/ void ConfigurableSound::mute(bool m) {
    if (use_start_sound) {
        start_sound->mute(m);
    }
    if (use_mid_sound) {
        mid_sound->mute(m);
    }
    if (use_end_sound) {
        end_sound->mute(m);
    }
    if (use_short_sound) {
        short_sound->mute(m);
    }
}

//@Override
/*public*/ void ConfigurableSound::setVolume(float v) {
    if (use_start_sound) {
        start_sound->setVolume(v);
    }
    if (use_mid_sound) {
        mid_sound->setVolume(v);
    }
    if (use_end_sound) {
        end_sound->setVolume(v);
    }
    if (use_short_sound) {
        short_sound->setVolume(v);
    }
}

//@Override
/*public*/ void ConfigurableSound::setPosition(PhysicalLocation* p) {
    VSDSound::setPosition(p);
    if (use_start_sound) {
        start_sound->setPosition(p);
    }
    if (use_mid_sound) {
        mid_sound->setPosition(p);
    }
    if (use_end_sound) {
        end_sound->setPosition(p);
    }
    if (use_short_sound) {
        short_sound->setPosition(p);
    }
}

//@Override
/*public*/ QDomElement ConfigurableSound::getXml() {
    //QDomElement me = new Element("sound");
QDomElement me = QDomElement();
me.setTagName("sound");
    int i;

    log->debug("Configurable Sound:");
    log->debug("  name = " + this->getName());
    log->debug("  start_file = " + start_file);
    log->debug("  mid_file = " + mid_file);
    log->debug("  end_file = " + end_file);
    log->debug("  short_file = " + short_file);
    log->debug("  use_start_file = " + start_file);

    me.setAttribute("name", this->getName());
    me.setAttribute("type", "configurable");
    if (use_start_sound)
    {
     QDomElement e = QDomElement();
     e.setTagName("start-file");
     QDomText t = QDomText();
     t.setData(start_file);
     e.appendChild(t);
        //me->appendChild(new Element("start-file").addContent(start_file));
     me.appendChild(e);
    }
#if 0
    if (use_mid_sound)
    {
        me.appendChild(new Element("mid-file").addContent(mid_file));
    }
    if (use_end_sound)
    {
        me.appendChild(new Element("end-file").addContent(end_file));
    }
    if (use_short_sound)
    {
        me.appendChild(new Element("short-file").addContent(short_file));
    }
    i = start_sound_duration;
    log->debug("  duration = " + i.toString());
    me.addContent(new Element("start-sound-duration").addContent(i.toString()));
#endif
    return (me);
}

//@Override
/*public*/ void ConfigurableSound::setXml(QDomElement e) {
    this->setXml(e, NULL );
}

/*public*/ void ConfigurableSound::setXml(QDomElement e, VSDFile* vf) {
    this->setName(this->getName() + e.attribute("name"));
    log->debug("ConfigurableSound: " + e.attribute("name"));
    //log->debug("  start file: " + e.getChildText("start-file"));
    if (((start_file = e.firstChildElement("start-file").text()) != NULL ) && !(start_file==(""))) {
        use_start_sound = true;
    } else {
        use_start_sound = false;
    }
    //log->debug("  mid file: " + e.getChildText("mid-file"));
    if (((mid_file = e.firstChildElement("mid-file").text()) != NULL ) && !(mid_file==(""))) {
        use_mid_sound = true;
    } else {
        use_mid_sound = false;
    }
    //log->debug("  end file: " + e.getChildText("end-file"));
    if (((end_file = e.firstChildElement("end-file").text()) != NULL ) && !(end_file==(""))) {
        use_end_sound = true;
    } else {
        use_end_sound = false;
    }
    //log->debug("  short file: " + e.getChildText("short-file"));
    if (((short_file = e.firstChildElement("short-file").text()) != NULL ) && !(short_file==(""))) {
        use_short_sound = true;
    } else {
        use_short_sound = false;
    }

    //log->debug("  start sound dur: " + e.getChildText("start-sound-duration"));
    QString ssd = e.firstChildElement("start-sound-duration").text();
    if ((ssd != NULL ) && !(ssd==(""))) {
        start_sound_duration = ssd.toInt();
    } else {
        start_sound_duration = 0;
    }

    //log->debug("  gain: " + e.getChildText("gain"));
    QString g = e.firstChildElement("gain").text();
    if ((g != NULL ) && !(g==(""))) {
        gain = g.toFloat();
    } else {
        gain = default_gain;
    }

    /*
     log->debug("Use:  start = " + use_start_sound +
     "mid = " + use_mid_sound +
     "end = " + use_end_sound +
     "short = " + use_short_sound);
     */
    // Reboot the sound
    initialized = false;
    this->init(vf);

}

