#include "dieselsound.h"
#include "logger.h"
#include "soundbite.h"
#include "notchtransition.h"
#include <QTimer>

//DieselSound::DieselSound(QObject *parent) :
//  EngineSound(parent)
//{
//}
// Usage:
// EngineSound() : constructor
// play() : plays short horn pop
// loop() : starts extended sustain horn
// stop() : ends extended sustain horn (plays end sound)
//class DieselSound extends EngineSound {


    /*public*/ DieselSound::DieselSound(QString name,QObject *parent) :
      EngineSound(name,parent) {
        //super(name);
     log = new Logger("DieselSound");
   current_notch = 1;
}

// Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
//@Override
/*public*/ void DieselSound::play() {
    log->debug("EngineSound Play: current_notch = " + current_notch);
    if (notch_sounds.contains(current_notch) && (engine_started || auto_start_engine)) {
        notch_sounds.value(current_notch)->play();
        is_playing = true;
    }
}

// Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
//@Override
/*public*/ void DieselSound::loop() {
    if (notch_sounds.contains(current_notch) && (engine_started || auto_start_engine)) {
        notch_sounds.value(current_notch)->play();
        is_playing = true;
    }
}

//@Override
/*public*/ void DieselSound::stop() {
    if (notch_sounds.contains(current_notch)) {
        notch_sounds.value(current_notch)->stop();
    }
    is_playing = false;
}

//@Override
/*public*/ void DieselSound::changeNotch(int new_notch)
{
    log->debug("EngineSound.changeNotch() current = " + QString::number(current_notch)
            + " new notch = " + QString::number(new_notch));
    if (new_notch != current_notch)
    {
        if (notch_sounds.contains(current_notch) && (engine_started || auto_start_engine))
        {
            notch_sounds.value(current_notch)->fadeOut();
        }

        notch_transition = findNotchTransient(current_notch, new_notch);
        if (notch_transition != NULL)
        {
            log->debug("notch transition: name = " + notch_transition->getFileName() + " length = " + QString::number(notch_transition->getLengthAsInt())
                    + "fade_length = " + QString::number(fade_length));
            // Handle notch transition...
            t = newTimer(notch_transition->getLengthAsInt() - notch_sounds.value(new_notch)->getFadeInTime(), false);
//                         /*new ActionListener()*/ handleNotchTimerPop);
//            {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            handleNotchTimerPop(e);
//                        }
//                    });
            connect(t, SIGNAL(timeout()), this, SLOT(handleNotchTimerPop()));
            t->start();
            notch_transition->fadeIn();
        }
        else
        {
         log->debug("notch transition not found!");
         if (notch_sounds.contains(new_notch) && (engine_started || auto_start_engine)) {
            notch_sounds.value(new_notch)->fadeIn();
         }
        }
        current_notch = new_notch;
    }
}

/*protected*/ void DieselSound::handleNotchTimerPop(JActionEvent* /*e*/)
{
    // notch value has already been changed
    log->debug("Notch timer pop. nt.next_notch = " + QString::number(notch_transition->getNextNotch())
            + "file = " + notch_sounds.value(notch_transition->getNextNotch())->getFileName());
    if (notch_sounds.contains(notch_transition->getNextNotch()) && (engine_started || auto_start_engine))
    {
        notch_sounds.value(notch_transition->getNextNotch())->fadeIn();
    }
    notch_transition->fadeOut();
}

/*private*/ NotchTransition* DieselSound::findNotchTransient(int prev, int next) {
    log->debug("Looking for Transient: prev = " + QString::number(prev) + " next = " + QString::number(next));
    foreach (NotchTransition* nt, transition_sounds)
    {
        log->debug("searching: nt.prev = " + QString::number(nt->getPrevNotch()) + " nt.next = " + QString::number(nt->getNextNotch()));
        if ((nt->getPrevNotch() == prev) && (nt->getNextNotch() == next)) {
            log->debug("Found transient: prev = " + QString::number(nt->getPrevNotch()) + " next = " + QString::number(nt->getNextNotch()));
            return (nt);
        }
    }
    // If we loop out, there's no transition that matches.
    return (NULL);
}

//@Override
/*public*/ void DieselSound::startEngine() {
    start_sound->play();
    current_notch = calcEngineNotch(0.0f);
    //t = newTimer(4500, false, new ActionListener() {
    t = newTimer(start_sound->getLengthAsInt() - start_sound->getFadeOutTime(), false); // /*new ActionListener()*/startToIdleAction);
//        {
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                startToIdleAction(e);
//            }
//        });
    //t.setInitialDelay(4500);
    connect(t, SIGNAL(timeout()), this, SLOT(startToIdleAction()));
    t->setInterval(start_sound->getLengthAsInt() - start_sound->getFadeOutTime());
    t->setSingleShot(true);
    log->debug("Starting Engine");
    t->start();
}

//@Override
/*public*/ void DieselSound::stopEngine() {
    notch_sounds.value(current_notch)->fadeOut();
    shutdown_sound->play();
    engine_started = false;
}

/*private*/ void DieselSound::startToIdleAction(JActionEvent* /*e*/) {
    log->debug("Starting idle sound notch = " + QString::number(current_notch) + " sound = " + notch_sounds.value(current_notch)->getFileName());
    notch_sounds.value(current_notch)->loop();
    engine_started = true;
}

