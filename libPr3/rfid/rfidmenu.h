#ifndef RFIDMENU_H
#define RFIDMENU_H
#include <QMenu>

class Item;
class RfidSystemConnectionMemo;
class RfidMenu : public QMenu
{
public:
 RfidMenu(RfidSystemConnectionMemo* memo, QWidget *parent = nullptr);

private:
 QList<Item*> panelItems; //= new Item[]{
//     new Item(Bundle.getMessage("MonitorXTitle", "RFID"), "jmri.jmrix.rfid.swing.serialmon.SerialMonPane")
};
/*static*/ class Item {
public:
    QString name;
    QString load;

    Item(QString name, QString load) {
        this->name = name;
        this->load = load;
    }
};

#endif // RFIDMENU_H
