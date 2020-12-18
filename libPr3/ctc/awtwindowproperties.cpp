#include "awtwindowproperties.h"
#include "file.h"
#include "ctcfiles.h"
#include "bufferedwriter.h"
#include "jframe.h"
#include <QFile>
#include "projectscommonsubs.h"


AwtWindowProperties::AwtWindowProperties(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 *  Technically, there should be ONLY ONE of these in the entire system!
 *  You can have more than one, you only "pollute" the file system with numerous other file(s).
 *  This object "maintains" certain properties of windows so that users when they restart
 *  the program can find the windows at the same place.
 */
///*public*/ class AwtWindowProperties {

    //@SuppressFBWarnings(value = "DE_MIGHT_IGNORE", justification = "Any errors, I don't care")
    /*public*/ AwtWindowProperties::AwtWindowProperties(JFrame* window, QString filename, QString windowName, QObject *parent) : QObject(parent){
        _mProperties = new Properties();
        _mFilename = filename;
        _mMasterWindow = window;
        try {
            File* file = CTCFiles::getFile(filename);
//            try (BufferedReader bufferedReader = new BufferedReader(new FileReader(file)))
            {
             QFile* f = new QFile(file->getPath());
             if(!f->open(QIODevice::ReadOnly))
              throw IOException(tr("%1 not open").arg(filename));
             QTextStream* bufferedReader = new QTextStream(f);
                _mProperties->load(bufferedReader);
            }
        } catch (IOException e) {}
        setWindowState(window, windowName);
    }

    //@SuppressFBWarnings(value = "DE_MIGHT_IGNORE", justification = "Let it not write anything if it fails.")
    /*public*/ void AwtWindowProperties::close() {
        try {
            File* file = CTCFiles::getFile(_mFilename);
            //try (BufferedWriter* bufferedWriter = new BufferedWriter(new FileWriter(file)))
            {
             QFile* f = new QFile(file->getPath());
             if(!f->open(QIODevice::WriteOnly))
              throw IOException(tr("%1 not open").arg(_mFilename));
             QTextStream* bufferedWriter = new QTextStream(f);
                _mProperties->store(bufferedWriter, "All Ant Windows Properties");           // NOI18N
            }
        } catch (IOException e) {}
    }

    /*public*/ /*final*/ void AwtWindowProperties::setWindowState(JFrame* window, QString windowName) {
        QRect currentWindowRectangle = window->rect();//window.getBounds();  // In case any width/heigth below "fail" (i.e. new file, problems of any kind),
                                                                // we will default to what the programmer designed the window size for.
//  If the "default" window size as created by the programmer is larger than what the user specified the size as from the
//  last time they closed this window, they we will override that users smaller value.  This is in case the programmer
//  increased it's size between versions of the program:
        int windowWidth = ProjectsCommonSubs::getIntFromStringNoThrow(_mProperties->getProperty(windowName + ".Width"), currentWindowRectangle.width());    // NOI18N
        int windowHeight = ProjectsCommonSubs::getIntFromStringNoThrow(_mProperties->getProperty(windowName + ".Height"), currentWindowRectangle.height()); // NOI18N
        if (currentWindowRectangle.width() > windowWidth) windowWidth = currentWindowRectangle.width();
        if (currentWindowRectangle.height() > windowHeight) windowHeight = currentWindowRectangle.height();
        window->setBounds(QRect( ProjectsCommonSubs::getIntFromStringNoThrow(_mProperties->getProperty(windowName + ".X"), _mMasterWindow->pos().x()), // NOI18N
                                        ProjectsCommonSubs::getIntFromStringNoThrow(_mProperties->getProperty(windowName + ".Y"), _mMasterWindow->pos().y()), // NOI18N
                                        windowWidth,
                                        windowHeight));
    }

    /*public*/ void AwtWindowProperties::saveWindowState(JFrame* window, QString windowName) {
        QRect rectangle = window->rect();//window->getBounds();
        _mProperties->setProperty(windowName + ".X", QString::number((int)rectangle.x()));           // NOI18N
        _mProperties->setProperty(windowName + ".Y", QString::number((int)rectangle.y()));           // NOI18N
        _mProperties->setProperty(windowName + ".Width", QString::number((int)rectangle.width()));   // NOI18N
        _mProperties->setProperty(windowName + ".Height", QString::number((int)rectangle.height())); // NOI18N
    }

    /*public*/ void AwtWindowProperties::saveWindowStateAndClose(JFrame* window, QString windowName) {
        saveWindowState(window, windowName);
        close();
    }
