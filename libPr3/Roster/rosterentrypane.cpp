#include "rosterentrypane.h"
#include "ui_rosterentrypane.h"
#include "rosterentry.h"
#include "locoaddress.h"
#include "roster.h"
#include "dcclocoaddressselector.h"

RosterEntryPane::RosterEntryPane(RosterEntry* r, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RosterEntryPane)
{
 ui->setupUi(this);
 re = r;
 addrSel = new DccLocoAddressSelector(/*ui->cbDCCAddr,(JTextField*) ui->edDccAddr*/);
 updateGUI(re);
}

RosterEntryPane::~RosterEntryPane()
{
 delete ui;
}
void RosterEntryPane::updateGUI(RosterEntry* re)
{
 ui->edID->setText(re->getId());
 ui->edRoadName->setText(re->getRoadName());
 ui->edManufacturer->setText(re->getMfg());
 ui->edModel->setText(re->getModel());
 ui->edOwner->setText(re->getOwner());
 ui->edRoadNumber->setText(re->getRoadNumber());
//    ui->edDccAddr->setText(QString::number(re->getDccLocoAddress()->getNumber()));
//    ui->cbDCCAddr->setCurrentIndex(re->getDccLocoAddress()->getProtocol());
 if(ui->edDccAddr != NULL)
 {
  ui->horizontalLayout->removeWidget(ui->edDccAddr);
  delete ui->edDccAddr;
  ui->edDccAddr = NULL;
  ui->horizontalLayout->removeWidget(ui->cbDCCAddr);
  delete ui->cbDCCAddr;
  ui->cbDCCAddr = NULL;
  ui->horizontalLayout->addWidget(addrSel->getCombinedJPanel());
 }
 addrSel->setAddress(re->getDccLocoAddress());
 addrSel->setEnabled(false);
 if(re->getId() == "<new loco>")
  addrSel->setEnabled(true);
 ui->edComment->setPlainText(re->getComment());
 ui->edDecoderComment->setPlainText(re->getDecoderComment());
 ui->lblDecoderFamily->setText(re->getDecoderFamily());
 ui->lblDecoderModel->setText(re->getDecoderModel());
 ui->lblFilename->setText(re->getFileName());
 ui->lblDateModified->setText(re->getDateUpdated());
}
/**
 * Does the GUI contents agree with a RosterEntry?
 */
/*public*/ bool RosterEntryPane::guiChanged(RosterEntry* r)
{
 if (r->getRoadName()!=(ui->edRoadName->text()) ) return true;
 if (r->getRoadNumber()!=(ui->edRoadNumber->text()) ) return true;
 if (r->getMfg()!=(ui->edManufacturer->text()) ) return true;
 if (r->getOwner()!=(ui->edOwner->text()) ) return true;
 if (r->getModel()!=(ui->edModel->text()) ) return true;
 if (r->getComment()!=(ui->edComment->toPlainText()) ) return true;
 if (r->getDecoderFamily()!=(ui->lblDecoderFamily->text()) ) return true;
 if (r->getDecoderModel()!=(ui->lblDecoderModel->text()) ) return true;
 if (r->getDecoderComment()!=(ui->edDecoderComment->toPlainText()) ) return true;
 if (r->getId()!=(ui->edID->text()) ) return true;
 if (r->getMaxSpeedPCT() != ( ui->sbSpeed->value()))
  return true;
    //DccLocoAddress* a = addrSel.getAddress();
    //DccLocoAddress a = DccLocoAddress(ui->edDccAddr->text().toInt(), ui->cbDCCAddr->currentIndex());
 DccLocoAddress* a = addrSel->getAddress();
 if (a==NULL)
 {
  if (r->getDccAddress()!=("")) return true;
 }
 else
 {
  if(r->getProtocol()!=a->getProtocol()) return true;
  if ( r->getDccAddress()!=(QString::number(a->getNumber())) ) return true;
 }
 return false;
}
/**
 *
 * @return true if the value in the id JTextField
 * is a duplicate of some other RosterEntry in the roster
 */
