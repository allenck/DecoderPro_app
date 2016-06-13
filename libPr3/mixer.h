#ifndef MIXER_H
#define MIXER_H

#include <QObject>
#include <QAudioFormat>
#include "line.h"
#include <QAudioDeviceInfo>

class QAudioFormat;
class Logger;
class QAudioDeviceInfo;
class Mixer : public QObject
{
 Q_OBJECT
public:
 explicit Mixer(QObject *parent = 0);
 // TODO: should be in a QtMixer class??
 Mixer(QAudioDeviceInfo* deviceInfo, QObject *parent = 0);
 void setDeviceInfo(QAudioDeviceInfo* deviceInfo);
 QAudioDeviceInfo* deviceInfo();
 /*public*/ /*static*/ class Info : public QObject
 {
  //Q_OBJECT
  /**
   * Mixer name.
   */
  /*private*/ /*final*/ QString name;

  /**
   * Mixer vendor.
   */
  /*private*/ /*final*/ QString vendor;

  /**
   * Mixer description.
   */
  /*private*/ /*final*/ QString description;

  /**
   * Mixer version.
   */
  /*private*/ /*final*/ QString version;

  /**
   * Constructs a mixer's info object, passing it the given
   * textual information.
   * @param name the name of the mixer
   * @param vendor the company who manufactures or creates the hardware
   * or software mixer
   * @param description descriptive text about the mixer
   * @param version version information for the mixer
   */
  /*protected*/ Info(QString name, QString vendor, QString description, QString version);

  /**
   * Indicates whether two info objects are equal, returning <code>true</code> if
   * they are identical.
   * @param obj the reference object with which to compare this info
   * object
   * @return <code>true</code> if this info object is the same as the
   * <code>obj</code> argument; <code>false</code> otherwise
   */
  /*public*/ /*final*/ bool equals(QObject* obj);

  /**
   * Finalizes the hashcode method.
   *
   * @return the hashcode for this object
   */
  /*public*/ /*final*/ int hashCode() ;

  /**
   * Obtains the name of the mixer.
   * @return a string that names the mixer
   */
  /*public*/ /*final*/ QString getName() ;

  /**
   * Obtains the vendor of the mixer.
   * @return a string that names the mixer's vendor
   */
  /*public*/ /*final*/ QString getVendor();

  /**
   * Obtains the description of the mixer.
   * @return a textual description of the mixer
   */
  /*public*/ /*final*/ QString getDescription();

  /**
   * Obtains the version of the mixer.
   * @return textual version information for the mixer
   */
  /*public*/ /*final*/ QString getVersion();

  /**
   * Provides a string representation of the mixer info.
   * @return a string describing the info object
   */
  /*public*/ /*final*/ QString toString();
 }; // class Info

 /*public*/ virtual Info* getMixerInfo();
 /*public*/ virtual QList<Line::Info<QAudioDeviceInfo*>*>* getSourceLineInfo();
 /*public*/ virtual QList<Line::Info<QAudioDeviceInfo*>*>* getTargetLineInfo();
 /*public*/ virtual QList<Line::Info<QAudioDeviceInfo*>*>* getSourceLineInfo(Line::Info<QAudioDeviceInfo*>* info);
 /*public*/ virtual QList<Line::Info<QAudioDeviceInfo*>*>* getTargetLineInfo(Line::Info<QAudioDeviceInfo*>* info);
 /*public*/ virtual bool isLineSupported(Line::Info<QAudioDeviceInfo*>* info);
 /*public*/ virtual Line* getLine(Line::Info<QAudioDeviceInfo*>* info) /*throws LineUnavailableException*/;
 /*public*/ virtual int getMaxLines(Line::Info<QAudioDeviceInfo*>* info);
 /*public*/ virtual QList<Line*> getSourceLines();
 /*public*/ virtual QList<Line*> getTargetLines();
 /*public*/ virtual void synchronize(QList<Line*> lines, bool maintainSync);
 /*public*/ virtual void unsynchronize(QList<Line*> lines);
 /*public*/ virtual bool isSynchronizationSupported(QList<Line*> lines, bool maintainSync);


signals:

public slots:

private:
 QAudioDeviceInfo* _deviceInfo;
 void common();
 Logger* log;
 QAudioFormat format;


};

#endif // MIXER_H
