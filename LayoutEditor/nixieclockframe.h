#ifndef NIXIECLOCKFRAME_H
#define NIXIECLOCKFRAME_H

#include "timebase.h"
#include "namedicon.h"
#include "positionableicon.h"
#include "jmrijframe.h"
#include "propertychangelistener.h"

class SimpleTimebase;
class QPushButton;
class JLabel;
class LIBLAYOUTEDITORSHARED_EXPORT NixieClockFrame : public JmriJFrame, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    /*public*/ NixieClockFrame( QObject *parent=0);
    /*public*/ void scaleImage();
//    void paint(QGraphicsScene* g);
    /*public*/ void dispose()override;
 /*public*/ QString getClassName() override;
  QObject* pself() {return (QObject*)this;}

signals:

public slots:
    void update();
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    // GUI member declarations
    JLabel* h1;  // msb of hours
    JLabel* h2;
    JLabel* m1;  // msb of minutes
    JLabel* m2;
    JLabel* colon;
    double aspect;
    double iconAspect;

    Timebase* clock;
 Logger* log;
    QVector<NamedIcon*> tubes;// = new QVector<NamedIcon*>(10, NULL);
    QVector<NamedIcon*> baseTubes;// = new QVector<NamedIcon*>(10, NULL);
    NamedIcon* colonIcon;
    NamedIcon* baseColon;
    QPushButton* b;
  //QGraphicsScene* g;
};

#endif // NIXIECLOCKFRAME_H
