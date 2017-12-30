#include "addsignalmastpanel.h"
#include "instancemanager.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "defaultsignalsystemmanager.h"
#include "defaultsignalsystem.h"
#include "xmlfile.h"
#include "fileutil.h"
#include "../Tables/jmribeancombobox.h"
#include "jtextfield.h"
#include "slotmanager.h"
#include "signalheadsignalmast.h"
#include <QMessageBox>
#include "turnoutmanager.h"
#include "defaultsignalappearancemap.h"
#include "signalmast.h"
#include "turnoutsignalmast.h"
#include "virtualsignalmast.h"
//#include "dccsignalmast.h"
#include "../Tables/beanselectcreatepanel.h"
#include "defaultsignalmastmanager.h"
#include "stringutil.h"
#include "decimalformat.h"
#include "actionevent.h"
#include "jmriuserpreferencesmanager.h"

//AddSignalMastPanel::AddSignalMastPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * JPanel to create a new SignalMast
 *
 * @author	Bob Jacobsen    Copyright (C) 2009, 2010
 * @version     $Revision: 22539 $
 */

///*public*/ class AddSignalMastPanel extends JPanel {



/*public*/ AddSignalMastPanel::AddSignalMastPanel(QWidget *parent) :
    QWidget(parent)
{
 init();



}

