#ifndef ANALOGFORMULATESTACTION_H
#define ANALOGFORMULATESTACTION_H

#include <abstractaction.h>

class Logger;
class AnalogFormulaTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AnalogFormulaTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANALOGFORMULATESTACTION_H
