#ifndef DEFAULTFEMALEDIGITALACTIONSOCKETTESTACTION_H
#define DEFAULTFEMALEDIGITALACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultFemaleDigitalActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleDigitalActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTFEMALEDIGITALACTIONSOCKETTESTACTION_H
