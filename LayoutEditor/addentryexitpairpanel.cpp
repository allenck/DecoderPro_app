#include "addentryexitpairpanel.h"
#include "instancemanager.h"
#include "entryexitpairs.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "panelmenu.h"
#include <QComboBox>
#include "layouteditor.h"
#include "flowlayout.h"
#include "tablemodel.h"
#include "jtable.h"
#include <QSortFilterProxyModel>
#include "layoutblockmanager.h"
#include "joptionpane.h"
#include "jtextfield.h"
#include "propertychangeevent.h"

//AddEntryExitPairPanel::AddEntryExitPairPanel(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/**
 * QWidget to create a new JMRI devices HiJacked to serve other beantable tables.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version $Revision: 1.2 $
 */
// /*public*/ class AddEntryExitPairPanel extends jmri.util.swing.JmriPanel {

/**
 *
 */

/*public*/ AddEntryExitPairPanel::AddEntryExitPairPanel(LayoutEditor* panel, QWidget *parent) :
  JmriPanel(parent)
{
  fromSet = QStringList();
  toSet = QStringList();

 selectPanel = new QComboBox();
 fromPoint = new QComboBox();
 toPoint = new QComboBox();

 interlockTypes = QStringList() << "Set Turnouts Only" << "Set Turnouts and SignalMasts" << "Full Interlock";
 typeBox = new QComboBox(/*interlockTypes*/);
 typeBox->addItems(interlockTypes);

 nxPairs = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");

 //protected static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.EntryExitBundle");
 entryExitFrame = NULL;
 sourceLabel = new QLabel();
 validPoints =  QList<ValidPoints*>();

 optionsFrame = NULL;
 optionsPane = NULL;
 clearOptions = QStringList() <<"Prompt User" << "Clear Route"<< "Cancel Route";
 clearEntry = new QComboBox(/*clearOptions*/);
 clearEntry->addItems(clearOptions);
 durationSetting = new JTextField(10);
 colorText = QStringList() <<"None"<< "Black"<< "DarkGray"<< "Gray"<<
     "LightGray"<< "White"<< "Red"<< "Pink"<< "Orange"<<
     "Yellow"<< "Green"<< "Blue"<< "Magenta"<< "Cyan";
 QList<QColor> colorCode = QList<QColor>() << QColor()<< Qt::black<< Qt::darkGray<< Qt::gray<<
     Qt::lightGray << Qt::white << Qt::red << QColor(255,192,203) << QColor(255,165,0) <<
     Qt::yellow << Qt::green << Qt::blue << Qt::magenta << Qt::cyan;
 numColors = 14;  // number of entries in the above arrays
 dispatcherUse = new QCheckBox("Integrate With Dispatcher");

 settingTrackColorBox = new QComboBox();

 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);

 QWidget* top = new QWidget();
 //top.setLayout(new GridLayout(6, 2));
 QGridLayout* g = new QGridLayout(top);

 g->addWidget(new QLabel(tr("Select Panel")),0,0);
 g->addWidget(selectPanel, 0,1);
 selectPanel->clear();
 panels = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 for (int i = 0; i < panels->size(); i++)
 {
  selectPanel->addItem(panels->at(i)->getLayoutName());
 }
 if (panel != NULL)
 {
  selectPanel->setCurrentIndex(selectPanel->findText(panel->getLayoutName()));
 }

 g->addWidget(new QLabel(tr("Entry Point")),1,0);
 g->addWidget(fromPoint, 1,1);
//    ActionListener selectPanelListener = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            selectPointsFromPanel();
//            nxModel.setPanel(panels.get(selectPanel.getSelectedIndex()));
//        }
//    };
 selectPointsFromPanel();
 //selectPanel.addActionListener(selectPanelListener);
 connect(selectPanel, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_selectPanel_currentIndexChanged(QString)));

 g->addWidget(new JLabel(tr("Exit Point")),2,0);
 g->addWidget(toPoint,2,1);
 g->addWidget(new JLabel("NX Type"),3,0);
 g->addWidget(typeBox, 3,1);
 thisLayout->addWidget(top);

    //add(top);