/*public*/ AddSignalMastPanel::AddSignalMastPanel(SignalMast* mast, QWidget *parent) :
    QWidget(parent)
{
    init();
    inEditMode=true;
    this->mast=mast;
    sigSysBox->setEnabled(false);
    mastBox->setEnabled(false);
    signalMastDriver->setEnabled(false);
    userName->setText(mast->getUserName());
    userName->setEnabled(false);
    //sigSysBox->setCurrentIndex(sigSysBox->findText(((AbstractSignalMast*)mast)->getSignalSystem()->getSystemName()));
   sigSysBox->setCurrentIndex(sigSysBox->findText(((AbstractSignalMast*)mast)->getSignalSystem()->getUserName()));
   loadMastDefinitions();

    QString mastType = "appearance-" + extractMastTypeFromMast(((AbstractSignalMast*)mast)->getSystemName())+".xml";
    for(int i = 0; i<mastNames->size(); i++)
    {
     if (mastNames->at(i).fileName().endsWith(mastType))
     {
      mastBox->setCurrentIndex(i);
      break;
     }
    }
    mastNames->at(mastBox->currentIndex()).fileName();

    signalMastDriver->setEnabled(false);

    systemPrefixBoxLabel->setEnabled(true);
    systemPrefixBox->setEnabled(true);
    dccAspectAddressLabel->setEnabled(true);
    dccAspectAddressField->setEnabled(true);

    //if(mast instanceof SignalHeadSignalMast)
    if(qobject_cast<SignalHeadSignalMast*>(mast)!=NULL)
    {
        signalMastDriver->setCurrentIndex(signalMastDriver->findText(tr("Signal Head Controlled Mast")));
        updateSelectedDriver();

        signalHeadPanel->setVisible(false);

        QStringList* disabled = ((SignalHeadSignalMast*)mast)->getDisabledAspects();
        if(disabled!=NULL){
            foreach(QString aspect, *disabled){
                if(disabledAspects->contains(aspect)){
                    disabledAspects->value(aspect)->setChecked(true);
                }
            }
        }

    }
    //else if(mast instanceof jmri.implementation.TurnoutSignalMast)
    if(qobject_cast<TurnoutSignalMast*>(mast)!=NULL)
    {

     signalMastDriver->setCurrentIndex(signalMastDriver->findText(tr("Turnout Controlled Mast")));

     updateSelectedDriver();
     SignalAppearanceMap* appMap = ((TurnoutSignalMast*)mast)->getAppearanceMap();
     TurnoutSignalMast* tmast = (TurnoutSignalMast*) mast;

     if(appMap!=NULL)
     {
      QStringListIterator aspects (appMap->getAspects());
      while(aspects.hasNext())
      {
        QString key = aspects.next();
        TurnoutAspectPanel* turnPanel = turnoutAspect->value(key);
        turnPanel->setSelectedTurnout(tmast->getTurnoutName(key));
        turnPanel->setTurnoutState(tmast->getTurnoutState(key));
        turnPanel->setAspectDisabled(tmast->isAspectDisabled(key));
      }
     }
     if(tmast->resetPreviousStates())
      resetPreviousState->setChecked(true);
    }
    //else if (mast instanceof jmri.implementation.VirtualSignalMast)
    if(qobject_cast<VirtualSignalMast*>(mast)!=NULL)
    {
     signalMastDriver->setCurrentIndex(signalMastDriver->findText(tr("Virtual Mast")));
     updateSelectedDriver();
     QStringList* disabled = ((VirtualSignalMast*)mast)->getDisabledAspects();
     if(disabled!=NULL)
     {
      foreach(QString aspect, *disabled)
      {
       if(disabledAspects->contains(aspect))
       {
        disabledAspects->value(aspect)->setChecked(true);
       }
      }
     }
    }
#if 0 // TODO: if DCCSignalMast implemented
    //else if (mast instanceof jmri.implementation.DccSignalMast)
    if(qobject_cast<DccSignalMast*>(mast)!=NULL)
    {
        //if(mast instanceof jmri.jmrix.loconet.LNCPSignalMast)
        if(qobject_cast<LNCPSignalMast*>(mast)!=NULL)
        {
            signalMastDriver->setCurrentIndex(signalMastDriver->findText(tr("LNCPMast")));
        } else {
            signalMastDriver->setCurrentIndex(signalMastDriver->findText(tr("DCCMast")));
        }

        updateSelectedDriver();
        SignalAppearanceMap* appMap = mast->getAppearanceMap();
        DccSignalMast* dmast = (DccSignalMast) mast;

        if(appMap!=NULL){
            java.util.Enumeration<QString> aspects = appMap.getAspects();
            while(aspects.hasMoreElements()){
                QString key = aspects.nextElement();
                DCCAspectPanel dccPanel = dccAspect.get(key);
                dccPanel.setAspectId(dmast.getOutputForAppearance(key));
                dccPanel.setAspectDisabled(dmast.isAspectDisabled(key));
            }
        }
        java.util.List<Object> connList = jmri.InstanceManager.getList(jmri.CommandStation.class);
        if(connList!=NULL){
            for(int x = 0; x < connList.size(); x++){
                jmri.CommandStation station = (jmri.CommandStation) connList.get(x);
                systemPrefixBox.addItem(station.getUserName());
            }
        } else {
            systemPrefixBox.addItem("None");
        }
        dccAspectAddressField.setText(QString::number(dmast.getDccSignalMastAddress()));
        systemPrefixBox->setCheckedItem(dmast.getCommandStation().getUserName());

        systemPrefixBoxLabel->setEnabled(false);
        systemPrefixBox->setEnabled(false);
        dccAspectAddressLabel->setEnabled(false);
        dccAspectAddressField->setEnabled(false);
    }
#endif
    cancel->setVisible(true);
//    cancel.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            ((jmri.util.JmriJFrame)getTopLevelAncestor()).dispose();
//        }
//    });
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

QString AddSignalMastPanel::extractMastTypeFromMast(QString name){
    QStringList parts = name.split(":");
    return parts.at(2).mid(0, parts.at(2).indexOf("("));
}
void AddSignalMastPanel::init()
{
    log = new Logger("AddSignalMastPanel");
    systemSelectionCombo = QString()+ this->metaObject()->className()+".SignallingSystemSelected";
    mastSelectionCombo = QString()+this->metaObject()->className()+".SignallingMastSelected";
    driverSelectionCombo = QString()+this->metaObject()->className()+".SignallingDriverSelected";
    alreadyUsed = new QList<NamedBean*>();
    signalMastDriver = new QComboBox();
    QStringList l1 = QStringList();
    l1 <<  tr("Signal Head Controlled Mast")<< tr("Turnout Controlled Mast")<< tr("Virtual Mast");
    signalMastDriver->addItems(l1);
    prefs = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    signalHeadPanel = new QGroupBox();
    turnoutMastPanel = new QWidget();
    dccMastPanel = new QWidget();
    systemPrefixBoxLabel = new QLabel(tr("System") + ":");
    systemPrefixBox = new QComboBox();
    dccAspectAddressLabel = new QLabel(tr("DCC Accessory Address"));
    dccAspectAddressField = new JTextField(5);

    cancel = new QPushButton(tr("Cancel"));

    mast = NULL;

    userName = new JTextField(20);
    sigSysBox = new QComboBox();
    mastBox = new QComboBox();
    includeUsed = new QCheckBox(tr("Include previously used Signal Heads"));
    resetPreviousState = new QCheckBox(tr("Reset previous appearance."));

    mastNames = new QList<QFileInfo>();

    disabledAspects = new QMap<QString, QCheckBox*>(); // need 10
    disabledAspectsPanel = new QGroupBox();
    inEditMode = false;
    map = new QMap<QString, int>();
    headList = new QList<JmriBeanComboBox*>(); // need 5

    turnoutAspect = new QMap<QString, TurnoutAspectPanel*>(); // need 1o
    dccAspect = new QMap<QString, DCCAspectPanel*>(); // need 10
    paddedNumber = new DecimalFormat("0000");

    // Define panel

    //Only allow the creation of DCC SignalMast if a command station instance is present, otherwise it will not work, so no point in adding it.
    if(InstanceManager::getList("CommandStation")!=NULL)
    {
     signalMastDriver->addItem(tr("DCC Signal Mast Decoder"));
     QObjectList* connList = InstanceManager::getList("CommandStation");
     for(int x = 0; x < connList->size(); x++)
     {
      //if(connList.get(x) instanceof jmri.jmrix.loconet.SlotManager)
      if(qobject_cast<SlotManager*>(connList->at(x)))
      {
       signalMastDriver->addItem(tr("LNCP Signal Mast Decoder"));
       break;
      }
     }
    }

    refreshHeadComboBox();
    setLayout(new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));

    QWidget* p;
    p = new QWidget();
    QFont font;
    font.setPointSize(9);
    p->setFont(font);
    QGridLayout* g;
    p->setLayout(g = new QGridLayout()); //jmri.util.javaworld.GridLayout2(4,2));
    g->setSpacing(1);
    QLabel* l = new QLabel(tr("User Name:"));
    g->addWidget(l,0,0);
    g->addWidget(userName, 0,1);

    l = new QLabel(tr("Signal system")+": ");
    g->addWidget(l,1,0);
    g->addWidget(sigSysBox, 1,1);

    l = new QLabel(tr("Mast type")+": ");
    g->addWidget(l,2,0);
    g->addWidget(mastBox, 2, 1);

    layout()->addWidget(p);

    l = new QLabel(tr("Select Mast Driver")+": ");
    g->addWidget(l, 3,0);
    g->addWidget(signalMastDriver, 3,1);
    layout()->addWidget(p);


    //TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
    signalHeadPanel = new QGroupBox();
    signalHeadPanel->setTitle("Signal Heads");
    signalHeadPanel->setLayout(new QVBoxLayout());
    signalHeadPanel->setVisible(false);
    layout()->addWidget(signalHeadPanel);

    //TitledBorder disableborder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
    disabledAspectsPanel = new QGroupBox();
    disabledAspectsPanel->setTitle("Disable Specific Aspects");
    disabledAspectsPanel->setLayout(disabledAspectsPanelLayout = new QGridLayout());
    layout()->addWidget(disabledAspectsPanel);

    turnoutMastScroll = new QScrollArea();
    turnoutMastScroll->setVisible(false);
    layout()->addWidget(turnoutMastScroll);
    turnoutMastScroll->setWidget(turnoutMastPanel);

    dccMastScroll = new QScrollArea();
    dccMastScroll->setVisible(false);
    layout()->addWidget(dccMastScroll);
    dccMastScroll->setWidget(dccMastPanel);

    QPushButton* ok;
    QWidget* buttonHolder = new QWidget();
    buttonHolder->setLayout(new QHBoxLayout());
    buttonHolder->layout()->addWidget(ok = new QPushButton(tr("OK")));
   //    ok.addActionListener(new ActionListener() {
   //        /*public*/ void actionPerformed(ActionEvent e) {
   //            okPressed(e);
   //        }
   //    });
    connect(ok, SIGNAL(clicked()), this, SLOT(okPressed()));
    cancel->setVisible(false);
    buttonHolder->layout()->addWidget(cancel);

    layout()->addWidget(buttonHolder);

    if(prefs->getComboBoxLastSelection(driverSelectionCombo)!=NULL)
           signalMastDriver->setCurrentIndex(signalMastDriver->findText(prefs->getComboBoxLastSelection(driverSelectionCombo)));

   //    signalMastDriver.addActionListener(new ActionListener() {
   //        /*public*/ void actionPerformed(ActionEvent e) {
   //            updateSelectedDriver();
   //        }
   //    });
    connect(signalMastDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSelectedDriver()));
   //    includeUsed.addActionListener(new ActionListener() {
   //        /*public*/ void actionPerformed(ActionEvent e) {
   //            refreshHeadComboBox();
   //        }
   //    });
    connect(includeUsed, SIGNAL(toggled(bool)), this, SLOT(refreshHeadComboBox()));
    // load the list of systemssignalMastDriver
    SignalSystemManager* man = InstanceManager::signalSystemManagerInstance();
    QStringList names = ((DefaultSignalSystemManager*)man)->getSystemNameArray();
    for (int i = 0; i < names.count(); i++)
    {
     //qDebug() << ((DefaultSignalSystem*)((DefaultSignalSystemManager*)man)->getSystem(names.at(i)))->getUserName();
     sigSysBox->addItem(((DefaultSignalSystem*)((DefaultSignalSystemManager*)man)->getSystem(names.at(i)))->getUserName());
    }
    if(prefs->getComboBoxLastSelection(systemSelectionCombo)!=NULL)
     sigSysBox->setCurrentIndex(sigSysBox->findText(prefs->getComboBoxLastSelection(systemSelectionCombo)));
    if(sigSysBox->currentIndex() < 0) sigSysBox->setCurrentIndex(0);
    qDebug() << QString("sigSysBox current text = %1, index %2").arg(sigSysBox->currentText()).arg(sigSysBox->currentIndex());
    loadMastDefinitions();
    updateSelectedDriver();
    updateHeads();
    refreshHeadComboBox();
   // sigSysBox.addItemListener(new ItemListener(){
   //        /*public*/ void itemStateChanged(ItemEvent e) {
   //            loadMastDefinitions();
   //            updateSelectedDriver();
   //        }
   //    });
    connect(sigSysBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sigSysBox_currentIndexChanged(int)));
}
/*protected*/ void AddSignalMastPanel::updateSelectedDriver() // SLOT[]
{
 if(mastBox->currentIndex() <0) return;
 signalHeadPanel->setVisible(false);
 turnoutMastScroll->setVisible(false);
 disabledAspectsPanel->setVisible(false);
 dccMastScroll->setVisible(false);
 if(tr("Turnout Controlled Mast")==(signalMastDriver->currentText()))
 {
  updateTurnoutAspectPanel();
  turnoutMastScroll->setVisible(true);
 }
 else if(tr("Signal Head Controlled Mast")==(signalMastDriver->currentText()))
 {
  updateHeads();
  updateDisabledOption();
  signalHeadPanel->setVisible(true);
  disabledAspectsPanel->setVisible(true);
 }
 else if(tr("Virtual Mast")==(signalMastDriver->currentText()))
 {
  updateDisabledOption();
  disabledAspectsPanel->setVisible(true);
 }
 else if ((tr("DCC Signal Mast Decoder")==(signalMastDriver->currentText())) || (tr("LNCP Signal Mast Decoder")==(signalMastDriver->currentText())))
 {
  updateDCCMastPanel();
  dccMastScroll->setVisible(true);
 }
 //validate();
// if (getTopLevelAncestor()!=NULL)
// {
//  ((jmri.util.JmriJFrame)getTopLevelAncestor()).setSize(((jmri.util.JmriJFrame)getTopLevelAncestor()).getPreferredSize());
//        ((jmri.util.JmriJFrame)getTopLevelAncestor()).pack();
// }
// repaint();
}


