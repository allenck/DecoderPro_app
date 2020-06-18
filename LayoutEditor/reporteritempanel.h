#ifndef REPORTERITEMPANEL_H
#define REPORTERITEMPANEL_H
#include "tableitempanel.h"
#include "dragjcomponent.h"

class RIconDragJComponent;
class ListSelectionEvent;
class ReporterIcon;
class ReporterItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit ReporterItemPanel(QWidget *parent = 0);
    /*public*/ ReporterItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent);
    /*public*/ void init();
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);

signals:

public slots:
 private:
    ReporterIcon* _reporter;
    Logger* log;
protected:
    /*protected*/ QWidget* instructions();
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ void makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString displayKey);
    /*protected*/ RIconDragJComponent* getDragger(DataFlavor* flavor);
    /*protected*/ JPanel* makeItemButtonPanel();
    
    friend class RIconDragJComponent;
};
/*protected*/ class RIconDragJComponent : public DragJComponent {
Q_OBJECT
    ReporterItemPanel* self;
public:
    /*public*/ RIconDragJComponent(DataFlavor* flavor, QSize dim, ReporterItemPanel* self);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    QByteArray mimeData();
};

#endif // REPORTERITEMPANEL_H
