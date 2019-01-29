#ifndef TEXTITEMPANEL_H
#define TEXTITEMPANEL_H
#include "itempanel.h"
#include "positionablelabel.h"

class DataFlavor;
class ItemPalette;
class DecoratorPanel;
class TextItemPanel : public ItemPanel
{
    Q_OBJECT
public:
    //explicit TextItemPanel(QWidget *parent = 0);
    /*public*/ TextItemPanel(ItemPalette* parentFrame, QString  type, Editor* editor, QWidget *parent);
    /*public*/ void init();
    /*public*/ void updateAttributes(PositionableLabel* l);
    /*public*/ void closeDialogs();

signals:

public slots:
private:
    DecoratorPanel* _decorator;
    static Logger* log;
protected:
    /*protected*/ void updateBackground0(BufferedImage* im);
    /*protected*/ void setPreviewBg(int index);
    /*protected*/ QWidget *makeDoneButtonPanel(ActionListener* doneAction);
    /*protected*/ void setEditor(Editor* ed);


};
/**
 * Export a Positionable item from panel.
 */
class DragDecoratorLabel : public PositionableLabel // implements DragGestureListener, DragSourceListener, Transferable
{
 Q_OBJECT
    DataFlavor* dataFlavor;
    TextItemPanel* textItemPanel;
public:
    /*public*/ DragDecoratorLabel(QString s, Editor* editor,TextItemPanel* textItemPanel);
//    /*public*/ void dragGestureRecognized(DragGestureEvent e);
#if 0
    /*public*/ void dragDropEnd(QDropEvent e) ;
    /*public*/ void dragEnter(QDragEnterEvent e);
    /*public*/ void dragExit(QDragLeaveEvent e);
    /*public*/ void dragOver(QDragMoveEvent e);
    /*public*/ void dropActionChanged(QDropEvent e);
    /*public*/ QList<DataFlavor*> getTransferDataFlavors();
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException, IOException) ;
#endif
};

#endif // TEXTITEMPANEL_H
