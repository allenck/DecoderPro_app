#include "slipiconadder.h"
#include <QRadioButton>
#include <QBoxLayout>
#include <QButtonGroup>
#include "flowlayout.h"
#include <QRadioButton>
#include <QSignalMapper>
#include "exceptions.h"
#include "jlabel.h"
#include <QTableView>
#include "turnout.h"
#include "instancemanager.h"
#include "dataflavor.h"
#include "iconadder.h"
#include "slipturnouticon.h"
#include <QMessageBox>
#include "itempalette.h"

SlipIconAdder::SlipIconAdder(QWidget *parent) :
    IconAdder(parent)
{
 common();
}
SlipIconAdder::~SlipIconAdder()
{
 delete log;
 delete _turnoutMap;
// delete doubleSlipButton;
// delete singleSlipButton;
// delete threeWayButton;
// delete scissorButton;
// delete singleDirection;
// delete lowerWestToLowerEastButton;
// delete upperWestToUpperEastButton;
// if(_addButton != NULL)
//  delete _addButton;
}

/**
 * Provides a simple editor for creating a Single or Double Slip Icon object.
 * Allows drops from icons dragged from a Catalog preview pane.  Also
 * implements dragging a row from the turnout table to be dropped on a turnout
 * label
 * <p>
 * To work right, the SlipTurnoutIcon needs to have all
 * images the same size.
 * Based upon MultiSensorIconAdder by Bob Jacobsen & Pete Cressman
 * @author  Bob Jacobsen  Copyright (c) 2007
 * @author  Kevin Dickerson  Copyright (c) 2010
 *
 */

// /*public*/ class SlipIconAdder extends IconAdder {


/*public*/ /*static*/ /*final*/ QString SlipIconAdder::NamedBeanFlavorMime = DataFlavor::javaJVMLocalObjectMimeType +
           ";class=jmri.NamedBean";

///*public*/ SlipIconAdder() {
//    super();
//}

/*public*/ SlipIconAdder::SlipIconAdder(QString type, QWidget *parent) : IconAdder(type, parent)
{
 //super(type);
 common();
}
/*private*/ void SlipIconAdder::common()
{
 log = new Logger("Slipiconadder");
 log->setDebugEnabled(true);
 resize(431, 477);
 _turnoutMap = new QMap <QString, NamedBeanHandle<Turnout*>*>();
 _lastIndex = 0;
 doubleSlip = 0x00;
 doubleSlipButton = new QRadioButton(tr("Double Slip"));
 singleSlipButton = new QRadioButton(tr("Single Slip"));
 threeWayButton = new QRadioButton(tr("Three Way Turnout"));
 scissorButton = new QRadioButton(tr("Scissor Crossing"));
 _addButton = NULL;

 singleDirection = new QRadioButton(tr("SingleSlipRoute"));
 lowerWestToLowerEastButton = new QRadioButton(tr("Lower West To Lower East"));
 upperWestToUpperEastButton = new QRadioButton(tr("Upper West To Upper East"));
 //connect(_table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(slot_SelectionChanged(const QItemSelection &, const QItemSelection &)));
}

/*public*/ void SlipIconAdder::setTurnoutType(int dblSlip)
{
 doubleSlip = dblSlip;
 doubleSlipButton->setChecked(false);
 singleSlipButton->setChecked(false);
 threeWayButton->setChecked(false);
 scissorButton->setChecked(false);
 switch(dblSlip)
 {
 case 0x00:
    doubleSlipButton->setChecked(true);
    break;
 case 0x02:
    singleSlipButton->setChecked(true);
    break;
 case 0x04:
    threeWayButton->setChecked(true);
    break;
 case 0x08:
    scissorButton->setChecked(true);
    break;
 }
}

/*public*/ int SlipIconAdder::getTurnoutType() { return doubleSlip; }

/*public*/ void SlipIconAdder::reset()
{
 _turnoutMap = new QMap <QString, NamedBeanHandle<Turnout*>*>();
 _lastIndex = 0;
 IconAdder::reset();
}




