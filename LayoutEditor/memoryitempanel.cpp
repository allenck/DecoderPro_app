#include "memoryitempanel.h"
#include <QVBoxLayout>
#include "itempalette.h"
#include "fileutil.h"
#include "namedicon.h"
#include "swingconstants.h"
#include "gridbagconstraints.h"
#include <QGridLayout>
#include <QSpinBox>
#include "spinnernumbermodel.h"
#include "jtextfield.h"
//#include "jspinner.h"
#include "editor.h"
#include "dataflavor.h"
#include "memoryinputicon.h"
#include "memoryspinnericon.h"
#include "memorycomboicon.h"
#include <QTableView>
#include "memoryicon.h"
#include "namedbean.h"
#include "editor.h"
#include "flowlayout.h"
#include <QGroupBox>
#include <QWidget>
#include "picklistmodel.h"
#include "memoryiconxml.h"
#include "memorycomboiconxml.h"
#include "memoryinputiconxml.h"
#include "memoryspinnericonxml.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "imagepanel.h"
#include <QComboBox>

//MemoryItemPanel::MemoryItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
///*public*/ class MemoryItemPanel extends TableItemPanel implements ChangeListener, ListSelectionListener {


/*public*/ MemoryItemPanel::MemoryItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent)
    : TableItemPanel(parentFrame, type, family, model, editor, parent)
{
 //super(parentFrame, type, family, model, editor);
 log = new Logger("MemoryItemPanel");
 setObjectName("MemoryItemPanel");
}

/*public*/ void MemoryItemPanel::init()
{
 if(!_initialized)
 {
  thisLayout->addWidget(initTablePanel(_model, _editor));
  this->initIconFamiliesPanel();
  thisLayout->addWidget(_iconFamilyPanel);
  thisLayout->addWidget(makeBgButtonPanel(_dragIconPanel, _iconPanel));
  connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged()));
  _initialized = true;
  update();
 }
}

