#ifndef ROSTERENTRYPANE_H
#define ROSTERENTRYPANE_H

#include <QWidget>
#include "libPr3_global.h"
#include <QLineEdit>
namespace Ui {
class RosterEntryPane;
}

class DccLocoAddressSelector;
class RosterEntry;
class LIBPR3SHARED_EXPORT RosterEntryPane : public QWidget
{
    Q_OBJECT

public:
    explicit RosterEntryPane(RosterEntry* r, QWidget *parent = 0);
    ~RosterEntryPane();
    void updateGUI(RosterEntry* re);
    /*public*/ bool guiChanged(RosterEntry* r);
    /*public*/ bool checkDuplicate();
    /*public*/ void update(RosterEntry* r);
    /*public*/ void setDccAddress(QString a);
    /*public*/ void setDccAddressLong(bool m);
    /*public*/ QLineEdit* id();
public slots:
    void on_edID_editingFinished();
    void on_edRoadName_editingFinished();
    void on_edRoadNumber_editingFinished();
    void on_edManufacturer_editingFinished();
    void on_edOwner_editingFinished();
    void on_edModel_editingFinished();
    void on_edComment_editingFinished();
    void on_edDecoderComment_editingFinished();
private:
    Ui::RosterEntryPane *ui;
    RosterEntry* re;
    DccLocoAddressSelector* addrSel;
};

#endif // ROSTERENTRYPANE_H
