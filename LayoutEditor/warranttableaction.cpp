#include "warranttableaction.h"
#include "jdialog.h"
#include "oblock.h"
#include "path.h"
#include "jtextarea.h"
#include "portal.h"
#include "opath.h"
#include "jtextfield.h"
#include "jtextarea.h"
#include <QScrollArea>
#include "borderlayout.h"
#include "flowlayout.h"
#include "warrantmanager.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "blockorder.h"
#include "warrant.h"
#include "oblockmanager.h"
#include "throttlesetting.h"
#include "warrantframe.h"
#include "savemenu.h"
#include <QTableView>
#include <QList>
#include <QPushButton>
#include <QButtonGroup>
#include <namedicon.h>
#include <QRadioButton>
#include "dcclocoaddress.h"
#include <QLabel>
#include "rosterentry.h"
#include "trackertableaction.h"
#include "nxframe.h"
#include "oblockmanager.h"

WarrantTableAction::WarrantTableAction(QObject *parent) :
    AbstractAction(tr("Warrants"), parent)
{
 common();
}
/**
 * A WarrantAction contains the operating permissions and directives needed for
 * a train to proceed from an Origin to a Destination.
 * WarrantTableAction provides the menu for panels to List, Edit and Create
 * Warrants.  It launched the appropiate frame for each action.
 * <P>
 * It contains an internal class, TableFrame, that lists existing Warrants
 * controls many of their functions.
 * <P>
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
 *
 * @author	Pete Cressman  Copyright (C) 2009, 2010
 */
///*public*/ class WarrantTableAction extends AbstractAction {
/*static*/ int WarrantTableAction::STRUT_SIZE = 10;
/*static*/ QMenu* WarrantTableAction::_warrantMenu = NULL;


//	/*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logix.WarrantBundle");
    /*private*/ /*static*/ QHash <QString, WarrantFrame*>*  WarrantTableAction::_frameMap = new QHash <QString, WarrantFrame*> ();
    /*private*/ /*static*/ WarrantTableFrame* WarrantTableAction::_tableFrame = NULL;
    /*private*/ /*static*/ WarrantTableAction* WarrantTableAction::_instance = NULL;
    /*private*/ /*static*/ QMap <QString, Warrant*> WarrantTableAction::_warrantMap =  QMap <QString, Warrant*> ();
    /*protected*/ /*static*/ TrackerTableAction* WarrantTableAction::_trackerTable = NULL;
    ///*private*/ /*static*/ JTextArea* WarrantTableAction::_textArea = NULL;
    /*private*/ /*static*/ bool WarrantTableAction::_hasErrors = false;
    /*private*/ /*static*/ JDialog*  WarrantTableAction::_errorDialog = NULL;
    ///*static*/ WarrantTableAction* WarrantTableAction::editWarrantAction = NULL;
    /*static*/ QColor WarrantTableAction::_background = QColor(Qt::lightGray);
    JTextField* WarrantTableAction::_endWarrant = NULL;
    JTextField* WarrantTableAction::_startWarrant = NULL;
    JTextField* WarrantTableAction::_status = NULL;
    /*protected*/ /*static*/ WarrantFrame* WarrantTableAction::_openFrame =  NULL;
    /*protected*/ /*static*/ NXFrame* WarrantTableAction::_nxFrame = NULL;
    /*private*/ /*static*/ OpSessionLog* WarrantTableAction::_log = NULL;
    /*private*/ /*static*/ bool WarrantTableAction::_edit = false;
    /*static*/ ShutDownTask*     WarrantTableAction::_shutDownTask = NULL;

/*public*/ WarrantTableAction::WarrantTableAction(QString menuOption, QObject *parent) : AbstractAction(menuOption,parent)
{
 //    super(tr(menuOption));
 common();
}

/*public*/ /*static*/ WarrantTableAction* WarrantTableAction::getDefault()
{
  WarrantTableAction* wta = (WarrantTableAction*)InstanceManager::getOptionalDefault("WarrantTableAction");
 if(! wta) //.orElseGet(() ->
 {
     wta = new WarrantTableAction("Show Warrants"); // NOI18N
     wta->errorCheck();
     return (WarrantTableAction*)InstanceManager::setDefault("WarrantTableAction", wta);
 }//);
 return wta;
}

void WarrantTableAction::common()
{
  this->menuOption = menuOption;
  log = new Logger("WarrantTableAction");
 _startWarrant = new JTextField(30);
 _endWarrant = new JTextField(30);
 _status = new JTextField(90);

 _trackerTable = TrackerTableAction::getInstance(this);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 command = this->text();
}

/*public*/ static WarrantTableAction* getDefault() {
    if( InstanceManager::getOptionalDefault("WarrantTableAction"))/*.orElseGet(() -> */
    {
     return (WarrantTableAction*) InstanceManager::getOptionalDefault("WarrantTableAction");
    }
    else
    {
        WarrantTableAction* wta = new WarrantTableAction("ShowWarrants"); // NOI18N
        wta->errorCheck();
        InstanceManager::setDefault("WarrantTableAction", wta);
        return wta;
    }//);
}
/*public*/ void WarrantTableAction::actionPerformed(JActionEvent * /*e*/)
{
 WarrantTableFrame::getDefault();
}
/**
 * @param edit true if portal errors should be shown in window created from
 *             menu item
 * @return a menu containing warrant actions
 */
