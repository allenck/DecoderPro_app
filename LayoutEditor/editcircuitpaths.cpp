#include "editcircuitpaths.h"
#include "oblock.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "circuitbuilder.h"
#include "portalicon.h"
#include "indicatortrack.h"
#include <QListView>
#include "jtextfield.h"
#include "opath.h"
#include <QMessageBox>
#include "indicatorturnouticon.h"
#include "turnout.h"
#include "rosterentry.h"
#include "portal.h"
#include "jtogglebutton.h"

//EditCircuitPaths::EditCircuitPaths(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2011
 *
 */

// /*public*/ class EditCircuitPaths extends jmri.util.JmriJFrame implements ListSelectionListener {


//    static java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;
    /*static*/ int EditCircuitPaths::STRUT_SIZE = 10;
    /*static*/ bool EditCircuitPaths::_firstInstance = true;
/*static*/ QPoint _loc = QPoint();
static QSize _dim = QSize();
    /*public*/ /*static*/ /*final*/ QString EditCircuitPaths::TEST_PATH = "TEST_PATH";

/*public*/ EditCircuitPaths::EditCircuitPaths(QString title, CircuitBuilder* builder, OBlock* block, QWidget *parent) :
JmriJFrame(parent)
{
 _parent = builder;
 _block = block;
 _length = new JTextField();
 log = new Logger("EditCircuitPaths");
 setTitle(QString(title).arg(_block->getDisplayName()));

//    addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            closingEvent();
//        }
//    });
    addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);

    QWidget* contentPane = new QWidget();
    QVBoxLayout* contentPaneLayout;
    contentPane->setLayout(contentPaneLayout=new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
#if 1
    contentPaneLayout->addStrut(STRUT_SIZE);
    contentPaneLayout->addWidget(makeContentPanel());
    contentPaneLayout->addStrut(STRUT_SIZE);

//    QWidget* border = new QWidget();
//    border.setLayout(new java.awt.BorderLayout(10,10));
//    border.add(contentPane);
//    setContentPane(border);
    setCentralWidget(contentPane);
    pack();
//    if (_firstInstance) {
//        setLocationRelativeTo(_parent->_editor);
//        resize(500,500);
//        _firstInstance = false;
//    } else {
//        setLocation(_loc);
//        setSize(_dim);
//    }
#endif
    setVisible(true);
}
#if 1
/*private*/ QWidget*  EditCircuitPaths::MakeButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout);//(buttonPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//    if(!findErrors)
//    {
//                closingEvent();
//    }
//            }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(on_doneClicked()));
    panel->layout()->addWidget(doneButton);

    buttonPanel->layout()->addWidget(panel);

    panel = new QWidget();
    panel->setLayout(new FlowLayout());
    panel->layout()->addWidget(buttonPanel);

    return panel;
}

void EditCircuitPaths::on_doneClicked()
{
 if(!findErrors())
  closingEvent();
}

/*private*/ QWidget* EditCircuitPaths::makeContentPanel() {
    QWidget* pathPanel = new QWidget();
    QVBoxLayout* pathPanelLayout;
    pathPanel->setLayout(pathPanelLayout = new QVBoxLayout(pathPanel/*, BoxLayout.Y_AXIS*/));

    pathPanelLayout->addStrut(STRUT_SIZE);
    QWidget* panel = new QWidget();
    panel->layout()->addWidget(new QLabel(tr("Paths through track circuit %1").arg(_block->getDisplayName())));
    pathPanel->layout()->addWidget(panel);

    _pathListModel = new PathListModel(this);
    _pathList = new QListView;
    _pathList->setModel(_pathListModel);
    //_pathList.addListSelectionListener(this);
    connect(_pathList, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged()));
//    _pathList.setCellRenderer(new PathCellRenderer());
    pathPanel->layout()->addWidget(_pathList);
    pathPanelLayout->addStrut(2*STRUT_SIZE);

    panel = new QWidget();
