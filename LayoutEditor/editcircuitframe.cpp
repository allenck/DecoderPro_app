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

/*public*/ EditCircuitFrame::EditCircuitFrame(QString title, CircuitBuilder* parent, OBlock* block, QWidget* parentWidget) : JmriJFrame(false, false, parentWidget)
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

 _block = block;
 setWindowTitle(QString(title).arg(_block->getDisplayName()));
 addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);
 _parent = parent;
 makeContentPanel();
 updateContentPanel();
}

/*private*/ void EditCircuitFrame::makeContentPanel()
{
 QWidget* contentPane = new QWidget();
 contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
    //contentPane->layout()->setSpacing(2);

//    addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            closingEvent();
//        }
//    });
 //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
 ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);
 QWidget* p = new QWidget();
 p->setLayout(new QHBoxLayout);
 p->layout()->addWidget(new QLabel(tr("Select (or deselect) all the track icons that display this OBlock track circuit")));
 contentPane->layout()->addWidget(p);
 //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
 ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

 QWidget* panel = new QWidget();
 panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(false, _blockState, tr("Circuit (OBlock) State"), false, NULL));
 _blockState->setMinimumSize( QSize(150, _blockState->getPreferredSize().height()));
 contentPane->layout()->addWidget(panel);

 panel = new QWidget();
 panel->setLayout(new QHBoxLayout);
 _blockName->setText(_block->getDisplayName());
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _blockName, tr("Circuit Name"), true, tr("Enter a name to change the user name of the OBlock for this circuit.")));
 _blockName->setMinimumSize( QSize(300, _blockName->getPreferredSize().height()));
 contentPane->layout()->addWidget(panel);

 contentPane->layout()->addWidget(MakeButtonPanel());
 //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
 ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

 p = new QWidget();
 p->setLayout(new QHBoxLayout);
 p->layout()->addWidget(new QLabel(tr("Number of Track Icons in circuit")));
 contentPane->layout()->addWidget(p);

 panel = new QWidget();
 panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
//    panel.add(Box.createHorizontalGlue());
 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _numTrackSeg, "Segments", false, NULL));
 _numTrackSeg->setMinimumSize( QSize(20, _numTrackSeg->getPreferredSize().height()));
 //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
 ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

 panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _numTurnouts, "Turnouts", false, NULL));
    _numTurnouts->setMinimumSize(QSize(20, _numTurnouts->getPreferredSize().height()));
    //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);
    contentPane->layout()->addWidget(panel);
    //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

    panel = new QWidget();
    panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
    _detectorSensorName->setMaximumSize( QSize(300, _detectorSensorName->getPreferredSize().height()));
    panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _detectorSensorName, "Detection Sensor", true, "detectorSensorName"));
    _detectorSensorName->setToolTip(tr("Enter the name of the sensor that detects occupancy for this track citcuit"));
    contentPane->layout()->addWidget(panel);

    panel = new QWidget();
    panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
    _errorSensorName->setMaximumSize( QSize(300, _errorSensorName->getPreferredSize().height()));
    panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _errorSensorName, "Error Sensor", true, "detectorErrorName"));
    _errorSensorName->setToolTip(tr("Enter the name of the sensor that indicates power problems for this track citcuit"));
    contentPane->layout()->addWidget(panel);
    //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

    contentPane->layout()->addWidget(MakePickListPanel());
    //contentPane.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

    contentPane->layout()->addWidget(MakeDoneButtonPanel());
    QWidget* border = new QWidget();
    border->setLayout(new BorderLayout(20));
    border->layout()->addWidget(contentPane);
    setCentralWidget(border);
    reSizeToFitOnScreen();
    pack();
    if (_firstInstance) {
//        setLocationRelativeTo(_parent->_editor);
        _firstInstance = false;
    } else {
        setLocation(_loc.x(), _loc.y());
        resize(_dim);
    }
    setVisible(true);
}

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
    _pickFrame = new JmriJFrame();
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

