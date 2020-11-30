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
#include "loggerfactory.h"
#include "defaultlistselectionmodel.h"
#include "borderfactory.h"
#include "editframe.h"
#include "joptionpane.h"
#include "placewindow.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "helputil.h"
#include "editsignalframe.h"
#include "convertdialog.h"
#include "portalmanager.h"
#include "portal.h"
#include "warranttableaction.h"
#include "box.h"
#include <QSortFilterProxyModel>
#include "helpbroker.h"

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
 _oblockModel = PickListModel::oBlockPickModelInstance();
 _blockTable = _oblockModel->makePickTable();
}

void CircuitBuilder::common()
{
 _editor = NULL;
 _iconMap = new QHash<Positionable*, OBlock*>();
 _sysNameBox = new JTextField();
 _userNameBox = new JTextField();
 _portalIcons = new QList<PortalIcon*>();
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
 _circuitMenu = new QMenu(tr("Circuit Builder"));
 OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 QSet<NamedBean*> oblocks = manager->getNamedBeanSet();
 for (NamedBean* nb : oblocks) {
  OBlock* block = (OBlock*)nb;
     _circuitMap->insert(block, new  QList<Positionable*>());
 }
 checkCircuits();  // need content for this
 int num = qMin(manager->getObjectCount(), 20) + 5;
// _blockTable.setPreferredScrollableViewportSize(new java.awt.Dimension(300, _blockTable.getRowHeight() * num));
 return _circuitMenu;
}

/*protected*/ void CircuitBuilder::openCBWindow() {
    if (_cbFrame != nullptr) {
        _cbFrame->toFront();
    } else {
        _cbFrame = new CBFrame(tr("Circuit Builder"),this);
    }
}

/*private*/ void CircuitBuilder::makeNoOBlockMenu() {
    QAction* circuitItem = new QAction(tr("Add New Detector Circuit"),this);
    _circuitMenu->addAction(circuitItem);
//    circuitItem.addActionListener((ActionEvent event) -> {
    connect(circuitItem, &QAction::triggered, [=]{
        newCircuit();
    });
    _circuitMenu->addSection(tr("At least two track circuits are needed "));
    QAction* helpItem = new QAction(tr("CircuitBuilder Help"),this);
    HelpUtil::getGlobalHelpBroker()->enableHelpOnButton(helpItem, "package.jmri.jmrit.display.CircuitBuilder", nullptr);
    _circuitMenu->addAction(helpItem);

}

/*private*/ void CircuitBuilder::makeCircuitMenu() {
    QAction* editItem = new QAction(tr("Add New Detector Circuit"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        newCircuit();
    });
    editItem = new QAction(tr("Edit Circuit OBlock"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        editCircuit(tr("Edit Circuit OBlock"), true);
    });
    editItem = new QAction(tr("Add/Edit Circuit Portals"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        editPortals(tr("Add/Edit Circuit Portals"), true);
    });
    editItem = new QAction(tr("Add/Edit Circuit Paths"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        editCircuitPaths(tr("Add/Edit Circuit Paths"), true);
    });
    editItem = new QAction(tr("Edit Portal Direction Icons"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        editPortalDirection(tr("Edit Portal Direction Icons"), true);
    });
    editItem = new QAction(tr("Add/Edit Signal Masts"));
    _circuitMenu->addAction(editItem);
    //editItem.addActionListener((ActionEvent event) -> {
    connect(editItem, &QAction::triggered, [=]{
        closeCBWindow();
        editSignalFrame(tr("Add/Edit Signal Masts"), true);
    });
    _todoMenu = new QMenu(tr("Error Checks"));
    _circuitMenu->addMenu(_todoMenu);
    QAction* helpItem = new QAction(tr("CircuitBuilder Help"));
    //HelpUtil::getGlobalHelpBroker().enableHelpOnButton(helpItem, "package.jmri.jmrit.display.CircuitBuilder", null);
    _circuitMenu->addAction(helpItem);
    makeToDoMenu();
}

/**
* Add icon 'pos' to circuit 'block'
*/
/*private*/ void CircuitBuilder::addIcon(OBlock* block, Positionable* pos) {
    QList<Positionable*>* icons = _circuitMap->value(block);
    if (pos!=NULL) {
        if (!icons->contains(pos)) {
            icons->append(pos);
        }
    }
    _darkTrack.removeOne(pos);
    // if (log.isDebugEnabled()) log.debug("addIcon: block "+block.getDisplayName()+" has "+icons.size()+" icons.");
}