void AddSignalMastPanel::updateDisabledOption(){
    QString mastType = mastNames->at(mastBox->currentIndex()).baseName();
    mastType =  mastType.mid(11, mastType.indexOf(".xml"));
    DefaultSignalAppearanceMap* sigMap = DefaultSignalAppearanceMap::getMap(sigsysname, mastType);
    QStringListIterator aspects (sigMap->getAspects());
    disabledAspects = new QMap<QString, QCheckBox*>(); // need 5

    while(aspects.hasNext()){
        QString aspect = aspects.next();
        QCheckBox* disabled = new QCheckBox(aspect);
        disabledAspects->insert(aspect, disabled);
    }
    //disabledAspectsPanel->clear();
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;
    while ((item = disabledAspectsPanelLayout->takeAt(0)))
    {
     if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
     else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
     else {delete item;}
    }
    delete disabledAspectsPanelLayout;

    disabledAspectsPanel->setLayout(disabledAspectsPanelLayout = new QGridLayout());
    disabledAspectsPanelLayout->setSpacing(1);
    for(int i=0; i< disabledAspects->size(); i++)
    {
     QString aspect = disabledAspects->keys().at(i);

     //disabledAspectsPanel.add(disabledAspects->get(aspect));
     disabledAspectsPanelLayout->addWidget(disabledAspects->value(aspect), i, 0);
    }
}

