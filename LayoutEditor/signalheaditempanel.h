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
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);
    /*protected*/ void addIconsToPanel(QMap<QString, NamedIcon*>* allIconsMap);
    /*protected*/ QMap<QString, NamedIcon*>* getFilteredIconMap(QMap<QString, NamedIcon *> *allIconsMap);
    /*protected*/ void showIcons();
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon) override;

friend class SHIconDragJLabel;
friend class SignalHeadIconDialog;
};

/*protected*/ class SHIconDragJLabel : public DragJLabel {
    QMap <QString, NamedIcon*>* iconMap;
    Logger* log;
    SignalHeadItemPanel* self;
 public:
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
    QByteArray mimeData();
    /*public*/ SHIconDragJLabel(DataFlavor* flavor, QMap <QString, NamedIcon*>* map, SignalHeadItemPanel* self);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);


};

#endif // SIGNNALHEADITEMPANEL_H
