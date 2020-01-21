#ifndef ANALOGCLOCKFRAME_H
#define ANALOGCLOCKFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class Timebase;
class LIBLAYOUTEDITORSHARED_EXPORT AnalogClockFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit AnalogClockFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:
private:
    // GUI member declarations

    Timebase* clock;
    double minuteAngle;
    double hourAngle;
    QString amPm;

};

#endif // ANALOGCLOCKFRAME_H
