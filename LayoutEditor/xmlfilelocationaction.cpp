#include "xmlfilelocationaction.h"
#include "fileutil.h"
#include "system.h"
#include "file.h"
#include "roster.h"
#include "jmrijframe.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include <QTextBrowser>

//XmlFileLocationAction::XmlFileLocationAction()
//{
/**
* Swing action to display the JMRI directory locations.
* <P>
* Although this has "XML" in it's name, it's actually much more general. It
* displays: <ul>
* <li>The preferences directory <li>The program directory <li>and any log files
* seen in the program directory </ul>
*
* @author	Bob Jacobsen Copyright (C) 2004, 2007
*/
///*public*/ class XmlFileLocationAction extends AbstractAction {

/*public*/ XmlFileLocationAction::XmlFileLocationAction(QObject* parent)
        : AbstractAction(parent)
{
 //super();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()) );
}

//@Override
/*public*/ void XmlFileLocationAction::actionPerformed(JActionEvent *ev) {

    /*final*/ QString user = FileUtil::getUserFilesPath();
    /*final*/ QString roster = Roster::getDefault()->getRosterLocation();
    /*final*/ QString profile = FileUtil::getProfilePath();
    /*final*/ QString settings = FileUtil::getPreferencesPath();
    /*final*/ QString scripts = FileUtil::getScriptsPath();
    /*final*/ QString prog = System::getProperty("user.dir");
    /*final*/ QString log = System::getProperty("jmri.log.path");

    QString configName = System::getProperty("org.jmri.Apps.configFilename");
    if (!( File(configName).isAbsolute())) {
        // must be relative, but we want it to
        // be relative to the preferences directory
        configName = profile + configName;
    }

    JFrame* frame = new JmriJFrameX("Locations");  // to ensure fits
    //frame->setTitle(tr("Locations"));

    QWidget* pane = new QWidget();
    pane->setLayout(new QVBoxLayout); //(pane, BoxLayout.Y_AXIS));

    QWidget* buttons = new QWidget();
    buttons->setLayout(new FlowLayout());
    pane->layout()->addWidget(buttons);

    QPushButton* b = new QPushButton("Open User Files Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new File(user));
//            } catch (IOException e) {
//                XmlFileLocationAction.log.error("Error when opening user files location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening user files location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openUserFilesButton()));
    b = new QPushButton("Open Roster Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(roster));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening roster location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening roster location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openRosterButton()));
    b = new QPushButton("Open Profile Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(profile));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening profile location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening profile location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openProfileButton()));
    b = new QPushButton("Open Settings Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(settings));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening settings location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening settings location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openSettingsButton()));
    b = new QPushButton("Open Scripts Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(scripts));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening scripts location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening scripts location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openScriptsButton(ActionEvent*)));
    b = new QPushButton("Open Program Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(prog));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening program location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening program location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openProgramButton()));
    b = new QPushButton("Open Log Files Location");
    buttons->layout()->addWidget(b);
//    b.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            try {
//                Desktop.getDesktop().open(new java.io.File(log));
//            } catch (java.io.IOException e) {
//                XmlFileLocationAction.log.error("Error when opening log files location: " + e);
//            } catch (UnsupportedOperationException e) {
//                XmlFileLocationAction.log.error("Error when opening log files location: " + e);
//            }
//        }
//    });
    connect(b, SIGNAL(clicked(bool)), this, SLOT(on_openLogFilesButton()));

    //QScrollArea* scroll = new JScrollPane(pane);
    //frame.getContentPane().add(scroll);
    //QVBoxLayout* thisLayout = new QVBoxLayout(frame->getContentPane());

    QTextBrowser* textPane = new QTextBrowser();
    //textPane->setEditable(false);
    pane->layout()->addWidget(textPane);
    frame->getContentPane()->layout()->addWidget(pane);

    textPane->append("User Files Location: " + user + "\n");

    textPane->append("Roster Location: " + roster + "\n");

    textPane->append("Profile Location: " + profile + "\n");

    textPane->append("Settings Location: " + settings + "\n");

    textPane->append("Current Config file: " + configName + "\n");

    textPane->append("Scripts Location: " + scripts + "\n");

    textPane->append("Program Location: " + prog + "\n");

    textPane->append("Log Files Location: " + log + "\n");

    addLogFiles(textPane, log);

    frame->adjustSize();
    frame->setVisible(true);
}

void XmlFileLocationAction::addLogFiles(QTextBrowser* pane, QString logDir) {
    File* dir = new File(logDir);
    QStringList files = dir->list();
    for (int i = 0; i < files.length(); i++) {
        if (files[i].indexOf(".log") != -1) {
            pane->setPlainText(logDir + files[i] + "\n");
        }
    }
}

/*public*/ void XmlFileLocationAction::on_openUserFilesButton(JActionEvent* event) {
//    try {
//        Desktop.getDesktop().open(new File(user));
//    } catch (IOException e) {
//        XmlFileLocationAction.log.error("Error when opening user files location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening user files location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openRosterButton(JActionEvent *event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(roster));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening roster location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening roster location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openProfileButton(JActionEvent* event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(profile));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening profile location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening profile location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openSettingsButton(JActionEvent* event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(settings));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening settings location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening settings location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openScriptsButton(JActionEvent* event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(scripts));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening scripts location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening scripts location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openProgramButton(JActionEvent* event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(prog));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening program location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening program location: " + e);
//    }
}

/*public*/ void XmlFileLocationAction::on_openLogFilesButton(JActionEvent *event) {
//    try {
//        Desktop.getDesktop().open(new java.io.File(log));
//    } catch (java.io.IOException e) {
//        XmlFileLocationAction.log.error("Error when opening log files location: " + e);
//    } catch (UnsupportedOperationException e) {
//        XmlFileLocationAction.log.error("Error when opening log files location: " + e);
//    }
}
