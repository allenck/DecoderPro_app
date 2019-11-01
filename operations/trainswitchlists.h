#ifndef TRAINSWITCHLISTS_H
#define TRAINSWITCHLISTS_H

#include "traincommon.h"

namespace Operations
{
 class TrainManager;
 class TrainSwitchLists : public TrainCommon
 {
  Q_OBJECT
 public:
  TrainSwitchLists(QObject* parent = 0);
  /*public*/ void buildSwitchList(Location* location);
  /*public*/ void printSwitchList(Location* location, bool isPreview);

 private:
  TrainManager* trainManager;// = TrainManager.instance();
  /*private*/ static /*final*/ const char FORM_FEED;// = '\f';
  /*private*/ static /*final*/ bool IS_PRINT_HEADER;// = true;
  QString messageFormatText;// = ""; // the text being formated in case there's an exception
  Logger* log;
 protected:
  /*protected*/ void newLine(PrintWriter* file, QString string);
  /*protected*/ void newLine(PrintWriter* file);

 };
}
#endif // TRAINSWITCHLISTS_H
