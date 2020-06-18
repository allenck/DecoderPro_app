#include "editcircuitframe.h"
#include "oblock.h"
#include "circuitbuilder.h"
#include "jtextfield.h"
#include <QBoxLayout>
#include <QLabel>
#include "borderlayout.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QSizePolicy>
#include "pickpanel.h"
#include "controlpaneleditor.h"
#include "itempalette.h"
#include "picklistmodel.h"
#include "turnouticon.h"
#include "indicatortrackicon.h"
#include "proxysensormanager.h"
#include "sensor.h"
#include "instancemanager.h"
#include "QMessageBox"
#include "lengthpanel.h"
#include "openpicklistbutton.h"
#include "joptionpane.h"
#include "box.h"
#include "oblockmanager.h"
#include "portalicon.h"
#include "portal.h"
#include "indicatortrack.h"


//EditCircuitFrame::EditCircuitFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2011
 *
 */

// /*public*/ class EditCircuitFrame extends jmri.util.JmriJFrame {

//static java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;
/*static*/ int EditCircuitFrame::STRUT_SIZE = 10;
/*static*/ bool EditCircuitFrame::_firstInstance = true;
/*static*/ QPoint EditCircuitFrame::_loc  = QPoint();
/*static*/ QSize EditCircuitFrame::_dim = QSize(200,500);

/*public*/ EditCircuitFrame::EditCircuitFrame(QString title, CircuitBuilder* parent, OBlock* block)
 : EditFrame(title, parent, block)
{
 _blockName = new JTextField(5);
 _detectorSensorName = new JTextField(5);
 _errorSensorName = new JTextField(5);
 _blockState  = new JTextField(10);
 _numTrackSeg = new JTextField(2);
 _numTurnouts = new JTextField(2);
 QFont font;
 font.setPointSize(8);
 setFont(font);
 log = new Logger("EditCircuitFrame");
 _pickFrame = NULL;
 _firstInstance = true;

 initContents(); // finish setting up EditFrame content

 _block = block;
 _create = (block == nullptr);

 updateContentPanel(_create);
 _homeBlock->addPropertyChangeListener("deleted", (PropertyChangeListener*)this);
 pack();
}

