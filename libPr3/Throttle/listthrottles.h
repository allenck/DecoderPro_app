#ifndef LISTTHROTTLES_H
#define LISTTHROTTLES_H

#include "../../LayoutEditor/jmrijframe.h"
#include "logger.h"
#include "libPr3_global.h"

namespace Ui {
class ListThrottles;
}

class ThrottlesTableCellRenderer;
class ThrottleWindow;
class LnPowerManager;
class PropertyChangeEvent;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT ListThrottles : public JmriJFrame
{
    Q_OBJECT
public:
    explicit ListThrottles(/*LocoNetSystemConnectionMemo* memo,*/ QWidget *parent = 0);
    ~ListThrottles();
    QString getTitle();
private:
    Ui::ListThrottles *ui;
    QAction* newThrottle;
    QAction* emergencyStop;
    QAction* togglePower;
    QAction* throttlePrefs;
//    LocoNetSystemConnectionMemo* memo;
 Logger* log;
 LnPowerManager* pmgr;
 ThrottlesTableCellRenderer* renderer;

private slots:
 void on_newThrottle_clicked();
    void on_togglePower_clicked();
    void on_emergencyStop_clicked();
    void propertyChange(PropertyChangeEvent* e);
    void refreshList();
    void onThrottleWindowChanged(PropertyChangeEvent*);
    friend class PropertyChangeSupport;
};

#endif // LISTTHROTTLES_H
