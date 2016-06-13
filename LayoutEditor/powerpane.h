#ifndef POWERPANE_H
#define POWERPANE_H
#include "jmripanel.h"
#include "logger.h"
#include "liblayouteditor_global.h"
class PropertyChangeEvent;
class PowerManager;
class PowerManagerMenu;
class QLabel;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT PowerPane : public JmriPanel
{
    Q_OBJECT
public:
    explicit PowerPane(QWidget *parent = 0);
    PowerManagerMenu* selectMenu;
    /*public*/ QString getHelpTarget();
    /*public*/ QString getTitle();
    /*public*/ QList<QMenu*> getMenus();
    /*public*/ void dispose();

signals:

public slots:
    void managerChanged();
    /*public*/ void onButtonPushed();
    /*public*/ void offButtonPushed();
    /*public*/ void propertyChange(PropertyChangeEvent* ev);

private:
    QLabel* onOffStatus;// 	= new QLabel(tr("Unknown"));
    QPushButton* onButton;// 	= new QPushButton(tr("On"));
    QPushButton* offButton;// 	= new QPushButton(tr("Off"));
    PowerManager* listening;// = null;
    void setStatus();
    Logger* log;
    /*private*/ bool mgrOK();
};

#endif // POWERPANE_H
