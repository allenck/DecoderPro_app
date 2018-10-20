#include "soundbite.h"
#include "audiomanager.h"
#include "instancemanager.h"
#include "audiosource.h"
#include "vsdfile.h"
#include "logger.h"
#include "limits.h"

//SoundBite::SoundBite(QObject *parent) :
//  VSDSound(parent)
//{
//}
//class SoundBite extends VSDSound {



    /*public*/ SoundBite::SoundBite(QString name,QObject *parent) :
  VSDSound(name, parent) {
        //this(name, BOUND_MODE);
 common();
 //this->name = name;
 this->bufferMode = BOUND_MODE;
    }

    // Constructor to replace QueueSoundBite, really.
    /*public*/ SoundBite::SoundBite(QString name, BufferMode mode, QObject *parent) :
  VSDSound(name,parent){
        //super(name);
 common();
        //this->filename = NULL;
        system_name = VSDSound::SrcSysNamePrefix + name;
        user_name = VSDSound::SrcUserNamePrefix + name;
        bufferMode = mode;
        initialized = init(NULL, mode);
    }

    // Constructor for backward compatibility
    /*public*/ SoundBite::SoundBite(VSDFile* vf, QString filename, QString sname, QString uname,QObject *parent) :
  VSDSound(sname, parent) {
        //this(BOUND_MODE, vf, filename, sname, uname);
 common();
     bufferMode = BOUND_MODE;
     this->filename = filename;
     this->system_name = sname;
     this->user_name = uname;
     initialized = init(vf, bufferMode);
    }

    /*public*/ SoundBite::SoundBite(BufferMode mode, VSDFile* vf, QString filename, QString sname, QString uname,QObject *parent) :
  VSDSound(uname, parent) {
        //super(uname);
        common();
        this->filename = filename;
        system_name = sname;
        user_name = uname;
        bufferMode = mode;
        initialized = init(vf, mode);
    }
void SoundBite::common()
{
 initialized = false;
 looped = false;
 buf_loaded = false;
 loopBufferList =  QList<AudioBuffer*>();
 log = new Logger("SoundBite");

}
/*public*/ QString SoundBite::getFileName() {
    return (filename);
}

/*public*/ QString SoundBite::getSystemName() {
    return (system_name);
}

/*public*/ QString SoundBite::getUserName() {
    return (user_name);
}

/*public*/ bool SoundBite::isInitialized() {
    return (initialized);
}

/*public*/ /*final*/ bool SoundBite::init(VSDFile* vf, BufferMode mode)
{
 AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");
 if (!initialized)
 {
     //try {
  sound_src = (AudioSource*) am->provideAudio(SrcSysNamePrefix + system_name);
  sound_src->setUserName(BufUserNamePrefix + user_name);
  setLooped(false);
  if (mode == BOUND_MODE)
  {
   sound_buf = (AudioBuffer*) am->provideAudio(BufSysNamePrefix + system_name);
   sound_buf->setUserName(BufUserNamePrefix + user_name);
   if (vf == NULL) {
       sound_buf->setURL(vsd_file_base + filename);
   }
   else
   {
    QDataStream* ins = vf->getInputStream(filename);
    if (ins != NULL )
    {
        sound_buf->setInputStream(ins);
    } else {
        return (false);
    }
   }
   sound_src->setAssignedBuffer(sound_buf);
   setLength();
  }
//            } catch (AudioException ex) {
//                log->warn("Problem creating SoundBite: " + ex);
//            }
 }
 return (true);
}

/*public*/ void SoundBite::queueBuffer(AudioBuffer* b) {
    if (bufferMode == QUEUE_MODE) {
        if (b == NULL ) {
            log->debug("queueAudioBuffer with NULL  buffer input");
            return;
        }
        if (sound_src == NULL ) {
            log->debug("queueAudioBuffer with NULL  sound_src");
            return;
        }

        log->debug("Queueing Buffer: " + b->getSystemName());

        sound_src->queueBuffer(b);
    } else {
        log->warn("Attempted to Queue buffer to a Bound SoundBite.");
    }
}

/*public*/ void SoundBite::unqueueBuffers() {
    if (bufferMode == QUEUE_MODE) {
        sound_src->unqueueBuffers();
    }
}

/*public*/ int SoundBite::numQueuedBuffers() {
    if (bufferMode == QUEUE_MODE) {
        return (sound_src->numQueuedBuffers());
    } else {
        return (0);
    }
}

// Direct access to the underlying source.  use with caution.
/*public*/ AudioSource* SoundBite::getSource() {
    return (sound_src);
}

// WARNING: This will go away when we go to shared buffers... or at least it will
// have to do the name lookup on behalf of the caller...
/*public*/ AudioBuffer* SoundBite::getBuffer() {
    return (sound_buf);
}

// These can(?) be used to get the underlying AudioSource and AudioBuffer objects
// from the DefaultAudioManager.
/*public*/ QString SoundBite::getSourceSystemName() {
    return (SrcSysNamePrefix + system_name);
}

