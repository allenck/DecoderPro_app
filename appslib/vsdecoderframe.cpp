#include "vsdecoderframe.h"
#include <QVBoxLayout>
#include "vsdecoderpane.h"
#include <QMenu>
#include <QMenuBar>
#include "loadvsdfileaction.h"
#include "vsdpreferencesaction.h"
#include "logger.h"

//VSDecoderFrame::VSDecoderFrame(QWidget *parent) :
//  JmriJFrame(parent)
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
//import java.awt.BorderLayout;
//import java.awt.Dimension;
//import java.util.ArrayList;
//import java.util.List;
//import java.util.ResourceBundle;
//import javax.swing.JMenu;
//import javax.swing.JMenuBar;
//import jmri.jmrit.vsdecoder.swing.VSDPreferencesAction;
//import jmri.util.JmriJFrame;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//@SuppressWarnings("serial")
//class VSDecoderFrame extends JmriJFrame {

    //private static final ResourceBundle vsdBundle = VSDecoderBundle.bundle();



/*public*/ VSDecoderFrame::VSDecoderFrame(QWidget *parent) :
  JmriJFrame(parent) {
    //super();
 log = new Logger("VSDecoderFrame");
    initGUI();
}

/*public*/ void VSDecoderFrame::initGUI() {
    log->debug("initGUI");
    this->setWindowTitle("VSDecoder - (no loco)");
    this->buildMenu();
    //this->setLayout(new BorderLayout());
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    decpane = new VSDecoderPane(this);
    decpane->initComponents();
    centralWidgetLayout->addWidget(decpane,0,Qt::AlignCenter);
    this->resize( QSize(decpane->sizeHint().width() + 20, decpane->sizeHint().height() + 20));
//    log->debug("pane size + " + decpane->sizeHint());
    this->setVisible(true);

    //this.pack();
    adjustSize();
    log->debug("done...");
}

/*private*/ void VSDecoderFrame::buildMenu() {
    QMenu* fileMenu = new QMenu(tr("File"));

    fileMenu->addAction(new LoadVSDFileAction(tr("Load VSD File"),this));
//    fileMenu->addAction(new StoreXmlVSDecoderAction(tr("VSDecoderFileMenuSaveProfile")));
//    fileMenu->addAction(new LoadXmlVSDecoderAction(tr("VSDecoderFileMenuLoadProfile")));
    fileMenu->addAction(new VSDPreferencesAction(tr("VSDecoder Preferences"),this));

//    fileMenu.getItem(1).setEnabled(false); // disable XML store
//    fileMenu.getItem(2).setEnabled(false); // disable XML load

    menuList =  QList<QMenu*>(/*2*/);

    menuList.append(fileMenu);

    this->setMenuBar(new QMenuBar());
    this->menuBar()->addMenu(fileMenu);
//    this->addHelpMenu("package.jmri.jmrit.vsdecoder.VSDecoderFrame", true);

}

/*public*/ void VSDecoderFrame::windowClosing(QCloseEvent* e) {
    // Call the superclass function
    JmriJFrame::windowClosing(e);

    log->debug("VSDecoderFrame windowClosing() called... "/* + e.toString()*/);

    log->debug("Calling decpane.windowClosing() directly " /*+ e.toString()*/);
//    decpane->windowClosing(e);
}

/*public*/ QList<QMenu*> VSDecoderFrame::getMenus() {
    return menuList;
}
