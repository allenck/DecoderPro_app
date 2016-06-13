#ifndef ENGINEPANE_H
#define ENGINEPANE_H

#include <QWidget>

class PropertyChangeEvent;
class EventListenerList;
class EngineSoundEvent;
class EnginePane : public QWidget
{
 Q_OBJECT
public:
 explicit EnginePane(QWidget *parent = 0);
 /*public*/ EnginePane(QString n, EngineSoundEvent* e,QWidget *parent = 0);
 /*public*/ EnginePane(QString n,QWidget *parent = 0);
 /*public*/ void init();
 /*public*/ void initContext(QVariant context);
 /*public*/ void initComponents() ;
 /*public*/ QString getName() ;
 /*public*/ void setName(QString n);
 /*public*/ EngineSoundEvent* getEngine() ;
 /*public*/ void setEngine(EngineSoundEvent* e);
 /*public*/ void setThrottle(int t);


signals:
 void propertyChange(PropertyChangeEvent*);
public slots:
private:
 QString name;
 EngineSoundEvent* engine;
 //EventListenerList* listenerList;

protected:
 /*protected*/ void firePropertyChangeEvent(PropertyChangeEvent* evt);

};

#endif // ENGINEPANE_H
