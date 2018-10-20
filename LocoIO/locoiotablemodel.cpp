#include "locoiotablemodel.h"
#include "locoiodata.h"
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>
#include "lnconstants.h"
#include "jtable.h"
#include "loggerfactory.h"

//LocoIOTableModel::LocoIOTableModel(QObject *parent) :
//    AbstractTableModel(parent)
//{
//}
/**
 * Basic Configurer for LocoIO hardware.
 * <P>
 * This code derves the SV values from the user-selected mode and address; this
 * is different from earlier versions where the user was expected to do the
 * derivation manually. This derivation is complicated by the fact that the
 * "mode" SV[port.0] in the LocoIO doesn't fully specify the operation being
 * done - additional bits in "v2" SV[port.2] are also used. For example, 0x80 is
 * both turnout closed and turnout high. We read and write the mode SV _last_ to
 * handle this.
 * <P>
 * The "addr" field is constructed from (or causes the construction of,
 * depending on whether we are reading or writing...) value1 and value2. In
 * particular, value2 requires knowledge of the mode being set. When "capturing"
 * a turnout address (where we don't have a mode setting) we presume that the
 * address seen in the OPC_SW_REQ packet is for a fixed contact, and interpret
 * the bits in that context.
 * <P>
 * The timeout code is modelled after that in jmri,jmrix.AbstractProgrammer,
 * though there are significant modifications.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version	$Revision: 28746 $
 */
///*public*/ class LocoIOTableModel
//        extends javax.swing.table.AbstractTableModel
//        implements java.beans.PropertyChangeListener {

/**
*
*/
/*private*/ static /*final*/ long serialVersionUID = 145067099477782903L;
///*private*/ String maxSizeMode = "";


/*public*/ /*static*/ /*final*/ int LocoIOTableModel::HIGHESTCOLUMN = LocoIOTableModel::WRITECOLUMN + 1;

/**
* Primary constructor. Initializes all the arrays.
*/
/*public*/ LocoIOTableModel::LocoIOTableModel(LocoIOData* ldata, QObject *parent) :
  AbstractTableModel(parent) {
//super();
 _numRows = 16;
 msg =  QVector<QString>(_numRows);
 status = NULL;
 buttonMap = new QMap<int, QSignalMapper*>();

inHex = true;
// references to external resources
liodata = ldata;
//ldata->addPropertyChangeListener(this);
connect(ldata, SIGNAL(notifyPropertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void LocoIOTableModel::propertyChange(PropertyChangeEvent* evt)
{
 // String s = "LocoIOTableModel: " + evt.getPropertyName() + " := " + evt.getNewValue() + " from " + evt.getSource();
 if (evt->getPropertyName()==("PortChange"))
 {
  int i = evt->getNewValue().toInt();
  int v = i;
  // System.out.println(s + " ROW = " + v);
  fireTableRowsUpdated(v, v);
 }
 else
 {
  // System.out.println(s);
 }
}

// basic methods for AbstractTableModel implementation
/*public*/ int LocoIOTableModel::rowCount(const QModelIndex &parent) const
{
 return _numRows;
}

/*public*/ int LocoIOTableModel::columnCount(const QModelIndex &parent) const
{
return HIGHESTCOLUMN;
}

/*public*/ QVariant LocoIOTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
   case PINCOLUMN:
       return "Port";
   case MODECOLUMN:
       return "Action";
   case ADDRCOLUMN:
       return "Address";
   case SV0COLUMN:
       return "SV";
   case SV1COLUMN:
       return "Value1";
   case SV2COLUMN:
       return "Value2";
   case CAPTURECOLUMN:
       return "";
   case READCOLUMN:
       return "";
   case WRITECOLUMN:
       return "";
   default:
       return "unknown";
  }
 }
 return QVariant();
}