/*private*/ JPanel *EditCircuitFrame::makeContentPanel()
{
 JPanel* contentPane = new JPanel();
 contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
 _blockName = new JTextField();
 _detectorSensorName = new JTextField();
 _errorSensorName = new JTextField();
 _blockState = new JTextField();
 _numTrackSeg = new JTextField();
 _numTurnouts = new JTextField();
 JPanel* p = new JPanel(new QVBoxLayout());

 p->layout()->addWidget(new JLabel(tr("Select (or deselect) all the track icons that display this OBlock track circuit")));
 contentPane->layout()->addWidget(p);
 contentPane->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

 JPanel* panel = new JPanel(new QVBoxLayout());
 // panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(false, _blockState, "Circuit (OBlock) State:", false, QString()));
 QSize d = _blockState->getPreferredSize();
 _blockState->resize(QSize(150, _blockState->getPreferredSize().height()));
 contentPane->layout()->addWidget(panel);

 _namePanel = new JPanel();
 _namePanel->setLayout(new QVBoxLayout());//_namePanel, BoxLayout.Y_AXIS));
 contentPane->layout()->addWidget(_namePanel);

 panel = new JPanel();
 panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
 _buttonPanel = new JPanel();
 _buttonPanel->setLayout(new FlowLayout());
 panel->layout()->addWidget(_buttonPanel);
 contentPane->layout()->addWidget(panel);

 contentPane->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
 p = new JPanel(new FlowLayout());
 p->layout()->addWidget(new JLabel(tr("Number of Track Icons in circuit:")));
 contentPane->layout()->addWidget(p);

 panel = new JPanel(new QVBoxLayout());
 // panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
 panel->layout()->addWidget(Box::createHorizontalGlue());
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
         false, _numTrackSeg, "Segments", false, nullptr));
 //_numTrackSeg->resize(QSize(20, _numTrackSeg->getPreferredSize().height()));
 panel->layout()->addWidget(Box::createHorizontalStrut(STRUT_SIZE));

 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
         false, _numTurnouts, "Turnouts:", false, nullptr));
 //_numTurnouts->resize(QSize(20, _numTurnouts->getPreferredSize().height()));
 panel->layout()->addWidget(Box::createHorizontalStrut(STRUT_SIZE));
 contentPane->layout()->addWidget(panel);
 contentPane->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

 panel = new JPanel(new QVBoxLayout());
 // panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
 //_detectorSensorName->resize(QSize(300, _detectorSensorName->getPreferredSize().height()));
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
         false, _detectorSensorName, tr("Detection Sensor"), true, "Enter the name of the sensor that detects occupancy for this track circuit"));
 _detectorSensorName->setToolTip(tr("Enter the name of the sensor that detects occupancy for this track circuit"));
 contentPane->layout()->addWidget(panel);

 panel = new JPanel(new QHBoxLayout());
 // panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
 //_errorSensorName->resize(QSize(300, _errorSensorName->getPreferredSize().height()));
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
         false, _errorSensorName, tr("Error Sensor"), true, "Enter the name of the sensor that indicates power problems for this track circuit"));
 _errorSensorName->setToolTip(tr("Enter the name of the sensor that indicates power problems for this track circuit"));
 contentPane->layout()->addWidget(panel);

 QStringList blurbLines = { tr("Drag name of a sensor that can detect occupancy to the \"%1\" field.").arg(tr("Detection Sensor")),
                         tr("Drag name of a sensor to show an error condition to the \"%1\" field.").arg(tr("Error Sensor"))};
 _pickTable = new OpenPickListButton/*<Sensor>*/(blurbLines, PickListModel::sensorPickModelInstance(), this);
 contentPane->layout()->addWidget(_pickTable->getButtonPanel());
 contentPane->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

 _lengthPanel = new LengthPanel(_homeBlock, "Block Length:");
 _lengthPanel->changeUnits();
 _lengthPanel->setLength(_homeBlock->getLengthMm());
 contentPane->layout()->addWidget(_lengthPanel);
 contentPane->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

 contentPane->layout()->addWidget(makeDoneButtonPanel());
 return contentPane;
}

#if 0
/*private*/ QWidget* EditCircuitFrame::MakePickListPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout); //(buttonPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    _openPicklistButton = new QPushButton(tr("Open Sensor Picklist"));
//    _openPicklistButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_pickFrame==NULL) {
//                    openPickList();
//                } else {
//                    closePickList();
//                }
//            }
//    });
    connect(_openPicklistButton, SIGNAL(clicked()), this, SLOT(openPickListButton_clicked()));
    _openPicklistButton->setToolTip(tr("The pick list table displays a choice of sensors to do the detection"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_openPicklistButton->sizePolicy().hasHeightForWidth());
    _openPicklistButton->setSizePolicy(sizePolicy);
    panel->layout()->addWidget(_openPicklistButton);
    panel->setToolTip(tr("The pick list table displays a choice of sensors to do the detection"));

    buttonPanel->layout()->addWidget(panel);
    return buttonPanel;
}
void EditCircuitFrame::openPickListButton_clicked()
{
 if (_pickFrame==NULL) {
    openPickList();
 } else {
    closePickList();
 }
}

