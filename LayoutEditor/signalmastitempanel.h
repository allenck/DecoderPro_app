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
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor);
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
        /*public*/ SMIconDragJLabel(DataFlavor* flavor, SignalMastItemPanel* self);
     /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
     QByteArray mimeData();
private:
     Logger* log;
};

#endif // SIGNALMASTITEMPANEL_H
