#ifndef AUTOMATSUMMARY_H
#define AUTOMATSUMMARY_H

#include <QObject>
#include <QMutex>
#include "swingpropertychangesupport.h"
#include "runnable.h"
#include "liblayouteditor_global.h"


class AbstractAutomaton;
class PropertyChangeListener;
class SwingPropertyChangeSupport;
class Runnable;
class LIBLAYOUTEDITORSHARED_EXPORT AutomatSummary : public QObject
{
    Q_OBJECT
public:
    //explicit AutomatSummary(QObject *parent = 0);
    static /*public*/ AutomatSummary* instance();
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* p) ;
    /*public*/ void _register(AbstractAutomaton* a);
    /*public*/ void remove(AbstractAutomaton* a);
    /*public*/ int length();
    /*public*/ AbstractAutomaton* get(int i);
    /*public*/ AbstractAutomaton* get(QString name);
    /*public*/ int indexOf(AbstractAutomaton* a);
    /*public*/ void loop(AbstractAutomaton* a);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* p);

signals:
    //void notify(QString property, QVariant arg1, QVariant arg2);
    //void propertyChange(PropertyChangeEvent*);

public slots:
private:
    /*private*/ AutomatSummary(QObject *parent = 0) ;
    static /*volatile*/ /*private*/ AutomatSummary* self;// = NULL;
    /*private*/ QList<AbstractAutomaton*>* automats;// = new ArrayList<AbstractAutomaton>();
    SwingPropertyChangeSupport* prop;// = new SwingPropertyChangeSupport(this, nullptr);
    QMutex mutex;
//    void notify(QString property, QVariant arg1, QVariant arg2);
#if 0
 class Notifier : public Runnable
 {
  public:
     Notifier(QString property, QVariant arg1, QVariant arg2)
     {
         this->property = property;
         this->arg1 = arg1;
         this->arg2 = arg2;
         SwingPropertyChangeSupport* prop = new SwingPropertyChangeSupport(this, nullptr);
     }
     QVariant arg1;
     QVariant arg2;
     QString property;
     SwingPropertyChangeSupport* prop;

     /*public*/ void run() {
         prop->firePropertyChange(property, arg1, arg2);
     }

 };
#endif
};

#endif // AUTOMATSUMMARY_H
