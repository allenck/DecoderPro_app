#ifndef MIMETYPE_H
#define MIMETYPE_H

#include <QObject>
#include "exceptions.h"
#include "logger.h"

class MimeTypeParameterList;
class MimeType : public QObject
{
    Q_OBJECT
public:
    explicit MimeType(QObject *parent = 0);
    /*public*/ MimeType(QString rawdata,QObject *parent = 0) /*throw (MimeTypeParseException)*/;
    /*public*/ MimeType(QString primary, QString sub, MimeTypeParameterList* mtpl = 0,QObject *parent = 0) /*throw
    (MimeTypeParseException)*/;
//    /*public*/ int hashCode();
    /*public*/ bool equals(QObject* thatObject);
    /*public*/ QString getPrimaryType();
    /*public*/ QString getSubType();
    /*public*/ MimeTypeParameterList* getParameters() ;
    /*public*/ QString getParameter(QString name);
    /*public*/ void setParameter(QString name, QString value);
    /*public*/ void removeParameter(QString name);
    /*public*/ QString toString();
    /*public*/ QString getBaseType();
    /*public*/ bool match(MimeType* type);
    /*public*/ bool match(QString rawdata) /*throw (MimeTypeParseException)*/;
//    /*public*/ void writeExternal(ObjectOutput out) throw (IOException) ;
//    /*public*/ void readExternal(ObjectInput in) throw (IOException,
//ClassNotFoundException);
    /*public*/ QObject* clone();

signals:

public slots:
private:
    /*private*/ void parse(QString rawdata) /*throw (MimeTypeParseException)*/;
    /*private*/ QString    primaryType;
    /*private*/ QString    subType;
    /*private*/ MimeTypeParameterList* parameters;
    /*private*/ static bool isTokenChar(QChar c);
    /*private*/ bool isValidToken(QString s);
    /**
     * A string that holds all the special chars.
     */
    /*private*/ static /*final*/ QString TSPECIALS;// = "()<>@,;:\\\"/[]?=";
    Logger* log;
friend class DataFlavor;
};

#endif // MIMETYPE_H