void EditCircuitFrame::openPickList() {
    _pickFrame = new JmriJFrameX("EditCircuit");
    QWidget* content = new QWidget();
    content->setLayout(new QVBoxLayout(content/*, BoxLayout.Y_AXIS*/));

    QWidget* blurb = new QWidget();
    blurb->setLayout(new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
    //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
    ((QBoxLayout*)blurb->layout())->addStrut(STRUT_SIZE);
    blurb->layout()->addWidget(new QLabel(tr("Drag name of device (OBlock or Sensor) to Occupancy Detector field.")));
    blurb->layout()->addWidget(new QLabel(tr("Drag name of sensor that can detect power to Error Sensor field.")));
    ((QBoxLayout*)blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout);
    panel->layout()->addWidget(blurb);
    content->layout()->addWidget(panel);
    QList<PickListModel*> models = QList<PickListModel*>() << PickListModel::sensorPickModelInstance();
    content->layout()->addWidget(new PickPanel(models,this));

    //_pickFrame->setContentPane(content);;
    _pickFrame->setCentralWidget(content);
//    _pickFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                closePickList();
//            }
//        });
//    _pickFrame->setLocationRelativeTo(this);
//    _pickFrame->toFront();
    _pickFrame->setVisible(true);
    _pickFrame->reSizeToFitOnScreen();
    _pickFrame->pack();
    _openPicklistButton->setText(tr("Close Picklist"));
}

void EditCircuitFrame::closePickList() {
    if (_pickFrame!=NULL) {
        _pickFrame->close();
        _pickFrame = NULL;
        _openPicklistButton->setText(tr("Open Sensor Picklist"));
    }
}

/*private*/ QWidget* EditCircuitFrame::MakeButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout);//(buttonPanel/*, BoxLayout.Y_AXIS)*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    QPushButton* changeButton = new QPushButton(tr("Change Name"));
//    changeButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                changeBlockName();
//            }
//    });
    changeButton->setToolTip(tr("Enter another name to change the name of a selection in the above list."));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(changeButton->sizePolicy().hasHeightForWidth());
    changeButton->setSizePolicy(sizePolicy);
    panel->layout()->addWidget(changeButton);


    QPushButton* deleteButton = new QPushButton(tr("Delete OBlock Circuit"));
//    deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                deleteCircuit();
//             }
//    });
    deleteButton->setToolTip(tr("Delete this track circuit but keep its icons, if any."));
    deleteButton->setSizePolicy(sizePolicy);
    panel->layout()->addWidget(deleteButton);
    buttonPanel->layout()->addWidget(panel);

    return buttonPanel;
}
#endif
/*private*/ JPanel* EditCircuitFrame::makeCreateBlockPanel() {
   _systemName = new JTextField();
   _systemName->setText(_homeBlock->getSystemName());
   _blockName->setText(_homeBlock->getUserName());
   JPanel* panel = new JPanel();
   panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
   panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
           false, _systemName, tr("System Name:"), true, "Enter a name to change the User Name of the OBlock for this Circuit."));
   _systemName->resize(QSize(300, _systemName->getPreferredSize().height()));
   panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
           false, _blockName, tr("Circuit Name:"), true, "Enter a name to change the User Name of the OBlock for this Circuit."));
   _blockName->resize(QSize(300, _blockName->getPreferredSize().height()));

   JPanel* buttonPanel = new JPanel();
   buttonPanel->setLayout(new FlowLayout());
   QPushButton* createButton = new QPushButton(tr("Create"));
   //createButton.addActionListener((ActionEvent a) -> {
   connect(createButton, &QPushButton::clicked, [=]{
       createBlock();
   });
   createButton->setToolTip(tr("Create an OBlock track circuit"));
   buttonPanel->layout()->addWidget(createButton);

   panel->layout()->addWidget(buttonPanel);
   panel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
   return panel;
}

/*private*/ JPanel* EditCircuitFrame::makeEditBlockPanel() {
   _blockName->setText(_homeBlock->getUserName());
   JPanel* panel = new JPanel();
   panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
   panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
           false, _blockName, "Circuit Name:", true, "Enter a name to change the User Name of the OBlock for this Circuit."));
   _blockName->resize(QSize(300, _blockName->sizeHint().height()));

   JPanel* buttonPanel = new JPanel();
   buttonPanel->setLayout(new FlowLayout());

   QPushButton* changeButton = new QPushButton(tr("Change Name"));
   //changeButton.addActionListener((ActionEvent a) -> {
   connect(changeButton, &QPushButton::clicked, [=]{
       changeBlockName();
   });
   changeButton->setToolTip(tr("Enter another name to change the name of a selection in the above list."));
   buttonPanel->layout()->addWidget(changeButton);

   QPushButton* deleteButton = new QPushButton(tr("Delete"));
   //deleteButton.addActionListener((ActionEvent a) -> {
   connect(deleteButton, &QPushButton::clicked, [=]{
       deleteCircuit();
   });
   deleteButton->setToolTip(tr("Delete this track circuit but keep its icons, if any."));
   buttonPanel->layout()->addWidget(deleteButton);

   panel->layout()->addWidget(buttonPanel);
   panel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
   return panel;
}

