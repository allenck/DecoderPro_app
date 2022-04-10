#ifndef STRINGFORMULATESTACTION_H
#define STRINGFORMULATESTACTION_H

#include <abstractaction.h>

class StringFormulaTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit StringFormulaTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // STRINGFORMULATESTACTION_H