/**
*  Override.  First look for a table selection to set the sensor.
*   If not, then look to change the icon image (super).
*/
//@SuppressWarnings("NULL")
/*public*/ void SlipIconAdder::makeIconPanel(bool /*useDefaults*/)
{
 if (_iconPanel != NULL)
 {
  thisLayout->removeWidget(_iconPanel);
  _iconPanel->deleteLater();
 }
 //super.makeIconPanel();
 QSize dim;
 _iconPanel = new QWidget();
 _iconPanel->setObjectName("iconPanel");
 _iconPanel->setContentsMargins(0,0,0,0);
 _iconPanel->setMinimumHeight(30);
 QVBoxLayout* iconPanelLayout;
 _iconPanel->setLayout(iconPanelLayout = new QVBoxLayout);//(_iconPanel/*, BoxLayout.Y_AXIS*/));
 iconPanelLayout->setSpacing(0);
 iconPanelLayout->setContentsMargins(0,0,0,0);
 QButtonGroup* typeGroup = new QButtonGroup();
 typeGroup->addButton(doubleSlipButton);
 typeGroup->addButton(singleSlipButton);
 typeGroup->addButton(threeWayButton);
 typeGroup->addButton(scissorButton);
 QSignalMapper* mapper = new QSignalMapper;
 mapper->setMapping(doubleSlipButton, 0x00);
 mapper->setMapping(singleSlipButton, 0x02);
 mapper->setMapping(threeWayButton,0x04);
 mapper->setMapping(scissorButton, 0x08);
 QWidget* _typePanel = new QWidget();
 _typePanel->setContentsMargins(0,0,0,0);
 _typePanel->setLayout(new FlowLayout(0,0,0));
 _typePanel->layout()->setSpacing(0);
 _typePanel->layout()->addWidget(doubleSlipButton);
 _typePanel->layout()->addWidget(singleSlipButton);
 _typePanel->layout()->addWidget(threeWayButton);
 _typePanel->layout()->addWidget(scissorButton);

 _iconPanel->layout()->addWidget(_typePanel);
//    doubleSlipButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                slipUpdate(0x00);
//            }
//        });
    connect(doubleSlipButton, SIGNAL(clicked()), mapper, SLOT(map()));
//    singleSlipButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                slipUpdate(0x02);
//            }
//        });
    connect(singleSlipButton, SIGNAL(clicked()), mapper, SLOT(map()));
//    threeWayButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                slipUpdate(0x04);
//            }
//        });
    connect(threeWayButton, SIGNAL(clicked()), mapper, SLOT(map()));
//    scissorButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                slipUpdate(0x08);
//            }
//        });
    connect(scissorButton, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(slipUpdate(int)));
// TODO:    if(lowerWestToLowerEastButton->getActionListeners().length() >0)
//        lowerWestToLowerEastButton->removeActionListener(lowerWestToLowerEastButton->getActionListeners()[0]);
//    if(upperWestToUpperEastButton->getActionListeners().length() >0)
//        upperWestToUpperEastButton->removeActionListener(upperWestToUpperEastButton.getActionListeners()[0]);
    if (getTurnoutType()==0x02)
    {
     QButtonGroup* group = new QButtonGroup();
     group->addButton(lowerWestToLowerEastButton);
     group->addButton(upperWestToUpperEastButton);
     lowerWestToLowerEastButton->setText(tr("Lower West To Lower East"));
     upperWestToUpperEastButton->setText(tr("Upper West To Upper East"));
     QWidget* _buttonSlipPanel = new QWidget();
     _buttonSlipPanel->setContentsMargins(0,0,0,0);
     _buttonSlipPanel->setLayout(new FlowLayout(0,0,0));
     _buttonSlipPanel->layout()->addWidget(lowerWestToLowerEastButton);
     _buttonSlipPanel->layout()->addWidget(upperWestToUpperEastButton);
     _iconPanel->layout()->addWidget(_buttonSlipPanel);
     QSignalMapper* lowerWestMapper = new QSignalMapper;
     lowerWestMapper->setMapping(lowerWestToLowerEastButton,0);
//     lowerWestToLowerEastButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                updateSingleSlipRoute(false);
//            }
//        });
     connect(lowerWestToLowerEastButton, SIGNAL(clicked()), lowerWestMapper, SLOT(map()));
//        upperWestToUpperEastButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                updateSingleSlipRoute(true);
//            }
//        });
     lowerWestMapper->setMapping(upperWestToUpperEastButton, 1);
     connect(upperWestToUpperEastButton, SIGNAL(clicked()), lowerWestMapper, SLOT(map()));
     connect(lowerWestMapper, SIGNAL(mapped(int)), this, SLOT(updateSingleSlipRoute(int)));
    }
    else if (getTurnoutType()==0x04)
    {
     QButtonGroup* group = new QButtonGroup();
     lowerWestToLowerEastButton->setText(tr("First Turnout Lower Exit"));
     upperWestToUpperEastButton->setText(tr("First Turnout Upper Exit"));
     group->addButton(lowerWestToLowerEastButton);
     group->addButton(upperWestToUpperEastButton);
     QWidget* _buttonSlipPanel = new QWidget();
     _buttonSlipPanel->setContentsMargins(0,0,0,0);
     _buttonSlipPanel->setLayout(new FlowLayout(0,0,0));
     _buttonSlipPanel->layout()->addWidget(lowerWestToLowerEastButton);
     _buttonSlipPanel->layout()->addWidget(upperWestToUpperEastButton);
     _iconPanel->layout()->addWidget(_buttonSlipPanel);
    }
    else if (getTurnoutType()==0x08)
    {
     QButtonGroup* group = new QButtonGroup();
     lowerWestToLowerEastButton->setText("4 Turnouts");
     upperWestToUpperEastButton->setText("2 Turnouts");
     group->addButton(lowerWestToLowerEastButton);
     group->addButton(upperWestToUpperEastButton);
     QWidget* _buttonSlipPanel = new QWidget();
     _buttonSlipPanel->setLayout(new FlowLayout(0,0,0));
     _buttonSlipPanel->layout()->addWidget(lowerWestToLowerEastButton);
     _buttonSlipPanel->layout()->addWidget(upperWestToUpperEastButton);
     _iconPanel->layout()->addWidget(_buttonSlipPanel);
//        lowerWestToLowerEastButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                changeNumScissorTurnouts();
//            }
//        });
     connect(lowerWestToLowerEastButton, SIGNAL(clicked()), this, SLOT(changeNumScissorTurnouts()));
//        upperWestToUpperEastButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent actionEvent) {
//                changeNumScissorTurnouts();
//            }
//        });
     connect(upperWestToUpperEastButton, SIGNAL(clicked()), this, SLOT(changeNumScissorTurnouts()));
    }

    QWidget* rowPanel = NULL;
    int cnt=0;
    int numTurnoutPanels = 2;
    if ((doubleSlip == 0x08) && (lowerWestToLowerEastButton->isChecked()))
     numTurnoutPanels = 4;
    for (int i=0; i<numTurnoutPanels; i++)
    {
     if (rowPanel == NULL)
     {
      rowPanel = new QWidget();
      QHBoxLayout* rowPanelLayout;
      //rowPanel->setMinimumHeight(100);
      rowPanel->setContentsMargins(0,0,0,0);
      rowPanel->setLayout(rowPanelLayout = new QHBoxLayout);//(rowPanel/*, BoxLayout.X_AXIS*/));
      //((QBoxLayout*)rowPanel->layout())->addStrut(STRUT_SIZE);
      rowPanel->layout()->setSpacing(0);
      rowPanelLayout->setContentsMargins(0,0,0,0);
     }

     QFrame* p3 = new DropPanel(this);
     QVBoxLayout* p3Layout;
     p3->setContentsMargins(0,0,0,0);
     p3->setFrameShape(QFrame::StyledPanel);
     p3->setFrameShadow(QFrame::Raised);
     p3->setObjectName("p3");
     //p3->setMinimumHeight(30);
     p3->setLayout(p3Layout = new QVBoxLayout); //(p3/*, BoxLayout.Y_AXIS*/));
     p3Layout->setSpacing(0);
     p3Layout->setContentsMargins(0,0,0,0);
     QSizePolicy p3Sp(QSizePolicy::Preferred,QSizePolicy::Fixed);
     p3Sp.setHorizontalStretch(0);
     p3Sp.setVerticalStretch(0);
     p3Sp.setHeightForWidth(p3->sizePolicy().hasHeightForWidth());
     p3->setSizePolicy(p3Sp);
//     QFrame* p4 = new QFrame();
//     p4->setFrameShape(QFrame::StyledPanel);
//     p4->setFrameShadow(QFrame::Raised);

     //p4->setLayout(new FlowLayout);
//     p4->setObjectName("p4");

     QString label;
     QString key;
     NamedBeanHandle<Turnout*>* turnout;
     if (i==0)
     {
      if (doubleSlip==0x04)
      {
       label = tr("First Turnout");
      }
      else if (doubleSlip==0x08)
      {
       if (lowerWestToLowerEastButton->isChecked())
        label = tr("Upper West Turnout");
       else
        label = tr("RH Crossing");
      }
      else
      {
       label = tr("West Turnout");
      }
      key = "west";
     }
     else if (i==1)
     {
      key = "east";
      if (doubleSlip==0x04)
      {
       label = tr("Second Turnout");
      }
      else if (doubleSlip==0x08)
      {
       if (lowerWestToLowerEastButton->isChecked())
        label = tr("Upper East Turnout");
       else
        label = tr("LH Crossing");
      }
      else
      {
       label = tr("East Turnout");
      }
     }
     else if (i==2)
     {
      key = "lowerwest";
      label = tr("Lower West Turnout");
     }
     else
     {
      key = "lowereast";
      label = tr("Lower East Turnout");
     }

     turnout = _turnoutMap->value(key);
     QLabel* k = new QLabel(key);
     k->setObjectName(key);
//     k->setName(key);
     k->setVisible(false);
     ((DropPanel*)p3)->setKey(key);
     p3->layout()->addWidget(k);
     //p4->layout()->addWidget(new JLabel(label));
     p3Layout->addWidget(new QLabel(label), 0, Qt::AlignHCenter);
     //p3->layout()->addWidget(p4);
//     p4 = new QFrame();
//     p4->setLayout(new FlowLayout);
//     p4->setFrameShape(QFrame::StyledPanel);
//     p4->setFrameShadow(QFrame::Raised);

     QString name = tr("undefined");
     QLabel* toName = new QLabel();
     QColor color = QColor(Qt::red);
     toName->setStyleSheet("QLabel { border: 1px solid red; }");

     if (turnout != NULL)
     {
      name = turnout->getName();
      color = QColor(Qt::black);
      toName->setStyleSheet("QLabel { border: 1px solid black; }");
     }
     //p4.setBorder(BorderFactory.createLineBorder(color));

     toName->setText(name);
     //p4->layout()->addWidget(toName);
     p3Layout->addWidget(toName, 0, Qt::AlignHCenter);
     //p4->setMaximumSize(p4->minimumSize());
     //p3->layout()->addWidget(p4);

//     QWidget* p13 =new QWidget();
//     QHBoxLayout* p13Layout;
//     p13->setLayout(p13Layout = new QHBoxLayout(p13/*, BoxLayout.X_AXIS*/));
//     p13->layout()->addWidget(p3);

     QWidget* panel =new QWidget();
     //panel->setMinimumHeight(100);
     QVBoxLayout* panelLayout;
     panel->setLayout(panelLayout = new QVBoxLayout); //(panel/*, BoxLayout.Y_AXIS*/));
     panel->setContentsMargins(0,0,0,0);
     panelLayout->setSpacing(0);
     panelLayout->setContentsMargins(0,0,0,0);
//     panel->layout()->addWidget(p13);
     panelLayout->addWidget(p3);
     //panel.setBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK));

     rowPanel->layout()->addWidget(panel);
     //((QBoxLayout*)rowPanel->layout())->addStrut((STRUT_SIZE));

     cnt++;
     if ((cnt%2)==0)
     {
      _iconPanel->layout()->addWidget(rowPanel);
      rowPanel = NULL;
     }
     dim = panel->sizeHint();
    }
    while ((cnt%2)!=0)
    {
     try {
//      rowPanel->layout()->addWidget(Box.createRigidArea(dim));
      cnt++;
     } catch (NullPointerException npe) { /* never */}
    }
    if (rowPanel != NULL)
    {
     _iconPanel->layout()->addWidget(rowPanel);
//     ((QBoxLayout*)_iconPanel->layout())->addStrut((STRUT_SIZE));
    }
    rowPanel = new QWidget();
    QHBoxLayout* rowPanelLayout;
    rowPanel->setLayout(rowPanelLayout = new QHBoxLayout); //(rowPanel/*, BoxLayout.X_AXIS*/));
//    ((QBoxLayout*)rowPanel->layout())->addStrut((STRUT_SIZE));
    rowPanelLayout->setSpacing(0);
    rowPanel->setContentsMargins(0,0,0,0);
    rowPanel->setMinimumHeight(100);
    rowPanelLayout->setContentsMargins(0,0,0,0);
    QWidget* panel = NULL;
    cnt=0;
    for (int i=_order.size()-1; i>=0; i--)
    {
     if (panel == NULL)
     {
      panel = new QWidget();
      QHBoxLayout* panelLayout;
      panel->setLayout(panelLayout = new QHBoxLayout);//(panel/*, BoxLayout.X_AXIS*/));
      //((QBoxLayout*)rowPanel->layout())->addStrut((STRUT_SIZE));
      panel->setContentsMargins(0,0,0,0);
      panelLayout->setSpacing(0);
      panelLayout->setContentsMargins(0,0,0,0);
     }
     QString key = _order.value(i);
     QWidget* p = new QWidget();
     QVBoxLayout* pLayout;
     p->setLayout(pLayout = new QVBoxLayout(/*p, BoxLayout.Y_AXIS*/));
     p->setContentsMargins(0,0,0,0);
     p->setMinimumHeight(100);
     pLayout->setSpacing(0);
     pLayout->setContentsMargins(0,0,0,0);
     pLayout->addWidget(new QLabel(/*rbean.getString(key)*/ItemPalette::convertText( key)));
     pLayout->addWidget(_iconMap->value(key),0,Qt::AlignHCenter);
     QSizePolicy pSp =  QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     pSp.setHorizontalStretch(0);
     pSp.setVerticalStretch(0);
     pSp.setHeightForWidth(p->sizePolicy().hasHeightForWidth());
     p->setSizePolicy(pSp);
     panel->layout()->addWidget(p);
//     ((QBoxLayout*)panel->layout())->addStrut((STRUT_SIZE));
     if ((cnt&1)!=0)
     {
      _iconPanel->layout()->addWidget(panel);
//      ((QBoxLayout*)_iconPanel->layout())->addStrut((STRUT_SIZE));
      panel = NULL;
  }
  cnt++;
 }
 if (panel != NULL)
 {
  _iconPanel->layout()->addWidget(panel);
//  ((QBoxLayout*)_iconPanel->layout())->addStrut((STRUT_SIZE));
 }
 thisLayout->addWidget(_iconPanel,0,Qt::AlignTop);
 valueChanged(NULL);

 pack();
}

