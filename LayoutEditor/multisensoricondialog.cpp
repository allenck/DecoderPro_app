#include "multisensoricondialog.h"
#include "loggerfactory.h"
#include "multisensoritempanel.h"
#include "flowlayout.h"
#include "imageindexeditor.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include "namedicon.h"

/**
 * Icons may be added or deleted from a family.
 *
 * @author Pete Cressman Copyright (c) 2010
 */
// /*public*/ class MultiSensorIconDialog extends IconDialog {

/**
 * Constructor for existing family to change icons, add/delete icons, or to
 * delete the family.
 */
/*public*/ MultiSensorIconDialog::MultiSensorIconDialog(QString type, QString family, FamilyItemPanel* parent,
        QMap<QString, NamedIcon*>* iconMap) : IconDialog(type, family, parent, iconMap)
{
    //super(type, family, parent, iconMap);
}

/*protected*/ QString MultiSensorIconDialog::getIconName() {
    return MultiSensorItemPanel::POSITION[_iconMap->size() - 3];
}

/**
 * Add/delete icon. For Multisensor, it adds another sensor position.
 */
//@Override
/*protected*/ void MultiSensorIconDialog::makeAddIconButtonPanel(QWidget* buttonPanel, QString addTip, QString deleteTip) {
    QWidget* panel2 = new QWidget();
    //panel2.setLayout(new FlowLayout());
    FlowLayout* panel2Layout = new FlowLayout(panel2);
    QPushButton* addSensor = new QPushButton(tr("Add Icon"));
//    addSensor.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (addNewIcon(getIconName())) {
//                InstanceManager.getDefault(ImageIndexEditor.class).indexChanged(true);
//                JPanel p = (JPanel) (getContentPane().getComponent(0));
//                p.remove(_iconPanel); // OK to replace on a Dialog
//                _iconPanel = makeIconPanel(_iconMap);
//                p.add(_iconPanel, 1);
//                pack();
//            }
//        }
//    });
    connect(addSensor, SIGNAL(clicked(bool)), this, SLOT(onAddSensor_clicked()));
    addSensor->setToolTip(addTip);
    panel2Layout->addWidget(addSensor);

    QPushButton* deleteSensor = new QPushButton(tr("Delete Icon"));
//    deleteSensor.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (deleteIcon()) {
//                InstanceManager.getDefault(ImageIndexEditor.class).indexChanged(true);
//                JPanel p = (JPanel) (getContentPane().getComponent(0));
//                p.remove(_iconPanel); // OK to replace on a Dialog
//                _iconPanel = makeIconPanel(_iconMap);
//                p.add(_iconPanel, 1);
//                pack();
//            }
//        }
//    });
    connect(deleteSensor, SIGNAL(clicked(bool)), this, SLOT(onDeleteSensor_clicked()));
    deleteSensor->setToolTip(deleteTip);
    panel2Layout->addWidget(deleteSensor);
    buttonPanel->layout()->addWidget(panel2);
}

void MultiSensorIconDialog::onAddSensor_clicked()
{
 if (addNewIcon(getIconName())) {
     ((ImageIndexEditor*)InstanceManager::getDefault("ImageIndexEditor"))->indexChanged(true);
     QWidget* p = (QWidget*) getContentPane()->children().at(0);//(getContentPane().getComponent(0));
     //p->layout()->removeWidget(_iconPanel); // OK to replace on a Dialog
     QObjectList ol = p->layout()->children();
     foreach (QObject* obj, ol) {
      if(qobject_cast<QWidget*>(obj))
       p->layout()->removeWidget(qobject_cast<QWidget*>(obj));
     }
     makeIconPanel(_iconMap, _iconEditPanel);
//     p->layout()->addWidget(_iconPanel/*, 1*/);
     pack();
 }

}

void MultiSensorIconDialog::onDeleteSensor_clicked()
{
 if (deleteIcon()) {
     ((ImageIndexEditor*)InstanceManager::getDefault("ImageIndexEditor"))->indexChanged(true);
     QWidget* p = (QWidget*) (getContentPane()->children().at(0));
//     p->layout()->removeWidget(_iconPanel); // OK to replace on a Dialog
     QObjectList ol = p->layout()->children();
     foreach (QObject* obj, ol) {
      if(qobject_cast<QWidget*>(obj))
       p->layout()->removeWidget(qobject_cast<QWidget*>(obj));
     }
     makeIconPanel(_iconMap, _iconEditPanel);
//     p->layout()->addWidget(_iconPanel/*, 1*/);
     pack();
 }

}
//@Override
/*protected*/ bool MultiSensorIconDialog::doDoneAction() {
    MultiSensorItemPanel* parent = (MultiSensorItemPanel*) _parent;
    if (_iconMap->size() != parent->_currentIconMap->size()) {
        parent->setSelections();
    }
    return IconDialog::doDoneAction();
}

/**
 * Action item for makeAddIconButtonPanel.
 */
/*protected*/ bool MultiSensorIconDialog::addNewIcon(QString name) {
    if (log->isDebugEnabled()) {
        log->debug("addNewIcon Action: iconMap.size()= " + _iconMap->size());
    }
    if (name == NULL || name.length() == 0) {
        JOptionPane::showMessageDialog(_parent->_paletteFrame, tr("Please enter a name for the Icon:"),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    } else if (_iconMap->value(name) != NULL) {
        JOptionPane::showMessageDialog(_parent->_paletteFrame,
                tr("Another icon is named %1.").arg(name),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    }
    QString fileName = "resources/icons/misc/X-red.gif";
    NamedIcon* icon = new NamedIcon(fileName, fileName);
    _iconMap->insert(name, icon);
    return true;
}

/**
 * Action item for makeAddIconButtonPanel.
 */
/*protected*/ bool MultiSensorIconDialog::deleteIcon() {
    if (log->isDebugEnabled()) {
        log->debug("deleteSensor Action: iconMap.size()= " + _iconMap->size());
    }
    if (_iconMap->size() < 4) {
        return false;
    }
    QString name = MultiSensorItemPanel::POSITION[_iconMap->size() - 4];
    _iconMap->remove(name);
    return true;
}

/*private*/ /*final*/ /*static*/ Logger* MultiSensorIconDialog::log = LoggerFactory::getLogger("MultiSensorIconDialog");
