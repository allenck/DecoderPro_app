#ifndef BOOSTERPANEL_H
#define BOOSTERPANEL_H

#include <QWidget>
#include "lntrafficcontroller.h"
#include "locoiodata.h"

namespace Ui {
class BoosterPanel;
}

class BoosterPanel : public QWidget
{

 Q_OBJECT
    
public:
     BoosterPanel(LocoIOData* data, int port, LnTrafficController* tc, QWidget *parent = 0);
    ~BoosterPanel();

public slots:
 void retranslateControls();
 void onMessageReceived(LocoNetMessage*, bool);

private:
    Ui::BoosterPanel *ui;
    LocoIOData* data;
    int port;
    int channel;
    LnTrafficController* tc;
};

#endif // BOOSTERPANEL_H
