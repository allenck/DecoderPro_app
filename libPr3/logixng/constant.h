#ifndef CONSTANT_H
#define CONSTANT_H
#include <QtCore>

class Constant : public QObject
{
  Q_OBJECT
 public:
  Constant(QString m, QString name, QVariant value);
  /*public*/  QString getModule();
  /*public*/  QString getName();
  /*public*/  QVariant getValue();

 private:
  /*private*/ /*final*/ QString _module;
  /*private*/ /*final*/ QString _name;
  /*private*/ /*final*/  QVariant _value;

};

#endif // CONSTANT_H
