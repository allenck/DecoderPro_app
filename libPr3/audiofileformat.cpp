#include "audiofileformat.h"
#include "audiosystem.h"
#include <QVariant>
#include "audioformat.h"

//AudioFileFormat::AudioFileFormat(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * An instance of the <code>AudioFileFormat</code> class describes
 * an audio file, including the file type, the file's length in bytes,
 * the length in sample frames of the audio data contained in the file,
 * and the format of the audio data.
 * <p>
 * The <code>{@link AudioSystem}</code> class includes methods for determining the format
 * of an audio file, obtaining an audio input stream from an audio file, and
 * writing an audio file from an audio input stream.
 *
 * <p>An <code>AudioFileFormat</code> object can
 * include a set of properties. A property is a pair of key and value:
 * the key is of type <code>String</code>, the associated property
 * value is an arbitrary object.
 * Properties specify additional informational
 * meta data (like a author, copyright, or file duration).
 * Properties are optional information, and file reader and file
 * writer implementations are not required to provide or
 * recognize properties.
 *
 * <p>The following table lists some common properties that should
 * be used in implementations:
 *
 * <table border=1>
 *  <caption>Audio File Format Properties</caption>
 *  <tr>
 *   <th>Property key</th>
 *   <th>Value type</th>
 *   <th>Description</th>
 *  </tr>
 *  <tr>
 *   <td>&quot;duration&quot;</td>
 *   <td>{@link java.lang.Long Long}</td>
 *   <td>playback duration of the file in microseconds</td>
 *  </tr>
 *  <tr>
 *   <td>&quot;author&quot;</td>
 *   <td>{@link java.lang.String String}</td>
 *   <td>name of the author of this file</td>
 *  </tr>
 *  <tr>
 *   <td>&quot;title&quot;</td>
 *   <td>{@link java.lang.String String}</td>
 *   <td>title of this file</td>
 *  </tr>
 *  <tr>
 *   <td>&quot;copyright&quot;</td>
 *   <td>{@link java.lang.String String}</td>
 *   <td>copyright message</td>
 *  </tr>
 *  <tr>
 *   <td>&quot;date&quot;</td>
 *   <td>{@link java.util.Date Date}</td>
 *   <td>date of the recording or release</td>
 *  </tr>
 *  <tr>
 *   <td>&quot;comment&quot;</td>
 *   <td>{@link java.lang.String String}</td>
 *   <td>an arbitrary text</td>
 *  </tr>
 * </table>
 *
 *
 * @author David Rivas
 * @author Kara Kytle
 * @author Florian Bomers
 * @see AudioInputStream
 * @since 1.3
 */
// /*public*/ class AudioFileFormat {


/**
 * Constructs an audio file format object.
 * This protected constructor is intended for use by providers of file-reading
 * services when returning information about an audio file or about supported audio file
 * formats.
 * @param type the type of the audio file
 * @param byteLength the length of the file in bytes, or <code>AudioSystem.NOT_SPECIFIED</code>
 * @param format the format of the audio data contained in the file
 * @param frameLength the audio data length in sample frames, or <code>AudioSystem.NOT_SPECIFIED</code>
 *
 * @see #getType
 */
/*protected*/ AudioFileFormat::AudioFileFormat(Type* type, int byteLength, AudioFormat* format, int frameLength, QObject* parent) : QObject(parent)
{
 this->type = type;
 this->byteLength = byteLength;
 this->format = format;
 this->frameLength = frameLength;
 this->_properties = NULL;
}


/**
 * Constructs an audio file format object.
 * This public constructor may be used by applications to describe the
 * properties of a requested audio file.
 * @param type the type of the audio file
 * @param format the format of the audio data contained in the file
 * @param frameLength the audio data length in sample frames, or <code>AudioSystem.NOT_SPECIFIED</code>
 */
