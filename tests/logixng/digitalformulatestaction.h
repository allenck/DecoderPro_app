#ifndef DIGITALFORMULATESTACTION_H
#define DIGITALFORMULATESTACTION_H

#include <abstractaction.h>

class DigitalFormulaTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalFormulaTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DIGITALFORMULATESTACTION_H
