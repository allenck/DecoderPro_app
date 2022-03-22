#ifndef RECURSIVEDESCENTPARSERTESTACTION_H
#define RECURSIVEDESCENTPARSERTESTACTION_H

#include <abstractaction.h>

class RecursiveDescentParserTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit RecursiveDescentParserTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();

 private:
  static Logger* log;
};

#endif // RECURSIVEDESCENTPARSERTESTACTION_H
