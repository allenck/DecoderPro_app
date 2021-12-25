#include "consisttoolscaffold.h"
#include "dcclocoaddressselector.h"
#include "dcclocoaddress.h"
#include "sleeperthread.h"
#include <QDebug>
/*
 *  Helper class for operating the Consist Tool Frame.
 *
 *  @author Paul Bender Copyright (C) 2018
 */
// /*public*/ class ConsistToolScaffold extends JFrameOperator {

/*public*/ ConsistToolScaffold::ConsistToolScaffold(QObject *parent)
 : JFrameOperator(tr("Consist Control"))
{
     //super(tr("Consist Control"));
}

// push consist type buttons.
/*public*/ void ConsistToolScaffold::pushAdvancedConsistButton(){
     (new JRadioButtonOperator(this,tr("Advanced Consist")))->push();
}

/*public*/ void ConsistToolScaffold::pushCommandStationConsistButton(){
     (new JRadioButtonOperator(this,tr("Command Station Consist")))->push();
}

// fill out the consist address field
/*public*/ void ConsistToolScaffold::setConsistAddressValue(QString value){
DccLocoAddressSelector* sel = (DccLocoAddressSelector*)(new JLabelOperator(this,tr("Consist:")))->getLabelFor();
 int addr = (value.toInt());
 sel->setAddress(new DccLocoAddress(addr,addr>=100));
}

// push loco specific buttons at the top.
/*public*/ void ConsistToolScaffold::pushAddButton(){
     (new JButtonOperator(this, tr("Add")))->push();
}

/*public*/ void ConsistToolScaffold::pushResetButton(){
     (new JButtonOperator(this, tr("Reset")))->push();
}

// fill out the loco address field
/*public*/ void ConsistToolScaffold::setLocoAddressValue(QString value){
     //new JTextFieldOperator((JTextField) new JLabelOperator(this,tr("LocoLabelText")).getLabelFor()).setText(value);
DccLocoAddressSelector* sel = (DccLocoAddressSelector*)(new JLabelOperator(this,tr("New Locomotive:")))->getLabelFor();
     int addr = (value).toInt();
 sel->setAddress(new DccLocoAddress(addr,addr>=100));
}


// push the buttons at the bottom.
/*public*/ void ConsistToolScaffold::pushDeleteButton()
{
     JButtonOperatorO1* jbo = new JButtonOperatorO1(this, /*new ComponentChooser()*/"");
//     {
//         //@Override
//         /*public*/ bool checkComponent(Component comp) {
//             QString tooltip = ((JButton)comp).getToolTipText();
//             if(tooltip!=null) {
//                 return tooltip.equals(tr("DeleteButtonToolTip"));
//             } else {
//                 return false;
//             }
//         }
//         //@Override
//         /*public*/ QString getDescription() {
//             return "tooltip for delete button";
//         }
//     }
//     );
 jbo->push();
}

/*public*/ bool JButtonOperatorO1::checkComponent(QWidget* comp)
{
    QString tooltip = ((QPushButton*)comp)->toolTip();
    if(tooltip!="") {
        return tooltip == (tr("Delete the Consist/remove all locomotives"));
    } else {
        return false;
    }
}


// push the buttons at the bottom and dismiss the resulting question dialog.
/*public*/ void ConsistToolScaffold::pushDeleteWithDismiss()
{

// JDialogOperator* jdo = new JDialogOperator(tr("Question"));
//     (new JButtonOperator(jdo,tr("Yes")))->push();
 DeleteWithDismiss* dwd = new DeleteWithDismiss();
 QThread* thread = new QThread();
 thread->setObjectName("DeleteWithDismiss");
 dwd->moveToThread(thread);
 connect(thread, SIGNAL(started()), dwd, SLOT(process()));
 connect(dwd, SIGNAL(finished()), thread, SLOT(quit()));
 connect(dwd, SIGNAL(finished()), thread, SLOT(deleteLater()));
 connect(thread, SIGNAL(finished()), dwd, SLOT(deleteLater()));
 thread->start();
 // and dismiss the dialog that appears by pressing OK.
 pushDeleteButton();  // and dismiss the dialog that appears by pressing OK.
 qApp->processEvents(QEventLoop::AllEvents, 100);

}

DeleteWithDismiss::DeleteWithDismiss()
{

}

void DeleteWithDismiss::process()
{
 qDebug() << "start DeleteWithDismiss";
 start = QDateTime::currentMSecsSinceEpoch();

 while(true)
 {
  try
  {
   JDialogOperator* jdo = new JDialogOperator(tr("Question"));
   qDebug() << "ready to click";
   (new JButtonOperator(jdo,tr("Yes")))->push();
   break;
  }
  catch(Exception* e)
  {
   // do nothing
   qDebug() << e->getMessage();
  }
  if((QDateTime::currentMSecsSinceEpoch() - start) < 200)
  {
   qApp->processEvents();
   continue;
  }
  throw new Exception("Dialog never ran");
 }
 qDebug() << "finish DeleteWithDismiss";

 emit finished();
 //exit(0);
}

/*public*/ void ConsistToolScaffold::pushThrottleButton(){
     (new JButtonOperator(this,tr("Throttle")))->push();
}

/*public*/ void ConsistToolScaffold::pushReverseButton(){
     (new JButtonOperator(this,tr("Reverse")))->push();
}

/*public*/ void ConsistToolScaffold::pushRestoreButton(){
     (new JButtonOperator(this,tr("Restore")))->push();
}

/*public*/ void ConsistToolScaffold::startRosterScan(){
     JMenuBarOperator* jmbo = new JMenuBarOperator(this); // there's only one menubar
#if 1
     JMenuOperator* jmo = new JMenuOperator(jmbo, tr("File"));  // NOI18N
     jmo->push();
     JMenuItemOperator* jmio = new JMenuItemOperator(jmo->getMenu(), tr("Scan Roster for Consists"));
     jmio->push();
#endif
}
/*public*/ void ConsistToolScaffold::requestClose()
{
 getFrame()->close();
}

