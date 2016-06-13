#include "trainprintutilities.h"
#include "hardcopywriter.h"
#include "jframe.h"
#include "setup.h"
#include <QTextStream>
#include <QFile>
#include "file.h"
#include "imageicon.h"
#include "qlabel.h"
#include "jlabel.h"
#include "traincommon.h"
#include "trainmanagerxml.h"
#include "printwriter.h"
#include <QComboBox>

namespace Operations
{
/**
 * Train print utilities. Used for train manifests and build reports.
 *
 * @author Daniel Boudreau (C) 2010
 * @version $Revision: 29599 $
 *
 */
///*public*/ class TrainPrintUtilities {

 /*static*/ /*final*/ QString TrainPrintUtilities::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ char TrainPrintUtilities::HORIZONTAL_LINE_SEPARATOR = '-'; // NOI18N
 /*static*/ /*final*/ char TrainPrintUtilities::VERTICAL_LINE_SEPARATOR = '|'; // NOI18N
 /*static*/ /*final*/ char TrainPrintUtilities::SPACE = ' ';

 /**
  * Print or preview a train manifest, build report, or switch list.
  *
  * @param file File to be printed or previewed
  * @param name Title of document
  * @param isPreview true if preview
  * @param fontName optional font to use when printing document
  * @param isBuildReport true if build report
  * @param logoURL optional pathname for logo
  * @param printerName optional default printer name
  * @param orientation Setup::LANDSCAPE, Setup::PORTRAIT, or Setup::HANDHELD
  * @param fontSize font size
  */
 /*public*/ /*static*/ void TrainPrintUtilities::printReport(File* file, QString name, bool isPreview, QString fontName,
         bool isBuildReport, QString logoURL, QString printerName, QString orientation, int fontSize)
 {
  Logger* log = new Logger("TrainPrintUtilities");
  // obtain a HardcopyWriter to do this
  HardcopyWriter* writer = NULL;
  JFrame* mFrame = new JFrame();
  bool isLandScape = false;
  bool printHeader = true;
  double margin = .5;
  QSize pagesize = QSize();
  if (orientation==(Setup::LANDSCAPE)) {
      margin = .65;
      isLandScape = true;
  }
  if (orientation==(Setup::HANDHELD) || orientation==(Setup::HALFPAGE)) {
      printHeader = false;
      pagesize = QSize(290, 792);
      if (orientation==(Setup::HALFPAGE)) {
          pagesize = QSize(345, 792);
      }
  }
  //try {
   writer = new HardcopyWriter(mFrame, name, fontSize, margin, margin, .5, .5,
              isPreview/*, printerName, isLandScape, printHeader, pagesize*/);
//        } catch (HardcopyWriter.PrintCanceledException ex) {
//            log->debug("Print cancelled");
//            return;
//        }
  // set font
  if (fontName!=("")) {
      writer->setFontName(fontName);
  }

  // now get the build file to print
  //BufferedReader in = NULL;
  QTextStream* in = NULL;
  QFile* qFile = new QFile(file->getPath());
  if(!qFile->open(QIODevice::ReadOnly))
  {
   Logger::error(tr("Build '%1'file doesn't exist").arg(file->getPath()));
   writer->close();
   return;
  }
  log->debug(tr("reading file %1").arg(file->getPath()));
  //try {
      //in = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8")); // NOI18N
  in =new QTextStream(qFile);
//     } catch (FileNotFoundException e) {
//         Logger::error("Build file doesn't exist");
//         writer->close();
//         return;
//     } catch (UnsupportedEncodingException e) {
//         Logger::error("Doesn't support UTF-8 encoding");
//         writer->close();
//         return;
//     }
  QString line;

  if (!isBuildReport && logoURL != NULL && logoURL!=(""))
  {
   ImageIcon* icon = new ImageIcon(logoURL);
   if (icon->getIconWidth() == -1) {
       Logger::error("Logo not found: " + logoURL);
   } else {
       writer->write(icon->getImage(), new QLabel);
   }
  }
  QColor c = QColor();
  while (true)
  {
   if(in->atEnd())
    break;
   try
   {
    line = in->readLine();
    log->debug(tr("read line of length %2: %1").arg(line).arg(line.length()));
   }

   catch (IOException e)
   {
    log->debug("Print read failed");
    break;
   }
   if (line == NULL) {
       break;
   }
   if(line.contains("DOCTYPE HTML"))
   {
    writer->writeHtml(line);
    continue;
   }
   //			log->debug("Line: {}", line.toString());
   // check for build report print level
   if (isBuildReport)
   {
    line = filterBuildReport(line, false); // no indent
    if (line==(""))
    {
     continue;
    }
   // printing the train manifest
   }
   else
   {
    // determine if there's a line separator
    if (line.length() > 0)
    {
     bool horizontialLineSeparatorFound = true;
     for (int i = 0; i < line.length(); i++)
     {
      if (line.at(i) != HORIZONTAL_LINE_SEPARATOR)
      {
       horizontialLineSeparatorFound = false;
       break;
      }
     }
     if (horizontialLineSeparatorFound)
     {
      writer->write(writer->getCurrentLineNumber(), 0, writer->getCurrentLineNumber(), line.length() + 1);
      c = QColor();
      continue;
     }
    }
    for (int i = 0; i < line.length(); i++)
    {
     if (line.at(i) == VERTICAL_LINE_SEPARATOR)
     {
         // make a frame (manifest two column format)
      if (Setup::isTabEnabled())
      {
       writer->write(writer->getCurrentLineNumber(), 0, writer->getCurrentLineNumber() + 1, 0);
       writer->write(writer->getCurrentLineNumber(), line.length() + 1,
               writer->getCurrentLineNumber() + 1, line.length() + 1);
      }
      writer->write(writer->getCurrentLineNumber(), i + 1, writer->getCurrentLineNumber() + 1, i + 1);
     }
    }
    line = line.replace(VERTICAL_LINE_SEPARATOR, SPACE);
    // determine if line is a pickup or drop
    if ((Setup::getPickupEnginePrefix()!=("") && line.startsWith(Setup
            ::getPickupEnginePrefix()))
            || (Setup::getPickupCarPrefix()!=("") && line.startsWith(Setup
                    ::getPickupCarPrefix()))
            || (Setup::getSwitchListPickupCarPrefix()!=("") && line
                    .startsWith(Setup::getSwitchListPickupCarPrefix())))
    {
     // log->debug("found a pickup line");
     c = Setup::getPickupColor();
    }
    else if ((Setup::getDropEnginePrefix()!=("") && line.startsWith(Setup
            ::getDropEnginePrefix()))
            || (Setup::getDropCarPrefix()!=("") && line.startsWith(Setup
                    ::getDropCarPrefix()))
            || (Setup::getSwitchListDropCarPrefix()!=("") && line.startsWith(Setup
                    ::getSwitchListDropCarPrefix())))
    {
     // log->debug("found a drop line");
     c = Setup::getDropColor();
    }
    else if ((Setup::getLocalPrefix()!=("") && line.startsWith(Setup
            ::getLocalPrefix()))
            || (Setup::getSwitchListLocalPrefix()!=("") && line.startsWith(Setup
                    ::getSwitchListLocalPrefix())))
    {
     // log->debug("found a drop line");
     c = Setup::getLocalColor();
    }
    else if (!line.startsWith(TrainCommon::TAB))
    {
     c = QColor();
    }
    if (c != QColor())
    {
     try
     {
      writer->write(c, line + NEW_LINE);
      continue;
     }
     catch (IOException e)
     {
      log->debug("Print write color failed");
      break;
     }
    }
   }
   try
   {
    writer->write(line + NEW_LINE);
   }
   catch (IOException e)
   {
    log->debug("Print write failed");
    break;
   }
  }
  // and force completion of the printing
  try {
      in->device()-> close();
  } catch (IOException e) {
      log->debug("Print close failed");
  }
  writer->close();
 }

