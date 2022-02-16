#ifndef DEFAULTDIGITALACTIONMANAGERXML_H
#define DEFAULTDIGITALACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>

class DefaultDigitalActionManagerXml : public AbstractManagerXml
{
 public:
  explicit DefaultDigitalActionManagerXml(QObject *parent = nullptr);
 private:
  static Logger* log;
};

#endif // DEFAULTDIGITALACTIONMANAGERXML_H
