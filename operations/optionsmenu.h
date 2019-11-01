#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H
#include "logger.h"
#include <QMenu>
#include "actionevent.h"


class DispatcherFrame;
class OptionsMenu : public QMenu
{
public:
 OptionsMenu(DispatcherFrame* f, QWidget*parent = 0);
 /*public*/ void initializeMenu();

private slots:
  /*private*/ void handleAutoDispatch(ActionEvent* e =0);
  /*private*/ void handleAutoTurnouts(ActionEvent* e =0);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("OptionsMenu");
 // Option menu items
 /*private*/ QAction* autoDispatchItem;// = null;
 /*private*/ QAction* autoTurnoutsItem ;//= null;

protected:
 /*protected*/ DispatcherFrame* dispatcher;// = null;

};

#endif // OPTIONSMENU_H