//    QWidget p = new QWidget();
 FlowLayout* pLayout = new FlowLayout;

 QPushButton* ok = new QPushButton(tr("Add"));
 pLayout->addWidget(ok);
//    ok.addActionListener(
//            new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    addButton();
//                }
//            });
 connect(ok, SIGNAL(clicked()), this, SLOT(addButton()));

 //p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
 QPushButton*  _auto = new QPushButton(tr("Auto Generate Entry Exit Pairs"));
//    p.add(auto = new JButton(tr("AutoGenerate")));
//    auto.addActionListener(
//            new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    autoDiscovery();
//                }
//            });
 connect(_auto, SIGNAL(clicked()), this, SLOT(autoDiscovery()));
 pLayout->addWidget(_auto);
 thisLayout->addLayout(pLayout);
 nxModel = new AEPTableModel(panel, this);
 nxSorter = new QSortFilterProxyModel;
 nxSorter->setSourceModel(nxModel);
 nxDataTable = new JTable(/*nxSorter*/);
 nxDataTable->setModel(nxSorter);
 //nxSorter.setTableHeader(nxDataTable.getTableHeader());
 //nxDataScroll = new JScrollPane(nxDataTable);
 nxModel->configureTable(nxDataTable);
 QSize dataTableSize = nxDataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 dataTableSize.setHeight(qMax(dataTableSize.height(), 400));
 //nxDataScroll.getViewport().setPreferredSize(dataTableSize);
 thisLayout->addWidget(nxDataTable);
}
int AEPTableModel::NUMCOL = AEPTableModel::ENABLEDCOL + 1;

/*private*/ void AddEntryExitPairPanel::addButton()
{
 ValidPoints* from = getValidPointFromCombo(fromPoint);
 ValidPoints* to = getValidPointFromCombo(toPoint);
 if (from == NULL || to == NULL) {
     return;
 }

 nxPairs->addNXDestination(from->getPoint(), to->getPoint(), panel);
 nxPairs->setEntryExitType(from->getPoint(), panel, to->getPoint(), typeBox->currentIndex());
}

void AddEntryExitPairPanel::on_selectPanel_currentIndexChanged(QString)
{
 selectPointsFromPanel();
 nxModel->setPanel(panels->at(selectPanel->currentIndex()));
}


