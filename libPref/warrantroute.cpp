#include "warrantroute.h"
#include <QLabel>
#include <QBoxLayout>
#include "jtextfield.h"
#include "blockorder.h"
#include <QIntValidator>
#include "rosterentry.h"
#include <QComboBox>
#include "blockorder.h"
#include "oblock.h"
#include "oblockmanager.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "opath.h"
#include "portal.h"
#include "dcclocoaddress.h"
#include "rosterentry.h"
#include "roster.h"
#include "flowlayout.h"
#include "jdialog.h"
#include "warrant.h"
#include "routefinder.h"
#include <QRadioButton>
#include <QScrollArea>
#include "jtable.h"
#include "defaulttreemodel.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "jtree.h"
#include <QGroupBox>
#include "defaulttablecolumnmodel.h"
#include "box.h"
#include "joptionpane.h"
#include "picklistmodel.h"

//WarrantRoute::WarrantRoute(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}

/**
 * Input window for defining a train's route from an eNtry OBlock to an eXit OBlock.
 * Routes are defined by choosing the originating block, the path on which the train
 * start and the exit Portal through which it will leave the block.  Also it is required
 * that a Destination block is chosen and the path and Portal through which the train will
 * arrive. The Portal selections establish the direction information.  Optionally,
 * additional blocks can be specified requiring the train to pass through or avoid entering.
 *
 * @author Peter Cressman
 *
 */

///*public*/ abstract class WarrantRoute extends jmri.util.JmriJFrame implements ActionListener, PropertyChangeListener {

 ///*private*/ static final long serialVersionUID = 6066050907933847146L;


 /*static*/ int WarrantRoute::STRUT_SIZE = 10;
 /*static*/ QString WarrantRoute::PAD = "               ";

 WarrantRoute::WarrantRoute(QWidget *parent) :
   JmriJFrame(parent)
 {
  //super(false, true);
  _origin = new RouteLocation(ORIGIN, this);
  _destination = new RouteLocation(DEST, this);
  _via =  new RouteLocation(VIA, this);
  _avoid =  new RouteLocation(AVOID, this);
  _routeModel = new RouteTableModel(this);
  _orders = new  QList <BlockOrder*>();
  _searchDepth =  new JTextField(5);
  _searchDepth->setValidator(new QIntValidator());
  _trainId = "";
  _rosterBox = new QComboBox();
  _dccNumBox = new JTextField();
  _trainNameBox = new JTextField(6);
  _depth =20;
  _pickRouteDialog = NULL;
  _tempWarrant = NULL;
  log = new Logger("WarrantRoute");
  _viewProfile = new QPushButton(tr("View Speed Profile"));

  getRoster();
 }

 /*public*/ /*abstract*/ void WarrantRoute::selectedRoute(QList <BlockOrder*>* /*orders*/) {}
 /*public*/ /*abstract*/ void WarrantRoute::propertyChange(PropertyChangeEvent* /*e*/) {}

 /*public*/ int WarrantRoute::getDepth() {
     bool bok;
     _depth = _searchDepth->text().toInt(&bok);
     if(!bok) {
         _searchDepth->setText(QString::number(_depth));
     }
     return _depth;
 }
 /*public*/ void WarrantRoute::setDepth(int d) {
     _depth = d;
     _searchDepth->setText(QString::number(_depth));
 }

 /*public*/ QWidget* WarrantRoute::searchDepthPanel(bool vertical) {
     _searchDepth->setText(QString::number(_depth));
     QWidget* p = new QWidget();
     FlowLayout* pLayout = new FlowLayout(p);
//     pLayout->addWidget(Box.createHorizontalGlue());
     pLayout->addWidget(makeTextBoxPanel(vertical, _searchDepth, tr("Max Number of Blocks in Route"), tr("Upper limit for the number of OBlocks in a warrant route")));
     _searchDepth->setColumns(5);
//     p->layout()->addWidget(Box.createHorizontalGlue());
     return p;
 }

/************************** Loco Address **********************/

 /*protected*/ QWidget* WarrantRoute::makeTrainPanel() {
     QWidget* trainPanel = new QWidget();
     //trainPanel.setLayout(new BoxLayout(trainPanel, BoxLayout.LINE_AXIS));
     QHBoxLayout* trainPanelLayout = new QHBoxLayout(trainPanel);
     trainPanelLayout->addStrut(STRUT_SIZE);

     QWidget* panel = new QWidget();
     //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
     QVBoxLayout* panelLayout = new QVBoxLayout(panel);
//        panelLayout->addWidget->addWidget(Box.createVerticalStrut(STRUT_SIZE));
     panelLayout->addWidget(makeTextBoxPanel(false, _trainNameBox, "TrainName", "noTrainName"));
//        panelLayout->addWidget->addWidget(Box.createVerticalStrut(STRUT_SIZE));
     panelLayout->addWidget(makeTextBoxPanel(false, _rosterBox, "Roster", NULL));
//        panelLayout->addWidget->addWidget(Box.createVerticalStrut(STRUT_SIZE));
     panelLayout->addWidget(makeTextBoxPanel(false, _dccNumBox, "DccAddress", NULL));
     trainPanelLayout->addWidget(panel);
     trainPanelLayout->addStrut(STRUT_SIZE);

//     _dccNumBox.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             setTrainInfo(_dccNumBox.getText());
//         }
//     });
     connect(_dccNumBox, SIGNAL(leaveField()), this, SLOT(on_dccNumBox()));
     QWidget* x = new QWidget();
     //x.setLayout(new BoxLayout(x, BoxLayout.PAGE_AXIS));
     QVBoxLayout* xLayout = new QVBoxLayout(x);
     xLayout->addWidget(trainPanel);
//        x.add(Box.createRigidArea(new QSize(600, 2)));
     return x;
 }
void WarrantRoute::on_dccNumBox()
{
 setTrainInfo(_dccNumBox->text());
}

/*public*/ QWidget* WarrantRoute::calculatePanel(bool vertical)
{
    _calculateButton->setMaximumSize(_calculateButton->sizeHint());
//    _calculateButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            calculate();
//        }
//    });
    connect(_calculateButton, SIGNAL(clicked(bool)), this, SLOT(calculate()));
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
//        p.add(Box.createHorizontalGlue());
    pLayout->addWidget(makeTextBoxPanel(vertical, _calculateButton, "CalculateRoute", ""));
//        p.add(Box.createHorizontalGlue());
    return p;
}

/*public*/ QWidget* WarrantRoute::makePickListPanel()
{
    QPushButton* button = new QPushButton(tr("OBlock Pick List"));
    button->setMaximumSize(_calculateButton->sizeHint());
//    button.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (_pickListFrame !=null) {
//                _pickListFrame.dispose();
//            }
//            _pickListFrame = new JmriJFrame();
//            PickListModel<OBlock> model = PickListModel.oBlockPickModelInstance();
//            _pickListFrame.add(new JScrollPane(model.makePickTable()));
//            _pickListFrame.pack();
//            _pickListFrame.setVisible(true);
//        }
//    });
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onButton()));
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    pLayout->addWidget(button);
    return p;
}

