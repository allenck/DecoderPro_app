#include "vsdoptionpanel.h"
#include <QGridLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "trainmanager.h"

//VSDOptionPanel::VSDOptionPanel(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 28746 $
 */
//import java.awt.GridLayout;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import javax.swing.JComboBox;
//import javax.swing.JLabel;
//import jmri.jmrit.operations.trains.Train;
//import jmri.jmrit.operations.trains.TrainManager;
//import jmri.util.swing.JmriPanel;

//@SuppressWarnings("serial")
///*public*/ class VSDOptionPanel extends JmriPanel {


/*public*/ VSDOptionPanel::VSDOptionPanel(QWidget *parent) :
JmriPanel(parent) {
    //this(NULL, NULL);
decoder_id = "";
main_frame = NULL;
}

/*public*/ VSDOptionPanel::VSDOptionPanel(QString dec, VSDecoderPane* dad) {
    //super();
    decoder_id = dec;
    main_frame = dad;
    selected_train = NULL;
    initComponents();
}

/*public*/ void VSDOptionPanel::init() {
}

/*public*/ void VSDOptionPanel::initContext(QVariant context) {
    initComponents();
}

/*public*/ void VSDOptionPanel::initComponents() {

    // Below is mostly just "filler" stuff until we implement the real thing
    //this.setLayout(new GridLayout(0, 2));
QGridLayout* g = new QGridLayout(this);

    QLabel* x = new QLabel();
    QHBoxLayout* xLayout = new QHBoxLayout(x);
    x->setText("Operations Train: ");
    g->addWidget(x, 0, 0, 0, 0);
    opsTrainComboBox = Operations::TrainManager::instance()->getTrainComboBox();
    g->addWidget(opsTrainComboBox,0,1,0,0);
//        opsTrainComboBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                opsTrainSelectAction(e);
//            }
//        });
    connect(opsTrainComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(opsTrainSelectAction()));

    hornOptionComboBox = new QComboBox();
    QStringList items = QStringList() << "3-Chime Leslie" << "5-Chime Leslie"<< "4-Chime Nathan";
    hornOptionComboBox->addItems(items);
    //hornOptionComboBox.setModel(new javax.swing.DefaultComboBoxModel<Object>(new String[]{"3-Chime Leslie", "5-Chime Leslie", "4-Chime Nathan"}));
    x = new QLabel();
    x->setText("Horn Option: ");
    g->addWidget(x,1.0,0,0);
    g->addWidget(hornOptionComboBox,1,1,0,0);
    x = new QLabel();
    x->setText("Engine Option: ");
    g->addWidget(x,2,0,0,0);
    QComboBox* y = new QComboBox();
    items.clear();
    items <<"Non-Turbo"<< "Turbo";
    //y.setModel(new javax.swing.DefaultComboBoxModel<Object>(new String[]{"Non-Turbo", "Turbo"}));
    y->addItems(items);
    g->addWidget(y,2,1,0,0);
}

/*public*/ void VSDOptionPanel::opsTrainSelectAction(JActionEvent* /*e*/) {
#if 0
if (opsTrainComboBox->itemData(opsTrainComboBox->currentIndex()) != QVariant()) {
        if (selected_train != NULL) {
            selected_train.removePropertyChangeListener(main_frame.getDecoder());
        }
        QString opsTrain = opsTrainComboBox->currentText();
        if ((selected_train = TrainManager::instance()->getTrainByName(opsTrain)) != NULL) {
            selected_train.addPropertyChangeListener(main_frame->getDecoder());
        }
    }
#endif
}
