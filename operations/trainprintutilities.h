#ifndef TRAINPRINTUTILITIES_H
#define TRAINPRINTUTILITIES_H

#include <QString>
#include <QObject>

class QComboBox;
class Logger;
class File;
namespace Operations
{
 class TrainPrintUtilities : public QObject
 {
  Q_OBJECT
 public:
  //TrainPrintUtilities();
  /*public*/ static void printReport(File* file, QString name, bool isPreview, QString fontName,
          bool isBuildReport, QString logoURL, QString printerName, QString orientation, int fontSize);
  /*public*/ static QString getDefaultPrinterName();
  /*public*/ static QComboBox* getPrinterJComboBox();
  /*public*/ static void editReport(File* file, QString name);

 private:
  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  static /*final*/ char HORIZONTAL_LINE_SEPARATOR;// = '-'; // NOI18N
  static /*final*/ char VERTICAL_LINE_SEPARATOR;// = '|'; // NOI18N
  static /*final*/ char SPACE;// = ' ';
  /*private*/ static QString filterBuildReport(QString line, bool indent);
  Logger* log;

 };
}
#endif // TRAINPRINTUTILITIES_H
