#ifndef EDITPORTALFRAME_H
#define EDITPORTALFRAME_H
#include "editframe.h"
#include <QListView>
#include "abstractlistmodel.h"
#include "dragjlabel.h"

class ListSelectionEvent;
class PortalList;
class Positionable;
class Portal;
class PortalIcon;
class JTextField;
class PortalListModel;
class CircuitBuilder;
class OBlock;
class EditPortalFrame : public EditFrame
{
    Q_OBJECT
public:
    //explicit EditPortalFrame(QWidget *parent = 0);
    /*public*/ EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block, Portal* portal, PortalIcon* icon);
    /*public*/ EditPortalFrame(QString _title, CircuitBuilder* parent, OBlock* block);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;
    /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void valueChanged(ListSelectionEvent* e);

private:
    /*private*/ void common(QString title, CircuitBuilder* parent, OBlock* block);

    /*private*/ OBlock* _homeBlock;
    /*private*/ CircuitBuilder* _parent;
    /*private*/ OBlock* _adjacentBlock;

    /*private*/ PortalList*       _portalList;
    /*private*/ PortalListModel* _portalListModel;
    /*private*/ QString _currentPortalName;			// name of last portal Icon made

    /*private*/ JTextField*  _portalName;// = new JTextField();
    Portal* _currentPortal;
    /*private*/ void hightLightIcon(Portal* portal);
    /*private*/ bool askForNameChange();
    JPanel* _dndPanel = nullptr;

 Logger* log;
 /*private*/ void changePortalName();
 /*private*/ void deletePortal();
 /*private*/ void setName(Portal* portal, QString name);
 /*private*/ QString showIntersectMessage(OBlock* block, PortalIcon* icon, bool moved);
 /*private*/ OBlock* findAdjacentBlock(PortalIcon* icon);

protected:
 /*protected*/ void closingEvent(bool close);
 /*protected*/ QString checkPortalIconForUpdate(PortalIcon* icon, bool moved);
 /*protected*/ JPanel* makeContentPanel();
 /*protected*/ void clearListSelection();
 /*protected*/ void setSelected(PortalIcon* icon);
 /*protected*/ QWidget* makeDndIconPanel();

 friend class CircuitBuilder;
 friend class PortalListModel;
 friend class EPIconDragJLabel;
};
#if 0
class PortalListModel : public AbstractListModel {
 Q_OBJECT
 EditPortalFrame* frame;
public:
 PortalListModel(EditPortalFrame* frame) { this->frame = frame;}
    /*public*/ int getSize();
    /*public*/ QObject* getElementAt(int index);
    /*public*/ void dataChange();
};
/*public*/ class IconDragJLabel : public DragJLabel {
Q_OBJECT
 EditPortalFrame *frame;
 bool addSecondIcon;
public:
    /*public*/ IconDragJLabel(DataFlavor* flavor, EditPortalFrame *frame) ;
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) ;
protected:
 /*protected*/ bool okToDrag();

};
#endif

class EPIconDragJLabel : public DragJLabel
{
 Q_OBJECT
 bool addSecondIcon = false;
 EditPortalFrame* frame;
public:
 /*public*/ EPIconDragJLabel(DataFlavor* flavor, EditPortalFrame* frame);
 /*public*/ QObject *getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException, IOException);

protected:
 /*protected*/ bool okToDrag();
};
#endif // EDITPORTALFRAME_H
