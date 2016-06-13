/* Default implementation for class NamedBean */
#include "namedbean.h"
//#ifndef WIN32
//const int NamedBean::UNKNOWN      = 0x01;
//const int NamedBean::INCONSISTENT = 0x08;
//#endif
NamedBean::NamedBean(QObject *parent)
{
 _parent = parent;
 _state = UNKNOWN;
}

NamedBean::NamedBean(QString name, QObject *parent)
{
 _parent = parent;
 _name = name;
 _state = UNKNOWN;
 _systemName = name;
}
NamedBean::NamedBean(const NamedBean & other)
{
 this->_parent = other._parent;
 this->_name = other._name;
 this->_state = other._state;
 this->_systemName = other._systemName;
 this->_userName = other._userName;
}

QString NamedBean::getUserName() { return _userName;}
void NamedBean::setUserName(QString s)
{
 _userName = s;
}
QString NamedBean::getSystemName() { return _systemName;}
QString NamedBean::getDisplayName() { return _displayName;}

void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/)
{

}
void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/, QString /*name*/, const QString /*listenerRef*/)
{

}
void NamedBean::removePropertyChangeListener(PropertyChangeListener */*l*/)
{

}
void NamedBean::updateListenerRef(PropertyChangeListener */*l*/, QString /*newName*/)
{

}
QString NamedBean::getListenerRef(PropertyChangeListener */*l*/)
{
    return "";
}
QList<QString>* NamedBean::getListenerRefs()
{
    //return QStringList();
 return NULL;
}
int NamedBean::getNumPropertyChangeListeners()
{
    return 0;
}
QList<PropertyChangeListener*>* NamedBean::getPropertyChangeListeners(QString /*name*/)
{
    return NULL;
}
void NamedBean::dispose()
{

}
void NamedBean::setState(int s)
{
 _state = s;
}
int NamedBean::getState() { return _state;}
QString NamedBean::getComment() { return _comment;}
void NamedBean::setComment(QString comment)
{
 _comment = comment;
}
void NamedBean::setProperty(QString /*key*/, QVariant /*value*/)
{

}
QVariant NamedBean::getProperty(QString /*key*/)
{
 return QVariant();
}