void WarrantRoute::onButton()
{
 if (_pickListFrame !=nullptr) {
     _pickListFrame->dispose();
 }
 _pickListFrame = new JmriJFrameX("Pick");
 PickListModel* model = PickListModel::oBlockPickModelInstance();
 QScrollArea* sa;
 _pickListFrame->setCentralWidget(sa =new QScrollArea(/*model.makePickTable()*/));
 sa->setWidget(model->makePickTable());
 sa->setWidgetResizable(true);
 _pickListFrame->pack();
 _pickListFrame->setVisible(true);

}

/* ************************* Train ID info: Loco Address, etc **********************/
/**
 * Make panel containing TextFields for Train name and address and ComboBox
 * for Roster entries
 *
 * @param comp optional panel to add
 * @return panel
 */
/*protected*/ QWidget* WarrantRoute::makeTrainIdPanel(QWidget* comp) {
    QWidget* trainPanel = new QWidget();
    //trainPanel.setLayout(new BoxLayout(trainPanel, BoxLayout.LINE_AXIS));
    QHBoxLayout* trainPanelLayout = new QHBoxLayout(trainPanel);
    trainPanelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));

    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(makeTextBoxPanel(false, _trainNameBox, "TrainName", "noTrainName"));
    panelLayout->addWidget(makeTextBoxPanel(false, _rosterBox, "Roster", ""));
    panelLayout->addWidget(Box::createVerticalStrut(2));
    panelLayout->addWidget(makeTextBoxPanel(false, _dccNumBox, "DccAddress", ""));
    QWidget* p = new QWidget();
    //p.setLayout(new BoxLayout(p, BoxLayout.LINE_AXIS));
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    pLayout->addWidget(_viewProfile);
    panelLayout->addWidget(p);
    if (comp != nullptr) {
        panelLayout->addWidget(comp);
    }
    trainPanelLayout->addWidget(panel);
    trainPanelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));

//    _dccNumBox->addActionListener((ActionEvent e) -> {
//        setTrainInfo(_dccNumBox.getText());
//    });
    connect(_dccNumBox, SIGNAL(leaveField()), this, SLOT(on_dccNumBox()));
    return trainPanel;
}


 /*private*/ void WarrantRoute::getRoster()
{
     QList<RosterEntry*> list = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
//     _rosterBox.setRenderer(new jmri.jmrit.roster.swing.RosterEntryListCellRenderer());
     _rosterBox->addItem(" ");
     _rosterBox->addItem(tr("Address not in Roster."));
     for (int i = 0; i < list.size(); i++) {
         RosterEntry* r = list.at(i);
         _rosterBox->addItem(r->titleString());
     }
     //_rosterBox = Roster.instance().fullRosterComboBox();
     _rosterBox->setMaximumSize(_rosterBox->sizeHint());
//     _rosterBox.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             String selection = (String)_rosterBox.getSelectedItem();
//             if (tr("noSuchAddress")==(selection)) {
//                 _dccNumBox.setText(NULL);
//             } else {
//                 setTrainInfo(selection);
//             }
//         }
//     });
     connect(_rosterBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_rosterBoxCurrentIndexChanged(QString)));
 }
void WarrantRoute::on_rosterBoxCurrentIndexChanged(QString selection)
{
 if (tr("noSuchAddress")==(selection))
 {
     _dccNumBox->setText(NULL);
 } else {
     setTrainInfo(selection);
 }
}
 /**
  * Set the roster entry, if it exists, or train id string if not.
  * i.e. set enough info to get a dccLocoAddress
  * @param name may be roster Id or address
  * @return
  */
 /*protected*/ QString WarrantRoute::setTrainInfo(QString name)
{
  if (  log->isDebugEnabled())
  {
   log->debug("setTrainInfo for: " + name);
  }
  _train = Roster::getDefault()->entryFromTitle(name);
  if (_train == NULL) {
      if (name==NULL || name.trimmed().length()==0) {
       _trainId = "";
          return tr("Locomotive not Assigned.");
      }
      int index = name.indexOf('(');
      QString numId;
      bool isLong = true;
      if (index >= 0) {
          if ((index + 1) < name.length()
                  && (name.at(index + 1) == 'S' || name.at(index + 1) == 's')) {
              isLong = false;
          }
          numId = name.mid(0, index);
      } else {
          QChar ch = name.at(name.length()-1);
          if (!ch.isDigit()) {
              if (ch == 'S' || ch == 's') {
                  isLong = false;
              }
              numId = name.mid(0, name.length()-1);
          } else {
              numId = name;
          }
      }
      QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, numId, NULL, NULL, NULL, NULL);
      if (l.size() > 0) {
          _train = l.at(0);
      } else {
          _train = NULL;
          bool bok;
              int num = numId.toInt(&bok);
              isLong = (name.at(0) == '0' || num > 255);  // leading zero means long
              _trainId = QString::number(num)+"("+(isLong?'L':'S')+")";
              if(!bok) {
               _trainId = "";
              return tr("\"%1\" is not a valid DCC address.").arg( name);
          }
      }
  }
  if (_train != NULL) {
      _trainId =  _train->getId();
      _rosterBox->setCurrentIndex(_rosterBox->findText(_train->getId()));
      _dccNumBox->setText(_train->getDccLocoAddress()->toString());
  } else {
      _rosterBox->setCurrentIndex(_rosterBox->findText(tr("Address not in Roster.")));
      _dccNumBox->setText(_trainId);
  }
  QString n = _trainNameBox->text();
  if (n == NULL || n.length() == 0) {
      if (_train != NULL) {
          _trainNameBox->setText(_train->getRoadNumber());
      } else {
          _trainNameBox->setText(_trainId);
      }
  }
  return NULL;
 }

 /*protected*/ RosterEntry* WarrantRoute::getTrain() {
     return _train;
 }

 /*protected*/ void WarrantRoute::setTrainName(QString name) {
     _trainNameBox->setText(name);
 }

 /*protected*/ QString WarrantRoute::getTrainName() {
     QString trainName = _trainNameBox->text();
     if (trainName == NULL || trainName.length() == 0) {
         trainName = _dccNumBox->text();
     }
     return trainName;
 }

 /*protected*/ void WarrantRoute::setAddress(QString address) {
     _dccNumBox->setText(address);
     if (address==NULL) {
         _rosterBox->setCurrentIndex(0);
     }
 }

 /*protected*/ QString WarrantRoute::getAddress() {
     return _dccNumBox->text();
 }

 /*protected*/ QString WarrantRoute::getTrainId() {
     return _trainId;
 }

 /*protected*/ DccLocoAddress* WarrantRoute::getLocoAddress() {
     if (_train!=NULL) {
         return _train->getDccLocoAddress();
     }
     if (_trainId!=NULL) {
         QString numId;
         int index = _trainId.indexOf('(');
         if (index >= 0) {
             numId = _trainId.mid(0, index);
         } else {
             numId = _trainId;
         }
         bool isLong = true;
         if ((index + 1) < _trainId.length()
                 && (_trainId.at(index + 1) == 'S' || _trainId.at(index + 1) == 's')) {
             isLong = false;
         }
         bool bok;
             int num = numId.toInt();
             return new DccLocoAddress(num, isLong);
             if(!bok) {
             return NULL;
         }
     }
     return NULL;
 }

 /*protected*/ QString WarrantRoute::checkLocoAddress() {
     if (_train != NULL || _trainId != NULL) {
         return NULL;
     }
     return setTrainInfo(_dccNumBox->text());
 }

