#ifndef OPATH_H
#define OPATH_H
#include "path.h"
#include "libPr3_global.h"

class OBlock;
class JActionEvent;
class OPTimeTurnout;
class ActionListener;
class Portal;
class QTimer;
class LIBPR3SHARED_EXPORT OPath : public Path
{
    Q_OBJECT
public:
    //explicit OPath(QObject *parent = 0);
    /*public*/ OPath(Block* owner, QString name, QObject *parent = 0);
    /*public*/ OPath(Block* owner, int toBlockDirection, int fromBlockDirection, QObject *parent = 0);
    /*public*/ OPath(Block* owner, int toBlockDirection, int fromBlockDirection, BeanSetting* setting, QObject *parent = 0);
//    /*public*/ OPath(QString name, OBlock* owner, Portal* entry, int fromBlockDirection,
//                     Portal* exit, int toBlockDirection, QObject *parent = 0);
    /*public*/ OPath(QString name, OBlock* owner, Portal* entry, Portal* exit, QList<BeanSetting*> settings, QObject *parent = 0);
    /*public*/ void setBlock(Block* block);
    /*public*/ void setName(QString name);
    /*public*/ QString getName();
    /*public*/ void setFromPortal(Portal* p);
    /*public*/ Portal* getFromPortal();
    /*public*/ void setToPortal(Portal* p);
    /*public*/ Portal* getToPortal();
    /*public*/ void setTurnouts(int delay, bool set, int lockState, bool lock);
    void fireTurnouts(QList<BeanSetting*> list, bool set, int lockState, bool lock);
    /*public*/ void dispose();
    /*public*/ QString getDescription();
    /*public*/ QString toString();
    /*public*/ void addSetting(BeanSetting* t) override;
    /*public*/ bool equals(OPath* path);

signals:

public slots:
private:
    /*private*/ Portal* _fromPortal = nullptr;
    /*private*/ Portal* _toPortal = nullptr;
    /*private*/ QString _name;
    /*private*/ QTimer* _timer = nullptr;
    /*private*/ bool _timerActive = false;
    /*private*/ OPTimeTurnout* _listener = nullptr;
    Logger* log;
    void common();
protected:
    /*protected*/ QString getOppositePortalName(QString name);
    /*protected*/ bool validatePortals();

    friend class OPTimeTurnout;
    friend class RouteFinder;
};

class OPTimeTurnout : public QObject
{
     Q_OBJECT
     /*private*/ QList<BeanSetting*> list;
     /*private*/ int lockState;
     bool set;
     bool lock;
     OPath* self;
public:
     /*public*/ OPTimeTurnout(OPath* self  );
     void setList(QList<BeanSetting*> l);
     void setParams(bool s, int ls, bool l);

public slots:
     /*public*/ void actionPerformed(JActionEvent* event = 0);
};
#endif // OPATH_H
