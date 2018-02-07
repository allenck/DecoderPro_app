#include "circuitbuilder.h"
#include "oblockmanager.h"
#include "instancemanager.h"
#include "oblock.h"
#include "portalicon.h"
#include "jtextfield.h"
#include "controlpaneleditor.h"
#include "portalicon.h"
#include "indicatortrack.h"
#include "turnouticon.h"
#include "portal.h"
#include "editcircuitframe.h"
#include <QMessageBox>
#include "borderlayout.h"
#include "picklistmodel.h"
#include "flowlayout.h"
#include "itempalette.h"
#include "indicatorturnouticon.h"
#include "indicatortoitempanel.h"
#include "indicatoritempanel.h"
#include "indicatortrackicon.h"
#include "warranttableaction.h"
#include <QMessageBox>
#include "editportalframe.h"
#include "editcircuitpaths.h"
#include "editportaldirection.h"
#include "portalmanager.h"
#include "instancemanager.h"
#include "inputdialog.h"
#include <QComboBox>

//CircuitBuilder::CircuitBuilder(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2011
 * @version $Revision: 21062 $
 *
 */

// /*public*/ class CircuitBuilder  {


//    /*public*/ final static ResourceBundle rbcp = ControlPanelEditor.rbcp;
    /*public*/ /*final*/ /*static*/ QColor CircuitBuilder::_editGroupColor =  QColor(150, 150, 255);
    /*public*/ /*final*/ /*static*/ QColor CircuitBuilder::_pathColor = QColor(Qt::green);
    /*public*/ /*final*/ /*static*/ QColor CircuitBuilder::_highlightColor =  QColor(255, 100, 200);

    /******************************************************************/

/*public*/ CircuitBuilder::CircuitBuilder(QObject *parent) :
    QObject(parent) {
    log = new Logger("CircuitBuilder");
//        _menuBar = new JMenuBar();
    log->error("CircuitBuilder ctor requires an Editor class");
    common();
}

/*public*/ CircuitBuilder::CircuitBuilder(ControlPanelEditor* ed, QObject *parent)
    :  QObject(parent){
    log = new Logger("CircuitBuilder");
 common();
 _editor = ed;
}

void CircuitBuilder::common()
{
 _editor = NULL;
 _iconMap = new QHash<Positionable*, OBlock*>();
 _sysNameBox = new JTextField();
 _userNameBox = new JTextField();
 _portalIcons = new QList<PortalIcon*>();
 hasOBlocks = false;
 _editPathsFrame = NULL;
 _editCircuitFrame = NULL;
 _editPortalFrame = NULL;
 _oblockModel = NULL;
 _editDirectionFrame = NULL;
 // list of track icons not belonging to an OBlock
 _darkTrack =  QList<Positionable*>();
 // list of OBlocks with no icons
 _bareBlock = new QList<OBlock*>();
 // list of circuit icons needing converting
 _unconvertedTrack =  QList<Positionable*>();
// list of OBlocks whose icons need converting
 _convertBlock = new QList<OBlock*>();
 // map of Portals without PortalIcons or misplaced icons
 _badPortalIcon = QMap<QString, Portal*>();
 // map of PortalIcons by portal name
 _portalIconMap = QHash<QString, PortalIcon*>();
 _sysNameBox = new JTextField();
 _userNameBox = new JTextField();
}
CircuitBuilder::~CircuitBuilder()
{
 delete log;
 if(_iconMap)
  delete _iconMap;
}

/*protected*/ QMenu* CircuitBuilder::makeMenu()
{
 _circuitMap =  new QHash<OBlock*, QList<Positionable*>* >();
 OBlockManager* manager = (OBlockManager*) InstanceManager::getDefault("OBlockManager");
 QStringList sysNames = manager->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++)
 {
  OBlock* block = manager->getBySystemName(sysNames.at(i));
  _circuitMap->insert(block,  new QList<Positionable*>());
 }

 // make menus
 checkCircuits();
 _todoMenu =  new QMenu(tr("Error Checks..."));
 makeToDoMenu();
 _circuitMenu = new QMenu(tr("Circuit Builder"));
 makeCircuitMenu();
 connect(_circuitMenu, SIGNAL(aboutToShow()), this, SLOT(makeCircuitMenu()));
 return _circuitMenu;
}

/**
* Add icon 'pos' to circuit 'block'
*/
/*private*/ void CircuitBuilder::addIcon(OBlock* block, Positionable* pos) {
    QList<Positionable*>* icons = _circuitMap->value(block);
    if (icons->isEmpty()) {
        icons = NULL;
    }
    if (pos!=NULL) {
        if (!icons->contains(pos)) {
            icons->append(pos);
        }
        _iconMap->insert(pos, block);
    }
    _circuitMap->insert(block, icons);
    _darkTrack.removeOne(pos);
    if (log->isDebugEnabled()) log->debug("addIcon: block "+block->getDisplayName()+" has "+QString::number(icons->size())+" icons.");
}

// display "todo" (Error correction) items
/*private*/ void CircuitBuilder::makeToDoMenu()
{
 _todoMenu->clear();

 QMenu* blockNeeds = new QMenu(tr("Circuits without icons"));
 _todoMenu->addMenu(blockNeeds);
//    ActionListener editCircuitAction = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                String sysName = event.getActionCommand();
//                editCircuitError(sysName);
//            }
//    };
 if (_bareBlock->size()>0)
 {
  for (int i=0; i<_bareBlock->size(); i++)
  {
   OBlock* block = _bareBlock->at(i);
   QAction* mi = new QAction(tr("Edit \"%1\" Circuit").arg(block->getDisplayName()),this);
//            mi->setActionCommand(block->getSystemName());
//            mi->addActionListener(editCircuitAction);
   EditCircuitActionListener* editCircuitAction = new EditCircuitActionListener(block->getSystemName(), this);

   connect(mi, SIGNAL(triggered()), editCircuitAction, SLOT(actionPerformed()));
   blockNeeds->addAction(mi);
  }
 }
 else
 {
  if (hasOBlocks)
  {
   blockNeeds->addMenu(new QMenu(tr("All circuits (OBlocks) are represented by icons")));
  }
  else
  {
   blockNeeds->addMenu(new QMenu(tr("No Track Circuits (OBlocks) are defined")));
  }
 }

 blockNeeds = new QMenu(tr("Circuits whose icons need conversion"));
 _todoMenu->addMenu(blockNeeds);
 if (_convertBlock->size()>0)
 {
  for (int i=0; i<_convertBlock->size(); i++)
  {
   OBlock* block = _convertBlock->at(i);
   QAction* mi = new QAction( tr("Edit \"%1\" Circuit").arg( block->getDisplayName()),this);
//            mi->setActionCommand(block->getSystemName());
//            mi->layout()->addWidgetActionListener(editCircuitAction);
   EditCircuitActionListener* editCircuitAction = new EditCircuitActionListener(block->getSystemName(), this);
   connect(mi,SIGNAL(triggered()), editCircuitAction, SLOT(actionPerformed()));
   blockNeeds->addAction(mi);
  }
 }
 else
 {
  if (hasOBlocks)
  {
   blockNeeds->addAction(new QAction(tr("All circuits (OBlocks) are represented by Indicator Track icons"),this));
  }
  else
  {
   blockNeeds->addAction(new QAction(tr("No Track Circuits (OBlocks) are defined"),this));
  }
 }
 QAction* iconNeeds;
 if (_unconvertedTrack.size()>0)
 {
  iconNeeds = new QAction(tr("Highlight track icons needing conversion"),this);
//        iconNeeds->addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                QList<Positionable> group = new QList<Positionable>();
//                for (int i=0; i<_unconvertedTrack.size(); i++) {
//                    group->layout()->addWidget(_unconvertedTrack.get(i));
//                }
//                _editor.setSelectionGroup(group);
//            }
//         });
  connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds1()));
 }
 else
 {
  iconNeeds = new QAction(tr("All track icons are Indicator Track icons"),this);
 }
 _todoMenu->addAction(iconNeeds);

 if (_darkTrack.size()>0)
 {
  iconNeeds = new QAction(tr("Highlight indicator tracks without circuits"),this);
//        iconNeeds->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                QList<Positionable> group = new QList<Positionable>();
//                for (int i=0; i<_darkTrack.size(); i++) {
//                    group->layout()->addWidget(_darkTrack.get(i));
//                }
//                _editor.setSelectionGroup(group);
//            }
//         });
  connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds2()));
 }
 else
 {
  if (hasOBlocks)
  {
   iconNeeds = new QAction(tr("Each indicator track icon belongs to a Track Circuit"),this);
  }
  else
  {
   iconNeeds = new QAction(tr("No Track Circuits (OBlocks) are defined"),this);
  }
 }
 _todoMenu->addAction(iconNeeds);

 blockNeeds = new QMenu(tr("Circuits with Portal icons misplaced"));
 _todoMenu->addMenu(blockNeeds);
