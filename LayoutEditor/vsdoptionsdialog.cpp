#include "vsdoptionsdialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "propertychangeevent.h"
#include "trainmanager.h"

//VSDOptionsDialog::VSDOptionsDialog(QWidget *parent) :
//  JDialog(parent)
//{
//}
/**
 * class VSDOptionsDialog
 *
 * Configuration dialog for setting up a new VSDecoder
 */

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
 * @version			$Revision: 21510 $
 */
//import javax.swing.BoxLayout;
//import javax.swing.JButton;
//import javax.swing.JComboBox;
//import javax.swing.JDialog;
//import javax.swing.JLabel;
//import javax.swing.JPanel;
//import javax.swing.SwingUtilities;
//import jmri.jmrit.operations.trains.Train;
//import jmri.jmrit.operations.trains.TrainManager;

///*public*/ class VSDOptionsDialog extends JDialog {

/**
 *
 */
//private static final long serialVersionUID = -4803792315315710325L;

/*public*/ /*static*/ /*final*/ QString VSDOptionsDialog::OPTIONS_PROPERTY = "Options"; // NOI18N


/*public*/ VSDOptionsDialog::VSDOptionsDialog(QWidget* parent, QString title)
 : JDialog(parent, title, true)
{
    //super(SwingUtilities.getWindowAncestor(parent), title);
    initComponents();
}

/*public*/ void VSDOptionsDialog::initComponents() {
    //this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.PAGE_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
    QLabel* x = new QLabel();
    x->setText(tr("Select Train"));
    thisLayout->addWidget(x);
    opsTrainComboBox = Operations::TrainManager::instance()->getTrainComboBox();
    thisLayout->addWidget(opsTrainComboBox);

    QPushButton* closeButton = new QPushButton(tr("OK"));
    closeButton->setEnabled(true);
    closeButton->setToolTip(tr("Close Dialog"));
//    closeButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            closeButtonActionPerformed(e);
//        }
//    });
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonActionPerformed()));
    thisLayout->addWidget(closeButton);
    this->adjustSize();
    this->setVisible(true);
}

/*private*/ void VSDOptionsDialog::closeButtonActionPerformed(JActionEvent* ae)
{
 if (opsTrainComboBox->currentText() != NULL) {
  //firePropertyChange(OPTIONS_PROPERTY, QVariant(), opsTrainComboBox->currentText());
  emit propertyChange(new PropertyChangeEvent(this, OPTIONS_PROPERTY, QVariant(), opsTrainComboBox->currentText()));
 }
 //dispose();
 close();
}