/*protected*/ QWidget* MemoryItemPanel::instructions() {
    QWidget* instructions = new QWidget();
    instructions->setObjectName(QString::fromUtf8("instructions"));
    QFont font;
    font.setPointSize(8);
    instructions->setFont(font);
    QVBoxLayout* verticalLayout_instructions = new QVBoxLayout(instructions);
    verticalLayout_instructions->setObjectName(QString::fromUtf8("verticalLayout_instructions"));
    verticalLayout_instructions->addWidget(new QLabel(tr("To Add an Icon to your control panel:")));
    verticalLayout_instructions->addWidget(new QLabel(tr("--drag an icon from the display panel below to your control panel")));
    QHBoxLayout* blurb3Layout = new QHBoxLayout();
    blurb3Layout->setObjectName(QString::fromUtf8("blurb3Layout"));
    QLabel* blurb3Icon = new QLabel(instructions);
    blurb3Icon->setObjectName(QString::fromUtf8("blurb3Icon"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(blurb3Icon->sizePolicy().hasHeightForWidth());
    blurb3Icon->setSizePolicy(sizePolicy1);
    blurb3Icon->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/misc/X-red.gif")));

    blurb3Layout->addWidget(blurb3Icon);

    QLabel* blurb3Text = new QLabel("is displayed for the Display Memory Icon when Memory is null.", instructions);
    blurb3Text->setObjectName(QString::fromUtf8("blurb3Text"));

    blurb3Layout->addWidget(blurb3Text);
    verticalLayout_instructions->addLayout(blurb3Layout);
    verticalLayout_instructions->addWidget(new QLabel(tr("When Memory is an empty string i.e. "" , the Display Memory Icon is blank.")));
    verticalLayout_instructions->addWidget(new QLabel(tr("When blank, enter a value in the other memory icons to view and drag it.")));
    QSpacerItem* horizontalSpacer_instructions = new QSpacerItem(438, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    verticalLayout_instructions->addItem(horizontalSpacer_instructions);
    verticalLayout_instructions->addWidget(new QLabel(tr("The ComboBox Memory Icon sets a memory by selecting an item from the ComboBox.")));
    verticalLayout_instructions->addWidget(new QLabel(tr("Use the \"Edit Memory Icon\" popup to add or delete items. ")));

    return instructions;
}


/*protected*/ void MemoryItemPanel::initIconFamiliesPanel()
{
 _iconFamilyPanel = new QWidget();
 _iconFamilyPanel->setLayout(new QVBoxLayout());
 if (!_update)
 {
  _iconFamilyPanel->layout()->addWidget(instructions());
 }
 makeDragIconPanel(1);
 this->makeDndIconPanel(NULL, "");

 //_iconFamilyPanel->layout()->addWidget(_dragIconPanel);
 log->debug("initIconFamiliesPanel done");
}

/*protected*/ void MemoryItemPanel::makeDndIconPanel(QMap<QString, NamedIcon *> * /*iconMap*/, QString /*displayKey*/)
{
 if (_update)
 {
  return;
 }
 QWidget* panel = new QWidget();
  //panel.setOpaque(false);
 GridBagLayout* panelLayout;
  panel->setLayout(panelLayout = new GridBagLayout());
  GridBagConstraints c = GridBagConstraints();
  c.gridwidth = 1;
  c.gridheight = 1;
  c.gridx = 0;
  c.gridy = 0;
  c.anchor = GridBagConstraints::CENTER;
  c.weightx = 1.0;

  QLabel* label = new QLabel(tr("Input Box Memory")); // "ReadWriteMemory"
  //label.setOpaque(false);
  panelLayout->addWidget(label, c);
  c.gridy = 1;
  _writeMem = new MemoryInputIcon(5, _editor);
  panelLayout->addWidget(makeDragIcon(_writeMem, Type::READWRITE), c);

  _spinner = new QSpinBox(); //new SpinnerNumberModel(0, 0, 100, 1));
  _spinner->setMinimum(0);
  _spinner->setMaximum(100);
  _spinner->setSingleStep(1);
  _spinner->setValue(0);
//  JTextField* field = ((JSpinner.DefaultEditor) _spinner.getEditor()).getTextField();
//  field.setColumns(2);
//  field.setText("5");
  _spinner->setMaximumSize(_spinner->sizeHint());
  //_spinner.addChangeListener(this);
  connect(_spinner, SIGNAL(valueChanged(int)), this, SLOT(stateChanged()));
  c.gridy = 2;
  panelLayout->addWidget(_spinner, c);

  c.gridy = 3;
  c.anchor = GridBagConstraints::NORTH;
  label = new QLabel(tr("Col Width"));
  //label.setOpaque(false);
  panelLayout->addWidget(label, c);

  c.gridx = 1;
  c.gridy = 0;
  c.anchor = GridBagConstraints::CENTER;
  label = new QLabel(tr("Display Memory"));
  //label.setOpaque(false);
  panelLayout->addWidget(label, c);
  c.gridy = 1;
  _readMem = new MemoryIcon(NamedIcon::getIconByName(":/resources/icons/misc/X-red.gif"), _editor);
  panelLayout->addWidget(makeDragIcon(_readMem, Type::READONLY), c);

  c.gridx = 2;
  c.gridy = 0;
  label = new JLabel(tr("Spinner Memory"));
//  label.setOpaque(false);
  panelLayout->addWidget(label, c);
  c.gridy = 1;
  _spinMem = new MemorySpinnerIcon(_editor);
  panelLayout->addWidget(makeDragIcon(_spinMem, Type::SPINNER), c);

  c.gridx = 0;
  c.gridy = 2;
  c.gridwidth = 4;
  label = new JLabel(tr("ComboBox Memory"));
//  label->setOpaque(false);
  panelLayout->addWidget(label, c);
  c.gridy = 3;
  QStringList sample = QStringList();
  _comboMem = new MemoryComboIcon(_editor, sample);
  sample << "selection 1" << "selection 2";
  panelLayout->addWidget(makeDragIcon(_comboMem, Type::COMBO), c);

  _dragIconPanel->layout()->addWidget(panel);
  _dragIconPanel->update();
}

/*private*/ QWidget* MemoryItemPanel::makeDragIcon(QWidget* mem, Type type)
{
 QWidget*  panel = new QWidget(/*new FlowLayout()*/);
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QVBoxLayout);
 //panel->setOpaque(false);
 QWidget* comp = NULL;
    try {
        comp = this->getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR), type, mem);
        comp->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
    }
    catch (ClassNotFoundException cnfe) {
        //cnfe.printStackTrace();
        comp = new QWidget();
    }
 switch (type)
 {
 case READONLY:
  comp->layout()->addWidget(new QLabel("text"));
  break;
 case SPINNER:
  comp->layout()->addWidget(new QSpinBox());
  break;
 case COMBO:
  comp->layout()->addWidget(new QComboBox());
  break;
default:
  comp->layout()->addWidget(mem);
  break;
 }
 panelLayout->addWidget(comp);
//    panel.validate();
 return panel;
}

