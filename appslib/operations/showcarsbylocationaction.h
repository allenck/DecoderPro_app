#ifndef SHOWCARSBYLOCATIONACTION_H
#define SHOWCARSBYLOCATIONACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ShowCarsByLocationAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ ShowCarsByLocationAction(QString s, QObject* parent);
  /*public*/ ShowCarsByLocationAction(bool showAllCars, QString locationName, QString trackName, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  void common();
  bool showAllCars;// = true;
  QString locationName;// = null;
  QString trackName;// = null;

 };
}
#endif // SHOWCARSBYLOCATIONACTION_H