/*private*/ QWidget* EditCircuitFrame::MakeDoneButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout);//(buttonPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    QPushButton* convertButton = new QPushButton(tr("Convert Icons"));
//    convertButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
    connect(convertButton, &QPushButton::clicked, [=]{
     convertIcons();
//            }
    });
    convertButton->setToolTip(tr("Indicator Track icons.  (re-orienting or positioning may be needed)"));
    panel->layout()->addWidget(convertButton);

    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
    connect(doneButton, &QPushButton::clicked, [=]{
     if (_create) {
         closeCreate();
     } else {
         closingEvent(false);
     }
     //            }
    });
    panel->layout()->addWidget(doneButton);
    buttonPanel->layout()->addWidget(panel);

    return buttonPanel;
}

/*private*/ void EditCircuitFrame::convertIcons() {
    _parent->setIconGroup(_homeBlock);
    _parent->queryConvertTrackIcons(_homeBlock, "PortalOrPath");
    this->toFront();
}
/************************* end setup **************************/
/*private*/ void EditCircuitFrame::createBlock() {
       QString userName = _blockName->text().trimmed();
       QString systemName = _systemName->text().trimmed();
       OBlockManager* mgr = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
       QString  sb;// = new StringBuilder ();
       if (userName.length() > 0) {
            OBlock* block = (OBlock*)mgr->getByUserName(userName);
           if (block != nullptr) {
               sb.append(tr("\"%1\" is a duplicate name for circuit %2.").arg(userName).arg(block->getSystemName()));
               sb.append("\n");
           }
       }
       if (!mgr->isValidSystemNameFormat(systemName)) {
           sb.append(tr("OBlock System Name must begin with \"OB\" with at least 3 characters."));
           sb.append("\n");
       } else {
           OBlock* block = (OBlock*)mgr->getBySystemName(systemName);
           if (block != nullptr) {
               sb.append(tr("\"%1\" is a duplicate name for circuit %2.").arg(systemName).arg(block->getUserName()));
               sb.append("\n");
           }
       }
       if (sb.length() > 0) {
           JOptionPane::showMessageDialog(this, sb,
                   tr("Edit Ciruit"), JOptionPane::INFORMATION_MESSAGE);
           _systemName->setText(_homeBlock->getSystemName());
           return;
       }
       _homeBlock = mgr->createNewOBlock(systemName, userName);
       updateContentPanel(false);
   }

/*private*/ void EditCircuitFrame::changeBlockName() {
 QString name = _blockName->text().trimmed();
 QString msg = "";
 if (name.length() == 0) {
     msg = tr("Enter a name to change the User Name of the OBlock for this Circuit.");
 } else {
     OBlock* block = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getByUserName(name);
     if (block != nullptr) {
         msg = tr("\"%1\" is a duplicate name for circuit %2.").arg(name).arg(block->getDisplayName(NamedBean::DisplayOptions::QUOTED_USERNAME_SYSTEMNAME));
     }
 }
 if (msg != nullptr) {
     JOptionPane::showMessageDialog(this, msg,
             tr("Edit Ciruit"), JOptionPane::INFORMATION_MESSAGE);
     return;

 }
 _homeBlock->setUserName(name);
 // block user name change will change portal names.  Change PortalIcon names to match
 for (Positionable* p : *_parent->getCircuitIcons(_homeBlock)) {
     if (qobject_cast<PortalIcon*>(p->self())) {
         PortalIcon* icon = (PortalIcon*)p->self();
         Portal* portal = icon->getPortal();
         icon->setName(portal->getName());
         icon->setToolTip(/*new ToolTip(*/portal->getDescription()/*, 0, 0)*/);
     }
 }
}

/*private*/ void EditCircuitFrame::deleteCircuit() {
 int result = JOptionPane::showConfirmDialog(this, tr("Are you sure you want to delete the circuit and all its paths and all its portals?"),
              tr("Edit Ciruit"), JOptionPane::YES_NO_OPTION,
              JOptionPane::QUESTION_MESSAGE);
      if (result == JOptionPane::YES_OPTION) {
          _parent->removeBlock(_homeBlock);
          EditFrame::closingEvent(true, "");   // No Messages, just close
      }
}

