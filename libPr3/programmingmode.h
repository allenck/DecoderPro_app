#ifndef PROGRAMMINGMODE_H
#define PROGRAMMINGMODE_H

#include <QObject>

class ProgrammingMode : public QObject
{
    Q_OBJECT
public:
    /*public*/ ProgrammingMode(/*@Nonnull*/ QString standardName,QObject *parent = nullptr);
    /*public*/ ProgrammingMode(QString standardName, QString localName,QObject *parent = nullptr);
    Q_INVOKABLE/*public*/ bool equals(QObject* o);
    Q_INVOKABLE/*public*/ QString toString();
    /*public*/ QString getStandardName();
    /*public*/ int hashCode();
    /*public*/ bool operator==(QObject* o);
 /**
  * NMRA "Paged" mode
  */
 /*public*/ static /*final*/ ProgrammingMode* PAGEMODE;// = new ProgrammingMode("PAGEMODE");

 /**
  * NMRA "Operations" or "Programming on the main" mode, using only the
  * bit-wise operations
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSBITMODE;// = new ProgrammingMode("OPSBITMODE");

 /**
  * NMRA "Programming on the main" mode for stationary decoders, using only
  * the byte-wise operations and "extended" addressing.
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSACCEXTBYTEMODE;// = new ProgrammingMode("OPSACCEXTBYTEMODE");

 /**
  * NMRA "Programming on the main" mode for stationary decoders, using only
  * the bit-wise operations. Note that this is defined as using the "normal",
  * not "extended" addressing.
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSACCBITMODE;// = new ProgrammingMode("OPSACCBITMODE");

 /**
  * NMRA "Programming on the main" mode for stationary decoders, using only
  * the bit-wise operations and "extended" addressing.
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSACCEXTBITMODE;// = new ProgrammingMode("OPSACCEXTBITMODE");

 /**
  * NMRA "Programming on the main" mode for stationary decoders, using only
  * the byte-wise operations. Note that this is defined as using the
  * "normal", not "extended" addressing.
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSACCBYTEMODE;// = new ProgrammingMode("OPSACCBYTEMODE");

 /**
  * NMRA "Address-only" mode. Often implemented as a proper subset of
  * "Register" mode, as the underlying operation is the same.
  */
 /*public*/ static /*final*/ ProgrammingMode* ADDRESSMODE;// = new ProgrammingMode("ADDRESSMODE");

 /**
  * NMRA "Operations" or "Programming on the main" mode, using only the
  * byte-wise operations.
  */
 /*public*/ static /*final*/ ProgrammingMode* OPSBYTEMODE;// = new ProgrammingMode("OPSBYTEMODE");

 /**
  * NMRA "Direct" mode, using only the byte-wise operations.
  */
 /*public*/ static /*final*/ ProgrammingMode* DIRECTBYTEMODE;// = new ProgrammingMode("DIRECTBYTEMODE");

 /**
  * NMRA "Register" mode.
  */
 /*public*/ static /*final*/ ProgrammingMode* REGISTERMODE;// = new ProgrammingMode("REGISTERMODE");

 /**
  * NMRA "Direct" mode, using only the bit-wise operations.
  */
 /*public*/ static /*final*/ ProgrammingMode* DIRECTBITMODE;// = new ProgrammingMode("DIRECTBITMODE");

 /**
  * NMRA "Direct" mode, using both the bit-wise and byte-wise operations.
  */
 /*public*/ static /*final*/ ProgrammingMode* DIRECTMODE;// = new ProgrammingMode("DIRECTMODE");
signals:

public slots:

private:
    /*private*/ QString standardName;
    /*private*/ QString localName;

};

#endif // PROGRAMMINGMODE_H
