#ifndef DEFAULTLOGIXNGINITIALIZATIONMANAGER_H
#define DEFAULTLOGIXNGINITIALIZATIONMANAGER_H

#include "logixng_initializationmanager.h"
#include "logixng.h"
#include <QObject>

class DefaultLogixNGInitializationManager : public QObject, public LogixNG_InitializationManager
{
  Q_OBJECT
 public:
  DefaultLogixNGInitializationManager(QObject* parent = nullptr) : QObject(parent) {}
  /*public*/  void add(LogixNG* logixNG)override;
  /*public*/  void _delete(LogixNG* logixNG)override;
  /*public*/  void _delete(int index)override;
  /*public*/  void moveUp(int index)override;
  /*public*/  void moveDown(int index)override;
  /*public*/  QList<LogixNG*> getList()override;
  /*public*/  void printTree(QLocale locale, PrintWriter* writer, QString indent)override;

   private:
  /*private*/ /*final*/ QList<LogixNG*> initLogixNGs = QList<LogixNG*>();

};

#endif // DEFAULTLOGIXNGINITIALIZATIONMANAGER_H
