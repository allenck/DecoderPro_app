#include "treepanel.h"
#include "usbtreemodel0.h"
#include "jtree.h"
#include <QVBoxLayout>
#include <QSplitter>
#include "box.h"
#include "jseparator.h"
#include <QLabel>
#include <QCheckBox>
#include "jtextfield.h"
#include "usbnode.h"
#include "propertychangeevent.h"
#include "usbcomponent.h"
#include "vptr.h"
#include "controller.h"
#include "swingpropertychangesupport.h"

//TreePanel::TreePanel(QWidget *parent) : QWidget(parent)
//{

//}
/**
 * Create a QWidget* containing a tree of JInput sources.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Bob Jacobsen Copyright 2008
  */
// /*public*/ class TreePanel extends QWidget* {
namespace Usb
{
/*public*/ TreePanel::TreePanel(QWidget *parent) : QWidget(parent) {

  currentNode = NULL;
  controllerName = new QLabel();
  controllerType = new QLabel();
  componentName = new QLabel();
  componentId = new QLabel();
  componentAnalog = new QLabel();
  componentRelative = new QLabel();
  componentValue = new QLabel();
  sensorBox = new QCheckBox("Copy to JMRI Sensor  ");
  sensorName = new JTextField(25);
  memoryBox = new QCheckBox("Copy to JMRI Memory  ");
  memoryName = new JTextField(25);
  dTree = new JTree();
  log = new Logger("TreePanel");

    //super(true);

    // create basic GUI
//    dTree = new JTree(TreeModel::instance());
    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout()); //new BoxLayout(this, BoxLayout.Y_AXIS));

    // build the main GUI
    //JScrollPane treePanel = new JScrollPane(dTree);
    QWidget* nodePanel = new QWidget();
    //add(new javax.swing.JSplitPane(javax.swing.JSplitPane.HORIZONTAL_SPLIT, treePanel, nodePanel));
    QSplitter* splitter;
    thisLayout->addWidget(splitter = new QSplitter());
    splitter->addWidget(dTree);
    splitter->addWidget(nodePanel);
    // configure the tree
//    dTree->setRootVisible(false);
    dTree->setShowsRootHandles(true);
    //dTree.setScrollsOnExpand(true);
    dTree->setExpandsSelectedPaths(true);
#if 0
    dTree->getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.SINGLE_TREE_SELECTION);

    dTree.addTreeSelectionListener(new TreeSelectionListener() {
        @Override
        /*public*/ void valueChanged(TreeSelectionEvent e) {
            if (!dTree.isSelectionEmpty() && dTree.getSelectionPath() != NULL) {
                // node has been selected
                currentNode = getSelectedElement();
                update();
            } else {
                currentNode = NULL;
                // no node selected, clear
                 sensorBox->setChecked(false);
                 memoryBox->setChecked(false);
                sensorName->setText("");
                memoryName->setText("");
            }
        }
    });
#endif
    // configure the view pane
    QWidget* p2 = new QWidget();
    QVBoxLayout* nodePanelLayout;
    nodePanel->setLayout(nodePanelLayout = new QVBoxLayout()); //new BorderLayout());
    nodePanelLayout->addWidget(p2, 0, Qt::AlignTop); //BorderLayout.NORTH);

    QVBoxLayout* p2Layout;
    p2->setLayout(p2Layout = new QVBoxLayout()); //new BoxLayout(p2, BoxLayout.Y_AXIS));

    QHBoxLayout* pLayout;
    QWidget* p = new QWidget();
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Controller: "));
    pLayout->addWidget(controllerName);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);
    {
    QHBoxLayout* pLayout;
    p = new QWidget();
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Type: "));
    pLayout->addWidget(controllerType);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);

    p2Layout->addWidget(new JSeparator(JSeparator::HORIZONTAL), 0, Qt::AlignTop);//BorderLayout.NORTH);
    }
    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Component: "));
    pLayout->addWidget(componentName);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);
    }

    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Identifier: "));
    pLayout->addWidget(componentId);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);

    p2Layout->addWidget(new JSeparator(JSeparator::HORIZONTAL), 0, Qt::AlignTop);//BorderLayout.NORTH);
    }
    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Analog: "));
    pLayout->addWidget(componentAnalog);
    pLayout->addWidget(new QLabel("  Relative: "));
    pLayout->addWidget(componentRelative);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);

    p2Layout->addWidget(new JSeparator(JSeparator::HORIZONTAL), 0, Qt::AlignTop);//BorderLayout.NORTH);
    }
    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(new QLabel("Value: "));
    pLayout->addWidget(componentValue);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);

    p2Layout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
    }
    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(sensorBox);
    pLayout->addWidget(new QLabel("Name: "));
    pLayout->addWidget(sensorName);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);
    }
    {
    p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout()); //new BoxLayout(p, BoxLayout.X_AXIS));
    pLayout->addWidget(memoryBox);
    pLayout->addWidget(new QLabel("Name: "));
    pLayout->addWidget(memoryName);
    pLayout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(p);
    }