/*private*/ void AddEntryExitPairPanel::autoDiscovery()
{
 if (!((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()) {
  int response = JOptionPane::showConfirmDialog(nullptr, tr("Layout Block Routing is not enabled.\nDo you want to enable it?"));  // NOI18N
  if (response == 0) {
      ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
      JOptionPane::showMessageDialog(nullptr, tr(" Please close and reopen this window for the changes to take effect."));  // NOI18N
  }
 }
 entryExitFrame = new JmriJFrameX(tr("Discover Entry Exit Pairs"), false, false);
 entryExitFrame->setMinimumSize(QSize());
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 entryExitFrame->setCentralWidget(centralWidget);
 //QWidget* panel1 = new QWidget();
 QHBoxLayout* panel1Layout = new QHBoxLayout;
 sourceLabel = new QLabel("Discovering Entry Exit Pairs");
    /*ImageIcon i;
     i = new ImageIcon(FileUtil.findURL("resources/icons/misc/gui3/process-working.gif"));
     JLabel label = new JLabel();
     label.setIcon(i);
     panel1.add(label);*/
 panel1Layout->addWidget(sourceLabel);

 centralWidgetLayout->addLayout(panel1Layout);
 entryExitFrame->adjustSize();
 entryExitFrame->setVisible(true);
    int retval = JOptionPane::showOptionDialog(NULL, tr("Do you want to automatically generate \nthe Entry Exit Pairs and Logic, based /nupon the track plan in the layout editor?"), tr("Auto Generate Entry Exit Pairs"),
            JOptionPane::YES_NO_OPTION,
            JOptionPane::QUESTION_MESSAGE/*, QIcon(), NULL, NULL*/);
    if (retval == 0) {
        /*final*/ PropertyChangeListener* propertyNXListener = new PropertyNXListener(this);
//     {
//            /*public*/ void propertyChange(PropertyChangeEvent evt) {
//                if (evt.getPropertyName()==("autoGenerateComplete")) {
//                    if (entryExitFrame != NULL) {
//                        entryExitFrame.setVisible(false);
//                        entryExitFrame.dispose();
//                    }
//                    nxPairs.removePropertyChangeListener(this);
//                    JOptionPane.showMessageDialog(NULL, "Generation of Entry Exit Pairs Completed");
//                }
//            }
//        };
  try
  {
   //nxPairs.addPropertyChangeListener(propertyNXListener);
   connect(nxPairs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyNXListener, SLOT(propertyChange(PropertyChangeEvent*)));
   nxPairs->automaticallyDiscoverEntryExitPairs(panels->at(selectPanel->currentIndex()), typeBox->currentIndex());
  }
  catch (JmriException e)
  {
   //nxPairs->removePropertyChangeListener(propertyNXListener);
   disconnect(nxPairs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyNXListener, SLOT(propertyChange(PropertyChangeEvent*)));
   //OptionPane.showMessageDialog(NULL, e.toString());
   entryExitFrame->setVisible(false);
  }
 }
 else
 {
  entryExitFrame->setVisible(false);
 }
}

void PropertyNXListener::propertyChange(PropertyChangeEvent * evt)
{
 if (evt->getPropertyName()==("autoGenerateComplete"))
 {
  if (panel->entryExitFrame != NULL)
  {
      panel->entryExitFrame->setVisible(false);
      panel->entryExitFrame->close();
  }
  //nxPairs.removePropertyChangeListener(this);
  disconnect(panel->nxPairs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
  JOptionPane::showMessageDialog(NULL, "Generation of Entry Exit Pairs Completed");
 }
}

ValidPoints* AddEntryExitPairPanel::getValidPointFromCombo(QComboBox* box)
{
 QString item = box->currentText();
 for (int i = 0; i < validPoints.size(); i++)
 {
  if (validPoints.at(i)->getDescription()==(item))
  {
      return validPoints.at(i);
  }
 }
 return NULL;
}


/*private*/ void AddEntryExitPairPanel::selectPointsFromPanel()
{
 if (selectPanel->currentIndex() == -1)
 {
     return;
 }
 if (panel == panels->value(selectPanel->currentIndex())) {
     return;
 }
 panel = panels->value(selectPanel->currentIndex());
 fromSet.clear();
 toSet.clear();
 doFromCombo = true;
 selectPoints(panel);

 // Do other panels if any
 doFromCombo = false;
 panels = static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 for (int i = 0; i < panels->size(); i++) {
     if (panels->at(i) != panel) {
         selectPoints(panels->value(i));
     }
 }

 // Update the combo boxes
 fromPoint->clear();
// fromSet.forEach((ent) -> {
//     fromPoint.addItem(ent);
// });
 foreach(QString ent, fromSet)
  fromPoint->addItem(ent);
 toPoint->clear();
// toSet.forEach((ent) -> {
//     toPoint.addItem(ent);
// });
 foreach(QString ent, toSet)
  toPoint->addItem(ent);
}

/*private*/ void AddEntryExitPairPanel::selectPoints(LayoutEditor* panel) {
    for (PositionablePoint* pp : panel->getPositionablePoints()) {
        addPointToCombo(pp->getWestBoundSignalMastName(), pp->getWestBoundSensorName());
        addPointToCombo(pp->getEastBoundSignalMastName(), pp->getEastBoundSensorName());
    }

    for (LayoutTurnout* t : panel->getLayoutTurnouts()) {
        addPointToCombo(t->getSignalAMastName(), t->getSensorAName());
        addPointToCombo(t->getSignalBMastName(), t->getSensorBName());
        addPointToCombo(t->getSignalCMastName(), t->getSensorCName());
        addPointToCombo(t->getSignalDMastName(), t->getSensorDName());
    }

    for (LevelXing* xing : panel->getLevelXings()) {
        addPointToCombo(xing->getSignalAMastName(), xing->getSensorAName());
        addPointToCombo(xing->getSignalBMastName(), xing->getSensorBName());
        addPointToCombo(xing->getSignalCMastName(), xing->getSensorCName());
        addPointToCombo(xing->getSignalDMastName(), xing->getSensorDName());
    }

    for (LayoutSlip* slip : panel->getLayoutSlips()) {
        addPointToCombo(slip->getSignalAMastName(), slip->getSensorAName());
        addPointToCombo(slip->getSignalBMastName(), slip->getSensorBName());
        addPointToCombo(slip->getSignalCMastName(), slip->getSensorCName());
        addPointToCombo(slip->getSignalDMastName(), slip->getSensorDName());
    }
}
void AddEntryExitPairPanel::addPointToCombo(QString signalMastName, QString sensorName)
{
 NamedBean* source = NULL;
 if (sensorName != NULL && !sensorName.isEmpty())
 {
  QString description = sensorName;
  source = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensorName);
  if (signalMastName != NULL && !signalMastName.isEmpty())
  {
   description = sensorName + " (" + signalMastName + ")";
  }
  validPoints.append(new ValidPoints(source, description));
  fromPoint->addItem(description);
  toPoint->addItem(description);
 }
}


////Need to add a property change listener to catch when paths go active.
//class TableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//    private static final long serialVersionUID = 3291217259103678604L;

//needs a method to for when panel changes
//need a method to delete an item
//Possibly also to set a route.
//Add a propertychange listener to hear when the route goes active.
AEPTableModel::AEPTableModel(LayoutEditor* panel, AddEntryExitPairPanel* parent)
{
 this->parent = parent;
 _rowCount = 0;

 setPanel(panel);
 //nxPairs.addPropertyChangeListener(this);
 connect(parent->nxPairs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 source = parent->nxPairs->getNxSource(panel);
 dest = parent->nxPairs->getNxDestination();
 log = new Logger("AEPTableModel");
}

void AEPTableModel::setPanel(LayoutEditor* panel)
{
    if (this->panel == panel)
    {
        return;
    }
    this->panel = panel;
    _rowCount = parent->nxPairs->getNxPairNumbers(panel);
    updateNameList();
    fireTableDataChanged();
}

//LayoutEditor panel;

//ArrayList<Object> source = NULL;
//ArrayList<Object> dest = NULL;

void AEPTableModel::updateNameList() {
    source = parent->nxPairs->getNxSource(panel);
    dest = parent->nxPairs->getNxDestination();

}
QStringList AEPTableModel::NXTYPE_NAMES = QStringList() << "Turnout"<< "SignalMast"<< "Full InterLock";

//int rowCount = 0;

/*public*/ int AEPTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return _rowCount;
}

/*public*/ void AEPTableModel::configureTable(JTable* table)
{
#if 0
    // allow reordering of the columns
    table->getTableHeader().setReorderingAllowed(true);

    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    table->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

    // resize columns as requested
    for (int i = 0; i < table.getColumnCount(); i++) {
        int width = getPreferredWidth(i);
        table.getColumnModel().getColumn(i).setPreferredWidth(width);
    }
#endif
    table->resizeColumnsToContents();

    configDeleteColumn(table);

}

/*public*/ QVariant AEPTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
    // get roster entry for row
    if (panel == NULL) {
        log->debug("no panel selected!");
        return "Error";
    }
    switch (col) {
        case FROMPOINTCOL:
            return parent->nxPairs->getPointAsString((NamedBean*) source.at(row), panel);
        case TOPOINTCOL:
            return parent->nxPairs->getPointAsString((NamedBean*) dest.at(row), panel);
        case ACTIVECOL:
            return isPairActive(row);
        case BOTHWAYCOL:
            return !parent->nxPairs->isUniDirection(source.at(row), panel, dest.at(row));
        case ENABLEDCOL:
            return !parent->nxPairs->isEnabled(source.at(row), panel, dest.at(row));
        case CLEARCOL:
            return tr("Clear");
        case DELETECOL:  //
            return tr("Delete");
        case TYPECOL:
            return NXTYPE_NAMES[parent->nxPairs->getEntryExitType(source.at(row), panel, dest.at(row))];
        default:
            return "";
    }
 }
 return QVariant();
}

