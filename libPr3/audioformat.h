#ifndef AUDIOFORMAT_H
#define AUDIOFORMAT_H

#include <QAudioFormat>
#include <QMap>
#include "libPr3_global.h"

/*public*/ /*static*/ class Encoding : public QObject
{

public:
    // ENCODING DEFINES

    /**
     * Specifies signed, linear PCM data.
     */
    /*public*/ static /*final*/ Encoding* PCM_SIGNED;// = new Encoding("PCM_SIGNED");

    /**
     * Specifies unsigned, linear PCM data.
     */
    /*public*/ static /*final*/ Encoding* PCM_UNSIGNED;// = new Encoding("PCM_UNSIGNED");

    /**
     * Specifies floating-point PCM data.
     *
     * @since 1.7
     */
    /*public*/ static /*final*/ Encoding* PCM_FLOAT;// = new Encoding("PCM_FLOAT");

    /**
     * Specifies u-law encoded data.
     */
    /*public*/ static /*final*/ Encoding* ULAW;// = new Encoding("ULAW");

    /**
     * Specifies a-law encoded data.
     */
    /*public*/ static /*final*/ Encoding* ALAW;// = new Encoding("ALAW");


    // INSTANCE VARIABLES
private:

    /**
     * Encoding name.
     */
    /*private*/ QString name;
public:

    // CONSTRUCTOR

    /**
     * Constructs a new encoding.
     * @param name  the name of the new type of encoding
     */
    /*public*/ Encoding(QString name =0);

    // METHODS

    /**
     * Finalizes the equals method
     */
//    /*public*/ /*final*/ bool equals(QObject* obj);
    /*public*/ /*final*/ int hashCode();
    /*public*/ /*final*/ QString toString();
};

class LIBPR3SHARED_EXPORT AudioFormat : public QObject
{
 Q_OBJECT
public:
 explicit AudioFormat(QObject *parent = 0);
 /*public*/ AudioFormat(Encoding* encoding, float sampleRate, int sampleSizeInBits, int channels, int frameSize, float frameRate, bool bigEndian, QObject *parent = 0);
 /*public*/ AudioFormat(Encoding* encoding, float sampleRate,
                    int sampleSizeInBits, int channels,
                    int frameSize, float frameRate,
                    bool bigEndian, QMap<QString, QVariant>* properties, QObject *parent = 0);
 /*public*/ AudioFormat(float sampleRate, int sampleSizeInBits,
                    int channels, bool _signed, bool bigEndian, QObject *parent = 0);
 /*public*/ Encoding* getEncoding();
 /*public*/ float getSampleRate();
 /*public*/ int getSampleSizeInBits();
 /*public*/ int getChannels() ;
 /*public*/ int getFrameSize();
 /*public*/ float getFrameRate();
 /*public*/ bool isBigEndian();
 /*public*/ QMap<QString,QVariant>* properties();
 /*public*/ QVariant getProperty(QString key);
 /*public*/ bool matches(AudioFormat* format);
 /*public*/ QString toString();
 /*public*/ QAudioFormat qAudioFormat();
 /*public*/ AudioFormat(QAudioFormat qAudioFormat);
signals:

public slots:
private:
 /** The set of properties */
 /*private*/ QMap<QString, QVariant>* _properties;
 QAudioFormat _qAudioFormat;
protected:
 // INSTANCE VARIABLES


 /**
  * The audio encoding technique used by this format.
  */
 /*protected*/ Encoding* encoding;

 /**
  * The number of samples played or recorded per second, for sounds that have this format.
  */
 /*protected*/ float sampleRate;

 /**
  * The number of bits in each sample of a sound that has this format.
  */
 /*protected*/ int sampleSizeInBits;

 /**
  * The number of audio channels in this format (1 for mono, 2 for stereo).
  */
 /*protected*/ int channels;

 /**
  * The number of bytes in each frame of a sound that has this format.
  */
 /*protected*/ int frameSize;

 /**
  * The number of frames played or recorded per second, for sounds that have this format.
  */
 /*protected*/ float frameRate;

 /**
  * Indicates whether the audio data is stored in big-endian or little-endian order.
  */
 /*protected*/ bool bigEndian;

};

#endif // AUDIOFORMAT_H
