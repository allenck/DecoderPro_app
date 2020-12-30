#include "cmdstnconfigpane.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include "loconetsystemconnectionmemo.h"
#include "slotmanager.h"
#include "flowlayout.h"
#include <QBoxLayout>
#include "gridbagconstraints.h"
#include <QGridLayout>
#include <QButtonGroup>
#include <QScrollArea>
#include "resourcebundle.h"

CmdStnConfigPane::CmdStnConfigPane(QWidget *parent) :
    LnPanel(parent)
{
 log = new Logger("CmdStnConfigPane");
 CONFIG_SLOT = 127 ;
 MIN_OPTION = 1 ;
 MAX_OPTION = 72 ;
 LabelT = "T";
 LabelC = "C";
 LabelTop = tr("Configure Command Station");

 read = "Read";
 write = "Write";

 oldcontent = QVector<int>(10);
 closedButtons =  QVector<QRadioButton*>(MAX_OPTION, NULL);
 thrownButtons =  QVector<QRadioButton*>(MAX_OPTION, NULL);
 labels = QVector<QLabel*>(MAX_OPTION, NULL);
 isReserved = QVector<bool>(MAX_OPTION,false);
 p2Widgets = QVector<QWidget*>(MAX_OPTION, NULL);
 rb = new ResourceBundle();
}
/**
 * User interface for Command Station Option Programming
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * @author			Alex Shepherd   Copyright (C) 2004
 * @author			Bob Jacobsen  Copyright (C) 2006
 * @version			$Revision: 28086 $
 */
// /*public*/ class CmdStnConfigPane extends LnPanel implements LocoNetListener {

 /**
 *
 */
//private static final long serialVersionUID = -4164148406541743498L;

///*public*/ CmdStnConfigPane() {
//super();
//}

//ResourceBundle rb;

/*public*/ QString CmdStnConfigPane::getHelpTarget() { return "package.jmri.jmrix.loconet.cmdstnconfig.CmdStnConfigFrame"; }

/*public*/ QString CmdStnConfigPane::getTitle()
{
 QString uName = "";
 if (memo!=NULL)
 {
  uName = memo->getUserName();
  if ("LocoNet"!=(uName))
  {
   uName = uName+": ";
  }
  else
  {
   uName = "";
  }
 }
 return uName+tr("Configure Command Station");
}

/*public*/ void CmdStnConfigPane::initComponents(LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);

 // set up constants from properties file, if possible
 QString name = "<unchanged>";
 // TODO: define class LnCommandStationType
  name = ((SlotManager*)memo->getSlotManager())->getCommandStationType()->getName();
  // get first token
  if ( name.indexOf(' ') != -1) name = name.mid(0, name.indexOf(' '));
  log->debug("match /"+name+"/");
  //rb = ResourceBundle.getBundle("jmri.jmrix.loconet.cmdstnconfig."+name+"options");
  rb->getBundle(name);

  CONFIG_SLOT = rb->getString("CONFIG_SLOT").toInt();
  MIN_OPTION =  rb->getString("MIN_OPTION").toInt();
  MAX_OPTION =  rb->getString("MAX_OPTION").toInt();
  LabelT = rb->getString("LabelT");
  LabelC = rb->getString("LabelC");
  LabelTop = rb->getString("LabelTop");
  read = rb->getString("ButtonRead");
  write = rb->getString("ButtonWrite");
