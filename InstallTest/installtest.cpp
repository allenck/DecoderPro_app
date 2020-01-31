#include "installtest.h"
#include "version.h"
#include <QBoxLayout>
#include <QWidget>
#include "paneprogaction.h"
#include "paneopsprogaction.h"
#include <QPushButton>
#include "globalprogrammermanager.h"
#include "addressedprogrammermanager.h"
#include "instancemanager.h"

//InstallTest::InstallTest()
//{

//}
/**
 * The JMRI application for testing JMRI installation.
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
 *
 * @author	Ken Cameron Copyright 2008
 */
///*public*/ class InstallTest extends Apps {

InstallTest::InstallTest(JFrame* p) : Apps(p) {
    //super(p);
//    ITWindowListener* l = new ITWindowListener(p, this);
//    p->addWindowListener(l);
//    init();
//    initGui();
    JmriJFrame* frame = new JmriJFrame("InstallTest");
    createFrame(this, frame);

    ITWindowListener* l = new ITWindowListener(frame, this);
    frame->addWindowListener(l);
}

//@Override
/*protected*/ QString InstallTest::logo() {
    return "resources/InstallTest.gif";
}

//@Override
/*protected*/ QString InstallTest::mainWindowHelpID() {
    return "package.apps.InstallTest.InstallTest";
}

//@Override
/*protected*/ QString InstallTest::line1() {
    return tr("InstallTest %1, part of the JMRI® project").arg(Version::name());
}

//@Override
/*protected*/ QString InstallTest::line2() {
    return "http://jmri.org/InstallTest";
}

//@Override
/*protected*/ QWidget* InstallTest::statusPanel() {
    QWidget* j = new QWidget();
    QBoxLayout* jLayout;
    j->setLayout(jLayout =new QVBoxLayout()); //(j, BoxLayout.Y_AXIS));
    jLayout->addWidget(Apps::statusPanel());

    Action* serviceprog = new PaneProgAction(tr("Service Mode (Programming Track) Programmer"),this);
    Action* opsprog = new PaneOpsProgAction(tr("Operations Mode (Main Track) Programmer"),this);
    Action* quit = new InstallTestQuitAction(tr("Quit"), this);
//    {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            Apps::handleQuit();
//        }
//    };

    // Buttons
    QPushButton* b1 = new QPushButton(tr("Service Mode (Programming Track) Programmer"));
    //b1.addActionListener(serviceprog);
    connect(b1, SIGNAL(clicked()), (PaneProgAction*)serviceprog, SLOT(actionPerformed()));
    //b1->setAlignmentX(JLabel.CENTER_ALIGNMENT);
    jLayout->addWidget(b1,0, Qt::AlignCenter);
#if 1
    GlobalProgrammerManager* gpm = (GlobalProgrammerManager*)InstanceManager::getDefault("ProgrammerManager");
    if (InstanceManager::getNullableDefault("ProgrammerManager") == NULL
            || /*!((GlobalProgrammerManager*)!InstanceManager::getDefault("ProgrammerManager"))->isGlobalProgrammerAvailable()*/ !gpm->isGlobalProgrammerAvailable())
    {
        b1->setEnabled(false);
        b1->setToolTip(tr("This button is disabled because your command station can't do service mode programming, or we don't yet have code to do it for that type of system"));
    }
#endif
    QPushButton* m1 = new QPushButton(tr("Operations Mode (Main Track) Programmer"));
//    m1.addActionListener(opsprog);
    connect(m1, SIGNAL(clicked()), (PaneOpsProgAction*)opsprog, SLOT(actionPerformed()));
//    m1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    jLayout->addWidget(m1, 0, Qt::AlignCenter);
    if (InstanceManager::getNullableDefault("AddressedProgrammerManager") == NULL
            || !((AddressedProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->isAddressedModePossible())
    {
        m1->setEnabled(false);
        m1->setToolTip(tr("This button is disabled because your command station can't do operations mode programming, or we don't yet have code to do it for that type of system"));
    }

    QPushButton* q1 = new QPushButton(tr("Quit"));
//    q1.addActionListener(quit);
    connect(q1, SIGNAL(clicked(bool)), (InstallTestQuitAction*)quit, SLOT(actionPerformed()));
//    q1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    jLayout->addWidget(q1, 0, Qt::AlignCenter);
    return j;
}


void InstallTestQuitAction::actionPerformed()
{
    Apps::handleQuit();
}

// Main entry point
/*public*/ /*static*/ void InstallTest::main(char *args[])
{
 Logger* log = new Logger("InstallTest");
    // show splash screen early
    splash(true);

    Apps::setStartupInfo("InstallTest");

    setConfigFilename("InstallTestConfig2.xml", args);
    JmriJFrame* f = new JmriJFrame("InstallTest");
    //createFrame(new InstallTest(f), f);
    new InstallTest(f);

    log->debug("main initialization done");
    splash(false);
}

ITWindowListener::ITWindowListener(JFrame *p, InstallTest* pp)
{
 this->p = p;
 this->pp = pp;
}
void ITWindowListener::windowClosing(QCloseEvent *)
{
 pp->handleQuit();
}
