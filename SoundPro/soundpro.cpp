#include "soundpro.h"
#include "loggerfactory.h"
#include "version.h"
#include <QBoxLayout>
#include <QAction>
#include "audiotableaction.h"
#include "abstractaction.h"
#include "jbutton.h"
#include "flowlayout.h"
#include "jlabel.h"
#include "helputil.h"
#include "qapplication.h"

/**
 * The JMRI application for controlling audio.
 * <p>
 * If an argument is provided at startup, it will be used as the name of the
 * configuration file. Note that this is just the name, not the path; the file
 * is searched for in the usual way, first in the preferences tree and then in
 * xml/
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Bob Jacobsen Copyright 2003, 2004, 2007
 * @author Matthew Harris copyright (c) 2009
 */
//  /*public*/ class SoundPro extends Apps {

    SoundPro::SoundPro(JFrame* p, QWidget* parent) : Apps(p, parent){
        //super();
     JmriJFrame* frame = new JmriJFrameX("SoundPro");

    createFrame(this, (JmriJFrame*)frame);

    SPWindowListener* l = new SPWindowListener(frame, this);
    frame->addWindowListener(l);
    }

    //@Override
    /*protected*/ QString SoundPro::logo() {
        return ":/resources/SoundPro.gif";
    }

    //@Override
    /*protected*/ QString SoundPro::mainWindowHelpID() {
        return "package.apps.SoundPro.SoundPro";
    }

    //@Override
    /*protected*/ QString SoundPro::line1() {
        return tr("SoundPro %1, part of the JMRI® project").arg(Version::name());
    }

    //@Override
    /*protected*/ QString SoundPro::line2() {
        return "http://jmri.org/SoundPro ";
    }

    /**
     * JPanel displayed as SoundPro main screen.
     */
    //@Override
    /*protected*/ JPanel* SoundPro::statusPanel() {
        JPanel* j = new JPanel();
        j->setLayout(new QVBoxLayout());//j, BoxLayout.Y_AXIS));
        j->layout()->addWidget(Apps::statusPanel());

        // Buttons
        AudioTableAction* audioTable = new AudioTableAction(tr("Open Audio Table"),this);
        QAction* quit = new AbstractAction(tr("Quit"),this);// {
            connect(quit, &QAction::triggered, [=] {
                Apps::handleQuit();
//            }
        });

        JButton* b1 = new JButton(tr("Open Audio Table"));
        connect(b1, &JButton::clicked, [=]{
            audioTable->actionPerformed();
        });
        //b1->addActionListener(audioTable);
//        b1->setAlignmentX(JLabel::CENTER_ALIGNMENT);
        j->layout()->addWidget(b1);

        JPanel* p3 = new JPanel();
        p3->setLayout(new FlowLayout());
        h1 = new JButton(tr("Help"));
        // as globalHelpBroker is still null, wait to attach help target after help menu is created
//        h1->setAlignmentX(JLabel::CENTER_ALIGNMENT);
        p3->layout()->addWidget(h1);
        JButton* q1 = new JButton(tr("Quit"));
//        q1->addActionListener(quit);
        connect(q1, &JButton::clicked, [=] {
           Apps::handleQuit();
        });
//        q1->setAlignmentX(JLabel::CENTER_ALIGNMENT);
        p3->layout()->addWidget(q1);
        j->layout()->addWidget(p3);

        return j;
    }



    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void SoundPro::attachHelp() {
        if (h1 != nullptr) {
            HelpUtil::addHelpToComponent(h1, "html.apps.SoundPro.SoundPro");
        }
    }

    // Main entry point
    /*public*/ /*static*/ void SoundPro::main(char* args[]) {

        // show splash screen early
        splash(true);

        Apps::setStartupInfo("SoundPro");

        setConfigFilename("SoundProConfig2.xml", args);
        //SoundPro* sp = new SoundPro();
        JmriJFrame* f = nullptr; //new JmriJFrame(QApplication::applicationName());
        //createFrame(sp, f);
        new SoundPro(f);

        log->debug("main initialization done");
        splash(false);
    }

    SPWindowListener::SPWindowListener(JFrame *p, SoundPro* sp)
    {
     this->p = p;
     this->sp = sp;
    }
    void SPWindowListener::windowClosing(QCloseEvent *)
    {
     sp->handleQuit();
    }

    /*private*/ /*final*/ /*static*/ Logger* SoundPro::log = LoggerFactory::getLogger("SoundPro");
