#ifndef OBLOCKTABLEPANEL_H
#define OBLOCKTABLEPANEL_H
#include "jpanel.h"
#include "box.h"

class OBlockTableModel;
class PortalTableModel;
class SignalTableModel;
class BlockPortalTableModel;
class JTabbedPane;
class JTable;
class TableFrames;
class Logger;
class OBlockTablePanel : public QWidget
{
    Q_OBJECT
public:
    /*public*/ OBlockTablePanel(OBlockTableModel* oblocks,
                            PortalTableModel* portals,
                            SignalTableModel* _signals,
                            BlockPortalTableModel* blockportals,
                            TableFrames* tf,
                            QString helpTarget,
                            QWidget *parent);

    /*public*/ void dispose();


private:
    static Logger* log;
    /*private*/ OBlockTableModel* oblockDataModel;
    /*private*/ PortalTableModel* portalDataModel;
    /*private*/ SignalTableModel* signalDataModel;
    /*private*/ BlockPortalTableModel* blockportalDataModel;

    /*private*/ JTable* oblockTable;
    /*private*/ JTable* portalTable;
    /*private*/ JTable* signalTable;
    /*private*/ JTable* blockportalTable;

//    /*private*/ JScrollPane oblockDataScroll;
//    /*private*/ JScrollPane portalDataScroll;
//    /*private*/ JScrollPane signalDataScroll;
//    /*private*/ JScrollPane blockportalDataScroll;

    /*private*/ /*final*/ JTabbedPane* oblockTabs;
    TableFrames* _tf;
    Box* bottomBox;                  // panel at bottom for extra buttons etc
    int bottomBoxIndex;             // index to insert extra stuff
    /*private*/ static /*final*/ int bottomStrutWidth;// = 20;
    void extras();

protected:
    /*protected*/ Box* getBottomBox();

};

#endif // OBLOCKTABLEPANEL_H