/*
* Set column width for InputMemoryIcon
*/
/*public*/ void MemoryItemPanel::stateChanged(/*ChangeEvent* e*/) {
//    if (log->isDebugEnabled()) log->debug("stateChanged: class= "+_spinner.value().getClass().getName()+
//                                        ", value= "+_spinner.getValue());

    int nCols = _spinner->value();
    _writeMem->setNumColumns(nCols);
//        _writeMem.validate();
//    _writePanel.validate();
}

/**
*  ListSelectionListener action from table
*/
/*public*/ void MemoryItemPanel::valueChanged(/*ListSelectionEvent e*/)
{
 if (_table == NULL)
 {
  return;
 }
 int row = _table->currentIndex().row();
 if (log->isDebugEnabled()) log->debug("Table valueChanged: row= "+row);
 if (row >= 0)
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(true);
   _updateButton->setToolTip("");
  }
  NamedBean* bean = getDeviceNamedBean();
  _readMem->setMemory(bean->getDisplayName());
  _writeMem->setMemory(bean->getDisplayName());
  _spinMem->setMemory(bean->getDisplayName());
  _spinner->setValue(_writeMem->getNumColumns());
 }
 else
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(false);
   _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
  }
 }
 //validate();
}


/*protected*/ MemoryIconDragJComponent* MemoryItemPanel::getDragger(DataFlavor* flavor, MemoryItemPanel::Type type, QWidget* comp )
{
 return new MemoryIconDragJComponent(flavor, type, comp,this);
}

///*protected*/ class IconDragJComponent :public  DragJComponent {
//    Type _memType;