/*private*/ void WarrantRoute::calculate() {
    QString msg = findRoute();
    if (msg != "") {
        JOptionPane::showMessageDialog(this, msg,
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
    }
}

/******************************* route info *******************/
 /**
  * Does the action on each of the 4 RouteLocation panels
  */
 /*public*/ void WarrantRoute::actionPerformed(JActionEvent* e)
{
 QObject* obj = e->getSource();
//        if (  log->isDebugEnabled())   log->debug("actionPerformed: source "+((Component)obj).getName()+
//                     " id= "+e.getID()+", ActionCommand= "+e.getActionCommand());
 doAction(obj);
}

 //@SuppressWarnings("unchecked") // parameter can be any of several types, including JComboBox<String>
void WarrantRoute::doAction(QObject* obj)
{
     //if (obj instanceof JTextField)
 if(qobject_cast<JTextField*>(obj) != NULL)
 {
  JTextField* box = (JTextField*)obj;
  if (!_origin->checkBlockBox(box))
  {
   if (!_destination->checkBlockBox(box))
   {
    if (!_via->checkBlockBox(box))
    {
     if (!_avoid->checkBlockBox(box))
     {
     }
    }
   }
  }
 }
 else
 {
  QComboBox* box = (QComboBox*)obj;
  if (!_origin->checkPathBox(box))
  {
   if (!_destination->checkPathBox(box))
   {
    if (!_via->checkPathBox(box))
    {
     if (!_avoid->checkPathBox(box))
     {
      if (_origin->checkPortalBox(box))
      {
          _origin->setOrderExitPortal();
      }
      if (_destination->checkPortalBox(box))
      {
          _destination->setOrderEntryPortal();
      }
     }
    }
   }
  }
 }
}

/*protected*/ QWidget* WarrantRoute::makeBlockPanels()
{
  QWidget* panel = new QWidget();
  //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
  QVBoxLayout* panelLayout = new QVBoxLayout(panel);

  QWidget* oPanel = _origin->makePanel(tr("Originating Location"), tr("Starting location of the train. Train must be located here to record or playback a warrant script"), tr("Path Name"), tr("Exit Portal Name"), this);
  panelLayout->addWidget(oPanel);

  oPanel = _destination->makePanel(tr("Destination Location"), tr("Ending location of the train when warrant expires (record or playback is terminated)."), tr("Path Name"), tr("Entry Portal Name"), this);
  panelLayout->addWidget(oPanel);

  oPanel = _via->makePanel(tr("Via Location"), tr("Route of the warrant should include this location (Optional)."), tr("Path Name"), NULL, this);
  panelLayout->addWidget(oPanel);

  oPanel = _avoid->makePanel(tr("Avoid Location"), tr("Route of the warrant should exclude this location (Optional)."), tr("Path Name"), NULL, this);
  panelLayout->addWidget(oPanel);
  return panel;
}

/*protected*/ QWidget* WarrantRoute::makeBlockPanels(bool add)
{
    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);

    QWidget* oPanel = _origin->makePanel("OriginBlock", "OriginToolTip", "PathName", "ExitPortalName", this);
    panelLayout->addWidget(oPanel);

    oPanel = _destination->makePanel("DestBlock", "DestToolTip", "PathName", "EntryPortalName", this);
    panelLayout->addWidget(oPanel);

    oPanel = _via->makePanel("ViaBlock", "ViaToolTip", "PathName", "", this);

    QWidget* aPanel = _avoid->makePanel("AvoidBlock", "AvoidToolTip", "PathName", "", this);

    if (add)
    {
        QWidget* pLeft = new QWidget();
        //pLeft.setLayout(new BoxLayout(pLeft, BoxLayout.PAGE_AXIS));
        QVBoxLayout* pLeftLayout = new QVBoxLayout(pLeft);
        pLeftLayout->addWidget(oPanel);
        pLeftLayout->addWidget(aPanel);

        QWidget* pRight = new QWidget();
        //pRight.setLayout(new BoxLayout(pRight, BoxLayout.PAGE_AXIS));
        QVBoxLayout* pRightLayout = new QVBoxLayout(pRight);

        pRightLayout->addWidget(searchDepthPanel(true));
        pRightLayout->addWidget(makePickListPanel());
        pRightLayout->addWidget(calculatePanel(true));

        QWidget* p = new QWidget();
        //p.setLayout(new BoxLayout(p, BoxLayout.LINE_AXIS));
        QHBoxLayout* pLayout = new QHBoxLayout(p);
        pLayout->addWidget(pLeft);
        pLayout->addWidget(pRight);
        panelLayout->addWidget(p);
    } else {
        panelLayout->addWidget(oPanel);
        panelLayout->addWidget(aPanel);
    }
    return panel;
}

 /*private*/ QWidget* WarrantRoute::makeLabelCombo(QString title, QComboBox* box, QString tooltip)
 {
  QWidget* p = new QWidget();
  QVBoxLayout* pLayout;
  p->setLayout(pLayout = new QVBoxLayout); //BorderLayout());
  p->setToolTip((tooltip));
  box->setToolTip((tooltip));
  pLayout->addWidget(new QLabel(PAD+(title)+PAD), 0, Qt::AlignTop);//, BorderLayout.NORTH);
  pLayout->addWidget(box,/* BorderLayout.CENTER*/0, Qt::AlignCenter);
//     box.setBackground(QColor(Qt::white));
//     box.addActionListener(this);
//     box.setAlignmentX(JComponent.CENTER_ALIGNMENT);
  return p;
 }

 /*private*/ bool WarrantRoute::setOriginBlock() {
     return _origin->setBlock();
 }

 /*private*/ bool WarrantRoute::setDestinationBlock() {
     return _destination->setBlock();
 }

 /*private*/ bool WarrantRoute::setViaBlock() {
     return _via->setBlock();
 }

 /*private*/ bool WarrantRoute::setAvoidBlock() {
     return _avoid->setBlock();
 }

 /*********** route blocks **************************/

// /*protected*/ class RouteLocation extends java.awt.event.MouseAdapter  {

//     Location location;
//     /*private*/ BlockOrder order;
//     JTextField blockBox = new JTextField();
//     /*private*/ JComboBox<String> pathBox = new JComboBox<String>();
//     /*private*/ JComboBox<String> portalBox;

RouteLocation::RouteLocation(WarrantRoute::Location loc, WarrantRoute* warrantRoute)
{
 blockBox = new JTextField();
 connect(blockBox, SIGNAL(editingFinished()), this, SLOT(on_blockBox_editingCompleted()));
 pathBox = new QComboBox();
 connect(pathBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_pathBox_currentIndexChanged(int)));
 this->warrantRoute = warrantRoute;
 location = loc;
 portalBox = NULL;
 if (location==WarrantRoute::ORIGIN ||location==WarrantRoute::DEST)
 {
  portalBox = new QComboBox();
  connect(portalBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_portalBox_currentIndexChanged(int)));
 }
}
void RouteLocation::on_blockBox_editingCompleted()
{
 emit actionPerformed(new JActionEvent(blockBox,0,NULL));
}
void RouteLocation::on_pathBox_currentIndexChanged(int)
{
 emit actionPerformed(new JActionEvent(pathBox,0,NULL));
}
void RouteLocation::on_portalBox_currentIndexChanged(int)
{
 emit actionPerformed(new JActionEvent(portalBox, 0, NULL));
}

