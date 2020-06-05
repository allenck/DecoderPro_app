#ifndef SIGNALMASTITEMPANEL_H
#define SIGNALMASTITEMPANEL_H
#include "tableitempanel.h"

class ListSelectionEvent;
class SignalMast;
class SignalMastItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit SignalMastItemPanel(QWidget *parent = 0);
    /*public*/ SignalMastItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    void init();
    void init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap);

signals:

public slots:
    void _showIconsButton_clicked();
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);
private:
    SignalMast* _mast;
    /*private*/ NamedIcon* getDragIcon();
    /*private*/ void getIconMap(int row);
    QLabel* _promptLabel = nullptr;
    QWidget* _blurb = nullptr;
    /*private*/ QMap<QString, NamedIcon*>* _iconMastMap = nullptr;

protected:
    /*protected*/ QWidget* instructions();
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);
    /*protected*/ void makeBottomPanel(ActionListener* doneAction);
    /*protected*/ JLabel* getDragger(DataFlavor* flavor, NamedIcon* icon);
    /*protected*/ void setFamily(QString family);
    /*protected*/ void showIcons();
    /*protected*/ void hideIcons();

friend class SMIconDragJLabel;
};
    /*protected*/ class SMIconDragJLabel : public DragJLabel
{
     Q_OBJECT
     SignalMastItemPanel* self;
        public:
        /*public*/ SMIconDragJLabel(DataFlavor* flavor, NamedIcon* icon, SignalMastItemPanel* self);
     /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
     QByteArray mimeData();
private:
     Logger* log;
protected:
     /*protected*/ bool okToDrag();

};

#endif // SIGNALMASTITEMPANEL_H
