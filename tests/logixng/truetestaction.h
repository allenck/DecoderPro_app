#ifndef TRUETESTACTION_H
#define TRUETESTACTION_H

#include <abstractaction.h>
#include <QObject>

class TrueTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit TrueTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // TRUETESTACTION_H
