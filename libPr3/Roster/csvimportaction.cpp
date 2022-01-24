#include "csvimportaction.h"
#include "csvimporter.h"
/**
 * Action to import the CV values from a CSV format file.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Dave Heap Copyright (C) 2015
 */
///*public*/ class CsvImportAction extends GenericImportAction {

/*public*/ CsvImportAction::CsvImportAction(QString actionName, CvTableModel* pModel, JFrame* pParent, QLabel* pStatus) :
    GenericImportAction(actionName, pModel, pParent, pStatus, "CSV list files", "csv", NULL)
{
}

//@Override
bool CsvImportAction::launchImporter(File* file, CvTableModel* tableModel) {
        try {
            // ctor launches operation
            new CsvImporter(file, mModel);
            return true;
        } catch (IOException* ex) {
            return false;
    }
}
