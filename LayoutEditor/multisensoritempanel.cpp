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
#include "icondialog.h"

//MultiSensorItemPanel::MultiSensorItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
// /*public*/ class MultiSensorItemPanel extends TableItemPanel {


/*public*/ MultiSensorItemPanel::MultiSensorItemPanel(JmriJFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent) : TableItemPanel(parentFrame, type, family, model, editor, parent)
{
    //super(parentFrame, type, family, model, editor);
    _upDown = false;
    //setToolTipText(tr("ToolTipDragSelection"));
    setToolTip(tr("Drag the sensor selections from the table to add the multisensor to the panel"));
}

/*protected*/ QWidget* MultiSensorItemPanel::initTablePanel(PickListModel* model, Editor* /*editor*/) {
    _table = model->makePickTable();
    ROW_HEIGHT = _table->rowHeight(0);
//    TableColumn column = new TableColumn(PickListModel::POSITION_COL);
//    column.setHeaderValue("Position");
//    _table.addColumn(column);
    _selectionModel = new MultiSensorSelectionModel(model, this);
//    _table->setSelectionModel(_selectionModel);
//    _table->getSelectionModel().setSelectionMode(ListSelectionModel::SINGLE_SELECTION);

    QWidget* topPanel = new QWidget();
    topPanel->setLayout(new BorderLayout());
    ((BorderLayout*)topPanel->layout())->addWidget(new JLabel(model->getName(), SwingConstants::CENTER), BorderLayout::North);
    //_scrollPane = new JScrollPane(_table);
    ((BorderLayout*)topPanel->layout())->addWidget(_table, BorderLayout::Center);
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
    if (_family!=NULL) {
        QHash<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
        size = map->size();
    }
    _selectionModel->setPositionRange(size-3);
    QPushButton* clearSelectionButton = new QPushButton(tr("Clear Selection"));
//    clearSelectionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                clearSelections();
//            }
//    });
    connect(clearSelectionButton, SIGNAL(clicked()), this, SLOT(clearSelections()));
    clearSelectionButton->setToolTip(tr("Clear selected table rows"));
    panel->layout()->addWidget(clearSelectionButton);
    ((BorderLayout*)topPanel->layout())->addWidget(panel, BorderLayout::South);
    _table->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    //_scrollPane.setToolTipText(tr("Drag a row from the table to add a label of the item to the panel"));
    topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    return topPanel;
}
/*public*/ void MultiSensorItemPanel::clearSelections() {
    _selectionModel->clearSelection();
    int size = 6;
//        if (_family!=NULL) {
//            Hashtable<String, NamedIcon> map = ItemPalette.getIconMap(_itemType, _family);
//            size = map.size();
//        }
    if (_currentIconMap!=NULL) {
        size = _currentIconMap->size();
    }
    _selectionModel->setPositionRange(size-3);
}

/*protected*/ void MultiSensorItemPanel::makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString /*displayKey*/) {
    TableItemPanel::makeDndIconPanel(iconMap, "second");
}

/*protected*/ void MultiSensorItemPanel::initIconFamiliesPanel() {
    TableItemPanel::initIconFamiliesPanel();
    makeMultiSensorPanel();
    _iconFamilyPanel->layout()->addWidget(_multiSensorPanel);
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
    if (_multiSensorPanel!=NULL) {
//        _iconFamilyPanel->remove(_multiSensorPanel);
    }
    makeMultiSensorPanel();
    _iconFamilyPanel->layout()->addWidget(_multiSensorPanel);
    _iconFamilyPanel->repaint();
    updateFamiliesPanel();
    setSelections();
}
/*protected*/ void MultiSensorItemPanel::setSelections() {
    QList<int> positions = _selectionModel->getPositions();
    clearSelections();
    int len = qMin(positions.length(), _selectionModel->getPositions().length());
    for (int i=0; i<len; i++) {
        if (positions[i]>-1) {
            _selectionModel->setSelectionInterval(positions[i], positions[i]);
        }
    }
}

/*protected*/ void MultiSensorItemPanel::openEditDialog() {
#if 0 // TODO:
    IconDialog* dialog = new MultiSensorIconDialog(_itemType, _family, this, _currentIconMap);
    dialog->sizeLocate();
#endif
}

/*protected*/ void MultiSensorItemPanel::createNewFamily(QString type)
{
#if 0 // TODO:
    IconDialog dialog = new MultiSensorIconDialog(_itemType, NULL, this, NULL);
    dialog->sizeLocate();
#endif
}

/**
* Used by Panel Editor to make updates the icon(s)
* into the user's Panel.
*/
/*public*/ QList<NamedBean*>* MultiSensorItemPanel::getTableSelections() {
    return _selectionModel->getSelections();
}

/*public*/ QList<int> MultiSensorItemPanel::getPositions() {
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
        valueChanged();
    }
}

/*public*/ void MultiSensorItemPanel::setUpDown(bool upDown) {
    _upDown = upDown;
}

/*public*/ /*static*/ /*final*/ QStringList MultiSensorItemPanel::POSITION = QStringList() << "first" << "second"<< "third"<< "fourth"<< "fifth"<< "sixth"<< "seventh"<< "eighth"<< "nineth"<< "tenth" ;