/*public*/ QMenu* WarrantTableAction::makeWarrantMenu(bool edit) {
    if (((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getNamedBeanSet().size() > 1) {
        _warrantMenu = new QMenu(tr("Warrant"));
        updateWarrantMenu();
        return _warrantMenu;
    }
    return nullptr;
}

//@InvokeOnGuiThread
    /*synchronized*/ /*protected*/ void WarrantTableAction::updateWarrantMenu() {
        _warrantMenu->clear();
        _warrantMenu->addAction(getDefault());
        QMenu* editWarrantMenu = new QMenu(tr("Edit Warrant"));
        _warrantMenu->addMenu(editWarrantMenu);
//        ActionListener editWarrantAction = (ActionEvent e) -> {
//            openWarrantFrame(e.getActionCommand());
//        };
        WarrantManager* manager = (WarrantManager*)InstanceManager::getDefault("WarrantManager");
        if (manager->getObjectCount() == 0) { // when there are no Warrants, enter the word "None" to the submenu
            QAction* _noWarrants;// = new JMenuItem(Bundle.getMessage("None"));
            _noWarrants = editWarrantMenu->addSection(tr("None"));
            // disable it
            _noWarrants->setEnabled(false);
        } else { // when there are warrants, add them to the submenu
            for (NamedBean* nb : manager->getNamedBeanSet()) {
             Warrant* warrant = (Warrant*)nb;
                // Warrant warrent = (Warrant) object;
                QAction* mi = new QAction(warrant->getDisplayName());
                //mi.setActionCommand(warrant.getDisplayName());
                //mi.addActionListener(editWarrantAction);
                connect(mi, &QAction::triggered, [=]{
                 QAction*act = (QAction*)QObject::sender();
                 openWarrantFrame(act->text());
                });
                editWarrantMenu->addAction(mi);
            }
        }
        QAction* act;
         _warrantMenu->addAction(act =new AbstractAction(tr("Create Warrant"),this));
//         {
//            @Override
//            public void actionPerformed(ActionEvent e) {
           connect(act, &QAction::triggered, [=]{
                makeWarrantFrame(nullptr, nullptr);
//            }
         });
        _warrantMenu->addAction((TrackerTableAction*)InstanceManager::getDefault("TrackerTableAction"));
        _warrantMenu->addAction(act =new AbstractAction(tr("Create NX Warrant"),this));
//        {
//            @Override
//            public void actionPerformed(ActionEvent e) {
        connect(act, &QAction::triggered, [=]{
                makeNXFrame();
//            }
        });
        _warrantMenu->addAction(makeLogMenu());

        log->debug(tr("updateMenu to %1 warrants.").arg(manager->getObjectCount()));
    }
/*synchronized*/ /*protected*/ void WarrantTableAction::writetoLog(QString text) {
        if (_logging) {
            OpSessionLog::writeLn(text);
        }
    }

  //@InvokeOnGuiThread
/*protected*/ void WarrantTableAction::closeNXFrame() {
    if (_nxFrame != nullptr) {
        _nxFrame->clearTempWarrant();
        _nxFrame->dispose();
        _nxFrame = nullptr;
    }
}

//@InvokeOnGuiThread
/*protected*/ NXFrame* WarrantTableAction::makeNXFrame() {
    if (_nxFrame == nullptr) {
        _nxFrame = new NXFrame();
    }
//    _nxFrame->setState(java.awt.Frame.NORMAL);
    _nxFrame->setVisible(true);
    _nxFrame->toFront();
    return _nxFrame;
}

/*protected*/ void WarrantTableAction::closeWarrantFrame() {
    if (_openFrame != nullptr) {
        _openFrame->close();
        _openFrame->dispose();
        _openFrame = nullptr;
    }
}

/*protected*/ void WarrantTableAction::makeWarrantFrame(Warrant* startW, Warrant* endW) {
    if (_openFrame != nullptr && _openFrame->isRunning()) {
        return;
    }
    closeWarrantFrame();
    _openFrame = new WarrantFrame(startW, endW);
//    _openFrame.setState(java.awt.Frame.NORMAL);
    _openFrame->setVisible(true);
    _openFrame->toFront();
}

/*protected*/ void WarrantTableAction::editWarrantFrame(Warrant* w) {
    if (_openFrame != nullptr && _openFrame->isRunning()) {
        return;
    }
    closeWarrantFrame();
    _openFrame = new WarrantFrame(w);
//    _openFrame.setState(java.awt.Frame.NORMAL);
    _openFrame->setVisible(true);
    _openFrame->toFront();
}

/*private*/ void WarrantTableAction::openWarrantFrame(QString key) {
    Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(key);
    if (w != nullptr) {
        editWarrantFrame(w);
    }
}

EditWarrantActionListener::EditWarrantActionListener(QSignalMapper* editWarrantMapper, WarrantTableAction *act)
{
 this->editWarrantMapper = editWarrantMapper;
 this->act = act;
 connect(editWarrantMapper, SIGNAL(mapped(QString)), this, SLOT(on_editWarrantMapper(QString)));
}

void EditWarrantActionListener::on_createNXWarrantAct()
{
 WarrantTableFrame::nxAction();
}

void EditWarrantActionListener::on_editWarrantMapper(QString cmd)
{
// if(cmd == tr("Warrant List") || cmd == tr("Create New Warrant"))
// { if (tr("Warrant List")==(cmd))
//  {
//   if(WarrantTableAction::getInstance()->_tableFrame==NULL)
//   {
//    WarrantTableAction::getInstance()->_tableFrame = new WarrantTableFrame();
//    try
//    {
//     WarrantTableAction::getInstance()->_tableFrame->initComponents();
//    }
//    catch (Exception ex ) {/*bogus*/ }
//   }
//   else
//   {
//    WarrantTableAction::getInstance()->_tableFrame->setVisible(true);
//    WarrantTableAction::getInstance()->_tableFrame->pack();
//   }
//  }
//  else if (tr("Create New Warrant")==(cmd))
//  {
//   CreateWarrantFrame* f = new CreateWarrantFrame(WarrantTableAction::getInstance());
//    try
//   {
//    f->initComponents();
//   } catch (Exception ex ) {/*bogus*/ }
//   f->setVisible(true);
//  }
//  WarrantTableAction::getInstance()->initPathPortalCheck();
//  OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
//  QStringList sysNames = manager->getSystemNameArray();
//  for (int i = 0; i < sysNames.length(); i++)
//  {
//   OBlock* block = manager->getBySystemName(sysNames[i]);
//         WarrantTableAction::getInstance()->checkPathPortals(block);
//  }
//  WarrantTableAction::getInstance()->showPathPortalErrors();}
 act->openWarrantFrame(cmd);
}
/*protected*/  QAction* WarrantTableAction::makeLogMenu()
{
 QAction* mi;
 if (!_logging) {
     mi = new QAction(tr("Open Session Log"),this);
     //mi.addActionListener((ActionEvent e) -> {
     connect(mi, &QAction::triggered, [=]{
//         if (!OpSessionLog::makeLogFile(WarrantTableFrame::getDefault())) {
//             return;
//         }
         _logging = true;
         _shutDownTask = new WTAShutDownTask("PanelPro Save default icon check",
                 nullptr, nullptr, nullptr);
//         {
//             @Override
//             public boolean checkPromptNeeded() {
//                 OpSessionLog.close();
//                 _logging = false;
//                 return true;
//             }
//         };
         ((ShutDownManager*) InstanceManager::getDefault("ShutDownManager"))->_register(_shutDownTask);
         updateWarrantMenu();
     });
 } else {
     mi = new QAction(tr("Flush data to Session Log"));
     //mi.addActionListener((ActionEvent e) -> {
     connect(mi, &QAction::triggered, [=]{
//         OpSessionLog::flush();
     });
     _warrantMenu->addAction(mi);
     mi = new QAction(tr("Close Session Log"));
     //mi.addActionListener((ActionEvent e) -> {
     connect(mi, &QAction::triggered, [=]{

         OpSessionLog::close();
         ((ShutDownManager*) InstanceManager::getDefault("ShutDownManager"))->deregister(_shutDownTask);
         _shutDownTask = nullptr;
         _logging = false;
         updateWarrantMenu();
     });
 }
 return mi;
}




/*synchronized*/ /*protected*/ /*static*/ void WarrantTableAction::portalNameChange(QString oldName, QString newName)
{
 WarrantManager* manager = (WarrantManager*)
InstanceManager::getDefault("WarrantManager");
 QStringList systemNameList = manager->getSystemNameList();
 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  Warrant* w =(Warrant*)manager->getBySystemName(iter.next());
  QList <BlockOrder*>* orders = w->getBlockOrders();
  QListIterator<BlockOrder*> it(*orders);
  while (it.hasNext())
  {
   BlockOrder* bo = it.next();
   if (oldName==(bo->getEntryName()))
   {
    bo->setEntryName(newName);
   }
   if (oldName==(bo->getExitName()))
   {
    bo->setExitName(newName);
   }
  }
 }
}

/*synchronized*/ /*protected*/ /*static*/ void WarrantTableAction::pathNameChange(OBlock* block, QString oldName, QString newName) {
 WarrantManager* manager = (WarrantManager*)
InstanceManager::getDefault("WarrantManager");
 QStringList systemNameList = manager->getSystemNameList();
 QStringListIterator iter( systemNameList);
 while (iter.hasNext())
 {
  Warrant* w = (Warrant*)manager->getBySystemName(iter.next());
  QList<BlockOrder*>* orders = w->getBlockOrders();
  QListIterator<BlockOrder*> it(*orders);
  while (it.hasNext())
  {
   BlockOrder* bo = it.next();
   if (bo->getBlock()==(block) && bo->getPathName()==(oldName)) {
       bo->setPathName(newName);
   }
  }
 }
}

/*    synchronized public static WarrantFrame getWarrantFrame(String key) {
    return _frameMap.get(key);
}*/

/*synchronized*/ /*static*/ /*public*/ void WarrantTableAction::mouseClickedOnBlock(OBlock* block)
{
 if (block==NULL) {
     return;
 }

 NXFrame* nxFrame = NXFrame::getInstance();
 if (nxFrame->isVisible()) {
     nxFrame->mouseClickedOnBlock(block);
     return;
 }

 if (_trackerTable!=NULL && TrackerTableAction::mouseClickedOnBlock(block)) {
     return;
 }
 if (_openFrame!=NULL) {
     _openFrame->mouseClickedOnBlock(block);
     return;
 }
}

/******************** Error checking ************************/

/*public*/ bool WarrantTableAction::errorCheck() {
    _hasErrors = false;
    JTextArea* textArea = new JTextArea(10, 50);
    textArea->setEditable(false);
    textArea->setTabSize(4);
    textArea->append(tr("The following are possible sources for errors:"));
    textArea->append("\n\n");
    OBlockManager* manager = (OBlockManager*) InstanceManager::getDefault("OBlockManager");
    for (NamedBean* nb : manager->getNamedBeanSet()) {
     OBlock* block = (OBlock*)nb;
        textArea->append(checkPathPortals(block));
    }
    return showPathPortalErrors(textArea);
}


/**
 * Validation of paths within a block. Gathers messages in a text area that
 * can be displayed after all are written.
 *
 * @param b the block to validate
 * @return error/warning message, if any
 */
//@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "OPath extends Path")
/*public*/ QString WarrantTableAction::checkPathPortals(OBlock* b) {
    if (log->isDebugEnabled()) {
        log->debug("checkPathPortals for " + b->getDisplayName());
    }
    QString sb;// = new StringBuffer();
    QVector<Path*>* pathList = b->getPaths();
    if (pathList->isEmpty()) {
        sb.append(tr("No Paths in Block \"%1\"").arg(b->getDisplayName()));
        sb.append("\n");
        _hasErrors = true;
        return sb;
    }
    QList<Portal*> portalList = b->getPortals();
    // make list of names of all portals.  Then remove those we check, leaving the orphans
    QList<QString> portalNameList = QStringList();
    for (int i = 0; i < portalList.size(); i++) {
        Portal* portal = portalList.at(i);
        if (portal->getFromPaths()->isEmpty()) {
            sb.append(tr("Portal \"%1\" has no path into block \"%2\".").arg(portal->getName()).arg(
                    portal->getFromBlockName()));
            sb.append("\n");
            _hasErrors = true;
            return sb;
        }

        if (portal->getToPaths()->isEmpty()) {
            sb.append(tr("Portal \"%1\" has no path into block \"%2\".").arg(portal->getName()).arg(
                    portal->getToBlockName()));
            sb.append("\n");
            _hasErrors = true;
            return sb;
        }
        portalNameList.append(portal->getName());
    }
    QVectorIterator<Path*> iter(*pathList);
    while (iter.hasNext()) {
        OPath* path = (OPath*) iter.next();
        OBlock* block = (OBlock*) path->getBlock();
        if (block == nullptr || !block->equals(b)) {
            sb.append(tr("Path \"%1\" belonging to block \"%2\" does not have\n \"%2\" as its owner.  Please delete this path.   ").arg(path->getName()).arg(b->getDisplayName()));
            sb.append("\n");
            _hasErrors = true;
            return sb;
        }
        QString msg = nullptr;
        bool hasPortal = false;
        Portal* fromPortal = path->getFromPortal();
        if (fromPortal != nullptr) {
            if (!fromPortal->isValid()) {
                msg = fromPortal->getName();
            }
            hasPortal = true;
            portalNameList.removeOne(fromPortal->getName());
        }
        Portal* toPortal = path->getToPortal();
        if (toPortal != nullptr) {
            if (!toPortal->isValid()) {
                msg = toPortal->getName();
            }
            hasPortal = true;
            portalNameList.removeOne(toPortal->getName());
            if (fromPortal != nullptr && fromPortal == (toPortal)) {
                sb.append(tr("Entrance portal cannot equal exit portal for path \"%1\" in block \"%2\". (ambiguous turnout settings)").arg(
                        path->getName()).arg(b->getDisplayName()));
                sb.append("\n");
            }
        }
        if (msg != "") {
            sb.append(tr("Portal \"%1\" needs to have a block specified on each side.").arg(msg));
            sb.append("\n");
            _hasErrors = true;
        } else if (!hasPortal) {
            sb.append(tr("Path \"%1\" in block \"%2\" needs to have at least one Portal.").arg(
                    path->getName()).arg(b->getDisplayName()));
            sb.append("\n");
            _hasErrors = true;
        }
        // check that the path's portals have the path in their lists
        bool validPath;
        if (toPortal != nullptr) {
            if (fromPortal != nullptr) {
                validPath = toPortal->isValidPath(path) && fromPortal->isValidPath(path);
            } else {
                validPath = toPortal->isValidPath(path);
            }
        } else {
            if (fromPortal != nullptr) {
                validPath = fromPortal->isValidPath(path);
            } else {
                validPath = false;
            }
        }
        if (!validPath) {
            sb.append(tr("Path \"%1\" in block \"%2\" is not registered in its portals.  (re-enter the path)").arg(
                    path->getName()).arg(b->getDisplayName()));
            sb.append("\n");
            _hasErrors = true;
        }
    }
    for (int i = 0; i < portalNameList.size(); i++) {
        sb.append(tr("Portal \"%1\" has no path into block \"%2\".").arg(
                portalNameList.at(i)).arg(b->getDisplayName()));
        sb.append("\n");
        _hasErrors = true;
    }
    // check whether any turnouts are shared between two blocks;
    checkSharedTurnouts(b);

    return sb;
}

/*public*/ /*static*/ bool WarrantTableAction::checkSharedTurnouts(OBlock* block)
{
 bool hasShared = false;
 OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 QStringList sysNames = manager->getSystemNameArray();
 QVector <Path*>* pathList = block->getPaths();
 QVectorIterator <Path*> iter(*pathList);
 while (iter.hasNext()) {
     OPath* path = (OPath*)iter.next();
     for (int i=0; i < sysNames.length(); i++) {
         if (block->getSystemName()==(sysNames[i])) {
             continue;
         }
         OBlock* b = (OBlock*)manager->getBySystemName(sysNames[i]);
         QVectorIterator <Path*> it(*b->getPaths());
         while (it.hasNext()) {
             bool shared = sharedTO(path, (OPath*)it.next());
             if (shared) {
                 hasShared =true;
                 break;
             }
         }
     }
 }
 return hasShared;
}
/*private*/ /*static*/ bool WarrantTableAction::sharedTO(OPath* myPath, OPath* path) {
QList<BeanSetting*> myTOs = myPath->getSettings();
QListIterator <BeanSetting*> iter(myTOs);
 QList<BeanSetting*> tos = path->getSettings();
 bool ret = false;
 while (iter.hasNext()) {
     BeanSetting* mySet = iter.next();
     NamedBean* myTO = mySet->getBean();
     int myState = mySet->getSetting();
     QListIterator <BeanSetting*> it(tos);
     while (it.hasNext()) {
         BeanSetting* set = it.next();
         NamedBean* to = set->getBean();
         if(myTO==(to)) {
             // turnouts are equal.  check if settings are compatible.
             OBlock* myBlock = (OBlock*)myPath->getBlock();
             int state = set->getSetting();
             OBlock* block = (OBlock*)path->getBlock();
//                  String note = "WARNING: ";
             if (myState!=state) {
                ret = myBlock->addSharedTurnout(myPath, block, path);
/*                       _textArea.append(note+Bundle.getMessage("sharedTurnout", myPath.getName(), myBlock.getDisplayName(),
                      myTO.getDisplayName(), (myState==jmri.Turnout.CLOSED ? "Closed":"Thrown"),
                      path.getName(), block.getDisplayName(), to.getDisplayName(),
                      (state==jmri.Turnout.CLOSED ? "Closed":"Thrown")));
               _textArea.append("\n");
             } else {
                 note = "Note: "; */
             }
         }
     }
 }
 return ret;
}
/*public*/ /*static*/ bool WarrantTableAction::showPathPortalErrors(JTextArea* textArea)
{
 if (_errorDialog != nullptr) {
     _errorDialog->dispose();
 }
 if (!_hasErrors) {
     return false;
 }

 //JScrollPane scrollPane = new JScrollPane(_textArea);
// QScrollArea* scrollPane = new QScrollArea();
// scrollPane->setWidget(_textArea);
// scrollPane->setWidgetResizable(true);
// scrollPane->setEnabled(true);

 _errorDialog = new JDialog();
 _errorDialog->setTitle(tr("Block/Portal/Path Warnings"));
 QPushButton* ok = new QPushButton(tr("OK"));
//    class myListener extends java.awt.event.WindowAdapter implements ActionListener {
//       /*  java.awt.Window _w;
//         myListener(java.awt.Window w) {
//             _w = w;
//         }  */
//         /*public*/ void actionPerformed(ActionEvent e) {
//             _hasErrors = false;
//             _textArea = NULL;
//             _errorDialog->dispose();
//         }
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             _hasErrors = false;
//             _textArea = NULL;
//             _errorDialog->dispose();
//         }
//    };
    //ok.addActionListener(new myListener());
 MyListener* myListener = new MyListener(_errorDialog);
 connect(ok, SIGNAL(clicked()),  myListener, SLOT(actionPerformed()));
    ok->setMaximumSize(ok->sizeHint());

//    QWidget* contentPane = _errorDialog->getContentPane();
 QVBoxLayout* contentPaneLayout;
 _errorDialog->setLayout(contentPaneLayout = new QVBoxLayout(_errorDialog/*, BoxLayout.Y_AXIS*/));
 contentPaneLayout->addWidget(/*scrollPane*/textArea, /*BorderLayout::Center*/0, Qt::AlignCenter);
//    contentPane.add(Box.createVerticalStrut(5));
//    contentPane.add(Box.createVerticalGlue());
 QWidget* panel = new QWidget();
 panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
 panel->layout()->addWidget(ok);
 contentPaneLayout->addWidget(panel, /*BorderLayout::South*/0, Qt::AlignBottom);
//    _errorDialog->addWindowListener( new myListener());
 _errorDialog->adjustSize();
 _errorDialog->setVisible(true);
 _errorDialog->show();

 return true;
}
//void WarrantTableAction::On_Ok_clicked()
//{
// _hasErrors = false;
// _textArea = NULL;
// _errorDialog->close();
//}


/******************* CreateWarrant ***********************/

///*static*/ class CreateWarrantFrame : public JFrame
//{
/*public*/ CreateWarrantFrame::CreateWarrantFrame(WarrantTableAction* parent)
{
    this->parent = parent;
 setTitle(tr("Create Warrant"));
 }

/*public*/ void CreateWarrantFrame::initComponents() {
    QWidget* contentPane = new QWidget();
    QVBoxLayout* contentPaneLayout;
    contentPane->setLayout(contentPaneLayout=new QVBoxLayout); //(10/*,10*/));
    QLabel* prompt = new QLabel(tr("Enter a System Name and (optionally) a User Name."));
    contentPaneLayout->addWidget(prompt, /*BorderLayout::North*/0, Qt::AlignTop);

    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
//    panel.add(Box.createHorizontalStrut(STRUT_SIZE));
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
    p->layout()->addWidget(new QLabel(tr("System Name")));
    _sysNameBox = new JTextField(15);
    p->layout()->addWidget(_sysNameBox);
    panel->layout()->addWidget(p);
//    panel.add(Box.createHorizontalStrut(STRUT_SIZE));
    {
    p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    p->layout()->addWidget(new QLabel(tr("User Name")));
    _userNameBox = new JTextField(15);
    p->layout()->addWidget(_userNameBox);
    panel->layout()->addWidget(p);
//    panel.add(Box.createHorizontalStrut(STRUT_SIZE));
    contentPaneLayout->addWidget(panel, /*BorderLayout::Center*/Qt::AlignCenter);
    }
    {
    panel = new QWidget();
    FlowLayout* panelLayout = new FlowLayout(panel);
    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            makeWarrant();
//        }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(makeWarrant()));
//    doneButton.setPreferredSize(doneButton.getPreferredSize());
    panel->layout()->addWidget(doneButton);
    }
    contentPaneLayout->addWidget(panel, BorderLayout::South);
//    contentPaneLayout->addStrut(Box.createVerticalStrut(STRUT_SIZE), BorderLayout.EAST);
//    contentPaneLayout.add(Box.createVerticalStrut(STRUT_SIZE), BorderLayout.WEST);

    setCentralWidget(contentPane);
//    setLocationRelativeTo(NULL);
    setVisible(true);
    adjustSize();
}

void CreateWarrantFrame::concatenate(Warrant* startW, Warrant* endW) {
    _startW = startW;
    _endW = endW;
}

void CreateWarrantFrame::makeWarrant()
{
 QString sysName = _sysNameBox->text().trimmed();
 QString userName = _userNameBox->text().trimmed();
 if (sysName==NULL || sysName.length()==0 || sysName.toUpper()==("IW"))
 {
  //dispose();
  close();
  return;
 }
 if (userName.trimmed().length()==0)
 {
  userName = "";
 }
  bool failed = false;
  Warrant* w = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getBySystemName(sysName);
  if (w != NULL)
  {
   failed = true;
  }
  else
  {
   w = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getByUserName(userName);
  if (w != NULL)
  {
   failed = true;
  }
  else
  {
   // register warrant if user saves this instance
   w = new Warrant(sysName, userName);
  }
 }
 if (failed)
 {
//        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                        tr("WarrantExists"), userName, sysName),
//                        tr("WarningTitle"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::warning(this, tr("Warning"), tr("A Warrant named \"%1\" or \"%2\" already exists.").arg(sysName).arg(userName));
 }
 else
 {
  if (_startW!=NULL && _endW!=NULL)
  {
   QList <BlockOrder*>* orders = _startW->getOrders();
   int limit = orders->size()-1;
   for (int i=0; i<limit; i++)
   {
    w->addBlockOrder(new BlockOrder(orders->at(i)));
   }
   BlockOrder* bo = new BlockOrder(orders->at(limit));
   orders = _endW->getOrders();
   bo->setExitName(orders->at(0)->getExitName());
   w->addBlockOrder(bo);
   for (int i=1; i<orders->size(); i++)
   {
    w->addBlockOrder(new BlockOrder(orders->at(i)));
   }

   QList <ThrottleSetting*>* commands = _startW->getThrottleCommands();
   for (int i=0; i<commands->size(); i++)
   {
    w->addThrottleCommand(new ThrottleSetting(commands->at(i)));
   }
   commands = _endW->getThrottleCommands();
   for (int i=0; i<commands->size(); i++)
   {
    w->addThrottleCommand(new ThrottleSetting(commands->at(i)));
   }
   parent->_frameMap->insert(w->getDisplayName(), new WarrantFrame(w, false));
  }
  else
  {
   parent->_frameMap->insert(w->getDisplayName(), new WarrantFrame(w, true));
  }
  //dispose();
  close();
 }
}

//};


void WarrantTableAction::on_createWarrant_triggered()
{
 WarrantTableFrame::nxAction();
}

/********************** Show Warrants Table *************************/

/*static*/ /*final*/ QString WarrantTableAction::halt = tr("Halt");
/*static*/ /*final*/ QString WarrantTableAction::resume = tr("Resume");
/*static*/ /*final*/ QString WarrantTableAction::abort = tr("Abort");
/*static*/ /*final*/ QStringList WarrantTableAction::controls = QStringList() << WarrantTableAction::halt << WarrantTableAction::resume <<  WarrantTableAction::abort;

//class TableFrame  : public JmriJFrame // implements ActionListener
//{

#if 0
/*public*/ WarrantTableFrame::WarrantTableFrame(QWidget* parent) :JmriJFrame(parent)
{
 this->parent = parent;
 setTitle(tr("Warrant Table"));

 _model = new WarrantTableModel(parent);
 _model->init();
//	Casts at getTableCellEditorComponent() now fails with 3.0 ??
 QTableView* table = new QTableView;   // = new JTable(_model);
 table->setModel(_model);
#if 0
//    ComboBoxCellEditor comboEd;
    try {   // following might fail due to a missing method on Mac Classic
        TableSorter sorter = new jmri.util.com.sun.TableSorter(_model);
        table = jmri.util.JTableUtil.sortableDataModel(sorter);
        sorter.setTableHeader(table.getTableHeader());
        comboEd = new ComboBoxCellEditor(new JComboBox(), sorter);
        // set model last so later casts will work
        ((jmri.util.com.sun.TableSorter)table.getModel()).setTableModel(_model);
    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
        log->error("WarrantTable: Unexpected error: "+e);
        table = new JTable(_model);
        comboEd = new ComboBoxCellEditor(new JComboBox());
    }

    table.setDefaultRenderer(Boolean.class, new ButtonRenderer());
    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
    JComboBox box = new JComboBox(controls);
    box.setFont(new Font(NULL, Font.PLAIN, 12));
    table.getColumnModel().getColumn(WarrantTableModel.CONTROL_COLUMN).setCellEditor(new DefaultCellEditor(box));
    table.getColumnModel().getColumn(WarrantTableModel.ROUTE_COLUMN).setCellEditor(comboEd);
    table.getColumnModel().getColumn(WarrantTableModel.ALLOCATE_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.ALLOCATE_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.DEALLOC_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.DEALLOC_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.SET_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.SET_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.AUTO_RUN_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.AUTO_RUN_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.MANUAL_RUN_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.MANUAL_RUN_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.EDIT_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.EDIT_COLUMN).setCellRenderer(new ButtonRenderer());
    table.getColumnModel().getColumn(WarrantTableModel.DELETE_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
    table.getColumnModel().getColumn(WarrantTableModel.DELETE_COLUMN).setCellRenderer(new ButtonRenderer());
    //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    for (int i=0; i<_model.getColumnCount(); i++) {
        int width = _model.getPreferredWidth(i);
        table.getColumnModel().getColumn(i).setPreferredWidth(width);
    }
    table.setRowHeight(box.getPreferredSize().height);
    table.setDragEnabled(true);
    table.setTransferHandler(new jmri.util.DnDTableExportHandler());
    JScrollPane tablePane = new JScrollPane(table);
    Dimension dim = table.getPreferredSize();
    dim.height = table.getRowHeight()*12;
    tablePane.getViewport().setPreferredSize(dim);
#endif
    QWidget* tablePanel = new QWidget();
    tablePanel->setLayout(new QVBoxLayout(tablePanel/*, BoxLayout.Y_AXIS*/));
    QLabel* title = new QLabel(tr("Warrant List"));
    ((QVBoxLayout*)tablePanel->layout())->addWidget(title, /*BorderLayout::North*/0,Qt::AlignTop);
    ((QVBoxLayout*)tablePanel->layout())->addWidget(table, /*BorderLayout::Center*/0,Qt::AlignCenter);

    QWidget* panel = new QWidget();
    QWidget* p = new QWidget();
    p->setLayout(new QHBoxLayout);
    p->layout()->addWidget(new QLabel("status"));
    parent->_background = parent->_status->getBackground();
    QFont f = parent->_status->font();
    f.setBold(true);
    parent->_status->setFont(f);
    p->layout()->addWidget(parent->_status);
    parent->_status->setEnabled(false);
    ((QVBoxLayout*)tablePanel->layout())->addWidget(p, /*BorderLayout.CENTER*/0,Qt::AlignCenter);

    panel = new QWidget();
    panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
//    panel.add(Box.createHorizontalStrut(2*STRUT_SIZE));
    //QWidget* p = new QWidget();
    //p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
    QWidget* pp = new QWidget();
    pp->setLayout(new FlowLayout());
    pp->layout()->addWidget(new QLabel("A:"));
    pp->layout()->addWidget(parent->_startWarrant);
    parent->_startWarrant->setDragEnabled(true);
//    _startWarrant.setTransferHandler(new DnDStringImportHandler());
    panel->layout()->addWidget(pp);
    pp = new QWidget();
    pp->setLayout(new FlowLayout());
    pp->layout()->addWidget(new QLabel("B:"));
    pp->layout()->addWidget(parent->_endWarrant);
    parent->_endWarrant->setDragEnabled(true);
//    _endWarrant.setTransferHandler(new DnDStringImportHandler());
    panel->layout()->addWidget(pp);
    QPushButton* concatButton = new QPushButton(tr("Concatenate"));
//    concatButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            concatenate();
//        }
//    });
    connect(concatButton, SIGNAL(clicked()), this, SLOT(concatenate()));
    //panel.add(p);
//    panel.add(Box.createHorizontalStrut(STRUT_SIZE));
    panel->layout()->addWidget(concatButton);
//    panel.add(Box.createHorizontalStrut(2*STRUT_SIZE));
    QWidget* bottomPanel = new QWidget();
    bottomPanel->setLayout(new QVBoxLayout(bottomPanel/*, BoxLayout.Y_AXIS*/));
    bottomPanel->layout()->addWidget(new QLabel(tr("Join Destination of Warrant A to Origin of Warrant B")));
    bottomPanel->layout()->addWidget(panel);
    ((QVBoxLayout*)tablePanel->layout())->addWidget(bottomPanel, /*BorderLayout.SOUTH*/0,Qt::AlignBottom);

//    addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                dispose();
//            }
//        });
    QMenuBar* menuBar = new QMenuBar();
    QMenu* fileMenu = new QMenu(tr("File"));
    fileMenu->addMenu(new SaveMenu());
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);
    addHelpMenu("package.jmri.jmrit.logix.Warrant", true);

    setCentralWidget(tablePanel);
    setLocation(0,100);
    setVisible(true);
    pack();
}
//};
#endif
/*private*/ void WarrantTableAction::concatenate()
{
 WarrantManager* manager = ( WarrantManager*)InstanceManager::getDefault("WarrantManager");
 Warrant* startW = manager->getWarrant(_startWarrant->text().trimmed());
 Warrant* endW = manager->getWarrant(_endWarrant->text().trimmed());
 if (startW==NULL || endW==NULL)
 {
//  JOptionPane.showMessageDialog(NULL, tr("BadWarrantNames"),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("Enter or drag warrant names into the text boxes."));
  return;
 }
 BlockOrder* last = startW->getLastOrder();
 BlockOrder* next = endW->getfirstOrder();
 if (last==NULL || next==NULL)
 {
//        JOptionPane.showMessageDialog(NULL, tr("EmptyRoutes"),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("Routes are not defined for both Warrants."));
  return;
 }
 if (last->getPathName()!=(next->getPathName()))
 {
//        JOptionPane.showMessageDialog(NULL, java.text.MessageFormat.format(
//                tr("RoutesDontMatch"), startW.getDisplayName(), endW.getDisplayName()),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("The destination path of %1 does not match the originating path of %2").arg(startW->getDisplayName()).arg( endW->getDisplayName()));
  return;
 }
 CreateWarrantFrame* f = new CreateWarrantFrame(this);
 try
 {
  f->initComponents();
  f->concatenate(startW, endW);
 } catch (Exception ex ) { log->error("error making CreateWarrantFrame", ex);}
 f->setVisible(true);
}
#if 0
static /*public*/ class ComboBoxCellEditor : public DefaultCellEditor
{
    TableSorter _sorter;

    ComboBoxCellEditor(JComboBox comboBox) {
        super(comboBox);
        comboBox.setFont(new Font(NULL, Font.PLAIN, 12));
    }
    ComboBoxCellEditor(JComboBox comboBox, TableSorter sorter) {
        super(comboBox);
        comboBox.setFont(new Font(NULL, Font.PLAIN, 12));
        _sorter = sorter;
    }
    /*public*/ Component getTableCellEditorComponent(JTable table, Object value,
                                     boolean isSelected, int row, int column)
    {
        jmri.util.com.sun.TableSorter m = ((jmri.util.com.sun.TableSorter)table.getModel());
        WarrantTableModel model = (WarrantTableModel)m.getTableModel();

        // If table has been sorted, table row no longer is the same as array index
        if (_sorter!=NULL) {
            row = _sorter.modelIndex(row);
        }
        Warrant warrant = model.getWarrantAt(row);
        JComboBox comboBox = (JComboBox)getComponent();
        comboBox.removeAllItems();
        List <BlockOrder> orders = warrant.getOrders();
        for (int i=0; i<orders.size(); i++) {
            BlockOrder order = orders.get(i);
            comboBox.addItem(order.getBlock().getDisplayName()+": - "+order.getPath().getName());
        }
        return comboBox;
    }
};
#endif
void WarrantTableAction::setStatusText(QString msg, QColor c)
{
    if (QColor(Qt::red)==(c))
    {
        _status->setBackground(QColor(Qt::white));
    } else {
        _status->setBackground(QColor(Qt::gray));
    }
    _status->setForeground(c);
    _status->setText(msg);
}



