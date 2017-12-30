#ifndef MESSAGEDIGEST_H
#define MESSAGEDIGEST_H
#include "messagedigestspi.h".h"
#include "exceptions.h"

class NoSuchAlgorithmException : public Exception
{
public:
 NoSuchAlgorithmException(QString msg) : Exception(msg) {}
};
class NoSuchProviderException : public Exception
{
public:
 NoSuchProviderException(QString msg) : Exception(msg) {}
};

class Provider;
class MessageDigest : public MessageDigestSpi
{
public:
 /*protected*/ MessageDigest(QString algorithm, QObject* parent =0);

private:
 /*private*/ QString algorithm;
 /*private*/ static /*final*/ int INITIAL;// = 0;
 /*private*/ static /*final*/ int IN_PROGRESS;// = 1;
 /*private*/ int state = INITIAL;

 // The provider
 /*private*/ Provider* provider;

};

#endif // MESSAGEDIGEST_H
