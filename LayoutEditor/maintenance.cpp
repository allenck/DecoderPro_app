#include "maintenance.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "logger.h"
#include "proxyturnoutmanager.h"
#include "jdialog.h"
#include <QVBoxLayout>
//#include "jtextarea.h"
#include "defaultsignalmastmanager.h"
#include "defaultconditionalmanager.h"
#include "defaultmemorymanager.h"
#include "abstractsignalheadmanager.h"
#include "abstractlightmanager.h"
#include "abstractsensor.h"
#include "defaultconditional.h"
#include "defaultlogix.h"
#include "defaultconditionalmanager.h"
#include "conditionalvariable.h"
#include "jlist.h"
#include "conditionalaction.h"
#include "picklistmodel.h"
#include "abstractsignalhead.h"
#include <QScrollArea>
#include <QTextEdit>
#include "sectionmanager.h"
#include "layoutblockmanager.h"
#include "routemanager.h"
#include "defaultroutemanager.h"
#include "defaultroute.h"
#include "transitmanager.h"
#include "transit.h"
#include "transitsection.h"
#include "blockbosslogic.h"
#include "defaultconditionalaction.h"
#include "panelmenu.h"
#include "turnouticon.h"
#include "defaultlogixmanager.h"
#include "indicatortrackicon.h"
#include "oblock.h"
#include "indicatorturnouticon.h"
#include "multisensoricon.h"
#include "namedbean.h"

Maintenance::Maintenance(QObject *parent) :
    QObject(parent)
{
}
/**
 * A collection of static utilities to provide cross referencing information
 * among the various PanelPro objects.  Most likely, this is incomplete as
 * there still may be references held by objects unknown to the author.  It is
 * intended to inform users where and how the various elements are used.  In
 * particular to identify useless elements ('orphans').  Currently, called only
 * from the Logix JFrame, which is probably not its ultimate UI.
 *<P>
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
 * <P>
 * @author  Pete Cressman   Copyright 2009
 * @version $Revision: 17977 $
 */

///*public*/ class Maintenance
//{
//	static final ResourceBundle rbm = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.MaintenanceBundle");

/**
*  Find references of a System or User name in the various Manager Objects
*/
/*public*/ /*static*/ void Maintenance::deviceReportPressed(QString devName, QWidget* parent)
{
    QTextEdit* text = NULL;
    QScrollArea* scrollPane = NULL;
    text = new QTextEdit(); //new javax.swing.JTextArea(25, 50);
    text->setReadOnly(true);
    text->setTabStopWidth(4);
    search(devName, text);
    scrollPane = new QScrollArea();
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(scrollPane->sizePolicy().hasHeightForWidth());
    scrollPane->setSizePolicy(sizePolicy);
    scrollPane->setWidget(text);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
    text->setSizePolicy(sizePolicy1);
    makeDialog(scrollPane, NULL, parent, tr("Cross References"));
}

/**
*  Find orphaned elements in the various Manager Objects
*/
/*public*/ /*static*/ void Maintenance::findOrphansPressed(QWidget* parent)
{
 QVector <QString>* display = new QVector<QString>();
 QVector <QString>* names = new QVector<QString>();

 QStringListIterator iter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL) && name!=("ISCLOCKRUNNING"))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