void SlipIconAdder::changeNumScissorTurnouts()
{
 if(upperWestToUpperEastButton->isChecked())
 {
  _turnoutMap->remove("lowerwest");
  _turnoutMap->remove("lowereast");
 }
 makeIconPanel(true);
}

void SlipIconAdder::slipUpdate(int slip)
{
 //If what we are setting to is the same as already set do nothing.
 if (slip==doubleSlip)
  return;
 if ((doubleSlip==0x04)||(doubleSlip==0x08))
 {
  _delete(4);
  _delete(3);
  _delete(2);
  _turnoutMap->remove("lowerwest");
  _turnoutMap->remove("lowereast");
  //We need to reset the icons back for a slip
  setIcon(3, "LowerWestToUpperEast",
            "resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif");
  setIcon(2, "UpperWestToLowerEast",
            "resources/icons/smallschematics/tracksegments/os-slip-upper-west-lower-east.gif");
  setIcon(4, "LowerWestToLowerEast",
            "resources/icons/smallschematics/tracksegments/os-slip-lower-west-lower-east.gif");
  setIcon(0, "BeanStateInconsistent",
            "resources/icons/smallschematics/tracksegments/os-slip-error-full.gif");
  setIcon(1, "BeanStateUnknown",
            "resources/icons/smallschematics/tracksegments/os-slip-unknown-full.gif");
 }

 if (slip==0x04)
 {
  //We need to setup the base icons for a three way.
  _delete(5);
  _delete(4);
  _delete(3);
  _delete(2);
  setIcon(3, "Upper",
        "resources/icons/smallschematics/tracksegments/os-3way-upper.gif");
  setIcon(2, "Middle",
        "resources/icons/smallschematics/tracksegments/os-3way-middle.gif");
  setIcon(4, "Lower",
        "resources/icons/smallschematics/tracksegments/os-3way-lower.gif");
  setIcon(0, "BeanStateInconsistent",
        "resources/icons/smallschematics/tracksegments/os-3way-error.gif");
  setIcon(1, "BeanStateUnknown",
        "resources/icons/smallschematics/tracksegments/os-3way-unknown.gif");
  upperWestToUpperEastButton->setChecked(true);
 }
 else if (slip == 0x08)
 {
  //We need to setup the base icons for a Scissor.
  _delete(5);
  setIcon(3, "LowerWestToUpperEast",
    "resources/icons/smallschematics/tracksegments/os-double-crossover-lower-west-upper-east.gif");
  setIcon(2, "UpperWestToLowerEast",
    "resources/icons/smallschematics/tracksegments/os-double-crossover-upper-west-lower-east.gif");
  setIcon(4, "LowerWestToLowerEast",
    "resources/icons/smallschematics/tracksegments/os-double-crossover-closed.gif");

  setIcon(0, "BeanStateInconsistent",
    "resources/icons/smallschematics/tracksegments/os-double-crossover-error.gif");
  setIcon(1, "BeanStateUnknown",
    "resources/icons/smallschematics/tracksegments/os-double-crossover-unknown.gif");

  upperWestToUpperEastButton->setChecked(true);
 }

 switch(slip)
 {
  case 0x00:
   _delete(4);
   setIcon(4, "LowerWestToLowerEast",
        "resources/icons/smallschematics/tracksegments/os-slip-lower-west-lower-east.gif");
   setIcon(5, "UpperWestToUpperEast",
        "resources/icons/smallschematics/tracksegments/os-slip-upper-west-upper-east.gif");
   break;
  case 0x02:
   _delete(5);
   updateSingleSlipRoute(false);
   break;
  }
  doubleSlip=slip;
  makeIconPanel(true);
}

