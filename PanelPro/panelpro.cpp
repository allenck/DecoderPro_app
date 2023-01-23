#include "panelpro.h"
#include "version.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "jbutton.h"
#include "helputil.h"
#include <QMenuBar>
#include "jmrijframe.h"
#include <QImageReader>
#include "connectionstatus.h"
#include "loggerfactory.h"

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

 JmriJFrame* frame = new JmriJFrameX("PanelPro");
 frame->setFrameRef(getClassName());
 createFrame(this, frame);

 PPWindowListener* l = new PPWindowListener(frame, this);
 frame->addWindowListener(l);
}

/*protected*/ QString PanelPro::logo() {
    qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();

    QImageReader reader(":/resources/PanelPro.gif");
    qDebug() << "Can read file?:" << reader.canRead();

    QImage image = reader.read();
    qDebug() << reader.errorString();
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

/*protected*/ JPanel* PanelPro::statusPanel()
{
 JPanel* j = new JPanel();
 QVBoxLayout* jLayout;
 j->setLayout(jLayout = new QVBoxLayout); //(j, BoxLayout.Y_AXIS));
 jLayout->addWidget(Apps::statusPanel());

 // Buttons
 QAction* quit = new QAction("Quit", this);
 connect(quit, SIGNAL(triggered()), this, SLOT(handleQuit()));

 JPanel* p3 = new JPanel();
 FlowLayout* p3Layout;
 p3->setLayout(p3Layout = new FlowLayout());
 h1 = new JButton(tr("Help"));
 //HelpUtil::addHelpToComponent(h1, "html.apps.PanelPro.PanelPro");
 //h1->setAlignment(Qt::AlignHCenter);
 p3Layout->addWidget(h1);
 JButton* q1 = new JButton(tr("Quit"));
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

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PanelPro::attachHelp() {
 if (h1 != nullptr) {
     HelpUtil::addHelpToComponent((QWidget*)h1, "html.apps.PanelPro.index");
 }
}

// Main entry point // moved to main.cpp ACK
/*public*/ /*static*/ void PanelPro::main(char *args[])
{
 // show splash screen early
 splash(true);

 Apps::setStartupInfo("PanelPro");

 setConfigFilename("PanelProConfig2.xml", args);
 //PanelPro* p = new PanelPro();
 JmriJFrame* f = nullptr;
 //Apps::createFrame(p, f);
 new PanelPro(f);

 log->debug("main initialization done");
 splash(false);
}

PPWindowListener::PPWindowListener(JFrame *p, PanelPro* pp)
{
 this->p = p;
 this->pp = pp;
}
void PPWindowListener::windowClosing(QCloseEvent *)
{
 pp->handleQuit();
}

/*private*/ /*final*/ /*static*/ Logger* PanelPro::log = LoggerFactory::getLogger("PanelPro");
