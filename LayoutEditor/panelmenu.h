#ifndef PANELMENU_H
#define PANELMENU_H
#include <QMenu>
#include "logger.h"
#include "QActionGroup"
#include "liblayouteditor_global.h"
#include "actionlistener.h"

class Editor;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT PanelMenu : public QMenu
{
    Q_OBJECT
public:
    /*public*/ int getNumberOfPanels();
    /*public*/ void deletePanel (Editor* panel);
    /*public*/ void addEditorPanel(/*final*/ Editor* panel);
    /*public*/ void updateEditorPanel (Editor* panel);
    /*public*/ void renameEditorPanel (Editor* panel);
    /*public*/ bool isPanelNameUsed (QString name);
    /*public*/ Editor* getEditorByName (QString name);
    /*public*/ QList<Editor*>* getEditorPanelList();
    /*public*/ QList<LayoutEditor*>* getLayoutEditorPanelList();
    //void updatePanelMenu(QMenu* menu);

signals:
    void newThrottleWindow();
public slots:
    void on_panelSelected(QAction* act);
    void menuSelected();
private:
    // operational variables
    /*private*/ QMenu* panelsSubMenu;//	= NULL;
    /*private*/ QAction* noPanelsItem;//  = NULL;
    /*private*/ QList<Editor*>* panelsList;// = new QList<Editor*>();
    Logger* log;
    QActionGroup* actionGroup;
protected:
    explicit PanelMenu(QWidget *parent = nullptr);

    friend class DefaultInstanceInitializer;
    friend class DefaultCabSignalTest;
};

class PanelActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 Editor* panel;
 PanelMenu* pm;
public:
  PanelActionListener(Editor* panel, PanelMenu* pm);
  QObject* self() override {return (QObject*)this;}

public slots:
  void actionPerformed();
};

#endif // PANELMENU_H