/*private*/ QWidget* RouteLocation::makePanel(QString title, QString tooltip, QString box1Name, QString box2Name, WarrantRoute* parent)
{
 QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

 QGroupBox* oPanel = new QGroupBox();
 oPanel->setStyleSheet(gbStyleSheet);
 oPanel->setTitle(title);
//         oPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//                 tr(title),
//                 javax.swing.border.TitledBorder.CENTER,
//                 javax.swing.border.TitledBorder.TOP));
 QWidget* hPanel = new QWidget();
 QHBoxLayout* hPanelLayout;
 hPanel->setLayout(hPanelLayout = new QHBoxLayout); //(hPanel, BoxLayout.X_AXIS));
 hPanelLayout->addStrut(WarrantRoute::STRUT_SIZE);
 hPanelLayout->addWidget(makeBlockBox(tooltip));
 hPanelLayout->addStrut(WarrantRoute::STRUT_SIZE);
 QWidget* pPanel = new QWidget();
 QHBoxLayout* panelLayout;
 pPanel->setLayout(panelLayout = new QHBoxLayout); //(pPanel, BoxLayout.X_AXIS));
 panelLayout->addWidget(warrantRoute->makeLabelCombo(box1Name, pathBox, tooltip));
 panelLayout->addStrut(WarrantRoute::STRUT_SIZE);

 if (box2Name != NULL)
 {
  panelLayout->addWidget(warrantRoute->makeLabelCombo(box2Name, portalBox, tooltip));
  panelLayout->addStrut(WarrantRoute::STRUT_SIZE);
 }
 hPanelLayout->addWidget(pPanel);
 QHBoxLayout* oPanelLayout = new QHBoxLayout(oPanel);
 oPanelLayout->addWidget(hPanel);
 pPanel->setToolTip((tooltip));
 hPanel->setToolTip((tooltip));
 oPanel->setToolTip((tooltip));

//         blockBox.addActionListener(parent);
//         blockBox.addPropertyChangeListener(parent);
 connect(blockBox, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//         blockBox.addMouseListener(this);

 return oPanel;
}

/*private*/ QWidget* RouteLocation::makeBlockBox(QString tooltip)
{
 blockBox->setDragEnabled(true);
//         blockBox.setTransferHandler(new jmri.util.DnDStringImportHandler());
 blockBox->setColumns(20);
 blockBox->setAlignment(Qt::AlignCenter);
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout());
 p->setToolTip((tooltip));
 blockBox->setToolTip((tooltip));
 pLayout->addWidget(new QLabel(tr("Block Name")), 0,  Qt::AlignHCenter);
 pLayout->addWidget(blockBox, 0, Qt::AlignHCenter);
 return p;
}

/*private*/ void RouteLocation::clearFields()
{
 setBlock(NULL);
}

/*private*/ bool RouteLocation::checkBlockBox(JTextField* box)
{
 if (box == blockBox)
 {
  setBlock(getEndPointBlock());
  return true;
 }
 return false;
}

/*private*/ bool RouteLocation::checkPathBox(QComboBox* box)
{
 if (box == pathBox)
 {
  if (portalBox!=NULL)
  {
   setPortalBox(order);
  }
  return true;
 }
 return false;
}
/*private*/ bool RouteLocation::checkPortalBox(QComboBox* box) {
    return (box == portalBox);
}
/*private*/ void RouteLocation::setOrderEntryPortal()
{
 if (order!=NULL)
 {
     order->setEntryName(portalBox->currentText());
 }
}
/*private*/ void RouteLocation::setOrderExitPortal()
{
 if (order!=NULL)
 {
     order->setExitName(portalBox->currentText());
 }
}

/*protected*/ void RouteLocation::setOrder(BlockOrder* o)
{
 if (o!=NULL)
 {
  // setting blockBox text triggers doAction, so allow that to finish
  order = new BlockOrder(o);
  OBlock* block = o->getBlock();
  blockBox->setText(block->getDisplayName());
  setPathBox(block);
  setPathName(o->getPathName());
  setPortalBox(o);
  if (location==WarrantRoute::DEST)
  {
   setPortalName(o->getEntryName());
  }
  else if (location==WarrantRoute::ORIGIN)
  {
   setPortalName(o->getExitName());
  }
 }
}

/*private*/ BlockOrder* RouteLocation::getOrder() {
    return order;
}
/*private*/ void RouteLocation::setPortalName(QString name) {
    portalBox->setCurrentIndex(portalBox->findText(name));
}
/*private*/ void RouteLocation::setPathName(QString name)
{
 pathBox->setCurrentIndex(portalBox->findText(name));
}
/*protected*/ QString RouteLocation::getBlockName() {
    return blockBox->text();
}

/*private*/ OBlock* RouteLocation::getEndPointBlock() {
    QString text = blockBox->text();
#if 0
    int idx = text.indexOf(java.awt.event.KeyEvent.VK_TAB);
    if (idx > 0){
        if (idx+1 < text.length()) {
            text = text.substring(idx+1);
        } else {
            text = text.substring(0, idx);
        }

    }
#endif
    blockBox->setText(text);
    OBlock* block = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getOBlock(text);
    if (block == NULL && text.length()>0) {
//             JOptionPane.showMessageDialog(NULL, tr("BlockNotFound", text),
//                     tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(NULL, tr("warning"), tr("Block \"%1\" not found.").arg(text));
    }
    return block;
}

/*private*/ bool RouteLocation::setBlock() {
    return setBlock(getEndPointBlock());
}
/*private*/ bool RouteLocation::setBlock(OBlock* block)
{
 bool result = true;
 if (block == NULL)
 {
  result = false;
  order = NULL;
 }
 else
 {
  if (order!= NULL && block==order->getBlock() &&
          warrantRoute->pathIsValid(block, order->getPathName())==NULL)
  {
   result = true;
  }
  else
  {
   if (warrantRoute->pathsAreValid(block))
   {
    order = new BlockOrder(block);
    if (!setPathBox(block)) {
        result = false;
    } else {
        setPortalBox(order);
    }
   }
   else
   {
    result = false;
   }
  }
 }
 if (result)
 {
  // block cannot be NULL here. it is /*protected*/ by result==true
  if (block!=NULL) blockBox->setText(block->getDisplayName());
  order->setPathName(pathBox->currentText());
  if (location==WarrantRoute::DEST)
  {
   order->setEntryName(portalBox->currentText());
  }
  else if (location==WarrantRoute::ORIGIN)
  {
   order->setExitName(portalBox->currentText());
  }
  setNextLocation();
 }
 else
 {
  blockBox->setText(NULL);
  pathBox->clear();
  if (portalBox!=NULL)
  {
      portalBox->clear();
  }
 }
 return result;
}
/*private*/ bool RouteLocation::setPathBox(OBlock* block)
{
 pathBox->clear();
 if (portalBox!=NULL)
 {
  portalBox->clear();
 }
 if (block==NULL)
 {
  return false;
 }
 QVector <Path*>* list = block->getPaths();
 if (list->size()==0)
 {
//             JOptionPane.showMessageDialog(NULL, tr("NoPaths", block.getDisplayName()),
//                     tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("No Paths in Block \"%1\"").arg(block->getDisplayName()));
     return false;
 }
 for (int i=0; i<list->size(); i++)
 {
  pathBox->addItem(((OPath*)list->at(i))->getName());
 }
 return true;
}
/*private*/ void RouteLocation::setPortalBox(BlockOrder* order)
{
 if (portalBox==NULL)
 {
     return;
 }
 portalBox->clear();
 QString pathName = pathBox->currentText();
 if (order==NULL)
 {
  return;
 }
 order->setPathName(pathName);
 OPath* path = order->getPath();
 if (path != NULL)
 {
  Portal* portal = path->getFromPortal();
  if (portal!=NULL)
  {
   QString name = portal->getName();
   if (name!=NULL) { portalBox->addItem(name); }
  }
  portal = path->getToPortal();
  if (portal!=NULL)
  {
   QString name = portal->getName();
   if (name!=NULL) { portalBox->addItem(name); }
  }
//                if (  log->isDebugEnabled())   log->debug("setPortalBox: Path "+path->getName()+
//                             " set in block "+order.getBlock().getDisplayName());
 } else {
//                if (  log->isDebugEnabled())   log->debug("setPortalBox: Path set to NULL in block"
//                             +order.getBlock().getDisplayName());
 }
}

