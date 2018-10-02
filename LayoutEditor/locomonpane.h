#ifndef LOCOMONPANE_H
#define LOCOMONPANE_H
#include "abstractmonpane.h"
#include "liblayouteditor_global.h"

class QSignalMapper;
class JTable;
class LocoNetMessage;
class LlnMon;
class LocoNetSystemConnectionMemo;
class LIBLAYOUTEDITORSHARED_EXPORT LocoMonPane : public AbstractMonPane
{
    Q_OBJECT
public:
    explicit LocoMonPane(QWidget *parent = 0);
 ~LocoMonPane();
 LocoMonPane(const LocoMonPane&) : AbstractMonPane() {}
    /*public*/ QString getHelpTarget();
    /*public*/ QString getTitle();
    /*public*/ void dispose();
    /*public*/ void initContext(QObject* context) throw (Exception);
    /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
    /*public*/ void init();
 static LocoMonPane* instance();
signals:
 void buttonClicked(int, QString);

public slots:
    /*public*/ /*synchronized*/ void message(LocoNetMessage* l);

private:
    /*private*/ QString systemConnectionPrefix;
    LocoNetSystemConnectionMemo* memo;
    LlnMon* llnmon;// = new Llnmon();
    Logger* log;
    void closeEvent(QCloseEvent *);
    static LocoMonPane* _instance;


};
#endif // LOCOMONPANE_H
