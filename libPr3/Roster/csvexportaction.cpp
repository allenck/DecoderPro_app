#include "csvexportaction.h"
#include "loggerfactory.h"
#include "file.h"
#include "QFile"
#include <QTextStream>

/**
 * Action to export the CV values to a Comma Separated Valiable (CSV) data file.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 */
///*public*/ class CsvExportAction extends AbstractAction {

/*public*/ CsvExportAction::CsvExportAction(QString actionName, CvTableModel* pModel, JFrame* pParent) : AbstractAction(actionName, pParent){
    //super(actionName);
    mModel = pModel;
    mParent = pParent;
}



//@Override
/*public*/ void CsvExportAction::actionPerformed(/*ActionEvent e*/)
{

 if (fileChooser == NULL) {
     fileChooser = new JFileChooser();
 }

 int retVal = fileChooser->showSaveDialog(mParent);

 if (retVal == JFileChooser::APPROVE_OPTION) {
     File* file = fileChooser->getSelectedFile();
     if (log->isDebugEnabled()) {
         log->debug("start to export to CSV file " + file->toString());
     }

     try
     {

         //PrintStream str = new PrintStream(new FileOutputStream(file));
      QFile f(file->getPath());
      if(!f.open(QIODevice::WriteOnly))  throw new IOException();
      QTextStream* str = new QTextStream(&f);


         *str << ("CV, value") << "\n";
         for (int i = 0; i < mModel->rowCount(QModelIndex()); i++) {
             CvValue* cv = mModel->getCvByRow(i);
             QString num = cv->number();
             int value = cv->getValue();
             //str.println(num + "," + value);
             *str << num + "," + value << "\n";
         }

         str->flush();
         str->device()->close();


     } catch (IOException* ex) {
         log->error("Error writing file: " + ex->getMessage());
     }
 }
}

/*private*/ /*final*/ /*static*/ Logger* CsvExportAction::log = LoggerFactory::getLogger("CsvExportAction");