/*private*/ void RouteLocation::setNextLocation()
{
  switch (location)
  {
  case WarrantRoute::ORIGIN:
      warrantRoute->_focusedField = warrantRoute->_destination;
      break;
  case WarrantRoute::DEST:
      warrantRoute->_focusedField = warrantRoute->_via;
      break;
  case WarrantRoute::VIA:
     warrantRoute->_focusedField = warrantRoute->_avoid;
      break;
  case WarrantRoute::AVOID:
     warrantRoute-> _focusedField = warrantRoute->_origin;
      break;
  }
 }

//@Override
/*public*/ void RouteLocation::mouseClicked(QMouseEvent* /*e*/)
{
 warrantRoute->_focusedField = this;
}
//};       // end RouteLocation

/*protected*/ void WarrantRoute::mouseClickedOnBlock(OBlock* block)
{
 if (_focusedField!=NULL)
 {
  _focusedField->setBlock(block);
 }
 else
 {
  _origin->setBlock(block);
 }
}

/*private*/ bool WarrantRoute::pathsAreValid(OBlock* block) {
QVector <Path*>* list = block->getPaths();
if (list->size()==0) {
//         JOptionPane.showMessageDialog(this, tr("NoPaths", block.getDisplayName()),
//                 tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
 QMessageBox::warning(NULL, tr("Warning"), tr("No Paths in Block \"%1\"").arg(block->getDisplayName()));
    return false;
}
for (int i=0; i<list->size(); i++) {
    OPath* path = (OPath*)list->at(i);
    if (path->getFromPortal()==NULL && path->getToPortal()==NULL)
    {
//             JOptionPane.showMessageDialog(this, tr("PathNeedsPortal", path->getName(), block.getDisplayName()),
//                     tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(NULL, tr("Warning"), tr("Path \"%1\" in block \"{%2\" needs to have at least one Portal.").arg(path->getName()).arg(block->getDisplayName()));
        return false;
    }
}
return true;
}

/******************************* Finding the route ********************************/

/**
* Gather parameters to search for a route
*/
/*protected*/ QString WarrantRoute::findRoute()
{
 // read and verify origin and destination blocks/paths/portals
 QString msg = NULL;
 BlockOrder* order = NULL;
 QString pathName = NULL;
 if (setOriginBlock())
 {
  order = _origin->getOrder();
  pathName = order->getPathName();
  if (pathName!=NULL)
  {
   if (order->getExitName() == NULL)
   {
     msg = tr("Set a portal to exit from the %1 of the route. ").arg(tr("Originating Location"));
   }
   else
   {
    msg = pathIsValid(order->getBlock(), pathName);
   }
  }
  else
  {
   msg = tr("Set a path for the %1 of the route.").arg(tr("Originating Location"));
  }
 }
 else
 {
  msg = tr("Enter a block name for the %1 of the route.").arg(tr("Originating Location"));
 }
 if (msg==NULL)
 {
  if (setDestinationBlock())
  {
   order = _destination->getOrder();
   pathName = order->getPathName();
   if (pathName!=NULL)
   {
    if (order->getEntryName() == NULL)
    {
        msg = tr("Set a portal to enter the %1 of the route. ").arg(tr("Destination Location"));
    } else {
        msg = pathIsValid(order->getBlock(), pathName);
    }
   }
   else
   {
    msg = tr("Set a path for the %1 of the route.").arg( tr("Destination Location"));
   }
  }
  else
  {
   msg = tr("Enter a block name for the %1 of the route.").arg(tr("Destination Location"));
  }
 }
 if (msg==NULL)
 {
  if (setViaBlock())
  {
   order = _via->getOrder();
   if (order!=NULL && order->getPathName()==NULL)
   {
     msg = tr("Set a path for the %1 of the route.").arg(tr("Via Location"));
   }
  }
 }
 if (msg==NULL)
 {
  if (setAvoidBlock())
  {
   order = _avoid->getOrder();
   if (order!=NULL && order->getPathName()==NULL) {
       msg = tr("Set a path for the %1 of the route.").arg( tr("Avoid Location"));
   }
  }
 }
 if (msg==NULL)
 {
  if (  log->isDebugEnabled())   log->debug("Params OK. findRoute() is creating a RouteFinder");
  _routeFinder = new RouteFinder(this, _origin->getOrder(), _destination->getOrder(),
          _via->getOrder(), _avoid->getOrder(), getDepth());
 // new Thread(_routeFinder).start();
 QThread* thread = new QThread;
 connect(thread, SIGNAL(started()), _routeFinder, SLOT(process()));
 connect(_routeFinder, SIGNAL(finished()), thread, SLOT(quit()));
 connect(_routeFinder, SIGNAL(finished()), _routeFinder, SLOT(deleteLater()));
 connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
 thread->start();

 }
 return msg;
}

/*protected*/ void WarrantRoute::stopRouteFinder()
{
 if (_routeFinder!=NULL)
 {
  _routeFinder->quit();
  _routeFinder = NULL;
 }
}

/************************************ Route Selection **************************************/

/*public*/ void WarrantRoute::setOrders(QList <BlockOrder*> oList)
{
 for (int i=0; i<oList.size(); i++)
 {
     BlockOrder* bo = new BlockOrder(oList.at(i));
     _orders->append(bo);
 }
}

/*public*/ QList<BlockOrder*>* WarrantRoute::getOrders() {
 return _orders;
}

/*public*/ BlockOrder* WarrantRoute::getViaBlockOrder() {
 return _via->getOrder();
}

/*public*/ BlockOrder* WarrantRoute::getAvoidBlockOrder() {
 return _avoid->getOrder();
}

/*protected*/ void WarrantRoute::clearTempWarrant()
{
 if (_tempWarrant!=NULL)
 {
  _tempWarrant->deAllocate();
  _tempWarrant = NULL;
 }
}

