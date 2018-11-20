#ifndef DRAGJLABEL_H
#define DRAGJLABEL_H
#include "jlabel.h"
#include "exceptions.h"
#include "logger.h"
#include "namedicon.h"

class DataFlavor;
class DragJLabel : public QLabel
{
    Q_OBJECT
public:
    //explicit DragJLabel(QWidget *parent = 0);
    /*public*/ DragJLabel(DataFlavor* flavor, QWidget *parent = 0);
    ~DragJLabel();
    /*public*/ QList<DataFlavor*> getTransferDataFlavors();
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
    /*public*/ QVariant getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
//    void dragEnterEvent(QDragEnterEvent *);
//    void dragMoveEvent(QDragMoveEvent *);
    void mousePressEvent(QMouseEvent *e);
    virtual QString mimeData();
    void setIcon(NamedIcon* icon);
    NamedIcon* getIcon();
    void setName(QString name);

signals:
 void showPopUp(NamedIcon*);

public slots:
private:
  Logger* log;
  NamedIcon* icon;
  QString name;

protected:
    /*protected*/ DataFlavor* _dataFlavor;
friend class IndicatorDragJLabel;
};

#endif // DRAGJLABEL_H
