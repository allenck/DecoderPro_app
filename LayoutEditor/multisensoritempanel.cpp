#include "multisensoritempanel.h"
#include "picklistmodel.h"
#include "borderlayout.h"
#include "swingconstants.h"
#include "multisensoricon.h"
#include <QMessageBox>
#include "editor.h"
#include "itempalette.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "multisensoricondialog.h"
#include "tablecolumn.h"
#include "joptionpane.h"
#include "multisensoriconxml.h"
#include "joptionpane.h"

//MultiSensorItemPanel::MultiSensorItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
// /*public*/ class MultiSensorItemPanel extends TableItemPanel {


/*public*/ MultiSensorItemPanel::MultiSensorItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor,QWidget *parent)
 : TableItemPanel(parentFrame, type, family, model, editor, parent)
{
  //super(parentFrame, type, family, model, editor);
  setToolTip(tr("Drag the sensor selections from the table to add the multisensor to the panel"));
  setObjectName("MultiSensorItemPanel");
  log->setDebugEnabled(true);
}

/*protected*/ QWidget* MultiSensorItemPanel::initTablePanel(PickListModel* model, Editor* /*editor*/) {
    _table = model->makePickTable();
    ROW_HEIGHT = _table->getRowHeight();
    TableColumn* column = new TableColumn(PickListModel::POSITION_COL);
    column->setHeaderValue("Position");
    _table->addColumn(column);
    _selectionModel = new MultiSensorSelectionModel(model, this);
    _table->setSelectionModel(_selectionModel);
    _table->getSelectionModel()->setSelectionMode(ListSelectionModel::SINGLE_SELECTION);
    connect(_table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), _selectionModel, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));

    QWidget* topPanel = new QWidget();
    QVBoxLayout* topPanelLayout;
    topPanel->setLayout(topPanelLayout = new QVBoxLayout());
     topPanelLayout->addWidget(new JLabel(model->getName()), 0, Qt::AlignTop | Qt::AlignHCenter);
    //_scrollPane = new JScrollPane(_table);
     topPanelLayout->addWidget(_table, 1, Qt::AlignCenter);
    topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));

    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout);
    _addTableButton = new QPushButton(tr("Create New Item"));
//    _addTableButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                makeAddToTableWindow();
//            }
//    });
    connect(_addTableButton, SIGNAL(clicked()), this, SLOT(makeAddToTableWindow()));
    _addTableButton->setToolTip(tr("Press to add a new item to the above table"));
    panel->layout()->addWidget(_addTableButton);

    int size = 6;
    if (_family!= "") {
        QMap<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
        if (map != nullptr)
        {
            size = map->size();
        }
    }
    _selectionModel->setPositionRange(size-3);
    QPushButton* clearSelectionButton = new QPushButton(tr("Clear Table Selections"));
//    clearSelectionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                clearSelections();
//            }
//    });
    connect(clearSelectionButton, SIGNAL(clicked()), this, SLOT(clearSelections()));
    clearSelectionButton->setToolTip(tr("Clear selected table rows"));
    panel->layout()->addWidget(clearSelectionButton);
    topPanelLayout->addWidget(panel,0, Qt::AlignBottom);
    _table->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    //_scrollPane.setToolTipText(tr("Drag a row from the table to add a label of the item to the panel"));
    topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    return topPanel;
}

/*public*/ void MultiSensorItemPanel::clearSelections()
{
    _selectionModel->clearSelection();
    int size = 6;
//        if (_family!=NULL) {
//            Hashtable<String, NamedIcon> map = ItemPalette.getIconMap(_itemType, _family);
//            size = map.size();
//        }
    QMap<QString, NamedIcon*>* map = getIconMap();
    if (map != nullptr) {
        size = map->size();
    }
    _selectionModel->setPositionRange(size-3);
}


/*protected*/ void MultiSensorItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString /*displayKey*/) {
    TableItemPanel::makeDndIconPanel(iconMap, "second");
}

/*protected*/ void MultiSensorItemPanel::initIconFamiliesPanel() {
    TableItemPanel::initIconFamiliesPanel();
    if (_multiSensorPanel == nullptr)
    {
     makeMultiSensorPanel();
     _iconFamilyPanel->layout()->addWidget(_multiSensorPanel); // Panel containing up-dn, le-ri radio buttons
    }
}