/**
* Override
*
*/
/*public*/ void SlipIconAdder::complete(ActionListener* addIconAction, bool changeIconAction, bool addToTable, bool update)
{
 IconAdder::complete(addIconAction, changeIconAction, addToTable, update);
 _table->setDragEnabled(true);
//    _table->setTransferHandler(new ExportHandler());
 valueChanged(NULL);
}

class TransferableNamedBean : public Transferable
{
 DataFlavor* dataFlavor;
 Logger* log;
 IconAdder* parent;
public:
 TransferableNamedBean(IconAdder* parent)
 {
     this->parent = parent;
  log = new Logger("TransferableNamedBean");
  try {
   dataFlavor = new DataFlavor(SlipIconAdder::NamedBeanFlavorMime);
  }
  catch (ClassNotFoundException cnfe)
  {
   //         cnfe.printStackTrace();
  }
 }
 /*public*/ QVector<DataFlavor*>* getTransferDataFlavors() {
        //if (log.isDebugEnabled()) log.debug("TransferableNamedBean.getTransferDataFlavors ");
     QVector<DataFlavor*>* vector =  new QVector<DataFlavor*>();
     vector->append(dataFlavor );
     return vector;
    }
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor) {
        //if (log.isDebugEnabled()) log.debug("TransferableNamedBean.isDataFlavorSupported ");
        return dataFlavor==(flavor);
    }
    /*public*/ NamedBean* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
        if (log->isDebugEnabled()) log->debug("TransferableNamedBean.getTransferData ");
        if (isDataFlavorSupported(flavor)) {
            return parent->getTableSelection();
        }
        return NULL;
    }
};

