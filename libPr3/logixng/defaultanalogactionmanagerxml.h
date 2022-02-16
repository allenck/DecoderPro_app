#ifndef DEFAULTANALOGACTIONMANAGERXML_H
#define DEFAULTANALOGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>

class DefaultAnalogActionManagerXml : public AbstractManagerXml
{
 public:
  explicit DefaultAnalogActionManagerXml(QObject *parent = nullptr);

 private:
  static Logger* log;
};

#endif // DEFAULTANALOGACTIONMANAGERXML_H
