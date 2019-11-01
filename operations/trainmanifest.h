#ifndef TRAINMANIFEST_H
#define TRAINMANIFEST_H
#include "traincommon.h"

class Logger;
namespace Operations
{
 class TrainManifest : public TrainCommon
 {
 public:
  TrainManifest(Train* train, QObject* parent=0);
 private:
  QString messageFormatText;// = ""; // the text being formated in case there's an exception
  Logger* log;
  /*private*/ void newLine(PrintWriter* file, QString string);
  /*private*/ void newLine(PrintWriter* file);
  /*private*/ void printChange(PrintWriter* fileOut, RouteLocation* rl, Train* train, int legOptions);

 };
}
#endif // TRAINMANIFEST_H
