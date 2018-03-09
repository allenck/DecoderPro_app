#ifndef CSVEXPORTACTION_H
#define CSVEXPORTACTION_H
#include "abstractaction.h"
#include "jfilechooser.h"
#include "jframe.h"
#include "cvtablemodel.h"

class Logger;
class CsvExportAction : public AbstractAction
{
 Q_OBJECT

public:
 /*public*/ CsvExportAction(QString actionName, CvTableModel* pModel, JFrame* pParent);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CsvExportAction");
 JFileChooser* fileChooser;
 JFrame* mParent;
 /**
  * CvTableModel to load
  */
 CvTableModel* mModel;

};

#endif // CSVEXPORTACTION_H
