#ifndef SIGNALLINGGUITOOLS_H
#define SIGNALLINGGUITOOLS_H

#include <QObject>

class JmriJFrame;
class SignalMast;
class SignallingGuiTools : public QObject
{
    Q_OBJECT
public:
    //explicit SignallingGuiTools(QObject *parent = 0);
    static /*public*/ void updateSignalMastLogic(JmriJFrame* frame, SignalMast* oldMast, SignalMast* newMast);
    static /*public*/ void swapSignalMastLogic(JmriJFrame* frame, SignalMast* oldMast, SignalMast* newMast);
    static /*public*/ bool removeSignalMastLogic(JmriJFrame *frame, SignalMast* mast);
    static /*public*/ void removeAlreadyAssignedSignalMastLogic(JmriJFrame* frame, SignalMast* mast);

signals:

public slots:
private:
    /*private*/ SignallingGuiTools();

};

#endif // SIGNALLINGGUITOOLS_H
