#ifndef ABSTRACTNAMEDBEAN_H
#define ABSTRACTNAMEDBEAN_H
#include "namedbean.h"
#include "logger.h"
#include "propertychangesupport.h"
#include <QSet>
#include "javaqt_global.h"
#include "exceptions.h"
#include "propertyvetoexception.h"

class JAVAQTSHARED_EXPORT AbstractNamedBean :  public NamedBean
{
    Q_OBJECT
public:
    explicit AbstractNamedBean(QObject *parent = 0);
    /**
     * Get associated comment text.
     */
    QString getComment();
    /**
     * Set associated comment text.
     * <p>
     * Comments can be any valid text.
     * @param comment Null means no comment associated.
     */
    void setComment(QString comment);
    QString getDisplayName();
    /*final*/ /*public*/ QString getDisplayName(DisplayOptions displayOptions);

    /*public*/ QString getFullyFormattedDisplayName();

    /*public synchronized*/ virtual void addPropertyChangeListener(PropertyChangeListener* l, QString beanRef, const QString listenerRef);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(/*@Nonnull */QString propertyName,
                                                       /*@Nonnull*/ PropertyChangeListener* l,
                                                           QString beanRef, QString listenerRef) override;
    /*public synchronized*/ virtual void addPropertyChangeListener(PropertyChangeListener* l);
    /*public synchronized*/ virtual void removePropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/ /*synchronized*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
    /*public synchronized*/ virtual QList<PropertyChangeListener*>* getPropertyChangeListeners(QString name);
    /* This allows a meaning full list of places where the bean is in use!*/
    /*public synchronized*/ virtual QList<QString>* getListenerRefs();
    /*public synchronized*/ virtual void updateListenerRef(PropertyChangeListener* l, QString newName);
    /*public synchronized*/ virtual QString getListenerRef(PropertyChangeListener* l);
    /**
     * Number of current listeners. May return -1 if the
     * information is not available for some reason.
     */
    /*public synchronized*/ virtual int getNumPropertyChangeListeners();
    /*public synchronized*/ virtual QVector<PropertyChangeListener *> getPropertyChangeListeners();
    /*public*/ QString getSystemName();
    /*public*/ QString getUserName();
//    /*public*/ virtual void setSysName(QString s); // needed for catalogtree
    /*public*/ void setUserName(QString s) throw (NamedBean::BadUserNameException);
    /*public*/ virtual void dispose();
    /*public*/ virtual void setProperty(QString key, QVariant value);
    /*public*/ virtual QVariant getProperty(QString key);

    /*public java.util.*/QSet<QString> getPropertyKeys();
    PropertyChangeSupport* pcs;
    /*public*/ void removeProperty(QString key);
    /*public*/ QString describeState(int state);
    Q_INVOKABLE /*public*/ bool equals(QObject* obj);
    /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n);
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException);

signals:
//    void propertyChange(AbstractNamedBean* bean, QString propertyName, QString o, QString n);
//    void propertyChange( QString propertyName, QVariant o, QVariant n);
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
    /*private*/ static Logger* log;// = LoggerFactory::getLogger("AbstractNamedBean");

 void common(QString sys, QString user, QObject *parent);
 QString comment;
 QMap<QString, QVariant>* parameters;
 // implementing classes will typically have a function/listener to get
 // updates from the layout, which will then call
 //		public void firePropertyChange(String propertyName,
 //					       	Object oldValue,
 //						Object newValue)
 // _once_ if anything has changed state

 // since we can't do a "super(this)" in the ctor to inherit from PropertyChangeSupport, we'll
 // reflect to it
 //PropertyChangeSupport* pcs;
 QHash<PropertyChangeListener*, QString>* _Register;
 QHash<PropertyChangeListener*, QString>* listenerRefs;
 QObject* parent;
 
 protected:
  QString mUserName;
  QString mSystemName;
  AbstractNamedBean(QString sys, QObject* parent = 0);
  AbstractNamedBean(QString sys, QString user, QObject* parent = 0);
  /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
//  /*protected*/ void firePropertyChange(QString p, QObject* old, QObject* n);
  friend class LayoutBlock;
  friend class CatalogTree;
  friend class AbstractCatalogTree;
  friend class JMRIClientTurnout;
  friend class JMRIClientLight;
  friend class LnReporter;
  friend class AbstractProvidingTurnoutManagerTestBase;
  friend class AbstractProvidingReporterManagerTestBase;
  friend class AbstractProvidingMemoryManagerTestBase;
};

#endif // ABSTRACTNAMEDBEAN_H
