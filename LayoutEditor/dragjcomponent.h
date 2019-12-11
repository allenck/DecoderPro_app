#ifndef DRAGJCOMPONENT_H
#define DRAGJCOMPONENT_H

#include <QWidget>

class DataFlavor;
class DragJComponent : public QWidget
{
    Q_OBJECT
public:
    //explicit DragJComponent(QWidget *parent = 0);
    /*public*/ DragJComponent(DataFlavor* flavor, QSize dim, QWidget *parent);
    void mousePressEvent(QMouseEvent *);
    //void mouseMoveEvent(QMouseEvent *);
    virtual QByteArray mimeData() { QByteArray();}
    /*public*/ QList<DataFlavor*> getTransferDataFlavors();
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);

signals:

public slots:
private:
    DataFlavor* _dataFlavor;
friend class RIconDragJComponent;
friend class MemoryItemPanel;
friend class MemoryIconDragJComponent;
};

#endif // DRAGJCOMPONENT_H
