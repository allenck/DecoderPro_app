#ifndef TOKENIZERTESTACTION_H
#define TOKENIZERTESTACTION_H

#include <abstractaction.h>

class TokenizerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit TokenizerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // TOKENIZERTESTACTION_H
