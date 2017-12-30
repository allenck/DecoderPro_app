#ifndef USBTREEMODEL_H
#define USBTREEMODEL_H
#include "defaulttreemodel1.h"
#include "usb_device.h"

class UsbTreeItem : public DefaultTreeItem
{
public:
 UsbTreeItem(const QList<QVariant> &data, DeviceFilter  f, DefaultTreeItem *parent);
 bool removeChild(DefaultTreeItem *);
 void clear();
};

class TreeSelectionEvent;
class Logger;
class JTextArea;
class Usb_Bus;
class UsbTreeModel : public DefaultTreeModel1
{
 Q_OBJECT
public:
 //UsbTreeModel();
 /*public*/ UsbTreeModel(Usb_Bus* rootBus, JTextArea* textArea, QObject* parent = 0);
// /*public*/ QObject* getRoot();
#if 0
 /*public*/ QObject* getChild(QObject* parent, int index);
 /*public*/ int getChildCount(QObject* parent);
 /*public*/ bool isLeaf(QObject* node) ;
 /*public*/ void valueForPathChanged(TreePath* path, QObject* newValue);
 /*public*/ int getIndexOfChild(QObject* parent, QObject* child);
 /*public*/ void addTreeModelListener(TreeModelListener* l);
 /*public*/ void removeTreeModelListener(TreeModelListener* l) ;
 /*public*/ void valueChanged(TreeSelectionEvent* e) ;
#endif
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
 /*public*/ void reload();
 void deviceChange(uchar bus, uchar address, bool bAdded);

private:
 /*private*/ Usb_Bus* rootBus;
 //DefaultTreeItem* rootItem;
 /*private*/ static /*final*/ QString USB_ROOT;// = "USB";
 /*private*/ JTextArea* textArea;
// /*private*/ Vector<TreeModelListener> treeModelListeners;
 Logger* log;
 /*private*/ int addChildren(UsbTreeItem* node);
// /*private*/ int columnCount(const QModelIndex &parent) const;
 static QHash<int, UsbTreeItem*>* itemHash;

#if 0
 /*private*/ QString extraDescriptorToString(QVector<quint8> extra);

protected:
 /*protected*/ void fireTreeStructureChanged(Usb_Bus* newRootBus);
#endif
friend class UsbTreeItem;
};


#endif // USBTREEMODEL_H