/*public*/ QString SoundBite::getSourceUserName() {
    return (SrcUserNamePrefix + user_name);
}

/*public*/ QString SoundBite::getBufferSystemName() {
    return (BufSysNamePrefix + system_name);
}

/*public*/ QString SoundBite::getBufferUserName() {
    return (BufUserNamePrefix + user_name);
}

/*public*/ void SoundBite::setLooped(bool loop, int minloops, int maxloops) {
    this->looped = loop;
    this->minloops = minloops;
    this->maxloops = maxloops;
    sound_src->setLooped(looped);
    sound_src->setMinLoops(minloops);
    sound_src->setMaxLoops(maxloops);
}

/*public*/ void SoundBite::setLooped(bool loop) {
    if (loop) {
        this->setLooped(true, AudioSource::LOOP_CONTINUOUS, AudioSource::LOOP_CONTINUOUS);
    } else {
        this->setLooped(false, AudioSource::LOOP_NONE, AudioSource::LOOP_NONE);
    }
}

/*public*/ bool SoundBite::isLooped() {
    return (looped);
}

/*public*/ int SoundBite::getFadeInTime() {
    return (sound_src->getFadeIn());
}

/*public*/ int SoundBite::getFadeOutTime() {
    return (sound_src->getFadeOut());
}

/*public*/ void SoundBite::setFadeInTime(int t) {
    sound_src->setFadeIn(t);
}

/*public*/ void SoundBite::setFadeOutTime(int t) {
    sound_src->setFadeOut(t);
}

/*public*/ void SoundBite::setFadeTimes(int in, int out) {
    sound_src->setFadeIn(in);
    sound_src->setFadeOut(out);
}

/*public*/ void SoundBite::shutdown() {
}

/*public*/ void SoundBite::mute(bool m) {
    if (m) {
        volume = sound_src->getGain();
        sound_src->setGain(0);
    } else {
        sound_src->setGain(volume);
    }
}

/*public*/ void SoundBite::setVolume(float v) {
    volume = v * gain;
    sound_src->setGain(volume);
}

/*public*/ void SoundBite::play() {
    sound_src->play();
    is_playing = true;
}

/*public*/ void SoundBite::loop() {
    sound_src->play();
    is_playing = true;
}

/*public*/ void SoundBite::stop() {
    sound_src->stop();
    is_playing = false;
}

/*public*/ void SoundBite::pause() {
    sound_src->pause();
    is_playing = false;
}

/*public*/ void SoundBite::rewind() {
    sound_src->rewind();
}

/*public*/ void SoundBite::fadeOut() {
    // Skip the fade action if the fade out time is zero.
    if (sound_src->getFadeOut() == 0) {
        sound_src->stop();
    } else {
        sound_src->fadeOut();
    }
    is_playing = false;
}

/*public*/ void SoundBite::fadeIn() {
    // Skip the fade action if the fade in time is zero.
    if (sound_src->getFadeIn() == 0) {
        sound_src->play();
    } else {
        sound_src->fadeIn();
    }
    is_playing = true;
}

//@Override
/*public*/ void SoundBite::setPosition(PhysicalLocation* v) {
    VSDSound::setPosition(v);
    sound_src->setPosition(v->getX(), v->getY(), v->getZ());
}

/*public*/ void SoundBite::setURL(QString filename) {
    this->filename = filename;
    sound_buf->setURL(vsd_file_base + filename);

}

/*public*/ long SoundBite::getLength() {
    return (length);
}

/*public*/ int SoundBite::getLengthAsInt() {
    // Note:  this only works for positive lengths...
    // Timer only takes an int... cap the length at MAXINT
    if (length > INT_MAX) {
        return (INT_MAX);
    } else // small enough to safely cast.
    {
        return ((int) length);
    }
}

/*public*/ void SoundBite::setLength(long p) {
    length = p;
}

/*public*/ void SoundBite::setLength() {
    length = calcLength(this);
}

/*public*/ /*static*/ long SoundBite::calcLength(SoundBite* s) {
    return (calcLength(s->getBuffer()));
}

/*public*/ /*static*/ long SoundBite::calcLength(AudioBuffer* buf) {
// Assumes later getBuffer() will find the buffer from AudioManager instead
    // of the current local reference... that's why I'm not directly using sound_buf here.

    // Required buffer functions not yet implemented
    long num_frames;
    int frequency;

    if (buf != NULL ) {
        num_frames = buf->getLength();
        frequency = buf->getFrequency();
    } else {
        // No buffer attached!
        num_frames = 0;
        frequency = 0;
    }

    /*
     long num_frames = 1;
     long frequency = 125;
     */
    if (frequency <= 0) {
        // Protect against divide-by-zero errors
        return (0l);
    } else {
        return ((1000 * num_frames) / frequency);
    }
}
