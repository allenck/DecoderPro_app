#ifndef CSVIMPORTACTION_H
#define CSVIMPORTACTION_H
#include "genericimportaction.h"

class CsvImportAction : public GenericImportAction
{
public:
 /*public*/ CsvImportAction(QString actionName, CvTableModel* pModel, JFrame* pParent, QLabel* pStatus);

private:
 bool launchImporter(File* file, CvTableModel* tableModel);

};

#endif // CSVIMPORTACTION_H
