#ifndef LNPANEL_H
#define LNPANEL_H

#include "jmripanel.h"
#include "libPr3_global.h"

class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnPanel : public JmriPanel
{
    Q_OBJECT
public:
    explicit LnPanel(QWidget *parent = 0);
    virtual/*public*/ void initComponents(LocoNetSystemConnectionMemo* memo) ;
    /*public*/ void initContext(QObject* context);
    /*public*/ virtual QString getTitle(QString menuTitle);
    QString getTitle();
signals:

public slots:
protected:
    /**
     * make "memo" object available as convenience
     */
    /*protected*/ LocoNetSystemConnectionMemo* memo;

};

#endif // LNPANEL_H
