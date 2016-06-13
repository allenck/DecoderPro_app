#include "detectionpanel.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include "flowlayout.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "itempalette.h"
#include "picklistmodel.h"
#include "instancemanager.h"
#include "oblock.h"
#include "abstractsensormanager.h"
#include "oblockmanager.h"
#include <QMessageBox>
#include <path.h>
#include "pickpanel.h"
#include "opath.h"
#include "borderlayout.h"
#include "itempanel.h"
#include "systemnamecomparator.h"

//DetectionPanel::DetectionPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
*  Panel for Occupancy and Error detection,
*/
///*public*/ class DetectionPanel extends QWidget* {


/**
*/
/*public*/ DetectionPanel::DetectionPanel(ItemPanel* itemPanel, QWidget* parent) : QWidget(parent)
{
  //super();
  _occDetectorName = new JTextField();   // can be either a Sensor or OBlock name
  log = new Logger("DetectionPanel");
  _parent = itemPanel;
  _pickFrame = NULL;
//    _occDetectorName.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            checkDetection();
//        }
//    });
  connect(_occDetectorName, SIGNAL(textChanged(QString)), this, SLOT(OnTextChanged(QString)));
//    _occDetectorName.addFocusListener(new FocusAdapter() {
//        /*public*/ void focusLost(FocusEvent e) {
//            checkDetection();
//        }
//    });
  connect(_occDetectorName, SIGNAL(editingFinished()), this, SLOT(checkDetection()));
  QVBoxLayout* thisLayout;
  setLayout(thisLayout = new QVBoxLayout);//(this/*, BoxLayout.Y_AXIS*/));
//  QWidget* panel = new QWidget();
//  panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
  QVBoxLayout* panelLayout = new QVBoxLayout;
  panelLayout->addWidget(makeSensorPanel(_occDetectorName, tr("Occupancy Circuit"), "Enter the name of a Sensor or OBlock that detects occupancy for this track item "),0,Qt::AlignCenter);
  _openPicklistButton = new QPushButton(tr("Open Detector Picklist"));
//    _openPicklistButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_pickFrame==NULL) {
//                    openPickList();
//                } else {
//                    closePickList();
//                }
//            }
//    });
  connect(_openPicklistButton, SIGNAL(clicked()), this, SLOT(_openPicklistButton_clicked()));
  _openPicklistButton->setToolTip(tr("The pick list table displays a choice of sensors to do the detection"));
//    QWidget* p = new QWidget();
//    p->setLayout(new FlowLayout);
  QHBoxLayout* pLayout = new QHBoxLayout;
  pLayout->addWidget(_openPicklistButton, 0, Qt::AlignCenter);
  //p->setToolTip(tr("The pick list table displays a choice of sensors to do the detection"));
  panelLayout->addLayout(pLayout);
  thisLayout->addLayout(panelLayout);

  _trainIdPanel = makeTrainIdPanel();
  thisLayout->addWidget(_trainIdPanel);

  _blockPathPanel = new QWidget();
  QVBoxLayout* blockPathPanelLayout;
  _blockPathPanel->setLayout(blockPathPanelLayout = new QVBoxLayout);//(_blockPathPanel/*, BoxLayout.Y_AXIS*/));
//    p = new QWidget();
//    p->setLayout(new FlowLayout);
  pLayout = new QHBoxLayout;
  pLayout->addWidget(new JLabel(tr("Select the path(s) that include this icon")));
  blockPathPanelLayout->addLayout(pLayout);
  _checkBoxPanel = new QWidget();
  _checkBoxPanel->setLayout(new QHBoxLayout);
  blockPathPanelLayout->addWidget(_checkBoxPanel);
  blockPathPanelLayout->addStrut(ItemPalette::STRUT_SIZE);
  _blockPathPanel->setVisible(false);
  _blockPathPanel->setToolTip(tr("Check the paths this icon is needed to display the path."));
  thisLayout->addWidget(_blockPathPanel);
}

void DetectionPanel::_openPicklistButton_clicked()
{
 if (_pickFrame==NULL) {
    openPickList();
 } else {
    closePickList();
 }
}

