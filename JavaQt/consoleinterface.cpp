#include "consoleinterface.h"

ConsoleInterface::ConsoleInterface(QObject *parent) :
    QObject(parent)
{
}
ConsoleInterface::~ConsoleInterface() {}
/*static*/ ConsoleInterface* ConsoleInterface::_instance = NULL;

/*static*/ ConsoleInterface* ConsoleInterface::instance()
{
 if(_instance == NULL) _instance = new ConsoleInterface();
 return _instance;
}
void ConsoleInterface::sendMessage(QString s, LoggingEvent* evt)
{
 emit message(s, evt);
}
