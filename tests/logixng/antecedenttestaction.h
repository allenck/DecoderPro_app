#ifndef ANTECEDENTTESTACTION_H
#define ANTECEDENTTESTACTION_H

#include <abstractaction.h>

class AntecedentTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AntecedentTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANTECEDENTTESTACTION_H
