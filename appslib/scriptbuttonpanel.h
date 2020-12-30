#ifndef SCRIPTBUTTONPANEL_H
#define SCRIPTBUTTONPANEL_H

#include <QWidget>
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>

class JActionEvent;
class Logger;
class JFileChooser;
class ScriptButtonPanel : public QWidget
{
 Q_OBJECT
public:
 explicit ScriptButtonPanel(JFileChooser* chooser, QWidget *parent = nullptr);

signals:

public slots:

private:
 /*private*/ /*final*/ QWidget* parent;
 /*private*/ /*final*/ JFileChooser* chooser;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ScriptButtonPanel");
 // Variables declaration - do not modify
 /*private*/ JTextField* buttonName;
 /*private*/ QLabel* nameLabel;
 /*private*/ JTextField* script;
 /*private*/ QPushButton* scriptButton;
 /*private*/ QLabel* scriptLabel;
 // End of variables declaration
 /*private*/ void initComponents();

private slots:
 /*private*/ void scriptButtonActionPerformed(JActionEvent* evt = 0);
protected:
 /*protected*/ QString getButtonName();
 /*protected*/ void setButtonName(QString name);
 /*protected*/ QString getScript();
 /*protected*/ void setScript(QString script);
friend class ScriptButtonModelFactory;
};

#endif // SCRIPTBUTTONPANEL_H