//    ActionListener portalCircuitAction = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                String sysName = event.getActionCommand();
//                portalCircuitError(sysName);
//            }
//    };
 QSignalMapper* mapper = new QSignalMapper();
 if (_convertBlock->size() > 0)
 {
  for (int i = 0; i < _convertBlock->size(); i++)
  {
      OBlock* block = _convertBlock->at(i);
      QAction* mi = new QAction(tr("Edit \"%1\" Track").arg(block->getDisplayName()),this);
      //mi.setActionCommand(block.getSystemName());
      mapper->setMapping(mi, mi->text() );
      connect(mi, SIGNAL(triggered()), mapper, SLOT(map()));
      //mi.addActionListener(editCircuitAction);

      blockNeeds->addAction(mi);
  }
  connect(mapper, SIGNAL(mapped(QString)), this, SLOT());
 }
 else
 {
  if (hasOBlocks) {
      blockNeeds->addAction(new QAction(tr("All circuits (OBlocks) are represented by Indicator Track icons"),this));
  } else {
      blockNeeds->addAction(new QAction(tr("No Track Circuits (OBlocks) are defined"),this));
  }
 }
 //QAction* iconNeeds;
 if (_unconvertedTrack.size() > 0)
 {
  iconNeeds = new QAction(tr("Highlight circuit track icons needing conversion"),this);
//  iconNeeds.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent event) {
//          ArrayList<Positionable> group = new ArrayList<Positionable>();
//          for (int i = 0; i < _unconvertedTrack.size(); i++) {
//              group.add(_unconvertedTrack.get(i));
//          }
//          _editor.setSelectionGroup(group);
//      }
//  });
  connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds1()));
 }
 else
 {
  iconNeeds = new QAction(tr("circuitIconsConverted"), this);
 }
 _todoMenu->addAction(iconNeeds);

 if (_darkTrack.size() > 0) {
  iconNeeds = new QAction(tr("Highlight indicator tracks without circuits"), this);
//  iconNeeds.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent event) {
//          ArrayList<Positionable> group = new ArrayList<Positionable>();
//          for (int i = 0; i < _darkTrack.size(); i++) {
//              group.add(_darkTrack.get(i));
//          }
//          _editor.setSelectionGroup(group);
//      }
//  });
 connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds2()));
 }
 else
 {
  if (hasOBlocks)
  {
   iconNeeds = new QAction(tr("Each indicator track icon belongs to a Track Circuit"),this);
  }
  else
  {
   iconNeeds = new QAction(tr("No Track Circuits (OBlocks) are defined"),this);
  }
 }
 _todoMenu->addAction(iconNeeds);

 blockNeeds = new QMenu(tr("Portals with no icons or misplaced icons"));
 _todoMenu->addMenu(blockNeeds);
// ActionListener portalCircuitAction = new ActionListener()
// {
//  public void actionPerformed(ActionEvent event) {
//      String portalName = event.getActionCommand();
//      portalCircuitError(portalName);
//  }
// };
 if (_badPortalIcon.size() > 0)
 {
  QSignalMapper* mapper = new QSignalMapper();
  QListIterator<QString> it(_badPortalIcon.keys());
  while (it.hasNext())
  {
   QString portalName = it.next();
   QAction* mi = new QAction(tr("Edit \"%1\" Portals").arg(portalName),this);
      mapper->setMapping(mi, portalName);
      connect(mi, SIGNAL(triggered()), mapper, SLOT(map()));
      //mi.addActionListener(portalCircuitAction);
      blockNeeds->addAction(mi);
  }
  connect(mapper, SIGNAL(mapped(QString)), this, SLOT(portalCircuitError(QString)));
 }
 else
 {
  if (hasOBlocks) {
      blockNeeds->addAction(new QAction(tr("Portal icons positioned OK"),this));
  } else {
      blockNeeds->addAction(new QAction(tr("No Track Circuits (OBlocks) are defined"),this));
  }
 }

 QAction* pError = new QAction(tr("Check Portal & Path Errors"),this);
 _todoMenu->addAction(pError);
 //pError.addActionListener(new ActionListener() {
 //  public void actionPerformed(ActionEvent event) {
 //      errorCheck();
 //  }
 //});
 connect(pError, SIGNAL(triggered()), this, SLOT(errorCheck()));
}
void CircuitBuilder::OnIconNeeds1()
{
 QList<Positionable*>* group = new QList<Positionable*>();
 for (int i=0; i<_unconvertedTrack.size(); i++)
 {
  group->append(_unconvertedTrack.value(i));
 }
 _editor->setSelectionGroup(group);
}

void CircuitBuilder::OnIconNeeds2()
{
 QList<Positionable*>* group = new QList<Positionable*>();
 for (int i=0; i<_darkTrack.size(); i++)
 {
  group->append(_darkTrack.value(i));
 }
 _editor->setSelectionGroup(group);
}

/*private*/ void CircuitBuilder::errorCheck() // SLOT[]
{
 WarrantTableAction::initPathPortalCheck();
 OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 QStringList sysNames = manager->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++)
 {
  WarrantTableAction::checkPathPortals(manager->getBySystemName(sysNames[i]));
 }
 if (!WarrantTableAction::showPathPortalErrors())
 {
//        JOptionPane.showMessageDialog(_editCircuitFrame,
//                tr("blocksEtcOK"), Bundle.getMessage("OK"),
//                javax.swing.JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(_editCircuitFrame, tr("Ok"), tr("Currently defined OBlocks, Portals and Paths are consistent without errors."));
 }
}


/*private*/ void  CircuitBuilder::makeCircuitMenu() {
    _circuitMenu->clear();

    QAction* circuitItem = new QAction(tr("Add Detector Circuit"),this);
    _circuitMenu->addAction(circuitItem);
//    circuitItem->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                newCircuit();
//            }
//        });
    connect(circuitItem, SIGNAL(triggered()), this, SLOT(newCircuit()));
    QAction* editCircuitItem = new QAction(tr("Edit Circuit OBlock"),this);
    _circuitMenu->addAction(editCircuitItem);
    QAction* editPortalsItem = new QAction(tr("Edit Circuit Portals"),this);
    _circuitMenu->addAction(editPortalsItem);
    QAction* editCircuitPathsItem = new QAction(tr("Edit Circuit paths"), this);
    _circuitMenu->addAction(editCircuitPathsItem);
    QAction* editDirectionItem = new QAction(tr("Edit Portal Direction Icons"),this);
            _circuitMenu->addAction(editDirectionItem);
    if ( _circuitMap->keys().size()>0) {
//        editCircuitItem->addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent event) {
//                    editCircuit("editCircuitItem");
//                }
//            });
        connect(editCircuitItem, SIGNAL(triggered()), this, SLOT(editCircuitItem_triggered()));
//        editPortalsItem->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent event) {
//                    editPortals("editPortalsItem");
//                }
//            });
        connect(editPortalsItem, SIGNAL(triggered()), this, SLOT(editPortalItem_triggered()));
//        editCircuitPathsItem->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent event) {
//                    editCircuitPaths("editCircuitPathsItem");
//                }
//            });
        connect(editCircuitPathsItem, SIGNAL(triggered()), this, SLOT(editCircuitPaths_triggered()));
    } else {
        editCircuitItem->setText(tr("No Detector Circuits are defined"));
        editPortalsItem->setText(tr("No Detector Circuits are defined"));
        editCircuitPathsItem->setText(tr("No Detector Circuits are defined"));
    }

    _circuitMenu->addMenu(_todoMenu);
}
void CircuitBuilder::editCircuitItem_triggered()
{
 editCircuit(tr("Edit Circuit OBlock"));
}
void CircuitBuilder::editPortalItem_triggered()
{
 editPortals(tr("Edit Circuit Portals"));
}
void CircuitBuilder::editCircuitPaths_triggered()
{
 editCircuitPaths("Edit Circuit paths");
}

/**************** Set up editing Frames *****************/

/*protected*/ void CircuitBuilder::newCircuit()
{
 if (editingOK())
 {
  addCircuitDialog();
  if (_currentBlock!=NULL)
  {
   if (_editCircuitFrame==NULL)
   {
    checkCircuits();
    _editor->setSelectionGroup(NULL);
    _editor->disableMenus();
    EditScene* targetPane = (EditScene*)_editor->getTargetPanel();
//    targetPane.setSelectGroupColor(_editGroupColor);
//    targetPane.setHighlightColor(_editGroupColor);
    _editCircuitFrame = new EditCircuitFrame(tr("Add Detector Circuit"), this, _currentBlock);
   }
  }
 }
}

