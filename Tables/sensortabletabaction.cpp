#include "sensortabletabaction.h"
#include "sensortableaction.h"
#include "instancemanager.h"
#include <QBoxLayout>

//SensorTableTabAction::SensorTableTabAction()
//{

//}
///*public*/ class SensorTableTabAction extends AbstractTableTabAction {

/*public*/ SensorTableTabAction::SensorTableTabAction(QString s, QObject*parent)
    : AbstractTableTabAction(s, parent)
{
    //super(s);
}
//BeanTableFrame* SensorTableTabAction::frame = NULL;

/*public*/ SensorTableTabAction::SensorTableTabAction(QObject* parent)
    : AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
}

/*protected*/ Manager* SensorTableTabAction::getManager() {
    return InstanceManager::sensorManagerInstance();
}

/*protected*/ QString SensorTableTabAction::getClassName() {
    return "SensorTableAction";
}

/*protected*/ AbstractTableAction* SensorTableTabAction::getNewTableAction(QString choice) {
    return new SensorTableAction(choice, this);
}

//@Override
/*protected*/ QString SensorTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SensorTable";
}
#if 0
BeanTableFrame* SensorTableTabAction::currFrame()
{
 return SensorTableTabAction::frame;
}

void SensorTableTabAction::setCurrFrame(BeanTableFrame *frame)
{
 this->frame = frame;
 SensorTableTabAction::frame = frame;
 AbstractTableAction::f = frame;
}

QWidget* SensorTableTabAction::getPane()
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
#endif
