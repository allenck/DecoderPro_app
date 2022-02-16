#ifndef DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
#define DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultDigitalBooleanActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultDigitalBooleanActionManagerXml(QObject *parent = nullptr);

 private:
  static Logger* log;
};

#endif // DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