/*protected*/ void CircuitBuilder::editCircuit(QString title)
{
 if (editingOK())
 {
  editCircuitDialog(title);
  if (_currentBlock!=NULL)
  {
   checkCircuits();
   makeSelectionGroup(_currentBlock, NULL);
   _editor->disableMenus();
   EditScene* targetPane = (/*TargetPane*/EditScene*)_editor->getTargetPanel();
//   targetPane.setSelectGroupColor(_editGroupColor);
//   targetPane.setHighlightColor(_editGroupColor);
   _editCircuitFrame = new EditCircuitFrame(tr("Edit \"%1\" Circuit"), this, _currentBlock);
  }
 }
}
#if 1
/*private*/ void CircuitBuilder::editCircuitError(QString sysName)
{
 if (editingOK())
 {
  //_currentBlock = InstanceManager::oBlockManagerInstance().getBySystemName(sysName);
  _currentBlock = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysName);
  if (_currentBlock!=NULL)
  {
   checkCircuits();
   makeSelectionGroup(_currentBlock, NULL);
   _editor->disableMenus();
   _editCircuitFrame = new EditCircuitFrame(tr("OpenCircuitItem"), this, _currentBlock);
  }
 }
}
#endif
/*protected*/ void CircuitBuilder::editPortals(QString title)
{
 if (editingOK())
 {
#if 1
  editCircuitDialog(title);
  if (_currentBlock != NULL)
  {
   checkCircuits();
   _circuitIcons = _circuitMap->value(_currentBlock);
   // check icons to be indicator type
   if (!iconsConverted(_currentBlock)) {
       queryConvertIcons(_currentBlock);
   }
   _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
   _editor->disableMenus();
#if 0
   EditScene* targetPane =  _editor->getTargetPanel();
   targetPane->setSelectGroupColor(_editGroupColor);
   targetPane->setHighlightColor(_highlightColor);
#endif
   _editPortalFrame = new EditPortalFrame("Edit \"%1\" Portals",this, _currentBlock, false);
  }
#endif
 }
}

/*private*/ void CircuitBuilder::portalCircuitError(QString portalName)
{
 if (editingOK())
 {
  PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
  Portal* portal = portalMgr->getByUserName(portalName);
  if (portal == NULL)
  {
//      JOptionPane.showMessageDialog(_editor, Bundle.getMessage("noSuchPortal", portalName),
//              Bundle.getMessage("ErrorPortal"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::critical(_editor, tr("Error Portal"), tr("There is no portal called \"%1\".").arg(portalName));
      return;
  }
  _currentBlock = portal->getToBlock();
  OBlock* adjacentBlock = NULL;
  if (_currentBlock == NULL) {
      _currentBlock = portal->getFromBlock();
  } else {
      adjacentBlock = portal->getFromBlock();
  }
  if (adjacentBlock == NULL) {
//      JOptionPane.showMessageDialog(_editor, Bundle.getMessage("invalidPortal", portalName, _currentBlock),
//              Bundle.getMessage("ErrorPortal"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::critical(_editor, tr("Error Portal"), tr("Portal \"%1\" attached to OBlock \"%2\" invalid - only one block. ").arg(portalName).arg(_currentBlock->getDisplayName()));
      return;
  }
  if (_currentBlock != NULL) {
      // check icons to be indicator type
      _circuitIcons = _circuitMap->value(_currentBlock);
      if (!iconsConverted(_currentBlock)) {
          queryConvertIcons(_currentBlock);
      }
      _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, false));
      _editor->setSecondSelectionGroup(makeSelectionGroup(adjacentBlock, false));
      _editor->disableMenus();
#if 0
      TargetPane targetPane = (TargetPane) _editor.getTargetPanel();
      targetPane.setSelectGroupColor(_editGroupColor);
      targetPane.setHighlightColor(_highlightColor);
#endif
      PortalIcon* icon = _portalIconMap.value(portalName);
      if (icon != NULL) {
          icon->setStatus(PortalIcon::VISIBLE);
      }
      setPortalsPositionable(_currentBlock, true);
      _editPortalFrame = new EditPortalFrame("Edit \"&1\" Portals", this,
              _currentBlock, portal, adjacentBlock);
  }
}
}
/*protected*/ void CircuitBuilder::editPortalDirection(QString title)
{
 if (editingOK())
 {
  editCircuitDialog(title);
  if (_currentBlock != NULL)
  {
   checkCircuits();
   _circuitIcons = _circuitMap->value(_currentBlock);
   // check icons to be indicator type
   if (!iconsConverted(_currentBlock)) {
       queryConvertIcons(_currentBlock);
   }
   _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
   _editor->disableMenus();
#if 0 // TODO:
   TargetPane targetPane = (TargetPane) _editor.getTargetPanel();
   targetPane.setSelectGroupColor(_editGroupColor);
   targetPane.setHighlightColor(_highlightColor);
#endif
   setPortalsPositionable(_currentBlock, true);
   _editDirectionFrame = new EditPortalDirection(tr("Edit \"%1\" Portal Direction Arrows"), this, _currentBlock);
  }
 }
}
/*protected*/ void CircuitBuilder::editCircuitPaths(QString title) {
 if (editingOK())
 {
#if 1
  editCircuitDialog(title);
  if (_currentBlock!=NULL)
  {
   checkCircuits();
   // check icons to be indicator type
   _circuitIcons = _circuitMap->value(_currentBlock);
   if( !iconsConverted(_currentBlock))
   {
    queryConvertIcons(_currentBlock);
   }
   // must have converted icons for paths
   if (!iconsConverted(_currentBlock))
   {
//    JOptionPane.showMessageDialog(_editor, Bundle.getMessage("needConversion", _currentBlock.getDisplayName()),
//               Bundle.getMessage("noIcons"), JOptionPane.INFORMATION_MESSAGE);
    QMessageBox::information(_editor, tr("No Icons"), tr("Block circuit \"%1\" needs to convert track icons to Indicator Track icons\nUse \"Edit Track Circuit\" menu to convert icons.").arg(_currentBlock->getDisplayName()));
   }
   else
   {
    _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
    _currentBlock->setState(OBlock::UNOCCUPIED);
    // A temporary path "TEST_PATH" is used to display the icons representing a path
    _currentBlock->allocate(EditCircuitPaths::TEST_PATH);
    _editor->disableMenus();
    EditScene* targetPane = (EditScene*)_editor->getTargetPanel();
//                targetPane->setSelectGroupColor(_editGroupColor);
//                targetPane->setHighlightColor(_editGroupColor);
    _editPathsFrame = new EditCircuitPaths(tr("OpenPathTitle"), this, _currentBlock);
   }
  }
#endif
 }
}

/*
private void addPortalIcons() {
    Iterator<PortalIcon> it = _portalIcons.iterator();
    while (it.hasNext()) {
        PortalIcon pi = it.next();
        pi.setStatus(PortalIcon.HIDDEN);
        _editor.putItem(pi);
    }
}
*/

/*private*/ void CircuitBuilder::removePortalIcons() {
    QListIterator<PortalIcon*> it(*_portalIcons);
    while (it.hasNext()) {
        _editor->removeFromContents((Positionable*)it.next());
    }
}

/*private*/ bool CircuitBuilder::editingOK()
{
 if (_editCircuitFrame!=NULL || _editPathsFrame!=NULL || _editPortalFrame!=NULL)
 {
  // Already editing a circuit, ask for completion of that edit
//        JOptionPane.showMessageDialog(_editCircuitFrame,
//                tr("AlreadyEditing"), Bundle.getMessage("errorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editCircuitFrame, tr("Error"), tr("Editing a Detection Circuit in progress.  Please complete before starting a new edit."));
  if (_editPathsFrame!=NULL)
  {
   _editPathsFrame->toFront();
   _editPathsFrame->setVisible(true);
  }
  else if (_editCircuitFrame!=NULL)
  {
   _editCircuitFrame->toFront();
   _editCircuitFrame->setVisible(true);
  }
  else if (_editPortalFrame!=NULL)
  {
   _editPortalFrame->toFront();
   _editPortalFrame->setVisible(true);
  }
  return false;
 }
 return true;
}

/**
* Create a new OBlock
* Used by New to set up _editCircuitFrame
* Sets _currentBlock to created new OBlock
*/
/*private*/ void CircuitBuilder::addCircuitDialog()
{
 //_dialog = new QDialog(_editor, tr("New Track Circuit (OBlock)"), true);
 _dialog = new JDialog();
 _dialog->setWindowTitle(tr("New Track Circuit (OBlock)"));
 _dialog->setLayout(new QVBoxLayout);
    QWidget* panel = new QWidget();
    panel->setLayout(new BorderLayout(10));
    QWidget* mainPanel = new QWidget();
    mainPanel->setLayout(new QVBoxLayout(mainPanel/*, BoxLayout.Y_AXIS*/));

    ((QBoxLayout*)mainPanel->layout())->addStrut(STRUT_SIZE);
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
    p->layout()->addWidget(new QLabel(tr("Create an OBlock track circuit")));
    mainPanel->layout()->addWidget(p);

    ((QBoxLayout*)mainPanel->layout())->addStrut(STRUT_SIZE);
    mainPanel->layout()->addWidget(makeSystemNamePanel());
    ((QBoxLayout*)mainPanel->layout())->addStrut(STRUT_SIZE);
    mainPanel->layout()->addWidget(makeDoneButtonPanel(true));
    panel->layout()->addWidget(mainPanel);
    _dialog->layout()->addWidget(panel);
    _dialog->move(_editor->pos().x()+100, _editor->pos().y()+100);
    _dialog->pack();
    _dialog->setVisible(true);
    _dialog->resize(300,250);
    _dialog->exec();
}