/*public*/ bool RosterEntryPane::checkDuplicate()
{
    // check its not a duplicate
    QList<RosterEntry*> l = Roster::instance()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, ui->edID->text());
    bool oops = false;
    for (int i=0; i<l.size(); i++) {
        if (re!=l.at(i)) oops =true;
    }
    return oops;
}
/**
 * Fill a RosterEntry object from GUI contents
 **/
/*public*/ void RosterEntryPane::update(RosterEntry* r)
{
 r->setId(ui->edID->text());
 r->setRoadName(ui->edRoadName->text());
 r->setRoadNumber(ui->edRoadNumber->text());
 r->setMfg(ui->edManufacturer->text());
 r->setOwner(ui->edOwner->text());
 r->setModel(ui->edModel->text());
#if 1 // Done, see below:
 DccLocoAddress* a = addrSel->getAddress();
 if (a != NULL)
 {
  r->setDccAddress(QString::number(a->getNumber()));
  r->setProtocol(a->getProtocol());
 }
#endif
//    DccLocoAddress a = DccLocoAddress(ui->edDccAddr->text().toInt(), ui->cbDCCAddr->currentIndex());
//    r->setDccAddress(ui->edDccAddr->text());
//    r->setProtocol((LocoAddress::Protocol)ui->cbDCCAddr->currentIndex());
 r->setComment(ui->edComment->toPlainText());

 //JComponent editor = maxSpeedSpinner.getEditor();
 r->setMaxSpeedPCT(ui->sbSpeed->value());
 r->setDecoderFamily(ui->lblDecoderFamily->text());
 r->setDecoderModel(ui->lblDecoderModel->text());
 r->setDecoderComment(ui->edDecoderComment->toPlainText());
}
/*public*/ void RosterEntryPane::setDccAddress(QString a)
{
 DccLocoAddress* addr = addrSel->getAddress();
 LocoAddress::Protocol protocol = addr->getProtocol();
 addrSel->setAddress(new DccLocoAddress(a.toInt(), protocol));
}
/*public*/ void RosterEntryPane::setDccAddressLong(bool m)
{
 DccLocoAddress* addr = addrSel->getAddress();
 int n = 0;
 if(addr!=NULL)
 {
  //If the protocol is already set to something other than DCC, then do not try to configure it as DCC long or short.
  if(addr->getProtocol() != LocoAddress::DCC_LONG
                   && addr->getProtocol() != LocoAddress::DCC_SHORT
                   && addr->getProtocol() != LocoAddress::DCC )
   return;
  n = addr->getNumber();
 }
 addrSel->setAddress(new DccLocoAddress(n, m));
}
void RosterEntryPane::on_edID_editingFinished()
{
 QString txt = ui->edID->text();
 if(txt == "") ui->edID->setText(re->getId());
 re->setId(txt);
}

void RosterEntryPane::on_edRoadName_editingFinished()
{
 re->setRoadName(ui->edRoadName->text());
}

void RosterEntryPane::on_edRoadNumber_editingFinished()
{
 re->setRoadNumber(ui->edRoadNumber->text());
}

void RosterEntryPane::on_edManufacturer_editingFinished()
{
 re->setMfg(ui->edManufacturer->text());
}

void RosterEntryPane::on_edOwner_editingFinished()
{
 re->setOwner(ui->edOwner->text());
}

void RosterEntryPane::on_edModel_editingFinished()
{
 re->setModel(ui->edModel->text());
}

void RosterEntryPane::on_edComment_editingFinished()
{
 re->setComment(ui->edComment->toPlainText());
}

void RosterEntryPane::on_edDecoderComment_editingFinished()
{
 re->setDecoderComment(ui->edDecoderComment->toPlainText());
}
