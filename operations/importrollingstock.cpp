#include "importrollingstock.h"
#include "jfilechooser.h"
#include "file.h"
#include "QLabel"
#include "operationsxml.h"
#include <QFile>
#include <QTextStream>
#include"jmrijframe.h"
#include <QBoxLayout>
#include "control.h"

namespace Operations
{

/**
 * Provides common routes for importing cars and locomotives
 *
 * @author Dan Boudreau Copyright (C) 2013
 * @version $Revision: 24463 $
 */
///*public*/ class ImportRollingStock extends Thread {

    /*protected*/ /*static*/ /*final*/ QString ImportRollingStock::NEW_LINE = "\n"; // NOI18N

 ImportRollingStock::ImportRollingStock(QObject *parent)
 {
  lineNumber = new QLabel();
  importLine = new QLabel();
 }
 // Get file to read from
 /*protected*/ File* ImportRollingStock::getFile() {
     JFileChooser* fc = new JFileChooser(OperationsXml::getFileLocation());
     //fc->addChoosableFileFilter(new ImportFilter());
     int retVal = fc->showOpenDialog(NULL);
     if (retVal != JFileChooser::APPROVE_OPTION) {
         return NULL; // canceled
     }
     if (fc->getSelectedFile() == NULL) {
         return NULL; // canceled
     }
     File* file = fc->getSelectedFile();
     return file;
 }

 /*protected*/ QTextStream* getBufferedReader(File* file) {
     QTextStream* in = NULL;
//        try {
//            in = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8")); // NOI18N
//        } catch (FileNotFoundException e) {
//            return NULL;
//        } catch (UnsupportedEncodingException e) {
//            log.error("UTF-8 encoding not supported");
//            return NULL;
//        }
     QFile* qFile = new QFile(file->getPath());
     if(!qFile->open(QIODevice::ReadOnly))
      return NULL;
     in = new QTextStream(qFile);
     in->setCodec("UTF8");
     return in;
 }

 // create a status frame showing line number and imported text
 /*protected*/ void ImportRollingStock::createStatusFrame(QString title) {
     QWidget* ps = new QWidget();
     ps->setLayout(new QVBoxLayout);//(ps, BoxLayout.Y_AXIS));
     fstatus = new JmriJFrameX(title);
     fstatus->move(10, 10);
     fstatus->resize(Control::panelWidth700, 100);

     ps->layout()->addWidget(lineNumber);
     ps->layout()->addWidget(importLine);

     fstatus->getContentPane()->layout()->addWidget(ps);
     fstatus->setVisible(true);
 }

 /*protected*/ QStringList ImportRollingStock::parseCommaLine(QString line, int arraySize)
 {
  QVector<QString> outLine = QVector<QString>(arraySize);
  if (line.contains("\""))
  { // NOI18N
   // log.debug("line number "+lineNum+" has escape char \"");
   QStringList parseLine = line.split(",");
   int j = 0;
   for (int i = 0; i < parseLine.length(); i++)
   {
    if (parseLine[i].contains("\""))
    { // NOI18N
     QString sb = QString(parseLine[i++]);
     //sb.deleteCharAt(0); // delete the "
     sb.remove(0,1);
     outLine.replace(j,sb);
     while (i < parseLine.length())
     {
      if (parseLine[i].contains("\""))
      { // NOI18N
       sb = QString(parseLine[i]);
       //sb.deleteCharAt(sb.length() - 1); // delete the "
       sb.remove(sb.length() - 1,1);
       outLine.replace(j,outLine[j] + "," + sb);
       // log.debug("generated string: "+outLine[j]);
       j++;
       break; // done!
      }
      else
      {
       outLine.replace(j, outLine[j] + "," + parseLine[i++]);
      }
     }
    }
    else
    {
     // log.debug("outLine: "+parseLine[i]);
     outLine.replace(j++, parseLine[i]);
    }
    if (j > arraySize - 1)
    {
     break;
    }
   }
  }
  else
  {
   outLine = line.split(",").toVector();
  }
  return outLine.toList();
 }
#if 0
 /*public*/ static class ImportFilter extends javax.swing.filechooser.FileFilter {

     //@Override
     /*public*/ bool accept(File f) {
         if (f.isDirectory()) {
             return true;
         }
         QString name = f.getName();
         if (name.matches(".*\\.txt")) // NOI18N
         {
             return true;
         }
         if (name.matches(".*\\.csv")) // NOI18N
         {
             return true;
         } else {
             return false;
         }
     }

     //@Override
     /*public*/ QString getDescription() {
         return Bundle.getMessage("Text&CSV");
     }
 }
#endif
}
