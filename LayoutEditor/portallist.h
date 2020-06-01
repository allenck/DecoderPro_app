#ifndef PORTALLISTMODEL_H
#define PORTALLISTMODEL_H
#include "jlist.h"
#include "abstractlistmodel.h"
#include "vptr.h"

class PropertyChangeEvent;
class Portal;
class PortalListModel;
class Logger;
class OBlock;
class EditFrame;
class PortalList : public JList
{
 Q_OBJECT
public:
 PortalList(QObject* parent = nullptr);
 PortalList(OBlock* block, EditFrame* parent);
 void dataChange();

private:
 static Logger* log;
 /*private*/ PortalListModel* _portalListModel;
  friend class EditPortalFrame;
  friend class PortalListModel;
};

#if 1
/*static*/ class PortalListModel : public AbstractListModel/*<Portal>*/ //implements PropertyChangeListener
{
 Q_OBJECT
    OBlock* _homeBlock;
    /*private*/ EditFrame* _parent;
    QList<Portal*> _list = QList<Portal*> ();
public:
    PortalListModel(OBlock* block, EditFrame* parent);
    /*public*/ int getSize() const;
    /*public*/ QVariant getElementAt(int index) const;
    /*public*/ void dataChange();
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    /*private*/ void makeList();
    static Logger* log;
    friend class EditPortalFrame;
friend class IconDragJLabel;
};
#endif
#endif // PORTALLISTMODEL_H