/*public*/ bool AEPTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int col = index.column();
  int row = index.row();
    if (col == DELETECOL) {
        // button fired, delete Bean
        deleteEntryExit(row, col);
    }
    if (col == CLEARCOL) {
        parent->nxPairs->cancelInterlock(source.at(row), panel, dest.at(row));
    }
    if (col == BOTHWAYCOL) {
        bool b = !value.toBool();
        parent->nxPairs->setUniDirection(source.at(row), panel, dest.at(row), b);
    }
    if (col == ENABLEDCOL) {
        bool b = !value.toBool();
        parent->nxPairs->setEnabled(source.at(row), panel, dest.at(row), b);
    }
    if (col == TYPECOL) {
        QString val =  value.toString();
        if (val==("Turnout")) {
            parent->nxPairs->setEntryExitType(source.at(row), panel, dest.at(row), 0x00);
        } else if (val==("SignalMast")) {
            parent->nxPairs->setEntryExitType(source.at(row), panel, dest.at(row), 0x01);
        } else if (val==("Full InterLock")) {
            parent->nxPairs->setEntryExitType(source.at(row), panel, dest.at(row), 0x02);
        }
    }
    return true;
 }
 return false;
}

/*public*/ int AEPTableModel::getPreferredWidth(int col) {
    switch (col) {
        case FROMPOINTCOL:
        case TOPOINTCOL:
     return  JTextField(15).sizeHint().width();
        case ACTIVECOL:
        case BOTHWAYCOL:
        case ENABLEDCOL:
     return  JTextField(5).sizeHint().width();
        case CLEARCOL:
        case DELETECOL:  //
     return  JTextField(22).sizeHint().width();
        case TYPECOL:
     return  JTextField(10).sizeHint().width();
        default:
            log->warn("Unexpected column in getPreferredWidth: " + col);
     return  JTextField(8).sizeHint().width();
    }
}