/**
* Edit existing OBlock
* Used by edit to set up _editCircuitFrame
* Sets _currentBlock to chosen OBlock or NULL if none selected
*/
/*private*/ void CircuitBuilder::editCircuitDialog(QString title)
{
 //_dialog = new QDialog(_editor, tr(title), true);
 _dialog = new JDialog();
    _dialog->setWindowTitle(title);
    _dialog->setLayout(new QVBoxLayout);
    QWidget* panel = new QWidget();
    panel->setLayout(new BorderLayout(10));
    QWidget* mainPanel = new QWidget();
    mainPanel->setLayout(new QVBoxLayout(mainPanel/*, BoxLayout.Y_AXIS*/));

    ((QBoxLayout*)mainPanel->layout())->addStrut(STRUT_SIZE);
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
    p->layout()->addWidget(new QLabel(tr("Select an OBlock track circuit")));
    mainPanel->layout()->addWidget(p);

    _oblockModel = PickListModel::oBlockPickModelInstance();
    QTableView* table = _oblockModel->makePickTable();
    mainPanel->layout()->addWidget(/*new JScrollPane*/(table));
    ((QBoxLayout*)mainPanel->layout())->addStrut(STRUT_SIZE);
    mainPanel->layout()->addWidget(makeDoneButtonPanel(false));
    panel->layout()->addWidget(mainPanel);
    _dialog->/*getContentPane()->*/layout()->addWidget(panel);
    _dialog->move(_editor->pos().x()+100, _editor->pos().y()+100);
    _dialog->pack();
    _dialog->resize(300,400);
    _dialog->setVisible(true);
    _dialog->exec();
}

/*private*/ QWidget* CircuitBuilder::makeSystemNamePanel() {
    _sysNameBox->setText("");
    _sysNameBox->setToolTip(tr("OBlock name, i.e. OB1; \"OB\" will be prepended if not present!"));
    _userNameBox->setText("");
    QWidget* namePanel = new QWidget();
    namePanel->setLayout(new QVBoxLayout(namePanel/*, BoxLayout.Y_AXIS*/));
    QWidget* p = new QWidget();
    QGridLayout* g;
    p->setLayout(g =new QGridLayout());
//    java.awt.GridBagConstraints c = new java.awt.GridBagConstraints();
//    c.gridwidth  = 1;
//    c.gridheight = 1;
//    c.gridx = 0;
//    c.gridy = 0;
//    c.anchor = java.awt.GridBagConstraints.EAST;
    g->addWidget(new QLabel(tr("System Name")), 0,0, 1,1);
//    c.gridy = 1;
    g->addWidget(new QLabel(tr("User Name")),1,0,1,1);
//    c.gridx = 1;
//    c.gridy = 0;
//    c.anchor = java.awt.GridBagConstraints.WEST;
//    c.weightx = 1.0;
//    c.fill = java.awt.GridBagConstraints.HORIZONTAL;  // text field will expand
    g->addWidget(_sysNameBox,0,1,1,1);
//    c.gridy = 1;
    g->addWidget(_userNameBox,1,1,1,1);
    namePanel->layout()->addWidget(p);
    return namePanel;
}

/*private*/ QWidget*  CircuitBuilder::makeDoneButtonPanel(bool add) {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QHBoxLayout);
    QWidget* panel0 = new QWidget();
    panel0->setLayout(new FlowLayout());
    QPushButton* doneButton;
    if (add)
    {
     doneButton = new QPushButton(tr("Add OBlock Circuit"));
//        doneButton->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    if (doAddAction()) {
//                        _dialog->dispose();
//                    }
//                }
//        });
     connect(doneButton, SIGNAL(clicked()), this, SLOT(doneButton_clicked()));
     QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
     sizePolicy.setHorizontalStretch(0);
     sizePolicy.setVerticalStretch(0);
     sizePolicy.setHeightForWidth(doneButton->sizePolicy().hasHeightForWidth());
     doneButton->setSizePolicy(sizePolicy);

    }
    else
    {
     doneButton = new QPushButton(tr("Show OBlock"));
//        doneButton->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    if (doOpenAction()) {
//                        _dialog->dispose();
//                    }
//                }
//        });
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(doneButton->sizePolicy().hasHeightForWidth());
        doneButton->setSizePolicy(sizePolicy);
        connect(doneButton, SIGNAL(clicked()), this, SLOT(showDoneButton_clicked()));
        doneButton->setSizePolicy(sizePolicy);
    }
    panel0->layout()->addWidget(doneButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _sysNameBox.setText("");
//                _currentBlock = NULL;
//                _dialog->dispose();
//            }
//    });
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
    cancelButton->setSizePolicy(sizePolicy);
    panel0->layout()->addWidget(cancelButton);
    buttonPanel->layout()->addWidget(panel0);
    return buttonPanel;
}
void CircuitBuilder::cancelButton_clicked()
{
 _sysNameBox->setText("");
 _currentBlock = NULL;
 //_dialog->dispose();
 _dialog->reject();
 _dialog->close();
}
void CircuitBuilder::doneButton_clicked()
{
 if (doAddAction())
 {
  //_dialog->dispose();
  _dialog->accept();
  _dialog->close();
 }
}

void CircuitBuilder::showDoneButton_clicked()
{
 if (doOpenAction())
 {
  //_dialog->dispose();
  _dialog->accept();
  _dialog->close();
 }
}

