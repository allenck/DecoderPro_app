#ifndef SIGNALHEADITEMPANEL_H
#define SIGNNALHEADITEMPANEL_H
#include "tableitempanel.h"
#include <QLabel>
#include "dragjlabel.h"

class SignalHeadItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit SignalHeadItemPanel(QWidget *parent = 0);
    /*public*/ SignalHeadItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    /*public*/ void valueChanged(/*ListSelectionEvent e*/);

signals:

public slots:
private:
    Logger* log;
protected:
    /*protected*/ QWidget* initTablePanel(PickListModel* model, Editor* editor);
    /*protected*/ void makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString displayKey);
    /*protected*/ void addIconsToPanel(QHash<QString, NamedIcon*>* allIconsMap);
    /*protected*/ QHash<QString, NamedIcon*>* getFilteredIconMap(QHash<QString, NamedIcon*>* allIconsMap);
//    /*protected*/ QLabel* getDragger(DataFlavor flavor, QHash<QString, NamedIcon*>* map);
    /*protected*/ void showIcons();
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QHash<QString, NamedIcon*>* map);
friend class SHIconDragJLabel;
};
/*protected*/ class SHIconDragJLabel : public DragJLabel {
    QHash <QString, NamedIcon*>* iconMap;
    Logger* log;
    SignalHeadItemPanel* self;
 public:
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
    /*public*/ SHIconDragJLabel(DataFlavor* flavor, QHash <QString, NamedIcon*>* map, SignalHeadItemPanel* self);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    QString mimeData();
};

#endif // SIGNNALHEADITEMPANEL_H