 /**
  * Creates a new build report file with the print detail numbers replaced by
  * indentations. Then calls open desktop editor.
  *
  * @param file build file
  * @param name train name
  */
 /*public*/ /*static*/ void TrainPrintUtilities::editReport(File* file, QString name)
 {
  // make a new file with the build report levels removed
  QTextStream* in = NULL;
  //try {
  QFile* qFile = new QFile(file->getPath());
  if(!qFile->open(QIODevice::ReadWrite))
  {
   Logger::error(tr("Build '%1'file doesn't exist").arg(file->getPath()));
   return;
  }
      //in = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8")); // NOI18N
  in = new QTextStream(qFile);
//     } catch (FileNotFoundException e) {
//      Logger::error(tr("Build '%1'file doesn't exist").arg(file->getPath()));
//         return;
//     }
//     catch (UnsupportedEncodingException e) {
//         Logger::error("Doesn't support UTF-8 encoding");
//         return;
//     }
  PrintWriter* out;
  File* buildReport = TrainManagerXml::instance()->createTrainBuildReportFile(
          tr("Report") + " " + name);
  //try {
  qFile = new QFile(buildReport->getPath());
  if(!qFile->open(QIODevice::WriteOnly))
  {
  Logger::error(tr("Build '%1'file doesn't exist").arg(buildReport->getPath()));
  return;
  }
//         out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
//                 new FileOutputStream(buildReport), "UTF-8")), true); // NOI18N
  out = new PrintWriter(new QTextStream(qFile));
//     } catch (IOException e) {
//         Logger::error("Can not create build report file");
//         try {
//             in.close();
//         } catch (IOException ee) {
//         }
      return;
//  }
  QString line = " ";
  while (true) {
      try {
          line = in->readLine();
          if (line == NULL) {
              break;
          }
          line = filterBuildReport(line, Setup::isBuildReportIndentEnabled());
          if (line==("")) {
              continue;
          }
          out->println(line); // indent lines for each level
      } catch (IOException e) {
//          log->debug("Print read failed");
          break;
      }
  }
  // and force completion of the printing
  try {
      in->device()-> close();
  } catch (IOException e) {
//      log->debug("Close failed");
  }
  out->close();
  // open editor
// TODO::  openDesktopEditor(buildReport);
 }

