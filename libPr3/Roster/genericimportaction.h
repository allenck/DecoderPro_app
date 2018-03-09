#ifndef GENERICIMPORTACTION_H
#define GENERICIMPORTACTION_H
#include "abstractaction.h"
#include "cvtablemodel.h"
#include "jframe.h"
#include <QLabel>
#include "jfilechooser.h"

class GenericImportAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ GenericImportAction(QString actionName, CvTableModel* pModel, JFrame* pParent, QLabel* pStatus, QString fileFilterName, QString fileExt1, QString fileExt2);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);


private:
 CvTableModel* mModel;
 JFrame* mParent;
 QLabel* mStatus;
 QString mActionName;
 QString mFileFilterName;
 QString mFileExt1;
 QString mFileExt2;
 JFileChooser* fileChooser;
 bool launchImporter(File* file, CvTableModel* tableModel);
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("GenericImportAction");

 friend class CsvImportAction;
};

#endif // GENERICIMPORTACTION_H
