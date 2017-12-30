#ifndef INPUTSOURCE_H
#define INPUTSOURCE_H

#include <QObject>

class Reader;
class QTextStream;
class InputSource : public QObject
{
 Q_OBJECT
public:
 explicit InputSource(QObject *parent = 0);
/*public*/ InputSource (QString systemId,QObject *parent = 0);
 /*public*/ InputSource (/*InputStream*/QTextStream* byteStream, QObject *parent = 0);
 /*public*/ void setPublicId (QString publicId);
 /*public*/ QString getPublicId ();
 /*public*/ void setSystemId (QString systemId);
 /*public*/ QString getSystemId ();
 /*public*/ void setByteStream (/*InputStream*/QTextStream* byteStream);
 /*public*/ /*InputStream*/QTextStream* getByteStream ();
 /*public*/ void setEncoding (QString encoding);
 /*public*/ QString getEncoding ();

signals:

public slots:

private:
 ////////////////////////////////////////////////////////////////////
 // Internal state.
 ////////////////////////////////////////////////////////////////////

 /*private*/ QString publicId;
 /*private*/ QString systemId;
 /*private*/ QTextStream* byteStream;
 /*private*/ QString encoding;
// /*private*/ Reader* characterStream;

};

#endif // INPUTSOURCE_H