// display "todo" (Error correction) items
/*private*/ void CircuitBuilder::makeToDoMenu()
{
 if (_todoMenu == nullptr) {
     _todoMenu = new QMenu(tr("Error Checks"));
     _circuitMenu->addMenu(_todoMenu);
 } else {
     _todoMenu->clear();
 }

 QMenu* blockNeeds = new QMenu(tr("Circuits without icons on this panel"));
// ActionListener editCircuitAction = (ActionEvent event) -> {
//     QString sysName = event.getActionCommand();
//     editCircuitError(sysName);
// };
 if (_bareBlock->size()>0)
 {
  for (int i=0; i<_bareBlock->size(); i++)
  {
   OBlock* block = _bareBlock->at(i);
   QAction* mi = new QAction(tr("Edit \"%1\" Circuit").arg(block->getDisplayName()),this);
//            mi->setActionCommand(block->getSystemName());
   connect(mi, &QAction::triggered, [=]{
    editCircuitError(block->getSystemName());
   });
   blockNeeds->addAction(mi);
  }
 }
 else
 {
  blockNeeds->addSection(tr("All Circuits (OBlocks) are represented by icons"));

 }
_todoMenu->addMenu(blockNeeds);  // #1

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
   connect(mi, &QAction::triggered, [=]{
    editCircuitError(block->getSystemName());
   });
   blockNeeds->addAction(mi);
  }
 }
 else
 {
  blockNeeds->addSection(tr("All Circuits (OBlocks) are represented by Indicator Track icons"));

 }
 _todoMenu->addMenu(blockNeeds);  // #2

 QAction* iconNeeds = new QAction(tr("Highlight circuit track icons needing conversion"));
 if (_unconvertedTrack.size() > 0) {
     //iconNeeds.addActionListener((ActionEvent event) -> {
  connect(iconNeeds, &QAction::triggered, [=]{
         if (editingOK()) {
             hidePortalIcons();
             QList<Positionable*> group = QList<Positionable*>();
             for (int i = 0; i < _unconvertedTrack.size(); i++) {
                 group.append(_unconvertedTrack.at(i));
             }
             _editor->setSelectionGroup(&group);
         }
     });
 } else {
     iconNeeds = new QAction(("No track icons need conversion"),this);
 }
 _todoMenu->addAction(iconNeeds);   // #3

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
  if (_hasIndicatorTrackIcons) {
                 iconNeeds = new QAction(tr("Each indicator track icon belongs to a Track Circuit"),this);
             } else {
                 iconNeeds = new QAction(tr("No Indicator Track icons on the panel"));
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
  blockNeeds = new QMenu(tr("All circuits have Portals and Paths"));

 }
 _todoMenu->addMenu(blockNeeds);  // #5

 //QAction* iconNeeds;
 if (_unconvertedTrack.size() > 0)
 {
  iconNeeds = new QAction(tr("Highlight circuit track icons needing conversion"),this);
//  iconNeeds.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent event) {
//          ArrayList<Positionable> group = new ArrayList<Positionable>();
//          for (int i = 0; i < _unconvertedTrack.size(); i++) {
//              group->layout()->addWidget(_unconvertedTrack.get(i));
//          }
//          _editor.setSelectionGroup(group);
//      }
//  });
  connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds1()));
 }
 else
 {
  iconNeeds = new QAction(tr("All Circuits (OBlocks) are represented by Indicator Track icons"), this);
 }
 _todoMenu->addAction(iconNeeds);

 if (_darkTrack.size() > 0) {
  iconNeeds = new QAction(tr("Highlight indicator tracks without circuits"), this);
//  iconNeeds.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent event) {
//          ArrayList<Positionable> group = new ArrayList<Positionable>();
//          for (int i = 0; i < _darkTrack.size(); i++) {
//              group->layout()->addWidget(_darkTrack.get(i));
//          }
//          _editor.setSelectionGroup(group);
//      }
//  });
 connect(iconNeeds, SIGNAL(triggered()), this, SLOT(OnIconNeeds2()));
 }
 else
 {
  if (_hasPortalIcons) {
      blockNeeds->addAction(new QAction(tr("Portal icons positioned OK"),this));
  } else {
      blockNeeds->addAction(new QAction(tr("There are no icons for Portals."),this));
  }
 }
 _todoMenu->addAction(iconNeeds); //#6

 if (_misplacedPortalIcon.size() > 0) {
     iconNeeds = new QAction(tr("Highlight misplaced Portal icons"),this);
     //iconNeeds.addActionListener((ActionEvent event) -> {
     connect(iconNeeds, &QAction::triggered, [=]{
         if (editingOK()) {
             QList<Positionable*> group = QList<Positionable*>();
             for (int i = 0; i < _misplacedPortalIcon.size(); i++) {
                 PortalIcon* pi = _misplacedPortalIcon.at(i);
                 group.append(pi);
                 pi->setStatus(PortalIcon::VISIBLE);
             }
             _editor->setSelectionGroup(&group);
         }
     });
 } else {
     if (_hasPortalIcons) {
         iconNeeds = new QAction(tr("All Portal icons positioned OK"),this);
     } else {
         iconNeeds = new QAction(tr("There are no icons for Portals."),this);
     }
 }
 _todoMenu->addAction(iconNeeds);   // #7

 if (_unattachedMastIcon.size() > 0) {
     iconNeeds = new QAction(tr("UnattachedMasts"),this);
     //iconNeeds.addActionListener((ActionEvent event) -> {
     connect(iconNeeds, &QAction::triggered, [=]{
         if (editingOK()) {
             QList<Positionable*> group = QList<Positionable*>();
             for (int i = 0; i < _unattachedMastIcon.size(); i++) {
                 PositionableIcon* pi = _unattachedMastIcon.at(i);
                 group.append(pi);
             }
             _editor->setSelectionGroup(&group);
         }
     });
 } else {
     if (_hasMastIcons) {
         iconNeeds = new QAction(tr("All Signal Mast icons are configured to portals"),this);
     } else {
         iconNeeds = new QAction(tr("There are no icons for Signal Masts."));
     }
 }
 _todoMenu->addAction(iconNeeds);   // #8

 blockNeeds = new QMenu(tr("Portals without icons on this panel"));
// ActionListener editPortalAction = (ActionEvent event) -> {
//     QString portalName = event.getActionCommand();
//     editPortalError(portalName);
//     };
 QSignalMapper* map = new QSignalMapper(this);
 if (_noPortalIcon.size() > 0) {
     for (int i = 0; i < _noPortalIcon.size(); i++) {
         Portal* portal = _noPortalIcon.at(i);
         QAction* mi = new QAction(portal->toString());
         //mi.setActionCommand(portal.getName());
         map->setMapping(mi, portal->getName());
         connect(mi, SIGNAL(triggered(bool)), map, SLOT(map()));
         //mi.addActionListener(editPortalAction);
         blockNeeds->addAction(mi);
     }
     connect(map, SIGNAL(mapped(QString)), this, SLOT(editPortalError(QString)));
 } else {
     blockNeeds->addAction(new QAction(tr("All portals have portal icons"),this));
 }
 _todoMenu->addMenu(blockNeeds);  // #9

 QAction* pError = new QAction(tr("Check Portal & Path Errors"),this);
 _todoMenu->addAction(pError);      // #10
 //pError.addActionListener((ActionEvent event) -> {
 connect(pError, &QAction::triggered, [=]{
     if (WarrantTableAction::getDefault()->errorCheck()) {
         JOptionPane::showMessageDialog(_editFrame,
                 tr("Currently defined OBlocks, Portals and Paths are consistent without errors."), tr("OK"),
                 JOptionPane::INFORMATION_MESSAGE);
     }
 });
}

// used for testing only
/*protected*/ EditFrame* CircuitBuilder::getEditFrame() {
    return _editFrame;
}

/**
 * ************** Set up editing Frames ****************
 */
/*protected*/ void CircuitBuilder::newCircuit() {
    if (editingOK()) {
        _blockTable->clearSelection();
        setUpEditCircuit();
        _editFrame = new EditCircuitFrame(tr("Add New Detector Circuit"), this, nullptr);
    }
}

/*protected*/ void CircuitBuilder::editCircuit(QString title, bool fromMenu)
{
 if (editingOK())
 {
  if (fromMenu) {
   editCircuitDialog(title);
  }
  if (_currentBlock!=NULL)
   if (_currentBlock != nullptr) {
       setUpEditCircuit();
       _editFrame = new EditCircuitFrame(tr("Edit \"%1\" Circuit Track").arg(_currentBlock->getDisplayName()),this, _currentBlock);
   } else if (!fromMenu) {
       selectPrompt();
   }
 }
}

