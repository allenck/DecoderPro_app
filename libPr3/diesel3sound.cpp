#include "diesel3sound.h"
#include "logger.h"
#include "audiobuffer.h"
#include "instancemanager.h"
#include "soundbite.h"
#include "vsdfile.h"
#include "audioutil.h"
#include "audiobuffer.h"
#include "audiomanager.h"
#include "audiosource.h"
#include "sleeperthread.h"

//Diesel3Sound::Diesel3Sound(QObject *parent) :
//  EngineSound(parent)
//{
//}
// Usage:
// EngineSound() : constructor
// play() : plays short horn pop
// loop() : starts extended sustain horn
// stop() : ends extended sustain horn (plays end sound)
// Suppressing "unused" warnings throughout. There are a dozen
// methods, ctors and values that aren't used and don't have
// outside access.
//@SuppressWarnings("unused")
//class Diesel3Sound extends EngineSound {

    // Engine Sounds

    /*public*/ Diesel3Sound::Diesel3Sound(QString name,QObject *parent) :
  EngineSound(name,parent){
        //super(name);
 current_notch = 1;
 changing_speed = false;
 is_looping = false;
 _loopThread = NULL;
 log = new Logger("Diesel3Sound");
        //_loopThread = new D3LoopThread(this);
        //_loopThread->start();
        log->debug("New Diesel3Sound name(param) = " + name + " name(val) " + this->getName());
    }

    /*private*/ void Diesel3Sound::startThread() {
        _loopThread = new D3LoopThread(this, notch_sounds.value(current_notch), _soundName, true);
        log->debug("Loop Thread Started.  Sound name = " + _soundName);
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    //@Override
    /*public*/ void Diesel3Sound::play() {
        this->loop();
    }

    // Note:  Play and Loop do the same thing, since all of the notch sounds are set to loop.
    //@Override

    /*public*/ void Diesel3Sound::loop() {
        if (notch_sounds.contains(current_notch) && (engine_started || auto_start_engine)) {
            // Really, nothing to do here.  The engine should be started/stopped through
            // the startEngine() and stopEngine() calls.  Maybe should clean that up or have
            // play() == loop() == startEngine() and stop == stopEngine() some time.
            if ((_loopThread != NULL ) && (_loopThread->isRunning())) {
                _loopThread->setRunning(true);
            }
        }
    }

    //@Override
    /*public*/ void Diesel3Sound::stop() {
        // Stop the loop thread, in case it's running
        if (_loopThread != NULL ) {
            _loopThread->setRunning(false);
        }
        is_looping = false;
    }

    //Override
    /*public*/ void Diesel3Sound::handleSpeedChange(float s, EnginePane* e) {
        //log->debug("Handling SpeedSetting event. speed = " + s);
        throttle_setting = s;
        if (!changing_speed) {
            changeSpeed(s, e);
        }
    }

    // Responds to "CHANGE" trigger
    /*public*/ void Diesel3Sound::changeThrottle(float s) {
        // This is all we have to do.  The loop thread will handle everything else.
        if (_loopThread != NULL ) {
            _loopThread->setThrottle(s);
        }
    }

    /*protected*/ void Diesel3Sound::changeSpeed(float s, EnginePane* e) {
        engine_pane = e; // this should probably be cleaned up.  It's here for the recursion.
        changeThrottle(s);
    }

    /*public*/ D3Notch* Diesel3Sound::getNotch(int n) {
        return (notch_sounds.value(n));
    }

    //@Override
    /*public*/ void Diesel3Sound::startEngine() {
        log->debug("startEngine.  ID = " + this->getName());
        //_loopThread = new D3LoopThread(this, notch_sounds.get(current_notch), _soundName, true);
        _loopThread->startEngine(start_buffer);
    }

   // @Override
    /*public*/ void Diesel3Sound::stopEngine() {
        log->debug("stopEngine.  ID = " + this->getName());
        if (_loopThread != NULL ) {
            _loopThread->stopEngine(stop_buffer);
        }
    }

    //@Override
    /*public*/ void Diesel3Sound::shutdown() {
        this->stop();
    }

    //@Override
    /*public*/ void Diesel3Sound::mute(bool m) {
        if (_loopThread != NULL ) {
            _loopThread->mute(m);
        }
    }

   //@Override
    /*public*/ void Diesel3Sound::setVolume(float v) {
        if (_loopThread != NULL ) {
            _loopThread->setVolume(v);
        }
    }

    //@Override
    /*public*/ void Diesel3Sound::setPosition(PhysicalLocation* p) {
        if (_loopThread != NULL ) {
            _loopThread->setPosition(p);
        }
    }

    /*protected*/ QTimer* Diesel3Sound::newTimer(long time, bool repeat, ActionListener* al) {
        time = qMax((long)1, time);  // make sure the time is > zero
        t = new QTimer(/*(int) time, al*/);
        connect(t, SIGNAL(timeout()), al, SLOT(actionPerformed()));
        t->setInterval((int) time);
        t->setSingleShot(!repeat);
        return (t);
    }

    //@Override
    /*public*/ QDomElement Diesel3Sound::getXml() {
        //QDomElement me = new Element("sound");
 QDomElement me = QDomElement();
 me.setTagName("sound");
        me.setAttribute("name", this->getName());
        me.setAttribute("type", "engine");
        // Do something, eventually...
        return (me);
    }

    //@Override
    /*public*/ void Diesel3Sound::setXml(QDomElement e, VSDFile* vf) {
        QDomElement el;
        QString fn;
        D3Notch* sb;

        // Handle the common stuff.
        EngineSound::setXml(e, vf);

        //log->debug("Diesel EngineSound: " + e.getAttribute("name").getValue());
        _soundName = this->getName() + ":LoopSound";
        log->debug("Diesel3: name: " + this->getName() + " soundName " + _soundName);
        notch_sounds = QMap<int, D3Notch*>();
        QString in = e.firstChildElement("idle-notch").text();
        int idle_notch = 0;
        if (in != "") {
            idle_notch = in.toInt();
        } else {
            // leave idle_notch NULL  for now. We'll use it at the end to trigger a "grandfathering" action
            log->warn("No Idle Notch Specified!");
        }

        // Get the notch sounds
        //Iterator<Element> itr = (e.getChildren("notch-sound")).iterator();
        QDomNodeList nl = e.elementsByTagName("notch-sound");
        //int i = 0;
       // while (itr.hasNext()) {
        for(int i = 0; i < nl.count(); i++)
        {
            el = nl.at(i).toElement(); //itr.next();
            sb = new D3Notch();
            int nn = el.firstChildElement("notch").text().toInt();
            sb->setNotch(nn);
            if ((idle_notch != 0) && (nn == idle_notch)) {
                sb->setIdleNotch(true);
                log->debug("This Notch (" + QString::number(nn) + ") is Idle.");
            }
            //List<Element> elist = el.getChildren("file");
            QDomNodeList nl1 = el.elementsByTagName("file");
            //int j = 0;
            //for (Element fe : elist) {
            for(int j = 0; j < nl1.count(); j++)
            {
             QDomElement fe = nl1.at(j).toElement();
                fn = fe.text();
                //AudioBuffer b = D3Notch.getBuffer(vf, fn, "Engine_n" + i + "_" + j, "Engine_" + i + "_" + j);
                //log->debug("Buffer created: " + b + " name: " + b.getSystemName());
                //sb.addLoopBuffer(b);
                QList<AudioBuffer*>* l = D3Notch::getBufferList(vf, fn, "Engine_n" + QString::number(i) + "_" + QString::number(j), "Engine_" + QString::number(i) + "_" + QString::number(j));
                log->debug("Buffers Created: ");
                foreach (AudioBuffer* b, *l) {
                    log->debug("\tSubBuffer: " + b->getSystemName());
                }
                sb->addLoopBuffers(l);
                //j++;
            }
     //log->debug("Notch: " + nn + " File: " + fn);

            // Gain is broken, for the moment.  Buffers don't have gain. Sources do.
            //_sound->setGain(setXMLGain(el));
            //_sound->setGain(default_gain);
            sb->setNextNotch(el.firstChildElement("next-notch").text());
            sb->setPrevNotch(el.firstChildElement("prev-notch").text());
            sb->setAccelLimit(el.firstChildElement("accel-limit").text());
            sb->setDecelLimit(el.firstChildElement("decel-limit").text());
            if (!el.firstChildElement("accel-file").isNull()) {
                sb->setAccelBuffer(D3Notch::getBuffer(vf, el.firstChildElement("accel-file").text(), "Engine_na" + i, "Engine_na" +QString::number( i)));
            } else {
                sb->setAccelBuffer(NULL );
            }
            if (!el.firstChildElement("decel-file").isNull()) {
                sb->setDecelBuffer(D3Notch::getBuffer(vf, el.firstChildElement("decel-file").text(), "Engine_nd" + i, "Engine_nd" + QString::number(i)));
            } else {
                sb->setDecelBuffer(NULL );
            }
            // Store in the list.
            notch_sounds.insert(nn, sb);
            //i++;
        }

        // Get the start and stop sounds
        el = e.firstChildElement("start-sound");
        if (!el.isNull()) {
            fn = el.firstChildElement("file").text();
            //log->debug("Start sound: " + fn);
            start_buffer = D3Notch::getBuffer(vf, fn, "Engine_start", "Engine_Start");
        }
        el = e.firstChildElement("shutdown-sound");
        if (!el.isNull()) {
            fn = el.firstChildElement("file").text();
            //log->debug("Shutdown sound: " + fn);
            stop_buffer = D3Notch::getBuffer(vf, fn, "Engine_shutdown", "Engine_Shutdown");
        }

        // Handle "grandfathering the idle notch indication
        // If the VSD designer did not explicitly designate an idle notch...
        // Find the Notch with the lowest notch number, and make it the idle notch.
        // If there's a tie, this will take the first value, but the notches /should/
        // all have unique notch numbers.
        if (idle_notch == 0) {
            D3Notch* min_notch = NULL;
            // No, this is not a terribly efficient "min" operation.  But that's OK.
            foreach (D3Notch* n, notch_sounds.values()) {
                if ((min_notch == 0) || (n->getNotch() < min_notch->getNotch())) {
                    min_notch = n;
                }
            }
            log->debug("No Idle Notch Specified.  Choosing Notch (" + (min_notch != NULL  ? QString::number(min_notch->getNotch()) : "min_notch not set") + ") to be the Idle Notch.");
            if (min_notch != NULL ) {
                min_notch->setIdleNotch(true);
            } else {
                log->warn("Could not set idle notch because min_notch was still NULL ");
            }
        }

        // Kick-start the loop thread.
// TODO:        this->startThread();
    }
#if 1
    ///*private*/ static final Logger log = LoggerFactory.getLogger(Diesel3Sound.class.getName());

//    /*private*/ static class D3Notch {

//        /*private*/ AudioBuffer accel_buf;
//        /*private*/ AudioBuffer decel_buf;
//        /*private*/ int my_notch, next_notch, prev_notch;
//        /*private*/ float accel_limit, decel_limit;
//        /*private*/ int loop_index;
//        /*private*/ List<AudioBuffer> loop_bufs = new ArrayList<AudioBuffer>();
//        /*private*/ Boolean is_idle;

        /*public*/ D3Notch::D3Notch() {
 loop_bufs = new QList<AudioBuffer*>();
            //this(1, 1, 1, NULL , NULL , NULL );
 my_notch = 1;
 next_notch = 1;
 prev_notch = 1;
 accel_buf = NULL;
 decel_buf = NULL;
 //loop_bufs = NULL;
        }

        /*public*/ D3Notch::D3Notch(int notch, int next, int prev) {
 loop_bufs = new QList<AudioBuffer*>();
            //this(notch, next, prev, NULL , NULL , NULL );
 my_notch = notch;
 next_notch = next;
 prev_notch = prev;
 accel_buf = NULL;
 decel_buf = NULL;
        }

        /*public*/ D3Notch::D3Notch(int notch, int next, int prev, AudioBuffer* accel, AudioBuffer* decel, QList<AudioBuffer*>* loop) {
 loop_bufs = new QList<AudioBuffer*>();
            my_notch = notch;
            next_notch = next;
            prev_notch = prev;
            accel_buf = accel;
            decel_buf = decel;
            if (loop != NULL ) {
                loop_bufs = loop;
            }
            loop_index = 0;
        }

        /*public*/ int D3Notch::getNextNotch() {
            return (next_notch);
        }

        /*public*/ int D3Notch::getPrevNotch() {
            return (prev_notch);
        }

        /*public*/ int D3Notch::getNotch() {
            return (my_notch);
        }

        /*public*/ AudioBuffer* D3Notch::getAccelBuffer() {
            return (accel_buf);
        }

        /*public*/ AudioBuffer* D3Notch::getDecelBuffer() {
            return (decel_buf);
        }

        /*public*/ float D3Notch::getAccelLimit() {
            return (accel_limit);
        }

        /*public*/ float D3Notch::getDecelLimit() {
            return (decel_limit);
        }

        /*public*/ bool D3Notch::isInLimits(float val) {
            return ((val >= decel_limit) && (val <= accel_limit));
        }

        /*public*/ QList<AudioBuffer*>* D3Notch::getLoopBuffers() {
            return (loop_bufs);
        }

        /*public*/ AudioBuffer* D3Notch::getLoopBuffer(int idx) {
            return (loop_bufs->at(idx));
        }

        /*public*/ long D3Notch::getLoopBufferLength(int idx) {
            return (SoundBite::calcLength(loop_bufs->at(idx)));
        }

        /*public*/ bool D3Notch::isIdleNotch() {
            return (is_idle);
        }

        /*public*/ void D3Notch::setNextNotch(int n) {
            next_notch = n;
        }

        /*public*/ void D3Notch::setNextNotch(QString s) {
            next_notch = setIntegerFromString(s);
        }

        /*public*/ void D3Notch::setPrevNotch(int p) {
            prev_notch = p;
        }

        /*public*/ void D3Notch::setPrevNotch(QString s) {
            prev_notch = setIntegerFromString(s);
        }

        /*public*/ void D3Notch::setAccelLimit(float l) {
            accel_limit = l;
        }

        /*public*/ void D3Notch::setAccelLimit(QString s) {
            accel_limit = setFloatFromString(s);
        }

        /*public*/ void D3Notch::setDecelLimit(float l) {
            decel_limit = l;
        }

        /*public*/ void D3Notch::setDecelLimit(QString s) {
            decel_limit = setFloatFromString(s);
        }

        /*public*/ void D3Notch::setNotch(int n) {
            my_notch = n;
        }

        /*public*/ void D3Notch::setAccelBuffer(AudioBuffer* b) {
            accel_buf = b;
        }

        /*public*/ void D3Notch::setDecelBuffer(AudioBuffer* b) {
            decel_buf = b;
        }

        /*public*/ void D3Notch::addLoopBuffer(AudioBuffer* b) {
            loop_bufs->append(b);
        }

        /*public*/ void D3Notch::addLoopBuffers(QList<AudioBuffer*>* l) {
            //loop_bufs->addAll(l);
 foreach(AudioBuffer* b, *l)
         loop_bufs->append(b);
        }

        /*public*/ void D3Notch::setLoopBuffers(QList<AudioBuffer*>* l) {
            loop_bufs = l;
        }

        /*public*/ void D3Notch::clearLoopBuffers() {
            loop_bufs->clear();
        }

        /*public*/ AudioBuffer* D3Notch::nextLoopBuffer() {
            return (loop_bufs->at(incLoopIndex()));
        }

        /*public*/ void D3Notch::setIdleNotch(bool i) {
            is_idle = i;
        }

        /*public*/ int D3Notch::loopIndex() {
            return (loop_index);
        }

        /*public*/ int D3Notch::incLoopIndex() {
            // Increment
            loop_index++;
            // Correct for wrap.
            if (loop_index >= loop_bufs->size()) {
                loop_index = 0;
            }

            return (loop_index);
        }

        /*private*/ int D3Notch::setIntegerFromString(QString s) {
            if (s == NULL ) {
                return (0);
            }
            //try {
                int n = s.toInt();
                return (n);
//            } catch (NumberFormatException e) {
//                log->debug("Invalid integer: " + s);
//                return (0);
//            }
        }

        /*private*/ float D3Notch::setFloatFromString(QString s) {
            if (s == NULL ) {
                return (0.0f);
            }
            //try {
                float f = s.toFloat() / 100.0f;
                return (f);
//            } catch (NumberFormatException e) {
//                log->debug("Invalid float: " + s);
//                return (0.0f);
//            }
        }

        /*static*/ /*public*/ QList<AudioBuffer*>* D3Notch::getBufferList(VSDFile* vf, QString filename, QString sname, QString uname) {
 Logger*log = new Logger("Diesel3Sound");
            QList<AudioBuffer*>* buflist = NULL ;
            if (vf == NULL ) {
                // Need to fix this->
                //buf.setURL(vsd_file_base + filename);
                log->debug("No VSD File");
                return (NULL );
            }
            else {
                QDataStream* ins = vf->getInputStream(filename);
                if (ins != NULL ) {
                    //buflist = AudioUtil.getSplitInputStream(VSDSound.BufSysNamePrefix+filename, ins, 250, 100);
                    buflist = AudioUtil::getAudioBufferList(VSDSound::BufSysNamePrefix + filename, ins, 250, 100);
                } else {
                    log->debug("Input Stream failed");
                    return (NULL );
                }
                return (buflist);
            }
        }

        /*static*/ /*public*/ AudioBuffer* D3Notch::getBuffer(VSDFile* vf, QString filename, QString sname, QString uname) {
            AudioBuffer* buf = NULL ;
            AudioManager* am = InstanceManager::audioManagerInstance();
            Logger*log = new Logger("Diesel3Sound");

            try {
                buf = (AudioBuffer*) am->provideAudio(VSDSound::BufSysNamePrefix + filename);
                buf->setUserName(VSDSound::BufUserNamePrefix + uname);
                if (vf == NULL ) {
                    // Need to fix this->
                    //buf.setURL(vsd_file_base + filename);
                    log->debug("No VSD File");
                    return (NULL );
                } else {
                    QDataStream* ins = vf->getInputStream(filename);
                    if (ins != NULL ) {
                        buf->setInputStream(ins);
                    } else {
                        log->debug("Input Stream failed");
                        return (NULL );
                    }
                }
            } catch (AudioException ex) {
                log->error("Problem creating SoundBite: " /*+ ex*/);
                return (NULL );
            }

            log->debug("Buffer created: " + buf->getDisplayName() + " name: " + buf->getSystemName());
            return (buf);
        }

        ///*private*/ static final Logger log = LoggerFactory.getLogger(D3Notch.class.getName());
    //};

//        /*private*/ static class D3LoopThread extends Thread {

//            /*private*/ bool is_running = false;
//            /*private*/ bool is_looping = false;
//            /*private*/ bool is_dying = false;
//            Diesel3Sound _parent;
//            D3Notch _notch;
//            SoundBite _sound;
//            float _throttle;

            /*public*/ /*static*/ /*final*/ int D3LoopThread::SLEEP_INTERVAL = 50;

            /*public*/ D3LoopThread::D3LoopThread(Diesel3Sound* p) {
                //super();
         log = new Logger("D3LoopThread");
                is_running = false;
                is_looping = false;
                is_dying = false;
                _notch = NULL ;
                _sound = NULL ;
                _parent = p;
                _throttle = 0.0f;
            }

            /*public*/ D3LoopThread::D3LoopThread(Diesel3Sound* d, D3Notch* n, QString s, bool r) {
                //super();
         log = new Logger("D3LoopThread");
                is_running = r;
                is_looping = false;
                is_dying = false;
                _notch = n;
                _sound = new SoundBite(s, SoundBite::QUEUE_MODE);
                _sound->setGain(0.8f);
                _parent = d;
                _throttle = 0.0f;
                QThread* thread;
                moveToThread(thread);
                connect(thread, SIGNAL(started()), this, SLOT(process()));
                connect(this, SIGNAL(finished()),thread, SLOT(quit()));
                connect(this,SIGNAL(finished()), thread, SLOT(deleteLater()));
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                if (r) {
                    thread->start();
                }
            }

            /*public*/ void D3LoopThread::setNotch(D3Notch* n) {
                _notch = n;
            }

            /*public*/ D3Notch* D3LoopThread::getNotch() {
                return (_notch);
            }

            /*public*/ void D3LoopThread::setSound(SoundBite* s) {
                _sound = s;
            }

            /*public*/ void D3LoopThread::setRunning(bool r) {
                is_running = r;
            }

            /*public*/ bool D3LoopThread::isRunning() {
                return (is_running);
            }

            /*public*/ void D3LoopThread::setThrottle(float t) {
                _throttle = t;
                log->debug("Throttle set: " + QString::number(_throttle));
            }

            /*public*/ void D3LoopThread::startEngine(AudioBuffer* start_buf) {
                _sound->unqueueBuffers();
                // Adjust the current notch to match the throttle setting
                log->debug(tr("Notch = ") + QString::number(_notch->getNotch()) + " prev = " + QString::number(_notch->getPrevNotch()) + " next = " + QString::number(_notch->getNextNotch()));
                if (!_notch->isInLimits(_throttle)) {
                    // We're out of whack. Find the right notch for the current throttle setting.
                    while (!_notch->isInLimits(_throttle)) {
                        if (_throttle > _notch->getAccelLimit()) {
                            _notch = _parent->getNotch(_notch->getNextNotch());
                        } else if (_throttle < _notch->getDecelLimit()) {
                            _notch = _parent->getNotch(_notch->getPrevNotch());
                        }
                    }
                }
                // Only queue the start buffer if we know we're in the idle notch.
                // This is indicated by prevNotch == self.
                if (_notch->isIdleNotch()) {
                    _sound->queueBuffer(start_buf);
                } else {
                    _sound->queueBuffer(_notch->nextLoopBuffer());
                }
                // Follow up with another loop buffer.
                _sound->queueBuffer(_notch->nextLoopBuffer());
                is_looping = true;
                if (!_sound->isPlaying()) {
                    _sound->play();
                }
            }

            /*public*/ void D3LoopThread::stopEngine(AudioBuffer* stop_buf) {
                is_looping = false; // stop the loop player
                is_dying = true;
                _sound->queueBuffer(stop_buf);
                if (!_sound->isPlaying()) {
                    _sound->play();
                }
            }

            /*public*/ void D3LoopThread::process() {
                try {
                    while (is_running) {
                        if (is_looping) {
                            if (_sound->getSource()->numProcessedBuffers() > 0) {
                                _sound->unqueueBuffers();
                            }
                            //log->debug("D3Loop"+ _sound->getName() + "Run loop. Buffers: " + _sound->getSource().numQueuedBuffers());
                            if (!_notch->isInLimits(_throttle)) {
                                //log->debug("Notch Change! throttle = " + _throttle);
                                changeNotch();
                            }
                            if (_sound->getSource()->numQueuedBuffers() < 2) {
                                //log->debug("D3Loop"+ _sound->getName() + "Buffer count low (" + _sound->getSource().numQueuedBuffers() + ").  Adding buffer. Throttle = " + _throttle);
                                AudioBuffer* b = _notch->nextLoopBuffer();
                                //log->debug("D3Loop"+ _sound->getName() + "Loop: Adding buffer " + b.getSystemName());
                                _sound->queueBuffer(b);
                            }
                            if (!_sound->isPlaying()) {
                                _sound->play();
                            }
                        } else {
                            // Quietly wait for the sound to get turned on again
                            // Once we've stopped playing, kill the thread.
                            if (_sound->getSource()->numProcessedBuffers() > 0) {
                                _sound->unqueueBuffers();
                            }
                            if (is_dying && (_sound->getSource()->getState() != Audio::STATE_PLAYING)) {
                                _sound->stop(); // good reason to get rid of SoundBite.is_playing variable!
                                //return;
                            }
                        }
#if QT_VERSION < 0x050000

                        sleep(SLEEP_INTERVAL);
#else
                        SleeperThread::sleep(SLEEP_INTERVAL);
#endif
                    }
                    // Note: if (is_running == false) we'll exit the endless while and the Thread will die.
                    return;
                } catch (InterruptedException ie) {
                    //_notch = _parent.getCurrentNotch();
                    is_running = false;
                    return;
                    // probably should do something. Not sure what.
                }
            }

            /*private*/ void D3LoopThread::changeNotch() {
                AudioBuffer* transition_buf = NULL ;
                int new_notch = _notch->getNotch();

                log->debug(tr("D3Thread Change Throttle: ") + QString::number(_throttle) + " Accel Limit = " + QString::number(_notch->getAccelLimit()) + " Decel Limit = " + QString::number(_notch->getDecelLimit()));
                if (_throttle < 0) {
                    // DO something to shut down
                    _sound->stop();
                    is_running = false;
                    return;
                }
                if (_throttle > _notch->getAccelLimit()) {
                    // Too fast. Need to go to next notch up.
                    transition_buf = _notch->getAccelBuffer();
                    new_notch = _notch->getNextNotch();
                    //log->debug("Change up. notch=" + new_notch);
                } else if (_throttle < _notch->getDecelLimit()) {
                    // Too slow.  Need to go to next notch down.
                    transition_buf = _notch->getDecelBuffer();
                    new_notch = _notch->getPrevNotch();
                    log->debug("Change down. notch=" + new_notch);
                }
                // Now, regardless of whether we're going up or down, set the timer,
                // fade the current sound, and move on.
                if (transition_buf == NULL ) {
                    // No transition sound to play.  Skip the timer bit.
                    // Recurse directly to try the next notch.
                    _notch = _parent->getNotch(new_notch);
                    log->debug("No transition sound defined.");
                    return;
                } else {
                    // Stop the loop if it's running
                    //this->stopLoop();
                    // queue up the transition sound buffer.
                    _notch = _parent->getNotch(new_notch);
                    _sound->queueBuffer(transition_buf);
                    try {
#if QT_VERSION < 0x050000
                        sleep(SoundBite::calcLength(transition_buf) - 50);
#else
                     SleeperThread::sleep(SoundBite::calcLength(transition_buf) - 50);
#endif

                    } catch (InterruptedException e) {
                    }
                }
                return;
            }

            /*public*/ void D3LoopThread::mute(bool m) {
                _sound->mute(m);
            }

            /*public*/ void D3LoopThread::setVolume(float v) {
                _sound->setVolume(v);
            }

            /*public*/ void D3LoopThread::setPosition(PhysicalLocation* p) {
                _sound->setPosition(p);
            }

            /*public*/ void D3LoopThread::kill() {
                is_running = false;
                _notch = NULL ;
                _sound = NULL ;
            }
//    };
#endif