void AddSignalMastPanel::loadMastDefinitions()
{
//    // need to remove itemListener before addItem() or item event will occur
//    if(mastBox.getItemListeners().length >0) {
//        mastBox.removeItemListener(mastBox.getItemListeners()[0]);
//    }
 mastBox->clear();
 try
 {
  mastNames = new QList<QFileInfo>();
  SignalSystemManager* man = InstanceManager::signalSystemManagerInstance();

  // get the signals system name from the user name in combo box
  qDebug() << QString("sigSysBox current text = %1, index %2").arg(sigSysBox->currentText()).arg(sigSysBox->currentIndex());
  if(sigSysBox->currentIndex() < 0) sigSysBox->setCurrentIndex(0);
  QString u = (QString) sigSysBox->currentText();
  sigsysname = ((DefaultSignalSystem*)((DefaultSignalSystemManager*)man)->getByUserName(u))->getSystemName();

   map = new QMap<QString, int>();

   // do file IO to get all the appearances
   // gather all the appearance files
   //Look for the default system defined ones first
   QList<QFileInfo> apps =  QDir(QString("")+"xml"+QDir::separator()+"signals"+QDir::separator()+sigsysname).entryInfoList();
   if(!apps.isEmpty())
   {
    for (int j=0; j<apps.count(); j++)
    {
     if (apps.at(j).fileName().startsWith("appearance")
                            && apps.at(j).fileName().endsWith(".xml"))
     {
      log->debug("   found file: "+apps.at(j).fileName());
      // load it and get name
      mastNames->append(apps.at(j));

      XmlFile* xf = new XmlFile();
      QDomElement root = xf->rootFromFile(new QFile(apps.at(j).absoluteFilePath()));
      QString name = root.firstChildElement("name").text();
      mastBox->addItem(name);

      map->insert(name, (root.firstChildElement("appearances")
                        .firstChildElement("appearance")
                        .elementsByTagName("show")
                        .size()));
     }
     }
    }
   } catch (JDOMException e) {
        mastBox->addItem("Failed to create definition, did you select a system?");
        log->warn("in loadMastDefinitions"+ e.getMessage());
   } catch (IOException e) {
        mastBox->addItem("Failed to read definition, did you select a system?");
        log->warn("in loadMastDefinitions" + e.getMessage());
   }

   try
   {
    QList<QFileInfo> apps =  QDir(FileUtil::getUserFilesPath()+"resources"+QDir::separator()
                +"signals"+QDir::separator()+sigsysname).entryInfoList();
    if(!apps.isEmpty())
    {
        for (int j=0; j<apps.count(); j++)
     {
       if (apps.at(j).fileName().startsWith("appearance")
                            && apps.at(j).fileName().endsWith(".xml"))
       {
        log->debug("   found file: "+apps.at(j).fileName());
        // load it and get name
        //If the mast file name already exists no point in re-adding it
        if(!mastNames->contains(apps.at(j)))
        {
         mastNames->append(apps[j]);

         XmlFile* xf = new XmlFile();
         QDomElement root = xf->rootFromFile(new QFile(apps.at(j).filePath()));
         QString name = root.firstChildElement("name").text();
         //if the mast name already exist no point in readding it.
         if(!map->contains(name))
         {
          mastBox->addItem(name);
          map->insert(name, (root.firstChildElement("appearances")
                                .firstChildElement("appearance")
                                .elementsByTagName("show")
                                .size()));
       }
      }
     }
    }
   }

  } catch (JDOMException e) {
        log->warn("in loadMastDefinitions"+ e.getMessage());
 } catch (IOException e) {
        //Can be considered normal
        log->warn("in loadMastDefinitions"+ e.getMessage());
 }
//    mastBox->addItemListener(new ItemListener(){
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            updateSelectedDriver();
//        }
//    });
 connect(mastBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSelectedDriver()));
    updateSelectedDriver();

    if(prefs->getComboBoxLastSelection(mastSelectionCombo+":"+((QString) sigSysBox->currentText()))!=NULL)
        mastBox->setCurrentIndex(mastBox->findText(prefs->getComboBoxLastSelection(mastSelectionCombo+":"+((QString) sigSysBox->currentText()))));

}


