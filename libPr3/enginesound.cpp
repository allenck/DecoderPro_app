#include "enginesound.h"
#include "vsdecodermanager.h"
#include "vsdecoderpreferences.h"
#include "logger.h"
#include "enginepane.h"

//EngineSound::EngineSound(QObject *parent) :
//  VSDSound(parent)
//{
//}
// Usage:
// EngineSound() : constructor
// play() : plays short horn pop
// loop() : starts extended sustain horn
// stop() : ends extended sustain horn (plays end sound)
//class EngineSound extends VSDSound {


    /*public*/ EngineSound::EngineSound(QString name, QObject *parent) :
  VSDSound(name, parent) {
        //super(name);
        initialized = false;
        engine_started = false;
        auto_start_engine = false;

        fade_length = 100;
        fade_in_time = 100;
        fade_out_time = 100;

        is_playing = false;
        engine_started = false;
        log = new Logger("EngineSound");
    }

    /*public*/ bool EngineSound::init() {
        auto_start_engine = VSDecoderManager::instance()->getVSDecoderPreferences()->isAutoStartingEngine();
        return (true);
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    /*public*/ void EngineSound::play() {
        log->debug("EngineSound Play");
        if (engine_started || auto_start_engine) {
            is_playing = true;
        }
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    /*public*/ void EngineSound::loop() {
        log->debug("EngineSound Loop");
        if (engine_started || auto_start_engine) {
            is_playing = true;
        }
    }

    /*public*/ void EngineSound::stop() {
        is_playing = false;
    }

    /*public*/ void EngineSound::fadeIn() {
        this->play();
    }

    /*public*/ void EngineSound::fadeOut() {
        this->stop();
    }

    /*public*/ int EngineSound::getFadeInTime() {
        return (this->fade_in_time);
    }

    /*public*/ int EngineSound::getFadeOutTime() {
        return (this->fade_out_time);
    }

    /*protected*/ void EngineSound::setFadeInTime(int t) {
        this->fade_in_time = t;
    }

    /*protected*/ void EngineSound::setFadeInTime(QString s) {
        if (s == NULL ) {
            log->debug("setFadeInTime NULL  string");
            return;
        }
        try {
            this->setFadeInTime(s.toInt());
        } catch (NumberFormatException* e) {
            log->debug("setFadeInTime Failed to parse int from: " + s);
        }
    }

    /*protected*/ void EngineSound::setFadeOutTime(int t) {
        this->fade_out_time = t;
    }

    /*protected*/ void EngineSound::setFadeOutTime(QString s) {
        if (s == NULL ) {
            log->debug("setFadeInTime NULL  string");
            return;
        }

        try {
            this->setFadeOutTime(s.toInt());
        } catch (NumberFormatException* e) {
            log->debug("setFadeOutTime Failed to parse int from: " + s);
        }
    }

    /*static*/ /*final*/ /*public*/ int EngineSound::calcEngineNotch(/*final*/ float throttle) {
        // This will convert to a value 0-8.
#ifdef WIN32
    int notch = int(throttle*8) +1; // no rint in MSVC
    #else
        int notch = ((int) rint(throttle * 8)) + 1;
#endif
        if (notch < 1) {
            notch = 1;
        }
        Logger* log = new Logger("EngineSound");
        log->warn("Throttle: " + QString::number(throttle) + " Notch: " + QString::number(notch));
        return (notch);

    }

    /*static*/ /*final*/ /*public*/ int EngineSound::calcEngineNotch(/*final*/ double throttle) {
        // This will convert from a % to a value 0-8.
#ifdef WIN32
    int notch = int(throttle*8) +1;
    #else
        int notch = ((int) rint(throttle * 8)) + 1;
#endif
        if (notch < 1) {
            notch = 1;
        }
        //log->warn("Throttle: " + throttle + " Notch: " + notch);
        return (notch);

    }

    // This is the default behavior.  Subclasses can do fancier things
    // if they want.
    /*public*/ void EngineSound::handleSpeedChange(float s, EnginePane* e) {
        e->setThrottle(EngineSound::calcEngineNotch(s));
    }

    /*protected*/ QTimer* EngineSound::newTimer(int time, bool repeat/*, ActionListener* al*/)
{
        t = new QTimer(/*time, al*/);
        t->setInterval(time);
        t->setSingleShot(!repeat);
        return (t);
    }

    /*public*/ void EngineSound::startEngine() {
        log->debug("Starting Engine");
    }

    /*public*/ void EngineSound::stopEngine() {
        engine_started = false;
    }

    /*public*/ bool EngineSound::isEngineStarted() {
        return (engine_started);
    }

    /*public*/ void EngineSound::setEngineStarted(bool es) {
        engine_started = es;
    }

    /*public*/ void EngineSound::shutdown() {
        // do nothing.
    }

    /*public*/ void EngineSound::mute(bool m) {
        // do nothing.
    }

    /*public*/ void EngineSound::setVolume(float v) {
        // do nothing.
    }

    /*protected*/ float EngineSound::setXMLGain(QDomElement e) {
        QString g = e.firstChildElement("gain").text();
        log->debug("  gain: " + g);
        if ((g != NULL ) && !(g==(""))) {
            return (g.toFloat());
        } else {
            return (default_gain);
        }

    }

    /*public*/ QDomElement EngineSound::getXml() {
        //QDomElement me = new Element("sound");
    QDomElement me = QDomElement();
    me.setTagName("sound");
        me.setAttribute("name", this->getName());
        me.setAttribute("type", "engine");
        // Do something, eventually...
        return (me);
    }

    /*public*/ void EngineSound::setXml(QDomElement e, VSDFile* vf) {
        // Do only the stuff common...
        if (this->getName() == NULL ) {
            this->setName(e.attribute("name"));
        }
        //log->debug("EngineSound: " + this->getName());
        this->setFadeInTime(e.firstChildElement("fade-in-time").text());
        this->setFadeOutTime(e.firstChildElement("fade-out-time").text());
        log->debug("Name: " + this->getName() + "Fade-In-Time: " + this->getFadeInTime()
                + " Fade-Out-Time: " + this->getFadeOutTime());
    }

