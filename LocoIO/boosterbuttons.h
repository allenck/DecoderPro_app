#ifndef BOOSTERBUTTONS_H
#define BOOSTERBUTTONS_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class BoosterButtons;
}

class BoosterButtons : public QWidget
{
    Q_OBJECT

public:
    explicit BoosterButtons(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QWidget *parent = nullptr);
    ~BoosterButtons();

private:
    Ui::BoosterButtons *ui;
    int port;
    int channel;
    LocoIOData* data;
    //LnPacketizer* packetizer;
    LnTrafficController* tc;

private slots:
    void onMessageReceived(LocoNetMessage *msg, bool b);
    void onSVChanged(int channel, int iOld, int iNew,QString ss);
    void onGoClicked();
    void onStopClicked();
};

#endif // BOOSTERBUTTONS_H
