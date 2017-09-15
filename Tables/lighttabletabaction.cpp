#include "lighttabletabaction.h"
#include "instancemanager.h"
#include "lighttableaction.h"
#include <QBoxLayout>

//LightTableTabAction::LightTableTabAction()
//{

//}
///*public*/ class LightTableTabAction extends AbstractTableTabAction {

/*public*/ LightTableTabAction::LightTableTabAction(QString s, QObject* parent) : AbstractTableTabAction(s,parent){
    //super(s);
    frame = NULL;
}

/*public*/ LightTableTabAction::LightTableTabAction( QObject* parent) : AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
    frame = NULL;
}

/*protected*/ Manager* LightTableTabAction::getManager() {
    return InstanceManager::lightManagerInstance();
}

/*protected*/ QString LightTableTabAction::getClassName() {
    return "LightTableAction";
}

/*protected*/ AbstractTableAction* LightTableTabAction::getNewTableAction(QString choice) {
    return new LightTableAction(choice,0);
}

//@Override
/*protected*/ QString LightTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.LightTable";
}

// added ACK
BeanTableFrame* LightTableTabAction::currFrame()
{
 return LightTableTabAction::frame;
}

void LightTableTabAction::setCurrFrame(BeanTableFrame *frame)
{
 this->frame = frame;
 LightTableTabAction::frame = frame;
 AbstractTableAction::f = frame;
}

QWidget* LightTableTabAction::getPanel()
{
 createModel();
 f = new ATABeanTableFrame(this);
 f->setObjectName("ATABeanTableFrame");
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
