#ifndef POWERPANE_H
#define POWERPANE_H
#include "jmripanel.h"
#include "logger.h"
#include "liblayouteditor_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class PowerManager;
class PowerManagerMenu;
class QLabel;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT PowerPane : public JmriPanel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    explicit PowerPane(QWidget *parent = 0);
    PowerManagerMenu* selectMenu;
    /*public*/ QString getHelpTarget() override;
    /*public*/ QString getTitle() override;
    /*public*/ QList<QMenu*> getMenus() override;
    /*public*/ void dispose() override;
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    void managerChanged();
    /*public*/ void onButtonPushed();
    /*public*/ void offButtonPushed();
    /*public*/ void propertyChange(PropertyChangeEvent* ev) override;

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
