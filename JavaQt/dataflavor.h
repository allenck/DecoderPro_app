#ifndef DATAFLAVOR_H
#define DATAFLAVOR_H

#include <QObject>
#include <QMimeData>
#include "exceptions.h"
#include "logger.h"
#include "javaqt_global.h"
class MimeType;
class ClassLoader;
class MimeTypeParameterList;
//class Class;
class JAVAQTSHARED_EXPORT DataFlavor : public QObject
{
    Q_OBJECT
public:
 /*public*/ static /*final*/ DataFlavor* stringFlavor;
 /*public*/ static /*final*/ DataFlavor* imageFlavor;// = createConstant("image/x-java-image; class=java.awt.Image", "Image");
 /*public*/ static /*final*/ DataFlavor* javaFileListFlavor;// = createConstant("application/x-java-file-list;class=java.util.List", null);
 /*public*/ static /*final*/ QString javaJVMLocalObjectMimeType;// = "application/x-java-jvm-local-objectref";
 /*public*/ static /*final*/ QString javaRemoteObjectMimeType;// = "application/x-java-remote-object";
 /*public*/ DataFlavor(QObject* representationClass, QString humanPresentableName, QObject *parent = 0);
 /*public*/ DataFlavor(QString mimeType, QString humanPresentableName, QObject *parent = 0);
 /*public*/ DataFlavor(QString mimeType, QObject *parent = 0 ) throw (ClassNotFoundException);
 /*public*/ QString toString();
 /*public*/ static /*final*/ DataFlavor* getTextPlainUnicodeFlavor();
 /*public*/ static /*final*/ DataFlavor* selectBestTextFlavor( QList<DataFlavor*>* availableFlavors);
    /*public*/ QString getParameter(QString paramName);
    /*public*/ void setHumanPresentableName(QString humanPresentableName);
    /*public*/ bool equals(QObject* o);
    /*public*/ bool equals(DataFlavor* that);
    /*public*/ bool match(DataFlavor* that);
    /*public*/ bool isMimeTypeEqual(QString mimeType);
    /*public*/ /*final*/ bool isMimeTypeEqual(DataFlavor* dataFlavor);
    /*private*/ bool isMimeTypeEqual(MimeType* mtype);
    /*public*/ QString getMimeType();
    /*public*/ QString getRepresentationClass() ;
    /*public*/ QString getHumanPresentableName();
    /*public*/ QString getPrimaryType();
    /*public*/ QString getSubType();
    void setMimeTypeParameter(QString k, QString v);
signals:

public slots:
private:
    /*
     * fields
     */

    /* placeholder for caching any platform-specific data for flavor */

    /*transient*/ int       atom;

    /* Mime Type of DataFlavor */

    MimeType*            mimeType;

    /*private*/ QString      humanPresentableName;

    /** Java class of objects this DataFlavor represents **/

    /*private*/ QObject*       representationClass;
    static /*private*/ DataFlavor* createConstant(QObject* rc, QString prn);
    static /*private*/ DataFlavor* createConstant(QString mt, QString prn);
    /*private*/ DataFlavor(QString primaryType, QString subType, MimeTypeParameterList* params, QObject* representationClass, QString humanPresentableName, QObject *parent = 0);
    /*private*/ void initialize(QString mimeType, QString humanPresentableName, ClassLoader* classLoader) throw (MimeTypeParseException, ClassNotFoundException);
    /*private*/ QString paramString();
protected:
    /*protected*/ /*final*/ static QObject* tryToLoadClass(QString className,
                                                   ClassLoader* fallback = NULL)
    throw (ClassNotFoundException);
    Logger* log;
};

#endif // DATAFLAVOR_H
