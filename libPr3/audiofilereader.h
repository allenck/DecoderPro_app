#ifndef AUDIOFILEREADER_H
#define AUDIOFILEREADER_H
#include <QObject>
#include "audiofileformat.h"
#include <QDataStream>
#include <QUrl>
#include "file.h"
#include "audiofileformat.h"
#include "audioinputstream.h"
#include "libPr3_global.h"

class AudioInputStream;
class QUrl;
class QDataStream;
class File;
class AudioFileFormat;
/**
 * Provider for audio file reading services.  Classes providing concrete
 * implementations can parse the format information from one or more types of
 * audio file, and can produce audio input streams from files of these types.
 *
 * @author Kara Kytle
 * @since 1.3
 */
/*public*/ /*abstract*/ class LIBPR3SHARED_EXPORT AudioFileReader : public QObject
{
public:
 AudioFileReader(QObject* parent) : QObject(parent) {}
 /**
  * Obtains the audio file format of the input stream provided.  The stream must
  * point to valid audio file data.  In general, audio file readers may
  * need to read some data from the stream before determining whether they
  * support it.  These parsers must
  * be able to mark the stream, read enough data to determine whether they
  * support the stream, and, if not, reset the stream's read pointer to its original
  * position.  If the input stream does not support this, this method may fail
  * with an <code>IOException</code>.
  * @param stream the input stream from which file format information should be
  * extracted
  * @return an <code>AudioFileFormat</code> object describing the audio file format
  * @throws UnsupportedAudioFileException if the stream does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  * @see InputStream#markSupported
  * @see InputStream#mark
  */
 virtual /*public*/ /*abstract*/ AudioFileFormat* getAudioFileFormat(QDataStream* stream) /*throws UnsupportedAudioFileException, IOException*/{ return NULL;}

 /**
  * Obtains the audio file format of the URL provided.  The URL must
  * point to valid audio file data.
  * @param url the URL from which file format information should be
  * extracted
  * @return an <code>AudioFileFormat</code> object describing the audio file format
  * @throws UnsupportedAudioFileException if the URL does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  */
 virtual /*public*/ /*abstract*/ AudioFileFormat* getAudioFileFormat(QUrl /*url*/)/* throws UnsupportedAudioFileException, IOException*/ {return NULL;}

 /**
  * Obtains the audio file format of the <code>File</code> provided.  The <code>File</code> must
  * point to valid audio file data.
  * @param file the <code>File</code> from which file format information should be
  * extracted
  * @return an <code>AudioFileFormat</code> object describing the audio file format
  * @throws UnsupportedAudioFileException if the <code>File</code> does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  */
 virtual /*public*/ /*abstract*/ AudioFileFormat* getAudioFileFormat(File* file) /*throws UnsupportedAudioFileException, IOException*/ {return NULL;}

 /**
  * Obtains an audio input stream from the input stream provided.  The stream must
  * point to valid audio file data.  In general, audio file readers may
  * need to read some data from the stream before determining whether they
  * support it.  These parsers must
  * be able to mark the stream, read enough data to determine whether they
  * support the stream, and, if not, reset the stream's read pointer to its original
  * position.  If the input stream does not support this, this method may fail
  * with an <code>IOException</code>.
  * @param stream the input stream from which the <code>AudioInputStream</code> should be
  * constructed
  * @return an <code>AudioInputStream</code> object based on the audio file data contained
  * in the input stream.
  * @throws UnsupportedAudioFileException if the stream does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  * @see InputStream#markSupported
  * @see InputStream#mark
  */
 /*public*/ /*abstract*/ AudioInputStream* getAudioInputStream(QDataStream* /*stream*/) /*throws UnsupportedAudioFileException, IOException*/ {return NULL;}

 /**
  * Obtains an audio input stream from the URL provided.  The URL must
  * point to valid audio file data.
  * @param url the URL for which the <code>AudioInputStream</code> should be
  * constructed
  * @return an <code>AudioInputStream</code> object based on the audio file data pointed
  * to by the URL
  * @throws UnsupportedAudioFileException if the URL does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  */
 /*public*/ /*abstract*/ AudioInputStream* getAudioInputStream(QUrl /*url*/) /*throws UnsupportedAudioFileException, IOException*/ {return NULL;}

 /**
  * Obtains an audio input stream from the <code>File</code> provided.  The <code>File</code> must
  * point to valid audio file data.
  * @param file the <code>File</code> for which the <code>AudioInputStream</code> should be
  * constructed
  * @return an <code>AudioInputStream</code> object based on the audio file data pointed
  * to by the File
  * @throws UnsupportedAudioFileException if the <code>File</code> does not point to valid audio
  * file data recognized by the system
  * @throws IOException if an I/O exception occurs
  */
 virtual /*public*/ /*abstract*/ AudioInputStream* getAudioInputStream(File* /*file*/) /*throws UnsupportedAudioFileException, IOException*/ {return NULL;}
};

#endif // AUDIOFILEREADER_H