 /*
  * Removes the print levels from the build report
  */
 /*private*/ /*static*/ QString TrainPrintUtilities::filterBuildReport(QString line, bool indent)
 {
  Logger*log = new Logger("TrainPrintUtilies");
  //QStringList inputLine = line.split("\\s+"); // NOI18N
  QStringList inputLine = line.split(" ");
  if (inputLine.length() == 0)
  {
   return "";
  }
  if (inputLine[0]==(Setup::BUILD_REPORT_VERY_DETAILED + "-")
          || inputLine[0]==(Setup::BUILD_REPORT_DETAILED + "-")
          || inputLine[0]==(Setup::BUILD_REPORT_NORMAL + "-")
          || inputLine[0]==(Setup::BUILD_REPORT_MINIMAL + "-"))
  {
   if (Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_MINIMAL))
   {
    if (inputLine[0]==(Setup::BUILD_REPORT_NORMAL + "-")
            || inputLine[0]==(Setup::BUILD_REPORT_DETAILED + "-")
            || inputLine[0]==(Setup::BUILD_REPORT_VERY_DETAILED + "-"))
    {
        return ""; // don't print this line
    }
   }
   if (Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_NORMAL))
   {
    if (inputLine[0]==(Setup::BUILD_REPORT_DETAILED + "-")
            || inputLine[0]==(Setup::BUILD_REPORT_VERY_DETAILED + "-"))
    {
        return ""; // don't print this line
    }
   }
   if (Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_DETAILED))
   {
       if (inputLine[0]==(Setup::BUILD_REPORT_VERY_DETAILED + "-"))
       {
           return ""; // don't print this line
       }
   }
   // do not indent if false
   int start = 0;
   if (indent) {
       // indent lines based on level
       if (inputLine[0]==(Setup::BUILD_REPORT_VERY_DETAILED + "-")) {
           inputLine[0] = "   ";
       } else if (inputLine[0]==(Setup::BUILD_REPORT_DETAILED + "-")) {
           inputLine[0] = "  ";
       } else if (inputLine[0]==(Setup::BUILD_REPORT_NORMAL + "-")) {
           inputLine[0] = " ";
       } else if (inputLine[0]==(Setup::BUILD_REPORT_MINIMAL + "-")) {
           inputLine[0] = "";
       }
   } else {
       start = 1;
   }
   // rebuild line
   QString buf = ""; //new StringBuffer();
   for (int i = start; i < inputLine.length(); i++) {
       buf.append(inputLine[i] + " ");
   }
   // blank line?
   if (buf.length() == 0) {
       return " ";
   }
   return buf/*.toString()*/;
  }
  else
  {
   log->debug("ERROR first characters of build report not valid (" + line + ")");
   return "ERROR " + line; // NOI18N
  }
 }
#if 0
 /**
  * This method uses Desktop which is supported in Java 1.6.
  */
 /*public*/ static void openDesktopEditor(File file) {
     if (!java.awt.Desktop.isDesktopSupported()) {
         log->warn("desktop not supported");
         return;
     }
     java.awt.Desktop desktop = java.awt.Desktop.getDesktop();
     if (desktop.isSupported(java.awt.Desktop.Action.EDIT)) {
         try {
             desktop.edit(file);
         } catch (IOException e) {
             e.printStackTrace();
         }
     } else if (desktop.isSupported(java.awt.Desktop.Action.OPEN)) {
         try {
             desktop.open(file);
         } catch (IOException e) {
             e.printStackTrace();
         }
     } else {
         log->warn("desktop edit or open not supported");
     }
 }
#endif
 /*public*/ /*static*/ QComboBox* TrainPrintUtilities::getPrinterJComboBox() {
     QComboBox* box = new QComboBox();
// TODO:     PrintService[] services = PrintServiceLookup.lookupPrintServices(NULL, NULL);
//     for (PrintService printService : services) {
//         box.addItem(printService.getName());
//     }

     // Set to default printer
//     box.setSelectedItem(getDefaultPrinterName());

     return box;
 }

 /*public*/ /*static*/ QString TrainPrintUtilities::getDefaultPrinterName() {
//     if (PrintServiceLookup.lookupDefaultPrintService() != NULL) {
//         return PrintServiceLookup.lookupDefaultPrintService().getName();
//     }
     return ""; // no default printer specified
 }

}
