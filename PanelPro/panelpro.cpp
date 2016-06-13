#include "panelpro.h"
#include "version.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "helputil.h"
#include <QMenuBar>
#include "jmrijframe.h"

//PanelPro::PanelPro(QObject *parent) :
//    Apps(parent)
//{
//}
/**
 * The JMRI program for creating control panels.
 * <P>
 * If an argument is provided at startup, it will be used as the name of the
 * configuration file. Note that this is just the name, not the path; the file
 * is searched for in the usual way, first in the preferences tree and then in
 * xml/
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
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28746 $
 */
///*public*/ class PanelPro extends Apps {

/**
 *
 */
//private static final long serialVersionUID = -6877561526624987567L;

PanelPro::PanelPro(JFrame* p, QWidget *parent) :
    Apps(p, parent)
{
 //super(p);
 initGui();
}

/*protected*/ QString PanelPro::logo() {
 return ":/resources/PanelPro.gif";
}

/*protected*/ QString PanelPro::mainWindowHelpID() {
    return "package.apps.PanelPro.PanelPro";
}

/*protected*/ QString PanelPro::line1() {
    return tr("PanelPro %1, part of the JMRI project").arg(Version::name());
}

/*protected*/ QString PanelPro::line2() {
    return "http://jmri.org/PanelPro ";
}

/*protected*/ QWidget* PanelPro::statusPanel()
{
 QWidget* j = new QWidget();
 QVBoxLayout* jLayout;
 j->setLayout(jLayout = new QVBoxLayout); //(j, BoxLayout.Y_AXIS));
 jLayout->addWidget(Apps::statusPanel());

 // Buttons
 QAction* quit = new QAction("Quit", this);//
//    {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 8078721796099848602L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Apps.handleQuit();
//        }
//    };

 connect(quit, SIGNAL(triggered()), this, SLOT(handleQuit()));

 QWidget* p3 = new QWidget();
 FlowLayout* p3Layout;
 p3->setLayout(p3Layout = new FlowLayout());
 QPushButton* h1 = new QPushButton(tr("Help"));
 HelpUtil::addHelpToComponent(h1, "html.apps.PanelPro.PanelPro");
 //h1->setAlignment(Qt::AlignHCenter);
 p3Layout->addWidget(h1);
 QPushButton* q1 = new QPushButton(tr("Quit"));
 //q1.addActionListener(quit);
 connect(q1, SIGNAL(clicked()), this, SLOT(handleQuit()));
 //q1->setAlignment(Qt::AlignHCenter);
 p3Layout->addWidget(q1);
 jLayout->addWidget(p3);

 return j;
}

void PanelPro::handleQuit()
{
 Apps::handleQuit();
}

// Main entry point // moved to main.cpp ACK
/*public*/ /*static*/ void PanelPro::main(char *args[])
{
 Logger log("PanelPro");
 // show splash screen early
 splash(true);

 Apps::setStartupInfo("PanelPro");

 setConfigFilename("PanelProConfig2.xml", args);
 JmriJFrame* f = new JmriJFrame("PanelPro");
 createFrame(new PanelPro(f), f);

 log.debug("main initialization done");
 splash(false);
}

///*protected*/ void PanelPro::windowClosing(QCloseEvent * e)
//{
// Apps::windowClosing(e);
//}
