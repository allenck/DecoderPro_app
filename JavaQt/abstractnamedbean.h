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
    QString getComment() override;
    /**
     * Set associated comment text.
     * <p>
     * Comments can be any valid text.
     * @param comment Null means no comment associated.
     */
    void setComment(QString comment) override;
    QString getDisplayName();
    /*final*/ /*public*/ QString getDisplayName(DisplayOptions displayOptions) override;

    /*public*/ QString getFullyFormattedDisplayName() override;

    /*public synchronized*/  void addPropertyChangeListener(PropertyChangeListener* l, QString beanRef, const QString listenerRef)  override;
    /*public*/ /*synchronized*/ void addPropertyChangeListener(/*@Nonnull */QString propertyName,
                                                       /*@Nonnull*/ PropertyChangeListener* l,
                                                           QString beanRef, QString listenerRef) override;
    /*public synchronized*/  void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public synchronized*/  void removePropertyChangeListener(PropertyChangeListener* listener) override;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/ /*synchronized*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    virtual/*public synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
    virtual /*public synchronized*/  QVector<PropertyChangeListener*> getPropertyChangeListeners(QString name);
    /* This allows a meaning full list of places where the bean is in use!*/
    /*public synchronized*/  QList<QString>* getListenerRefs() override;
    /*public synchronized*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override;
    /*public synchronized*/  QString getListenerRef(PropertyChangeListener* l) override;
    /**
     * Number of current listeners. May return -1 if the
     * information is not available for some reason.
     */
    /*public synchronized*/ int getNumPropertyChangeListeners() override;
    /*public*/ /*synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(QString propertyName) override;

    /*public*/ QString getSystemName() const override ;
    /*public*/ QString getUserName() const override;
    /*public*/ void setUserName(QString s) throw (NamedBean::BadUserNameException)  override;
    /*public*/ void dispose() override;
    /*public*/ void setProperty(QString key, QVariant value) override;
    /*public*/ QVariant getProperty(QString key) override;

    /*public java.util.*/QSet<QString> getPropertyKeys() override;
    PropertyChangeSupport* pcs = nullptr;
    /*public*/ void removeProperty(QString key) override;
    /*public*/ QString describeState(int state);
    Q_INVOKABLE /*public*/ bool equals(QObject* obj) override;
    /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n) override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) override;
    /*public*/ uint hashCode() { return qHash(mSystemName, qGlobalQHashSeed());}
    inline bool operator ==(const AbstractNamedBean &e2)
    {
     return mSystemName == e2.mSystemName;
    }

    inline  bool operator <(const AbstractNamedBean &e2)
    {
     return mSystemName < e2.mSystemName;
    }

    inline uint qHash(const AbstractNamedBean &/*key*/, uint /*seed*/)
    {
     return hashCode();
    }

signals:

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
 QHash<PropertyChangeListener*, QString>* _register;
 QHash<PropertyChangeListener*, QString>* listenerRefs;
 QObject* parent;


 protected:
  QString mUserName;
  QString mSystemName;
  AbstractNamedBean(QString sys, QObject* parent = 0);
  AbstractNamedBean(QString sys, QString user, QObject* parent = 0);
  /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n) const;
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
  friend class Warrant;
};

#endif // ABSTRACTNAMEDBEAN_H
