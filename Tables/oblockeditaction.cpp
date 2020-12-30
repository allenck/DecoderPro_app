#include "oblockeditaction.h"
#include "actionevent.h"
#include "tableframes.h"
#include "oblockmanager.h"
#include "beanitempanel.h"
#include "sensordebounceeditaction.h"
#include "signalspeedmap.h"
#include "spinnernumbermodel.h"
#include <QButtonGroup>
#include "beanedititem.h"
/**
 * Provides a tabbed beanedit panel for an OBlock object.
 *
 * @author Kevin Dickerson Copyright (C) 2011
 * @author Egbert Broerse Copyright (C) 2020
 */
///*public*/ class OBlockEditAction extends BeanEditAction<OBlock> {

    /*private*/ /*static*/ /*final*/ QString OBlockEditAction::noneText = tr("None");
    /*private*/ /*static*/ /*final*/ QString OBlockEditAction::gradualText = tr("Gradual");
    /*private*/ /*static*/ /*final*/ QString OBlockEditAction::tightText = tr("Tight");
    /*private*/ /*static*/ /*final*/ QString OBlockEditAction::severeText = tr("Severe");
    /*static*/ /*final*/ QVector<QString> OBlockEditAction::speedList = QVector<QString>();

    /*public*/ OBlockEditAction::OBlockEditAction(JActionEvent* ae) : BeanEditAction() {
        //super();
        if (ae != nullptr) {
            tabName = ((QAction*)ae->getSource())->text();//ae->getActionCommand();
        }
    }

    //@Override
    /*public*/ QString OBlockEditAction::helpTarget() {
        return "package.jmri.jmrit.beantable.OBlockTable";
    } // NOI18N

    /*public*/ void OBlockEditAction::setTablePanel(TableFrames::BlockPathJPanel* panel){
        blockPathPanel = panel;
    }

    //@Override
    /*protected*/ void OBlockEditAction::initPanels() {
        BeanEditAction::initPanels();
        sensor();
        paths();
        reporterDetails();
        physicalDetails();
    }

    //@Override
    /*public*/ QString OBlockEditAction::getBeanType() {
        return tr("OBlock");
    }

    //@Override
    /*public*/ NamedBean *OBlockEditAction::getByUserName(QString name) {
        return ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getByUserName(name);
    }

    BeanItemPanel* OBlockEditAction::sensor() {
        BeanItemPanel* basic = new BeanItemPanel();
        basic->setName(tr("Sensors"));

        sensorComboBox = new NamedBeanComboBox(InstanceManager::sensorManagerInstance(), ((Block*)bean)->getSensor(), NamedBean::DisplayOptions::DISPLAYNAME);
        sensorComboBox->setAllowNull(true);
        basic->addItem(new BeanEditItem(sensorComboBox, tr("Sensor"), tr("Set the Sensor that is used to determine the occupancy state of the Block")));

        errorSensorComboBox = new NamedBeanComboBox(InstanceManager::sensorManagerInstance(), ((Block*)bean)->getSensor(), NamedBean::DisplayOptions::DISPLAYNAME);
        errorSensorComboBox->setAllowNull(true);
        basic->addItem(new BeanEditItem(errorSensorComboBox, tr("Error Sensor"), tr("Set the Sensor that is used to report errors of the OBlock")));

        /*final*/ SensorDebounceEditAction* debounce = new SensorDebounceEditAction();
        debounce->sensorDebounce(basic);

//        sensorComboBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(sensorComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
                debounce->setBean(sensorComboBox->getSelectedItem());
                debounce->resetDebounceItems(/*e*/);
//            }
        });
#if 0
        basic->setSaveItem(new AbstractAction() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                if (sensorComboBox->getSelectedItem() == nullptr) {
                    bean->setSensor(null);
                } else {
                    bean->setSensor(sensorComboBox->getSelectedItem()->getDisplayName());
                }
                if (errorSensorComboBox->getSelectedItem() == nullptr) {
                    bean->setErrorSensor(null);
                } else {
                    bean->setErrorSensor(errorSensorComboBox->getSelectedItem()->getDisplayName());
                }
            }
        });
        basic->setResetItem(overload<AbstractAction>() {
            //@Override
            /*public*/ void actionPerformed(ActionEvent* e) {
                //From basic details
                sensorComboBox->setSelectedItem(bean->getSensor());
                errorSensorComboBox->setSelectedItem(bean->getErrorSensor());
                debounce.setBean(bean->getSensor());
                debounce.resetDebounceItems(e);
            }
        });
