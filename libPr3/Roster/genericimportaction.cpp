#include "genericimportaction.h"
#include "loggerfactory.h"
#include "xmlfile.h"
#include "file.h"

/**
 * Action to import the CV values from a LokProgrammer CV list file.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Dave Heap Copyright (C) 2015
 */
// /*public*/ class GenericImportAction extends AbstractAction {


/*public*/ GenericImportAction::GenericImportAction(QString actionName, CvTableModel* pModel, JFrame* pParent, QLabel* pStatus, QString fileFilterName, QString fileExt1, QString fileExt2) : AbstractAction(actionName, (QObject*)pParent)
{
    //super(actionName);
    mModel = pModel;
    mParent = pParent;
    mStatus = pStatus;
    mActionName = actionName;
    mFileFilterName = fileFilterName;
    mFileExt1 = fileExt1;
    mFileExt2 = fileExt2;
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@override
/*public*/ void GenericImportAction::actionPerformed(/*ActionEvent e*/) {

    log->debug("start to import " + mActionName);
    mStatus->setText(tr("Importing %1").arg(mActionName));

    if (fileChooser == NULL) {
        fileChooser = XmlFile::userFileChooser(mFileFilterName, mFileExt1, mFileExt2);

    }

    int retVal = fileChooser->showOpenDialog(mParent);

    if (retVal == JFileChooser::APPROVE_OPTION) {
        File* file = fileChooser->getSelectedFile();
        log->debug("Import from " + mActionName + " \"" + file->toString() + "\"");

        if (launchImporter(file, mModel)) {
            mStatus->setText(tr("OK"));
        } else {
            mStatus->setText(tr("Error Importing file \"%1\"").arg(
           file->toString()));
        }
    } else {
        mStatus->setText(tr("StateCancelled"));
    }
}

bool GenericImportAction::launchImporter(File* file, CvTableModel* tableModel) {
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* GenericImportAction::log = LoggerFactory::getLogger("GenericImportAction");
