#ifndef ABSTRACTFILEMODELFACTORY_H
#define ABSTRACTFILEMODELFACTORY_H
#include "startupmodelfactory.h"

class JFileChooser;
class Logger;
class AbstractFileModelFactory : public QObject, public StartupModelFactory
{
 Q_OBJECT
  Q_INTERFACES(StartupModelFactory)
public:
 AbstractFileModelFactory();
 /*public*/ QString getDescription();
 /*public*/ void editModel(StartupModel* model, QWidget* parent);
 /*public*/ QString getActionText();
 /*public*/ void initialize();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(AbstractFileModelFactory.class);
 /*private*/ JFileChooser* chooser;// = null;

protected:
 /*abstract*/ /*protected*/virtual JFileChooser* setFileChooser();

};

#endif // ABSTRACTFILEMODELFACTORY_H
