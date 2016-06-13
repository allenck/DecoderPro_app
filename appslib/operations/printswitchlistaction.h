#ifndef PRINTSWITCHLISTACTION_H
#define PRINTSWITCHLISTACTION_H

#include "abstractaction.h"
namespace Operations
{
 class Location;
 class PrintSwitchListAction : public AbstractAction
 {
 public:
  /*public*/ PrintSwitchListAction(QString actionName, Location* location, bool isPreview, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  Location* location;
  bool isPreview;

 };
}
#endif // PRINTSWITCHLISTACTION_H
