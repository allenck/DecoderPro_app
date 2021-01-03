#include "blockeditaction.h"
#include "decimalformat.h"
#include "blockmanager.h"
#include "instancemanager.h"
#include "namedbeancombobox.h"
#include <QCheckBox>
#include "beanitempanel.h"
#include "jmribeancombobox.h"
#include "signalspeedmap.h"
#include <QButtonGroup>
#include <QBoxLayout>
#include <flowlayout.h>
#include <QRadioButton>
#include "jtextfield.h"
#include "decimalformat.h"
#include "jtextarea.h"
#include "sensordebounceeditaction.h"
#include <QScrollArea>
#include "beaneditaction.h"
#include <QMessageBox>
#include "beanedititem.h"

BlockEditAction::BlockEditAction(QObject *parent) :
  BeanEditAction(parent)
{
 noneText = tr("None");
 gradualText = tr("Gradual");
 tightText = tr("Tight");
 severeText = tr("Severe");
 curveOptions = QStringList() << noneText << gradualText << tightText << severeText;
 twoDigit = new DecimalFormat("0.00");
 userNameField = new JTextField(20);
 useCurrent = new QCheckBox();
 commentField = new JTextArea(3, 30);
 commentFieldScroller = new QScrollArea(commentField);
 curvatureField = new QComboBox(/*curveOptions*/);
 curvatureField->addItems(curveOptions);
 permissiveField = new QCheckBox();
 inch = new QRadioButton(tr("Inches"));
 cm = new QRadioButton(tr("Centimeters"));
 lengthField = new JTextField(20);
}

/**
 * Provides an edit panel for a block object
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 19923 $
 */
///*public*/ class BlockEditAction extends BeanEditAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = -2188902845944347657L;

/*public*/ QString BlockEditAction::helpTarget() {
    return "package.jmri.jmrit.beantable.BlockEdit";
} //IN18N
/*static*/ /*final*/ QVector<QString> BlockEditAction::speedList =  QVector<QString>();

//@Override
/*protected*/ void BlockEditAction::initPanels() {
    BeanEditAction::initPanels();
    sensor();
    reporterDetails();
    physcialDetails();
}

/*public*/ QString BlockEditAction::getBeanType() {
    return tr("Block");
}

/*public*/ NamedBean* BlockEditAction::getByUserName(QString name) {
 return (NamedBean*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getByUserName(name);
}


BeanItemPanel* BlockEditAction::reporterDetails()
{
    BeanItemPanel* reporter = new BeanItemPanel();
    reporter->setName(tr("Reporter"));

    reporterComboBox = new NamedBeanComboBox(((ReporterManager*)InstanceManager::getDefault("ReporterManager")), ((Block*) bean)->getReporter(), NamedBean::DISPLAYNAME);
    reporterComboBox->setAllowNull(true);

    reporter->addItem(new BeanEditItem(reporterComboBox, tr("BeanNameReporter"), tr("Set the reporter used to identify trains in the block")));

//    reporterField.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (reporterField.getSelectedBean() != NULL) {
//                useCurrent.setEnabled(true);
//            } else {
//                useCurrent.setEnabled(false);
//            }
//        }
//    });
    connect(reporterComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_reporterComboBox_currentIndexChanged(QString)));

    reporter->addItem(new BeanEditItem(useCurrent, tr("BlockReporterCurrent"), tr("Use the Current Report from the reporter as the value for the block")));

    if (reporterComboBox->currentText() == "") {
        useCurrent->setEnabled(false);
    }
#if 0
    reporter->setResetItem(new AbstractAction() {
        /**
         *
         */
        /*private*/ static final long serialVersionUID = 2449970976942578601L;

        /*public*/ void actionPerformed(ActionEvent e) {
            reporterField.setSelectedBean(((Block) bean).getReporter());
            useCurrent.setSelected(((Block) bean).isReportingCurrent());
        }
    });
#endif
    reporter->setResetItem(new SetResetItemAction(this));
#if 0
    reporter.setSaveItem(new AbstractAction() {
        /**
         *
         */
        /*private*/ static final long serialVersionUID = -6560902254904220330L;

        /*public*/ void actionPerformed(ActionEvent e) {
            Block blk = (Block) bean;
            blk->setReporter((Reporter) reporterField.getSelectedBean());
            blk->setReportingCurrent(useCurrent.isSelected());
        }
    });
#endif
    reporter->setSaveItem(new SetSaveItemAction(this));
    bei.append(reporter);
    if (InstanceManager::getDefault("ReporterManager") == NULL)
    {
     setEnabled(false);
    }
    return reporter;
}