/*private*/ void CircuitBuilder::setUpEditCircuit() {
    _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, false));
    _editor->disableMenus();

    TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
    targetPane->setSelectGroupColor(_editGroupColor);
    targetPane->setHighlightColor(_highlightColor);
}

/*protected*/ void CircuitBuilder::editCircuitError(QString sysName) {
    hidePortalIcons();
    if (editingOK()) {
        _currentBlock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysName);
        if (_currentBlock != nullptr) {
            _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, false));
            _editor->disableMenus();
            _editFrame = new EditCircuitFrame(tr("Edit \"%1\" Circuit Track").arg(_currentBlock->getDisplayName()),this, _currentBlock);
        }
    }
}

/*protected*/ void CircuitBuilder::editPortals(QString title, bool fromMenu) {
    if (editingOK()) {
        if (fromMenu) {
            editCircuitDialog(title);
        }
        if (_currentBlock != nullptr) {
            // check icons to be indicator type
            _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
            _editor->disableMenus();
            TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
            targetPane->setSelectGroupColor(_editGroupColor);
            targetPane->setHighlightColor(_highlightColor);
            setPortalsPositionable(_currentBlock, true);
            _editFrame = new EditPortalFrame(tr("Edit \"%1\" Portals").arg(_currentBlock->getDisplayName()), this, _currentBlock);
            _editFrame->canEdit();   // will close _editFrame if editing cannot be done
        } else if (!fromMenu) {
            selectPrompt();
        }
    }
}

/*protected*/ void CircuitBuilder::editPortalError(QString name) {
    if (editingOK()) {
        Portal* portal = ((PortalManager*)InstanceManager::getDefault("PortalManager"))->getPortal(name);
        _currentBlock = portal->getFromBlock();
        if (_currentBlock == nullptr) {
            _currentBlock = portal->getToBlock();
        }
        editPortals(nullptr, false);
    }
}

/*protected*/ void CircuitBuilder::editPortalError(OBlock* block, Portal* portal, PortalIcon* icon) {
    if (editingOK()) {
        _currentBlock = block;
        if (_currentBlock != nullptr) {
            _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
            _editor->disableMenus();
            TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
            targetPane->setSelectGroupColor(_editGroupColor);
            targetPane->setHighlightColor(_highlightColor);
            setPortalsPositionable(_currentBlock, true);
            _editFrame = new EditPortalFrame(tr("Edit \"%1\" Portals").arg(_currentBlock->getDisplayName()),this,_currentBlock, portal, icon);
        }
    }
}

/*protected*/ void CircuitBuilder::editPortalDirection(QString title, bool fromMenu) {
    if (editingOK()) {
        if (fromMenu) {
            editCircuitDialog(title);
        }
        if (_currentBlock != nullptr) {
            _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
            _editor->disableMenus();
            TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
            targetPane->setSelectGroupColor(_editGroupColor);
            targetPane->setHighlightColor(_highlightColor);
            setPortalsPositionable(_currentBlock, true);
            _editFrame = new EditPortalDirection(tr("Edit \"%1\" Portal Direction Arrows").arg(_currentBlock->getDisplayName()),this, _currentBlock);
            _editFrame->canEdit();   // will close _editFrame if editing cannot be done
        } else if (!fromMenu) {
            selectPrompt();
        }
    }
}

/*protected*/ void CircuitBuilder::editSignalFrame(QString title, bool fromMenu) {
    if (editingOK()) {
        if (fromMenu) {
            editCircuitDialog(title);
        }
        if (_currentBlock != nullptr) {
            // check icons to be indicator type
            _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
            _editor->disableMenus();
#if 0
            TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
            targetPane->setSelectGroupColor(_editGroupColor);
            targetPane->setHighlightColor(_highlightColor);
#endif
            _editFrame = new EditSignalFrame(tr("Edit \"%1\" Signal Masts").arg(_currentBlock->getDisplayName()),this, _currentBlock);
            _editFrame->canEdit();   // will close _editFrame if editing cannot be done
        } else if (!fromMenu) {
            selectPrompt();
        }
    }
}

/*protected*/ void CircuitBuilder::editCircuitPaths(QString title, bool fromMenu) {
 if (editingOK())
 {
   if(fromMenu)
   {
    editCircuitDialog(title);
   }
   if (_currentBlock != nullptr) {
         // check icons to be indicator type
         // must have converted icons for paths
         _editor->setSelectionGroup(makeSelectionGroup(_currentBlock, true));
         // A temporary path "TEST_PATH" is used to display the icons representing a path
         _currentBlock->allocate(EditCircuitPaths::TEST_PATH);
         _editor->disableMenus();
         TargetPane* targetPane = (TargetPane*) _editor->getTargetPanel();
         targetPane->setSelectGroupColor(_editGroupColor);
         targetPane->setHighlightColor(_editGroupColor);
         _currentBlock->setState(OBlock::UNOCCUPIED);
         _editFrame = new EditCircuitPaths(tr("Add/Edit \"%1\" Paths").arg(_currentBlock->getDisplayName()),this, _currentBlock);
         _editFrame->canEdit();   // will close _editFrame if editing cannot be done
     } else if (!fromMenu) {
         selectPrompt();
     }
 }
}

/*protected*/ void CircuitBuilder::setCurrentBlock(OBlock* b) {
    _currentBlock = b;
}