void AddSignalMastPanel::updateHeads()
{
 if(tr("Signal Head Controlled Mast")!=(signalMastDriver->currentText()))
  return;
 if (mastBox->currentText()=="")
  return;
 int count = map->value(mastBox->currentText());
 headList = new QList<JmriBeanComboBox*>();  //need count
 QLayoutItem * item;
 QLayout * sublayout;
 QWidget * widget;
 while ((item = signalHeadPanel->layout()->takeAt(0))) {
     if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
     else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
     else {delete item;}
 }
 delete signalHeadPanel->layout();
 QGridLayout* g;
 signalHeadPanel->setLayout(g = new QGridLayout()); //jmri.util.javaworld.GridLayout2(count+1,1));
 for(int i = 0; i<count; i++)
 {
  JmriBeanComboBox* head = new JmriBeanComboBox((Manager*)InstanceManager::signalHeadManagerInstance());
  head->excludeItems(alreadyUsed);
  headList->append(head);
  g->addWidget(head, i,0);
 }
 includeUsed = new QCheckBox(tr("Include previously used Signal Heads"));
 g->addWidget(includeUsed,count,0);
 connect(includeUsed, SIGNAL(toggled(bool)), this, SLOT(refreshHeadComboBox()));

}
#if 1
void AddSignalMastPanel::okPressed(ActionEvent* /*e*/)
{
 QString mastname = mastNames->at(mastBox->currentIndex()).baseName();

 QString user = userName->text().trimmed();
 if(user==(""))
 {
//  int i = JOptionPane.showConfirmDialog(NULL, "No Username has been defined, this may cause issues when editing the mast later.\nAre you sure that you want to continue?",
//            "No UserName Given",
//            JOptionPane.YES_NO_OPTION);
//        if(i !=0) {
//            return;
//        }
//    }
  switch(QMessageBox::question(0, tr("No userName Given"), tr("No Username has been defined, this may cause issues when editing the mast later.\nAre you sure that you want to continue?"), QMessageBox::Yes | QMessageBox::No))
  {
  default:
  case QMessageBox::No:
   return;
  case QMessageBox::Yes:
   break;
  }
 }
 if(mast==NULL)
 {
   if(tr("Signal Head Controlled Mast")==(signalMastDriver->currentText()))
   {
    if((!checkSignalHeadUse()) || (!checkUserName(userName->text())))
    {
     return;
    }

    QString build = "";
    build.append("IF$shsm:"
            +sigsysname
            +":"+mastname.mid(11,mastname.length()-4));
    foreach(JmriBeanComboBox* head , *headList)
    {
     build.append("("+StringUtil::parenQuote(head->currentText())+")");
    }
    QString name = build;
    log->debug("add signal: "+name);
    SignalMast* m = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(name);
    if(m!=NULL){
//        JOptionPane.showMessageDialog(NULL, java.text.MessageFormat.format(tr("DuplicateMast"),
//                new Object[]{ m.getDisplayName() }) , tr("DuplicateMastTitle"), JOptionPane.INFORMATION_MESSAGE);
        QMessageBox::critical(0, tr("Duplicate Signal Mast"), tr("The creation of this SignalMast will cause a duplication of Signal Mast \"%1\"\nTherefore the SignalMast has not been created").arg(m->getDisplayName()));
        return;
    }
    try {
        m = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->provideSignalMast(name);
    } catch (IllegalArgumentException ex) {
        // user input no good
        handleCreateException(name);
        return; // without creating
    }
    if (user!=("")) m->setUserName(user);

    foreach(QString aspect, disabledAspects->keys())
    {
     if(disabledAspects->value(aspect)->isChecked())
      ((SignalHeadSignalMast*)m)->setAspectDisabled(aspect);
     else
      ((SignalHeadSignalMast*)m)->setAspectEnabled(aspect);
    }
   }
   else if(tr("Turnout Controlled Mast")==(signalMastDriver->currentText()))
   {
    if(!checkUserName(userName->text()))
        return;
    QString name = "IF$tsm:"
            +sigsysname
            +":"+mastname.mid(11,mastname.length()-4);
    name += "($"+(paddedNumber->format(TurnoutSignalMast::getLastRef()+1))+")";
    TurnoutSignalMast* turnMast = new TurnoutSignalMast(name);
    foreach(QString aspect, turnoutAspect->keys())
    {
     turnoutAspect->value(aspect)->setReference(name + ":" + aspect);
     turnoutMastPanel->layout()->addWidget(turnoutAspect->value(aspect)->getPanel());
     if(turnoutAspect->value(aspect)->isAspectDisabled())
      turnMast->setAspectDisabled(aspect);
     else
     {
      turnMast->setAspectEnabled(aspect);
      turnMast->setTurnout(aspect, turnoutAspect->value(aspect)->getTurnoutName(), turnoutAspect->value(aspect)->getTurnoutState());
     }
     turnoutMastScroll->setWidget(turnoutMastPanel);
    }
    turnMast->resetPreviousStates(resetPreviousState->isChecked());
    if (user!=("")) turnMast->setUserName(user);
    ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->Register(turnMast);
   }
   else if(tr("Virtual Mast")==(signalMastDriver->currentText()))
   {
    if(!checkUserName(userName->text()))
        return;
    QString name = "IF$vsm:"
            +sigsysname
            +":"+mastname.mid(11,mastname.length()-4);
    name += "($"+(paddedNumber->format(VirtualSignalMast::getLastRef()+1))+")";
    VirtualSignalMast* virtMast = new VirtualSignalMast(name);
    if (user!=("")) virtMast->setUserName(user);
    ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->Register(virtMast);

    foreach(QString aspect, disabledAspects->keys())
    {
        if(disabledAspects->value(aspect)->isChecked())
            virtMast->setAspectDisabled(aspect);
        else
            virtMast->setAspectEnabled(aspect);

    }
   }
#if 0
   else if((tr("DCC Signal Mast Decoder")==(signalMastDriver->currentText())) || (tr("LNCPMast")==(signalMastDriver->currentText()))){
    if(!checkUserName(userName.getText())){
        return;
    }
    if(!validateDCCAddress()){
        return;
    }
    QString systemNameText = ConnectionNameFromSystemName.getPrefixFromName((QString) systemPrefixBox->currentText());
    //if we return a NULL string then we will set it to use internal, thus picking up the default command station at a later date.
    if(systemNameText==("\0"))
        systemNameText = "I";
    if(tr("LNCPMast")==(signalMastDriver->currentText())){
        systemNameText = systemNameText+ "F$lncpsm:";
    } else {
        systemNameText = systemNameText+ "F$dsm:";
    }
    QString name = systemNameText
            +sigsysname
            +":"+mastname.substring(11,mastname.length()-4);
    name += "("+dccAspectAddressField.getText()+")";
    DccSignalMast dccMast;
    if(tr("LNCPMast")==(signalMastDriver->currentText())){
        dccMast = new jmri.jmrix.loconet.LNCPSignalMast(name);
    } else {
        dccMast = new DccSignalMast(name);
    }

    for(QString aspect: dccAspect.keySet()){
        dccMastPanel.add(dccAspect.get(aspect).getPanel());
        if(dccAspect.get(aspect).isAspectDisabled())
            dccMast.setAspectDisabled(aspect);
        else {
            dccMast.setAspectEnabled(aspect);
            dccMast.setOutputForAppearance(aspect, dccAspect.get(aspect).getAspectId());
        }
    }
    if (!user==("")) dccMast.setUserName(user);
    InstanceManager.signalMastManagerInstance().register(dccMast);

   }
#endif
   prefs->addComboBoxLastSelection(systemSelectionCombo, (QString) sigSysBox->currentText());
   prefs->addComboBoxLastSelection(driverSelectionCombo, (QString) signalMastDriver->currentText());
   prefs->addComboBoxLastSelection(mastSelectionCombo+":"+((QString) sigSysBox->currentText()), (QString) mastBox->currentText());
   refreshHeadComboBox();
  }
  else  // Edit the supplied mast.
  {
   if(tr("Signal Head Controlled Mast")==(signalMastDriver->currentText()))
   {
    SignalHeadSignalMast* headMast = (SignalHeadSignalMast*) mast;
    foreach(QString aspect, disabledAspects->keys())
    {
        if(disabledAspects->value(aspect)->isChecked())
            headMast->setAspectDisabled(aspect);
        else
            headMast->setAspectEnabled(aspect);
    }
   }
   else if(tr("Turnout Controlled Mast")==(signalMastDriver->currentText()))
   {
    QString name = "IF$tsm:"
        +sigsysname
        +":"+mastname.mid(11,mastname.length()-4);
    TurnoutSignalMast* turnMast = (TurnoutSignalMast*) mast;
    foreach(QString aspect, turnoutAspect->keys())
    {
        turnoutAspect->value(aspect)->setReference(name + ":" + aspect);
        turnMast->setTurnout(aspect, turnoutAspect->value(aspect)->getTurnoutName(), turnoutAspect->value(aspect)->getTurnoutState());
        turnoutMastPanel->layout()->addWidget(turnoutAspect->value(aspect)->getPanel());
        if(turnoutAspect->value(aspect)->isAspectDisabled())
            turnMast->setAspectDisabled(aspect);
        else
            turnMast->setAspectEnabled(aspect);
    }
    turnMast->resetPreviousStates(resetPreviousState->isChecked());
   }
   else if(tr("Virtual Mast")==(signalMastDriver->currentText())){
    VirtualSignalMast* virtMast = (VirtualSignalMast*) mast;
    foreach(QString aspect, disabledAspects->keys())
    {
        if(disabledAspects->value(aspect)->isChecked())
            virtMast->setAspectDisabled(aspect);
        else
            virtMast->setAspectEnabled(aspect);
    }
   }
#if 0
   else if((tr("DCC Signal Mast Decoder")==(signalMastDriver->currentText())) || (tr("LNCPMast")==(signalMastDriver->currentText())))
   {
    DccSignalMast dccMast = (DccSignalMast) mast;
    for(QString aspect: dccAspect.keySet())
    {
        dccMastPanel.add(dccAspect.get(aspect).getPanel());
        if(dccAspect.get(aspect).isAspectDisabled())
            dccMast.setAspectDisabled(aspect);
        else
        {
            dccMast.setAspectEnabled(aspect);
            dccMast.setOutputForAppearance(aspect, dccAspect.get(aspect).getAspectId());
        }
    }
   }
#endif
  }
}