///*public*/ Class<?> getColumnClass(int col) {
//switch (col) {
//    case PINCOLUMN:
//        return String.class;
//    case MODECOLUMN:
//        return String.class;
//    case ADDRCOLUMN:
//        return String.class;
//    case SV0COLUMN:
//        return String.class;
//    case SV1COLUMN:
//        return String.class;
//    case SV2COLUMN:
//        return String.class;
//    case CAPTURECOLUMN:
//        return JButton.class;
//    case READCOLUMN:
//        return JButton.class;
//    case WRITECOLUMN:
//        return JButton.class;
//    default:
//        return NULL;
//}
//}

/*public*/ Qt::ItemFlags LocoIOTableModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags f = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 Qt::ItemFlags editable = f | Qt::ItemIsEditable;
 switch (index.column())
 {
    case PINCOLUMN:
        return f;
    case MODECOLUMN:
        return editable;
    case ADDRCOLUMN:
        return editable;
    case SV0COLUMN:
        return f;
    case SV1COLUMN:
        return f;
    case SV2COLUMN:
        return f;
    case CAPTURECOLUMN:
        return editable;
    case READCOLUMN:
        return editable;
    case WRITECOLUMN:
        return editable;
    default:
        return f;
 }
 return 0;
}

/*public*/ QVariant LocoIOTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  switch (index.column()) {
    case PINCOLUMN:
        return (row + 1);  // Ports 1 to 16
    case MODECOLUMN:
        return liodata->getMode(row);
    case ADDRCOLUMN:
        return (liodata->getAddr(row) == 0 ? "<none>" : QString::number(liodata->getAddr(row)));
    case SV0COLUMN:
        return (inHex) ? "0x" + QString::number(liodata->getSV(row),16) : QString::number(liodata->getSV(row));
    case SV1COLUMN:
        return (inHex) ? "0x" + QString::number(liodata->getV1(row),16) : QString::number(liodata->getV1(row));
    case SV2COLUMN:
        return (inHex) ? "0x" + QString::number(liodata->getV2(row),16) : QString::number(liodata->getV2(row));
    case CAPTURECOLUMN:
        return "Capture";
    case READCOLUMN:
        return "Read";
    case WRITECOLUMN:
        return "Write";
    default:
        return "unknown";
}
 }
 return QVariant();
}

/*public*/ int LocoIOTableModel::getPreferredWidth(int col) {
switch (col) {
    case PINCOLUMN:
 return  QLabel(" 16 ").sizeHint().width();
    case MODECOLUMN:
 return  QLabel("1234567890123456789012345678901234567890").sizeHint().width();
    case ADDRCOLUMN:
 return  QLabel(getColumnName(ADDRCOLUMN)).sizeHint().width();
    case SV0COLUMN:
    case SV1COLUMN:
    case SV2COLUMN:
 return  QLabel(" 0xFF ").sizeHint().width();
    case CAPTURECOLUMN:
 return  QPushButton(" Capture ").sizeHint().width();
    case READCOLUMN:
 return  QPushButton(" Read ").sizeHint().width();
    case WRITECOLUMN:
 return  QPushButton(" Write ").sizeHint().width();
    default:
 return  QLabel(" <unknown> ").sizeHint().width();
}
}

