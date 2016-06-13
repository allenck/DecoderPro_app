#ifndef SLOTMONITOR_H
#define SLOTMONITOR_H

#include <QMainWindow>
#include "loconetsystemconnectionmemo.h"
#include "QSignalMapper"
#include "libtables_global.h"

namespace Ui {
class SlotMonitor;
}

class SlotMonDataModel;
class LocoNetSlot;
class SlotManger;
class LIBTABLESSHARED_EXPORT SlotMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlotMonitor(LocoNetSystemConnectionMemo* memo, QWidget *parent = 0);
    ~SlotMonitor();
/*public*/ QString getHelpTarget();

private:
    Ui::SlotMonitor *ui;
    LocoNetSystemConnectionMemo* memo;
    Logger* log;
    SlotMonDataModel* slotModel;
private slots:
    void on_chkShowUnusedSlots_toggled(bool b);
    void on_chkShowSystemSlots_toggled(bool b);
    void on_estopAllButton_clicked();
//    void eStopControlAction(int);
//    void freeControlAction(int);

    friend class PropertyChangeSupport;
    friend class SlotManager;
};

#endif // SLOTMONITOR_H
