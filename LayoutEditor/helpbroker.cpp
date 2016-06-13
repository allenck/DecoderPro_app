#include "helpbroker.h"
#include <QUrl>
#include <QSignalMapper>
#include <QAction>
#include "helputil.h"
#include <QPushButton>

HelpBroker::HelpBroker(QObject *parent) : QObject(parent)
{
 //hMap = QMap<QString, QString>();
 mapper = new QSignalMapper();
 connect(mapper, SIGNAL(mapped(QString)), this, SLOT(on_action(QString)));
}

HelpBroker::~HelpBroker()
{

}

void HelpBroker::enableHelpOnButton(QObject *mi, QString string, HelpSet *hs)
{
 if(qobject_cast<QPushButton*>(mi) != NULL)
 {
  const QPushButton* b = (QPushButton*)mi;
  mapper->setMapping(mi, string);
  connect(mi, SIGNAL(clicked()), mapper, SLOT(map()));
 }
 else if(qobject_cast<QAction*>(mi))
 {
  QAction* b = (QAction*)mi;
  mapper->setMapping(mi, string);
  connect(mi, SIGNAL(triggered()), mapper, SLOT(map()));
 }
}

void HelpBroker::on_action(QString ref)
{
 //HelpUtil* helpUtil = HelpUtil::instance();
// QString actionText = ((QAction*)o)->text();
// QString ref;
 HelpFrame* f = new HelpFrame(ref);
 f->show();
}