#if 0
    // attach controls
     sensorBox->addActionListener(new ActionListener() {
        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            checkSensorBox();
        }
    });
     memoryBox->addActionListener(new ActionListener() {
        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            checkMemoryBox();
        }
    });
#endif
    // initial states
    sensorBox->setChecked(false);
    memoryBox->setChecked(false);
//    sensorName->setEnabled(true);
//    memoryName->setEnabled(true);

    // starting listening for changes
#if 0
    TreeModel::instance().addPropertyChangeListener(
            new PropertyChangeListener() {
                @Override
                /*public*/ void propertyChange(PropertyChangeEvent e) {
                    if (currentNode == NULL) {
                        return;
                    }
                    if (e.getOldValue() != currentNode) {
                        return;
                    }
                    // right place, update
                    float value = ((Float) e.getNewValue()).floatValue();
                    if (currentNode->getComponent()->isAnalog()) {
                         componentValue->setText("" + value);
                    } else {
                         componentValue->setText((value > 0.0) ? "Yes" : "No");
                    }
                }
            }
    );

#endif
    connect(UsbTreeModel0::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

void TreePanel::checkSensorBox() {
    if (currentNode == NULL) {
        return;
    }
    if (sensorBox->isChecked()) {
        // checked box, if anything there, set the node
        currentNode->setAttachedSensor(sensorName->text());
        sensorName->setEnabled(false);
    } else {
        // unchecked box, reset the node
        currentNode->setAttachedSensor("");
        sensorName->setEnabled(true);
    }

}

void TreePanel::checkMemoryBox() {
    if (currentNode == NULL) {
        return;
    }
    if ( memoryBox->isChecked()) {
        // checked box, if anything there, set the node
        currentNode->setAttachedMemory(memoryName->text());
        memoryName->setEnabled(false);
    } else {
        // unchecked box, reset the node
        currentNode->setAttachedMemory("");
        memoryName->setEnabled(true);
    }
}


void TreePanel::update() {
    if (currentNode->getController() != NULL) {
        controllerName->setText(currentNode->getController()->getName());
        controllerType->setText(currentNode->getController()->getType().toString());
    } else {
        controllerName->setText("");
        controllerType->setText("");
    }
    if (currentNode->getComponent() != NULL) {
        componentName->setText(currentNode->getComponent()->getName());
        componentId->setText(currentNode->getComponent()->getIdentifier()->toString());
        if (currentNode->getComponent()->isAnalog()) {
            componentAnalog->setText("Yes");
             componentValue->setText(QString::number(currentNode->getValue()));
            componentRelative->setText(currentNode->getComponent()->isRelative() ? "Yes" : "No");
        } else {
            componentAnalog->setText("No");
            componentRelative->setText("");
             componentValue->setText((currentNode->getValue() > 0.0) ? "Yes" : "No");
        }
        if ((currentNode->getAttachedSensor() != NULL) && (currentNode->getAttachedSensor() != (""))) {
            sensorName->setText(currentNode->getAttachedSensor());
            sensorName->setEnabled(false);
             sensorBox->setChecked(true);
        } else {
            sensorName->setText("");
            sensorName->setEnabled(true);
             sensorBox->setChecked(false);
        }
        if ((currentNode->getAttachedMemory() != NULL) && (currentNode->getAttachedMemory() != (""))) {
            memoryName->setText(currentNode->getAttachedMemory());
            memoryName->setEnabled(false);
             memoryBox->setChecked(true);
        } else {
            memoryName->setText("");
            memoryName->setEnabled(true);
             memoryBox->setChecked(false);
        }
    } else {
        componentName->setText("");
        componentId->setText("");
        componentAnalog->setText("No");
        componentRelative->setText("No");
         componentValue->setText("");
        sensorName->setText("");
        sensorName->setEnabled(true);
         sensorBox->setChecked(false);
        memoryName->setText("");
        memoryName->setEnabled(true);
         memoryBox->setChecked(false);
    }
}


/*public*/ UsbNode* TreePanel::getSelectedElement() {
    if (!dTree->isSelectionEmpty() && dTree->getSelectionPath() != NULL) {
        // somebody has been selected
        log->debug("getSelectedIcon with " + dTree->getSelectionPath()->toString());
        TreePath* path = dTree->getSelectionPath();

        int level = path->getPathCount();
        // specific items are at level 3, no action above that

        return (UsbNode*) path->getPathComponent(level - 1);
    } else {
        return NULL;
    }
}


/*public*/ void TreePanel::propertyChange(PropertyChangeEvent* e) {
    if (currentNode == NULL) {
        return;
    }
    if (VPtr<UsbNode>::asPtr(e->getOldValue()) != currentNode) {
        return;
    }
    // right place, update
    float value = /*((Float)*/ e->getNewValue().toFloat();
    if (currentNode->getComponent()->isAnalog()) {
        componentValue->setText(QString::number(value));
    } else {
        componentValue->setText((value > 0.0) ? "Yes" : "No");
    }
}
}
