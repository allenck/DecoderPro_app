#include "propertychangelistener.h"

PropertyChangeListener::PropertyChangeListener(QObject *parent) :
    QObject(parent)
{
 //handleChange = NULL;

}
//@Override
void PropertyChangeListener::propertyChange(PropertyChangeEvent* e) {
 //qDebug() << tr("Property change received");
}
