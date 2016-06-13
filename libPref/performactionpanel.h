#ifndef PERFORMACTIONPANEL_H
#define PERFORMACTIONPANEL_H
#include "abstractactionpanel.h"
#include "libpref_global.h"

class PerformActionModel;
class AbstractActionModel;
class LIBPREFSHARED_EXPORT PerformActionPanel : public AbstractActionPanel
{
    Q_OBJECT
public:
    //explicit PerformActionPanel(QWidget *parent = 0);
    /*public*/ PerformActionPanel(QWidget *parent = 0) ;
    ~PerformActionPanel() {}
    PerformActionPanel(const PerformActionPanel&);
    virtual
    QList<PerformActionModel*> rememberedObjects();
    virtual
    AbstractActionModel* getNewModel();
    virtual
    /*public*/ QString getTabbedPreferencesTitle();
    virtual
    /*public*/ QString getLabelKey();

signals:

public slots:

};

#endif // PERFORMACTIONPANEL_H
