#include "decoderpro3.h"
#include "file.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "jmrijframe.h"
#include "decoderindexfile.h"
#include "tabbedpreferencesaction.h"
#include "fileutil.h"
#include "decoderpro3window.h"

//DecoderPro3::DecoderPro3(QObject *parent) :
//    Apps3(parent)
//{
//}
/**
 * The JMRI application for developing the DecoderPro 3 GUI
 * <P>
 *
 * <hr> This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Bob Jacobsen Copyright 2003, 2004, 2007, 2009, 2010
 * @version $Revision: 29276 $
 */
///*public*/  class DecoderPro3 extends apps.gui3.Apps3 {
///
/*private*/ /*static*/ QString DecoderPro3::menuFile = NULL;
/*private*/ /*static*/ QString DecoderPro3::toolbarFile = NULL;
/*private*/ /*static*/ /*final*/ QString DecoderPro3::applicationName = "DecoderPro";


/*public*/  DecoderPro3::DecoderPro3(QStringList args, QObject *parent) :
  Apps3(applicationName, "DecoderProConfig3.xml", args, parent)
{
 //super(applicationName, "DecoderProConfig3.xml", args);
 log= new Logger("DecoderPro3");
 setObjectName("DecoderPro3");

 createAndDisplayFrame();
}

/*public*/  /*synchronized*/ /*static*/ QString DecoderPro3::getMenuFile()
{
 Logger* log = new Logger("DecoderPro3");
 if (menuFile == NULL)
 {
  menuFile = "dp3/Gui3Menus.xml";
  File* file = new File(menuFile);
  // decide whether name is absolute or relative
  if (!file->isAbsolute()) {
      // must be relative, but we want it to
      // be relative to the preferences directory
      menuFile = FileUtil::getUserFilesPath() + "dp3/Gui3Menus.xml";
      file = new File(menuFile);
  }
  if (!file->exists()) {
      menuFile =  "xml/config/parts/jmri/jmrit/roster/swing/RosterFrameMenu.xml";
  } else {
      log->info("Found user created menu structure this will be used instead of the system default");
  }
 }
 return menuFile;
}

/*public*/  /*synchronized*/ /*static*/ QString DecoderPro3::getToolbarFile()
{
 Logger* log = new Logger("DecoderPro3");
    if (toolbarFile == NULL) {
        toolbarFile = "dp3/Gui3MainToolBar.xml";
        File* file = new File(toolbarFile);
        // decide whether name is absolute or relative
        if (!file->isAbsolute()) {
            // must be relative, but we want it to
            // be relative to the preferences directory
            toolbarFile = FileUtil::getUserFilesPath() + "dp3/Gui3MainToolBar.xml";
            file = new File(toolbarFile);
        }
        if (!file->exists()) {
            toolbarFile = "xml/config/parts/jmri/jmrit/roster/swing/RosterFrameToolBar.xml";
        } else {
            log->info("Found user created toolbar structure this will be used instead of the system default");
        }
    }
    return toolbarFile;
}

//@Override
/*protected*/ void DecoderPro3::createMainFrame() {
    // create and populate main window
    mainFrame = new DecoderPro3Window(getMenuFile(), getToolbarFile());
}

/**
 * Force our test size. Superclass method set to max size, filling real
 * window.
 *
 * @param d
 */
//@Override
/*protected*/ void DecoderPro3::displayMainFrame(QSize d) {
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if (!p->hasProperties(mainFrame->getWindowFrameRef())) {
        mainFrame->resize(QSize(1024, 600));
        mainFrame->setMaximumSize(QSize(1024, 600));
    }

    mainFrame->setVisible(true);
}

////@Override
///*protected*/ ResourceBundle getActionModelResourceBundle() {
//    return ResourceBundle.getBundle("apps.gui3.dp3.DecoderPro3ActionListBundle");
//}

// Main entry point
/*public*/  /*static*/ void DecoderPro3::main(QStringList args)
{
    preInit(args);
    DecoderPro3* app = new DecoderPro3(args);
    app->start();
}

/*static*/ /*public*/  void DecoderPro3::preInit(QStringList args) {
    Apps3::preInit(applicationName);
    setConfigFilename("DecoderProConfig3.xml", args);
}

/**
 * Final actions before releasing control of app to user
 */
//@Override
/*protected*/ void DecoderPro3::start()
{
 Apps3::start();

 if ((!configOK) || (!configDeferredLoadOK))
 {
  if (preferenceFileExists)
  {
   //if the preference file already exists then we will launch the normal preference window
   QAction* prefsAction = new TabbedPreferencesAction(tr("Preferences"), this);
   ((TabbedPreferencesAction*)prefsAction)->actionPerformed();
  }
 }
 addToActionModel();

//    Runnable r = new Runnable() {

//        //@Override
//        /*public*/  void run() {
//            try {
//                DecoderIndexFile::instance();
//            } catch (Exception ex) {
//                log->error("Error in trying to initialize decoder index file " + ex.toString());
//            }
//        }
//    };
//    Thread thr = new Thread(r, "initialize decoder index");
//    thr.start();
 LoadDecoders* worker = new LoadDecoders(this);
 QThread* thread = new QThread;
 worker->moveToThread(thread);
 //connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
 connect(thread, SIGNAL(started()), worker, SLOT(process()));
 connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
 connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
 connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
 thread->start();
}

LoadDecoders::LoadDecoders(QObject *parent) : QObject(parent) {}
void LoadDecoders::process()
{
    try {
        InstanceManager::getDefault("DecoderIndexFile");
    } catch (Exception ex) {
        ((DecoderPro3*)parent())->log->error(tr("Error in trying to initialize decoder index file %1").arg(ex.toString()));
    }

}
