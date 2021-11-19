#ifndef PRAGOTRONCLOCKFRAME_H
#define PRAGOTRONCLOCKFRAME_H
#include "jmrijframe.h"
#include "actionlistener.h"
#include "jlabel.h"
#include "timebase.h"
#include "namedicon.h"
#include <QPushButton>
#include "propertychangelistener.h"

class PragotronClockFrame : public JmriJFrame, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 PragotronClockFrame(QWidget* parent = nullptr);
 /*public*/ void dispose() override;
 /*public*/ QString getClassName() override;
 QObject* self() override{return (QObject*)this;}

public slots:
 void update();
 /*public*/ void propertyChange(PropertyChangeEvent* e)override;

private:
 // GUI member declarations
 JLabel* h24;  // hours
 JLabel* m1;  // msb of minutes
 JLabel* m2;
 JLabel* colon;

 double aspect;
 double iconAspect10;
 double iconAspectDot;
 double iconAspect24;

 Timebase* clock;

 QVector<NamedIcon*> foldingSheets10 = QVector<NamedIcon*>(10);
 QVector<NamedIcon*> baseFoldingSheets10 = QVector<NamedIcon*>(10);
 QVector<NamedIcon*> foldingSheets24 = QVector<NamedIcon*>(24);
 QVector<NamedIcon*> baseFoldingSheets24 = QVector<NamedIcon*>(24);
 NamedIcon* colonIcon;
 NamedIcon* baseColon;

 QPushButton* b;
 /*public*/ void scaleImage();

 friend class PCButtonListener;
 friend class PCMinuteChangeListener;
};

/*private*/ class PCButtonListener : public QObject, public ActionListener {
 Q_OBJECT
  Q_INTERFACES(ActionListener)
 PragotronClockFrame* frame;
public:
 PCButtonListener(PragotronClockFrame* frame) {this->frame = frame;}
public slots:
    //@Override
    /*public*/ void actionPerformed(/*ActionEvent a*/);
};

//class PCMinuteChangeListener : public PropertyChangeListener
//{
// Q_OBJECT
// PragotronClockFrame* frame;
//public:
// PCMinuteChangeListener(PragotronClockFrame* frame) {this->frame = frame;}
//public slots:
//    //@Override
//    /*public*/ void propertyChange(PropertyChangeEvent* /*e*/) {
//     frame->update();
//    }
//};
#endif // PRAGOTRONCLOCKFRAME_H
