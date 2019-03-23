#ifndef JMRICLIENTCOMPONENTFACTORY_H
#define JMRICLIENTCOMPONENTFACTORY_H
#include "componentfactory.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientComponentFactory : public ComponentFactory
{
 Q_OBJECT


public:
 JMRIClientComponentFactory(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QMenu* getMenu(QWidget *frame);

 private:
 JMRIClientSystemConnectionMemo* memo;
 };


#endif // JMRICLIENTCOMPONENTFACTORY_H