//@Override
/*public*/ void DieselSound::shutdown() {
    foreach (SoundBite* ns, notch_sounds.values()) {
        ns->stop();
    }
    foreach (NotchTransition* nt, transition_sounds) {
        nt->stop();
    }
    if (start_sound != NULL) {
        start_sound->stop();
    }
    if (shutdown_sound != NULL) {
        shutdown_sound->stop();
    }

}

//@Override
/*public*/ void DieselSound::mute(bool m) {
    foreach (SoundBite* ns, notch_sounds.values()) {
        ns->mute(m);
    }
    foreach (NotchTransition* nt, transition_sounds) {
        nt->mute(m);
    }
    if (start_sound != NULL) {
        start_sound->mute(m);
    }
    if (shutdown_sound != NULL) {
        shutdown_sound->mute(m);
    }

}

//@Override
/*public*/ void DieselSound::setVolume(float v) {
    foreach (SoundBite* ns, notch_sounds.values()) {
        ns->setVolume(v);
    }
    foreach (NotchTransition* nt, transition_sounds) {
        nt->setVolume(v);
    }
    if (start_sound != NULL) {
        start_sound->setVolume(v);
    }
    if (shutdown_sound != NULL) {
        shutdown_sound->setVolume(v);
    }

}

// @Override
/*public*/ void DieselSound::setPosition(PhysicalLocation* p) {
    foreach (SoundBite* ns, notch_sounds.values()) {
        ns->setPosition(p);
    }
    foreach (NotchTransition* nt, transition_sounds) {
        nt->setPosition(p);
    }
    if (start_sound != NULL) {
        start_sound->setPosition(p);
    }
    if (shutdown_sound != NULL) {
        shutdown_sound->setPosition(p);
    }
}

//@Override
/*public*/ QDomElement DieselSound::getXml()
{
 //Element me = new Element("sound");
 QDomElement me = QDomElement();
 me.setTagName("sound");
 me.setAttribute("name", this->getName());
 me.setAttribute("type", "engine");
 // Do something, eventually...
 return (me);
}

//@Override
/*public*/ void DieselSound::setXml(QDomElement e, VSDFile* vf) {
    QDomElement el;
    //int num_notches;
    QString fn;
    SoundBite* sb;

    // Handle the common stuff.
    EngineSound::setXml(e, vf);

    log->debug("Diesel EngineSound: " + e.attribute("name"));
    notch_sounds = QMap<int, SoundBite*>();
    transition_sounds =QList<NotchTransition*>();

    // Get the notch sounds
    //Iterator<Element> itr = (e.getChildren("notch-sound")).iterator();
    QDomNodeList nl = e.elementsByTagName("notch-sound");
    //int i = 0;
    //while (itr.hasNext()) {
    for(int i = 0; i < nl.count(); i++)
    {
        el = nl.at(i).toElement(); //itr.next();
        fn = el.firstChildElement("file").text();
        int nn = el.firstChildElement("notch").text().toInt();
        //log->debug("Notch: " + nn + " File: " + fn);
        sb = new SoundBite(vf, fn, "Engine_n" + i, "Engine_" + i);
        sb->setLooped(true);
        sb->setFadeTimes(this->getFadeInTime(), this->getFadeOutTime());
        sb->setGain(setXMLGain(el));
        // Store in the list.
        notch_sounds.insert(nn, sb);
        //i++;
    }

    // Get the notch transitions
    //itr = (e.getChildren("notch-transition")).iterator();
    nl = e.elementsByTagName("notch-transition");
    //i = 0;
    NotchTransition* nt;
   //while (itr.hasNext()) {
    for(int i = 0; i < nl.count(); i++)
    {
        el = nl.at(i).toElement(); //itr.next();    el = itr.next();
        fn = el.firstChildElement("file").text();
        nt = new NotchTransition(vf, fn, "Engine_nt" + i, "Engine_nt" + i);
        nt->setPrevNotch(el.firstChildElement("prev-notch").text().toInt());
        nt->setNextNotch(el.firstChildElement("next-notch").text().toInt());
        //log->debug("Transition: prev=" + nt.getPrevNotch() + " next=" + nt.getNextNotch() + " File: " + fn);
        nt->setLooped(false);
        nt->setFadeTimes(this->getFadeInTime(), this->getFadeOutTime());
        // Handle gain
        nt->setGain(setXMLGain(el));
        transition_sounds.append(nt);
        //i++;
    }

    // Get the start and stop sounds
    el = e.firstChildElement("start-sound");
    if (!el.isNull()) {
        fn = el.firstChildElement("file").text();
        //log->debug("Start sound: " + fn);
        start_sound = new SoundBite(vf, fn, "Engine_start",
                "Engine_Start");
        // Handle gain
        start_sound->setGain(setXMLGain(el));
        start_sound->setFadeTimes(this->getFadeInTime(), this->getFadeOutTime());
        start_sound->setLooped(false);
    }
    el = e.firstChildElement("shutdown-sound");
    if (!el.isNull()) {
        fn = el.firstChildElement("file").text();
        //log->debug("Shutdown sound: " + fn);
        shutdown_sound = new SoundBite(vf, fn, "Engine_shutdown",
                "Engine_Shutdown");
        shutdown_sound->setLooped(false);
        // Handle gain
        shutdown_sound->setGain(setXMLGain(el));
        shutdown_sound->setFadeTimes(this->getFadeInTime(), this->getFadeOutTime());
    }

}