/*protected*/ void AEPTableModel::deleteEntryExit(int row, int /*col*/) {
    NamedBean* nbSource = ((NamedBean*) source.at(row));
    NamedBean* nbDest = (NamedBean*) dest.at(row);
    parent->nxPairs->deleteNxPair(nbSource, nbDest, panel);
}

QString AEPTableModel::isPairActive(int row) const
{
    if (parent->nxPairs->isPathActive(source.at(row), dest.at(row), panel)) {
        return ("yes");
    }
    return ("");
}

//@Override
/*public*/ QVariant AEPTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {

    switch (section) {
        case FROMPOINTCOL:
            return tr("From");
        case TOPOINTCOL:
            return tr("To");
        case ACTIVECOL:
            return tr("Active");
        case DELETECOL:
            return "";
        case CLEARCOL:
            return "";
        case BOTHWAYCOL:
            return tr("Both");
        case TYPECOL:
            return "NX Type";
        case ENABLEDCOL:
            return "Disabled";
        default:
            return "<UNKNOWN>";
    }
 }
 return QVariant();
}

/*public*/ QString AEPTableModel::getColumnClass(int col) {
    switch (col) {
        case FROMPOINTCOL:
        case TOPOINTCOL:
        case ACTIVECOL:
            return "String";
        case DELETECOL:
        case CLEARCOL:
            return "JButton";
        case BOTHWAYCOL:
        case ENABLEDCOL:
            return "Boolean";
        case TYPECOL:
            return "String";
        default:
            return "";
    }
}

