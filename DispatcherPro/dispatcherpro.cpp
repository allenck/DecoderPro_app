#include "dispatcherpro.h"
#include "loggerfactory.h"
#include "helputil.h"
#include "jbutton.h"
#include "version.h"
/**
 * The JMRI program for creating control panels.
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
 * @author Bob Jacobsen Copyright 2003
 */
// /*public*/ class DispatcherPro extends Apps {

    DispatcherPro::DispatcherPro(JFrame* p, QWidget *parent) :
        Apps(p, parent)
    {
        JmriJFrame* frame = new JmriJFrameX("PanelPro");
        createFrame(this, frame);

        DPWindowListener* l = new DPWindowListener(frame, this);
        frame->addWindowListener(l);
    }

    //@Override
    /*protected*/ QString DispatcherPro::logo() {
        return ":/resources/logo.gif";
    }

    //@Override
    /*protected*/ QString DispatcherPro::mainWindowHelpID() {
        return "package.apps.DispatcherPro.DispatcherPro";
    }

    //@Override
    /*protected*/ QString DispatcherPro::line1() {
        return tr("DispatcherPro %1, part of the JMRI® project").arg(Version::name());
    }

    //@Override
    /*protected*/ QString DispatcherPro::line2() {
        return "http://jmri.org/DispatcherPro ";
    }

    /**
     * JPanel displayed as DispatcherPro main screen.
     */
    //@Override
    /*protected*/ JPanel* DispatcherPro::statusPanel() {
        JPanel* j = new JPanel();
        j->setLayout(new QVBoxLayout());//j, BoxLayout.Y_AXIS));
        j->layout()->addWidget(Apps::statusPanel());

        // Buttons
        AbstractAction* quit = new AbstractAction(tr("Quit"), this);
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                Apps.handleQuit();
//            }
//        };

        JPanel* p3 = new JPanel();
        p3->setLayout(new FlowLayout());
        h1 = new JButton(tr("Help"));
        // as globalHelpBroker is still null, wait to attach help target after help menu is created
//        h1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        p3->layout()->addWidget(h1);
        JButton* q1 = new JButton(tr("Quit"));
//        q1.addActionListener(quit);
        connect(q1, &JButton::clicked, [=]{
           Apps::handleQuit();
        });
//        q1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        p3->layout()->addWidget(q1);
        j->layout()->addWidget(p3);

        return j;
    }


    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void DispatcherPro::attachHelp() {
        if (h1 != nullptr) {
            HelpUtil::addHelpToComponent(h1, "html.apps.DispatcherPro.index");
        }
    }

    // Main entry point
    /*public*/ /*static*/ void DispatcherPro::main(char * args[]) {

        // show splash screen early
        splash(true);

        Apps::setStartupInfo("DispatcherPro");

        setConfigFilename("DispatcherProConfig2.xml", args);
        //DispatcherPro* dp = new DispatcherPro();
        JmriJFrame* f = nullptr;//new JmriJFrame(jmri.Application.getApplicationName());
        //createFrame(dp, f);
        new DispatcherPro(f);

        log->debug("main initialization done");
        splash(false);
    }

    DPWindowListener::DPWindowListener(JFrame *p, DispatcherPro* pp)
    {
     this->p = p;
     this->pp = pp;
    }
    void DPWindowListener::windowClosing(QCloseEvent *)
    {
     pp->handleQuit();
    }

    /*private*/ /*final*/ /*static*/ Logger* DispatcherPro::log = LoggerFactory::getLogger("DispatcherPro");
