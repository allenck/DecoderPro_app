#ifndef STRINGMANYTESTACTION_H
#define STRINGMANYTESTACTION_H

#include <abstractaction.h>

class StringManyTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit StringManyTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // STRINGMANYTESTACTION_H