BeanItemPanel* BlockEditAction::physcialDetails() {

 defaultBlockSpeedText = (tr("UseGlobal") + " " + ((BlockManager*) InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());
    speedList.append(defaultBlockSpeedText);
    QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
    for (int i = 0; i < _speedMap.size(); i++) {
        if (!speedList.contains(_speedMap.at(i))) {
            speedList.append(_speedMap.at(i));
        }
    }
    BeanItemPanel* basic = new BeanItemPanel();
    basic->setName(tr("Physical Details"));

    basic->addItem(new BeanEditItem(NULL, NULL, tr("Use this tab to update the physical information about the block")));
    basic->addItem(new BeanEditItem(lengthField, tr("Length"), tr("Length of the block")));

//    lengthField.addKeyListener(new KeyListener() {
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            String text = lengthField.getText();

//            // ensure data valid
//            try {
//                jmri.util.IntlUtilities.floatValue(text);
//            } catch (java.text.ParseException e) {
//                String msg = java.text.MessageFormat.format(tr("ShouldBeNumber"), new Object[]{tr("BlockLengthColName")});
//                jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).showInfoMessage(tr("ErrorTitle"), msg, "Block Details", "length", false, false);
//            }
//        }

//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

    QButtonGroup* rg = new QButtonGroup();
    rg->addButton(inch);
    rg->addButton(cm);

    QWidget* p = new QWidget();
    FlowLayout* pLayout = new FlowLayout(p);
    pLayout->addWidget(inch);
    pLayout->addWidget(cm);
    //p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
    inch->setChecked(true);

    //    inch.addActionListener(new ActionListener() {
    //        /*public*/ void actionPerformed(ActionEvent e) {
    //            cm.setSelected(!inch.isSelected());
    //            updateLength();
    //        }
    //    });
    //    cm.addActionListener(new ActionListener() {
    //        /*public*/ void actionPerformed(ActionEvent e) {
    //            inch.setSelected(!cm.isSelected());
    //            updateLength();
    //        }
    //    });
    connect(inch, SIGNAL(toggled(bool)), this, SLOT(updateLength()));
    basic->addItem(new BeanEditItem(p, tr("BlockLengthUnits"), tr("BlockLengthUnitsText")));
    basic->addItem(new BeanEditItem(curvatureField, tr("Curvature"), ""));
    speedField = new QComboBox(/*speedList*/);
    speedField->addItems(speedList.toList());
    basic->addItem(new BeanEditItem(speedField, tr("Speed"), tr("BlockMaxSpeedText")));
    basic->addItem(new BeanEditItem(permissiveField, tr("Permissive"), tr("BlockPermissiveText")));

    permissiveField->setChecked(((Block*) bean)->getPermissiveWorking());

//    basic->setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        /*private*/ static final long serialVersionUID = 3999787373758196069L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Block blk = (Block) bean;
//            String cName = (String) curvatureField.getSelectedItem();
//            if (cName==(noneText)) {
//                blk->setCurvature(Block::NONE);
//            } else if (cName==(gradualText)) {
//                blk->setCurvature(Block::GRADUAL);
//            } else if (cName==(tightText)) {
//                blk->setCurvature(Block::TIGHT);
//            } else if (cName==(severeText)) {
//                blk->setCurvature(Block::SEVERE);
//            }

//            String speed = (String) speedField.getSelectedItem();
//            try {
//                blk->setBlockSpeed(speed);
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
//                return;
//            }
//            if (!speedList.contains(speed) && !speed.contains(tr("UseGlobal"))) {
//                speedList.add(speed);
//            }
//            float len = 0.0f;
//            try {
//                len = jmri.util.IntlUtilities.floatValue(lengthField.getText());
//            } catch (java.text.ParseException ex2) {
//                log.error("Error parsing length value of \"{}\"", lengthField.getText());
//            }
//            if (inch.isSelected()) {
//                blk->setLength(len * 25.4f);
//            } else {
//                blk->setLength(len * 10.0f);
//            }
//            blk->setPermissiveWorking(permissiveField.isSelected());
//        }
//    });
//    basic->setSaveItem(on_setSaveItem());

//    basic.setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        /*private*/ static final long serialVersionUID = 1875022997531442999L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Block blk = (Block) bean;
//            lengthField.setText(twoDigit.format(((Block) bean).getLengthMm()));

//            if (blk->getCurvature() == Block::NONE) {
//                curvatureField.setSelectedItem(0);
//            } else if (blk->getCurvature() == Block::GRADUAL) {
//                curvatureField.setSelectedItem(gradualText);
//            } else if (blk->getCurvature() == Block::TIGHT) {
//                curvatureField.setSelectedItem(tightText);
//            } else if (blk->getCurvature() == Block::SEVERE) {
//                curvatureField.setSelectedItem(severeText);
//            }

//            String speed = blk->getBlockSpeed();
//            if (!speedList.contains(speed)) {
//                speedList.add(speed);
//            }

//            speedField.setEditable(true);
//            speedField.setSelectedItem(speed);
//            double len = 0.0;
//            if (inch.isSelected()) {
//                len = blk->getLengthIn();
//            } else {
//                len = blk->getLengthCm();
//            }
//            lengthField.setText(twoDigit.format(len));
//            permissiveField.setSelected(((Block) bean).getPermissiveWorking());
//        }
//    });
//    basic->setResetItem(on_setResetItem());
    bei.append(basic);
    return basic;
}

void BlockEditAction::on_setSaveItem()
{
 Block* blk = (Block*) bean;
 QString cName = curvatureField->currentText();
 if (cName==(noneText))
 {
   blk->setCurvature(Block::NONE);
 } else if (cName==(gradualText))
 {
     blk->setCurvature(Block::GRADUAL);
 } else if (cName==(tightText))
 {
     blk->setCurvature(Block::TIGHT);
 } else if (cName==(severeText))
 {
     blk->setCurvature(Block::SEVERE);
 }

 QString speed =  speedField->currentText();
 try {
     blk->setBlockSpeed(speed);
 } catch (JmriException ex) {
//         JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
  QMessageBox::critical(NULL, tr("Error"), tr("Speed error"));
     return;
 }
 if (!speedList.contains(speed) && !speed.contains(tr("Use Global")))
 {
  speedList.append(speed);
 }
 float len = 0.0f;
 bool bok;
 len = lengthField->text().toFloat(&bok);
 if(!bok)
 {
  log->error(tr("Error parsing length value of \"%1\"").arg( lengthField->text()));
 }
 if (inch->isChecked())
 {
  blk->setLength(len * 25.4f);
 }
 else
 {
  blk->setLength(len * 10.0f);
 }
 blk->setPermissiveWorking(permissiveField->isChecked());
}

void BlockEditAction::on_setResetItem()
{
 Block* blk = (Block*) bean;
 lengthField->setText(twoDigit->format(((Block*) bean)->getLengthMm()));

 if (blk->getCurvature() == Block::NONE) {
     curvatureField->setCurrentIndex(0);
 } else if (blk->getCurvature() == Block::GRADUAL) {
     curvatureField->setCurrentIndex(curvatureField->findText(gradualText));
 } else if (blk->getCurvature() == Block::TIGHT) {
     curvatureField->setCurrentIndex(curvatureField->findText(tightText));
 } else if (blk->getCurvature() == Block::SEVERE) {
     curvatureField->setCurrentIndex(curvatureField->findText(severeText));
 }

 QString speed = blk->getBlockSpeed();
 if (!speedList.contains(speed)) {
     speedList.append(speed);
 }

 speedField->setEditable(true);
 speedField->setCurrentIndex(speedField->findText(speed));
 double len = 0.0;
 if (inch->isChecked()) {
     len = blk->getLengthIn();
 } else {
     len = blk->getLengthCm();
 }
 lengthField->setText(twoDigit->format(len));
 permissiveField->setChecked(((Block*) bean)->getPermissiveWorking());
}

void BlockEditAction::on_reporterComboBox_currentIndexChanged(QString s)
{
 //            if (reporterField.getSelectedBean() != NULL) {
 if(s != "")
 {
  useCurrent->setEnabled(true);
 } else {
     useCurrent->setEnabled(false);
 }

}

/*private*/ void BlockEditAction::updateLength() {
    double len = 0.0;
    Block* blk = (Block*) bean;
    if (inch->isChecked()) {
        len = blk->getLengthIn();
    } else {
        len = blk->getLengthCm();
    }
    lengthField->setText(twoDigit->format(len));
}


BeanItemPanel* BlockEditAction::sensor() {

    BeanItemPanel* basic = new BeanItemPanel();
    basic->setName(tr("Sensor"));

    sensorComboBox = new NamedBeanComboBox(InstanceManager::sensorManagerInstance(), ((Block*) bean)->getSensor(), NamedBean::DISPLAYNAME);
    sensorComboBox->setAllowNull(true);
    basic->addItem(new BeanEditItem(sensorComboBox, tr("Sensor"), tr("Set the sensor that is used to determine the occupancy state of the block")));

    /*final*/ SensorDebounceEditAction* debounce = new SensorDebounceEditAction();
    //debounce.setBean(bean);
    debounce->sensorDebounce(basic);

//    sensorField.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            debounce.setBean(sensorField.getSelectedBean());
//            debounce.resetDebounceItems(e);
//        }
//    });

//    basic.setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        /*private*/ static final long serialVersionUID = 6849518499144179541L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Block blk = (Block) bean;
//            jmri.jmrit.display.layoutEditor.LayoutBlock lBlk = InstanceManager.getDefault(jmri.jmrit.display.layoutEditor.LayoutBlockManager.class).getLayoutBlock(blk);
//            //If the block is related to a layoutblock then set the sensor details there and allow that to propergate the changes down.
//            if (lBlk != NULL) {
//                lBlk.validateSensor(sensorField.getSelectedDisplayName(), NULL);
//            } else {
//                blk->setSensor(sensorField.getSelectedDisplayName());
//            }
//            debounce.saveDebounceItems(e);
//        }
//    });

//    basic.setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        /*private*/ static final long serialVersionUID = 1648534584189754888L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Block blk = (Block) bean;
//            //From basic details
//            sensorField.setSelectedBean(blk->getSensor());
//            debounce.setBean(blk->getSensor());
//            debounce.resetDebounceItems(e);
//        }
//    });

    bei.append(basic);
    return basic;
}

