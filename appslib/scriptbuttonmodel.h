#ifndef SCRIPTBUTTONMODEL_H
#define SCRIPTBUTTONMODEL_H
#include "abstractstartupmodel.h"
#include "abstractaction.h"

class ScriptButtonAction;
class Logger;
class File;
class ScriptButtonModel : public AbstractStartupModel
{
 Q_OBJECT
public:
 ScriptButtonModel();
 /*public*/ File* getScript();
 /*public*/ void setScript(File* script);
 /*public*/ QString toString();
 /*public*/ void performAction(QString) /*throw (JmriException)*/;

private:
 /*private*/ File* script;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("ScriptButtonModel");
friend class ScriptButtonAction;
};

/*private*/ /*static*/ class ScriptButtonAction : public AbstractAction {
Q_OBJECT
    ScriptButtonModel* model;
public:
    /*public*/ ScriptButtonAction(ScriptButtonModel* model);
public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
};

#endif // SCRIPTBUTTONMODEL_H
