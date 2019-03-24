#ifndef LOCOMONPANE_H
#define LOCOMONPANE_H
#include "abstractmonpane.h"
#include "liblayouteditor_global.h"

class QSignalMapper;
class JTable;
class LocoNetMessage;
//class LlnMon;
class LocoNetSystemConnectionMemo;
class LIBLAYOUTEDITORSHARED_EXPORT LocoMonPane : public AbstractMonPane
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LocoMonPane(QWidget *parent = nullptr);
 ~LocoMonPane();
 LocoMonPane(const LocoMonPane&) : AbstractMonPane() {}
    /*public*/ QString getHelpTarget();
    /*public*/ QString getTitle();
    /*public*/ void dispose();
    /*public*/ void initContext(QObject* context) throw (Exception);
    /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
    /*public*/ void init();

    QString getClassName();


signals:
 void buttonClicked(int, QString);

public slots:
    /*public*/ /*synchronized*/ void message(LocoNetMessage* l);

private:
    /*private*/ QString systemConnectionPrefix;
    LocoNetSystemConnectionMemo* memo;
    //LlnMon* llnmon;// = new Llnmon();
    Logger* log;
    void closeEvent(QCloseEvent *);

};
#endif // LOCOMONPANE_H
