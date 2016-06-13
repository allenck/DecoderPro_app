#ifndef ABSTRACTACTIONMODEL_H
#define ABSTRACTACTIONMODEL_H

#include <QObject>
#include <QMap>
#include "logger.h"
#include "exceptions.h"
#include "libpref_global.h"

class PropertyChangeListener;
class PropertyChangeSupport;
class LIBPREFSHARED_EXPORT AbstractActionModel : public QObject
{
    Q_OBJECT
public:
    explicit AbstractActionModel(QObject *parent = 0);
    /*public*/ QString getClassName();
    /*public*/ QString getName();
    /*public*/ void setName(QString n);
    /*public*/ void setClassName(QString n);
    static /*public*/ QStringList nameList();
    static /*public*/ QStringList classList();
    /*public*/ void addAction(QString strClass, QString name) throw (ClassNotFoundException);
    /*public*/ void removeAction(QString strClass) throw (ClassNotFoundException);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);

signals:

public slots:
private:
    static /*private*/ QMap<QString, QString> _classList;// = NULL;
    //TODO At some point this class might need to consider which system connection memo is being against certain system specific items
    QString className;
    static /*private*/ void loadArrays();
    PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
    Logger* log;
protected:
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
 friend class AbstractActionPanel;
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
