#ifndef ROSTERFRAMEACTION_H
#define ROSTERFRAMEACTION_H

#include "jmriabstractaction.h"
#include "logger.h"
#include "libPr3_global.h"

class RosterFrame;
class JmriPanel;
class WindowInterface;
class LIBPR3SHARED_EXPORT RosterFrameAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit RosterFrameAction(QObject *parent =0);
    /*public*/ RosterFrameAction(QString s, WindowInterface* wi) ;
    /*public*/ RosterFrameAction(QString s, WindowInterface* wi, bool allowQuit);
    /*public*/ RosterFrameAction(QString s, QIcon i, WindowInterface* wi);
    /*public*/ RosterFrameAction(QString pName, bool allowQuit,QObject *parent);
 ~RosterFrameAction() {}
 RosterFrameAction(const RosterFrameAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
    /*public*/ JmriPanel* makePanel();
public slots:
    /*public*/ void actionPerformed(ActionEvent* event = 0) ;
signals:

public slots:
private:
    bool allowQuit;// = true;
    void common();
    Logger* log;
    RosterFrame* mainFrame;
};
Q_DECLARE_METATYPE(RosterFrameAction)
#endif // ROSTERFRAMEACTION_H