//        panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
    panel->setLayout(new FlowLayout());

    QPushButton* clearButton = new QPushButton(tr("Clear Selection"));
//    clearButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                clearListSelection();
//            }
//    });
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearListSelection()));
    clearButton->setToolTip(tr("Clear the selections in the list."));
    panel->layout()->addWidget(clearButton);
    pathPanel->layout()->addWidget(panel);
    ((QBoxLayout*)pathPanel->layout())->addStrut((STRUT_SIZE));

    panel = new QWidget();
    panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _pathName, tr("Path Name"), true, tr("Enter the name of the path through this track circuit.")));
    _pathName->setMinimumSize( QSize(300, _pathName->getPreferredSize().height()));
    pathPanel->layout()->addWidget(panel);

    panel = new QWidget();

    QPushButton* addButton = new QPushButton(tr("Add Path"));
//    addButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                addPath();
//            }
//    });
    connect(addButton, SIGNAL(clicked()), this, SLOT(addPath()));
    addButton->setToolTip(tr("Enter a name, then select the icons that show\nthe track and portals of the path. Then press this button."));
    panel->layout()->addWidget(addButton);

    QPushButton* changeButton = new QPushButton(tr("Change Name"));
//    changeButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                changePathName();
//            }
//    });
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changePathName()));
    changeButton->setToolTip(tr("Enter another name to change the name of a selection in the above list."));
    panel->layout()->addWidget(changeButton);

    QPushButton* deleteButton = new QPushButton(tr("Delete Path"));