#endif
        basic->setSaveItem(new OBTSaveItemAction1(this));
        basic->setResetItem(  new OBTResetItemAction1(debounce,this));
        bei.append(basic);
        return basic;
    }

    BeanItemPanel* OBlockEditAction::paths() {
        BeanItemPanel* paths = new BeanItemPanel();
        QString name = tr("Paths");
        paths->setName(name);

        paths->addItem(new BeanEditItem(blockPathPanel, tr("<html>Paths<br>in OBlock<br>\"%1\"</html>").arg(bean->getDisplayName()), nullptr));
        // includes Add Path button
#if 0
        paths->setResetItem(new AbstractAction() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                //clear the table?
            }
        });
#endif
        paths->setResetItem(  new OBTResetItemAction1a(this));
        bei.append(paths);
        if (InstanceManager::getNullableDefault("OBlockManager") == nullptr) {
            setEnabled(false);
        }
        if (name == (tabName)) {
            setSelectedComponent(paths);
        }
        return paths;
    }

    BeanItemPanel* OBlockEditAction::reporterDetails() {
        BeanItemPanel* reporter = new BeanItemPanel();
        reporter->setName(tr("Reporter"));

        reporterComboBox = new NamedBeanComboBox((ReporterManager*)InstanceManager::getDefault("ReporterManager"), ((OBlock*)bean)->getReporter(), NamedBean::DisplayOptions::DISPLAYNAME);
        reporterComboBox->setAllowNull(true);

        reporter->addItem(new BeanEditItem(reporterComboBox, tr("Reporter"), tr("BlockReporterText")));

//        reporterComboBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(reporterComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
                if (reporterComboBox->getSelectedItem() != nullptr) {
                    useCurrent->setEnabled(true);
                } else {
                    useCurrent->setEnabled(false);
                }
//            }
        });

        reporter->addItem(new BeanEditItem(useCurrent, tr("Use Current"), tr("BlockUseCurrentText")));

        if (reporterComboBox->getSelectedItem() == nullptr) {
            useCurrent->setEnabled(false);
        }
#if 0
        reporter->setResetItem(new AbstractAction() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                reporterComboBox->setSelectedItem(bean->getReporter());
                useCurrent->setSelected(bean->isReportingCurrent());
            }
        });

        reporter->setSaveItem(new AbstractAction() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                bean->setReporter(reporterComboBox.getSelectedItem());
                bean->setReportingCurrent(useCurrent.isSelected());
            }
        });
#endif
        reporter->setSaveItem(new OBTSaveItemAction2(this));
        reporter->setResetItem(  new OBTResetItemAction2(this));

        bei.append(reporter);
        if (InstanceManager::getNullableDefault("ReporterManager") == nullptr) {
            setEnabled(false);
        }
        return reporter;
    }

    BeanItemPanel* OBlockEditAction::physicalDetails() {
        defaultBlockSpeedText = (tr("UseGlobal", "Global") + " " + ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());
        speedList.append(defaultBlockSpeedText);
        QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
        for (QString s : _speedMap) {
            if (!speedList.contains(s)) {
                speedList.append(s);
            }
        }
        BeanItemPanel* basic = new BeanItemPanel();
        basic->setName(tr("BlockPhysicalProperties"));

        basic->addItem(new BeanEditItem(nullptr, nullptr, tr("BlockPropertiesText")));
        lengthSpinner->setModel(new SpinnerNumberModel((0.), (0.), (1000.), (0.01)));
//        lengthSpinner->setEditor(new JSpinner::NumberEditor(lengthSpinner, "###0.00"));
        lengthSpinner->resize( JTextField(8).sizeHint());
        lengthSpinner->setValue(0.); // reset from possible previous use
        basic->addItem(new BeanEditItem(lengthSpinner, tr("BlockLengthColName"), tr("BlockLengthText")));

        QButtonGroup* rg = new QButtonGroup(this);
        rg->addButton(inch);
        rg->addButton(cm);

        JPanel* p = new JPanel(new FlowLayout());
        p->layout()->addWidget(inch);
        p->layout()->addWidget(cm);
        p->setLayout(new QVBoxLayout());//p, BoxLayout.Y_AXIS));
        inch->setChecked(true);

//        inch.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(inch, &QRadioButton::clicked, [=]{
                cm->setChecked(!inch->isChecked());
                updateLength();
//            }
        });