bool AddSignalMastPanel::checkUserName(QString nam)
{
if (!((nam==NULL) || (nam==(""))))
{
 // user name changed, check if new name already exists
        NamedBean* nB = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getByUserName(nam);
 if (nB != NULL)
 {
  log->error("User name is not unique " + nam);
//            QString msg = java.text.MessageFormat.format(rb
//                    .getQString("WarningUserName"), new Object[] { ("" + nam) });
//            JOptionPane.showMessageDialog(NULL, msg,
//                        tr("WarningTitle"),
//                            JOptionPane.ERROR_MESSAGE);
  QMessageBox::warning(0, tr("Warning"), tr("User Name \" %1 \" has already been used.").arg(nam));
  return false;
 }
 //Check to ensure that the username doesn't exist as a systemname.
 nB = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getBySystemName(nam);
 if (nB!=NULL)
 {
  log->error("User name is not unique " + nam + " It already exists as a System name");
//        QString msg = java.text.MessageFormat.format(rb
//                .getQString("WarningUserNameAsSystem"), new Object[] { ("" + nam) });
//        JOptionPane.showMessageDialog(NULL, msg,
//                    tr("WarningTitle"),
//                        JOptionPane.ERROR_MESSAGE);
  QMessageBox::warning(0, tr("Warning"), tr("User Name \" %1 \" has already been used as a System Name.").arg(nam));     return false;
  }
 }
 return true;
}

bool AddSignalMastPanel::checkSystemName(QString /*nam*/){
    return false;
}

bool AddSignalMastPanel::checkSignalHeadUse()
{
 for(int i = 0; i<headList->size(); i++)
 {
  JmriBeanComboBox* head = headList->at(i);
        NamedBean* h = headList->at(i)->getSelectedBean();
        for(int j = i; j<headList->size(); j++){
            JmriBeanComboBox* head2check = headList->at(j);
            if((head2check != head) && (head2check->getSelectedBean()==h)){
                if(!duplicateHeadAssigned(headList->at(i)->getSelectedDisplayName()))
                    return false;
            }
        }
        if(includeUsed->isChecked()){
            QString isUsed = SignalHeadSignalMast::isHeadUsed((SignalHead*)h);
            if((isUsed!=NULL) && (!headAssignedElseWhere(h->getDisplayName(), isUsed))){
                return false;
            }
        }
    }
    return true;
}

