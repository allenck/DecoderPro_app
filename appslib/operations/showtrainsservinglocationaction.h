#ifndef SHOWTRAINSSERVINGLOCATIONACTION_H
#define SHOWTRAINSSERVINGLOCATIONACTION_H

#include "abstractaction.h"
namespace Operations
{
 class Location;
 class Track;
 class ShowTrainsServingLocationFrame;
 class ShowTrainsServingLocationAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ ShowTrainsServingLocationAction(QString title, Location* location, Track* track, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  Location* _location;
  Track* _track;
  ShowTrainsServingLocationFrame* _frame;

 };
}
#endif // SHOWTRAINSSERVINGLOCATIONACTION_H