// catch (Exception e)
// {
//  log->error("Failed to load values from /"+name+"/ properties");
// }

 log->debug("Constants: "+QString::number(CONFIG_SLOT)+" "+QString::number(MIN_OPTION)+" "+QString::number(MAX_OPTION));

 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

 {
  // section holding buttons buttons
  readButton = new QPushButton(read);
  writeButton = new QPushButton(write);

  QWidget* pane = new QWidget();
  FlowLayout* paneLayout;
  pane->setLayout(paneLayout = new FlowLayout());
  paneLayout->addWidget(readButton);
  paneLayout->addWidget(writeButton);
  thisLayout->addWidget(pane);

  optionBox = new QCheckBox(rb->getString("CheckBoxReserved"));
  thisLayout->addWidget(optionBox);

  // heading
  thisLayout->addWidget(new QLabel(rb->getString("HeadingText")));

  // section holding options
  QWidget* options = new QWidget();
  GridBagConstraints gc;// = GridBagConstraints();
  QGridLayout* gl = new QGridLayout();
  gc.gridy = 0;
  gc.ipady = 0;

  options->setLayout(gl);
  for (int i = MIN_OPTION; i<=MAX_OPTION; i++)
  {
   QWidget* p2 = new QWidget();
   FlowLayout* p2Layout;
   p2->setLayout(p2Layout = new FlowLayout());
   QButtonGroup* g = new QButtonGroup();
   QRadioButton* c = new QRadioButton(LabelC);
   QRadioButton* t = new QRadioButton(LabelT);
   g->addButton(c);
   g->addButton(t);

   p2Layout->addWidget(t);
   p2Layout->addWidget(c);

   closedButtons.replace(i-MIN_OPTION, c);
   thrownButtons.replace(i-MIN_OPTION, t);
   gc.weightx = 1.0;
   gc.gridx = 0;
   gc.anchor = GridBagConstraints::CENTER;
   //gl.setConstraints(p2, gc);
   gl->addWidget(p2, gc.gridy, gc.gridx);
   gc.gridx = 1;
   gc.weightx = GridBagConstraints::REMAINDER;
   gc.anchor = GridBagConstraints::WEST;
   QString label;
   label = rb->getString("Option"+QString::number(i));
   isReserved.replace(i-MIN_OPTION, false);
   if(label == "")
   {
    label = QString::number(i)+": "+rb->getString("Reserved");
    isReserved.replace(i-MIN_OPTION, true);
   }
   QLabel* l = new QLabel(label);
   labels.replace(i-MIN_OPTION, l);
   //gl.setConstraints(l, gc);
   gl->addWidget(l, gc.gridy, gc.gridx);
   p2Widgets.replace(i-MIN_OPTION,p2);
   gc.gridy++;
  }
  QScrollArea* js = new QScrollArea(/*options*/);
  js->setWidget(options);
//  js.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//  js.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  thisLayout->addWidget(js);
 }

// optionBox.addActionListener(new java.awt.event.ActionListener() {
//  /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//    updateVisibility(optionBox.isSelected());
//  }
//});
 connect(optionBox, SIGNAL(toggled(bool)), this, SLOT(updateVisibility(bool)));
// readButton.addActionListener(new java.awt.event.ActionListener() {
//  /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//    readButtonActionPerformed(e);
//  }
// });
 connect(readButton, SIGNAL(clicked()), this, SLOT(readButtonActionPerformed()));
// writeButton.addActionListener(new java.awt.event.ActionListener() {
//  /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//    writeButtonActionPerformed(e);
//  }
// });
 connect(writeButton, SIGNAL(clicked()),this, SLOT(writeButtonActionPerformed()));

 updateVisibility(optionBox->isChecked());

 // connect to the LnTrafficController
 //memo->getLnTrafficController()->addLocoNetListener(~0, (LocoNetListener*) this);
 connect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));

 // and start
 start();
}

void CmdStnConfigPane::updateVisibility(bool show)
{
 for (int i = MIN_OPTION; i<=MAX_OPTION; i++)
 {
  if (isReserved[i-MIN_OPTION])
  {
   closedButtons[i-MIN_OPTION]->setVisible(show);
   thrownButtons[i-MIN_OPTION]->setVisible(show);
   labels[i-MIN_OPTION]->setVisible(show);
   p2Widgets.at(i-MIN_OPTION)->setVisible(show);
  }
 }
 //revalidate();
}

/*public*/ void CmdStnConfigPane::readButtonActionPerformed(JActionEvent* /*e*/)
{
 // format and send request
 start();
}

/*public*/ void CmdStnConfigPane::writeButtonActionPerformed(JActionEvent* /*e*/)
{
 LocoNetMessage* msg = new LocoNetMessage(14);
 msg->setElement(0, LnConstants::OPC_WR_SL_DATA);
 msg->setElement(1, 0x0E);
 msg->setElement(2, CONFIG_SLOT);

// load last seen contents into message
for (int i = 0; i<10; i++)
    msg->setElement(3+i, oldcontent[i]);

// load contents to message
for (int i = 0; i <= (MAX_OPTION - MIN_OPTION); i++)
{
 // i indexes over closed buttons
 int byteIndex = i / 8; // byteIndex = 0 is the first payload byte
 if (byteIndex > 3)
  byteIndex++; // Skip the 4th payload byte for some reason

 byteIndex += 3 ; // Add base offset into slot message to first data byte

 int bitIndex = i % 8;
 int bitMask = 0x01 << bitIndex ;

 if (closedButtons.at(i)->isChecked())
    msg->setElement(byteIndex, msg->getElement(byteIndex) | bitMask );
  else
    msg->setElement(byteIndex, msg->getElement(byteIndex) & ~bitMask );
 }

 // send message
 memo->getLnTrafficController()->sendLocoNetMessage(msg);
 return;
}