//    deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                deletePath();
//            }
//    });
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePath()));
    deleteButton->setToolTip(tr("Delete the path selected in the list from the track circuit. "));
    panel->layout()->addWidget(deleteButton);

    pathPanel->layout()->addWidget(panel);
    ((QBoxLayout*)pathPanel->layout())->addStrut((STRUT_SIZE));

    panel = new QWidget();
    QVBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    QLabel* l = new QLabel(tr("To make a New path, enter text into the Path Name box"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new QLabel(tr("selectPathIcons"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new QLabel(tr("pressAddButton"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    panelLayout->addStrut((STRUT_SIZE/2));
    l = new QLabel(tr("selectPath"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new QLabel(tr("editPathIcons"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    panelLayout->addStrut((STRUT_SIZE/2));
    l = new JLabel(tr("throwPathTO"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new JLabel(tr("holdShiftDown"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    QWidget* p = new QWidget();
    p->layout()->addWidget(panel);
    pathPanel->layout()->addWidget(p);

    ((QBoxLayout*)pathPanel->layout())->addStrut((STRUT_SIZE));
    pathPanel->layout()->addWidget(MakeButtonPanel());
    return pathPanel;
}
#if 0
/*private*/ static class PathCellRenderer extends JLabel implements ListCellRenderer {

    /*public*/ Component getListCellRendererComponent(
       JList list,              // the list
       Object value,            // value to display
       int index,               // cell index
       boolean isSelected,      // is the cell selected
       boolean cellHasFocus)    // does the cell have focus
    {
         String s = ((OPath)value).getDescription();
         setText(s);
         if (isSelected) {
             setBackground(list.getSelectionBackground());
             setForeground(list.getSelectionForeground());
         } else {
             setBackground(list.getBackground());
             setForeground(list.getForeground());
         }
         setEnabled(list.isEnabled());
         setFont(list.getFont());
         setOpaque(true);
         return this;
    }
};

#endif
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SIC_INNER_SHOULD_BE_STATIC")
// passing just the path list instead of using _block saves a call
//class PathListModel : public QAbstractListModel
//{
    PathListModel::PathListModel(EditCircuitPaths* parent)
    {
     this->parent = parent;
    }

    /*public*/ int PathListModel::rowCount(const QModelIndex &parent) const
    {
        return this->parent->_block->getPaths()->size();
    }
    /*public*/ QVariant PathListModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
      return ((OBlock*)parent->_block->getPaths()->at(index.row()))->getDescription();
//     if(role == Qt::BackgroundRole)
//         return QBrush(QColor(Qt::lightGray));
//     if(role == Qt::ForegroundRole)
//         return QBrush(QColor(Qt::black));
     return QVariant();
    }
    /*public*/ void PathListModel::dataChange() {
        //fireContentsChanged(this, 0, 0);
        beginResetModel();
        endResetModel();
    }
    /*public*/ Path* PathListModel::getSelectedValue()
    {
     QModelIndex index = parent->_pathList->currentIndex();
     return parent->_block->getPaths()->at(index.row());
    }

//};

/**
*  When a
*/
/*public*/ void EditCircuitPaths::valueChanged(ListSelectionEvent* /*e*/)
{
 clearPath();
 OPath* path = (OPath*)_block->getPaths()->at(_pathList->currentIndex().row());
 if (path!=NULL)
 {
  _pathName->setText(path->getName());
  showPath(path);
 }
 else
 {
  checkForSavePath();
  _pathName->setText("");
 }
 int state = _block->getState() | OBlock::ALLOCATED;
 _block->pseudoPropertyChange("state", (0), (state));
}

/*private*/ void EditCircuitPaths::showPath(OPath* path)
{
    path->setTurnouts(0, true, 0, false);
    makePath(path);
    updatePath(false);
}

/**
 * Construct the array of icons that displays the path
 * @param path
 */
/*private*/ void EditCircuitPaths::makePath(OPath* path)
{
 Portal* fromPortal = path->getFromPortal();
 Portal* toPortal = path->getToPortal();
 QString name = path->getName();

 QList<Positionable*>* list = _parent->getCircuitGroup();
 if (log->isDebugEnabled()) log->debug("showPath for "+name+" CircuitGroup size= "+QString::number(list->size()));
 _pathGroup = new QList<Positionable*>();
 for (int i=0; i<list->size(); i++)
 {
  Positionable* pos = list->at(i);
  //if (pos instanceof IndicatorTrack)
  if(qobject_cast<IndicatorTrack*>((QObject*)pos)!= NULL)
  {
   QStringList* paths = ((IndicatorTrack*)pos)->getPaths();
   if (paths!=NULL)
   {
    for (int j=0; j<paths->size(); j++)
    {
     if (name==(paths->at(j)))
     {
      _pathGroup->append(pos);
     }
    }
   }
  }
  else
  {
   PortalIcon* icon = (PortalIcon*)pos;
   Portal* portal = icon->getPortal();
   if (portal==(fromPortal))
   {
    _pathGroup->append(icon);
   }
   else if (portal==(toPortal))
   {
    _pathGroup->append(icon);
   }
  }
 }
}
/**
 * Construct the array of icons that displays the path
 *
 * @param path
 */
/*private*/ QList<Positionable*>* EditCircuitPaths::makePathGroup(OPath* path)
{
 Portal* fromPortal = path->getFromPortal();
 Portal* toPortal = path->getToPortal();
 QString name = path->getName();

 QList<Positionable*>* list = _parent->getCircuitGroup();
 if (log->isDebugEnabled()) {
     log->debug("makePathGroup for " + name + " CircuitGroup size= " + list->size());
 }
 QList<Positionable*>* pathGroup =  new QList<Positionable*>();
 for (int i = 0; i < list->size(); i++)
 {
  Positionable* pos = list->at(i);
  if (qobject_cast<IndicatorTrack*>((QObject*)pos) != NULL)
  {
   QList<QString>* paths = ((IndicatorTrack*) pos)->getPaths();
   if (paths != NULL)
   {
    for (int j = 0; j < paths->size(); j++)
    {
     if (name==(paths->at(j)))
     {
      ((IndicatorTrack*) pos)->setControlling(true);
      pathGroup->append(pos);
     }
    }
   }
  }
  else
  {
   PortalIcon* icon = (PortalIcon*) pos;
   Portal* portal = icon->getPortal();
   if (portal==(fromPortal))
   {
       pathGroup->append(icon);
   }
   else if (portal==toPortal)
   {
       pathGroup->append(icon);
   }
  }
 }
 return pathGroup;
}

/**
 * sets the path for display
 * @param pathChanged
 */
/*protected*/ void EditCircuitPaths::updatePath(bool pathChanged)
{
 // to avoid ConcurrentModificationException now set data
 for (int i=0; i<_pathGroup->size(); i++)
 {
  Positionable* pos = _pathGroup->at(i);
  //if (pos instanceof IndicatorTrack)
  if(qobject_cast<IndicatorTrack*>((QObject*)pos)!= NULL)
  {
    ((IndicatorTrack*)pos)->addPath(TEST_PATH);
  }
  else
  {
   ((PortalIcon*)pos)->setStatus(PortalIcon::PATH);
  }
 }
 _pathChange = pathChanged;
 QString name = _pathName->text();
 if (name == NULL || name.length() == 0)
 {
//  JOptionPane.showMessageDialog(this, Bundle.getMessage("needPathName"),
//             Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(this, tr("Make Path"), tr("Enter the name for a new path or select a path from the above list."));
 }
 else
 {
 }
}

/*private*/ bool EditCircuitPaths::findErrors()
{
  bool error = false;
  if (checkForSavePath()) {
      return true;
  }
  QVector<Path*>* list = _block->getPaths();
  if (list->size() == 0)
  {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("noPaths", _block.getDisplayName()),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Make Path"), tr("Circuit Block \"%1\" has no paths.").arg(_block->getDisplayName()));
   return NULL;
  }
  for (int i = 0; i < list->size(); i++)
  {
      OPath* path = (OPath*) list->at(i);
      QList<Positionable*>* pathGp = makePathGroup(path);
      if (pathGp->size() == 0) {
          error = true;
          break;
      }
      OPath* p = makeOPath(path->getName(), pathGp, false);
      if (p == NULL) {
          error = true;
          break;
      }
  }
  if (error)
  {
//      int result = JOptionPane.showConfirmDialog(this, Bundle.getMessage("hasPathErrors"),
//              Bundle.getMessage("makePath"), JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
//      if (result == JOptionPane.YES_OPTION) {
   if(QMessageBox::information(this, tr("Make Path"), tr("Circuit Block has incomplete Path definitions.  Do you want to Exit?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
    error = false;
   }
  }
  return error;
}

/*private*/ bool EditCircuitPaths::checkForSavePath()
{
 QString name = _pathName->text();
 if (!_pathChange || name.trimmed().length() == 0)
 {
  return false;
 }
//        int result = JOptionPane.showConfirmDialog(this, java.text.MessageFormat.format(
//                        tr("savePath"), _pathName.getText()),
//                        tr("makePath"), JOptionPane.YES_NO_OPTION,
//                        JOptionPane.QUESTION_MESSAGE);
//        if (result==JOptionPane.YES_OPTION) {
//           	deletePath();
  if(QMessageBox::question(this, tr("Make Path"), tr("Do you want to save the path \"%1\"?"), QMessageBox::Yes |QMessageBox::No) == QMessageBox::Yes)
  {
   addPath();
   return true;
  }
  _pathChange = false;
  return false;

}
/*private*/ /*static*/ bool EditCircuitPaths::pathsEqual(OPath* p1, OPath* p2) {
    Portal* toPortal1 = p1->getToPortal();
    Portal* fromPortal1 = p1->getFromPortal();
    Portal* toPortal2 = p2->getToPortal();
    Portal* fromPortal2 = p2->getFromPortal();
    bool testSettings = false;
    if (toPortal1 != NULL) {
        if ((toPortal1==(toPortal2) || toPortal1==(fromPortal2))) {
            if (fromPortal1 != NULL) {
                if (fromPortal1==(fromPortal2) || fromPortal1==(toPortal2)) {
                    testSettings = true;
                }
            } else {
                if (toPortal2 == NULL || fromPortal2 == NULL) {
                    testSettings = true;
                }
            }
        }
    } else if (toPortal2 == NULL) {	//i.e. toPortal2 matches toPortal1==NULL
        if (fromPortal1 != NULL && fromPortal1==(fromPortal2)) {
            testSettings = true;
        }
    } else if (fromPortal2 == NULL) {	//i.e. fromPortal2 matches toPortal1==NULL
        if (fromPortal1 != NULL && fromPortal1==(toPortal2)) {
            testSettings = true;
        }
    }

    if (testSettings) {
        QList<BeanSetting*> setting1 = p1->getSettings();
        QList<BeanSetting*> setting2 = p2->getSettings();
        if (setting1.size() != setting2.size()) {
            return false;
        }
        if (setting1.size() == 0) {		// no turnouts in paths, but portals the same
            return true;
        }
        QListIterator<BeanSetting*> it(setting1);
        while (it.hasNext()) {
            BeanSetting* bs1 = it.next();
            QListIterator<BeanSetting*> iter( setting2);
            while (iter.hasNext()) {
                BeanSetting* bs2 = iter.next();
                if (bs1->getBean()==(bs2->getBean()) && bs1->getSetting() == bs2->getSetting()) {
                    return true;
                }
            }
        }
    }
    return false;
}
/************************* end setup **************************/

/*private*/ void EditCircuitPaths::clearListSelection() {
    _pathList->clearSelection();
    int state = _block->getState() & ~OBlock::ALLOCATED;
    _block->pseudoPropertyChange("state", QVariant(0), QVariant(state));
}
/**
 * Make the OPath from the icons in the Iterator
 */
/*private*/ OPath* EditCircuitPaths::makeOPath(QString name, QList<Positionable*>* pathGp, bool showMsg)
{
 if (pathGp->size() == 0)
 {
  if (showMsg) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("noPathIcons"),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Make Path"), tr("To display a path in a circuit at least one track icon must be selected."));
  }
  return NULL;
 }
 QListIterator<Positionable*> it( *pathGp);
 QList<BeanSetting*> settings =  QList<BeanSetting*>();
 Portal* fromPortal = NULL;
 Portal* toPortal = NULL;
 bool hasTrack = false;
 int portalIconCount = 0;
 while (it.hasNext())
 {
  Positionable* pos = it.next();
  //if (pos instanceof IndicatorTurnoutIcon)
  if(qobject_cast<IndicatorTurnoutIcon*>((QObject*)pos) != NULL)
  {
   Turnout* t = ((IndicatorTurnoutIcon*) pos)->getTurnout();
   QString turnoutName = ((IndicatorTurnoutIcon*) pos)->getNamedTurnout()->getName();
   int state = t->getKnownState();
   if (state != Turnout::CLOSED && state != Turnout::THROWN)
   {
    if (showMsg)
    {
//        JOptionPane.showMessageDialog(this, Bundle.getMessage("turnoutNotSet", t.getDisplayName()),
//                Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(this, tr("Make Path"), tr("Turnout \"%1\" must be set to \"Closed\" or \"Thrown\".").arg(t->getDisplayName()));
    }
    return NULL;
   }
   settings.append(new BeanSetting(t, turnoutName, state));
   hasTrack = true;
  }
  //else if (pos instanceof PortalIcon)
  else if(qobject_cast<PortalIcon*>((QObject*)pos) != NULL)
  {
      if (toPortal == NULL) {
          toPortal = ((PortalIcon*) pos)->getPortal();
      } else if (fromPortal == NULL) {
          fromPortal = ((PortalIcon*) pos)->getPortal();
      }
      portalIconCount++;
  }
  //else if (pos instanceof IndicatorTrack)
  else if(qobject_cast<IndicatorTrack*>((QObject*)pos) != NULL)
  {
      hasTrack = true;
  }
 }
 if (showMsg)
 {
  if (!hasTrack) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("noPathIcons"),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);\
      QMessageBox::information(this, tr("Make Path"), tr("To display a path in a circuit at least one track icon must be selected."));return NULL;
  }
  if (toPortal == NULL && fromPortal == NULL) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("tooFewPortals"),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Make Path"), tr("A path must have at least one portal."));return NULL;
      return NULL;
  }
  if (portalIconCount == 0) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("noPortalIcons"),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Make Path"), tr("Path has portals but no portal icons are defined."));return NULL;
  }
  if (portalIconCount > 2) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("tooManyPortals"),
//              Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Make Path"), tr("A path cannot have more than two portal icons."));return NULL;
      return NULL;
  }
 }

 if (hasTrack && portalIconCount > 0 && portalIconCount < 3) {
     return new OPath(name, _block, fromPortal, toPortal, settings);
 }
 return NULL;
}

/*private*/ void EditCircuitPaths::changePathNameInIcons(QString name, OPath* path) {
    // add or remove path name from IndicatorTrack icons
    QListIterator<Positionable*> iter(*_parent->getCircuitGroup());
    while (iter.hasNext()) {
        Positionable* pos = iter.next();
        if (_pathGroup->contains(pos)) {
         if (qobject_cast< IndicatorTrack*>((QObject*)pos) != NULL) {
                ((IndicatorTrack*) pos)->addPath(name);
            }
        } else {
            if (qobject_cast< IndicatorTrack*>((QObject*)pos) != NULL) {
                ((IndicatorTrack*) pos)->removePath(name);
            } else {
                PortalIcon* pi = (PortalIcon*) pos;
                //                   pi.setStatus(PortalIcon.VISIBLE);
                Portal* p = pi->getPortal();
                p->removePath(path);
            }
        }
    }

}

/**
 * Create or update the selected path named in the text field
 * Checks that icons have been selected for the path
 */
/*private*/ void EditCircuitPaths::addPath()
{
 QString name = _pathName->text();
 if (name == NULL || name.trimmed().length() == 0)
 {
//  JOptionPane.showMessageDialog(this, Bundle.getMessage("TooltipPathName"),
//          Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(this, tr("Make Path"), tr("Enter the name of the path through this track circuit."));
  return;
 }
 OPath* otherPath = _block->getPathByName(name);
 bool sameName = false;
 if (otherPath != NULL)
 {
  //_pathList->setSelectedValue(otherPath, true);
  int row;
  for(row=0; row < _block->getPaths()->size(); row ++)
  {
   if(((OBlock*) _block->getPaths())->getDescription() == otherPath->getDescription())
   {
    _pathList->setCurrentIndex(_pathListModel->index(row,0, QModelIndex()));
    break;
   }
  }
  sameName = true;
  if (!_pathChange)
  {
   // check portals OK
   Portal* p = otherPath->getFromPortal();
   if (p != NULL && !p->isValidPath(otherPath))
   {
    p->addPath(otherPath);
   }
   p = otherPath->getToPortal();
   if (p != NULL && !p->isValidPath(otherPath))
   {
    p->addPath(otherPath);
   }
   setPathLength(otherPath);
   return;
  }
 }
 OPath* path = makeOPath(name, _pathGroup, true);
 if (path == NULL)
 {
  return;		// proper OPath cannot be made
 }
 if (otherPath == NULL)
 {
  // is this path already defined?
  QVectorIterator<Path*> iter(*_block->getPaths());
  while (iter.hasNext())
  {
   OPath* p = (OPath*) iter.next();
   if (pathsEqual(path, p))
   {
    otherPath = p;
    break;
   }
  }
 }
 // match icons to current selections
 changePathNameInIcons(name, path);

 if (otherPath != NULL)
 {		// same path
  if (!sameName)
  {
//   int result = JOptionPane.showConfirmDialog(this, Bundle.getMessage("samePath",
//           otherPath.getName(), name), Bundle.getMessage("makePath"), JOptionPane.YES_NO_OPTION,
//           JOptionPane.QUESTION_MESSAGE);
//   if (result == JOptionPane.YES_OPTION) {
   if(QMessageBox::information(this, tr("Make Path"), tr("Path is the same as path \"%1\".\nDo you want to change the name to \"%2\"?").arg(otherPath->getName()).arg(name),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
    changePathName();
   }
  }
  //_pathList->setSelectedValue(otherPath, true);
  int row;
  for(row=0; row < _block->getPaths()->size(); row ++)
  {
   if(((OBlock*) _block->getPaths())->getDescription() == otherPath->getDescription())
   {
    _pathList->setCurrentIndex(_pathListModel->index(row,0, QModelIndex()));
    break;
   }
  }
 }
 Portal* toPortal = path->getToPortal();
 Portal* fromPortal = path->getFromPortal();
 if (fromPortal != NULL && fromPortal == (toPortal))
 {
//  int result = JOptionPane.showConfirmDialog(this, Bundle.getMessage("balloonTrack",
//          name, fromPortal.getDescription()),
//          Bundle.getMessage("makePath"), JOptionPane.YES_NO_OPTION,
//          JOptionPane.QUESTION_MESSAGE);
//  if (result == JOptionPane.NO_OPTION) {
  if(QMessageBox::information(this, tr("Make Path"), tr("Is path \%1\" a balloon track?\n(%2 is both an entrance and exit portal)").arg(name).arg(fromPortal->getDescription()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
  {
   fromPortal = NULL;
  }
 }
 _pathChange = false;
 // If the name is the same as a Path already in the block, don't add.
 // Just update OPath changes
 if (sameName)
 {
   OPath* oldPath = _block->getPathByName(name);
   oldPath->setToPortal(toPortal);
   oldPath->setFromPortal(fromPortal);
   setPathLength(oldPath);
   oldPath->clearSettings();
   QListIterator<BeanSetting*> it(path->getSettings());
   while (it.hasNext()) {
       oldPath->addSetting(it.next());
   }
   toPortal->addPath(oldPath);
   if (fromPortal!=NULL)
   {
       fromPortal->addPath(oldPath);
   }
 }
 else
 {
  _block->addPath(path);		// OBlock adds path to portals and checks for duplicate path names
  setPathLength(path);
 }
 //_pathList->setSelectedValue(path, true);
 int row;
 for(row=0; row < _block->getPaths()->size(); row ++)
 {
  if(((OBlock*) _block->getPaths())->getDescription() == path->getDescription())
  {
   _pathList->setCurrentIndex(_pathListModel->index(row,0, QModelIndex()));
   break;
  }
 }
 _pathListModel->dataChange();
}

/*private*/ OPath* EditCircuitPaths::getBlockPath(QString name)
{
 QVector<Path*>* list = _block->getPaths();
 for (int i=0; i<list->size(); i++)
 {
  OPath* path = (OPath*)list->at(i);
  if (name==(path->getName()))
  {
   return path;
  }
 }
 return NULL;
}
/*private*/ bool EditCircuitPaths::setPathLength(OPath* path)
{
 float f = 0.0f;
 try {
     QString num = _length->text();
     if (num==NULL || num.length()==0) {
         num = "0.0";
     }
     f = num.toFloat();
     if (_units->isSelected()) {
         path->setLength(f*25.4);
     } else {
         path->setLength(f*10);
     }
 } catch (NumberFormatException nfe) {
     f = -1.0;
 }
 if (f<0.0f)
 {
//     JOptionPane.showMessageDialog(this, Bundle.getMessage("MustBeFloat", _length.getText()),
//             Bundle.getMessage("makePath"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(this, tr("Make Path"), tr("%1} is an invalid number.  Must be a positive decimal number.").arg(_length->text()));

     return false;
 }

 return true;
}
/*private*/ void EditCircuitPaths::changePathName()
{
 OPath* path = (OPath*)_block->getPaths()->at(_pathList->currentIndex().row());
 QString name = _pathName->text();
 if (name==NULL || name.trimmed().length()==0 || path==NULL)
 {
//        JOptionPane.showMessageDialog(this, tr("changePathName"),
//                        tr("makePath"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(this, tr("Make Path"), tr("Select a path from the above list. Enter the name change. Press [Change Name] button."));
  return;
 }
 QString oldName = path->getName();
 OPath* oldPath = _block->getPathByName(name);
 if (oldPath!=NULL)
 {
//        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                        tr("duplicatePathName"), name, _block.getDisplayName()),
//                        tr("makePath"), JOptionPane.INFORMATION_MESSAGE);
  QMessageBox::information(this, tr("Make Path"), tr("Path \"%1\" is the name of another path in circuit %2.").arg(name).arg(_block->getDisplayName()));
  return;
 }
 path->setName(name);

 QList<Positionable*>* list = _parent->getCircuitGroup();
 // cannot do remove/add path on the fly due to conncurrent access with Iterator
 QList<IndicatorTrack*>* changeGroup = new QList<IndicatorTrack*>();
 for (int i=0; i<list->size(); i++)
 {
  //if (list.get(i) instanceof IndicatorTrack)
  if(qobject_cast<IndicatorTrack*>((QObject*)list->at(i))!= NULL)
  {
   IndicatorTrack* icon = (IndicatorTrack*)list->at(i);
   QStringList* paths = icon->getPaths();
   if (paths!=NULL)
   {
    for (int j=0; j<paths->size(); j++)
    {
     if (oldName==(paths->at(j)))
     {
      changeGroup->append(icon);
     }
    }
   }
  }
 }
 for (int i=0; i<changeGroup->size(); i++)
 {
  IndicatorTrack* track = changeGroup->at(i);
  track->removePath(oldName);
  track->addPath(name);
 }
 _pathChange = false;
 _pathListModel->dataChange();
}

/*private*/ void EditCircuitPaths::deletePath() {
    OPath* path = (OPath*)_block->getPaths()->at(_pathList->currentIndex().row());
    if (path==NULL) {
        // check that name was typed in and not selected
        path = _block->getPathByName(_pathName->text());
    }
    if (path==NULL) {
        return;
    }
    _pathChange = false;
    _block->removePath(path);
    _pathListModel->dataChange();
    // Get icons for path
    makePath(path);
    clearPath();
}

/*protected*/ void EditCircuitPaths::closingEvent()
{
 checkForSavePath();
 clearPath();
 _parent->closePathFrame(_block);
// _loc = getLocation(_loc);
// _dim = getSize(_dim);
 dispose();
}

/*private*/ void EditCircuitPaths::clearPath()
{
 for (int i=0; i<_pathGroup->size(); i++)
 {
  Positionable* pos = _pathGroup->at(i);
  //if (pos instanceof PortalIcon)
  if(qobject_cast<PortalIcon*>((QObject*)pos) != NULL)
  {
   ((PortalIcon*)pos)->setStatus(PortalIcon::VISIBLE);
  }
  else
  {
   ((IndicatorTrack*)pos)->removePath(TEST_PATH);
  }
 }
 int state = _block->getState() & ~OBlock::ALLOCATED;
 _block->pseudoPropertyChange("state", 0, state);
}

/************** callbacks from main frame *****************/

/*protected*/ QList<Positionable*>* EditCircuitPaths::getPathGroup()
{
    return _pathGroup;
}

/*protected*/ OBlock* EditCircuitPaths::getBlock() {
    return _block;
}
#endif