/*public*/ bool  LocoIOTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  if (index.column() == MODECOLUMN)
  {
   if (liodata->getLocoIOModeList()->isValidModeValue(value))
   {
    liodata->setMode(index.row(), value.toString());
    liodata->setLIM(index.row(),  value.toString());
    LocoIOMode* l = liodata->getLIM(index.row());
    if (l != NULL)
    {
     liodata->setSV(index.row(), l->getSV());
     liodata->setV1(index.row(), l, liodata->getAddr(index.row()));
     liodata->setV2(index.row(), l, liodata->getAddr(index.row()));

     msg.replace( index.row(), "Packet: " + LnConstants::OPC_NAME(l->getOpcode()) + " "
             + QString::number(liodata->getV1(index.row()), 0,16) + " "
             + QString::number(liodata->getV2(index.row()), 0, 16) + " <CHK>");
     if (status != NULL)
     {
      status->setText(msg[index.row()]);
     }
     fireTableRowsUpdated(index.row(), index.row());
    }
   }
  }
  else if (index.column() == ADDRCOLUMN)
  {
   int a;
   if (( value.toString()).startsWith("0x"))
   {
    //a = Integer.valueOf(((String) value).substring(2), 16).intValue();
    a = value.toString().toInt(0,16);
   } else {
       //a = Integer.valueOf((String) value, 10).intValue();
    a = value.toString().toInt(0,10);

   }
   if (a < 1)
   {
    a = 1;
   }
   if (a > 0xFFF)
   {
    a = 0xFFF;
   }
   liodata->setAddr(index.row(), a);
   if (!("<none>"==(liodata->getMode(index.row()))))
   {
    LocoIOMode* l = liodata->getLIM(index.row());
    liodata->setV1(index.row(), l, a);
    liodata->setV2(index.row(), l, a);

    int opcode = (l == NULL) ? 0 : l->getOpcode();
    msg[index.row()] = "Packet: " + LnConstants::OPC_NAME(opcode)
            + " " + QString::number(liodata->getV1(index.row()),0,16)
            + " " + QString::number(liodata->getV2(index.row()),0,16)
            + " <CHK>";

    if (status != NULL)
    {
     status->setText(msg[index.row()]);
    }
   }
   fireTableRowsUpdated(index.row(), index.row());
  }
  else if (index.column() == CAPTURECOLUMN)
  {
    // start a capture operation
    liodata->captureValues(index.row());
  }
  else if (index.column() == READCOLUMN)
  {
   // start a read operation
   liodata->readValues(index.row());

  }
  else if (index.column() == WRITECOLUMN)
  {
   // start a write operation
   liodata->writeValues(index.row());
  }
 }
 return false;
}

// /*public*/ static QStringList getValidOnModes() { return validmodes.getValidModes(); }
/*public*/ void LocoIOTableModel::dispose()
{
 if (log->isDebugEnabled())
 {
    log->debug("dispose");
 }
}
/*public*/ void LocoIOTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
{ // TODO:
 // install a button renderer & editor
//    ButtonRenderer buttonRenderer = new ButtonRenderer();
//    table.setDefaultRenderer(JButton.class,buttonRenderer);
//    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//    table.setDefaultEditor(JButton.class,buttonEditor);
//    // ensure the table rows, columns have enough room for buttons
//    table.setRowHeight(sample.getPreferredSize().height);
//    table.getColumnModel().getColumn(column)
//        .setPreferredWidth((sample.getPreferredSize().width)+4);
 if(buttonMap->value(column) == nullptr)
  buttonMap->insert(column, new QSignalMapper);
 table->setItemDelegateForColumn(column, new LMPBDelegate(buttonMap->value(column)));
 connect(buttonMap->value(column), SIGNAL(mapped(QObject*)), this, SLOT(OnButtonClicked(QObject*)));
}
void LocoIOTableModel::OnButtonClicked(QObject* o)
{
 QModelIndex* index = (QModelIndex*)o;
 emit buttonClicked(index);
 setData(*index, QVariant(), Qt::EditRole);
}

LMPBDelegate::LMPBDelegate(QSignalMapper* mapper, QObject *parent) : QItemDelegate(parent)
{
 this->mapper = mapper;
}

QWidget* LMPBDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & index ) const
{
 QPushButton* editor = new QPushButton(index.data().toString(),parent);
 if(mapper != nullptr)
 {
  QModelIndex* pIndex = new QModelIndex(index);
  mapper->setMapping(editor,(QObject*)pIndex);
  connect(editor, SIGNAL(clicked()), mapper, SLOT(map()));
 }
 return editor;
}
void LMPBDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
 editor->setGeometry(option.rect);
}
/*private*/ /*static*/ Logger* LocoIOTableModel::log =  LoggerFactory::getLogger("LocoIOTableModel");
