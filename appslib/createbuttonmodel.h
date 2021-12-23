#ifndef CREATEBUTTONMODEL_H
#define CREATEBUTTONMODEL_H
#include "abstractactionmodel.h"
#include "appslib_global.h"
#include "propertychangeevent.h"

class QPushButton;
class APPSLIBSHARED_EXPORT CreateButtonModel : public AbstractActionModel
{
    Q_OBJECT
public:
    explicit CreateButtonModel(QObject *parent = 0);
    ~CreateButtonModel() {}
    CreateButtonModel(const CreateButtonModel&)
        : AbstractActionModel() {}
signals:
private:
    QPushButton* b;
    Action* action;

protected slots:
    /*protected*/ void performAction(Action* action) /*throw (JmriException)*/;
    void propertyChange(PropertyChangeEvent*);
};
Q_DECLARE_METATYPE(CreateButtonModel)
#endif // CREATEBUTTONMODEL_H
