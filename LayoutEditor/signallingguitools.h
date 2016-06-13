#ifndef SIGNALLINGGUITOOLS_H
#define SIGNALLINGGUITOOLS_H

#include <QObject>

class QMainWindow;
class SignalMast;
class SignallingGuiTools : public QObject
{
    Q_OBJECT
public:
    //explicit SignallingGuiTools(QObject *parent = 0);
    static /*public*/ void updateSignalMastLogic(QMainWindow* frame, SignalMast* oldMast, SignalMast* newMast);
    static /*public*/ void swapSignalMastLogic(QMainWindow* frame, SignalMast* oldMast, SignalMast* newMast);
    static /*public*/ bool removeSignalMastLogic(QMainWindow* frame, SignalMast* mast);
    static /*public*/ void removeAlreadyAssignedSignalMastLogic(QMainWindow* frame, SignalMast* mast);

signals:

public slots:
private:
    /*private*/ SignallingGuiTools();

};

#endif // SIGNALLINGGUITOOLS_H
