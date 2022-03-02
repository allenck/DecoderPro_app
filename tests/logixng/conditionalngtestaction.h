#ifndef CONDITIONALNGTESTACTION_H
#define CONDITIONALNGTESTACTION_H

#include <abstractaction.h>

class ConditionalNGTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit ConditionalNGTestAction(QObject *parent = nullptr);

 public slots:
  void actionPerformed();

 private:
  static Logger* log;
};

#endif // CONDITIONALNGTESTACTION_H
