#ifndef MIMETYPEPARAMETERLIST_H
#define MIMETYPEPARAMETERLIST_H

#include <QObject>
#include <QHash>
#include "exceptions.h"
#include "logger.h"

class MimeTypeParameterList : public QObject
{
    Q_OBJECT
public:
    explicit MimeTypeParameterList(QObject *parent = 0);
    /*public*/ MimeTypeParameterList(QString rawdata) /*throw (MimeTypeParseException)*/;
//    /*public*/ int hashCode();
    /*public*/ bool equals(QObject* thatObject);
    /*public*/ int size();
    /*public*/ bool isEmpty();
    /*public*/ QString get(QString name);
    /*public*/ void set(QString name, QString value);
    /*public*/ void remove(QString name);
    /*public*/ QStringList getNames();
    /*public*/ QString toString();
     /*public*/ QObject* clone();

signals:

public slots:
private:
    /*private*/ static bool isTokenChar(QChar c);
    /*private*/ static int skipWhiteSpace(QString rawdata, int i);
    /*private*/ static QString quote(QString value);
    /*private*/ static QString unquote(QString value);
    /**
     * A string that holds all the special chars.
     */
    /*private*/ static /*final*/ QString TSPECIALS;// = "()<>@,;:\\\"/[]?=";
    QHash<QString, QString>* parameters;
    Logger* log;
protected:
    /*protected*/ void parse(QString rawdata) /*throw (MimeTypeParseException)*/;
 friend class DataFlavor;
};

#endif // MIMETYPEPARAMETERLIST_H
