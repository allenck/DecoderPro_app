#ifndef PRINTROUTEACTION_H
#define PRINTROUTEACTION_H

#include "abstractaction.h"
#include "jframe.h"

class HardcopyWriter;
namespace Operations
{
 class Route;
 class PrintRouteAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintRouteAction(bool isPreview, Route* route, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;

 private:
  /*private*/ QString truncate(QString string);
  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  static /*final*/ QString TAB;// = "\t"; // NOI18N
  /*private*/ static /*final*/ int MAX_NAME_LENGTH;// = Control.max_len_string_location_name - 5;
  /**
   * Frame hosting the printing
   */
  JFrame* mFrame;// = new JFrame();
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  Route* route;
 protected:
  /*protected*/ void printRoute(HardcopyWriter* writer, Route* route);
 friend class PrintRoutesAction;
 };
}
#endif // PRINTROUTEACTION_H