/*protected*/ void EditCircuitFrame::updateContentPanel(bool create)
{
    updateIconList(_parent->_editor->getSelectionGroup());
    QString name = "";
    Sensor* sensor = _homeBlock->getSensor();
    if (sensor!=NULL) {
        name = sensor->getDisplayName();
    }
    _detectorSensorName->setText(name);

    sensor = _homeBlock->getErrorSensor();
    if (sensor!=NULL) {
        name = sensor->getDisplayName();
    } else {
        name = "";
    }
    _errorSensorName->setText(name);

    int state = _homeBlock->getState();
    QString stateText;// = new StringBuffer();
    if ((state & OBlock::UNKNOWN) > 0) {
        stateText.append("Unknown ");
    }
    if ((state & OBlock::OCCUPIED) > 0) {
        stateText.append("Occupied ");
    }
    if ((state & OBlock::UNOCCUPIED) > 0) {
        stateText.append("Unoccupied ");
    }
    if ((state & OBlock::INCONSISTENT) > 0) {
        stateText.append("Inconsistent ");
    }
    if ((state & OBlock::ALLOCATED) > 0) {
        stateText.append("Allocated ");
    }
    if ((state & OBlock::RUNNING) > 0) {
        stateText.append("Positioned ");
    }
    if ((state & OBlock::OUT_OF_SERVICE) > 0) {
        stateText.append("OutOf Service ");
    }
    if ((state & OBlock::DARK) > 0) {
        stateText.append("Dark ");
    }
    if ((state & OBlock::TRACK_ERROR) > 0) {
        stateText.append("TrackError ");
    }
    if (state==0) {
        stateText.append("Not Initialized");
    }
    if (log->isDebugEnabled()) log->debug("updateContentPanel: state= "+stateText);
    _blockState->setText(stateText);

    JPanel* panel;
    if (create) {
        panel = makeCreateBlockPanel();
    } else {
        panel = makeEditBlockPanel();
        _create = false;
    }
    _namePanel->removeAll();
    _namePanel->setLayout(new QVBoxLayout());
    _namePanel->layout()->addWidget(panel);
    _namePanel->update();
    pack();
}

/*private*/ void EditCircuitFrame::closeCreate() {
    QString  sb;// = new StringBuilder ();
    QString sysName = _homeBlock->getSystemName();
    OBlock* block = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysName);
    if (block == nullptr) {
        // get rid of icon selections
        for (Positionable* pos : *_parent->getCircuitIcons(_homeBlock)) {
            if (qobject_cast< IndicatorTrack*>(pos->self())) {
                ((IndicatorTrack*) pos)->setOccBlockHandle(nullptr);
            }
        }
        _parent->_editor->getSelectionGroup()->clear();
        sb.append( tr("OBlock circuit \"%1\" has not been created.").arg(_systemName->text().trimmed()));
        EditFrame::closingEvent(false, sb);
        if (_pickTable != nullptr) {
            _pickTable->closePickList();
        }
    } else {
        closingEvent(false);
    }
}

///*private*/ Sensor* EditCircuitFrame::getSensor(QString sensorName) {
//    try {
//        if (sensorName!=NULL && sensorName.trimmed().length()>0) {
//            return ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(sensorName);
//        }
//    } catch (Throwable t) {
////        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
////                        tr("sensorFail"), sensorName, t.toString()),
////                        tr("noSensor"), JOptionPane.INFORMATION_MESSAGE);
//        QMessageBox::information(this, tr("No Detection Sensor"), tr("Sensor failed for \"%1\" due to %2.").arg(sensorName).arg(t.getMessage()));
//    }
//    return NULL;
//}

/*protected*/ void EditCircuitFrame::closingEvent(bool close) {
 QString sb;// = new StringBuffer();
 QString msg = checkForSensors();
 if (msg != "") {
     sb.append(msg);
     sb.append("\n");
 }
 QString name = _blockName->text().trimmed();
 if (name.length() == 0) {
     msg = tr("A non-blank user name is recommended.");
     if (msg != "") {
         sb.append(msg);
         sb.append("\n");
     }
 } else if (name !=(_homeBlock->getUserName())) {
     msg = tr("User name \"%1\" for the circuit %2has not been saved.").arg(name).arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_USERNAME_SYSTEMNAME));
     if (msg != "null") {
         sb.append(msg);
         sb.append("\n");
     }
 }
 _parent->setIconGroup(_homeBlock);
