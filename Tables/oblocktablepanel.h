#ifndef OBLOCKTABLEPANEL_H
#define OBLOCKTABLEPANEL_H
#include "jpanel.h"
#include "box.h"
#include <QMenu>

class RowSorter;
class TableModel;
class OBlockTableModel;
class PortalTableModel;
class SignalTableModel;
class BlockPortalTableModel;
class JTabbedPane;
class JTable;
class TableFrames;
class Logger;
class OBlockTablePanel : public JPanel
{
    Q_OBJECT
public:
    /*public*/ OBlockTablePanel(OBlockTableModel* oblocks,
                            PortalTableModel* portals,
                            SignalTableModel* _signals,
                            BlockPortalTableModel* blockportals,
                            TableFrames* tf,
                            QString helpTarget,
                            QWidget *parent = nullptr);

    /*public*/ void dispose();

    /*public*/ JTable* makeJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ TableModel* model, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter);
    /*public*/ void configureWarrantTable(JTable* table);
    /*public*/ QMenu *getPrintItem();
    /*public*/ QMenu* getOptionMenu();
    /*public*/ QMenu* getTablesMenu();

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
    QWidget* bottomBox;                  // panel at bottom for extra buttons etc
    int bottomBoxIndex;             // index to insert extra stuff
    /*private*/ static /*final*/ int bottomStrutWidth;// = 20;
    void extras();

protected:
    /*protected*/ QWidget* getBottomBox();
    /*protected*/ JTable* configureJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ JTable* table, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter);
    /*protected*/ void addToBottomBox(QWidget* comp);

    friend class OBlockTableAction;
};

#endif // OBLOCKTABLEPANEL_H
