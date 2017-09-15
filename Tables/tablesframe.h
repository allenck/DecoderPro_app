#ifndef TABLEFRAME_H
#define TABLEFRAME_H

#include <QMainWindow>
#include "turnoutwidget.h"
#include "sensorwidget.h"
#include <QListWidgetItem>
#include "reporterwidget.h"
#include "memorywidget.h"
#include "blockwidget.h"
#include "idtagswidget.h"
#include "routewidget.h"
#include "lightwidget.h"
#include "signalheadwidget.h"
#include "signalmastwidget.h"
#include "signalgroupswidget.h"
#include "signalmastlogicwidget.h"
#include "lroutewidget.h"
#include "logixwidget.h"
#include <QMenuBar>
#include "sectionwidget.h"
#include "transitwidget.h"
#include "../LayoutEditor/jmrijframe.h"
#include "audiotableframe.h"
#include "audiowidget.h"
#include "libtables_global.h"

namespace Ui {
class TablesFrame;
}

class SensorTableTabAction;
class TurnoutTableTabAction;
//class JmriJFrame;
class AudioTableAction;
class LIBTABLESSHARED_EXPORT TablesFrame : public JmriJFrame
{
    Q_OBJECT
    
public:
    explicit TablesFrame(QString type = tr("Turnouts"), QWidget *parent = 0);
    ~TablesFrame();
    QMenuBar* getMenuBar();
    QMenu* createViewMenu();
    QMenu* speedMenu;
    QAction* defaultsMenu;
    void setupType(QString type);

private slots:
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void on_viewMenu_triggered(QAction*);
    void on_logixOptions_triggered(bool);
    void on_findOrphans_triggered();
    void on_findEmpty_triggered();
    void on_openPickListTables();
private:
    Ui::TablesFrame *ui;
    QWidget* toWidget;
    TurnoutTableTabAction* ttact;
    QString curType;
    QWidget* currWidget;
    QWidget* sensorWidget;
    SensorTableTabAction* stAct;
    ReporterWidget* reporterWidget;
    MemoryWidget* memoryWidget;
    BlockWidget* blockWidget;
    IdTagsWidget* idTagsWidget;
    RouteWidget* routeWidget;
    LightWidget* lightWidget;
    SignalHeadWidget* signalHeadWidget;
    SignalMastWidget* signalMastWidget;
    SignalGroupsWidget* signalGroupsWidget;
    SignalMastLogicWidget* signalMastLogicWidget;
    LRouteWidget* lRouteWidget;
    LogixWidget* logixWidget;
    SectionWidget* sectionWidget;
    TransitWidget* transitWidget;
    AudioTablePanel* audioTablePanel;
    //AudioWidget* audioWidget;
    AudioTableAction* audioTableAction;

    friend class IdTagsWidget;
    QMenu* fileMenu;
    QMenu* viewMenu;
    QMenu* optionsMenu;
    QMenu* toolsMenu;
    QMenu* windowMenu;
    QMenu* helpMenu;
    JmriJFrame* jFrame;
};

#endif // TABLEFRAME_H