#if 0
 msg = _parent->checkForTrackIcons(_homeBlock, "PortalOrPath");
 if (msg.length() > 0) {
     sb.append(msg);
     sb.append("\n");
 }
#endif
 if (_lengthPanel->getLength() <= 0.001) {
     msg = tr("Block circuits should have a default length to insure its paths have lengths.");
     if (msg != "") {
         sb.append(msg);
         sb.append("\n");
     }
 } else {
     _homeBlock->setLength(_lengthPanel->getLength());
 }

 EditFrame::closingEvent(close, sb);
 if (_pickTable != nullptr) {
     _pickTable->closePickList();
 }
}

/*private*/ QString EditCircuitFrame::checkForSensors() {
    QString name = _detectorSensorName->text();
    QString errName = _errorSensorName->text();
    if (!_homeBlock->setSensor(name)) {
       return tr("\"%1\" is not a valid Sensor name.").arg(name);
    }
    if (errName.length() > 2) {
        if (_homeBlock->getSensor() == nullptr) {
            int result = JOptionPane::showConfirmDialog(this, tr("No detector Sensor specified. Do you want to use the Error Sensor for occupancy::"),
                    tr("No Detection Sensor"), JOptionPane::YES_NO_OPTION,
                    JOptionPane::QUESTION_MESSAGE);
            if (result == JOptionPane::YES_OPTION) {
                if (!_homeBlock->setSensor(errName)) {
                    return tr("\"%1\" is not a valid Sensor name.").arg(errName);
                } else {
                    _homeBlock->setErrorSensor(nullptr);
                    _detectorSensorName->setText(_homeBlock->getSensor()->getDisplayName());
                    _errorSensorName->setText("");
                }
            } else {
                if (!_homeBlock->setErrorSensor(errName)) {
                    return tr("\"%1\" is not a valid Sensor name.").arg(errName);
                }
            }
        } else {
            if (!_homeBlock->setErrorSensor(errName)) {
                return tr("\"%1\" is not a valid Sensor name.").arg(errName);
            }
        }
    } else if (errName.trimmed().length() == 0){ {
        _homeBlock->setErrorSensor(nullptr);
    }

    }
    Sensor* sensor = _homeBlock->getSensor();
    if (sensor == nullptr) {
        return tr("No detector Sensor specified. This will be a Dark block and cannot be included in an interlock.");
    } else if (sensor->equals(_homeBlock->getErrorSensor())) {
        _homeBlock->setErrorSensor(nullptr);
        _errorSensorName->setText("");
        return tr("Duplicate track error sensor %1removed.").arg(
                sensor->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME));
    }
    return nullptr;
}

///*protected*/ OBlock* EditCircuitFrame::getBlock() {
//    return _block;
//}



/*protected*/ void EditCircuitFrame::updateIconList(QList<Positionable*>* icons) {
    //if (log.isDebugEnabled()) log.debug(
    int segments = 0;
    int turnouts = 0;
    if (icons!=NULL) {
        if (log->isDebugEnabled()) log->debug("updateIconList: icons.size()= "+QString::number(icons->size()));
        for (int i=0; i<icons->size(); i++) {
            Positionable* pos = icons->at(i);
            //if (pos instanceof IndicatorTurnoutIcon)
//            if(qobject_cast<IndicatorTurnoutIcon*>(pos) != NULL)
//            {
//                turnouts++;
//            }
//            else
            //else if (pos instanceof IndicatorTrackIcon )
            if(qobject_cast<IndicatorTrackIcon*>(pos->self()) != NULL)
            {
                segments++;
            }
           // else if (pos instanceof TurnoutIcon)
            else if(qobject_cast<TurnoutIcon*>(pos->self()) != NULL)
            {
                turnouts++;
            } else {
                segments++;
            }
        }
    }
    _numTrackSeg->setText(QString::number(segments));
    _numTurnouts->setText(QString::number(turnouts));
}

//@Override
/*public*/ void EditCircuitFrame::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("deleted")) {
        EditFrame::closingEvent(true, "");   // No Messages, just close
    }
}


/*public*/ QString EditCircuitFrame::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.EditCircuitFrame";
}