/*public*/ MemoryIconDragJComponent::MemoryIconDragJComponent(DataFlavor* flavor, MemoryItemPanel::Type type, QWidget* comp, QWidget* parent)
    : DragJComponent(flavor, comp, parent)
{
 //super(flavor, dim);
 _memType = type;
 setObjectName("MemoryIconDragJComponent");
 self = (MemoryItemPanel*)parent;
}
/*public*/ QObject* MemoryIconDragJComponent::getTransferData(DataFlavor* /*flavor*/) throw (UnsupportedFlavorException,IOException )
{
//        if (!isDataFlavorSupported(flavor)) {
//            return NULL;
//        }
 NamedBean* bean = self->getDeviceNamedBean();
 if (bean==NULL)
 {
  self->log->error("IconDragJComponent.getTransferData: NamedBean is NULL!");
  return NULL;
 }

 switch (_memType)
 {
  case MemoryItemPanel::READONLY:
  {
        MemoryIcon* m = new MemoryIcon("", self->_editor);
        m->setMemory(bean->getDisplayName());
        m->setSize(m->size().width(), m->size().height());
        m->setLevel(Editor::MEMORIES);
        return m;
  }
  case MemoryItemPanel::READWRITE:
  {
        int numCols = 5;
        try {
//                    ((JSpinner.DefaultEditor)_spinner.getEditor()).commitEdit();
//                    SpinnerNumberModel spinModel = (SpinnerNumberModel)_spinner.getModel();
//                    if (log->isDebugEnabled()) log->debug("MemoryDnD.createTransferable: spinCols= "
//                                                        +spinModel.getNumber().intValue());
           numCols = self->_spinner->value();
        } catch (ParseException pe) {
            self->log->error("MemoryDnD.createTransferable: "+pe.getMessage());
        }
        MemoryInputIcon* mi = new MemoryInputIcon(numCols, self->_editor);
        mi->setMemory(bean->getDisplayName());
        mi->setSize(mi->size().width(), mi->size().height());
        mi->setLevel(Editor::MEMORIES);
        return mi;
  }
  case MemoryItemPanel::SPINNER:
  {
        MemorySpinnerIcon* ms = new MemorySpinnerIcon(self->_editor);
        ms->setMemory(bean->getDisplayName());
        ms->setSize(ms->size().width(), ms->size().height());
        ms->setLevel(Editor::MEMORIES);
        return ms;
  }
  case MemoryItemPanel::COMBO:
  {
   MemoryComboIcon* mc = new MemoryComboIcon(self->_editor, QStringList());
   mc->setMemory(bean->getDisplayName());
   mc->setSize(mc->size().width(), mc->size().height());
   mc->setLevel(Editor::MEMORIES);
   return mc;
  }
 }
 return NULL;
}
QByteArray MemoryIconDragJComponent::mimeData()
{
 NamedBean* bean = self->getTableSelection();
 QByteArray xmldata;
 if(bean != NULL)
 {
  switch(_memType)
  {
   case MemoryItemPanel::READONLY:
   {
      MemoryIcon* m = new MemoryIcon("??", self->_editor);
      m->setMemory(bean->getDisplayName());
      m->setSize(m->size().width(), m->size().height());
      m->setLevel(Editor::MEMORIES);
      _dataFlavor = new DataFlavor(m,"MemoryIcon");
      MemoryIconXml* xml = new MemoryIconXml();
      QDomElement e = xml->store((QObject*)m);
      xml->doc.appendChild(e);
      xmldata.append(xml->doc.toString());
      break;
   }
   case MemoryItemPanel::READWRITE:
   {
    int numCols = 5;
      try {
//                    ((JSpinner.DefaultEditor)_spinner.getEditor()).commitEdit();
//                    SpinnerNumberModel spinModel = (SpinnerNumberModel)_spinner.getModel();
//                    if (log->isDebugEnabled()) log->debug("MemoryDnD.createTransferable: spinCols= "
//                                                        +spinModel.getNumber().intValue());
         numCols = self->_spinner->value();
      } catch (ParseException pe) {
          self->log->error("MemoryDnD.createTransferable: "+pe.getMessage());
      }
      MemoryInputIcon* mi = new MemoryInputIcon(numCols, self->_editor);
      mi->setMemory(bean->getDisplayName());
      mi->setSize(mi->size().width(), mi->size().height());
      mi->setLevel(Editor::MEMORIES);
      _dataFlavor = new DataFlavor(mi,"MemoryInputIcon");
      MemoryInputIconXml* xml = new MemoryInputIconXml();
      QDomElement e = xml->store((QObject*)mi);
      xml->doc.appendChild(e);
      xmldata.append(xml->doc.toString());
      break;
   }
   case MemoryItemPanel::COMBO:
   {
    MemoryComboIcon* mc = new MemoryComboIcon(self->_editor, QStringList());
    mc->setMemory(bean->getDisplayName());
    mc->setSize(mc->size().width(), mc->size().height());
    mc->setLevel(Editor::MEMORIES);
    _dataFlavor = new DataFlavor(mc,"MemoryComboIcon");
    MemoryComboIconXml* xml = new MemoryComboIconXml();
    QDomElement e = xml->store((QObject*)mc);
    xml->doc.appendChild(e);
    xmldata.append(xml->doc.toString());
    break;
   }
   case MemoryItemPanel::SPINNER:
   {
      MemorySpinnerIcon* ms = new MemorySpinnerIcon(self->_editor);
      ms->setMemory(bean->getDisplayName());
      ms->setSize(ms->size().width(), ms->size().height());
      ms->setLevel(Editor::MEMORIES);
      _dataFlavor = new DataFlavor(ms,"MemorySpinnerIcon");
      MemoryIconXml* xml = new MemoryIconXml();
      QDomElement e = xml->store((QObject*)ms);
      xml->doc.appendChild(e);
      xmldata.append(xml->doc.toString());
      break;
   }
  }
//  _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));
//  return _dataFlavor->toString();
  return xmldata;
 }
 else
     return "";
}

//}
