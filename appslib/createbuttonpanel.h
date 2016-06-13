#ifndef CREATEBUTTONPANEL_H
#define CREATEBUTTONPANEL_H
#include "abstractactionpanel.h"
#include "appslib_global.h"

class CreateButtonModel;
class APPSLIBSHARED_EXPORT CreateButtonPanel : public AbstractActionPanel
{
    Q_OBJECT
public:
    explicit CreateButtonPanel(QWidget *parent = 0);
    ~CreateButtonPanel() {}
    CreateButtonPanel(const CreateButtonPanel& );
    template<class T>
    //virtual
    QList<T> rememberedObjects();
    virtual
    AbstractActionModel* getNewModel();
    virtual
    /*public*/ QString getTabbedPreferencesTitle();
    virtual
    /*public*/ QString getLabelKey();

signals:

public slots:

};

#endif // CREATEBUTTONPANEL_H
