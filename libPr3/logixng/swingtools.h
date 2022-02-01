#ifndef SWINGTOOLS_H
#define SWINGTOOLS_H

#include <QObject>
#include "swingconfiguratorinterface.h"

class Logger;
class SwingTools : public QObject
{
  Q_OBJECT
 public:
  explicit SwingTools(QObject *parent = nullptr);
  /*public*/  static QString adapterNameForObject(QObject* o);
  /*public*/  static QString adapterNameForClass(QString c);
  static /*public*/  SwingConfiguratorInterface* getSwingConfiguratorForObject(QObject* object);
  static /*public*/  SwingConfiguratorInterface* getSwingConfiguratorForClass(Class* clazz);

 signals:

   private:
   static Logger* log;
};

#endif // SWINGTOOLS_H