bool AddSignalMastPanel::duplicateHeadAssigned(QString head)
{
//    int i = JOptionPane.showConfirmDialog(NULL, java.text.MessageFormat.format(tr("DuplicateHeadAssign"),
//                new Object[]{ head }),
//        tr("DuplicateHeadAssignTitle"),
//        JOptionPane.YES_NO_OPTION);

//    if(i ==0) {
//        return true;
//    }
    switch(QMessageBox::question(0, tr("Duplicate Assignment"), tr("You have selected Signal Head \"%1\" to be used in two\ndifferent places on the Signal Mast are you sure?,").arg(head),QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
     return true;
    default:
    case QMessageBox::No:
     break;
    }

    return false;
}

bool AddSignalMastPanel::headAssignedElseWhere(QString head, QString mast){
//    int i = JOptionPane.showConfirmDialog(NULL, java.text.MessageFormat.format(tr("AlreadyAssinged"),
//                new Object[]{ head, mast }),
//        tr("DuplicateHeadAssignTitle"),
//        JOptionPane.YES_NO_OPTION);
//    if(i ==0) {
//        return true;
//    }
    switch(QMessageBox::question(0, tr("Duplicate Assignment"), tr("You have selected Signal Head \"%1\"his head has already been assigned to Signal Mast \"%2\"are you sure you want to do this?").arg(head).arg(mast),QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
     return true;
    default:
        break;
    }

    return false;
}
#endif
void AddSignalMastPanel::refreshHeadComboBox() // SLOT[]
{
 if(tr("Signal Head Controlled Mast")!=(signalMastDriver->currentText()))
  return;
 if(includeUsed->isChecked())
 {
  alreadyUsed = new QList<NamedBean*>();
 }
 else
 {
  QList<SignalHead*>* alreadyUsedHeads = SignalHeadSignalMast::getSignalHeadsUsed();
  alreadyUsed = new QList<NamedBean*>();
  foreach(SignalHead* head, *alreadyUsedHeads)
  {
    alreadyUsed->append(head);
  }
 }

 foreach(JmriBeanComboBox* head,  *headList)
 {
  head->excludeItems(alreadyUsed);
 }
}
void AddSignalMastPanel::handleCreateException(QString sysName) {
//    javax.swing.JOptionPane.showMessageDialog(AddSignalMastPanel.this,
//            java.text.MessageFormat.format(
//                tr("ErrorSignalMastAddFailed"),
//                new Object[] {sysName}),
//            tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(0, tr("Error"), tr("Could not create signal mast \"%1\" to add it. Check that number/name is OK.").arg(sysName));
}

void AddSignalMastPanel::updateTurnoutAspectPanel()
{
 if(tr("Turnout Controlled Mast")!=(signalMastDriver->currentText()))
        return;
 turnoutAspect = new QMap<QString, TurnoutAspectPanel*>(); // need 10
 QString mastType = mastNames->value(mastBox->currentIndex()).baseName();
 mastType =  mastType.mid(11, mastType.indexOf(".xml"));
 DefaultSignalAppearanceMap* sigMap = DefaultSignalAppearanceMap::getMap(sigsysname, mastType);
 QStringListIterator aspects( sigMap->getAspects());
 while(aspects.hasNext())
 {
  QString aspect = aspects.next();
  TurnoutAspectPanel* aPanel = new TurnoutAspectPanel(aspect);
  turnoutAspect->insert(aspect, aPanel);
 }
 if(turnoutMastPanel != NULL && turnoutMastPanel->layout() != NULL)
 {
  for(int i=0; i < turnoutMastPanel->layout()->count(); i++)
  turnoutMastPanel->layout()->removeItem(turnoutMastPanel->layout()->itemAt(i));
 }
 else
 {
  turnoutMastPanel= new QWidget();
  QGridLayout* g;
  turnoutMastPanel->setLayout(g = new QGridLayout()); // turnoutAspect.size()+1,2));
 }
 int i = 0;
 foreach(QString aspect, turnoutAspect->keys())
 {
  //turnoutMastPanel.add(turnoutAspect.get(aspect).getPanel());
  ((QGridLayout*)turnoutMastPanel->layout())->addWidget(turnoutAspect->value(aspect)->getPanel(), i++, 0);
 }
//static
 //turnoutMastPanel.add(resetPreviousState);
 ((QGridLayout*)turnoutMastPanel->layout())->addWidget(resetPreviousState, i, 0);
  turnoutMastScroll->setWidget(turnoutMastPanel);
}

TurnoutAspectPanel::TurnoutAspectPanel(QString aspect)
{
 this->aspect = aspect;
 init();
}
void TurnoutAspectPanel::init()
{
 log = new Logger("TurnoutAspectPanel");
 panel = NULL;

 beanBox = new BeanSelectCreatePanel((Manager*)InstanceManager::turnoutManagerInstance(), NULL);
 disabledCheck = new QCheckBox("Disable Aspect");

 stateThrown = ((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
 stateClosed = ((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
 turnoutStates = QStringList() << stateClosed << stateThrown;
 turnoutStateValues =  QList<int>() << Turnout::CLOSED<< Turnout::THROWN;

 turnoutState = new QComboBox();
 turnoutState ->addItems(turnoutStates);
 turnoutStateLabel = new QLabel("Set State");
 //QString aspect = "";
}

TurnoutAspectPanel::TurnoutAspectPanel(QString turnoutName, int /*state*/)
{
 init();
 if(turnoutName==NULL || turnoutName==(""))
  return;
 beanBox->setDefaultNamedBean(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnoutName));
}

void TurnoutAspectPanel::setReference(QString reference){
    beanBox->setReference(reference);
}

int TurnoutAspectPanel::getTurnoutState(){
    return turnoutStateValues[turnoutState->currentIndex()];
}

void TurnoutAspectPanel::setSelectedTurnout(QString name){
    if(name==NULL || name==(""))
        return;
    beanBox->setDefaultNamedBean(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(name));
}

void TurnoutAspectPanel::setTurnoutState(int state)
{
 if(state==Turnout::CLOSED)
 {
  //turnoutState->setCheckedItem(stateClosed);
  turnoutState->setCurrentIndex(turnoutState->findText(stateClosed));
 }
 else
 {
  //turnoutState->setCheckedItem(stateThrown);
  turnoutState->setCurrentIndex(turnoutState->findText(stateThrown));
 }
}

void TurnoutAspectPanel::setAspectDisabled(bool boo){
    disabledCheck->setChecked(boo);
    if(boo){
        beanBox->setEnabled(false);
        turnoutStateLabel->setEnabled(false);
        turnoutState->setEnabled(false);
    }
    else {
        beanBox->setEnabled(true);
        turnoutStateLabel->setEnabled(true);
        turnoutState->setEnabled(true);
    }
}

bool TurnoutAspectPanel::isAspectDisabled(){
    return disabledCheck->isChecked();
}

QString TurnoutAspectPanel::getTurnoutName(){
    return beanBox->getDisplayName();
}

NamedBean* TurnoutAspectPanel::getTurnout(){
    try {
        return beanBox->getNamedBean();
    } catch (JmriException ex){
        log->warn("skipping creation of turnout");
        return NULL;
    }
}


QWidget* TurnoutAspectPanel::getPanel()
{
if(panel==NULL)
{
 panel = new QGroupBox(aspect);
 panel->setObjectName(aspect);
 panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(panel->sizePolicy().hasHeightForWidth());
 panel->setSizePolicy(sizePolicy);
 QWidget* turnDetails = new QWidget();
 turnDetails->setLayout(new QHBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 turnDetails->layout()->addWidget(beanBox);
 turnDetails->layout()->addWidget(turnoutStateLabel);
 turnDetails->layout()->addWidget(turnoutState);
 panel->layout()->addWidget(turnDetails);
 panel->layout()->addWidget(disabledCheck);
        //TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//     QGroupBox* border = new QGroupBox();
//     border->setTitle(aspect);
//     panel->layout()->addWidget(border);

//            disabledCheck.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setAspectDisabled(disabledCheck->isChecked());
//                }
//            });
 connect(disabledCheck, SIGNAL(toggled(bool)), this, SLOT(setAspectDisabled(bool)));
}
return panel;
}




void AddSignalMastPanel::updateDCCMastPanel(){
#if 0
    if((!tr("DCCMast")==(signalMastDriver->currentText())) && (!tr("LNCPMast")==(signalMastDriver->currentText())))
        return;
    dccAspect = new HashMap<QString, DCCAspectPanel>(10);
    java.util.List<Object> connList = jmri.InstanceManager.getList(jmri.CommandStation.class);
    systemPrefixBox.removeAllItems();
    if(connList!=NULL){
        for(int x = 0; x < connList.size(); x++){
            jmri.CommandStation station = (jmri.CommandStation) connList.get(x);
            if(tr("LNCPMast")==(signalMastDriver->currentText())){
                if(station instanceof jmri.jmrix.loconet.SlotManager){
                    systemPrefixBox.addItem(station.getUserName());
                }
            } else {
                systemPrefixBox.addItem(station.getUserName());
            }
        }
    } else {
        systemPrefixBox.addItem("None");
    }
    QString mastType = mastNames.get(mastBox.getSelectedIndex()).getName();
    mastType =  mastType.substring(11, mastType.indexOf(".xml"));
    jmri.implementation.DefaultSignalAppearanceMap sigMap = jmri.implementation.DefaultSignalAppearanceMap.getMap(sigsysname, mastType);
    java.util.Enumeration<QString> aspects = sigMap.getAspects();
    while(aspects.hasMoreElements()){
        QString aspect = aspects.nextElement();
        DCCAspectPanel aPanel = new DCCAspectPanel(aspect);
        dccAspect.put(aspect, aPanel);
    }
    dccMastPanel.removeAll();
    dccMastPanel.setLayout(new jmri.util.javaworld.GridLayout2(dccAspect.size()+3,2));
    dccMastPanel.add(systemPrefixBoxLabel);
    dccMastPanel.add(systemPrefixBox);
    dccMastPanel.add(dccAspectAddressLabel);
    dccMastPanel.add(dccAspectAddressField);
    if(dccAddressListener==NULL){
        dccAddressListener = new FocusListener() {
            /*public*/ void focusLost(FocusEvent e){
                if(dccAspectAddressField.getText()==("")){
                    return;
                }
                validateDCCAddress();
            }
            /*public*/ void focusGained(FocusEvent e){ }

        };

        dccAspectAddressField.addFocusListener(dccAddressListener);
    }

    if(mast==NULL){
        systemPrefixBoxLabel->setEnabled(true);
        systemPrefixBox->setEnabled(true);
        dccAspectAddressLabel->setEnabled(true);
        dccAspectAddressField->setEnabled(true);
    }

    for(QString aspect: dccAspect.keySet()){
        dccMastPanel.add(dccAspect.get(aspect).getPanel());
    }
    if((dccAspect.size() & 1) == 1)
        dccMastPanel.add(new JLabel());
    dccMastPanel.add(new JLabel(tr("DCCMastCopyAspectId")));
    dccMastPanel.add(copyFromMastSelection());
#endif
}


/*static*/ bool AddSignalMastPanel::validateAspectId(QString strAspect){
    Logger* log = new Logger("AddSignalMastPanel");
    int aspect = -1;
    try{
        aspect=strAspect.trimmed().toInt();
    } catch (NumberFormatException e){
        //JOptionPane.showMessageDialog(NULL, tr("DCCMastAspectNumber"));
        QMessageBox::critical(0, tr("Error"), tr("Aspect ID must be a number"));
        return false;
    }

    if (aspect < 0 || aspect>31) {
//        JOptionPane.showMessageDialog(NULL, tr("DCCMastAspectOutOfRange"));
        QMessageBox::critical(0, tr("Error"), tr("SignalMast aspect should be in the range of 0 to 31"));
        log->error(tr("invalid aspect ") + QString::number(aspect));
        return false;
    }
    return true;
}

bool AddSignalMastPanel::validateDCCAddress(){
    if(dccAspectAddressField->text()==("")){
        //JOptionPane.showMessageDialog(NULL, tr("DCCMastAddressBlank"));
        QMessageBox::critical(0, tr("Error"), tr("A DCC Address must be entered"));
        return false;
    }
    int address =-1;
//    try{
    bool bOk;
        address=dccAspectAddressField->text().trimmed().toInt(&bOk);
//    } catch (NumberFormatException e){
        if(!bOk)
        {
        //JOptionPane.showMessageDialog(NULL, tr("DCCMastAddressNumber"));
        QMessageBox::critical(0, tr("Error"), tr("DCC Address must be a number"));
        return false;
        }
//    }

    if (address < 1 || address>2048) {
        //JOptionPane.showMessageDialog(NULL, tr("SignalMast address should be in the range of 1 to 2044"));
        QMessageBox::critical(0, tr("error"), tr(""));
        log->error("invalid address " + address);
        return false;
    }
#if 0
    if(DccSignalMast::isDCCAddressUsed(address)!=NULL){
        QString msg = java.text.MessageFormat.format(rb
            .getQString("DCCMastAddressAssigned"), new Object[] { dccAspectAddressField.getText(), DccSignalMast.isDCCAddressUsed(address)});
        JOptionPane.showMessageDialog(NULL, msg);
        return false;
    }
#endif
    return true;
}

QComboBox* AddSignalMastPanel::copyFromMastSelection(){
    mastSelect = new QComboBox();
    QStringList names = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSystemNameList();
    foreach(QString name, names)
    {
#if 0
        if(qobject_cast<DccSignalMast*>(((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getNamedBean(name)!= NULL) &&
            ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(name)->getSignalSystem()->getSystemName()==(sigsysname)) {
            mastSelect->addItem(((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getNamedBean(name)->getDisplayName());
        }
#endif
    }
    if(mastSelect->count()==0){
        mastSelect->setEnabled(false);
    } else {
        mastSelect->insertItem(0,"");
//        mastSelect->setCheckedIndex(0);

//        mastSelect.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                JComboBox eb = (JComboBox) e.getSource();
//                QString sourceMast = (QString)eb->currentText();
//                if(sourceMast!=NULL && !sourceMast==(""))
//                    copyFromAnotherDCCMastAspect(sourceMast);
//            }
//        });
        connect(mastSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(on_mastSelect_CurrentIndexChanged(int)));
    }
    return mastSelect;
}
void AddSignalMastPanel::on_mastSelect_CurrentIndexChanged(int)
{
    QString sourceMast = mastSelect->currentText();
    if(sourceMast!=NULL && sourceMast!=(""))
     copyFromAnotherDCCMastAspect(sourceMast);
}

void AddSignalMastPanel::copyFromAnotherDCCMastAspect(QString /*strMast*/){
#if 0
    DccSignalMast mast = (DccSignalMast)InstanceManager.signalMastManagerInstance().getNamedBean(strMast);
    for(QString aspect: dccAspect.keySet()){
        dccAspect.get(aspect).setAspectId(mast.getOutputForAppearance(aspect));
    }
#endif
}



DCCAspectPanel::DCCAspectPanel(QString aspect)
{
 this->aspect = aspect;
 panel = NULL;
 disabledCheck = new QCheckBox("Disable Aspect");
 aspectLabel = new QLabel("Set Aspect Id");
 aspectId = new JTextField(5);
 log = new Logger("DCCAspectPanel");
}

void DCCAspectPanel::setAspectDisabled(bool boo) // SLOT[]
{
 disabledCheck->setChecked(boo);
 if(boo)
 {
  aspectLabel->setEnabled(false);
  aspectId->setEnabled(false);
 }
 else
 {
  aspectLabel->setEnabled(true);
  aspectId->setEnabled(true);
 }
}

bool DCCAspectPanel::isAspectDisabled()
{
 return disabledCheck->isChecked();
}

int DCCAspectPanel::getAspectId(){
    try {
        QString value = aspectId->text();
        return (value).toInt();

    } catch (Exception ex) {
        log->error("failed to convert DCC number");
    }
    return -1;
}

void DCCAspectPanel::setAspectId(int i){
    aspectId->setText(QString::number(i));
}


QWidget* DCCAspectPanel::getPanel()
{
 if(panel==NULL)
 {
    panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    QWidget* dccDetails = new QWidget();
    dccDetails->layout()->addWidget(aspectLabel);
    dccDetails->layout()->addWidget(aspectId);
    panel->layout()->addWidget(dccDetails);
    panel->layout()->addWidget(disabledCheck);
    //TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
    QGroupBox* border = new QGroupBox();
    border->setTitle(aspect);
    panel->layout()->addWidget(border);
    //aspectId.addFocusListener(new FocusListener() {
    connect(aspectId, SIGNAL(editingFinished()), this, SLOT(editingFinished()));
//            /*public*/ void focusLost(FocusEvent e){
//                if(aspectId.getText()==("")){
//                    return;
//                }
//                if(!validateAspectId(aspectId.getText()))
//                    aspectId.requestFocusInWindow();
//            }
//            /*public*/ void focusGained(FocusEvent e){ }

//        });
    //            disabledCheck->addActionListener(new ActionListener()
    //            {
    //                /*public*/ void actionPerformed(ActionEvent* /*e*/) {
    //                    setAspectDisabled(disabledCheck->isChecked());
    //                }
    //            });
    connect(disabledCheck, SIGNAL(toggled(bool)), this, SLOT(setAspectDisabled(bool)));
  }
  return panel;
 }

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AddSignalMastPanel.class.getName());
//}


/* @(#)SensorTableAction.java */
void AddSignalMastPanel::sigSysBox_currentIndexChanged(int) // SLOT[]
{
 loadMastDefinitions();
 updateSelectedDriver();
}