/*public*/ Qt::ItemFlags AEPTableModel::flags(const QModelIndex &index) const
{
 int row = index.row();
 switch (index.column())
 {
  case BOTHWAYCOL:
  {
   QObject* obj = parent->nxPairs->getEndPointLocation((NamedBean*) dest.at(row), panel);
   //if (obj instanceof PositionablePoint)
   if(qobject_cast<PositionablePoint*>(obj))
   {
    PositionablePoint* point = (PositionablePoint*) obj;
    if (point->getType() == PositionablePoint::END_BUMPER)
    {
     JOptionPane::showMessageDialog(NULL, tr("Destination location is at an End Bumper, it is not possible to do Both Way NX at this location"));
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
   }
   if (!parent->nxPairs->canBeBiDirectional(source.at(row), panel, dest.at(row)))
   {
    JOptionPane::showMessageDialog(NULL, tr("Both Way Operation can not be used if a Signal is present at both Entry and Exit points"));
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
   }
      /*if(nxPairs.getEntryExitType(source.get(row), panel, dest.get(row))!=0x00){
       JOptionPane.showMessageDialog(NULL, tr("BothWayTurnoutOnly"));
       return false;
       }*/
      return Qt::ItemIsEditable |  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  case DELETECOL:
  case CLEARCOL:
  case ENABLEDCOL:
  case TYPECOL:
  {
      return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  default:
  {
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
 }
}

/*public*/ int AEPTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return NUMCOL;
}

/*public*/ void AEPTableModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length") || e->getPropertyName()==("active"))
 {
  _rowCount = parent->nxPairs->getNxPairNumbers(panel);
  updateNameList();
  fireTableDataChanged();
 }
}
//};


/*protected*/ void AEPTableModel::configDeleteColumn(JTable* table)
{
 // have the delete column hold a button
 setColumnToHoldButton(table, AEPTableModel::DELETECOL,
         new QPushButton(tr("Delete")));

 setColumnToHoldButton(table, AEPTableModel::CLEARCOL,
         new QPushButton(tr("Clear")));

 QComboBox* typeCombo = new QComboBox(/*AEPTableModel::NXTYPE_NAMES*/);
 typeCombo->addItems(AEPTableModel::NXTYPE_NAMES);
#if 0
 TableColumn* col = table->getColumnModel().getColumn(TYPECOL);
 col.setCellEditor(new DefaultCellEditor(typeCombo));
#endif
}

/**
 * Service method to setup a column so that it will hold a button for it's
 * values
 *
 * @param table
 * @param column
 * @param sample Typical button, used for size
 */
/*protected*/ void AddEntryExitPairPanel::setColumnToHoldButton(JTable* table, int column, QPushButton* sample)
    {
    //TableColumnModel tcm = table.getColumnModel();
    // install a button renderer & editor
#if 0
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    table.setDefaultRenderer(JButton.class, buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    table.setDefaultEditor(JButton.class, buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    table.setRowHeight(sample.getPreferredSize().height);
    table.getColumnModel().getColumn(column)
            .setPreferredWidth((sample.getPreferredSize().width) + 4);
#endif
}

//static class ValidPoints {

//    NamedBean bean;
//    String description;

    ValidPoints::ValidPoints(NamedBean* bean, QString description)
    {
        this->bean = bean;
        this->description = description;
    }

    NamedBean* ValidPoints::getPoint() {
        return bean;
    }

    QString ValidPoints::getDescription() {
        return description;
    }
//};


/*private*/ void AddEntryExitPairPanel::initializeColorCombo(QComboBox* colorCombo)
{
 colorCombo->clear();
 for (int i = 0; i < numColors; i++)
 {
     colorCombo->addItem(colorText[i]);
 }
}

/*private*/ void AddEntryExitPairPanel::setColorCombo(QComboBox* colorCombo, QColor color)
{
 for (int i = 0; i < numColors; i++)
 {
  if (color == colorCode[i])
  {
   colorCombo->setCurrentIndex(i);
   return;
  }
 }
}

/*private*/ QColor AddEntryExitPairPanel::getSelectedColor(QComboBox* colorCombo)
    {
    return (colorCode[colorCombo->currentIndex()]);
}

/**
 * Utility methods for converting between string and color Note: These names
 * are only used internally, so don't need a resource bundle
 */
/*protected*/ void AddEntryExitPairPanel::optionWindow(JActionEvent* /*e*/)
{
 if (optionsFrame == NULL)
 {
  optionsFrame = new JmriJFrameX(tr("Entry Exit Options"), false, true);
  //optionsFrame.addHelpMenu("package.jmri.jmrit.dispatcher.Options", true);
//  optionsPane = optionsFrame.getContentPane();
//  optionsPane.setLayout(new BoxLayout(optionsFrame.getContentPane(), BoxLayout.Y_AXIS));
  QWidget* centralWidget = new QWidget;
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
  optionsFrame->setCentralWidget(centralWidget);
  clearEntry->setCurrentIndex(nxPairs->getClearDownOption());
  //QWidget* p1 = new QWidget();
  FlowLayout* p1Layout = new FlowLayout;
  //clearEntry.addActionListener(clearEntryListener);
  clearEntry->setToolTip("set the action for when the NX buttons are reselected");
  p1Layout->addWidget(new QLabel(tr("Route Reselection Option")));
  p1Layout->addWidget(clearEntry);
  centralWidgetLayout->addLayout(p1Layout);
  //QWidget* p2 = new QWidget();
  FlowLayout* p2Layout = new FlowLayout;
  initializeColorCombo(settingTrackColorBox);
  setColorCombo(settingTrackColorBox, nxPairs->getSettingRouteColor());
//  ActionListener settingTrackColorListener = new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {

//          if (getSelectedColor(settingTrackColorBox) != NULL) {
//              durationSetting.setEnabled(true);
//          } else {
//              durationSetting.setEnabled(false);
//          }
//      }
//  };

//  settingTrackColorBox.addActionListener(settingTrackColorListener);
  connect(settingTrackColorBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_settingtrackColorBox_currentIndexChanged(QString)));
  p2Layout->addWidget(new QLabel(tr("Initial colour of path while route is Setup")));
  p2Layout->addWidget(settingTrackColorBox);
  centralWidgetLayout->addLayout(p2Layout);
  durationSetting->setText( QString::number(nxPairs->getSettingTimer()));
  if (nxPairs->useDifferentColorWhenSetting())
  {
   durationSetting->setEnabled(true);
  }
  else
  {
   durationSetting->setEnabled(false);
  }
  //QWidget p3 = new QWidget();
  FlowLayout* p3Layout = new FlowLayout;
  p3Layout->addWidget(new QLabel(tr("Duration of setting Colour (ms)")));
  p3Layout->addWidget(durationSetting);
  centralWidgetLayout->addLayout(p3Layout);

  //QWidget p4 = new QWidget();
  FlowLayout* p4Layout = new FlowLayout;
  p4Layout->addWidget(dispatcherUse);
  dispatcherUse->setChecked(nxPairs->getDispatcherIntegration());
  centralWidgetLayout->addLayout(p4Layout);

  QPushButton* ok = new QPushButton(tr("Okay"));
  centralWidgetLayout->addWidget(ok);
//  ok.addActionListener(
//          new ActionListener() {
//              /*public*/ void actionPerformed(ActionEvent e) {
//                  optionSaveButton();
//              }
//          });
  connect(ok, SIGNAL(clicked()), this, SLOT(optionSaveButton()));
 }
 optionsFrame->adjustSize();
 optionsFrame->setVisible(true);
}

void AddEntryExitPairPanel::on_settingtrackColorBox_currentIndexChanged(QString)
{
 if (getSelectedColor(settingTrackColorBox) != QColor()) {
     durationSetting->setEnabled(true);
 } else {
     durationSetting->setEnabled(false);
 }
}

void AddEntryExitPairPanel::optionSaveButton()\
{
 int settingTimer = 2000;
 bool bOk;
 settingTimer = durationSetting->text().toInt(&bOk);
 if(!bOk)
 {
  JOptionPane::showMessageDialog(NULL, tr("Duration of setting color should be a number!"));
     return;
 }
 nxPairs->setSettingTimer(settingTimer);
 nxPairs->setSettingRouteColor(getSelectedColor(settingTrackColorBox));
 nxPairs->setClearDownOption(clearEntry->currentIndex());
 nxPairs->setDispatcherIntegration(dispatcherUse->isChecked());
 optionsFrame->setVisible(false);
}

//    static final Logger log = LoggerFactory.getLogger(AddEntryExitPairPanel.class.getName());
//}