/**
*  Override.  Activate Add to Panel button when all icons are
*  assigned sensors.
*/
/*public*/ void SlipIconAdder::valueChanged(ListSelectionEvent* /*e*/)
{
 if (_addButton == NULL)
 {
  return;
 }
 int numTurnouts = 2;
 if ((doubleSlip == SlipTurnoutIcon::SCISSOR) && (lowerWestToLowerEastButton->isChecked()))
  numTurnouts = 4;
 if (_turnoutMap->size() == numTurnouts)
 {
  _addButton->setEnabled(true);
  _addButton->setToolTip("");
  //checkIconSizes();
 }
 else
 {
  _addButton->setEnabled(false);
  _addButton->setToolTip(tr("AssignTurnouts"));
 }
}

/**
*
*/
void SlipIconAdder::_delete(int index)
{
 if (index >= _order.size())
  return;
 QString key = _order.at(index);
 if (log->isDebugEnabled()) log->debug("delete("+QString::number(index)+") Sizes: _iconMap= "+QString::number(_iconMap->size())
              +", _order= "+QString::number(_order.size()));
 _iconMap->remove(key);
 _order.removeAt(index);
}

/**
 * Returns a new NamedIcon object for your own use.
 * see NamedIcon getIcon(String key) in super
 * @param index of key
 * @return Unique object
 */