//                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }
 iter = QStringListIterator(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
   //                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }
 iter = QStringListIterator(static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
 //                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }
 iter = QStringListIterator(((AbstractLightManager*)InstanceManager::lightManagerInstance())->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
 //                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }
 iter = QStringListIterator(static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
 //                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }

    iter = QStringListIterator(((SectionManager*)InstanceManager::getDefault("SectionManager"))->getSystemNameList());
    while (iter.hasNext()) {
        QString name = iter.next();
        if (!search(name, NULL)) {
            display->append(tr("%1: \"%2\" (%3)").arg(getTypeAndNames(name).at(0)).arg(getTypeAndNames(name).at(1)).arg(getTypeAndNames(name).at(2)));
            names->append( name);
        }
    }

 iter = QStringListIterator(((BlockManager*)InstanceManager::getDefault("BlockManager"))->getSystemNameList());
 while (iter.hasNext())
 {
  QString name = iter.next();
  if (!search(name, NULL))
  {
   QStringList l = getTypeAndNames(name);
   display->append(tr("%1: \"%2\" (%3)").arg(l.at(0)).arg(l.at(1)).arg(l.at(2)));
   //                                                       (Object[])getTypeAndNames(name)));
   names->append( name);
  }
 }

 MDefaultListModel* listModel = new MDefaultListModel(display);
//    for (int i=0; i<display.size(); i++)  {
//        listModel.addElement(display.get(i));
//    }
 JList* list = new JList(listModel);
 list->setSelectionMode(QAbstractItemView::SingleSelection);

 QPushButton* button = new QPushButton(tr("Delete"));
 button->setToolTip(tr("Select an item from the list to delete and press button"));
#if 0
    class SearchListener implements ActionListener {
         JList l;
         Vector<String> n;
         SearchListener(JList list, Vector<String> name) {
             l = list;
             n = name;
         }
         /*public*/ void actionPerformed(ActionEvent e) {
             int index = l.getMaxSelectionIndex();
             if (index < 0)  {
                 javax.swing.JOptionPane.showMessageDialog(NULL,
                         rbm.getString("OrphanDeleteHint"),
                         rbm.getString("DeleteTitle"),
                         javax.swing.JOptionPane.INFORMATION_MESSAGE);
                 return;
             }
             int min =l.getMinSelectionIndex();
             DefaultListModel model = (DefaultListModel)l.getModel();
             while (index>=min) {
                 String[] names = getTypeAndNames(n.get(index));
                 if (names[0]==("Sensor")) {
                     Sensor s = InstanceManager::sensorManagerInstance().getBySystemName(names[2]);
                     if (s == NULL) {
                         s = InstanceManager::sensorManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::sensorManagerInstance().deregister(s);
                 } else if (names[0]==("Turnout"))  {
                     Turnout t = InstanceManager::turnoutManagerInstance().getBySystemName(names[2]);
                     if (t == NULL) {
                         t = InstanceManager::turnoutManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::turnoutManagerInstance().deregister(t);
                 } else if (names[0]==("SignalHead"))  {
                     SignalHead sh = InstanceManager::signalHeadManagerInstance().getBySystemName(names[2]);
                     if (sh == NULL) {
                         sh = InstanceManager::signalHeadManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::signalHeadManagerInstance().deregister(sh);
                 } else if (names[0]==("Light"))  {
                     Light l = InstanceManager::lightManagerInstance().getBySystemName(names[2]);
                     if (l == NULL) {
                         l = InstanceManager::lightManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::lightManagerInstance().deregister(l);
                 } else if (names[0]==("Conditional"))  {
                     Conditional c = InstanceManager::conditionalManagerInstance().getBySystemName(names[2]);
                     if (c == NULL) {
                         c = InstanceManager::conditionalManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::conditionalManagerInstance().deregister(c);
                 } else if (names[0]==("Section"))  {
                     jmri.Section sec = InstanceManager::sectionManagerInstance().getBySystemName(names[2]);
                     if (sec == NULL) {
                         sec = InstanceManager::sectionManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::sectionManagerInstance().deregister(sec);
                 } else if (names[0]==("Block"))  {
                     jmri.Block b = InstanceManager::blockManagerInstance().getBySystemName(names[2]);
                     if (b == NULL) {
                         b = InstanceManager::blockManagerInstance().getBySystemName(names[1]);
                     }
                     InstanceManager::blockManagerInstance().deregister(b);
                 }
                 model.remove(index);
                 n.remove(index);
                 index--;
             }
             index++;
             if (index >= model.getSize()) {
                 index = model.getSize()-1;
             }
             if (index >= 0) {
                 l.setSelectedIndex(index);
             }
         }
    }
#endif
    //JScrollPane scrollPane = new JScrollPane(list);
//    QWidget* scrollPane = new QWidget();
//    scrollPane->setLayout(new QVBoxLayout());
//    scrollPane->layout()->addWidget(list);
    //button.addActionListener(new SearchListener(list, names));
    //button.setMaximumSize(button.getPreferredSize());
    makeDialog(list, button, parent, tr("Orphaned Items"));
}

/**
*  Find useless conditionals in the various Manager Objects
*/
/*public*/ /*static*/ void Maintenance::findEmptyPressed(QWidget* parent)
{
 Logger* log = new Logger("Maintenance");
 QVector <QString>* display = new QVector<QString>();
 QVector <QString>* names = new QVector<QString>();

 log->debug("findEmptyPressed");
 QStringListIterator iter(static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->getSystemNameList());
 ConditionalManager* cm = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"));
 while (iter.hasNext())
 {
  QString name = iter.next();
  Conditional* c = ((DefaultConditionalManager*)cm)->getBySystemName(name);
  if (c != NULL)
  {
   QList <ConditionalVariable*>* variableList = ((DefaultConditional*)c)->getCopyOfStateVariables();
   if (variableList->size()==0)
   {
    QString userName = ((DefaultConditional*)c)->getUserName();
    display->append(tr("%1: \"%2\" (%3)").arg("Conditional").arg(userName).arg(name));
    names->append( name);
   }
  }
 }
 MDefaultListModel* listModel = new MDefaultListModel(display);
//    for (int i=0; i<display.size(); i++)  {
//        listModel.addElement(display.get(i));
//    }
 QListView* list = new QListView();
 list->setModel(listModel);
 list->setSelectionMode(QAbstractItemView::SingleSelection);


 QPushButton* button = new QPushButton(tr("Delete"));
 button->setToolTip(tr("Select an item from the list to delete and press button"));
#if 0
    class EmptyListener implements ActionListener {
         JList l;
         Vector<String> n;
         EmptyListener(JList list, Vector<String> name) {
             l = list;
             n = name;
         }
         /*public*/ void actionPerformed(ActionEvent e) {
             int index = l.getMaxSelectionIndex();
             if (index < 0)  {
                 javax.swing.JOptionPane.showMessageDialog(NULL,
                         rbm.getString("OrphanDeleteHint"),
                         rbm.getString("DeleteTitle"),
                         javax.swing.JOptionPane.INFORMATION_MESSAGE);
                 return;
             }
             int min =l.getMinSelectionIndex();
             DefaultListModel model = (DefaultListModel)l.getModel();
             while (index>=min) {
                 String[] names = getTypeAndNames(n.get(index));
                 model.remove(index);
                 Conditional c = InstanceManager::conditionalManagerInstance().getBySystemName(names[2]);
                 if (c != NULL) {
                     Logix x = InstanceManager::conditionalManagerInstance().getParentLogix(names[2]);
                     if (x != NULL) {
                         x.deActivateLogix();
                         x.deleteConditional(names[2]);
                         x.activateLogix();
                     }
                     InstanceManager::conditionalManagerInstance().deregister(c);
                     n.remove(index);
                     index--;
                 }
             }
             index++;
             if (index >= model.getSize()) {
                 index = model.getSize()-1;
             }
             if (index >= 0) {
                 l.setSelectedIndex(index);
             }
         }
    }
#endif
    QWidget* scrollPane = new QWidget();
    scrollPane->setLayout(new QVBoxLayout());
    scrollPane->layout()->addWidget(list);
//    button.addActionListener(new EmptyListener(list, names));
//    button.setMaximumSize(button.getPreferredSize());
    makeDialog(scrollPane, button, parent, tr("Useless Conditionals"));
}

/**
*  Find type of element and its names from a name that may be a user name
* or a system name.   (Maybe this can be done at a generic manager level, but there
* seem to be two kinds of implemetation of Managers and I don't know the which is the
* preferred kind or why they need to be different.)
*
* Searches each Manager for a reference to the "name"
* returns 4 element String: {Type, userName, sysName, numListeners}
*/
//@SuppressWarnings("NULL")
/*static*/ QStringList Maintenance::getTypeAndNames(QString name)
{
 Logger* log = new Logger("Maintenance");
 QString userName = name.trimmed();
 QString sysName = userName;
//        String sysName = userName.toUpper();
 bool found = false;
 if (log->isDebugEnabled()) log->debug("getTypeAndNames for \""+name+"\"");

 SensorManager* sensorManager = InstanceManager::sensorManagerInstance();
 Sensor* sen = ((ProxySensorManager*)sensorManager)->getBySystemName(sysName);
 if ( sen!=NULL )
 {
  userName = ((AbstractSensor*)sen)->getUserName();
  found = true;
 }
 else
 {
  sen = ((ProxySensorManager*)sensorManager)->getBySystemName(userName.toUpper());
  if (sen!=NULL)
  {
   sysName = ((AbstractSensor*)sen)->getSystemName();
   userName = ((AbstractSensor*)sen)->getUserName();
   found = true;
  }
  else
  {
   sen = ((ProxySensorManager*)sensorManager)->getByUserName(userName);
   if ( sen!=NULL )
   {
    sysName = ((AbstractSensor*)sen)->getSystemName();
    found = true;
   }
  }
 }
 if (found)
 {
  QStringList l = QStringList();
  l << "Sensor" <<  userName << sysName <<
                              QString::number(((AbstractSensor*)sen)->getNumPropertyChangeListeners());
  return l;
 }
 TurnoutManager* turnoutManager = InstanceManager::turnoutManagerInstance();
 Turnout* t = (Turnout*)((ProxyTurnoutManager*)turnoutManager)->getBySystemName(sysName);
 if ( t!=NULL )
 {
  userName = ((AbstractTurnout*)t)->getUserName();
  found = true;
 }
 else
 {
  t = (Turnout*)((ProxyTurnoutManager*)turnoutManager)->getBySystemName(userName.toUpper());
  if (t!=NULL)
  {
   sysName = ((AbstractTurnout*)t)->getSystemName();
   userName = ((AbstractTurnout*)t)->getUserName();
   found = true;
  }
  else
  {
   t = (Turnout*)((ProxyTurnoutManager*)turnoutManager)->getByUserName(userName);
   if ( t!=NULL )
   {
    sysName = ((AbstractTurnout*)t)->getSystemName();
    found = true;
   }
  }
 }
 if (found)
 {
// return (new String[] {"Turnout", userName, sysName,
//                      Integer.toString(t.getNumPropertyChangeListeners())});
  QStringList l = QStringList() << "Turnout" << userName << sysName << QString::number(((AbstractTurnout*)t)->getNumPropertyChangeListeners());
  return l;
 }

 LightManager* lightManager = InstanceManager::lightManagerInstance();
 Light* l =(Light*) ((AbstractLightManager*)lightManager)->getBySystemName(sysName);
 if ( l!=NULL )
 {
   userName = l->getUserName();
   found = true;
 }
 else
 {
   l = (Light*)((AbstractLightManager*)lightManager)->getBySystemName(userName.toUpper());
   if (l!=NULL)
   {
    sysName = ((AbstractLight*)l)->getSystemName();
    userName = ((AbstractLight*)l)->getUserName();
    found = true;
   }
   else
   {
    l = (Light*)((AbstractLightManager*)lightManager)->getByUserName(userName);
    if ( l!=NULL )
    {
     sysName = l->getSystemName();
     found = true;
    }
   }
 }
 if (found)
 {
//        return (new String[] {"Light", userName, sysName,
//                              Integer.toString(l.getNumPropertyChangeListeners())});
  QStringList list = QStringList() << "Light"<< userName << sysName << QString::number(((AbstractLight*)l)->getNumPropertyChangeListeners());
  return list;
 }

 SignalHeadManager* signalManager = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
 SignalHead* sh =(SignalHead*) ((AbstractSignalHeadManager*)signalManager)->getBySystemName(sysName);
 if ( sh!=NULL )
 {
  userName = ((AbstractSignalHead*)sh)->getUserName();
  found = true;
 }
 else
 {
  sh = (SignalHead*)((AbstractSignalHeadManager*)signalManager)->getBySystemName(userName.toUpper());
  if (sh!=NULL)
  {
   sysName = ((AbstractSignalHead*)sh)->getSystemName();
   userName = ((AbstractSignalHead*)sh)->getUserName();
   found = true;
  }
  else
  {
   sh = (SignalHead*)((AbstractSignalHeadManager*)signalManager)->getByUserName(userName);
   if ( sh!=NULL )
   {
    sysName = ((AbstractSignalHead*)sh)->getSystemName();
    found = true;
   }
  }
 }
 if (found)
 {
//        return (new String[] {"SignalHead", userName, sysName,
//                              Integer.toString(sh.getNumPropertyChangeListeners())});
  QStringList list = QStringList() << "SignalHead"<< userName << sysName << QString::number(((AbstractSignalHead*)sh)->getNumPropertyChangeListeners());
  return list;
 }

 ConditionalManager* cm = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"));
 Conditional* c = ((DefaultConditionalManager*)cm)->getBySystemName(sysName);
 if ( c!=NULL )
 {
  userName = ((DefaultConditional*)c)->getUserName();
  found = true;
 }
 else
 {
  c = ((DefaultConditionalManager*)cm)->getBySystemName(userName.toUpper());
  if (c!=NULL)
  {
   sysName = ((DefaultConditional*)c)->getSystemName();
   userName = ((DefaultConditional*)c)->getUserName();
   found = true;
  }
  else
  {
   c = ((DefaultConditionalManager*)cm)->getByUserName(userName);
   if ( c!=NULL )
   {
    sysName = ((DefaultConditional*)c)->getSystemName();
    found = true;
   }
  }
 }
 if (found)
 {
//  return (new String[] {"Conditional", userName, sysName,
//                              Integer.toString(c.getNumPropertyChangeListeners())});
  QStringList l = QStringList() << "Conditional" << userName << sysName << QString::number(((DefaultConditional*)c)->getNumPropertyChangeListeners());
  return l;
 }

 BlockManager* blockManager = ((BlockManager*)InstanceManager::getDefault("BlockManager"));
 Block* b = (Block*)blockManager->getBySystemName(sysName);
 if ( b!=NULL )
 {
  userName = b->getUserName();
  found = true;
 }
 else
 {
  b = (Block*)blockManager->getBySystemName(userName.toUpper());
  if (b!=NULL)
  {
   sysName = b->getSystemName();
   userName = b->getUserName();
   found = true;
  }
  else
  {
   b = (Block*)blockManager->getByUserName(userName);
   if ( b!=NULL )
   {
    sysName = b->getSystemName();
        found = true;
    }
   }
  }
  if (found)
  {
//        return (new String[] {"Block", userName, sysName,
//                              Integer.toString(b.getNumPropertyChangeListeners())});
   QStringList list = QStringList() << "Block"<< userName << sysName << QString::number(((Block*)b)->getNumPropertyChangeListeners());
   return list;
  }

    SectionManager* sectionManager = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
    Section* sec = (Section*)sectionManager->getBySystemName(sysName);
    if ( sec!=NULL ) {
        userName = sec->getUserName();
        found = true;
    } else {
        sec = (Section*)sectionManager->getBySystemName(userName.toUpper());
        if (sec!=NULL) {
            sysName = sec->getSystemName();
            userName = sec->getUserName();
            found = true;
        } else {
            sec = (Section*)sectionManager->getByUserName(userName);
            if ( sec!=NULL ) {
                sysName = sec->getSystemName();
                found = true;
            }
        }
    }
    if (found) {
        return (QStringList()<< "Block" << userName << sysName <<
                              QString::number(sec->getNumPropertyChangeListeners()));
    }
    log->warn(" No type found for "+userName+" ("+sysName+").");
#if 0
    jmri.jmrit.logix.OBlockManager oBlockManager = InstanceManager::oBlockManagerInstance();
    jmri.jmrit.logix.OBlock blk = oBlockManager.getBySystemName(sysName);
    if ( sec!=NULL ) {
        userName = blk.getUserName();
        found = true;
    } else {
        blk = oBlockManager.getBySystemName(userName.toUpper());
        if (blk!=NULL) {
            sysName = blk.getSystemName();
            userName = blk.getUserName();
            found = true;
        } else {
            blk = oBlockManager.getByUserName(userName);
            if ( blk!=NULL ) {
                sysName = blk.getSystemName();
                found = true;
            }
        }
    }
    if (found) {
        return (new String[] {"OBlock", userName, sysName,
                              Integer.toString(blk.getNumPropertyChangeListeners())});
 }
 log->warn(" No type found for "+userName+" ("+sysName+").");
#endif

 //return (new String[] {"", userName, sysName, "0"});
 QStringList lst = QStringList() << "" << userName << sysName <<"0";
 return lst;
}

/*static*/ bool Maintenance::testName(QString name, bool found, QStringList names, QString line1, QString line2,
                        QString line, QString tempText)
{
    if (name==NULL) {
        return false;
    }
    QString sysName = names.at(2);
    QString userName = names.at(1);
    if (name==(sysName) || name==(userName))
    {
        if (!found) {
            if (line1!="") {
                tempText.append(line1);
            }
            if (line2!="") {
                tempText.append(line2);
            }
        }
        tempText.append(line);
        return true;
    }
    return false;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*static*/ bool Maintenance::search(QString name, /*JTextArea*/QTextEdit* text)
{
 Logger* log = new Logger("Maintenance");

 QStringList names = getTypeAndNames(name);
 if (log->isDebugEnabled()) log->debug("search for "+name+" as "+names.at(0)+" \""+names.at(1)+"\" ("+names.at(2)+")");
 if (names.at(0).length() == 0)
 {
  if (text != NULL)
  {
      text->append(tr("\"%1\" (%2) not found to be a name for a\nSensor, Turnout, Light, Signal, Conditional, Block, Section or OBlock.\n").arg(names.at(0)).arg(names.at(1)));
   return false;
  }
 }
 if (text != NULL)
 {
  text->append(tr("Looking for references to %1: \"%2\" (%3) in the following:").arg(names.at(0)).arg(names.at(1)).arg(names.at(2)));
 }
 QString sysName = names.at(2);
 QString userName = names.at(1);
 int referenceCount = 0;
 QString tempText =  QString();
 bool found = false;
 bool empty = true;
 // search for references among each class known to be listeners
 QStringListIterator iter1(static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getSystemNameList());
 while (iter1.hasNext())
 {
  // get the next Logix
  QString sName = iter1.next();
  Logix* x =(Logix*) static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getBySystemName(sName);
  if (x==NULL)
  {
   log->error("Error getting Logix  - " + sName);
   break;
  }
  tempText =  QString();
  QString uName = ((DefaultLogix*)x)->getUserName();
  QString line1 =tr("%1%2: \"%3\" (%4)").arg("").arg( tr("Logix")).arg( uName).arg( sName);
  for (int i=0; i<((DefaultLogix*)x)->getNumConditionals(); i++)
  {
   sName = ((DefaultLogix*)x)->getConditionalByNumberOrder(i);
   if (sName == NULL)
   {
    log->error("Null conditional system name");
    break;
   }
   Conditional* c = ((DefaultConditionalManager*)static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager")))->getBySystemName(sName);
   if (c == NULL)
   {
    log->error("Invalid conditional system name - " + sName);
    break;
   }
   uName = ((DefaultConditional*)c)->getUserName();
   QString line2 = tr("%1%2: \"%3\" (%4)").arg("").arg( tr("Conditional")).arg( uName).arg( sName);
   QString line = tr("%1Conditional Reference found.").arg("\t");
   if (sysName==(sName) || (userName!=NULL && userName.length()>0 && userName==(uName)) )
   {
    if (testName(sysName, found, names, line1, NULL, line, tempText))
    {
     found = true;
     referenceCount++;
    }
   }
   QList <ConditionalVariable*>* variableList = ((DefaultConditional*)c)->getCopyOfStateVariables();
   for (int k=0; k<variableList->size(); k++)
   {
    ConditionalVariable* v = variableList->at(k);
    line = tr("%1Tested as a StateVariable for: %2 %3").arg("\t\t").arg(v->getTestTypeString()).arg( v->getDataString());
    if (testName(v->getName(), found, names, line1, line2, line, tempText))
    {
     found = true;
     referenceCount++;
    }
   }
   QList <ConditionalAction*>* actionList = ((DefaultConditional*)c)->getCopyOfActions();
   for (int k=0; k<actionList->size(); k++)
   {
    ConditionalAction* a = actionList->at(k);
    line = tr("%1Set as an Action for: %2, %3 %4").arg("\t\t").arg(a->getTypeString()).arg( a->getOptionString(false)).arg( a->getActionDataString());
    if (testName(a->getDeviceName(), found, names, line1, line2, line, tempText))
    {
     found = true;
     referenceCount++;
    }
   }
   if (text != NULL && found)
   {
    text->append(tempText);
    tempText = "";
        found = false;
        empty = false;
        line1 = "";
   }
  }
  if (text != NULL && found)
  {
   text->append(tempText);
   tempText = "";
   found = false;
   empty = false;
  }
 }
 if (text != NULL)
 {
  if (empty)
  {
      text->append(tr("No references found in %1.").arg("Logix"));
  }
  else
  {
   text->append("\n");
  }
 }
#if 0
    tempText = new StringBuffer();
    found = false;
    empty = true;
    jmri.jmrit.logix.OBlockManager oBlockManager = InstanceManager::oBlockManagerInstance();
    iter1 = oBlockManager.getSystemNameList().iterator();
    while (iter1.hasNext()) {
        // get the next Logix
        String sName = iter1.next();
        jmri.jmrit.logix.OBlock block = oBlockManager.getBySystemName(sName);
        String uName = block.getUserName();
        String line1 = tr("%1%2: \"%3\" (%4)\n"),
                        new Object[] { " ", rbm.getString("OBlock"), uName,  sName});
        Sensor sensor = block.getSensor();
        if (sensor != NULL) {
            String line = tr("OBlockSensor").arg("\t");
            if (testName(sensor.getSystemName(), found, names, line1, NULL, line, tempText)) {
                found = true;
                referenceCount++;
            }
        }
        if (text != NULL && found) {
            text.append(tempText.toString());
            tempText = new StringBuffer();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text.append(tr("NoReference"), "OBlock"));
        } else {
            text.append("\n");
        }
    }
#endif
    tempText = QString();
    found = false;
    empty = true;
    RouteManager* routeManager = (RouteManager*)InstanceManager::getDefault("RouteManager");
    iter1 = QStringListIterator(((DefaultRouteManager*)routeManager)->getSystemNameList());
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        Route* r = (Route*)((DefaultRouteManager*)routeManager)->getBySystemName(sName);
        if (r==NULL) {
            log->error("Error getting Route  - "+sName);
            break;
        }
        QString uName = ((DefaultRoute*)r)->getUserName();
        QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg(tr("Route")).arg(uName).arg(sName);
        for (int i=0; i<Route::MAX_CONTROL_SENSORS; i++)
        {
            QString line = tr("Used as a Control %1\n").arg(tr("Sensor"));
            if (testName(((DefaultRoute*)r)->getRouteSensorName(i), found, names, line1, NULL, line, tempText)) {
                found = true;
                referenceCount++;
            }
        }
        QString line = tr("TurnoutsAlignedSensor").arg(tr("Sensor"));
        if (testName(((DefaultRoute*)r)->getTurnoutsAlignedSensor(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("Used as a Control %1\n").arg(tr("Turnout"));
        if (testName(((DefaultRoute*)r)->getControlTurnout(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("LockControlTurnout").arg(tr("Turnout"));
        if (testName(((DefaultRoute*)r)->getLockControlTurnout(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        for (int i=0; i<((DefaultRoute*)r)->getNumOutputTurnouts(); i++)
        {
            line = tr("	Used as an Output %1\n").arg(tr("Turnout"));
            if (testName(((DefaultRoute*)r)->getOutputTurnoutByIndex(i), found, names, line1, NULL, line, tempText)) {
                found = true;
                referenceCount++;
            }
        }
        for (int i=0; i<((DefaultRoute*)r)->getNumOutputSensors(); i++)
        {
            line = tr("Used as an Output %1\n").arg(tr("Sensor"));
            if (testName(((DefaultRoute*)r)->getOutputSensorByIndex(i), found, names, line1, NULL, line, tempText)) {
                found = true;
                referenceCount++;
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1.\n").arg("Route"));
        } else {
            text->append("\n");
        }
    }

    tempText = QString();
    found = false;
    empty = true;
    TransitManager*     transitManager = (TransitManager*)InstanceManager::getNullableDefault("TransitManager");

    iter1 = QStringListIterator(transitManager->getSystemNameList());
    while (iter1.hasNext())
    {
     // get the next Logix
     QString sName = iter1.next();
     Transit* transit = transitManager->getBySystemName(sName);
     if (transit==NULL)
     {
      log->error("Error getting Transit - "+sName);
      break;
     }
     QString uName = transit->getUserName();
     QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg(tr("Transit")).arg(uName).arg(sName);
     QList<TransitSection*>* sectionList = transit->getTransitSectionList();
        for (int i=0; i<sectionList->size(); i++) {
            TransitSection* transitSection = sectionList->at(i);
            Section* section = transitSection->getSection();
            uName = section->getUserName();
            sName = section->getSystemName();
            QString line2 = tr("%1%2: \"%3\" (%4)\n").arg("\t").arg(tr("Transit Section")).arg(uName).arg(sName);
            if (sName==(sysName) || uName==(userName))  {
                tempText.append(line1);
                tempText.append(line2);
                tempText.append(tr("%1Section Reference found.\n").arg("\t\t"));
                found = true;
                referenceCount++;
            }
            QString line = tr("%1Used as a Forward Blocking Sensor\n").arg("\t\t");
            if (testName(section->getForwardBlockingSensorName(), found, names, line1, line2, line, tempText)) {
                found = true;
                referenceCount++;
            }
            line = tr("%1Used as a Forward Stopping Sensor\n").arg("\t\t");
            if (testName(section->getForwardStoppingSensorName(), found, names, line1, line2, line, tempText)) {
                found = true;
                referenceCount++;
            }
            line = tr("%1Used as a Reverse Blocking Sensor\n").arg("\t\t");
            if (testName(section->getReverseBlockingSensorName(), found, names, line1, line2, line, tempText)) {
                found = true;
                referenceCount++;
            }
            line = tr("%1Used as a Reverse Stopping Sensor\n").arg("\t\t");
            if (testName(section->getReverseStoppingSensorName(), found, names, line1, line2, line, tempText)) {
                found = true;
                referenceCount++;
            }
            QVector<Block*>* blockList = section->getBlockList();

            for (int k=0; k<blockList->size(); k++) {
                Block* block = blockList->at(k);
                sName = block->getSystemName();
                uName = block->getUserName();
                tempText.append(tr("%1%2: \"%3\" (%4)\n").arg("\t\t").arg(tr("Block")).arg(uName).arg(sName));
                if (sName==(sysName) || uName==(userName))  {
                    tempText.append(tr("%1Block Reference found.\n").arg("\t\t"));
                    found = true;
                    referenceCount++;
                }
                Sensor* sensor = block->getSensor();
                if (sensor != NULL) {
                    line = tr("%1Used as the Block Sensor\n").arg("\t\t");
                    if (testName(sensor->getSystemName(), found, names, line1, line2, line, tempText)) {
                        found = true;
                        referenceCount++;
                    }
                }
            }
            if (text != NULL && found) {
                text->append(tempText);
                tempText = QString();
                found = false;
                empty = false;
                line1 = "";
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1.\n").arg("Transit"));
        } else {
            text->append("\n");
        }
    }

//        if (text != NULL) {
//            text.append(rbm.getString("NestMessage"));
//        }
    tempText = QString();
    found = false;
    empty = true;
    SectionManager* sectionManager = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
    QStringList sysNameList = sectionManager->getSystemNameList();

    transitManager = (TransitManager*)InstanceManager::getNullableDefault("TransitManager");
    iter1 = QStringListIterator(transitManager->getSystemNameList());
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        Transit* transit = transitManager->getBySystemName(sName);
        if (transit!=NULL) {
            QList<TransitSection*>* sectionList = transit->getTransitSectionList();
            for (int i=0; i<sectionList->size(); i++) {
                TransitSection* transitSection = sectionList->at(i);
                Section* section = transitSection->getSection();
                sysNameList.removeAt(sysNameList.indexOf(section->getSystemName()));
            }
        }
    }
    iter1 = QStringListIterator(sysNameList);
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        Section* section = (Section*)sectionManager->getBySystemName(sName);
        if (section==NULL) {
            log->error("Error getting Section - "+sName);
            break;
        }
        QString uName = section->getUserName();
        QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg(tr("Section")).arg(uName).arg(sName);
        if (sName==(sysName) || uName==(userName))  {
            tempText.append(tr("%1Section Reference found.\n").arg("\t"));

            found = true;
            referenceCount++;
        }
        QString line = tr("%1Used as a Forward Blocking Sensor\n").arg("\t");
        if (testName(section->getForwardBlockingSensorName(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Forward Stopping Sensor\n").arg("\t");
        if (testName(section->getForwardStoppingSensorName(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Reverse Blocking Sensor\n").arg("\t");
        if (testName(section->getReverseBlockingSensorName(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Reverse Stopping Sensor\n").arg("\t");
        if (testName(section->getReverseStoppingSensorName(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }

        QVector<Block*>* blockList = section->getBlockList();
        for (int k=0; k<blockList->size(); k++) {
            Block* block = blockList->at(k);
            sName = block->getSystemName();
            uName = block->getUserName();
            QString line2 = tr("%1%2: \"%3\" (%4)\n").arg("\t").arg(tr("Block")).arg(uName).arg(sName);
            if (sName==(sysName) || (uName!= NULL && uName==(userName)))  {
                tempText.append(line2);
                tempText.append(tr("%1Block Reference found.\n").arg("\t"));
                found = true;
                referenceCount++;
            }
            Sensor* sensor = block->getSensor();
            if (sensor != NULL) {
                line = tr("%1Used as the Block Sensor\n").arg("\t\t");
                if (testName(sensor->getSystemName(), found, names, line1, line2, line, tempText)) {
                    found = true;
                    referenceCount++;
                }
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1.\n").arg("Section"));
        } else {
            text->append("\n");
        }
    }

    tempText = QString();
    found = false;
    empty = true;
    BlockManager* blockManager = ((BlockManager*)InstanceManager::getDefault("BlockManager"));
    sysNameList = blockManager->getSystemNameList();

    sectionManager = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
    iter1 = QStringListIterator(sectionManager->getSystemNameList());
    while (iter1.hasNext()) {
        QString sName = iter1.next();
        Section* section = (Section*)sectionManager->getBySystemName(sName);
        if (section!=NULL) {
            //sysNameList.removeAt(sysNameList.indexOf(section->getBlockList()));
            sysNameList.removeAt(sysNameList.indexOf(sName));
        }
    }
    iter1 = QStringListIterator(sysNameList);
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        Block* b = (Block*)blockManager->getBySystemName(sName);
        QString uName = b->getUserName();
        QString line1 = tr("%1%2: \"%3\" (%4)").arg(" ").arg(tr("Block")).arg(uName).arg(sName);
        if (sName==(sysName) || (uName !=NULL && uName==(userName)))  {
            tempText.append(line1);
            tempText.append(tr("%1Block Reference found.\n").arg("\t"));
            found = true;
            referenceCount++;
        }
        Sensor* s = b->getSensor();
        if (s != NULL) {
            QString line = tr("BlockSensor").arg("\t\t");
            if (testName(((AbstractSensor*)s)->getSystemName(), found, names, line1, NULL, line, tempText))
            {
                found = true;
                referenceCount++;
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1.\n").arg("Block"));
        } else {
            text->append("\n");
        }
    }

    tempText = QString();
    found = false;
    empty = true;
    LayoutBlockManager* lbm = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"));
    iter1 = QStringListIterator(lbm->getSystemNameList());
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        LayoutBlock* lb = (LayoutBlock*)lbm->getBySystemName(sName);
        if (lb==NULL) {
            log->error("Error getting LayoutBlock - "+sName);
            break;
        }
        QString uName = lb->getUserName();
        QString line1 = tr("%1%2: \"%3\" (%4)").arg(" ").arg(tr("Layout Block")).arg(uName).arg( sName);
        Sensor* s = lb->getOccupancySensor();
        if (s != NULL) {
            QString line = tr("%1Used as the Layout Block Occupancy Sensor\n").arg("\t\t");
            if (testName(((AbstractSensor*)s)->getSystemName(), found, names, line1, NULL, line, tempText)) {
                found = true;
                referenceCount++;
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("	No references found in %1.\n").arg("Layout Block"));
        } else {
            text->append("\n");
        }
    }

    tempText = QString();
    found = false;
    empty = true;
    QListIterator<BlockBossLogic*> enumeration( BlockBossLogic::entries());
    while (enumeration.hasNext())
    {
        // get the next Logix
        BlockBossLogic* bbl = enumeration.next();
        QString sName = bbl->getName();
        QString uName = bbl->getDrivenSignal();
        QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg(tr("Block Boss Logic")).arg(uName).arg(sName);
        if (uName==(sysName) || uName==(userName) || sName==(sysName) || sName==(userName)) {
            tempText.append(line1);
            tempText.append(tr("%1Used as the Driven Signal\n                               ").arg("\t"));
            found = true;
            referenceCount++;
        }
        QString line = tr("%1Used as a Watch Sensor\n").arg("1\t");
        if (testName(bbl->getSensor1(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("2\t");
        if (testName(bbl->getSensor2(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("3\t");
        if (testName(bbl->getSensor3(), found, names, line1, NULL, line, tempText)) {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("4\t");
        if (testName(bbl->getSensor4(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("5\t");
        if (testName(bbl->getSensor5(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as the Monitored Turnout\n").arg("\t");
        if (testName(bbl->getTurnout(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as the Monitored Signal\n").arg("1\t");
        if (testName(bbl->getWatchedSignal1(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as the Monitored Turnout\n").arg("1Alt\t");
        if (testName(bbl->getWatchedSignal1Alt(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as the Monitored Turnout\n").arg("2\t");
        if (testName(bbl->getWatchedSignal2(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as the Monitored Turnout\n").arg("2Alt\t");
        if (testName(bbl->getWatchedSignal2Alt(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("1\t");
        if (testName(bbl->getWatchedSensor1(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("1Alt\t");
        if (testName(bbl->getWatchedSensor1Alt(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor\n").arg("2\t");
        if (testName(bbl->getWatchedSensor2(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        line = tr("%1Used as a Watch Sensor/n").arg("2Alt\t");
        if (testName(bbl->getWatchedSensor2Alt(), found, names, line1, NULL, line, tempText))
        {
            found = true;
            referenceCount++;
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText = QString();
            found = false;
            empty = false;
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1\n").arg("Block Boss Logic"));
        } else {
            text->append("\n");
        }
    }

    tempText = QString();
    found = false;
    empty = true;
    ConditionalManager* conditionalManager = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"));
    sysNameList = conditionalManager->getSystemNameList();

    iter1 = QStringListIterator(static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getSystemNameList());
    while (iter1.hasNext()) {
        QString sName = iter1.next();
        Logix* x =(Logix*)static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getBySystemName(sName);
        for (int i=0; i<((DefaultLogix*)x)->getNumConditionals(); i++)  {
            sName = ((DefaultLogix*)x)->getConditionalByNumberOrder(i);
            sysNameList.removeAt(sysNameList.indexOf(sName));
        }
    }
    iter1 = QStringListIterator(sysNameList);
    while (iter1.hasNext()) {
        // get the next Logix
        QString sName = iter1.next();
        Conditional* c =((DefaultConditionalManager*) conditionalManager)->getBySystemName(sName);
        if (c==NULL) {
            log->error("Error getting Condition - "+sName);
            break;
        }
        QString uName = ((DefaultConditional*)c)->getUserName();
        QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg(tr("Conditional")).arg(uName).arg(sName);
        if (sName==(sysName) || uName==(userName))  {
            tempText.append(line1);
            tempText.append(tr("%1Conditional Reference found.\n").arg("\t"));
            found = true;
            //referenceCount++; Don't count, this conditional is orphaned by logix(es)
        }
        QList <ConditionalVariable*>* variableList = ((DefaultConditional*)c)->getCopyOfStateVariables();
        for (int k=0; k<variableList->size(); k++)  {
            ConditionalVariable* v = variableList->at(k);
            QString line = tr("%1Tested as a StateVariable for: %2 {2}\n").arg("\t\t").arg(((ConditionalVariable*)v)->getTestTypeString()).arg(((ConditionalVariable*)v)->getDataString());
            if (testName(((ConditionalVariable*)v)->getName(), found, names, line1, NULL, line, tempText)) {
                found = true;
                //referenceCount++; Don't count, this conditional is orphaned by logix(es)
            }
        }
        QList <ConditionalAction*>* actionList = ((DefaultConditional*)c)->getCopyOfActions();
        for (int k=0; k<actionList->size(); k++) {
            ConditionalAction* a = actionList->at(k);
            QString line = tr("%1Set as an Action for: %2, %3 %4\n").arg("\t\t").arg(((DefaultConditionalAction*)a)->getTypeString()).arg(((DefaultConditionalAction*)a)->getOptionString(false)).arg(((DefaultConditionalAction*)a)->getActionDataString());
            if (testName(((DefaultConditionalAction*)a)->getDeviceName(), found, names, line1, NULL, line, tempText)) {
                found = true;
                //referenceCount++; Don't count, this conditional is orphaned by logix(es)
            }
        }
        if (text != NULL && found) {
            text->append(tempText);
            tempText =  QString();
            found = false;
            empty = false;
            line1 = "";
        }
    }
    if (text != NULL) {
        if (empty) {
            text->append(tr("No references found in %1.\n").arg( "Conditional"));
        }
        text->append("\n");
    }

    found = false;
    empty = true;
    QList<Editor*>* panelList = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getEditorPanelList();
    for (int i=0; i<panelList->size(); i++)
    {
     if(qobject_cast<Editor*>(panelList->at(i)) == NULL)
        continue;
     Editor* panelEditor = panelList->at(i);
     name = panelEditor->getTitle();
     QString line1 = tr("%1%2: \"%3\" (%4)\n").arg(" ").arg( tr("Panel")).arg(name).arg( name);
     QList <Positionable*> contents = panelEditor->getContents();
     for (int k=0; k<contents.size(); k++) {
         Positionable* o = contents.at(k);
         if (QString(((QObject*)o)->metaObject()->className())==("SensorIcon"))
         {
             name = ((SensorIcon*)o)->getSensor()->getSystemName();
             QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg( tr("Sensor"));
             if (testName(name, found, names, line1, NULL, line, tempText)) {
                 found = true;
                 referenceCount++;
             }
         } else if (QString(((QObject*)o)->metaObject()->className())==("TurnoutIcon")) {
             name = ((TurnoutIcon*)o)->getTurnout()->getSystemName();
             QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("Turnout"));
             if (testName(name, found, names, line1, NULL, line, tempText)) {
                 found = true;
                 referenceCount++;
             }
         } else if (QString(((QObject*)o)->metaObject()->className())==("SignalHeadIcon")) {
             name = ((SignalHeadIcon*)o)->getSignalHead()->getSystemName();
             QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("SignalHead"));
             if (testName(name, found, names, line1, NULL, line, tempText)) {
                 found = true;
                 referenceCount++;
             }
         }
 #if 1
         else if (QString(((QObject*)o)->metaObject()->className())==("MultiSensorIcon"))
         {
             MultiSensorIcon* msi = (MultiSensorIcon*)o;
             for (int j=0; j<msi->getNumEntries(); j++)
             {
                 name = msi->getSensorName(j);
                 QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("MultiSensor"));
                 if (testName(name, found, names, line1, NULL, line, tempText)) {
                     found = true;
                     referenceCount++;
                 }
             }
         }

         else if (QString(((QObject*)o)->metaObject()->className())==("IndicatorTurnoutIcon"))
         {
             IndicatorTurnoutIcon* ito = (IndicatorTurnoutIcon*)o;
             name = ito->getTurnout()->getSystemName();
             QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("IndicatorTurnout"));
             if (testName(name, found, names, line1, NULL, line, tempText)) {
                 found = true;
                 referenceCount++;
             }
             Sensor* sensor = ito->getOccSensor();
             if (sensor!=NULL) {
                 name = sensor->getSystemName();
                 line = tr("%1Referred to in a %2 icon\n").arg("\t").arg( tr("IndicatorTurnout"));
                 if (testName(name, found, names, line1, NULL, line, tempText)) {
                     found = true;
                     referenceCount++;
                 }
             }
             OBlock* block = ito->getOccBlock();
             if (block!=NULL) {
                 sensor = block->getSensor();
                 if (sensor!=NULL) {
                     name = sensor->getSystemName();
                     line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("IndicatorTurnout"));
                     if (testName(name, found, names, line1, NULL, line, tempText)) {
                         found = true;
                         referenceCount++;
                     }
                 }
             }
         }

         else if (QString(((QObject*)o)->metaObject()->className())==("IndicatorTrackIcon"))
         {
             IndicatorTrackIcon* track = (IndicatorTrackIcon*)o;
             Sensor* sensor = track->getOccSensor();
             if (sensor!=NULL) {
                 name = sensor->getSystemName();
                 QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("IndicatorTrack"));
                 if (testName(name, found, names, line1, NULL, line, tempText)) {
                     found = true;
                     referenceCount++;
                 }
             }
             OBlock* block = track->getOccBlock();
             if (block!=NULL) {
                 sensor = block->getSensor();
                 if (sensor!=NULL) {
                     name = sensor->getSystemName();
                     QString line = tr("%1Referred to in a %2 icon\n").arg("\t").arg(tr("IndicatorTrack"));
                     if (testName(name, found, names, line1, NULL, line, tempText)) {
                         found = true;
                         referenceCount++;
                     }
                 }
             }

         }
         if (text != NULL && found) {
             text->append(tempText);
             tempText =  QString();
             found = false;
             empty = false;
             line1 = "";
         }
#endif
     }
     if (text != NULL)
     {
      if (empty)
      {
       text->append(tr("No references found in %1.\n").arg( "Panel"));
      }
     }
   }

   if (text != NULL)
   {
    if (referenceCount == 0)
    {
        text->append(tr("%1: \"%2\" (%3) is an Orphan.\n").arg(names.at(0)).arg(names.at(1)).arg(names.at(2)));
    }
    else
    {
        text->append(tr("Found %1 references to \"%2\" (%3).").arg(referenceCount).arg(userName).arg( sysName));
    }
   }
   if (names[0] != NULL)
   {
    // The manager is always a listener
    int numListeners = names.at(3).toInt() - 1;
    // PickLists are also listeners
    numListeners = numListeners - PickListModel::getNumInstances(names.at(0));
        if (names.at(0)==("Sensor"))
        {
         numListeners = numListeners - PickListModel::getNumInstances("MultiSensor");
   }

   if (numListeners > referenceCount)
   {
    if (names[0].length()==0)
    {
        names[0] = "Unknown Type?";
    }
    /*
    JOptionPane.showMessageDialog(NULL,
            tr("OrphanName"), (Object[])names)+" has "+numListeners+
                " listeners installed and only "+referenceCount+
                " references found.\n"+names[0]+
                " Tables are listeneners.  Check that the table is closed.",
            rbm.getString("infoTitle"), JOptionPane.INFORMATION_MESSAGE);
   */
    if (text != NULL)
    {
     text->append(tr("%1: \"%2\" (%3)").arg(names.at(0)).arg(names.at(1)).arg(names.at(2))+" has "+QString::number(numListeners)+
                " listeners installed and only "+QString::number(referenceCount)+
                " references found.\n"+names.at(0)+
                " Tables are listeneners.  Check that the table is closed.");
    }
  }
 }
 return (referenceCount > 0);
}

/*static*/ void Maintenance::makeDialog(QWidget* component, QWidget* button, QWidget* parent, QString title) {
    JDialog* dialog = new JDialog(parent, title, true);
    QPushButton* ok = new QPushButton(tr("OK"));
//    class myListener implements ActionListener {
//         java.awt.Window _w;
//         myListener(java.awt.Window w) {
//             _w = w;
//         }
//         /*public*/ void actionPerformed(ActionEvent e) {
//             _w.dispose();
//         }
//    }
//    ok.addActionListener(new myListener(dialog));
//    ok.setMaximumSize(ok.getPreferredSize());
    connect(ok, SIGNAL(clicked()), dialog, SLOT(close()));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ok->sizePolicy().hasHeightForWidth());
    ok->setSizePolicy(sizePolicy);

    //java.awt.Container contentPane = dialog->getContentPane();
    dialog->setLayout(new QVBoxLayout(dialog/*, BoxLayout.Y_AXIS*/));
    dialog->layout()->addWidget(component/*, BorderLayout.CENTER*/);
//    contentPane.add(Box.createVerticalStrut(5));
//    contentPane.add(Box.createVerticalGlue());
    QWidget* panel = new QWidget();
    panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
    panel->layout()->addWidget(ok);
    if (button != NULL)
    {
     button->setSizePolicy(sizePolicy);
        //panel->layout()->addWidget(Box.createHorizontalStrut(5));
     panel->layout()->addWidget(button);
    }
    dialog->layout()->addWidget(panel/*, BorderLayout.SOUTH*/);
//    class myAdapter extends java.awt.event.WindowAdapter {
//         java.awt.Window _w;
//         myAdapter(java.awt.Window w) {
//             _w = w;
//         }
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             _w.dispose();
//         }
//    }
//    dialog->addWindowListener( new myAdapter(dialog));
//    dialog->setLocationRelativeTo(parent);
//    dialog->pack();
    dialog->setVisible(true);
}

//	static final org.apache.log4j.Logger log = org.apache.log4j.Logger
//			.getLogger(Maintenance.class.getName());
//}
MDefaultListModel::MDefaultListModel(QVector<QString>* display, QObject *parent) : QAbstractListModel(parent)
{
 this->display = display;
}
int MDefaultListModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 1;
}
int MDefaultListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return display->count();
}
QVariant MDefaultListModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  return display->at(index.row());
 }
 return QVariant();
}
