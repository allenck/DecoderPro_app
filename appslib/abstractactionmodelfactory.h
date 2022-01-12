#ifndef ABSTRACTACTIONMODELFACTORY_H
#define ABSTRACTACTIONMODELFACTORY_H
#include "startupmodelfactory.h"
#include "jlist.h"
#include <QComboBox>
#include "listselectionevent.h"
#include <QLabel>

class StartupModel;
class Logger;
class AbstractActionModelFactory : public QObject, public StartupModelFactory
{
 Q_OBJECT
  Q_INTERFACES(StartupModelFactory)
public:
 AbstractActionModelFactory();
 /*public*/ QString getDescription();
 /*public*/ QString getActionText();
 /*public*/ /*abstract*/ virtual QString getEditModelMessage();
 /*public*/ void editModel(StartupModel* model, QWidget* parent);
 /*public*/ void initialize();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("AbstractActionModelFactory");
 /*private*/ QWidget* getDialogMessage(JList* actions, QComboBox* connections);
 QComboBox* connections;
 QLabel* connectionsLabel;
 JList* actions;

private slots:
 void on_selected(/*ListSelectionEvent* = 0*/QModelIndex index);
};

#endif // ABSTRACTACTIONMODELFACTORY_H
