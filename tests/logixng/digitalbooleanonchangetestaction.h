#ifndef DIGITALBOOLEANONCHANGETESTACTION_H
#define DIGITALBOOLEANONCHANGETESTACTION_H

#include <abstractaction.h>

class DigitalBooleanOnChangeTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalBooleanOnChangeTestAction(QObject *parent = nullptr);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DIGITALBOOLEANONCHANGETESTACTION_H
