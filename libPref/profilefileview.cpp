#include "profilefileview.h"
#include "profile.h"
#include "fileutil.h"
#include <QUrl>
#include "imageicon.h"

ProfileFileView::ProfileFileView(QObject *parent) :
    FileView(parent)
{
}
/**
 * FileView for use in a JFileChooser.
 *
 * @author Randall Wood Copyright (C) 2013, 2014
 */
///*public*/ class ProfileFileView extends FileView {

//    private static final Logger log = LoggerFactory.getLogger(ProfileFileView.class);

//@Override
/*public*/ QString ProfileFileView::getDescription(File* f) {
    if (!this->isTraversable(f)) {
        return tr("FileViewDescription") + f->getName();
    } else {
        return "";
    }
}

//@Override
/*public*/ bool ProfileFileView::isTraversable(File* f) {
//    try {
        if (Profile::isProfile(f)) {
            return false;
        }
//    } catch (NullPointerException* ex) {
//        // this is most likely caused by virtual folders like Networks in Windows 7
//        log.debug("Unable to list contents of {}", f.getPath());
//    }
    return true;
}

//@Override
/*public*/ ImageIcon* ProfileFileView::getIcon(File* f) {
    if (!isTraversable(f)) {
        return new ImageIcon(FileUtil::findURL("program:resources/jmri16x16.gif")); // NOI18N
    }
    return nullptr;
}
