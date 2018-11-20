#ifndef JLAYEREDPANE_H
#define JLAYEREDPANE_H

#include <QFrame>
#include "exceptions.h"


class JLayeredPane : public QFrame
{
 Q_OBJECT
public:
 explicit JLayeredPane(QWidget *parent = nullptr);
 /*public*/ /*final*/ static int DEFAULT_LAYER;// = new Integer(0);
/** Convenience object defining the Palette layer. Equivalent to new Integer(100).*/
 /*public*/ /*final*/ static int PALETTE_LAYER;// = new Integer(100);
/** Convenience object defining the Modal layer. Equivalent to new Integer(200).*/
 /*public*/ /*final*/ static int MODAL_LAYER;// = new Integer(200);
/** Convenience object defining the Popup layer. Equivalent to new Integer(300).*/
 /*public*/ /*final*/ static int POPUP_LAYER;// = new Integer(300);
/** Convenience object defining the Drag layer. Equivalent to new Integer(400).*/
 /*public*/ /*final*/ static int DRAG_LAYER;// = new Integer(400);
 /*public*/ /*final*/ static int FRAME_CONTENT_LAYER;// = new Integer(-30000);
 /*public*/ /*final*/ static QString LAYER_PROPERTY;// = "layeredContainerLayer";

 /*public*/ void remove(int index);
 /*public*/ QWidget* getComponent(int n);
 /*public*/ void removeAll();
 /*public*/ QList<QWidget*> getComponents();
 /*public*/ static int s_getLayer(QWidget* c);
 /*public*/ void setLayer(QWidget* c, int layer);
 /*public*/ void setLayer(QWidget* c, int layer, int position);
 /*public*/ int getLayer(QWidget* c);
 /*public*/ int getPosition(QWidget* c);
 /*public*/ int getIndexOf(QWidget* c);
 /*public*/ void moveToFront(QWidget* c);
 /*public*/ void moveToBack(QWidget* c);
 /*public*/ void setPosition(QWidget* c, int position);

signals:

public slots:

private:
 /*private*/ QHash<QWidget*,int> componentToLayer;
 /*private*/ bool optimizedDrawingPossible = true;
 QList<QWidget*> components;
 /*private*/ int insertIndexForLayer(QWidget* comp, int layer, int position);
 /*private*/ int getComponentCount();

protected:
 /*protected*/ QHash<QWidget*,int> getComponentToLayer();
 /*protected*/ int getObjectForLayer(int layer);
 /*protected*/ int insertIndexForLayer(int layer, int position);

};

#endif // JLAYEREDPANE_H
