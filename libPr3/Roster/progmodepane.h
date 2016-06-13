#ifndef PROGMODEPANE_H
#define PROGMODEPANE_H
#include "progmodeselector.h"
#include "logger.h"
#include <QBoxLayout>
#include "libPr3_global.h"

class QButtonGroup;
class ProgServiceModePane;
class ProgOpsModePane;
class LIBPR3SHARED_EXPORT ProgModePane : public ProgModeSelector
{
    Q_OBJECT
public:
    ProgModePane(QBoxLayout::Direction direction, QWidget *parent = 0);
    /*public*/ bool isSelected() ;
    /*public*/ Programmer* getProgrammer();
    /*public*/ void dispose();
//    /*public*/ void setDefaultMode();
signals:

public slots:
private:
    // GUI member declarations
    ProgOpsModePane*     mOpsPane;
    ProgServiceModePane* mServicePane;
    QButtonGroup* group;// = new ButtonGroup();
 Logger* log;
};

#endif // PROGMODEPANE_H
