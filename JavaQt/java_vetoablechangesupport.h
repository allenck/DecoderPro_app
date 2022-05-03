#ifndef JAVA_VETOABLECHANGESUPPORT_H
#define JAVA_VETOABLECHANGESUPPORT_H
#include <QObject>
#include "vetoablechangelistener.h"
class Java_VetoableChangeSupport : public QObject
{
  Q_OBJECT
 public:
  Java_VetoableChangeSupport(QObject* source);
  /*public*/  /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l);
  /*public*/  /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l);
  /*public*/  /*synchronized*/ QVector<VetoableChangeListener*>* getVetoableChangeListeners();
  /*public*/  /*synchronized*/ void addVetoableChangeListener(QString propertyName,
                                                     VetoableChangeListener* l);
  /*public*/  /*synchronized*/ void
    removeVetoableChangeListener(QString propertyName, VetoableChangeListener* l);
  /*public*/  /*synchronized*/ QVector<VetoableChangeListener*>*
    getVetoableChangeListeners(QString propertyName);
  /*public*/  void fireVetoableChange(QString propertyName,
                                 QVariant oldVal, QVariant newVal);
  /*public*/  void fireVetoableChange(QString propertyName, int oldVal, int newVal);
  /*public*/  void fireVetoableChange(QString propertyName,
                                 bool oldVal, bool newVal);
  /*public*/  void fireVetoableChange(PropertyChangeEvent* event);
  /*public*/  /*synchronized*/ bool hasListeners(QString propertyName);

 private:
  /**
   * Compatible with JDK 1.1+.
   */
//  /*private*/ static final long serialVersionUID = -5090210921595982017L;

  /**
   * Maps property names (String) to named listeners (VetoableChangeSupport).
   * If this is a child instance, this field will be null.
   *
   * @serial the map of property names to named listener managers
   * @since 1.2
   */
  /*private*/ QMap<QString,Java_VetoableChangeSupport*>*  children =nullptr;

  /**
   * The non-null source object for any generated events.
   *
   * @serial the event source
   */
  /*private*/ /*final*/ QObject* source;

  /**
   * A field to compare serialization versions - this class uses version 2.
   *
   * @serial the serialization format
   */
//  /*private*/ static /*final*/ int vetoableChangeSupportSerializedDataVersion = 2;

  /**
   * The list of all registered vetoable listeners. If this instance was
   * created by user code, this only holds the global listeners (ie. not tied
   * to a name), and may be null. If it was created by this class, as a
   * helper for named properties, then this vector will be non-null, and this
   * instance appears as a value in the <code>children</code> hashtable of
   * another instance, so that the listeners are tied to the key of that
   * hashtable entry.
   */
  /*private*/ /*transient*/ QVector<VetoableChangeListener*>* listeners =nullptr;
};

#endif // JAVA_VETOABLECHANGESUPPORT_H
