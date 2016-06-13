#include "panelpropane.h"
#include <QVBoxLayout>
#include "action.h"
#include "apps.h"
#include "abstractaction.h"
#include <QPushButton>
#include "helputil.h"
#include "flowlayout.h"

PanelProPane::PanelProPane(QWidget *parent) :
  AppsLaunchPane(parent)
{
}
/**
 * The JMRI main pane for creating control panels.
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
 * @author	Bob Jacobsen Copyright 2003, 2014
 * @version $Revision: 28746 $
 */
///*public*/ class PanelProPane extends apps.AppsLaunchPane {

/**
 *
 */
//private static final long serialVersionUID = -5742354704602024439L;

//PanelProPane() {
//    super();
//}

/**
 * Returns the ID for the window's help, which is application specific
 */
/*protected*/ QString PanelProPane::windowHelpID() {
    return "package.apps.PanelPro.PanelPro";
}

/*protected*/ QString PanelProPane::logo() {
    return "resources/PanelPro.gif";
}

/*protected*/ QString PanelProPane::line1() {
 return QString("Qt version %1").arg(QT_VERSION);
}

/*protected*/ QString PanelProPane::line2() {
    return "http://jmri.org/PanelPro ";
}

/*protected*/ QWidget* PanelProPane::statusPanel() {
    QWidget* j = new QWidget();
    QVBoxLayout* jLayout;
    j->setLayout(jLayout = new QVBoxLayout); //(j, BoxLayout.Y_AXIS));
    jLayout->addWidget(AppsLaunchPane::statusPanel());

    // Buttons
    Action*  quit = new AbstractAction(tr("Quit"),this);
//    {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -9134833676932931297L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Apps.handleQuit();
//        }
//    };
    connect(quit, SIGNAL(triggered()), this, SLOT(On_quit()));

    QWidget* p3 = new QWidget();
    FlowLayout* p3Layout;
    p3->setLayout(p3Layout = new FlowLayout());
    QPushButton* h1 = new QPushButton(tr("Help"));
    HelpUtil::addHelpToComponent(h1, "html.apps.PanelPro.PanelPro");
//    h1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    p3Layout->addWidget(h1);
    QPushButton* q1 = new QPushButton(tr("Quit"));
    //q1.addActionListener(quit);
   // q1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    p3Layout->addWidget(q1);
    jLayout->addWidget(p3);

    return j;
}
void PanelProPane::On_quit()
{
 Apps::handleQuit();
}
