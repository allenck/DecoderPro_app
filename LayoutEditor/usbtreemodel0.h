#ifndef USBTREEMODEL_H
#define USBTREEMODEL_H
#include "defaulttreemodel.h"
#include <QVector>
#include "controller.h"
#include "usb_bus.h"

class Logger;
class Controller;
class DefaultMutableTreeNode;
class SwingPropertyChangeSupport;
namespace Usb
{
class UsbTreeModel0 : public DefaultTreeModel
{
public:
 DefaultMutableTreeNode* insertNode(DefaultMutableTreeNode* pChild, DefaultMutableTreeNode* pParent);
 static /*public*/ UsbTreeModel0* instance();
 /*public*/ QVector<Usb::Controller*>* controllers();


private:
 SwingPropertyChangeSupport* pcs;// = new SwingPropertyChangeSupport(this, nullptr);
 /*private*/ UsbTreeModel0(QObject* parent = 0);
 DefaultMutableTreeNode* dRoot;
 static /*private*/ UsbTreeModel0* instanceValue;// = NULL;
 // we build an array of USB controllers here
 // note they might not arrive for a while
 QVector<Usb::Controller*>* ca;
 Logger* log;
 bool loadSystem();
 QHash<qint16,DeviceFilter> devHash;

 friend class TreePanel;
};
//const QDBusArgument  &operator>>(const QDBusArgument &argument, DeviceFilter &f);
}
#endif // USBTREEMODEL_H
