#ifndef ABSTRACTACTIONMODEL_H
#define ABSTRACTACTIONMODEL_H

#include <QObject>
#include <QMap>
#include "logger.h"
#include "exceptions.h"
#include "libpref_global.h"
#include "startupmodel.h"
#include "action.h"

class PropertyChangeListener;
class PropertyChangeSupport;
class LIBPREFSHARED_EXPORT AbstractActionModel : public StartupModel
{
    Q_OBJECT
public:
    explicit AbstractActionModel(QObject *parent = 0);
    /*public*/ QString getClassName();
    /*public*/ QString getName();
    /*public*/ void setName(QString n);
    /*public*/ void setClassName(QString n);
    /*public*/ QString getSystemPrefix();
    /*public*/ void setSystemPrefix(/*@Nullable*/ QString prefix);
    /*public*/ bool isSystemConnectionAction();
    /*public*/ bool isValid();
    /*public*/ QString toString();
 /*public*/ void performAction(QString) throw (JmriException);
 /*public*/ QList<Exception>* getExceptions();
 /*public*/ void addException(Exception exception);


signals:

public slots:
private:
    //TODO At some point this class might need to consider which system connection memo is being against certain system specific items
    /*private*/ QString systemPrefix;// = ""; // NOI18N
    /*private*/ QString className;// = ""; // NOI18N
    /*private*/ /*final*/ QList<Exception>* exceptions;// = new ArrayList<>();

    /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(AbstractActionModel.class);
 QString title;

protected:
    /*protected*/ /*abstract*/ virtual void performAction(Action* action) throw (JmriException);
 friend class AbstractActionPanel;
 friend class PerformActionModel;
};
#if 0
class ResourceBundle :  public QObject
{
 Q_OBJECT
public:
    static void getBundle(QString );
    static QString getString(QString);
    static QMap<QString, QString> bundleMap;
    static QStringList keys();

};
#endif

#endif // ABSTRACTACTIONMODEL_H
