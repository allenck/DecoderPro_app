#ifndef DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultFemaleDigitalExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT

 public:
  explicit DefaultFemaleDigitalExpressionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;};

#endif // DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTESTACTION_H