/*private*/ void MultiSensorItemPanel::makeMultiSensorPanel() {
    _multiSensorPanel = new QWidget();
    _multiSensorPanel->setLayout(new QVBoxLayout(_multiSensorPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel2 = new QWidget();
    panel2->setLayout(new QHBoxLayout);
    QButtonGroup* group2 = new QButtonGroup();
    QRadioButton* button = new QRadioButton(tr("Click Left/Right"));
//    button.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _upDown = false;
//            }
//        });
    connect(button, SIGNAL(clicked()), this, SLOT(buttonLR_clicked()));
    group2->addButton(button);
    panel2->layout()->addWidget(button);
    button->setChecked(true);
    button = new QRadioButton(tr("Click Up/Down"));
//    button.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _upDown = true;
//            }
//        });
    connect(button, SIGNAL(clicked()), this, SLOT(buttonLR_clicked()));
    group2->addButton(button);
    panel2->layout()->addWidget(button);
    _multiSensorPanel->layout()->addWidget(panel2);
    _multiSensorPanel->repaint();
}
void MultiSensorItemPanel::buttonLR_clicked() { _upDown=false;}
void MultiSensorItemPanel:: buttonUD_clicked() {_upDown = true;}

/*protected*/ void MultiSensorItemPanel::setFamily(QString family) {
    TableItemPanel::setFamily(family);
    if (_multiSensorPanel==NULL) {
      makeMultiSensorPanel();
      _iconFamilyPanel->layout()->addWidget(_multiSensorPanel);
    }
    _iconFamilyPanel->repaint();
    updateFamiliesPanel();
    setSelections();
}
/*protected*/ void MultiSensorItemPanel::setSelections() {
    QVector<int> positions = _selectionModel->getPositions();
    clearSelections();
    int len = qMin(positions.length(), _selectionModel->getPositions().length());
    for (int i=0; i<len; i++) {
        if (positions[i] > -1) {
            _selectionModel->setSelectionInterval(positions[i], positions[i]);
        }
    }
}

//@OverrideQMap
/*protected*/ void MultiSensorItemPanel::openDialog(QString type, QString family, QMap<QString, NamedIcon*>* iconMap)
{
 closeDialogs();
 _dialog = new MultiSensorIconDialog(type, family, this, iconMap);
 _dialog->sizeLocate();
}

/**
* Used by Panel Editor to make updates the icon(s)
* into the user's Panel.
*/
/*public*/ QVector<NamedBean*> MultiSensorItemPanel::getTableSelections() {
    return _selectionModel->getSelections();
}

/*public*/ QVector<int> MultiSensorItemPanel::getPositions() {
    return _selectionModel->getPositions();
}

/*public*/ bool MultiSensorItemPanel::getUpDown() {
    return _upDown;
}

/*public*/ void MultiSensorItemPanel::setSelection(NamedBean* bean) {
    int row = _model->getIndexOf(bean);
    if (row>=0) {
        _selectionModel->setSelectionInterval(row, row);
        //_scrollPane.getVerticalScrollBar().setValue(row*ROW_HEIGHT);
    } else {
        valueChanged(new ListSelectionEvent(this, row,row, false));
    }
}

/*public*/ void MultiSensorItemPanel::setUpDown(bool upDown) {
    _upDown = upDown;
}

/*public*/ /*static*/ /*final*/ QStringList MultiSensorItemPanel::POSITION = QStringList() << "first" << "second"<< "third"<< "fourth"<< "fifth"<< "sixth"<< "seventh"<< "eighth"<< "nineth"<< "tenth" ;

/*static*/ /*public*/ QString MultiSensorItemPanel::getPositionName(int index) {
        return POSITION[index];
    }
// /*protected*/ class MultiSensorSelectionModel : DefaultListSelectionModel {

#if 0
/*public*/ void MultiSensorItemPanel::updateFamilyIcons()
{
 if(_currentIconMap == nullptr)
  return;
 QStringList keys = _currentIconMap->keys();
 if(_selectionModel->_positions.isEmpty())
  _selectionModel->_positions= QVector<int>(MultiSensorItemPanel::POSITION.count());
 for(int i =0; i < MultiSensorItemPanel::POSITION.count(); i++)
 {
  QString name = MultiSensorItemPanel::POSITION.at(i);
  int j = keys.indexOf(name);
  if(j >= 0)
  {
   _selectionModel->_positions.replace(i, j);
   //_selectionModel->_selections.replace(i, _currentIconMap->value(name));
  }
 }
}
#endif

MultiSensorSelectionModel::MultiSensorSelectionModel(PickListModel* tableModel, MultiSensorItemPanel* self)
 : DefaultListSelectionModel(self)
{
 //super();
 log = new Logger("MultiSensorSelectionModel");
 setObjectName("MultiSensorSelectionModel");
 log->setDebugEnabled(true);

 _tableModel = tableModel;
 this->self = self;
 setPositionRange(0);
}

/*protected*/ QVector<NamedBean*> MultiSensorSelectionModel::getSelections() {
    if (log->isDebugEnabled()) log->debug("getSelections: size= "+QString::number(_selections.size())+
                                        ", _nextPosition= "+QString::number(_nextPosition));
    return _selections;
}

/*protected*/ QVector<int> MultiSensorSelectionModel::getPositions() {
    QVector<int> positions =  QVector<int>(_positions.length());
    //System.arraycopy(_positions, 0, positions, 0, _positions.length());
    for (int i=0; i < _positions.count(); i++) {
     positions.replace(i, _positions.at(i));
    }
    return positions;
}

/*protected*/ int MultiSensorSelectionModel::getNextPosition() {
    return _nextPosition;
}

/*protected*/ void MultiSensorSelectionModel::setPositionRange(int size)
{
 if (log->isDebugEnabled()) log->debug("setPositionRange: size= "+ QString::number(size));
 if (size > self->POSITION.length()) {
     size = self->POSITION.length();
 }
 _positions =  QVector<int>(size, -1);
// for (int i=0; i < size; i++)
// {
//  _positions.append(-1);
// }
 _selections =  QVector<NamedBean*>(size, nullptr);
 _nextPosition = 0;
}

/*************** DefaultListSelectionModel overrides ********************/

/*public*/ bool MultiSensorSelectionModel::isSelectedIndex(int index)
{
 for (int i=0; i<_positions.length(); i++)
 {
  if (_positions[i] == index)
  {
   if (log->isDebugEnabled()) log->debug("isSelectedIndex("+QString::number(index)+") returned true");
   return true;
  }
 }
 if (log->isDebugEnabled()) log->debug("isSelectedIndex("+QString::number(index)+") returned false");
 return false;
}

/*public*/ void MultiSensorSelectionModel::clearSelection()
{
 if (log->isDebugEnabled()) log->debug("clearSelection()");
 for (int i=0; i<_positions.length(); i++)
 {
  if (_positions[i] >= 0)
  {
   _tableModel->setValueAt("", _positions.at(i), PickListModel::POSITION_COL);
   DefaultListSelectionModel::setSelectionInterval(_positions[i], _positions.at(i));
   DefaultListSelectionModel::clearSelection();
   _positions.replace(i, -1);
  }
 }
 _selections = QVector<NamedBean*>(_positions.length(), nullptr);
 _nextPosition = 0;
}

/*public*/ void MultiSensorSelectionModel::addSelectionInterval(int index0, int index1)
{
 if (log->isDebugEnabled()) log->debug("addSelectionInterval("+QString::number(index0)+", "+QString::number(index1)+") - stubbed");
//            super.addSelectionInterval(index0, index1);
}

/*public*/ void MultiSensorSelectionModel::setSelectionInterval(int row, int index1)
{
 if (_nextPosition>=_positions.length())
 {
  JOptionPane::showMessageDialog(self->_paletteFrame,
    tr("This Multisensor has only %1 positions.  Clear selections to change position order./nFor additional positions, add another icon.").arg(self->_selectionModel->getPositions().length()),
    tr("Warning"), JOptionPane::WARNING_MESSAGE);
  return;
 }
 if (log->isDebugEnabled())
  log->debug("setSelectionInterval("+QString::number(row)+", "+QString::number(index1)+")");
 NamedBean* bean = _tableModel->getBeanAt(row);
 if(log->isDebugEnabled())
  log->debug(tr("bean selected: %1").arg(bean->getDisplayName()));
 //QString position = _tableModel->getValueAt(row, PickListModel::POSITION_COL);
 QString position = _tableModel->data(_tableModel->index(row, PickListModel::POSITION_COL),Qt::DisplayRole).toString();
 if (position!=NULL && position.length()>0)
 {
  JOptionPane::showMessageDialog(self->_paletteFrame,
   tr("Sensor %1 is already set to be the %2 position.").arg(bean->getDisplayName()).arg(position),
   tr("warning"), JOptionPane::WARNING_MESSAGE);
 } else {
  //_tableModel->setValueAt(tr(self->POSITION[_nextPosition]), row, PickListModel::POSITION_COL);
  _tableModel->setData(_tableModel->index(row, PickListModel::POSITION_COL),QVariant(self->POSITION.at(_nextPosition)),Qt::EditRole);
  _selections.replace(_nextPosition, bean);
  _positions[_nextPosition] = row;
  _nextPosition++;
  DefaultListSelectionModel::setSelectionInterval(row, row);
 }
}


/*protected*/ DragJLabel* MultiSensorItemPanel::getDragger(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, NamedIcon *icon) {
    return new MSIconDragJLabel(flavor, map, icon, this);
}

//@Override
/*public*/ bool MultiSensorItemPanel::oktoUpdate() {
    QVector<NamedBean*> selections = _selectionModel->getSelections();
    if (selections.isEmpty()) {
        JOptionPane::showMessageDialog(this, tr("Select a row in the table to provide a device for this icon."),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    }
    if (selections.size() < _selectionModel->getPositions().length()) {
        JOptionPane::showMessageDialog(this,
                tr("Multisensor needs %1 positions. Select more rows from the table.").arg(_selectionModel->getPositions().length()),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    }
    if (getIconMap() == nullptr) {
        return false;
    }
    return true;
}


///*protected*/ class MSIconDragJLabel extends DragJLabel {
//    Hashtable <String, NamedIcon> iconMap;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ MSIconDragJLabel::MSIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon *icon, MultiSensorItemPanel* self)
 : DragJLabel(flavor, icon, self )
{
 //super(flavor);
 iconMap = map;
 this->self = self;
}

//@Override
/*protected*/ bool MSIconDragJLabel::okToDrag() {
    return self->oktoUpdate();
}

/*public*/ bool MSIconDragJLabel::isDataFlavorSupported(DataFlavor* flavor)
{
 return DragJLabel::isDataFlavorSupported(flavor);
}

/*public*/ QObject* MSIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 if (iconMap==NULL)
 {
  self->log->error("IconDragJLabel.getTransferData: iconMap is NULL!");
  return NULL;
 }
 self->_selectionModel->getPositions();
 QVector<NamedBean*> selections = self->_selectionModel->getSelections();
 if (selections.isEmpty() || selections.size() < self->_selectionModel->getPositions().length()) {
     return nullptr;
 }

 MultiSensorIcon* ms = new MultiSensorIcon(self->_editor);
 ms->setInactiveIcon(new NamedIcon(iconMap->value("SensorStateInactive")));
 ms->setInconsistentIcon(new NamedIcon(iconMap->value("BeanStateInconsistent")));
 ms->setUnknownIcon(new NamedIcon(iconMap->value("BeanStateUnknown")));
 for (int i=0; i<selections.size(); i++) {
     ms->addEntry(selections.at(i)->getDisplayName(), new NamedIcon(iconMap->value(self->POSITION[i])));
 }
 self->_selectionModel->clearSelection();
 ms->setFamily(self->_family);
 ms->setUpDown(self->_upDown);
 ms->setLevel(Editor::SENSORS);
 return ms;
}
//};
QByteArray MSIconDragJLabel::mimeData()
{
 if (iconMap==NULL)
 {
  self->log->error("IconDragJLabel.getTransferData: iconMap is NULL!");
  return NULL;
 }
 self->_selectionModel->getPositions();
 QVector<NamedBean*> selections = self->_selectionModel->getSelections();
 if (selections.isEmpty() || selections.size() < self->_selectionModel->getPositions().length()) {
     return nullptr;
 }

 MultiSensorIcon*  icon = new MultiSensorIcon(self->_editor);
  icon->setInactiveIcon(new NamedIcon(iconMap->value("SensorStateInactive")));
  icon->setInconsistentIcon(new NamedIcon(iconMap->value("BeanStateInconsistent")));
  icon->setUnknownIcon(new NamedIcon(iconMap->value("BeanStateUnknown")));
 for (int i=0; i<selections.size(); i++) {
      icon->addEntry(selections.at(i)->getDisplayName(), new NamedIcon(iconMap->value(self->POSITION[i])));
 }
 self->_selectionModel->clearSelection();
  icon->setFamily(self->_family);
  icon->setUpDown(self->_upDown);
  icon->setLevel(Editor::SENSORS);

 MultiSensorIconXml* xml = new MultiSensorIconXml();
 QDomElement e = xml->store((QObject*)icon);
 xml->doc.appendChild(e);
 QByteArray xmldata;
 xmldata.append(xml->doc.toString());
 return xmldata;
}
