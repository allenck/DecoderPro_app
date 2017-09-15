#include "turnouttabletabaction.h"
#include "instancemanager.h"
#include "turnouttableaction.h"
#include <QVBoxLayout>

//TurnoutTableTabAction::TurnoutTableTabAction(QObject *parent) :
//    AbstractTableTabAction(parent)
//{
//}
// /*public*/ class TurnoutTableTabAction extends AbstractTableTabAction {

/**
 *
 */
//private static final long serialVersionUID = 5514320062139920106L;

/*public*/ TurnoutTableTabAction::TurnoutTableTabAction(QString s, QObject *parent) :
    AbstractTableTabAction(s, parent)
{
    //super(s);
 common();
}
BeanTableFrame* TurnoutTableTabAction::frame = NULL;

/*public*/ TurnoutTableTabAction::TurnoutTableTabAction(QObject *parent) :
    AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
 common();
}
void TurnoutTableTabAction::common()
{
}

/*protected*/ Manager* TurnoutTableTabAction::getManager() {
    return InstanceManager::turnoutManagerInstance();
}

/*protected*/ QString TurnoutTableTabAction::getClassName() {
    return /*TurnoutTableAction.class.getName()*/ "jmri.jmrit/beantable/TurnoutTableTabAction";
}

/*protected*/ AbstractTableAction* TurnoutTableTabAction::getNewTableAction (QString choice){
    return new TurnoutTableAction(choice,parent());
}

//@Override
/*protected*/ QString TurnoutTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TurnoutTable";
}
BeanTableFrame* TurnoutTableTabAction::currFrame()
{
 return TurnoutTableTabAction::frame;
}

void TurnoutTableTabAction::setCurrFrame(BeanTableFrame *frame)
{
 this->frame = frame;
 TurnoutTableTabAction::frame = frame;
 AbstractTableAction::f = frame;
}

QWidget* TurnoutTableTabAction::getPane()
{
 createModel();
 f = new ATABeanTableFrame(this);
 f->setProperty("type", "BeanTableFrame");
 setCurrFrame(f);
 QWidget* centralWidget = new QWidget;
 centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 f->setCentralWidget(centralWidget);
 centralWidgetLayout->addWidget(dataTabs);
 for(int i=0; i < tabbedTableArray.size(); i++)
 {
  centralWidgetLayout->addWidget(tabbedTableArray.at(i)->bottomBox);
  tabbedTableArray.at(i)->bottomBox->setVisible(i == currTab);
 }
 f->pack();
 return f;
}
