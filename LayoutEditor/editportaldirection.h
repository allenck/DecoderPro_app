#ifndef EDITPORTALDIRECTION_H
#define EDITPORTALDIRECTION_H
#include "editframe.h"

class ListSelectionEvent;
class PortalList;
class QRadioButton;
class OBlock;
class CircuitBuilder;
class PortalIcon;
class EditPortalDirection : public EditFrame
{
 Q_OBJECT
public:
 //explicit EditPortalDirection(QWidget *parent = 0);
 /*public*/ EditPortalDirection(QString title, CircuitBuilder* parent, OBlock* block);
 /*public*/ QString getClassName();

signals:

public slots:
 /*public*/ void valueChanged(ListSelectionEvent* e = 0);
 /*public*/ void actionPerformed(QString actionCmd);

private:
 /*private:*/ OBlock* _homeBlock;
 /*private:*/ CircuitBuilder* _parent;
 /*private:*/ PortalIcon* _icon;
 /*private:*/ QRadioButton* _toButton;
 /*private:*/ QRadioButton* _fromButton;
 /*private:*/ QRadioButton* _noButton;

 /*private:*/ PortalList* _portalList;
 static int STRUT_SIZE;// = 10;
 static bool _firstInstance;// = true;
 static QPoint _loc;// = null;
 static QSize _dim;// = null;
 /*private:*/ QWidget* makeDoneButtonPanel();
 /*private:*/ QWidget* makePortalPanel();
 /*private:*/ QWidget* makeArrowPanel();
protected:
 /*protected*/ void setPortalIcon(PortalIcon* icon, bool setValue);
 /*protected*/ void closingEvent(bool close);
 /*protected*/ OBlock* getHomeBlock();

 friend class CircuitBuilder;
};

#endif // EDITPORTALDIRECTION_H
