#ifndef AUDIOFILEFORMAT_H
#define AUDIOFILEFORMAT_H

#include <QObject>
#include <QMap>
//#include "audioformat.h"
#include "libPr3_global.h"

/**
 * An instance of the <code>Type</code> class represents one of the
 * standard types of audio file.  Static instances are provided for the
 * common types.
 */
class AudioFormat;
class LIBPR3SHARED_EXPORT AudioFileFormat : public QObject
{
 Q_OBJECT
public:
 /*public*/ /*static*/ class Type : public QObject
 {
 public:
  // FILE FORMAT TYPE DEFINES

  /**
   * Specifies a WAVE file.
   */
  /*public*/ static /*final*/ Type* WAVE;// = new Type("WAVE", "wav");

  /**
   * Specifies an AU file.
   */
  /*public*/ static /*final*/ Type* AU;// = new Type("AU", "au");

  /**
   * Specifies an AIFF file.
   */
  /*public*/ static /*final*/ Type* AIFF;// = new Type("AIFF", "aif");

  /**
   * Specifies an AIFF-C file.
   */
  /*public*/ static /*final*/ Type* AIFC;// = new Type("AIFF-C", "aifc");

  /**
   * Specifies a SND file.
   */
  /*public*/ static /*final*/ Type* SND;// = new Type("SND", "snd");

private:
  // INSTANCE VARIABLES

  /**
   * File type name.
   */
  /*private*/ /*final*/ QString name;

  /**
   * File type extension.
   */
  /*private*/ /*final*/ QString extension;

 public:
  // CONSTRUCTOR

  /**
   * Constructs a file type.
   * @param name the string that names the file type
   * @param extension the string that commonly marks the file type
   * without leading dot.
   */
  /*public*/ Type(QString name, QString extension, QObject *parent = 0);
  /*public*/ /*final*/ bool equals(QObject* obj);
  /*public*/ /*final*/ int hashCode();
  /*public*/ /*final*/ QString toString();
  /*public*/ QString getExtension();
 }; // class Type
 //explicit AudioFileFormat(QObject *parent = 0);
 /*public*/ AudioFileFormat(Type* type, AudioFormat* format, int frameLength, QObject *parent = 0);
 /*public*/ AudioFileFormat(Type* type, AudioFormat* format,
                        int frameLength, QMap<QString, QVariant>* properties, QObject *parent = 0);
 /*public*/ Type* getType();
 /*public*/ int getByteLength();
 /*public*/ AudioFormat* getFormat() ;
 /*public*/ int getFrameLength();
 /*public*/ QMap<QString,QVariant>* properties();
 /*public*/ QVariant getProperty(QString key);
 /*public*/ QString toString();

signals:

public slots:
private:
 // INSTANCE VARIABLES


 /**
  * File type.
  */
 /*private*/ Type* type;

 /**
  * File length in bytes
  */
 /*private*/ int byteLength;

 /**
  * Format of the audio data contained in the file.
  */
 /*private*/ AudioFormat* format;

 /**
  * Audio data length in sample frames
  */
 /*private*/ int frameLength;


 /** The set of properties */
 /*private*/ QMap<QString, QVariant>* _properties;
protected:
 /*protected*/ AudioFileFormat(Type* type, int byteLength, AudioFormat* format, int frameLength, QObject* parent = 0);

};

#endif // AUDIOFILEFORMAT_H