/*public*/ AudioFileFormat::AudioFileFormat(Type* type, AudioFormat* format, int frameLength, QObject *parent)
 :  QObject(parent)
{
 //this(type,AudioSystem.NOT_SPECIFIED,format,frameLength);
 this->type = type;
 this->byteLength = AudioSystem::NOT_SPECIFIED;
 this->format = format;
 this->frameLength = frameLength;
 this->_properties = NULL;

}

/**
 * Construct an audio file format object with a set of
 * defined properties.
 * This public constructor may be used by applications to describe the
 * properties of a requested audio file. The properties map
 * will be copied to prevent any changes to it.
 *
 * @param type        the type of the audio file
 * @param format      the format of the audio data contained in the file
 * @param frameLength the audio data length in sample frames, or
 *                    <code>AudioSystem.NOT_SPECIFIED</code>
 * @param properties  a <code>Map&lt;String,Object&gt;</code> object
 *        with properties
 *
 * @since 1.5
 */
/*public*/ AudioFileFormat::AudioFileFormat(Type* type, AudioFormat* format,
                       int frameLength, QMap<QString, QVariant>* properties, QObject* parent)
 : QObject(parent)
{
 //this(type,AudioSystem::NOT_SPECIFIED,format,frameLength);
 this->type = type;
 this->byteLength = AudioSystem::NOT_SPECIFIED;
 this->format = format;
 this->frameLength = frameLength;
 this->_properties = new QMap<QString, QVariant>(*properties);
}


/**
 * Obtains the audio file type, such as <code>WAVE</code> or <code>AU</code>.
 * @return the audio file type
 *
 * @see Type#WAVE
 * @see Type#AU
 * @see Type#AIFF
 * @see Type#AIFC
 * @see Type#SND
 */
/*public*/ AudioFileFormat::Type* AudioFileFormat::getType() {
    return type;
}

/**
 * Obtains the size in bytes of the entire audio file (not just its audio data).
 * @return the audio file length in bytes
 * @see AudioSystem#NOT_SPECIFIED
 */
/*public*/ int AudioFileFormat::getByteLength() {
    return byteLength;
}

/**
 * Obtains the format of the audio data contained in the audio file.
 * @return the audio data format
 */
/*public*/ AudioFormat* AudioFileFormat::getFormat() {
    return format;
}

/**
 * Obtains the length of the audio data contained in the file, expressed in sample frames.
 * @return the number of sample frames of audio data in the file
 * @see AudioSystem#NOT_SPECIFIED
 */
/*public*/ int AudioFileFormat::getFrameLength() {
    return frameLength;
}

/**
 * Obtain an unmodifiable map of properties.
 * The concept of properties is further explained in
 * the {@link AudioFileFormat class description}.
 *
 * @return a <code>Map&lt;String,Object&gt;</code> object containing
 *         all properties. If no properties are recognized, an empty map is
 *         returned.
 *
 * @see #getProperty(String)
 * @since 1.5
 */
/*public*/ QMap<QString,QVariant>* AudioFileFormat::properties()
{
 QMap<QString,QVariant>* ret = new QMap<QString,QVariant>();
 if (_properties == NULL)
 {
  ret = new QMap<QString,QVariant>(/*0*/);
 }
 else
 {
  //ret = (QMap<QString,QVariant>) (properties.clone());
  ret = new QMap<QString, QVariant>(*_properties);
 }
 //return (QMap<QString,QVariant>) Collections.unmodifiableMap(ret);
 return ret;
}


/**
 * Obtain the property value specified by the key.
 * The concept of properties is further explained in
 * the {@link AudioFileFormat class description}.
 *
 * <p>If the specified property is not defined for a
 * particular file format, this method returns
 * <code>NULL</code>.
 *
 * @param key the key of the desired property
 * @return the value of the property with the specified key,
 *         or <code>NULL</code> if the property does not exist.
 *
 * @see #properties()
 * @since 1.5
 */
/*public*/ QVariant AudioFileFormat::getProperty(QString key) {
    if (_properties == NULL) {
     return QVariant();
    }
    return _properties->value(key);
}