/**
*
* Start the Frame operating by asking for a read
*/
/*public*/ void CmdStnConfigPane::start()
{
 // format and send request for slot contents
    LocoNetMessage* l = new LocoNetMessage(4);
 l->setElement(0, LnConstants::OPC_RQ_SL_DATA);
 l->setElement(1, CONFIG_SLOT );
 l->setElement(2, 0);
 l->setElement(3, 0);
 memo->getLnTrafficController()->sendLocoNetMessage(l);
}

/**
* Process the incoming message to look for Slot 127 Read
*/

/*public*/ void CmdStnConfigPane::message(LocoNetMessage* msg)
{
 if (msg->getOpCode() != LnConstants::OPC_SL_RD_DATA)
  return;
 if (msg->getElement(2) != CONFIG_SLOT )
  return;

 // save contents for later
 for (int i = 0; i<10; i++)
    oldcontent.replace(i, msg->getElement(3+i));

 // set the GUI
 for (int i = 0; i <= (MAX_OPTION - MIN_OPTION); i++)
 {
  // i indexes over closed/thrown buttons
  int byteIndex = i / 8; // index = 0 is the first payload byte
  if (byteIndex > 3)
    byteIndex++; // Skip the 4th payload byte for some reason

  byteIndex += 3 ; // Add base offset to first data byte

  int bitIndex = i % 8;
  int bitMask = 0x01 << bitIndex ;

  int data = msg->getElement( byteIndex );  // data is the payload byte

  if ( (data & bitMask ) != 0)
    closedButtons[ i ]->setChecked(true);
  else
    thrownButtons[ i ]->setChecked(true);
 }

 log->debug("Config Slot Data: " + msg->toString());
}

/*public*/ void CmdStnConfigPane::dispose()
{
 // disconnect from LnTrafficController
 memo->getLnTrafficController()->removeLocoNetListener(~0, (LocoNetListener*)this);
 //super.dispose();

}
#if 0
ResourceBundle::ResourceBundle()
{
 map = new QMap<QString, QString>();
 log = new Logger("ResourceBundle");
}
void ResourceBundle::getBundle(QString name)
{
 if(name == "DCS51")
 {
  initDCS51();
 }
 else if(name == "LocoBuffer")
 {
  initLocoBuffer();
 }
 else
 {
  log->error(QString("Command station '%1' not found, using 'Default'").arg(name));
  initDefault();
 }
}

