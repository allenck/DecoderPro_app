#ifndef LCDCLOCKFRAME_H
#define LCDCLOCKFRAME_H

#include "timebase.h"
#include "namedicon.h"
#include "jmrijframe.h"
#include "liblayouteditor_global.h"
#include "propertychangelistener.h"

class SimpleTimebase;
class QPushButton;
class JLabel;
class LIBLAYOUTEDITORSHARED_EXPORT LcdClockFrame : public JmriJFrame, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    explicit LcdClockFrame(QWidget *parent = 0);
    ~LcdClockFrame();
    /*public*/ void scaleImage();
    /*public*/ void dispose() override;
 /*public*/ QString getClassName() override;
  QObject* pself() override {return (QObject*)this;}

signals:

public slots:
    void update();
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

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
};

#endif // LCDCLOCKFRAME_H