// /*protected*/ class MultiSensorSelectionModel : DefaultListSelectionModel {


    MultiSensorSelectionModel::MultiSensorSelectionModel(PickListModel* tableModel, MultiSensorItemPanel* self)
    {
     //super();
     log = new Logger("MultiSensorSelectionModel");

     _tableModel = tableModel;
     this->self = self;
     setPositionRange(0);
    }

    /*protected*/ QList<NamedBean*>* MultiSensorSelectionModel::getSelections() {
        if (log->isDebugEnabled()) log->debug("getSelections: size= "+QString::number(_selections->size())+
                                            ", _nextPosition= "+QString::number(_nextPosition));
        if (_nextPosition < _positions.length()) {
            return NULL;
        }
        return _selections;
    }

    /*protected*/ QList<int> MultiSensorSelectionModel::getPositions() {
        QList<int> positions =  QList<int>();//int[_positions.length()];
        //System.arraycopy(_positions, 0, positions, 0, _positions.length());
        foreach (int i, _positions) {
         positions.append(i);
        }
        return positions;
    }

    /*protected*/ int MultiSensorSelectionModel::getNextPosition() {
        return _nextPosition;
    }

    /*protected*/ void MultiSensorSelectionModel::setPositionRange(int size)
    {
     if (log->isDebugEnabled()) log->debug("setPositionRange: size= "+size);
     if (size>self->POSITION.length()) {
         size = self->POSITION.length();
     }
     _positions =  QList<int>(); //int[size];
     for (int i=0; i<size; i++)
     {
      _positions.append(-1);
     }
     _selections =  new QList<NamedBean*>(/*size*/);
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
       _tableModel->setValueAt(QVariant(), _positions.at(i), PickListModel::POSITION_COL);
       DefaultListSelectionModel::setSelectionInterval(_positions[i], _positions.at(i));
       DefaultListSelectionModel::clearSelection();
       _positions.replace(i, -1);
      }
     }
     _selections = new QList<NamedBean*>();//_positions.length());
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
//            JOptionPane.showMessageDialog(_paletteFrame,
//                    java.text.MessageFormat.format(
//                        tr("NeedIcon"), _selectionModel.getPositions().length),
//                        ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(self->_paletteFrame, tr("Warning"), tr("This Multisensor has only %1} positions.  Clear selections to change position order./nFor additional positions, add another icon.").arg(self->_selectionModel->getPositions().length()));
         return;
     }
     if (log->isDebugEnabled()) log->debug("setSelectionInterval("+QString::number(row)+", "+QString::number(index1)+")");
     NamedBean* bean = _tableModel->getBeanAt(row);
     //QString position = _tableModel->getValueAt(row, PickListModel::POSITION_COL);
     QString position = _tableModel->data(_tableModel->index(row, PickListModel::POSITION_COL),Qt::DisplayRole).toString();
     if (position!=NULL && position.length()>0)
     {
//            JOptionPane.showMessageDialog(_paletteFrame,
//                    java.text.MessageFormat.format(tr("DuplicatePosition"),
//                        new Object[]{bean.getDisplayName(), position}),
//                    ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(self->_paletteFrame, tr("Warning"), tr("Sensor %1 is already set to be the %2 position.").arg(bean->getDisplayName()).arg(position));
  } else {
      //_tableModel->setValueAt(tr(self->POSITION[_nextPosition]), row, PickListModel::POSITION_COL);
      _tableModel->setData(_tableModel->index(row, PickListModel::POSITION_COL),QVariant(self->POSITION.at(_nextPosition)),Qt::EditRole);
      _selections->append(/*_nextPosition,*/ bean);
      _positions[_nextPosition] = row;
      _nextPosition++;
      DefaultListSelectionModel::setSelectionInterval(row, row);
     }
    }


/*protected*/ DragJLabel* MultiSensorItemPanel::getDragger(DataFlavor* flavor, QHash<QString, NamedIcon*>* map) {
    return new MSIconDragJLabel(flavor, map,this);
}

///*protected*/ class MSIconDragJLabel extends DragJLabel {
//    Hashtable <String, NamedIcon> iconMap;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ MSIconDragJLabel::MSIconDragJLabel(DataFlavor* flavor, QHash<QString, NamedIcon*>* map, MultiSensorItemPanel* self) : DragJLabel(flavor, self)
{
 //super(flavor);
 iconMap = map;
 this->self = self;
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

 MultiSensorIcon* ms = new MultiSensorIcon(self->_editor);
 ms->setInactiveIcon(new NamedIcon(iconMap->value("SensorStateInactive")));
 ms->setInconsistentIcon(new NamedIcon(iconMap->value("BeanStateInconsistent")));
 ms->setUnknownIcon(new NamedIcon(iconMap->value("BeanStateUnknown")));
 QList<NamedBean*>* selections = self->_selectionModel->getSelections();
 if (selections==NULL)
 {
//  JOptionPane.showMessageDialog(_paletteFrame,
//                java.text.MessageFormat.format(
//                    tr("NeedPosition"), _selectionModel.getPositions().length),
//                    ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(self->_paletteFrame, tr("Warning"), tr("Multisensor needs %1 positions.  Select more rows from the table.").arg(self->_selectionModel->getPositions().length()));
  return NULL;
 }
 for (int i=0; i<selections->size(); i++) {
        ms->addEntry(selections->at(i)->getDisplayName(), new NamedIcon(iconMap->value(self->POSITION[i])));
    }
    self->_selectionModel->clearSelection();
    ms->setFamily(self->_family);
    ms->setUpDown(self->_upDown);
    ms->setLevel(Editor::SENSORS);
    return ms;
}
//};
