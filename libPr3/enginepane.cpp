#include "enginepane.h"
#include "eventlistenerlist.h"
#include <QVariant>

//EnginePane::EnginePane(QWidget *parent) :
//  QWidget(parent)
//{
//}
///*public*/ class EnginePane extends JPanel {
    // Superclass for Diesel, Steam, Electric panes.
    // Doesn't really do anything.



    /*public*/ EnginePane::EnginePane(QString n, EngineSoundEvent* e,QWidget *parent)
     : QWidget(parent){
        //super();
        name = n;
        engine = e;
        //listenerList = new EventListenerList();
    }

    /*public*/ EnginePane::EnginePane(QString n,QWidget *parent)
 : QWidget(parent)
{
        //this(n, null);
 name = n;
 engine = NULL;
    }

    /*public*/ EnginePane::EnginePane(QWidget *parent) :
      QWidget(parent) {
        //this(null, null);
 name = "";
 engine = NULL;
    }

    /*public*/ void EnginePane::init() {

    }

    /*public*/ void EnginePane::initContext(QVariant context) {
        initComponents();
    }

    /*public*/ void EnginePane::initComponents() {
    }

    /*public*/ QString EnginePane::getName() {
        return (name);
    }

    /*public*/ void EnginePane::setName(QString n) {
        name = n;
    }

    /*public*/ EngineSoundEvent* EnginePane::getEngine() {
        return (engine);
    }

    /*public*/ void EnginePane::setEngine(EngineSoundEvent* e) {
        engine = e;
    }

    /*public*/ void EnginePane::setThrottle(int t) {
    }

//    /*public*/ void addPropertyChangeListener(PropertyChangeListener listener) {
//        listenerList.add(PropertyChangeListener.class, listener);
//    }

//    /*public*/ void removePropertyChangeListener(PropertyChangeListener listener) {
//        listenerList.remove(PropertyChangeListener.class, listener);
//    }

    /*protected*/ void EnginePane::firePropertyChangeEvent(PropertyChangeEvent* evt) {
        //Object[] listeners = listenerList.getListenerList();

//        for (PropertyChangeListener l : listenerList.getListeners(PropertyChangeListener.class)) {
//            l.propertyChange(evt);
//        }
 emit propertyChange(evt);
    }