/*public*/ NamedIcon* SlipIconAdder::getIcon(int index)
{
 return (NamedIcon*)_iconMap->value(_order.value(index))->getIcon();
}
/*public*/ NamedIcon*  SlipIconAdder::getIcon(QString key)
{
 return IconAdder::getIcon(key);
}

/**
 * Returns a Turnout object for your own use.
 * see NamedIcon getIcon(String key) in super
 * @param index of key
 * @return Unique object
 */
/*public*/ NamedBeanHandle<Turnout*>* SlipIconAdder::getTurnout(QString index) {
    return _turnoutMap->value(index);
}

/*public*/ void SlipIconAdder::setTurnout(QString key, NamedBeanHandle<Turnout*>* turnout){
    _turnoutMap->insert(key, turnout);
}

void SlipIconAdder::updateSingleSlipRoute(bool single)
{
 _delete(4);
 if (single)
 {
  upperWestToUpperEastButton->setChecked(true);
  setIcon(4, "Slip",
            "resources/icons/smallschematics/tracksegments/os-slip-upper-west-upper-east.gif");
 }
 else
 {
  lowerWestToLowerEastButton->setChecked(true);
  setIcon(4, "Slip",
            "resources/icons/smallschematics/tracksegments/os-slip-lower-west-lower-east.gif");
 }
 makeIconPanel(true);
}

/*public*/ void SlipIconAdder::setSingleSlipRoute(bool single)
{
 if (single)
 {
  upperWestToUpperEastButton->setChecked(true);
 }
 else
 {
  lowerWestToLowerEastButton->setChecked(true);
 }
}

/*public*/ bool SlipIconAdder::getSingleSlipRoute(){
    if (upperWestToUpperEastButton->isChecked())
        return true;
    else
        return false;
}

/*private*/ bool SlipIconAdder::putTurnout(QString key, Turnout* turnout) {
    QString name = turnout->getUserName();
    if (name == NULL) {
        name = turnout->getSystemName();
    }
    QListIterator<NamedBeanHandle<Turnout*>*> iter( _turnoutMap->values());
    while (iter.hasNext())
    {
     if (name==(iter.next()->getName()))
     {
//      JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                                           tr("DupTurnoutName"),
//                                           new Object[] {name}),
//                                           tr("errorTitle"),
//                                           JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Error"), tr("Dup Turnout Name %1").arg(name));
         return false;
        }
    }
    _turnoutMap->insert(key,((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, turnout));
    return true;
}

