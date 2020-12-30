#ifndef INPUTWINDOWACTION_H
#define INPUTWINDOWACTION_H
#include "abstractaction.h"
#include "windowlistener.h"

class UserPreferencesManager;
class JFrame;
class InputWindowAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit InputWindowAction(QObject *parent );
 /*public*/ InputWindowAction(QString name, QObject *parent);
 /*public*/ JFrame* getFrame();

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);

private :
 JFrame* f;
 void common();
 UserPreferencesManager* pref;
 void closeEvent(QCloseEvent *);
 friend class IWWindowListener;
};
class IWWindowListener : public WindowListener
{
 Q_OBJECT
 InputWindowAction* parent;
public:
 IWWindowListener(InputWindowAction* parent);
 void windowClosing(QCloseEvent *e);
};

#endif // INPUTWINDOWACTION_H
