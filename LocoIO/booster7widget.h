#ifndef BOOSTER7WIDGET_H
#define BOOSTER7WIDGET_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class Booster7Widget;
}

class Booster7Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Booster7Widget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc,QWidget *parent = nullptr);
    ~Booster7Widget();

private:
    Ui::Booster7Widget *ui;
    int port;
    int channel;
    LocoIOData* data;
    //LnPacketizer* packetizer;
    LnTrafficController* tc;

private slots:
    void onMessageReceived(LocoNetMessage *msg, bool b);
    void onSVChanged(int channel, int iOld, int iNew,QString ss);

};

#endif // BOOSTER7WIDGET_H
