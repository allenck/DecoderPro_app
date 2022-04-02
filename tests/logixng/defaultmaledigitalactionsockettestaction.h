#ifndef DEFAULTMALEDIGITALACTIONSOCKETTESTACTION_H
#define DEFAULTMALEDIGITALACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultMaleDigitalActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTMALEDIGITALACTIONSOCKETTESTACTION_H