QString ResourceBundle::getString( QString key)
{
 return map->value(key,"");
}
void ResourceBundle::initDCS51()
{
 map = new QMap<QString, QString>();
 map->insert("ButtonRead", tr("Read"));
 map->insert("ButtonWrite", tr("Write"));
 map->insert("CONFIG_SLOT", tr("127"));
 map->insert("CheckBoxReserved", tr("Show reserved option switches"));
 map->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 map->insert("LabelC", tr("C"));
 map->insert("LabelT", tr("T"));
 map->insert("LabelTop", tr("DCS51 (Zephyr) Programmer"));
 map->insert("MAX_OPTION", tr("49"));
 map->insert("MIN_OPTION", tr("1"));
 map->insert("Option1", tr("1: One jump port (normally two)"));
 map->insert("Option10", tr("10: Recall Depth 4"));
 map->insert("Option11", tr("11: Recall Depth 8"));
 map->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 map->insert("Option14", tr("14: Disable loco address purging"));
 map->insert("Option15", tr("15: Purge will force a loco to zero speed"));
 map->insert("Option17", tr("17: Automatic advanced consists are disabled"));
 map->insert("Option18", tr("18: Extend booster short shutdown to 1/2 second"));
 map->insert("Option2", tr("2: Booster/Throttle, not command station"));
 map->insert("Option20", tr("20: Disable address 0 analog operation"));
 map->insert("Option21", tr("21: Global default for new loco: FX"));
 map->insert("Option22", tr("22: Global default for new loco: 28 step"));
 map->insert("Option23", tr("23: Global default for new loco: 14 step"));
 map->insert("Option27", tr("27: Disable normal switch commands (Bushby bit)"));
 map->insert("Option28", tr("28: Disable DS54 interrogate at power on"));
 map->insert("Option3", tr("3: Booster is autoreversing"));
 map->insert("Option33", tr("33: Restore track power to prior state at power on"));
 map->insert("Option34", tr("34: Allow track to power up to run state"));
 map->insert("Option39", tr("39: Clear all internal memory"));
 map->insert("Option43", tr("43: Disable LocoNet update of track status"));
 map->insert("Option45", tr("45: Disable reply for switch state request"));
 map->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 map->insert("Option6", tr("6: Function 3 is non-latching"));
 map->insert("Option7", tr("7: Blast-mode programming for sound decoders"));
 map->insert("Reserved", tr("Reserved"));
}
void ResourceBundle::initDefault()
{
 map = new QMap<QString, QString>();
 map->insert("ButtonRead", tr("Read"));
 map->insert("ButtonWrite", tr("Write"));
 map->insert("CONFIG_SLOT", tr("127"));
 map->insert("CheckBoxReserved", tr("Show reserved option switches"));
 map->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 map->insert("LabelC", tr("C"));
 map->insert("LabelT", tr("T"));
 map->insert("LabelTop", tr("DCS51 (Zephyr) Programmer"));
 map->insert("MAX_OPTION", tr("49"));
 map->insert("MIN_OPTION", tr("1"));
 map->insert("Option10", tr("10: Recall Depth 4"));
 map->insert("Option11", tr("11: Recall Depth 8"));
 map->insert("Option12", tr("12: Trinary addresses 1-80 allowed"));
 map->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 map->insert("Option14", tr("14: Disable loco address purging"));
 map->insert("Option15", tr("15: Purge will force a loco to zero speed"));
 map->insert("Option17", tr("17: Automatic advanced consists are disabled"));
 map->insert("Option18", tr("18: Extend booster short shutdown to 1/2 second"));
 map->insert("Option2", tr("2: Booster/Throttle, not command station"));
 map->insert("Option20", tr("20: Disable address 0 analog operation"));
 map->insert("Option21", tr("21: Global default for new loco: FX"));
 map->insert("Option22", tr("22: Global default for new loco: 28 step"));
 map->insert("Option23", tr("23: Global default for new loco: 14 step"));
 map->insert("Option25", tr("25: Disable aliasing"));
 map->insert("Option26", tr("26: Enable routes"));
 map->insert("Option27", tr("27: Disable normal switch commands (Bushby bit)"));
 map->insert("Option28", tr("28: Disable DS54 interrogate at power on"));
 map->insert("Option3", tr("3: Booster is autoreversing"));
 map->insert("Option31", tr("31: Meter route/switch output when not in trinary"));
 map->insert("Option33", tr("33: Restore track power to prior state at power on"));
 map->insert("Option34", tr("34: Allow track to power up to run state"));
 map->insert("Option36", tr("36: Clear all mobile decoder info and consists"));
 map->insert("Option37", tr("37: Clear all routes"));
 map->insert("Option38", tr("38: Clear the loco roster"));
 map->insert("Option39", tr("39: Clear all internal memory"));
 map->insert("Option41", tr("41: Diagnostic click when LocoNet command received"));
 map->insert("Option42", tr("42: Disable 3 beeps when loco address purged"));
 map->insert("Option43", tr("43: Disable LocoNet update of track status"));
 map->insert("Option45", tr("45: Disable reply for switch state request"));
 map->insert("Option47", tr("47: Program track is brake generator"));
 map->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 map->insert("Option9", tr("9: Allow Motorola trinary echo for 1-256"));
 map->insert("Reserved", tr("Reserved"));
}
void ResourceBundle::initLocoBuffer()
{
 map = new QMap<QString, QString>();
 map->insert("ButtonRead", tr("Read"));
 map->insert("ButtonWrite", tr("Write"));
 map->insert("CONFIG_SLOT", tr("127"));
 map->insert("CheckBoxReserved", tr("Show reserved option switches"));
 map->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 map->insert("LabelC", tr("C"));
 map->insert("LabelT", tr("T"));
 map->insert("LabelTop", tr("DCS51 (Zephyr) Programmer"));
 map->insert("MAX_OPTION", tr("41"));
 map->insert("MIN_OPTION", tr("1"));
 map->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 map->insert("Option14", tr("14: Disable loco address purging"));
 map->insert("Option22", tr("22: Global default for new loco: 28 step"));
 map->insert("Option23", tr("23: Global default for new loco: 14 step"));
 map->insert("Option33", tr("33: Restore track power to prior state at power on"));
 map->insert("Option34", tr("34: Allow track to power up to run state"));
 map->insert("Option4", tr("4: Programmer mode only"));
 map->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 map->insert("Reserved", tr("Reserved"));
}
#endif