/*protected*/ void CircuitBuilder::hidePortalIcons() {
    if (_editFrame != nullptr) {
        _editFrame->clearListSelection();
    } else {
        for (QList<PortalIcon*>* array : _portalIconMap.values()) {
            for (PortalIcon* pi : *array) {
                pi->setStatus(PortalIcon::HIDDEN);
            }
        }
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

 mainPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
 JPanel* p = new JPanel(new FlowLayout());
 p->layout()->addWidget(new QLabel(tr("Select an OBlock track circuit")));
 mainPanel->layout()->addWidget(p);

 mainPanel->layout()->addWidget(/*new JScrollPane*/(_blockTable));
 mainPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
 mainPanel->layout()->addWidget(makeDoneButtonPanel());
 panel->layout()->addWidget(mainPanel);
 _dialog->/*getContentPane()->*/layout()->addWidget(panel);
 _dialog->move(_editor->pos().x()+100, _editor->pos().y()+100);
 _dialog->pack();
 _dialog->resize(300,400);
 _dialog->setVisible(true);
 _dialog->exec();
}

/*private*/ JPanel*  CircuitBuilder::makeDoneButtonPanel() {
 JPanel* buttonPanel = new JPanel(new QVBoxLayout());
 JPanel* panel0 = new JPanel();
 panel0->setLayout(new FlowLayout());
 QPushButton* doneButton;
 doneButton = new QPushButton(tr("Show OBlock"));
 //doneButton.addActionListener((ActionEvent a) -> {
 connect(doneButton, &QPushButton::clicked, [=]{
     if (doOpenAction()) {
         _dialog->dispose();
     }
 });
 panel0->layout()->addWidget(doneButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
 //cancelButton.addActionListener((ActionEvent a) -> {
 connect(cancelButton, &QPushButton::clicked, [=]{
     _dialog->dispose();
 });
 panel0->layout()->addWidget(cancelButton);
 buttonPanel->layout()->addWidget(panel0);
 buttonPanel->setMaximumSize(QSize(300, buttonPanel->sizeHint().height()));
 return buttonPanel;
}

/*private*/ bool CircuitBuilder::doOpenAction()
{
 int row;
 QModelIndex modelIndex = _blockTable->currentIndex();
 QAbstractItemModel* model =  _blockTable->model();
 if(row >= 0)
 {
  if(qobject_cast<QSortFilterProxyModel*>(model))
  {
   QSortFilterProxyModel* smodel = (QSortFilterProxyModel*)(modelIndex.model());
   row = smodel->mapToSource(modelIndex).row();
  }
  else
   row = modelIndex.row();
  _currentBlock = (OBlock*)_oblockModel->getBeanAt(row);
  return true;
 }
// int row = _blockTable->getSelectedRow();
// if (row >= 0) {
//     row = _blockTable->convertRowIndexToModel(row);
//     _currentBlock = (OBlock*)_oblockModel->getBeanAt(row);
//     return true;
// }
 _currentBlock = nullptr;
 selectPrompt();
 return false;
}

/*private*/ void CircuitBuilder::selectPrompt() {
    JOptionPane::showMessageDialog(_editor, tr("Select an OBlock track circuit:"),
            tr("Please enter Data"), JOptionPane::INFORMATION_MESSAGE);
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
  if(qobject_cast<PortalIcon*>((QObject*)p) != NULL)
  {
      p->setPositionable(set);
  }
 }
}

////////////////////////// Closing Editing Frames //////////////////////////
/**
 * Edit frame closing, set block's icons to support OBlock's state changes
 * @param block OBlock to set icon selections into data maps
 */
/*protected*/ void CircuitBuilder::setIconGroup(OBlock* block) {
    for (Positionable* pos : *getCircuitIcons(block)) {
        if (qobject_cast<IndicatorTrack*>(pos->self())) {
            ((IndicatorTrack*) pos->self())->setOccBlockHandle(nullptr);
        }
    }
    // the selectionGroup for all edit frames is full collection of icons
    // comprising the block.  Gather them and store in the block's hashMap
    QList<Positionable*>* selections = _editor->getSelectionGroup();
    QList<Positionable*>* icons = getCircuitIcons(block);
    icons->clear();
    if (selections != nullptr && !selections->isEmpty()) {
        NamedBeanHandle<OBlock*>* handle = ((NamedBeanHandleManager*)
                InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(block->getSystemName(), block);
         for (Positionable* pos : *selections) {
             if (qobject_cast<IndicatorTrack*>(pos->self())) {
                 ((IndicatorTrack*) pos->self())->setOccBlockHandle(handle);
             }
             icons->append(pos);
         }
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("setIconGroup: block \"%1\" has %2 icons.").arg(block->getDisplayName()).arg(icons->size()));
    }
}

/*private*/ void CircuitBuilder::closeCircuitBuilder(OBlock* block) {
   _currentBlock = NULL;
   _editFrame = nullptr;
    checkCircuits();
    setPortalsPositionable(block, false);
    hidePortalIcons();
    _editor->setSecondSelectionGroup(nullptr);
    _editor->resetEditor();
}
/**************** end closing frames ********************/

/**
 * Find the blocks with no icons and the blocks with icons that need
 * conversion Setup for main Frame - used in both initialization and close
 * of an editing frame Build Lists that are used to create menu items
 */
/*private*/ void CircuitBuilder::checkCircuits() {

    _portalIconMap.clear();
    _signalIconMap.clear();
    _signalMap.clear();
    _unattachedMastIcon.clear();
    _darkTrack.clear();
    _unconvertedTrack.clear();
    _hasIndicatorTrackIcons = false;
    _hasPortalIcons = false;
    _hasMastIcons = false;
    QList<Positionable*> removeList = QList<Positionable*>();
    PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");

    QListIterator<Positionable*> it = (_editor->getContents());
    while (it.hasNext()) {
        Positionable* pos = it.next();
        if (qobject_cast<IndicatorTrack*>(pos->self())) {
            _hasIndicatorTrackIcons = true;
            OBlock* block = ((IndicatorTrack*) pos)->getOccBlock();
            ((IndicatorTrack*) pos)->removePath(EditCircuitPaths::TEST_PATH);
            if (block != nullptr) {
                addIcon(block, pos);
            } else {
                _darkTrack.append(pos);
            }
        } else if (qobject_cast<PortalIcon*>(pos->self())) {
            _hasPortalIcons = true;
            PortalIcon* pIcon = (PortalIcon*) pos;
            Portal* portal = pIcon->getPortal();
            if (portal == nullptr) {
                log->error(tr("No Portal for PortalIcon called \"%1\". Discarding icon.").arg(pIcon->getName()));
                removeList.append(pIcon);
            } else {
                QList<PortalIcon*>* piArray = getPortalIconMap(portal);
                piArray->append(pIcon);
            }
        } else if (qobject_cast<SignalMastIcon*>(pos->self())) {
            _hasMastIcons = true;
            SignalMastIcon* sIcon = (SignalMastIcon*)pos;
            NamedBean* mast = (NamedBean*)sIcon->getSignalMast();
            if (mast == nullptr) {
                log->error(tr("No SignalMast for SignalMastIcon called \"%1\".").arg(sIcon->getNameString()));
                removeList.append(sIcon);
            } else {
                QList<PositionableIcon*>* siArray = getSignalIconMap(mast);
                siArray->append(sIcon);
                _unattachedMastIcon.append(sIcon);
            }
        } else if (qobject_cast<SignalHeadIcon*>(pos->self())) {
            _hasMastIcons =true;
            SignalHeadIcon* sIcon = (SignalHeadIcon*)pos;
            NamedBean* mast = sIcon->getSignalHead();
            if (mast == nullptr) {
                log->error(tr("No SignalHead for SignalHeadIcon called \"%1\".").arg(sIcon->getNameString()));
                removeList.append(sIcon);
            } else {
                QList<PositionableIcon*>* siArray = getSignalIconMap(mast);
                siArray->append(sIcon);
                _unattachedMastIcon.append(sIcon);
            }
        } else if (isUnconvertedTrack(pos)) {
            if (!_unconvertedTrack.contains(pos)) {
                _unconvertedTrack.append(pos);
            }
        }
    }
    QListIterator<Positionable*> its(removeList);
    while (its.hasNext()) {
        its.next()->remove();
    }

    _bareBlock->clear();         // blocks with no track icons
    _convertBlock->clear();      // blocks with at least one unconverted track icon
    _misplacedPortalIcon.clear();
    _noPortalIcon.clear();
    _noPortals.clear();
    _noPaths.clear();
    OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
    QSet<NamedBean*> oblocks = manager->getNamedBeanSet();
    for (NamedBean* nb : oblocks) {
     OBlock* block = (OBlock*)nb;
        QList<Portal*> portals = block->getPortals();
        if (portals.isEmpty()) {
            _noPortals.append(block);
        } else {
            // first add PortalIcons and SignalIcons to circuitMap
            for (Portal* portal : portals) {
                QList<PortalIcon*>* piArray = getPortalIconMap(portal);
                for (PortalIcon* pi : *piArray) {
                    addIcon(block, pi);
                }
                NamedBean* mast = portal->getSignalProtectingBlock(block);
                if (mast != nullptr) {
                    QList<PositionableIcon*>* siArray = getSignalIconMap(mast);
                    for (PositionableIcon* si : *siArray) {
                        addIcon(block, si);
                        _unattachedMastIcon.removeOne(si);

                    }
                    _signalMap.insert(mast, portal);
                }
                if (log->isDebugEnabled()) {
                    log->debug(tr("Portal %1 in block %2 has %3 icons").arg(portal->getName()).arg(block->getDisplayName()).arg(piArray->size()));
                }
            }
        }
        QVector<Path*>* paths = block->getPaths();
        if (paths ==nullptr || paths->isEmpty()) {
            _noPaths.append(block);
        }

        QList<Positionable*>* icons = getCircuitIcons(block);
        if (log->isDebugEnabled()) {
            log->debug("checkCircuits: block " + block->getDisplayName()
                    + " has " + QString::number(icons->size()) + " icons.");
        }
        if (icons->isEmpty()) {
            _bareBlock->append(block);
        } else {
            bool hasTrackIcon = false;
            bool iconNeedsConversion = false;
            for (int k = 0; k < icons->size(); k++) {
                Positionable* pos = icons->at(k);
                if (!(qobject_cast<PortalIcon*>(pos->self())) && !(qobject_cast<SignalMastIcon*>(pos->self())) && !(qobject_cast<SignalHeadIcon*>(pos->self())) ) {
                    hasTrackIcon = true;
                    if (!(qobject_cast<IndicatorTrack*>(pos->self()))) {
                        iconNeedsConversion = true;
                    }
                }
            }
            if (hasTrackIcon) {
                _bareBlock->removeOne(block);
            } else if (!_bareBlock->contains(block)) {
                _bareBlock->append(block);
            }
            if (iconNeedsConversion && !_convertBlock->contains(block)) {
                _convertBlock->append(block);
            }
        }
    }

    // check positioning of portal icons for 'direction arrow' state.
    for (Portal* portal : portalMgr->getPortalSet()) {
        QList<PortalIcon*>* piArray = getPortalIconMap(portal);
        if (piArray->isEmpty()) {
            _noPortalIcon.append(portal);
        } else {
            PortalIcon* icon1 = piArray->at(0);
            if (piArray->size() == 1) {
                if (!iconIntersectsBlock(icon1, portal->getToBlock()) ||
                        !iconIntersectsBlock(icon1, portal->getFromBlock())) {
                    _misplacedPortalIcon.append(icon1);
                }
            } else {
                bool fromOK = false;
                bool toOK = false;
                PortalIcon* icon = nullptr;
                for (PortalIcon* ic : *piArray) {
                    if (!toOK && iconIntersectsBlock(ic, portal->getToBlock()) &&
                            !iconIntersectsBlock(ic, portal->getFromBlock())) {
                        toOK = true;
                    } else if (!fromOK && !iconIntersectsBlock(ic, portal->getToBlock()) &&
                            iconIntersectsBlock(ic, portal->getFromBlock())) {
                        fromOK = true;
                    } else {
                        icon = ic;
                    }
                }
                if (!toOK || !fromOK) {
                    _misplacedPortalIcon.append(icon);
                }
            }
        }
    }

    if (oblocks.size() > 1) {
        if (_circuitMenu->actions().count() <= 3) {
            _circuitMenu->clear();
            makeCircuitMenu();
        } else {
            makeToDoMenu();
        }
    } else {
        _circuitMenu->clear();
        makeNoOBlockMenu();
    }
}   // end checkCircuits

/*protected*/ bool CircuitBuilder::iconIntersectsBlock(Positionable* icon, OBlock* block) {
        QList<Positionable*>* list = getCircuitIcons(block);
        if (list->isEmpty()) {
            return false;
        }
        QRectF rect = QRectF();
        QRectF iconRect = icon->getBounds(QRectF());
        for (int i = 0; i < list->size(); i++) {
            Positionable* comp = list->value(i);
            if (CircuitBuilder::isTrack(comp)) {
                rect = list->value(i)->getBounds(rect);
                if (iconRect.intersects(rect)) {
                    return true;
                }
            }
        }
        return false;
    }
////////////////////////// Frame Utilities //////////////////////////

/**
* Used by Portal Frame
*/
/*protected*/ QList<Positionable*>* CircuitBuilder::getCircuitIcons(OBlock* block) {
 // return empty array when block == null
 QList<Positionable*>* array = _circuitMap->value(block, nullptr);
 if (array == nullptr) {
     array = new QList<Positionable*>();
     _circuitMap->insert(block, array);
 }
 return array;
}

//@Nonnull
/*protected*/ QList<PortalIcon *>* CircuitBuilder::getPortalIconMap(/*@Nonnull*/ Portal* portal) {
 QList<PortalIcon*>* array = _portalIconMap.value(portal);
 if (array == nullptr) {
     array = new QList<PortalIcon*>();
     _portalIconMap.insert(portal, array);
 }
 return array;
}

//@Nonnull
/*protected*/ QList<PositionableIcon*>* CircuitBuilder::getSignalIconMap(/*@Nonnull*/ NamedBean* mast) {
    QList<PositionableIcon*>* array = _signalIconMap.value(mast);
    if (array == nullptr) {
        array = new QList<PositionableIcon*>();
        _signalIconMap.insert(mast, array);
    }
    return array;
}

/*protected*/ Portal* CircuitBuilder::getSignalPortal(/*@Nonnull*/ NamedBean* mast) {
    return _signalMap.value(mast);
}

/*protected*/ void CircuitBuilder::putSignalPortal(/*@Nonnull*/ NamedBean* mast, Portal* portal) {
    if (portal == nullptr) {
        _signalMap.remove(mast);
    }
    _signalMap.insert(mast, portal);
}

/**
 * Remove block, but keep the track icons. Sets block reference in icon to
 * null.
 *
 * @param block the block to remove
 */
/*protected*/ void CircuitBuilder::removeBlock(OBlock* block) {
    QList<Positionable*>* list = getCircuitIcons(block);
    for (Positionable* pos : *list) {
        if (qobject_cast<IndicatorTrack*>(pos->self())) {
            ((IndicatorTrack*) pos->self())->setOccBlockHandle(nullptr);
        }
        _darkTrack.append(pos);
    }
    block->dispose();
    if (((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getNamedBeanSet().size() < 2) {
        _editor->makeWarrantMenu(true, false);
    }
}


/*protected*/ QString CircuitBuilder::checkForPortals(/*@Nonnull*/ OBlock* block, QString key) {
    QString sb;// = new StringBuffer();
    QList<Portal*> portals = block->getPortals();
    if (portals.isEmpty()) {
        sb.append(tr("Block circuit (OBlock) \"%1\" has no portals.\nPortals are needed to add a %2 in CircuitBuilder.").arg(block->getDisplayName()).arg((key)));
    } else {
        for (Portal* portal : portals) {
            if (portal->getToBlock() == nullptr || portal->getFromBlock() == nullptr) {
                if (sb.length() > 0) {
                    sb.append("\n");
                }
                sb.append(tr("Portal \"%1\" is incomplete! It must have an OBlock on each side.").arg(portal->getName()));
            }
        }
        for (Portal* portal : portals) {
            if (sb.length() > 0) {
                sb.append("\n");
            }
            if (!block->equals(portal->getToBlock()) && !block->equals(portal->getFromBlock())) {
                sb.append(tr("Portal \"%1\" does not connect to track circuit (OBlock) \"%2\".").arg(portal->getName()).arg(block->getDisplayName()));
            }
        }
    }
    return sb/*.toString()*/;
}


/**
 * Check that there is at least one PortalIcon
 * @param block check icons of this block
 * @param key properties key
 * @return true if at least one PortalIcon found
 */
/*protected*/ QString CircuitBuilder::checkForPortalIcons(/*@Nonnull*/ OBlock* block, QString key) {
    QString sb;// = new StringBuffer();
    QList<Portal*> portals = block->getPortals();
    for (Portal* portal : portals) {
        QList<PortalIcon*>* iconMap = getPortalIconMap(portal);
        if (iconMap->isEmpty()) {
            if (sb.length() > 0) {
                sb.append("\n");
            }
            sb.append(tr("Portal \"%1\" does not have an icon.\nPortal Icons are needed to add a %2 in CircuitBuilder.").arg(portal->getName()).arg((key)));
        } else {
            for (PortalIcon* icon : *iconMap) {
                Portal* p = icon->getPortal();
                if (p == nullptr) {
                    deletePortalIcon(icon);
                } else if (qobject_cast<EditPortalFrame*>(_editFrame)){
                    QString msg = ((EditPortalFrame*)_editFrame)->checkPortalIconForUpdate(icon, false);
                    if (msg != nullptr) {
                        if (sb.length() > 0) {
                            sb.append("\n");
                        }
                        sb.append(msg);
                    }
                }
            }
        }
    }
    // block has pPortals
    bool ok = false;
    QList<Positionable*>* list = getCircuitIcons(block);
    if (!list->isEmpty()) {
        for (Positionable* pos : *list) {
            if (qobject_cast<PortalIcon*>(pos->self())) {
                ok = true;
            }
        }
    }
    if (!ok) {
        if (sb.length() > 0) {
            sb.append("\n");
        }
        sb.append(tr("Block circuit \"%1\" needs portal icons.\nPortal Icons are needed to add a %2 in CircuitBuilder.").arg(block->getDisplayName()).arg((key)));
    }
    return sb;
}

/*protected*/ QString CircuitBuilder::checkForTrackIcons(/*@Nonnull*/ OBlock* block, QString key) {
    QString sb;// = new StringBuilder();
    QList<Positionable*>* list = getCircuitIcons(block);
    if (list->isEmpty()) {
        sb.append(tr("Block circuit (OBlock) \"%1\" needs Indicator Track icons to add a {1} in CircuitBuilder.").arg(block->getDisplayName()).arg((key)));
    } else {
        bool ok = true;
        for (Positionable* p : *list) {
            PositionableLabel* pos = (PositionableLabel*) p;
            if (CircuitBuilder::isUnconvertedTrack(pos)) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            sb.append(tr("Track icons in circuit (OBlock) \"%1\" need conversion before saving the panel file.").arg(block->getDisplayName()));
            sb.append("\n");
            sb.append(tr("Block circuit (OBlock) \"%1\" needs Indicator Track icons to add a %2 in CircuitBuilder.").arg(block->getDisplayName()).arg((key)));
        }
    }
    return  sb;
}

/*protected*/ void CircuitBuilder::deletePortalIcon(PortalIcon* icon) {
    if (log->isDebugEnabled()) {
        log->debug("deletePortalIcon: " + icon->getName());
    }
    Portal* portal = icon->getPortal();
    if (portal != nullptr) {
        getCircuitIcons(portal->getToBlock())->removeOne(icon);
        getCircuitIcons(portal->getFromBlock())->removeOne(icon);
        getPortalIconMap(portal)->removeOne(icon);
    }
    QList<Positionable*>* selections = _editor->getSelectionGroup();
    if (selections != nullptr) {
        _editor->getSelectionGroup()->removeOne(icon);
    }
    _editor->repaint();
}

/**
  * Check if the block being edited has all its track icons converted to indicator icons
 * If icons need conversion. ask if user wants to convert them
 * @param block OBlock to check
 * @param key properties key
 * @return true if all track icons are IndicatorTrack icons
 */
/*protected*/ bool CircuitBuilder::queryConvertTrackIcons(/*@Nonnull*/ OBlock* block, QString key) {
    // since iconList will be modified, use a copy to find unconverted icons
    QList<Positionable*> list = QList<Positionable*>(*getCircuitIcons(block));
    QString msg = "";
    if (list.isEmpty()) {
        msg = tr("Block circuit (OBlock) \"%1\" needs Indicator Track icons to add a %2 in CircuitBuilder.").arg(block->getDisplayName()).arg(key);
    } else {
        for (Positionable* p : list) {
            PositionableLabel* pos = (PositionableLabel*) p->self();
            if (CircuitBuilder::isUnconvertedTrack(pos)) {
                _editor->highlight(pos);
                new ConvertDialog(this, pos, block);
                _editor->highlight(nullptr);
            }
        }
    }
    if (msg != nullptr) {
        JOptionPane::showMessageDialog(_editFrame, msg,
                tr("no Icons"), JOptionPane::INFORMATION_MESSAGE);
        return false;
    } else {
        return true;
    }
}

//////////////// select - deselect track icons //////////
/**
 * Select block's track icons for editing. filter for what icon types to show and highlight
 */
/*private*/ QList<Positionable*>* CircuitBuilder::makeSelectionGroup(OBlock* block, bool showPortal) {
    QList<Positionable*> group = QList<Positionable*>();
    for (Positionable* p : *getCircuitIcons(block)) {
        if (qobject_cast<PortalIcon*>(p->self())) {
            if (showPortal) {
                ((PortalIcon*) p)->setStatus(PortalIcon::VISIBLE);
                group.append(p);
            }
        } else if (!(qobject_cast<SignalMastIcon*>(p->self())) && !(qobject_cast<SignalHeadIcon*>(p->self()))) {
            group.append(p);
        }
    }
    return &group;
}

/*protected*/ bool CircuitBuilder::isTrack(Positionable* pos) {
    if (qobject_cast<IndicatorTrack*>((QObject*)pos)) {
        return true;
    } else if (qobject_cast<TurnoutIcon*>((QObject*)pos)) {
        return true;
    } else if (qobject_cast<PositionableLabel*>((QObject*)pos)) {
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
/*private*/ bool CircuitBuilder::isUnconvertedTrack(Positionable* pos) {
    //if (pos instanceof IndicatorTrack)
    if(qobject_cast<IndicatorTrack*>((QObject*)pos)!= NULL)
    {
        return false;
    }
   // else  if (pos instanceof TurnoutIcon)
    else if(qobject_cast<TurnoutIcon*>((QObject*)pos)!= NULL)
    {
        return true;
    }
    //else if (pos instanceof PositionableLabel)
    else if(qobject_cast<PositionableLabel*>((QObject*)pos)!= NULL)
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

/**
* Can this track icon be added to the circuit?
* N.B. Be sure Positionable pos passes isTrack() call
*/
/*private*/ bool CircuitBuilder::okToAdd(Positionable* pos, OBlock* editBlock)
{
    if (qobject_cast<IndicatorTrack*>((QObject*)pos)) {
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

/*protected*/ void CircuitBuilder::doMousePressed(QGraphicsSceneMouseEvent* /*event*/, Positionable* /*selection*/) {
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

/*public*/ bool CircuitBuilder::doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* /*event*/) {
    if (_editCircuitFrame!=NULL || _editPathsFrame!=NULL) {
        return true;
    } else if (_editPortalFrame!=NULL) {
        if (qobject_cast<PortalIcon*>((QObject*)selection)) {
            _editPortalFrame->checkPortalIconForUpdate((PortalIcon*)selection, true);
        }
        return true;
    }
    return false;
}

/*protected*/ bool CircuitBuilder::doMouseClicked(QList<Positionable*>* selections, QGraphicsSceneMouseEvent* event)
{
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
                    if (isTrack(pos) || qobject_cast<PortalIcon*>((QObject*)pos)) {
                        tracks->append(pos);
                    }
                }
            } else {
                while (iter.hasNext()) {
                    Positionable* pos = iter.next();
                    if (qobject_cast<PortalIcon*>((QObject*)pos)) {
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
  if (qobject_cast<PortalIcon*>((QObject*)selection))
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

/*
* For the param, selection, Add to or delete from selectionGroup.
* If not there, add.
* If there, delete.
*/
/*private*/ void CircuitBuilder::handleSelection(Positionable* selection, QGraphicsSceneMouseEvent* event) {
 if (_editFrame == nullptr) {
     return;
 }
 if (qobject_cast<EditCircuitFrame*>(_editFrame)) {
     EditCircuitFrame* editCircuitFrame = (EditCircuitFrame*)_editFrame;
     QList<Positionable*>* selectionGroup = _editor->getSelectionGroup();
     if (selectionGroup == nullptr) {
         selectionGroup = new QList<Positionable*>();
     }
     if (selectionGroup->contains(selection)) {
         selectionGroup->removeOne(selection);
     } else if (okToAdd(selection, editCircuitFrame->_homeBlock)) {
         selectionGroup->append(selection);
     }
     editCircuitFrame->updateIconList(selectionGroup);
     _editor->setSelectionGroup(selectionGroup);
 } else if (qobject_cast< EditCircuitPaths*>(_editFrame)) {
     EditCircuitPaths* editPathsFrame = (EditCircuitPaths*)_editFrame;
     editPathsFrame->updateSelections(!(event->modifiers()&Qt::ShiftModifier), selection);
 } else if (qobject_cast<EditPortalFrame*>(_editFrame)) {
     EditPortalFrame* editPortalFrame = (EditPortalFrame*)_editFrame;
     if (qobject_cast< PortalIcon*>(selection->self())) {
         editPortalFrame->setSelected((PortalIcon*)selection);
     }
 } else if (qobject_cast<EditPortalDirection*>(_editFrame)) {
     EditPortalDirection* editDirectionFrame = (EditPortalDirection*)_editFrame;
     if (qobject_cast< PortalIcon*>(selection->self())) {
         editDirectionFrame->setPortalIcon((PortalIcon*)selection, true);
     }
 } else if (qobject_cast< EditSignalFrame*>(_editFrame)) {
     EditSignalFrame* editSignalFrame = (EditSignalFrame*)_editFrame;
     editSignalFrame->setSelected((PositionableIcon*)selection);
 }
}

/*protected*/ void CircuitBuilder::closeCBWindow() {
    if (_cbFrame !=nullptr) {
        _cbFrame->dispose();
    }
}
/**************************** static methods ************************/

/*protected*/ /*static*/ void CircuitBuilder::doSize(QWidget* comp, int max, int min) {
    QSize dim = comp->sizeHint();
    dim.setWidth( max);
    comp->setMaximumSize(dim);
    dim.setWidth(min);
    comp->setMinimumSize(dim);
}

/*protected*/ /*static*/ JPanel* CircuitBuilder::makeTextBoxPanel(bool vertical, JTextField* textField, QString label, bool editable, QString tooltip) {
    JPanel* panel = makeBoxPanel(vertical, textField, label, tooltip);
    textField->setEnabled(editable);
    textField->setBackground(QColor(Qt::white));
    return panel;
}

/*protected*/ /*static*/ JPanel* CircuitBuilder::makeBoxPanel(bool vertical, JTextField *textField, QString label, QString tooltip)
{
//    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed, QSizePolicy::LineEdit);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(textField->sizePolicy().hasWidthForHeight());

 JPanel* panel = new JPanel();
 panel->setLayout(new QVBoxLayout);
 QGridLayout* g = new QGridLayout();
 //panel->setSizePolicy(sizePolicy);
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
//        textField->setAlignment(Qt::AlignHCenter);
    } else {
//        c.anchor = java.awt.GridBagConstraints.EAST;
        l->setAlignment(Qt::AlignLeft);
//        textField->setAlignment(Qt::AlignRight);
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
//    textField->setSizePolicy(sizePolicy);
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
     if(dragging && qobject_cast<PortalIcon*>((QObject*)selection) != NULL && _circuitIcons->contains(selection))
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

/*public*/ QString CircuitBuilder::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.CircuitBuilder";
}


//    class CBFrame extends jmri.util.JmriJFrame implements ListSelectionListener  {

//        ButtonGroup _buttonGroup = new ButtonGroup();
//        int _which = 0;
//        JRadioButton _newCircuitButton = makeButton("newCircuitItem", NONE);

       CBFrame::CBFrame(QString title, CircuitBuilder*cb) : JmriJFrame(false, false){
            //super(false, false);
            setTitle(title);
            addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);

            cb->_blockTable->getSelectionModel()->addListSelectionListener((ListSelectionListener*)this);

            JPanel* contentPane = new JPanel();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
            Border* padding = BorderFactory::createEmptyBorder(10, 5, 4, 5);
            contentPane->setBorder(padding);

            JPanel* panel0 = new JPanel();
            panel0->setLayout(new QHBoxLayout());//panel0, BoxLayout.X_AXIS));
            JPanel* panel = new JPanel();
            panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
            panel->layout()->addWidget(_newCircuitButton);
            panel->layout()->addWidget(makeButton("editCircuitItem", CircuitBuilder::OBLOCK));
            panel->layout()->addWidget(makeButton("editPortalsItem", CircuitBuilder::PORTAL));
            panel->layout()->addWidget(makeButton("editCircuitPathsItem", CircuitBuilder::OPATH));
            panel->layout()->addWidget(makeButton("editDirectionItem", CircuitBuilder::ARROW));
            panel->layout()->addWidget(makeButton("editSignalItem", CircuitBuilder::_SIGNAL));
            _newCircuitButton->setChecked(true);
            panel0->layout()->addWidget(panel);

            panel = new JPanel();
            panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
            panel->layout()->addWidget(/*new JScrollPane*/(cb->_blockTable));
            panel0->layout()->addWidget(panel);
            contentPane->layout()->addWidget(panel0);

            panel0 = new JPanel();
            panel0->setLayout(new QHBoxLayout());//panel0, BoxLayout.X_AXIS));
            panel = new JPanel();
            QPushButton* button = new QPushButton(tr("Open"));
//            button.addActionListener((ActionEvent event) -> {
            connect(button, &QPushButton::clicked, [=]{
                if (cb->editingOK()) {
                    setCurrentBlock();
                    if (_which == CircuitBuilder::NONE) {
                        cb->newCircuit();
                    } else if (_which == CircuitBuilder::OBLOCK) {
                        cb->editCircuit(tr("Edit Circuit OBlock"), false);
                    } else if (_which == CircuitBuilder::PORTAL) {
                        cb->editPortals(tr("Add/Edit Circuit Portals"), false);
                    } else if (_which == CircuitBuilder::OPATH) {
                        cb->editCircuitPaths(tr("Add/Edit Circuit Paths"), false);
                    } else if (_which ==CircuitBuilder:: ARROW) {
                        cb->editPortalDirection(tr("Edit Portal Direction Icons"), false);
                    } else if (_which == CircuitBuilder::_SIGNAL) {
                        cb->editSignalFrame(tr("Edit Signal masts protecting block %1").arg("?"), false);
                    }
                }
            });
            panel->layout()->addWidget(button);

            button = new QPushButton(tr("Done"));
            //button.addActionListener((ActionEvent a) -> {
            connect(button, &QPushButton::clicked, [=]{
                cb->_currentBlock = nullptr;
                this->dispose();
            });
            panel->layout()->addWidget(button);
            panel->setMaximumSize(QSize(300, panel->sizeHint().height()));
            panel0->layout()->addWidget(panel);
            contentPane->layout()->addWidget(panel0);

            setContentPane(contentPane);
            cb->_blockTable->clearSelection();
            pack();
            ((PlaceWindow*)InstanceManager::getDefault("PlaceWindow"))->nextTo(cb->_editor, nullptr, this);
            setVisible(true);
        }

        //@Override
        /*public*/ void CBFrame::valueChanged(ListSelectionEvent* e) {
            setCurrentBlock();
        }

        /*private*/ void CBFrame::setCurrentBlock() {
            int row = cb->_blockTable->getSelectedRow();
            if (row >= 0) {
                row = cb->_blockTable->convertRowIndexToModel(row);
                cb->_currentBlock = (OBlock*)cb->_oblockModel->getBeanAt(row);
            } else {
                cb->_currentBlock = nullptr;
            }
        }

        QRadioButton* CBFrame::makeButton(QString title, int which) {
            QRadioButton* button = new QRadioButton((title));
//            button.addActionListener((ActionEvent event) -> {
            connect(button, &QPushButton::clicked, [=]{

                _which = which;
            });
            _buttonGroup->addButton(button);
            return button;
        }

        //@Override
        /*public*/ void CBFrame::dispose() {
            cb->_cbFrame = nullptr;
            JmriJFrame::dispose();
        }
//    }



    /*private*/ /*final*/ /*static*/ Logger* CircuitBuilder::log = LoggerFactory::getLogger("CircuitBuilder");
