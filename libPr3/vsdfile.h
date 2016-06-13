#ifndef VSDFILE_H
#define VSDFILE_H
#include "zipfile.h"
#include "xmlfile.h"
#include "libPr3_global.h"

class QuaZipFile;
class ValidateStatus;
class Logger;
class LIBPR3SHARED_EXPORT VSDFile : public ZipFile
{
 Q_OBJECT
public:
 explicit VSDFile(QObject *parent = 0);
 /*public*/ VSDFile(File* file, QObject *parent = 0);
 /*public*/ VSDFile(File* file, int mode, QObject *parent =0);
 /*public*/ VSDFile(QString name, QObject *parent=0);
 /*public*/ bool isInitialized();
 /*public*/ QString getStatusMessage();
 /*public*/ QDomElement getRoot();
 /*public*/ ValidateStatus* validate(QDomElement xmlroot);
 /*public*/ File* getFile(QString name);
 /*public*/ QDataStream* getInputStream(QString name);

signals:

public slots:
private:
 void common();
 Logger* log;
 /*private*/ QString _statusMsg;// = tr("OK");
  /*private*/ static /*final*/ QString VSDXmlFileName;// = "config.xml"; // NOI18N
 QDataStream* rv;
 QuaZipFile* file;

protected:
 /*protected*/ QDomElement root;
 /*protected*/ bool initialized;// = false;
 /*protected*/ bool init();
 /*protected*/ bool validateRequiredElement(QDomElement el, QString name);
 /*protected*/ bool validateOptionalFile(QDomElement el, QString name);
 /*protected*/ bool validateOptionalFile(QDomElement el, QString name, bool required) ;
 /*protected*/ bool validateFiles(QDomElement el, QString name, QStringList fnames) ;
 /*protected*/ bool validateFiles(QDomElement el, QString name, QStringList fnames, bool required);
};
// Dummy class just used to instantiate
/*private*/ /*static*/ class VSDXmlFile : public XmlFile {
 Q_OBJECT
};
/*static*/ class ValidateStatus : public QObject
{
 Q_OBJECT
    QString msg;// = "";
    bool valid;// = false;

    /*public*/ ValidateStatus();
    /*public*/ ValidateStatus(bool v, QString m);
    /*public*/ void setValid(bool v);
    /*public*/ void setMessage(QString m) ;
    /*public*/ bool getValid();
    /*public*/ QString getMessage();
    friend class VSDFile;
};
#endif // VSDFILE_H
