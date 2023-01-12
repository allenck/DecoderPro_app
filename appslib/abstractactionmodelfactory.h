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
 /*public*/ QString getDescription() override ;
 /*public*/ QString getActionText() override ;
 /*public*/ /*abstract*/ virtual QString getEditModelMessage();
 /*public*/ void editModel(StartupModel* model, QWidget* parent) override ;
 Q_INVOKABLE/*public*/ void initialize() override ;

 QObject* self() override {return this;}

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