/*private*/ void WarrantRoute::showTempWarrant(QList<BlockOrder*>* orders)
{
 QString s = QString::number(qrand()).mid(4);
 _tempWarrant = new Warrant("IW"+s+"TEMP", NULL);
 _tempWarrant->setBlockOrders(orders);
 QString msg = _tempWarrant->setRoute(0, orders);
 if (msg!=NULL)
 {
  //         JOptionPane.showMessageDialog(NULL, msg,
  //                 tr("WarningTitle"),
  //                 JOptionPane.WARNING_MESSAGE);
  showWarning(msg);
 }
}

/**
*  Callback from RouteFinder - several routes found
*/
/*protected*/ void WarrantRoute::pickRoute(QList <DefaultMutableTreeNode*>* destNodes, DefaultTreeModel* routeTree)
{
 if (destNodes->size()==1)
 {
 showRoute(destNodes->at(0), routeTree);
 selectedRoute(_orders);
 return;
 }
 _pickRouteDialog = new JDialog(this, tr("Possible Routes"), false);
 _pickRouteDialog->addWindowListener(new PRWindowListener(this));
 //  {
 //      //@Override
 //      /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
 //          clearTempWarrant();
 //      }
 //  });
 _tempWarrant = NULL;
 QWidget* mainPanel = new QWidget();
 //mainPanel.setLayout(new BorderLayout(5,5));
 QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
 QWidget* panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 panelLayout->addWidget(new QLabel(tr("%1 routes found.  Review and").arg( QString::number(destNodes->size()))));
 panelLayout->addWidget(new QLabel(tr("Select the one you want to use.")));

 mainPanelLayout->addWidget(panel, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 QButtonGroup* buttons = new QButtonGroup();
 QPushButton* ok;
 QPushButton* _show;
 {
 panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 for (int i=0; i<destNodes->size(); i++) {
 QRadioButton* button = new QRadioButton(tr("Route %1 traverses %2 blocks.").arg(i+1).arg( destNodes->at(i)->getLevel()+1) );
  //button.setActionCommand(""+i);
 //      button.addActionListener(new ActionListener() {
 //          /*public*/ void actionPerformed(ActionEvent e) {
 //              clearTempWarrant();
 //          }
 //      });
 connect(button, SIGNAL(clicked()), this, SLOT(clearTempWarrant()));
  buttons->addButton(button);
  panelLayout->addWidget(button);
 }
 QScrollArea* scrollPane = new QScrollArea(/*panel*/);
 scrollPane->setWidget(panel);
 mainPanelLayout->addWidget(scrollPane, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 ok = new QPushButton(tr("Select"));
 //  ok.addActionListener(new ActionListener() {
 //          ButtonGroup buts;
 //          JDialog dialog;
 //          List <DefaultMutableTreeNode> dNodes;
 //          DefaultTreeModel tree;
 //          /*public*/ void actionPerformed(ActionEvent e) {
 //              if (buts.getSelection()!=NULL) {
 //                  clearTempWarrant();
 //                  int i = Integer.parseInt(buttons.getSelection().getActionCommand());
 //                  showRoute(dNodes.get(i), tree);
 //                  selectedRoute(_orders);
 //                  dia  log->dispose();
 //              } else {
 //                  showWarning(tr("SelectRoute"));
 //              }
 //          }
 //          ActionListener init(ButtonGroup bg, JDialog d, List <DefaultMutableTreeNode> dn,
 //                              DefaultTreeModel t) {
 //              buts = bg;
 //              dialog = d;
 //              dNodes = dn;
 //              tree = t;
 //              return this;
 //          }
 //      }.init(buttons, _pickRouteDialog, destNodes, routeTree));
 SelectActionListener* seal = new SelectActionListener();
 seal->init(buttons, _pickRouteDialog, destNodes, routeTree, this);
 connect(ok, SIGNAL(clicked()), seal, SLOT(actionPerformed()));
 ok->setMaximumSize(ok->sizeHint());
 _show = new QPushButton(tr("Review"));
 //  show.addActionListener(new ActionListener();
 //  {
 //          ButtonGroup buts;
 //          List <DefaultMutableTreeNode> destinationNodes;
 //          DefaultTreeModel tree;
 //          /*public*/ void actionPerformed(ActionEvent e) {
 //              if (buts.getSelection()!=NULL) {
 //                  clearTempWarrant();
 //                  int i = Integer.parseInt(buttons.getSelection().getActionCommand());
 //                  showRoute(destinationNodes.get(i), tree);
 //                  showTempWarrant(_orders);
 //              } else {
 //                  showWarning(tr("SelectRoute"));
 //              }
 //          }
 //          ActionListener init(ButtonGroup bg, List <DefaultMutableTreeNode> dn,
 //                              DefaultTreeModel t) {
 //              buts = bg;
 //              destinationNodes = dn;
 //              tree = t;
 //              return this;
 //          }
 //      }.init(buttons, destNodes, routeTree));
 ShowActionListener* shal = new ShowActionListener();
 shal->init(buttons, destNodes, routeTree, this);
 connect(_show, SIGNAL(clicked()), shal, SLOT(actionPerformed()));
 _show->setMaximumSize(_show->sizeHint());
 }
 {
 panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 panelLayout->addStrut(STRUT_SIZE);
 panelLayout->addWidget(_show);
 panelLayout->addStrut(STRUT_SIZE);
 panelLayout->addWidget(ok);
 panelLayout->addStrut(STRUT_SIZE);
 mainPanelLayout->addWidget(panel, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
 }
 {
  panel = new QWidget();
  //panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout(panel);
  panelLayout->addStrut(STRUT_SIZE);
  panelLayout->addWidget(makeRouteTablePanel());
  panelLayout->addStrut(STRUT_SIZE);
  panelLayout->addWidget(mainPanel);
  panelLayout->addStrut(STRUT_SIZE);

  //_pickRouteDialog->getContentPane().add(panel);
  QVBoxLayout* contentLayout = new QVBoxLayout(_pickRouteDialog);
  contentLayout->addWidget(panel);
  _pickRouteDialog->setLocation(pos().x()-20, pos().y()+150);
  _pickRouteDialog->adjustSize();
  _pickRouteDialog->setVisible(true);
 }
}

/*public*/ void WarrantRoute::showWarning(QString msg) {
//     JOptionPane.showMessageDialog(this, msg,
//             tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
 QMessageBox::warning(this, tr("Warning"), msg);
}

/**
*  Callback from RouteFinder - exactly one route found
*/
/*protected*/ void WarrantRoute::showRoute(DefaultMutableTreeNode* destNode, DefaultTreeModel* tree)
{
 QList<TreeNode*>* nodes = tree->getPathToRoot(destNode);
 _orders->clear();
 for (int i=0; i<nodes->length(); i++)
 {
  _orders->append(VPtr<BlockOrder>::asPtr(((DefaultMutableTreeNode*)nodes->at(i))->getUserObject()));
 }
 _routeModel->fireTableDataChanged();
 if (  log->isDebugEnabled())   log->debug("showRoute: Route has "+QString::number(_orders->size())+" orders.");
}

/*protected*/ QWidget* WarrantRoute::makeRouteTablePanel()
{
 JTable* routeTable = new JTable(_routeModel);
 //  routeTable.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
 //routeTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 routeTable->setColumnModel(new DefaultTableColumnModel(routeTable));
 for (int i=0; i<_routeModel->columnCount(QModelIndex()); i++)
 {
  int width = _routeModel->getPreferredWidth(i);
  routeTable->getColumnModel()->addColumn(new TableColumn());
  routeTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 //JScrollPane tablePane = new JScrollPane(routeTable);
 QSize dim = routeTable->sizeHint();
 //  dim.setHeight( routeTable->getRowHeight()*8);
 //  tablePane.getViewport().setPreferredSize(dim);

 QWidget* routePanel = new QWidget();
 QVBoxLayout* routePanelLayout = new QVBoxLayout(routePanel);
 //routePanel.setLayout(new BoxLayout(routePanel, BoxLayout.Y_AXIS));
 QLabel* title = new QLabel(tr("Route Table"));
 routePanelLayout->addWidget(title, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 routePanelLayout->addWidget(routeTable);
 return routePanel;
}

/**
*  Callback from RouteFinder - no routes found
*/
/*protected*/ void WarrantRoute::debugRoute(DefaultTreeModel* tree, BlockOrder* origin, BlockOrder* dest)
{
 //     if (JOptionPane.NO_OPTION == JOptionPane.showConfirmDialog(this, tr("NoRoute",
 //                         new Object[] {origin.getBlock().getDisplayName(),
 //                                     origin.getPathName(), origin.getExitName(), dest.getBlock().getDisplayName(),
 //                                      dest.getEntryName(), dest.getPathName(), Integer.valueOf(getDepth()) }),
 //                             tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
 //                                                 JOptionPane.WARNING_MESSAGE)) {
 if(QMessageBox::warning(this, tr("Warning"), tr("No Route found from \"%1\"on  path \"%2\"\nexiting at \"%3\" and entering \"%4\"\nat \"%5\" on path \"%6\" within %7 blocks.\nCheck that the Portals and Paths for exit and entry are correctly defined.\n\nShow the search tree?").arg(origin->getBlock()->getDisplayName()).arg(origin->getPathName()).arg(origin->getExitName()).arg(dest->getBlock()->getDisplayName()).arg(dest->getEntryName()).arg(dest->getPathName()).arg(getDepth()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
 {
  return;
 }

 if (_debugFrame!=NULL) {
  _debugFrame->dispose();
 }
 _debugFrame = new JFrame(tr("DebugRoute"));
 JTree* dTree = new JTree(tree);
 dTree->setShowsRootHandles(true);
 dTree->setScrollsOnExpand(true);
 dTree->setExpandsSelectedPaths(true);
 //JScrollPane treePane = new JScrollPane(dTree);
 //treePane.getViewport().setPreferredSize(new QSize(900, 300));
 // _debugFrame.getContentPane().add(treePane);
 _debugFrame->setCentralWidget(dTree);
 _debugFrame->setVisible(true);
 _debugFrame->adjustSize();

}

/*protected*/ void WarrantRoute::clearRoute()
{
 _orders = new QList <BlockOrder*>();
 clearFrames();
 clearFields();
 _focusedField = _origin;
 _routeModel->fireTableDataChanged();
}

/*private*/ void WarrantRoute::clearFrames()
{
 if (_debugFrame!=NULL)
 {
 _debugFrame->dispose();
 _debugFrame = NULL;
 }
 if (_pickRouteDialog!=NULL)
 {
 _pickRouteDialog->close();
 _pickRouteDialog = NULL;
 }
}



/*private*/ void WarrantRoute::clearFields() {
_origin->clearFields();
_destination->clearFields();
_via->clearFields();
_avoid->clearFields();
}

/*protected*/ QString WarrantRoute::routeIsValid() {
QString msg = NULL;
if (_orders->size() == 0) {
    return tr("noBlockOrders");
}
BlockOrder* blockOrder = _orders->at(0);
msg =pathIsValid(blockOrder->getBlock(), blockOrder->getPathName());
if (msg==NULL){
    for (int i=1; i<_orders->size(); i++){
        BlockOrder* nextBlockOrder = _orders->at(i);
        msg = pathIsValid(nextBlockOrder->getBlock(), nextBlockOrder->getPathName());
        if (msg!=NULL) {
            return msg;
        }
        if (blockOrder->getExitName()!=(nextBlockOrder->getEntryName())) {
            return tr("disconnectedRoute %1 %2").arg(
                    blockOrder->getBlock()->getDisplayName()).arg( nextBlockOrder->getBlock()->getDisplayName());
        }
        blockOrder = nextBlockOrder;
    }
}
return msg;
}

/*static*/ /*private*/ QString WarrantRoute::pathIsValid(OBlock* block, QString pathName)
{
 QVector <Path*>* list = block->getPaths();
 if (list->size()==0)
 {
  return tr("WarningTitle");
 }
 if (pathName!=NULL)
 {
  for (int i=0; i<list->size(); i++)
  {
   OPath* path = (OPath*)list->at(i);
   //if (  log->isDebugEnabled())   log->debug("pathIsValid: pathName= "+pathName+", i= "+i+", path is "+path->getName());
   if (pathName==(path->getName()) )
   {
    if (path->getFromPortal()==NULL && path->getToPortal()==NULL)
    {
     return tr("Path \"%1\" in block \"%2\" needs to have at least one Portal.").arg( pathName).arg( block->getDisplayName());
    }
    return NULL;
   }
  }
}
return tr("Path \"%1\" is not a path in block \"%2\".").arg( pathName).arg(block->getDisplayName());
}

//@Override
/*public*/ void WarrantRoute::dispose() {
//     clearFrames();
JmriJFrame::dispose();
}

/************************* Route Table ******************************/
// class RouteTableModel : public AbstractTableModel
// {
//     /**
//      *
//      */
//     /*private*/ static final long serialVersionUID = 1966890806689115258L;
//     /*public*/ static final int BLOCK_COLUMN = 0;
//     /*public*/ static final int ENTER_PORTAL_COL =1;
//     /*public*/ static final int PATH_COLUMN = 2;
//     /*public*/ static final int DEST_PORTAL_COL = 3;
//     /*public*/ static final int NUMCOLS = 4;

/*public*/ RouteTableModel::RouteTableModel(WarrantRoute *warrantRoute) : AbstractTableModel()
{
  //super();
this->warrantRoute = warrantRoute;
}

/*public*/ int RouteTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return NUMCOLS;
}

/*public*/ int RouteTableModel::rowCount(const QModelIndex &/*parent*/) const{
    return warrantRoute->_orders->size();
}

//@Override
/*public*/ QVariant RouteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
{

    switch (section) {
        case BLOCK_COLUMN: return tr("Block or Sensor Name");
        case ENTER_PORTAL_COL: return tr("Entry Portal");
        case PATH_COLUMN: return tr("Path");
        case DEST_PORTAL_COL: return tr("Exit Portal");
    }
    return "";
}
return QVariant();
}

//@Override
/*public*/ Qt::ItemFlags RouteTableModel::flags(const QModelIndex &/*index*/) const{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//@Override
/*public*/ QString RouteTableModel::getColumnClass(int col) {
 return "String";
}

/*public*/ int RouteTableModel::getPreferredWidth(int /*col*/) {
 return  JTextField(15).getPreferredSize().width();
}

/*public*/ QVariant RouteTableModel::data(const QModelIndex &index, int role) const
{
if(role == Qt::DisplayPropertyRole)
{
 int row = index.row();
 int col = index.column();
    // some error checking
    if (row >= warrantRoute->_orders->size()){
        return "";
    }
    BlockOrder* bo = warrantRoute->_orders->at(row);
    // some error checking
    if (bo == NULL){
        Logger::error("BlockOrder is NULL");
        return "";
    }
    switch (col) {
        case BLOCK_COLUMN:
            return bo->getBlock()->getDisplayName();
        case ENTER_PORTAL_COL:
            return bo->getEntryName();
        case PATH_COLUMN:
            return bo->getPathName();
        case DEST_PORTAL_COL:
            if (row==warrantRoute->_orders->size()-1) { return ""; }
            return bo->getExitName();
    }
    return "";
 }
 return QVariant();
}

//@Override
/*public*/ bool RouteTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
if(role == Qt::EditRole)
{
 int row = index.row();
 int col = index.column();
    BlockOrder* bo = warrantRoute->_orders->at(row);
    OBlock* block = NULL;
    switch (col) {
        case BLOCK_COLUMN:
     block = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getOBlock(value.toString());
            if (block != NULL) { bo->setBlock(block); }
            break;
        case ENTER_PORTAL_COL:
            bo->setEntryName(value.toString());
            break;
        case PATH_COLUMN:
            bo->setPathName(value.toString());
            break;
        case DEST_PORTAL_COL:
            bo->setExitName(value.toString());
            break;
    }
    fireTableRowsUpdated(row, row);
    return true;
 }
 return false;
}
 //};
/**
 * Puts label message to the Left
 *
 * @param vertical Label orientation true = above, false = left
 * @param comp     Component to put into JPanel
 * @param label    Bundle keyword for label message
 * @param tooltip  Bundle keyword for tooltip message
 * @return Panel containing Component
 */
/*static*/ /*protected*/ QWidget* WarrantRoute::makeTextBoxPanel(bool vertical, QWidget* comp, QString label, QString tooltip)
{
 QWidget* panel = new QWidget();
 QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
 sizePolicy.setHorizontalStretch(1);
 sizePolicy.setVerticalStretch(1);
 sizePolicy.setHeightForWidth(false);
 panel->setSizePolicy(sizePolicy);
 int compAlign = 0;
 QLabel* l = new QLabel(label);
 QBoxLayout* panelLayout;
 if (vertical)
 {
     //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
  panelLayout = new QVBoxLayout(panel);
     //l.setAlignmentX(JComponent.CENTER_ALIGNMENT);
     //comp.setAlignmentX(JComponent.CENTER_ALIGNMENT);
  compAlign = Qt::AlignLeft;
  panelLayout->addWidget(Box::createVerticalStrut(STRUT_SIZE));
  panelLayout->addWidget(l, 0, Qt::AlignVCenter);
 }
 else
 {
     //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
  panelLayout = new QHBoxLayout(panel);
//        l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
//        comp.setAlignmentX(JComponent.RIGHT_ALIGNMENT);
  compAlign = Qt::AlignRight;
  panel->layout()->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
  panelLayout->addWidget(l, 0, Qt::AlignLeft);
 }
 //panelLayout.add(l);
 panelLayout->addWidget(l, 0, Qt::AlignLeft);
 if (!vertical) {
     panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
 }
 comp->setMaximumSize(QSize(300, comp->sizeHint().height()));
 comp->setMinimumSize(QSize(30, comp->sizeHint().height()));
 //panelLayout.add(comp);
 if (vertical) {
  panelLayout->addWidget(comp, compAlign, Qt::AlignVCenter);
  panelLayout->addWidget(Box::createVerticalStrut(STRUT_SIZE));
 } else {
  panelLayout->addWidget(comp, compAlign, Qt::AlignRight);
  panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
 }
//    if (comp instanceof JTextField || comp instanceof JComboBox) {
//        comp.setBackground(Color.white);
//    }
 if (tooltip != "")
 {
  QString tipText = (tooltip);
  panel->setToolTip(tipText);
  comp->setToolTip(tipText);
  l->setToolTip(tipText);
 }
// panel->setMaximumSize(QSize(350, comp->sizeHint().height()));
// panel->setMinimumSize(QSize(80, comp->sizeHint().height()));
 return panel;
}

/**
 * Puts label message to the Left, 2nd component (button) to the right
 *
 * @param comp     Component to put into JPanel
 * @param button   2nd Component for panel, usually a button
 * @param label    Bundle keyword for label message
 * @param tooltip  Bundle keyword for tooltip message
 * @return Panel containing Component
 */
/*static*/ /*protected*/ QWidget* WarrantRoute::makeTextAndButtonPanel(QWidget* comp, QWidget* button, QString label, QString tooltip) {
    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    QWidget* l = new QLabel((label));
    //l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    //comp.setAlignmentX(JComponent.RIGHT_ALIGNMENT);
    panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
    panelLayout->addWidget(l, 0, Qt::AlignLeft);
    panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
    panelLayout->addWidget(Box::createHorizontalGlue());

    panelLayout->addWidget(comp, 0, Qt::AlignRight);
#if 0 // TODO:
    if (comp instanceof JTextField || comp instanceof JComboBox) {
        comp.setBackground(Color.white);
    }
#endif
    //button.setAlignmentX(JComponent.RIGHT_ALIGNMENT);
    panelLayout->addWidget(button, 0, Qt::AlignRight);
    panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));

    if (tooltip != "") {
        QString tipText = (tooltip); // note caller translates
        panel->setToolTip(tipText);
        button->setToolTip(tipText);
        comp->setToolTip(tipText);
        l->setToolTip(tipText);
    }
    panel->setMaximumSize(QSize(350, comp->sizeHint().height()));
    panel->setMinimumSize(QSize(80, comp->sizeHint().height()));
    return panel;
}

 /**
 *
 * @param vertical  Label orientation true = above, false = left
 * @param textField
 * @param label String label message
 * @return
 */
/*static*/ /*protected*/ QWidget* WarrantRoute::makeTextBoxPanel(QWidget* comp, QString label, QString tooltip)
 {
 QWidget* panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
 //comp->setAlignmentX(JComponent.LEFT_ALIGNMENT);
 comp->setMaximumSize(QSize(300, comp->sizeHint().height()));
 comp->setMinimumSize(QSize(30, comp->sizeHint().height()));
 panelLayout->addWidget(comp, 0,Qt::AlignLeft);
 //if (comp instanceof JTextField || comp instanceof JComboBox)
 if(qobject_cast<JTextField*>(comp) || qobject_cast<QComboBox*>(comp))
 {
//     comp->setBackground(Color.white);
     QLabel* l = new QLabel((label));
//     l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
     l->setToolTip((tooltip));
     panelLayout->addWidget(l,0, Qt::AlignLeft);
 }
 //else if (comp instanceof AbstractButton)
 if(qobject_cast<QPushButton*>(comp))
 {
     ((QPushButton*) comp)->setText((label));
 }
 panelLayout->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
 if (tooltip != "") {
     QString tipText = (tooltip);
     panel->setToolTip(tipText);
     comp->setToolTip(tipText);
 }
 panel->setMaximumSize(QSize(350, comp->sizeHint().height()));
 panel->setMinimumSize(QSize(80, comp->sizeHint().height()));
 return panel;
}
