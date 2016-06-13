#ifndef LOCONETMENU_H
#define LOCONETMENU_H
#include "libPr3_global.h"

#include <QMenu>

class LIBPR3SHARED_EXPORT LocoNetSystemConnectionMemo;
/*static*/ class LocoNetMenuItem : public QObject
{
 Q_OBJECT
public:
    LocoNetMenuItem(QString name, QString load);
    QString name;
    QString load;
};
class LIBPR3SHARED_EXPORT LocoNetMenu : public QMenu
{
 Q_OBJECT
public:
 //explicit LocoNetMenu(QWidget *parent = 0);
 /*public*/ LocoNetMenu(LocoNetSystemConnectionMemo* memo, QWidget *parent);
 static LocoNetMenu* instance(LocoNetSystemConnectionMemo* memo, QWidget* parent);

signals:

public slots:
 void on_probeAction();

private:
 QList<LocoNetMenuItem*> panelItems;
 QWidget* parent;
 LocoNetSystemConnectionMemo* memo;
 static LocoNetMenu* _instance;
};

#endif // LOCONETMENU_H
