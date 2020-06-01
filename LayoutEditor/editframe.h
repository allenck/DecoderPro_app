#ifndef EDITFRAME_H
#define EDITFRAME_H
#include "jmrijframe.h"

class OBlock;
class CircuitBuilder;
class EditFrame : public JmriJFrame
{
 Q_OBJECT
public:
 EditFrame();
 /*public*/ EditFrame(QString title, CircuitBuilder* parent, OBlock* block);

private:
 static int STRUT_SIZE;// = 10;
 static QPoint _loc;// = new Point(-1, -1);
 static QSize _dim;// = new Dimension();
 /*private*/ static void storeLocDim(/*@Nonnull*/ QPoint location, /*@Nonnull*/ QSize size);

protected:
 /*protected*/ OBlock* _homeBlock;
 /*protected*/ /*final*/ CircuitBuilder* _parent;
 /*protected*/ bool _canEdit = true;
 /*protected*/ bool _suppressWarnings = false;

 virtual     /*protected*/ /*abstract*/ JPanel* makeContentPanel(){}
 /*protected*/ JPanel* makeDoneButtonPanel();
 /*protected*/ void checkCircuitIcons(QString editType);
 /*protected*/ void clearListSelection();
 /*protected*/ bool canEdit();
 /*protected*/ bool closingEvent(bool close, QString msg);
  virtual /*protected*/ /*abstract*/ void closingEvent(bool close) {}

 friend class CircuitBuilder;
 friend class PortalListModel;
 friend class EditSignalFrame;
};

#endif // EDITFRAME_H