QWidget* DetectionPanel::makeSensorPanel(JTextField* field, QString text, QString toolTip) {
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QHBoxLayout);
 JLabel* label = new JLabel(text);
 panelLayout->addWidget(label);
 QSize dim = field->sizeHint();
 dim.setWidth( 500);
 field->setMaximumSize(dim);
 dim.setWidth(200);
 field->setMinimumSize(dim);
 field->setColumns(20);
 field->setDragEnabled(true);
//    field.setTransferHandler(new jmri.util.DnDStringImportHandler());
 label->setToolTip(toolTip);
 field->setToolTip(toolTip);
 //panel->setToolTip(toolTip);
 panelLayout->addWidget(field);
 return panel;
}

void DetectionPanel::openPickList()
{
 _pickFrame = new JFrame();
 QVBoxLayout* contentLayout;
 if(_pickFrame->centralWidget() == NULL)
 {
  QWidget* content = new QWidget();
  content->setLayout(contentLayout = new QVBoxLayout(content/*, BoxLayout.Y_AXIS*/));
  _pickFrame->setCentralWidget(content);
 }
 else
  contentLayout = (QVBoxLayout*)_pickFrame->centralWidget()->layout();

//    QWidget* blurb = new QWidget();
 QVBoxLayout* blurbLayout = new QVBoxLayout;
//    blurb->setLayout(new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
 blurbLayout->addWidget(new JLabel(tr("Drag name of device (OBlock or Sensor) to Occupancy Detector field.")));
 blurbLayout->addWidget(new JLabel(tr("Drag name of sensor that can detect power to Error Sensor field.")));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
//    QWidget* panel = new QWidget();
//    panel->setLayout(new QVBoxLayout);
 QVBoxLayout* panelLayout = new QVBoxLayout;
 panelLayout->addLayout(blurbLayout);
 contentLayout->addLayout(panelLayout);
 QList<PickListModel*> models = QList<PickListModel*>() << PickListModel::oBlockPickModelInstance()<<
                                PickListModel::sensorPickModelInstance();
 contentLayout->addWidget(new PickPanel(models, this));

 //_pickFrame->setContentPane(content);
 QVBoxLayout* pickFrameLayout = new QVBoxLayout;
 _pickFrame->setLayout(pickFrameLayout = new QVBoxLayout);
 pickFrameLayout->addLayout(contentLayout);
//    _pickFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                closePickList();
//            }
//        });
//    _pickFrame.setLocationRelativeTo(this);
//    _pickFrame->toFront();
 _pickFrame->setVisible(true);
 _pickFrame->pack();
 _openPicklistButton->setText(tr("Close Picklist"));
}

void DetectionPanel::closePickList()
{
 //delete _pickFrame;
 _pickFrame = NULL;
 _openPicklistButton->setText(tr("Open Detector Picklist"));
}

/*private*/ QWidget* DetectionPanel::makeTrainIdPanel() {
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout);
    _showTrainName = new QCheckBox(tr("Display Train Name when occupied by a warranted train."));
    _showTrainName->setToolTip(tr("Track section should display the name of the warranted train when it occupies the section"));
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
    p->layout()->addWidget(_showTrainName);
    p->setToolTip(tr("Track section should display the name of the warranted train when it occupies the section"));
    panel->layout()->addWidget(p);
    return panel;
}

/*public*/ void DetectionPanel::dispose() {
    if (_pickFrame!=NULL) {
       delete _pickFrame;
        _pickFrame = NULL;
    }
}

/****************** Getters & Setters ***************************/

/*public*/ bool DetectionPanel::getShowTrainName() {
    return _showTrainName->isChecked();
}

/*public*/ void DetectionPanel::setShowTrainName(bool show) {
    _showTrainName->setChecked(show);
}

/*public*/ QString DetectionPanel::getOccSensor() {
    QString name = _occDetectorName->text();
    if (name!=NULL && name.trimmed().length()>0) {
        if (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(name)!=NULL) {
            return name;
        }
    }
    return NULL;
}

