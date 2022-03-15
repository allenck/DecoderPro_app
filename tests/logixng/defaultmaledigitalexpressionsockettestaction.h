#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultMaleDigitalExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalExpressionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;};

#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKETTESTACTION_H