/*private*/ QWidget* EditCircuitFrame::MakeDoneButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout);//(buttonPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    QPushButton* convertButton = new QPushButton(tr("Convert Icons"));
//    convertButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _parent->convertIcons();
//            }
//    });
    connect(convertButton, SIGNAL(clicked()), _parent, SLOT(convertIcons()));
    convertButton->setToolTip(tr("Indicator Track icons.  (re-orienting or positioning may be needed)"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(convertButton->sizePolicy().hasHeightForWidth());
    convertButton->setSizePolicy(sizePolicy);

    panel->layout()->addWidget(convertButton);

    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                closingEvent();
//            }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(closingEvent()));
    doneButton->setSizePolicy(sizePolicy);
    panel->layout()->addWidget(doneButton);
    buttonPanel->layout()->addWidget(panel);

    return buttonPanel;
}
#if 0
/************************* end setup **************************/

/*private*/ void changeBlockName() {
    String name = _blockName.getText();
    if (name==NULL || name.trim().length()==0) {
        JOptionPane.showMessageDialog(this, tr("changeBlockName"),
                        tr("editCiruit"), JOptionPane.INFORMATION_MESSAGE);
        return;
    }
    _block.setUserName(name);
    // block user name change will change portal names.  Change PortalIcon names to match
    java.util.List<Positionable> list = _parent.getCircuitIcons(_block);
    if (list!=NULL) {
        for (int i=0; i<list.size(); i++) {
            if (list.get(i) instanceof PortalIcon) {
                PortalIcon icon = (PortalIcon)list.get(i);
                Portal portal = icon.getPortal();
                icon.setName(portal.getName());
                icon.setTooltip(new ToolTip(portal.getDescription(), 0, 0));
            }
        }
    }
}

/*private*/ void deleteCircuit() {
    int result = JOptionPane.showConfirmDialog(this, tr("confirmBlockDelete"),
                    tr("editCiruit"), JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE);
    if (result==JOptionPane.YES_OPTION) {
        _parent.removeBlock(_block);
        _parent.closeCircuitFrame();
        dispose();
    }
}
#endif
/*protected*/ void EditCircuitFrame::updateContentPanel()
{
    updateIconList(_parent->_editor->getSelectionGroup());
    QString name = "";
    Sensor* sensor = _block->getSensor();
    if (sensor!=NULL) {
        name = sensor->getDisplayName();
    }
    _detectorSensorName->setText(name);

    sensor = _block->getErrorSensor();
    if (sensor!=NULL) {
        name = sensor->getDisplayName();
    } else {
        name = "";
    }
    _errorSensorName->setText(name);

    int state = _block->getState();
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
}

/*private*/ Sensor* EditCircuitFrame::getSensor(QString sensorName) {
    try {
        if (sensorName!=NULL && sensorName.trimmed().length()>0) {
            return ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(sensorName);
        }
    } catch (Throwable t) {
//        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                        tr("sensorFail"), sensorName, t.toString()),
//                        tr("noSensor"), JOptionPane.INFORMATION_MESSAGE);
        QMessageBox::information(this, tr("No Detection Sensor"), tr("Sensor failed for \"%1\" due to %2.").arg(sensorName).arg(t.getMessage()));
    }
    return NULL;
}

/*protected*/ void EditCircuitFrame::closingEvent() {
    // check Sensors
    QString sensorName = _detectorSensorName->text();
    Sensor* sensor = getSensor(sensorName);
    if (sensor==NULL) {
//        JOptionPane.showMessageDialog(this, tr("noDetecterSensor"),
//                        tr("noSensor"), JOptionPane.INFORMATION_MESSAGE);
        QMessageBox::information(this, tr("No Detection Sensor"), tr("No detector Sensor specified.  This will be a Dark block and cannot be included in an interlock."));
    } else {
        try {
            _block->setSensor(sensorName);
        } catch (Throwable t) {
//            JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(tr("badSensorName"),
//                    sensorName, t.toString()),
//                    tr("noSensor"), JOptionPane.INFORMATION_MESSAGE);
            QMessageBox::information(this, tr("No Detection Sensor"),tr("\"%1\" cannot be used as a Sensor name. (%2)").arg(sensorName).arg(t.getMessage()));
        }
    }

    QString errorName = _errorSensorName->text();
    Sensor* errSensor = getSensor(errorName);
    _block->setErrorSensor(errorName);
    if (errSensor!=NULL && sensor==NULL)
    {
//        int result = JOptionPane.showConfirmDialog(this, tr("mixedSensors"),
//                        tr("noSensor"), JOptionPane.YES_NO_OPTION,
//                        JOptionPane.QUESTION_MESSAGE);
//        if (result==JOptionPane.YES_OPTION)
        int result = QMessageBox::question(this, tr("No Detection Sensor"),tr("No detector Sensor specified.  Do you want to use the error sensor for occupancy?"),QMessageBox::Yes | QMessageBox::No);
        if(result == QMessageBox::Yes)
        {
            _block->setSensor(errorName);
            _block->setErrorSensor(NULL);
            _detectorSensorName->setText(errSensor->getDisplayName());
        }
    }
    closePickList();

    _parent->checkCircuitFrame(_block);
    _loc = pos();
    _dim = size();
    //dispose();
    close();
}

/*protected*/ OBlock* EditCircuitFrame::getBlock() {
    return _block;
}

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
            if(qobject_cast<IndicatorTrackIcon*>(pos) != NULL)
            {
                segments++;
            }
           // else if (pos instanceof TurnoutIcon)
            else if(qobject_cast<TurnoutIcon*>(pos) != NULL)
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

