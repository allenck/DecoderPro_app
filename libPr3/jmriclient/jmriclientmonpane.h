#ifndef JMRICLIENTMONPANE_H
#define JMRICLIENTMONPANE_H
#include "abstractmonpane.h"
#include "jmrinamedpaneaction.h"
#include "instancemanager.h"
#include "jmriclientsystemconnectionmemo.h"

class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientMonPane : public AbstractMonPane
{
public:
// /*static*/ /*public*/ class Default : public  JmriNamedPaneAction
// {

//   /*public*/ Default(QObject* parent) : JmriNamedPaneAction(tr(" Jmri Client Command Monitor"), "JMRIClientMonPane", parent)
//   {
//          //super(tr(" Jmri Client Command Monitor"), "JMRIClientMonPane");
//          setContext(static_cast<JMRIClientSystemConnectionMemo*>(InstanceManager::
//                  getDefault("JMRIClientSystemConnectionMemo")));
//          connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(ActionEvent*)));
//   }
//  friend class JMRIClientMonAction;
// };
 JMRIClientMonPane(QWidget *parent =nullptr);
 /*public*/ QString getTitle();
 /*public*/ void initContext(QObject* context);
 /*public*/ void dispose();
 /*public*/ /*synchronized*/ void reply(JMRIClientReply* l);  // receive a reply message and log it

public slots:
  /*public*/ /*synchronized*/ void message(JMRIClientMessage* l);  // receive a message and log it


protected:
 /*protected*/ JMRIClientTrafficController* tc = nullptr;
 /*protected*/ void init();

};
/*static*/ /*public*/ class JmriNamedPaneActionDefault : public  JmriNamedPaneAction
{
 Q_OBJECT
public:
 /*public*/ JmriNamedPaneActionDefault(QObject* parent) : JmriNamedPaneAction(tr(" Jmri Client Command Monitor"), "JMRIClientMonPane", parent)
 {
        //super(tr(" Jmri Client Command Monitor"), "JMRIClientMonPane");
        setContext(static_cast<JMRIClientSystemConnectionMemo*>(InstanceManager::
                getDefault("JMRIClientSystemConnectionMemo")));
        connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(ActionEvent*)));
 }
public slots:
void actionPerformed()
{
 JMRIClientMonPane* pane = new JMRIClientMonPane();
 pane->setVisible(true);
 pane->pack();
}
friend class JMRIClientMonAction;
};

#endif // JMRICLIENTMONPANE_H