/*public*/ QString DetectionPanel::getOccBlock() {
    QString name = _occDetectorName->text();
    if (name!=NULL && name.trimmed().length()>0) {
        if (((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(name)!=NULL) {
            return name;
        }
    }
    return NULL;
}

/**
* Name of either Sensor or OBlock for detection
*/
/*public*/ void DetectionPanel::setOccDetector(QString name) {
    _occDetectorName->setText(name);
    checkDetection();
}

/*public*/ QStringList DetectionPanel::getPaths() {
    QStringList paths = QStringList();
    if (!_pathBoxes.isEmpty()) {
        for (int i=0; i<_pathBoxes.size(); i++) {
            if ( _pathBoxes.at(i)->isChecked()) {
                paths.append(_pathBoxes.at(i)->text().trimmed());
            }
        }
    }
    return paths;
}

/*public*/ void DetectionPanel::setPaths(QStringList iconPath) {
    if (iconPath.isEmpty() || _block==NULL) {
        _pathBoxes.clear();
        return;
    }
    for (int k=0; k<iconPath.size(); k++) {
        for (int i=0; i<_pathBoxes.size(); i++) {
            QString name = _pathBoxes.at(i)->text().trimmed();
            if (iconPath.at(k)==(name) ) {
                _pathBoxes.at(i)->setChecked(true);
            }
        }
    }
}
void DetectionPanel::OnTextChanged(QString text)
{
 QStringList completerList;
 QStringList blockSysList = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getSystemNameList();
 foreach(QString s, blockSysList)
     if(s.startsWith(text)) completerList.append(s);
 QStringList blockUsrList = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getUserNameList();
 foreach(QString s, blockUsrList)
     if(s.startsWith(text)) completerList.append(s);

 QStringList sensorSysList = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())-> getSystemNameList();
 foreach(QString s, sensorSysList)
     if(s.startsWith(text)) completerList.append(s);
 QStringList sensorUsrList = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())-> getUserNameList();
 foreach(QString s, sensorUsrList)
     if(s.startsWith(text)) completerList.append(s);

 qSort(completerList.begin(), completerList.end(), SystemNameComparator::compare);
 QCompleter* completer = new QCompleter(completerList);
 _occDetectorName->setCompleter(completer);
}

/*********************************************/

/*private*/ void DetectionPanel::checkDetection()
{
 QString name = _occDetectorName->text();
 if (name!=NULL && name.trimmed().length()>0)
 {
  OBlock* block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(name);
  if (block!=NULL)
  {
   if (block==(_block))
   {
    return;
   }
   makePathList(block);
  }
  else
  {
   Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(name);
   if (sensor==NULL)
   {
//                JOptionPane.showMessageDialog(_parent._paletteFrame, java.text.MessageFormat.format(
//                    tr("InvalidOccDetector"), name),
//                        ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(0, tr("Warning"), tr("%1 is not a valid Sensor or OBlock occupancy detector for Indicator track ").arg(name));
    _occDetectorName->setText("");
   }
  _blockPathPanel->setVisible(false);
  _block = NULL;
  }
 }
 else
 {
  _blockPathPanel->setVisible(false);
  _block = NULL;
 }
}

/*private*/ void DetectionPanel::makePathList(OBlock* block)
{
 _blockPathPanel->layout()->removeWidget(_checkBoxPanel);

 _checkBoxPanel = new QFrame();
 QVBoxLayout* checkBoxPanelLayout;
 _checkBoxPanel->setLayout(checkBoxPanelLayout = new QVBoxLayout(_checkBoxPanel/*, BoxLayout.Y_AXIS*/));
    //_checkBoxPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.black), tr("circuitPaths")));
 _checkBoxPanel->  setStyleSheet("QFrame { border: 1px solid black; }");

 _block = block;
 _pathBoxes =  QList<QCheckBox*>();
 QVector<Path*>* paths = _block->getPaths();
 for (int i=0; i<paths->size(); i++)
 {
  QString name = ((OPath*)paths->at(i))->getName();
  if (name.length()<25)
  {
   //char[] ca = new char[25];
   QString ca;
   for (int j=0; j<name.length(); j++ )
   {
    //ca[j] = name.charAt(j);
    ca.append(name.at(j));
   }
   for (int j=name.length(); j<25; j++ )
   {
    //ca[j] = ' ';
    ca.append(" ");
   }
   name = ca;
  }
  QCheckBox* box = new QCheckBox(name);
  box->setText(name);
  _pathBoxes.append(box);
  checkBoxPanelLayout->addWidget(box);
 }
 ((QVBoxLayout*)_blockPathPanel->layout())->addWidget(_checkBoxPanel,BorderLayout::South);
 _blockPathPanel->setVisible(true);
}
