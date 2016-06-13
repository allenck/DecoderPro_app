#ifndef EDITPORTALFRAME_H
#define EDITPORTALFRAME_H
#include "jmrijframe.h"
#include <QListView>

class Portal;
class JTextField;
class PortalListModel;
class CircuitBuilder;
class OBlock;
class EditPortalFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit EditPortalFrame(QWidget *parent = 0);
 /*public*/ EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block, Portal* portal, OBlock* adjacent);
    /*public*/ EditPortalFrame(QString _title, CircuitBuilder* parent, OBlock* block, bool update);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;

signals:

public slots:
private:
    void common();
    /*private*/ OBlock* _homeBlock;
    /*private*/ CircuitBuilder* _parent;
    /*private*/ OBlock* _adjacentBlock;

    /*private*/ QListView*       _portalList;
    /*private*/ PortalListModel* _portalListModel;
    /*private*/ QString _currentPortalName;			// name of last portal Icon made

    /*private*/ JTextField*  _portalName;// = new JTextField();
    /*private*/ QWidget* MakeButtonPanel();
 Logger* log;
 /*private*/ QWidget* makePortalPanel(bool update);

};

#endif // EDITPORTALFRAME_H