//        cm.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(cm, &QRadioButton::clicked, [=]{
                inch->setChecked(!cm->isChecked());
                updateLength();
//            }
        });

        basic->addItem(new BeanEditItem(p, tr("Units"), tr("Select length measurements")));
        basic->addItem(new BeanEditItem(curvatureField, tr("Curvature"), ""));
        basic->addItem(new BeanEditItem(speedField = new JComboBox/*<String>*/(speedList.toList()), tr("Speed"), tr("Set the maximum speed through the Block")));
        basic->addItem(new BeanEditItem(permissiveField, tr("BlockPermColName"), tr("BlockPermissiveText")));

        permissiveField->setChecked(((Block*)bean)->getPermissiveWorking());

        basic->setSaveItem(new OBTSaveItemAction3(this));
//        {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                QString cName = (QString) curvatureField.getSelectedItem();
//                if (cName.equals(noneText)) {
//                    bean->setCurvature(Block.NONE);
//                } else if (cName.equals(gradualText)) {
//                    bean->setCurvature(Block.GRADUAL);
//                } else if (cName.equals(tightText)) {
//                    bean->setCurvature(Block.TIGHT);
//                } else if (cName.equals(severeText)) {
//                    bean->setCurvature(Block.SEVERE);
//                }

//                QString speed = (QString) speedField.getSelectedItem();
//                try {
//                    bean->setBlockSpeed(speed);
//                } catch (JmriException ex) {
//                    JOptionPane.showMessageDialog(null, ex.getMessage() + "\n" + speed);
//                    return;
//                }
//                if (!speedList.contains(speed) && !speed.contains("Global")) {
//                    speedList.add(speed);
//                }
//                float len = 0.0f;
//                len = (Float) lengthSpinner.getValue();
//                if (inch.isSelected()) {
//                    bean->setLength(len * 25.4f);
//                } else {
//                    bean->setLength(len * 10.0f);
//                }
//                bean->setPermissiveWorking(permissiveField.isSelected());
//            }
//        });
//        basic.setResetItem(new AbstractAction() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                lengthSpinner.setValue(bean->getLengthMm());

//                if (bean->getCurvature() == Block.NONE) {
//                    curvatureField.setSelectedItem(0);
//                } else if (bean->getCurvature() == Block.GRADUAL) {
//                    curvatureField.setSelectedItem(gradualText);
//                } else if (bean->getCurvature() == Block.TIGHT) {
//                    curvatureField.setSelectedItem(tightText);
//                } else if (bean->getCurvature() == Block.SEVERE) {
//                    curvatureField.setSelectedItem(severeText);
//                }

//                QString speed = bean->getBlockSpeed();
//                if (!speedList.contains(speed)) {
//                    speedList.add(speed);
//                }

//                speedField.setEditable(true);
//                speedField.setSelectedItem(speed);
//                float len = 0.0f;
//                if (inch.isSelected()) {
//                    len = bean->getLengthIn();
//                } else {
//                    len = bean->getLengthCm();
//                }
//                lengthSpinner.setValue(len);
//                permissiveField.setSelected(bean->getPermissiveWorking());
//            }
//        });
          basic->setResetItem(new OBTResetItemAction3(this));

        bei.append(basic);
        return basic;
    }

    /*private*/ void OBlockEditAction::updateLength() {
        float len = 0.0f;
        if (inch->isChecked()) {
            len = ((Block*)bean)->getLengthIn();
        } else {
            len = ((Block*)bean)->getLengthCm();
        }
        lengthSpinner->setValue(len);
    }
