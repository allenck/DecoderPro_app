#ifndef PRINTLOCATIONSBYCARTYPESACTION_H
#define PRINTLOCATIONSBYCARTYPESACTION_H

#include "abstractaction.h"

class Logger;
class JFrame;
class HardcopyWriter;
namespace Operations
{
 class LocationManager;
 class PrintLocationsByCarTypesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintLocationsByCarTypesAction(QString actionName, JFrame* frame, bool preview,
          QWidget* pWho);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  Logger* log;
  LocationManager* locManager;// = LocationManager.instance();

  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  static /*final*/ QString TAB;// = "\t"; // NOI18N
  /**
   * Frame hosting the printing
   */
  JFrame* mFrame;
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  HardcopyWriter* writer;

 };
}
#endif // PRINTLOCATIONSBYCARTYPESACTION_H