/*private*/ bool CircuitBuilder::doAddAction()
{
 bool retOK = false;
 QString sysname = _sysNameBox->text();
 if (sysname != "" && sysname.length() >= 1)
 {
  QString uname = _userNameBox->text();
  if (uname!="" && uname.trimmed().length()==0)
  {
   uname = "";
  }
  _currentBlock =((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->createNewOBlock(sysname, uname);
  if (_currentBlock!=NULL)
  {
   retOK = true;
  }
  else
  {
//            int result = JOptionPane.showConfirmDialog(_editor, java.text.MessageFormat.format(
//                            tr("blockExists"), sysname),
//                            tr("AskTitle"), JOptionPane.YES_NO_OPTION,
//                            JOptionPane.QUESTION_MESSAGE);
//            if (result==JOptionPane.YES_OPTION) {
   int result = QMessageBox::question(_editor, tr("What shall we do?"), tr("Circuit \"%1\" already exists.  Do you want to edit it?").arg(sysname), QMessageBox::Yes | QMessageBox::No);
   if(result == QMessageBox::Yes)
   {
    _currentBlock = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysname);
    if (_currentBlock==NULL) {
        retOK = false;
    }
    checkCircuits();
    _editor->setSelectionGroup(_circuitMap->value(_currentBlock));
    _editCircuitFrame = new EditCircuitFrame(tr("Edit \"%1\" Circuit"), this, _currentBlock);
    retOK = true;
   }
  }
 }
 if (!retOK)
 {
//        JOptionPane.showMessageDialog(_editor, tr("createOBlock"),
//                tr("NeedDataTitle"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(_editor, tr("Create an OBlock track circuit"),tr("Please Enter Data"));
 }
 return retOK;
}

/*private*/ bool CircuitBuilder::doOpenAction()
{
 int row = _oblockModel->getTable()->currentIndex().row();
 if (row >= 0) {
    _currentBlock = (OBlock*)_oblockModel->getBeanAt(row);
    return true;
 } else {
//        JOptionPane.showMessageDialog(_editor, tr("selectOBlock"),
//                        tr("NeedDataTitle"), JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(_editor, tr("Please Enter Data"), tr("Select an OBlock track circuit"));
 }
 _currentBlock = NULL;
 return false;
}

/**
 * ************************ end setup frames *****************************
 */
/*private*/ void CircuitBuilder::setPortalsPositionable(OBlock* block, bool set)
{
 QList<Positionable*>* circuitIcons = _circuitMap->value(block);
 QListIterator<Positionable*> iter(*circuitIcons);
 while (iter.hasNext())
 {
  Positionable* p = iter.next();
  //if (p instanceof PortalIcon)
  if(qobject_cast<PortalIcon*>(p) != NULL)
  {
      p->setPositionable(set);
  }
 }
}

/************************* Closing Editing Frames ********************/

/**
* Update block data in menus
*/
/*protected*/ void CircuitBuilder::checkCircuitFrame(OBlock* block)
{
 if (block!=NULL)
 {
  QList<Positionable*>* group = _editor->getSelectionGroup();
  // check icons to be indicator type
  setIconGroup(block, group);
  if (!iconsConverted(block))
  {
   queryConvertIcons(block);
  }
 }
 closeCircuitFrame();
}

/*protected*/ void CircuitBuilder::closeCircuitFrame() {
    _editCircuitFrame = NULL;
    closeCircuitBuilder();
}

/**
*  Edit frame closing, set block's icons
*/
/*private*/ void CircuitBuilder::setIconGroup(OBlock* block, QList<Positionable*>* selections)
{
 QList<Positionable*>* oldIcons = _circuitMap->value(block);
 if (oldIcons!=NULL)
 {
  for (int i=0; i<oldIcons->size(); i++)
  {
   Positionable* pos = oldIcons->value(i);
   //if (pos instanceof IndicatorTrack)
   if(qobject_cast<IndicatorTrack*>(pos)!= NULL)
   {
    ((IndicatorTrack*)pos)->setOccBlockHandle(NULL);
   }
   _iconMap->remove(pos);
  }
 }
 // the selectionGroup for all edit frames is full collection of icons
 // comprising the block.  Gather them and store in the block's hashMap
 QList<Positionable*>* icons = new QList<Positionable*>();
 if (selections!=NULL)
 {
  if (log->isDebugEnabled()) log->debug("setIconGroup: selectionGroup has "+
                QString::number(selections->size())+" icons.");
  NamedBeanHandle<OBlock*>* handle = new NamedBeanHandle<OBlock*>(block->getSystemName(), block);
  for (int i=0; i<selections->size(); i++)
  {
   Positionable* pos = selections->value(i);
   //if (pos instanceof IndicatorTrack)
   if(qobject_cast<IndicatorTrack*>(pos)!= NULL)
   {
                ((IndicatorTrack*)pos)->setOccBlockHandle(handle);
            }
            icons->append(pos);
            _iconMap->insert(pos, block);
        }
        QList<Portal*> portals = block->getPortals();
        for (int i=0; i<portals.size(); i++) {
            PortalIcon* icon = _portalIconMap.value(portals.value(i)->getName());
            if (icon!=NULL) {
                _iconMap->insert((Positionable*)icon, block);
            }
        }
    }
    _circuitMap->insert(block, icons);
    if (log->isDebugEnabled()) log->debug("setIconGroup: block "+block->getDisplayName()+
                                        " has "+QString::number(icons->size())+" icons.");
}

/*protected*/ void CircuitBuilder::closePathFrame(OBlock* /*block*/) {
    _currentBlock->deAllocate(NULL);
    _editPathsFrame = NULL;
    closeCircuitBuilder();
}

/*protected*/ void CircuitBuilder::closePortalFrame(OBlock* /*block*/) {
    _editPortalFrame = NULL;
    closeCircuitBuilder();
}

/*protected*/ void CircuitBuilder::closePortalDirection(OBlock* block)
{
 setPortalsPositionable(block, false);
 _editDirectionFrame = NULL;
 closeCircuitBuilder();
}
/*private*/ void CircuitBuilder::closeCircuitBuilder() {
    _circuitIcons = new QList<Positionable*>();
    _currentBlock = NULL;
    checkCircuits();
    makeToDoMenu();
    makeCircuitMenu();
    removePortalIcons();
    _editor->resetEditor();
}
/**************** end closing frames ********************/


/**
* Find the blocks with no icons and the blocks with icons that need conversion
* Setup for main Frame - used in both initialization and close of an editing frame
* Build Lists that are used to create menu items
*/
/*private*/ void CircuitBuilder::checkCircuits()
{
 _portalIconMap.clear();
 _darkTrack.clear();
 _unconvertedTrack.clear();
 PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");

 QListIterator<Positionable*> it(_editor->getContents());
 while (it.hasNext())
 {
  Positionable* pos = it.next();
//            if (log->isDebugEnabled()) log->debug("class: "+pos.getClass().getName());
  //if (pos instanceof IndicatorTrack)
  if(qobject_cast<IndicatorTrack*>(pos) != NULL)
  {
   OBlock* block = ((IndicatorTrack*)pos)->getOccBlock();
//            ((IndicatorTrack*)pos)->removePath(EditCircuitPaths::TEST_PATH);
   if (block!=NULL)
   {
    addIcon(block, pos);
   }
   else
   {
    _darkTrack.append(pos);
   }
  }
  //else if (pos instanceof PortalIcon)
  else if(qobject_cast<PortalIcon*>(pos)!= NULL)
  {
   PortalIcon* pIcon = (PortalIcon*) pos;
   QString name = pIcon->getName();
   Portal* portal = portalMgr->getByUserName(name);
   if (portal == NULL)
   {
    log->error("No Portal for PortalIcon called \"" + name + "\". Discarding icon.");
    pIcon->remove();
   }
   else
   {
    PortalIcon* pi = _portalIconMap.value(name);
    if (pi != NULL) {
        log->error("Removing duplicate PortalIcon for Portal \"" + name + "\".");
        pi->remove();
    }
    _portalIconMap.insert(name, pIcon);
   }
  } else if (isUnconvertedTrack(pos)) {
   if (!_unconvertedTrack.contains(pos)) {
       _unconvertedTrack.append(pos);
   }
  }
 }
 QListIterator<QList<Positionable*>* > iters(_circuitMap->values());
 while (iters.hasNext())
 {
  //iters.next();
  QListIterator<Positionable*> iter( *iters.next());
  while (iter.hasNext())
  {
   Positionable* pos = iter.next();
   if (isUnconvertedTrack(pos))
   {
    if (!_unconvertedTrack.contains(pos)) {
        _unconvertedTrack.append(pos);
    }
   }
  }
 }
 _bareBlock = new QList<OBlock*>();
 _convertBlock = new QList<OBlock*>();
 _badPortalIcon =  QMap<QString, Portal*>();
 OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 QStringList sysNames = manager->getSystemNameArray();
 hasOBlocks = (sysNames.length()>0);
 for (int i = 0; i < sysNames.length(); i++) {
     OBlock* block = manager->getBySystemName(sysNames[i]);
     QList<Positionable*>* icons = _circuitMap->value(block);
     if (log->isDebugEnabled()) log->debug("checkCircuits: block "+block->getDisplayName()
                                         +" has "+QString::number(icons->size())+" icons.");
     if (icons==NULL || icons->size()==0) {
         _bareBlock->append(block);
     } else {
         for (int k=0; k<icons->size(); k++) {
             Positionable* pos = icons->at(k);
             //if (!(pos instanceof IndicatorTrack) && !(pos instanceof PortalIcon))
             if(qobject_cast<IndicatorTrack*>(pos) == NULL && qobject_cast<PortalIcon*>(pos)== NULL)
             {
                 if (!_convertBlock->contains(block)) {
                     _convertBlock->append(block);
                     break;
                 }
             }
         }
         QList<Portal*> list = block->getPortals();
         //int iconCount = 0;
         if (/*list!=NULL &&*/ list.size()>0) {
             for (int k=0; k<list.size(); k++) {
                 PortalIcon* pi = _portalIconMap.value(list.at(k)->getName());
                 if (pi!=NULL) {
                     //iconCount++;
                     addIcon(block, (Positionable*)pi);
//                        if (!EditPortalFrame::portalIconOK(icons, pi)) {
//                            if (!_portalMisplacedBlock->contains(block)) {
//                                _portalMisplacedBlock->add(block);
//                            }
//                        }
                 }
             }
         }
         // make map of all Portals
         QList <Portal*> pList = block->getPortals();
         for (int k=0; k<pList.size(); k++) {
             Portal* portal = pList.at(k);
             _portalMap.insert(portal->getName(), portal);
         }
}
    }
}   // end checkCircuits

/*************** Frame Utilities **************/

/**
* Used by Portal Frame
*/
/*protected*/ QList<Positionable*>* CircuitBuilder::getCircuitIcons(OBlock* block) {
    return _circuitMap->value(block);
}

/**
* Used by Portal Frame
*/
/*protected*/ OBlock* CircuitBuilder::getBlock(Positionable* pos) {
    return _iconMap->value(pos);
}

/**
* Used by Path Frame
*/
/*protected*/ QList<Positionable*>* CircuitBuilder::getCircuitGroup() {
    return _circuitIcons;
}
#if 1
/**
* Used by Portal Frame
*/
/*protected*/ QHash<QString, PortalIcon*> CircuitBuilder::getPortalIconMap() {
    return _portalIconMap;
}

/*protected*/ Portal* CircuitBuilder::getPortalByName(QString name) {
    return _portalMap.value(name);
}

/*protected*/ void CircuitBuilder::changePortalName(QString oldName, QString newName) {
    PortalIcon* icon = _portalIconMap.value(oldName);
    Portal* portal = _portalMap.value(oldName);
    _portalMap.remove(oldName);
    _portalIconMap.remove(oldName);
    _portalMap.insert(newName, portal);
    _portalIconMap.insert(newName, icon);
}

/*protected*/ void CircuitBuilder::removePortal(QString name) {
    _portalMap.remove(name);
    _portalIconMap.remove(name);
}
#endif
/*protected*/ void CircuitBuilder::addPortalIcon(PortalIcon* icon) {
    //Portal portal = icon.getPortal();
    QString name = icon->getName();
    // Eliminate possible duplicate icons for this portal
    if(!_portalIconMap.contains(name)) {
        _portalMap.insert(name, icon->getPortal());
        _portalIconMap.insert(name, icon);
        _portalIcons->append(icon);
    }
    //
    if (_circuitIcons!=NULL) {
        _circuitIcons->append((Positionable*)icon);
    }
}

/*public*/ QList<PortalIcon*>* CircuitBuilder::getPortalIcons() {
    return _portalIcons;
}
#if 0
/**
* Remove block, but keep the track icons. Set block reference in icon NULL
*/
protected void removeBlock (OBlock block) {
    java.util.List<Positionable> list = _circuitMap->get(block);
    if (list!=NULL) {
        for (int i=0; i<list.size(); i++) {
            Positionable pos = list.get(i);
            if (pos instanceof IndicatorTrack) {
                ((IndicatorTrack)pos).setOccBlockHandle(NULL);
            } else if (pos instanceof PortalIcon) {
                pos.remove();
            }
            _darkTrack.add(pos);
        }
    }
//        InstanceManager.oBlockManagerInstance().deregister(block);
    _circuitMap->remove(block);
    block.dispose();
}

/***************** Overriden methods of Editor *******************/

/*public*/ void paintTargetPanel(Graphics g) {
    Graphics2D g2d = (Graphics2D)g;
    if (_circuitIcons!=NULL){
        java.awt.Stroke stroke = g2d.getStroke();
        Color color = g2d.getColor();
        g2d.setColor(_editGroupColor);
        g2d.setStroke(new java.awt.BasicStroke(2.0f));
        for(int i=0; i<_circuitIcons->size();i++){
            g.drawRect(_circuitIcons->get(i).getX(), _circuitIcons->get(i).getY(),
                       _circuitIcons->get(i).maxWidth(), _circuitIcons->get(i).maxHeight());
        }
        g2d.setColor(color);
        g2d.setStroke(stroke);
    }
}
/*
/*public*/ void setAllEditable(boolean state) {
    _editable = state;
    for (int i = 0; i<_contents.size(); i++) {
        _contents.get(i).setEditable(state);
    }
    _editor.setSelectionGroup(NULL);
}

/********************* convert plain track to indicator track **************/

#endif
/**
 * Check if the block being edited has all its icons converted to indicator
 * icons
 */
/*private*/ bool CircuitBuilder::iconsConverted(OBlock* block) {
    if (block == NULL) {
        return true;
    }
    QList<Positionable*>* list = _circuitMap->value(block);
    if (list != NULL && list->size() > 0)
    {
        for (int i = 0; i < list->size(); i++)
        {
            Positionable* pos = list->at(i);
            //if (!(pos instanceof IndicatorTrack) && !(pos instanceof PortalIcon))
            if(qobject_cast<IndicatorTrack*>(pos) != NULL && qobject_cast<PortalIcon*>(pos) != NULL)
            {
                if (log->isDebugEnabled()) {
                    log->debug("icon needs Convertion " + QString(pos->metaObject()->className()));
                }
                return false;
            }
        }
    }
    return true;
}

/**
 * Icons need conversion. ask if user wants to convert them
 */
/*private*/ void CircuitBuilder::queryConvertIcons(OBlock* block) {
    if (block == NULL) {
        return;
    }
    QList<Positionable*>* list = _circuitMap->value(block);
    if (list != NULL && list->size() > 0)
    {
//        int result = JOptionPane.showConfirmDialog(_editor, Bundle.getMessage("notIndicatorIcon"),
//                Bundle.getMessage("incompleteCircuit"), JOptionPane.YES_NO_OPTION,
//                JOptionPane.QUESTION_MESSAGE);
     int result = QMessageBox::question(_editor,tr("Track Circuit Incomplete"), tr("Not all of the track icons are indicator icons.  Do you want to convert them?"), QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            convertIcons(_circuitMap->value(block));
        }
    } else {
//        JOptionPane.showMessageDialog(_editor, Bundle.getMessage("needIcons", block.getDisplayName()),
//                Bundle.getMessage("noIcons"), JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(_editor, tr("Information"), tr("Block circuit \"%1\" needs at least one track icon.\n Use \"Edit Track Circuit\" to add Indicator Track icons.").arg(block->getDisplayName()));
    }
}


/*protected*/ void CircuitBuilder::convertIcons(QList<Positionable*>* iconList)
{
    if (iconList == NULL || iconList->size() == 0) {
        return;
    }
    // use global member for finishConvert to remove and add converted icons,
    _circuitIcons = iconList;
    // since iconList will be modified, use a copy to find unconverted icons
    QList<Positionable*>* list =  new QList<Positionable*>();
    for (int i = 0; i < iconList->size(); i++) {
        list->append(iconList->at(i));
    }
    if (list->size() > 0)
    {
//        TargetPane targetPane = (TargetPane) _editor.getTargetPanel();
//        targetPane.setHighlightColor(_highlightColor);

        for (int i = 0; i < list->size(); i++) {
            Positionable* pos = list->at(i);
            //if (!(pos instanceof IndicatorTrack) && !(pos instanceof PortalIcon))
            if(qobject_cast<IndicatorTrack*>(pos) == NULL && qobject_cast<PortalIcon*>(pos) == NULL)
            {
                if (log->isDebugEnabled()) {
                    log->debug("convertIcons: #" + QString::number(i) + " pos= " + QString(pos->metaObject()->className()));
                }
                convertIcon(pos);
            }
        }
//        targetPane.setHighlightColor(_editGroupColor);
//        _editor.highlight(NULL);
    }
}

/*private*/ void CircuitBuilder::convertIcon(Positionable* pos)
{
 _oldIcon = (PositionableLabel*)pos;
 _editor->highlight((Positionable*)_oldIcon);
 _editor->toFront();
//    _editor.repaint();
    //if (pos instanceof TurnoutIcon)
 if(qobject_cast<TurnoutIcon*>(pos)!= NULL)
 {
  makePalettteFrame("IndicatorTO");
  _trackTOPanel = new IndicatorTOItemPanel(_convertFrame, "IndicatorTO", NULL, NULL, _editor, (QWidget*)this);
  _convertDialog->layout()->addWidget(_trackTOPanel);
//        ActionListener updateAction = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                convertTO();
//            }
//        };
  TOPActionListener* updateAction = new TOPActionListener(true, this);
     _trackTOPanel->init(updateAction);
     _convertDialog->layout()->addWidget(_trackTOPanel);
    } else {
        makePalettteFrame("IndicatorTrack");
        _trackPanel = new IndicatorItemPanel(_convertFrame, "IndicatorTrack", NULL, _editor, (QWidget*)this);
//            _convertDialog->add(_trackPanel);
//        ActionListener updateAction = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                convertSeg();
//            }
//        };
        TOPActionListener* updateAction = new TOPActionListener(false, this);
        _trackPanel->init(updateAction);
        _convertDialog->layout()->addWidget(_trackPanel);
  }
  // _convertDialog->pack();
  _convertDialog->setVisible(true);
 _editor->repaint();
}
TOPActionListener::TOPActionListener(bool bIsTO, CircuitBuilder *parent)
{
 this->bIsTO = bIsTO;
 this->parent = parent;
}
void TOPActionListener::actionPerformed(ActionEvent */*e*/)
{
 if(bIsTO)
  parent->convertTO();
 else
  parent->convertSeg();
}

/*private*/ void CircuitBuilder::makePalettteFrame(QString title) {
    ItemPalette::loadIcons();
//    _convertDialog = new JmriJFrame(_editor, tr("EditItem"), Bundle.getMessage(title)), true);
    _convertDialog = new QDialog();
    _convertDialog->setWindowTitle( tr("Edit %1 Icon").arg(title));
    _convertFrame = new convertFrame(_convertDialog, this);

//    _convertDialog->setLocationRelativeTo(_editor);
//    _convertDialog->toFront();
}

/*
 * gimmick to get JDialog to re-layout contents and repaint
 */
//static class convertFrame extends JmriJFrame {
//    JDialog _dialog;
convertFrame::convertFrame (QDialog* dialog, CircuitBuilder* parent) :JmriJFrame(false, false)
{
 //super(false, false);
  _dialog = dialog;
  this->parent = parent;
}

/*public*/ void convertFrame::pack() {
    JmriJFrame::pack();
//        _dialog->pack();
}
//};

/*private*/ void CircuitBuilder::convertTO() {
    IndicatorTurnoutIcon* t = new IndicatorTurnoutIcon(_editor);
    t->setOccBlockHandle(new NamedBeanHandle<OBlock*>(_currentBlock->getSystemName(), _currentBlock));
    t->setTurnout( ((TurnoutIcon*)_oldIcon)->getNamedTurnout());
    t->setFamily(_trackTOPanel->getFamilyName());

    QHash <QString, QHash <QString, NamedIcon*>*>* iconMap = _trackTOPanel->getIconMaps();
    QHashIterator<QString, QHash<QString, NamedIcon*>*> it(*iconMap);
    while (it.hasNext())
    {
        //Entry<String, QHash<String, NamedIcon>> entry = it.next();
        it.next();
        QString status = it.key();
        QHashIterator<QString, NamedIcon*> iter(* it.value());
        while (iter.hasNext())
        {
            //Entry<String, NamedIcon> ent = iter.next();
            iter.next();
            t->setIcon(status, iter.key(), new NamedIcon(iter.value()));
        }
    }
    t->setLevel(Editor::TURNOUTS);
    t->setScale(_oldIcon->getScale());
    t->rotate(_oldIcon->getDegrees());
    finishConvert((Positionable*)t);
}
/*private*/ void CircuitBuilder::convertSeg() // SLOT[]
{
    IndicatorTrackIcon* t = new IndicatorTrackIcon(_editor);
    t->setOccBlockHandle(new NamedBeanHandle<OBlock*>(_currentBlock->getSystemName(), _currentBlock));
    t->setFamily(_trackPanel->getFamilyName());

    QHash<QString, NamedIcon*>* iconMap = _trackPanel->getIconMap();
    if (iconMap!=NULL) {
        QHashIterator<QString, NamedIcon*> it( * iconMap);
        while (it.hasNext()) {
            //QHash<QString, NamedIcon*>* entry = it.next();
            it.next();
            if (log->isDebugEnabled()) log->debug("key= "+it.key());
            t->setIcon(it.key(), new NamedIcon(it.value()));
        }
    }
    t->setLevel(Editor::TURNOUTS);
    t->setScale(_oldIcon->getScale());
    t->rotate(_oldIcon->getDegrees());
    finishConvert((Positionable*)t);
}

/*private*/ void CircuitBuilder::finishConvert(Positionable* pos) {
    _circuitIcons->removeOne(_oldIcon);
    _oldIcon->remove();
    pos->setLocation(_oldIcon->getLocation());
    _editor->putItem(pos);
    _circuitIcons->append(pos);
    pos->updateSize();

    _oldIcon = NULL;
    _trackPanel = NULL;
    _trackTOPanel = NULL;
    //_convertDialog->dispose();
    _convertDialog->close();
    _convertDialog = NULL;
    _convertFrame = NULL;
}
/*************** end convert icons *******************/

/**************** select - deselect track icons ************************/

/**
* select block's track icons for editing
*/
/*private*/ QList<Positionable*>* CircuitBuilder::makeSelectionGroup(OBlock* block, bool showPortal)
{
 QList<Positionable*>* group =  new QList<Positionable*>();
 QListIterator<Positionable*> iter(*_circuitMap->value(block));
 while (iter.hasNext())
 {
  Positionable* p = iter.next();
  //if (p instanceof PortalIcon)
  if(qobject_cast<PortalIcon*>(p) != NULL)
  {
   if (showPortal) {
       ((PortalIcon*) p)->setStatus(PortalIcon::VISIBLE);
       group->append(p);
   }
  }
  else
  {
   group->append(p);
  }
  }
 return group;
}
#if 1
/*protected*/ bool CircuitBuilder::isTrack(Positionable* pos) {
    if (qobject_cast<IndicatorTrack*>(pos)) {
        return true;
    } else if (qobject_cast<TurnoutIcon*>(pos)) {
        return true;
    } else if (qobject_cast<PositionableLabel*>(pos)) {
        PositionableLabel* pl = (PositionableLabel*)pos;
        if (pl->isIcon()) {
             NamedIcon* icon = (NamedIcon*)pl->getIcon();
             if (icon!=NULL) {
                 QString fileName = icon->getURL();
                 // getURL() returns Unix separatorChar= "/" even on windows
                 // so don't use java.io.File.separatorChar
                 if (fileName.contains("/track/") ||
                        (fileName.contains("/tracksegments/") && !fileName.contains("circuit"))) {
                     return true;
                 }
             }
        }

    }
    return false;
}
#endif
/*private*/ bool CircuitBuilder::isUnconvertedTrack(Positionable* pos) {
    //if (pos instanceof IndicatorTrack)
    if(qobject_cast<IndicatorTrack*>(pos)!= NULL)
    {
        return false;
    }
   // else  if (pos instanceof TurnoutIcon)
    else if(qobject_cast<TurnoutIcon*>(pos)!= NULL)
    {
        return true;
    }
    //else if (pos instanceof PositionableLabel)
    else if(qobject_cast<PositionableLabel*>(pos)!= NULL)
    {
        PositionableLabel* pl = (PositionableLabel*)pos;
        if (pl->isIcon()) {
             NamedIcon* icon = (NamedIcon*)pl->getIcon();
             if (icon!=NULL) {
                 QString fileName = icon->getURL();
                 if (log->isDebugEnabled()) log->debug("isUnconvertedTrack Test: url= "+fileName);
                 // getURL() returns Unix separatorChar= "/" even on windows
                 // so don't use java.io.File.separatorChar
                 if ( (fileName.contains("/track/") || fileName.contains("/tracksegments/"))
                             && (fileName.indexOf("circuit")<0) ) {
                     return true;
                 }
             }
        }

    }
    return false;
}
#if 1
/**
* Can a path in this circuit be drawn through this icon?
*/
/*private*/ bool CircuitBuilder::okPath(Positionable* pos, OBlock* block) {
    QList<Positionable*>* icons = _circuitMap->value(block);
    if (qobject_cast<PortalIcon*>(pos)) {
        Portal* portal = ((PortalIcon*)pos)->getPortal();
        if (portal!=NULL) {
            if (block==(portal->getFromBlock()) || block==(portal->getToBlock())) {
                ((PortalIcon*)pos)->setStatus(PortalIcon::PATH);
                return true;
            }
        }
//        JOptionPane.showMessageDialog(_editor, java.text.MessageFormat.format(
//                            tr("portalNotInCircuit"),block.getDisplayName()),
//                        tr("badPath"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editor, tr("Invalid Path"), tr("This Portal is not part of track circuit \"%1\".").arg(block->getDisplayName()));
        return false;
    }
    if (!icons->contains(pos)) {
//        JOptionPane.showMessageDialog(_editor, java.text.MessageFormat.format(
//                            tr("iconNotInCircuit"),block.getDisplayName()),
//                        tr("badPath"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editor, tr("Invalid Path"), tr("This icon is not part of track circuit \"%1\".").arg(block->getDisplayName()));
        return false;
    }
    return true;
}

/**
* Can this track icon be added to the circuit?
* N.B. Be sure Positionable pos passes isTrack() call
*/
/*private*/ bool CircuitBuilder::okToAdd(Positionable* pos, OBlock* editBlock)
{
    if (qobject_cast<IndicatorTrack*>(pos)) {
        OBlock* block = ((IndicatorTrack*)pos)->getOccBlock();
        if (block!=NULL) {
            if (block!=(editBlock)) {
//                int result = JOptionPane.showConfirmDialog(_editor, java.text.MessageFormat.format(
//                                    tr("iconBlockConflict"),
//                                    block.getDisplayName(), editBlock.getDisplayName()),
//                                tr("whichCircuit"), JOptionPane.YES_NO_OPTION,
//                                JOptionPane.QUESTION_MESSAGE);
//                if (result==JOptionPane.YES_OPTION) {
             if(QMessageBox::question(_editor, tr("Which Track Circuit for Icon?"), tr("This icon displays Track Circuit \"%1\". Do you want to change it to display Circuit \"%2\"?").arg(block->getDisplayName()).arg(editBlock->getDisplayName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
             {
                    // move icon from block to editBlock
                    QList<Positionable*>* ic = _circuitMap->value(block);
                    ic->removeOne(pos);
                    ((IndicatorTrack*)pos)->setOccBlockHandle(
                            new NamedBeanHandle<OBlock*>(editBlock->getSystemName(), editBlock));
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}
#endif
/**************************** Mouse *************************/

/**
* Keep selections when editing.  Restore what super NULLs
*/
/*protected*/ bool  CircuitBuilder::saveSelectionGroup(QList<Positionable*>* selectionGroup) {
 _saveSelectionGroup = selectionGroup;
        if (_editCircuitFrame != NULL || _editPortalFrame != NULL
                || _editPathsFrame != NULL || _editDirectionFrame != NULL) {
            return true;
        }
        return false;
}

/*protected*/ void CircuitBuilder::doMousePressed(QGraphicsSceneMouseEvent* event, Positionable* selection) {
    if (_editCircuitFrame!=NULL) {
        _editCircuitFrame->toFront();
        _editor->setSelectionGroup(_saveSelectionGroup);
    } else if (_editPathsFrame!=NULL) {
        _editPathsFrame->toFront();
        _editor->setSelectionGroup(_saveSelectionGroup);
    } else if (_editPortalFrame!=NULL) {
        _editPortalFrame->toFront();
        _editor->setSelectionGroup(_saveSelectionGroup);
    }
}
#if 1
/*public*/ bool CircuitBuilder::doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* event) {
    if (_editCircuitFrame!=NULL || _editPathsFrame!=NULL) {
        return true;
    } else if (_editPortalFrame!=NULL) {
        if (qobject_cast<PortalIcon*>(selection)) {
            _editPortalFrame->checkPortalIconForUpdate((PortalIcon*)selection, true);
        }
        return true;
    }
    return false;
}
#endif
/*protected*/ bool CircuitBuilder::doMouseClicked(QList<Positionable*>* selections, QGraphicsSceneMouseEvent* event)
{
#if 1
    if (_editCircuitFrame != NULL || _editPathsFrame != NULL
            || _editPortalFrame != NULL || _editDirectionFrame != NULL) {
        if (selections != NULL && selections->size() > 0) {
            QList<Positionable*>* tracks = new QList<Positionable*>();
            QListIterator<Positionable*> iter (*selections);
            if (_editCircuitFrame != NULL) {
                while (iter.hasNext()) {
                    Positionable* pos = iter.next();
                    if (isTrack(pos)) {
                        tracks->append(pos);
                    }
                }
            } else if (_editPathsFrame != NULL) {
                while (iter.hasNext()) {
                    Positionable* pos = iter.next();
                    if (isTrack(pos) || qobject_cast<PortalIcon*>(pos)) {
                        tracks->append(pos);
                    }
                }
            } else {
                while (iter.hasNext()) {
                    Positionable* pos = iter.next();
                    if (qobject_cast<PortalIcon*>(pos)) {
                        tracks->append(pos);
                    }
                }
            }
            if (tracks->size() > 0) {
                Positionable* selection = NULL;
                if (tracks->size() == 1) {
                    selection = tracks->at(0);
                } else {
                    selection = getSelection(tracks);
                }
                if (_editPathsFrame != NULL && event->modifiers()&Qt::ShiftModifier && !event->modifiers()&Qt::ControlModifier) {
                    selection->doMouseClicked(event);
                }
                handleSelection(selection, event);
            }
        }
        return true;
    }
#endif
    return false;
}

/**
* No dragging when editing
*/
/*public*/ bool CircuitBuilder::doMouseDragged(Positionable* selection, QGraphicsSceneMouseEvent* /*event*/) {
 if (_editCircuitFrame!=NULL || _editPathsFrame!=NULL)
 {
     return true;     // no dragging when editing
 }
 if (_editPortalFrame != NULL || _editDirectionFrame != NULL)
 {
  if (qobject_cast<PortalIcon*>(selection))
  {
   _editor->highlight(selection);
      return false;		// OK to drag portal icon
  }
  return true;
 }
 return false;
}

/**
 * Second call needed to only drag the portal icon and not entire selection
 *
 * @return true if portal frame is open
 */
/*public*/ bool CircuitBuilder::dragPortal() {
    return (_editPortalFrame != NULL || _editDirectionFrame != NULL);
}
#if 1
/*
* For the param, selection, Add to or delete from selectionGroup.
* If not there, add.
* If there, delete.
*/
/*private*/ void CircuitBuilder::handleSelection(Positionable* selection, QGraphicsSceneMouseEvent* event) {
    if (_editCircuitFrame!=NULL) {
        QList<Positionable*>* selectionGroup = _editor->getSelectionGroup();
        if (isTrack(selection)) {
            if (selectionGroup==NULL) {
                selectionGroup = new QList<Positionable*>();
            }
            if (selectionGroup->contains(selection)) {
                selectionGroup->removeOne(selection);
            } else if (okToAdd(selection, _editCircuitFrame->getBlock())) {
                selectionGroup->append(selection);
            }
        }
        _editCircuitFrame->updateIconList(selectionGroup);
        _editCircuitFrame->toFront();
        _editor->setSelectionGroup(selectionGroup);
    } else if (_editPathsFrame!=NULL)
    {
        //if (selection instanceof IndicatorTrack || selection instanceof PortalIcon)
     if(qobject_cast<IndicatorTrack*>(selection) || qobject_cast<PortalIcon*>(selection))
        {
            OBlock* block = _editPathsFrame->getBlock();
            // A temporary path "TEST_PATH" is used to display the icons representing a path
            // the OBlock has allocated TEST_PATH
            // pathGroup collects the icons and the actual path is edited or
            // created with a save in _editPathsFrame
            QList<Positionable*>* pathGroup = _editPathsFrame->getPathGroup();
            if (!event->modifiers()&Qt::ShiftModifier) {
                if (pathGroup->contains(selection)) {
                    pathGroup->removeOne(selection);
                    if (qobject_cast<PortalIcon*>(selection)) {
                        ((PortalIcon*)selection)->setStatus(PortalIcon::VISIBLE);
                    } else {
                        ((IndicatorTrack*)selection)->setStatus(Sensor::INACTIVE);
                        ((IndicatorTrack*)selection)->removePath(EditCircuitPaths::TEST_PATH);
                        if (log->isDebugEnabled()) log->debug("removePath TEST_PATH");
                    }
                } else if (okPath(selection, block)) {
                    pathGroup->append(selection);
                    // okPath() sets PortalIcons to status PortalIcon.PATH
                    if (qobject_cast<IndicatorTrack*>(selection)) {
                        ((IndicatorTrack*)selection)->addPath(EditCircuitPaths::TEST_PATH);
                    }
                } else {
                    return;
                }
            } else {
                if (qobject_cast<PortalIcon*>(selection)) {
                    ((PortalIcon*)selection)->setStatus(PortalIcon::VISIBLE);
                }
            }
            int state = block->getState() | OBlock::ALLOCATED;
            block->pseudoPropertyChange("state", (0), (state));
            _editPathsFrame->updatePath(true);
        }
         _editPathsFrame->toFront();
    } else if (_editPortalFrame!=NULL) {
        if (log->isDebugEnabled()) log->debug("selection= "+(selection==NULL?"NULL":
                                                        QString(selection->metaObject()->className())));
        if (qobject_cast<PortalIcon*>(selection) && _circuitIcons->contains(selection))
        {
            _editPortalFrame->checkPortalIconForUpdate((PortalIcon*)selection, false);
            //_editor.getSelectionGroup()->layout()->addWidget(selection);
            _editor->highlight(getPortalIconMap().value(((PortalIcon*)selection)->getName()));
        }
        _editPortalFrame->toFront();
    }
}
#endif
/**************************** static methods ************************/

/*protected*/ /*static*/ void CircuitBuilder::doSize(QWidget* comp, int max, int min) {
    QSize dim = comp->size();
    dim.setWidth( max);
    comp->setMaximumSize(dim);
    dim.setWidth(min);
    comp->setMinimumSize(dim);
}

/*protected*/ /*static*/ QWidget* CircuitBuilder::makeTextBoxPanel(bool vertical, JTextField* textField, QString label, bool editable, QString tooltip) {
    QWidget* panel = makeBoxPanel(vertical, textField, label, tooltip);
    textField->setEnabled(editable);
    textField->setBackground(QColor(Qt::white));
    return panel;
}

/*protected*/ /*static*/ QWidget* CircuitBuilder::makeBoxPanel(bool vertical, JTextField* textField, QString label, QString tooltip)
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed, QSizePolicy::LineEdit);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(textField->sizePolicy().hasWidthForHeight());

 QWidget* panel = new QWidget();
 panel->setLayout(new QVBoxLayout);
 QGridLayout* g = new QGridLayout();
 panel->setSizePolicy(sizePolicy);
//    java.awt.GridBagConstraints c = new java.awt.GridBagConstraints();
//    c.gridwidth  = 1;
//    c.gridheight = 1;
//    c.gridx = 0;
//    c.gridy = 0;
//    c.weightx = 1.0;
    QLabel* l = new QLabel((label));
    if (vertical) {
//        c.anchor = java.awt.GridBagConstraints.SOUTH;
        l->setAlignment(Qt::AlignHCenter);
        textField->setAlignment(Qt::AlignHCenter);
    } else {
//        c.anchor = java.awt.GridBagConstraints.EAST;
        l->setAlignment(Qt::AlignLeft);
        textField->setAlignment(Qt::AlignRight);
    }
    g->addWidget(l,0,0,1,1);
//    if (vertical) {
//        c.anchor = java.awt.GridBagConstraints.NORTH;
//        c.gridy = 1;
//    } else {
//        c.anchor = java.awt.GridBagConstraints.WEST;
//        c.gridx = 1;
//    }
//    c.fill = java.awt.GridBagConstraints.HORIZONTAL;  // text field will expand
    doSize(textField, 9000, 200);    // default
    g->addWidget(textField, 0,1,1,1);
    textField->setSizePolicy(sizePolicy);
    ((QVBoxLayout*)panel->layout())->addLayout(g);
    if (tooltip!=NULL) {
        textField->setToolTip((tooltip));
        l->setToolTip((tooltip));
        panel->setToolTip((tooltip));
    }
    return panel;
}
/*public*/ bool CircuitBuilder::doMouseReleased(Positionable* selection, bool dragging) {
    if (_editCircuitFrame != NULL || _editPathsFrame != NULL || _editDirectionFrame != NULL) {
        return true;
    } else if (_editPortalFrame != NULL) {
        //if (dragging && selection instanceof PortalIcon && _circuitIcons.contains(selection)) {
     if(dragging && qobject_cast<PortalIcon*>(selection) != NULL && _circuitIcons->contains(selection))
     {
            _editPortalFrame->checkPortalIconForUpdate((PortalIcon*) selection, true);
        }
        return true;
    }
    return false;
}

/*private*/ Positionable* CircuitBuilder::getSelection(QList<Positionable*>* tracks)
{
 if (tracks->size() > 0)
 {
  if (tracks->size() == 1)
  {
      return tracks->at(0);
  }
  if (tracks->size() > 1)
  {

   QVector<QString> selects = QVector<QString>(tracks->size());
   QListIterator<Positionable*> iter(*tracks);
   int i = 0;
   while (iter.hasNext()) {
       selects.replace(i++, iter.next()->getNameString());
   }
//   Object select = JOptionPane.showInputDialog(_editor, tr("multipleSelections"),
//           tr("questionTitle"), JOptionPane.QUESTION_MESSAGE,
//           NULL, selects, NULL);
   QComboBox* selectBox = new QComboBox();
   selectBox->addItems(selects.toList());
   InputDialog* dlg = new InputDialog(tr("Icons are stacked over each other.\nSelect the one you want."),selectBox, tr("questionTitle"));
   dlg->exec();
   QString select = selectBox->currentText();
   if (select != NULL) {
       //iter = tracks.iterator();
       QListIterator<Positionable*> iter(*tracks);
       while (iter.hasNext()) {
           Positionable* pos = iter.next();
           if (((QString) select)==(pos->getNameString())) {
               return pos;
           }
       }
   } else {
       return tracks->at(tracks->size() - 1);
   }
  }
 }
 return NULL;
}