/**
 * Provides a string representation of the file format.
 * @return the file format as a string
 */
/*public*/ QString AudioFileFormat::toString() {

    QString buf;

    //$$fb2002-11-01: fix for 4672864: AudioFileFormat.toString() throws unexpected NullPointerException
    if (type != NULL) {
        buf.append(type->toString() + " (." + type->getExtension() + ") file");
    } else {
        buf.append("unknown file format");
    }

    if (byteLength != AudioSystem::NOT_SPECIFIED) {
        buf.append(", byte length: " + QString::number(byteLength));
    }

    buf.append(", data format: " + format->toString());

    if (frameLength != AudioSystem::NOT_SPECIFIED) {
        buf.append(", frame length: " + QString::number(frameLength));
    }

    return  (buf);
}


/**
 * An instance of the <code>Type</code> class represents one of the
 * standard types of audio file.  Static instances are provided for the
 * common types.
 */
// /*public*/ static class Type {

    // FILE FORMAT TYPE DEFINES

    /**
     * Specifies a WAVE file.
     */
    /*public*/ /*static*/ /*final*/ AudioFileFormat::Type* AudioFileFormat::Type::WAVE = new AudioFileFormat::Type("WAVE", "wav");

    /**
     * Specifies an AU file.
     */
    /*public*/ /*static*/ /*final*/ AudioFileFormat::Type* AudioFileFormat::Type::AU = new AudioFileFormat::Type("AU", "au");

    /**
     * Specifies an AIFF file.
     */
    /*public*/ /*static*/ /*final*/ AudioFileFormat::Type* AudioFileFormat::Type::AIFF = new AudioFileFormat::Type("AIFF", "aif");

    /**
     * Specifies an AIFF-C file.
     */
    /*public*/ /*static*/ /*final*/ AudioFileFormat::Type* AudioFileFormat::Type::AIFC = new AudioFileFormat::Type("AIFF-C", "aifc");

    /**
     * Specifies a SND file.
     */
    /*public*/ /*static*/ /*final*/ AudioFileFormat::Type* AudioFileFormat::Type::SND = new AudioFileFormat::Type("SND", "snd");


    // INSTANCE VARIABLES

    /**
     * File type name.
     */
    /*private*/ /*final*/ QString name;

    /**
     * File type extension.
     */
    /*private*/ /*final*/ QString extension;


    // CONSTRUCTOR

    /**
     * Constructs a file type.
     * @param name the string that names the file type
     * @param extension the string that commonly marks the file type
     * without leading dot.
     */
/*public*/ AudioFileFormat::Type::Type(QString name, QString extension, QObject* parent)
 : QObject(parent)
{

 this->name = name;
 this->extension = extension;
}


// METHODS

/**
 * Finalizes the equals method
 */
/*public*/ /*final*/ bool AudioFileFormat::Type::equals(QObject* obj)
{
 if (toString() == NULL)
 {
  return (obj != NULL) && (obj->/*toString()*/objectName() == "");
 }
 //if (obj instanceof Type)
#if 0
if(qobject_cast<Type*>(obj) != NULL)
 {
  return toString()==(obj->/*toString()*/objectName());
 }
#endif
 return false;
}

/**
 * Finalizes the hashCode method
 */
/*public*/ /*final*/ int AudioFileFormat::Type::hashCode() {
    if (toString() == NULL) {
        return 0;
    }
    //return toString().hashCode();
    return 0;
}

/**
 * Provides the file type's name as the <code>String</code> representation
 * of the file type.
 * @return the file type's name
 */
/*public*/ /*final*/ QString AudioFileFormat::Type::toString() {
    return name;
}

/**
 * Obtains the common file name extension for this file type.
 * @return file type extension
 */
/*public*/ QString AudioFileFormat::Type::getExtension() {
    return extension;
}

//}; // class Type

//}; // class AudioFileFormat
