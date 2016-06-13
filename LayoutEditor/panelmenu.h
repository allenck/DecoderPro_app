#ifndef PANELMENU_H
#define PANELMENU_H
#include <QMenu>
#include "logger.h"
#include "QActionGroup"
#include "liblayouteditor_global.h"

class Editor;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT PanelMenu : public QMenu
{
    Q_OBJECT
public:
   // explicit PanelMenu(QObject *parent = 0);
    static /*public*/ PanelMenu* instance();
    /*public*/ int getNumberOfPanels();
    /*public*/ void deletePanel (Editor* panel);
    /*public*/ void addEditorPanel(/*final*/ Editor* panel);
    /*public*/ void updateEditorPanel (Editor* panel);
    /*public*/ void renameEditorPanel (Editor* panel);
    /*public*/ bool isPanelNameUsed (QString name);
    /*public*/ Editor* getEditorByName (QString name);
    /*public*/ QList<Editor*>* getEditorPanelList();
    /*public*/ QList<LayoutEditor*>* getLayoutEditorPanelList();
    void updatePanelMenu(QMenu* menu);

signals:
    void newThrottleWindow();
public slots:
    void on_panelSelected(QAction* act);
private:
    /*private*/ PanelMenu(QWidget* parent = 0);
    // operational variables
    /*private*/ QMenu* panelsSubMenu;//	= NULL;
    /*private*/ QAction* noPanelsItem;//  = NULL;
    static /*private*/ PanelMenu* thisMenu;// = NULL;
    /*private*/ QList<Editor*>* panelsList;// = new QList<Editor*>();
    Logger* log;
    QActionGroup* actionGroup;
};

#endif // PANELMENU_H
