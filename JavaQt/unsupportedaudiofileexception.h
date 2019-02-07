#ifndef UNSUPPORTEDAUDIOFILEEXCEPTION_H
#define UNSUPPORTEDAUDIOFILEEXCEPTION_H
#include "exceptions.h"

class UnsupportedAudioFileException : public Exception
{
public:
 /*public*/ UnsupportedAudioFileException(QString string);
 /*public*/ UnsupportedAudioFileException();
 /*public*/ UnsupportedAudioFileException(QString string, Throwable *thrwbl);
 /*public*/ UnsupportedAudioFileException(Throwable* thrwbl);
};

#endif // UNSUPPORTEDAUDIOFILEEXCEPTION_H
