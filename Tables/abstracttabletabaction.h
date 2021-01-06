#ifndef ABSTRACTTABLETABACTION_H
#define ABSTRACTTABLETABACTION_H
#include "abstracttableaction.h"
#include "libtables_global.h"

class QGridLayout;
class QFrame;
class QVBoxLayout;
class QTableView;
class TabbedTableItem;
class QTabWidget;
class LIBTABLESSHARED_EXPORT AbstractTableTabAction : public AbstractTableAction
{
    Q_OBJECT
public:
    //explicit AbstractTableTabAction(QObject *parent = 0);
    /*public*/ AbstractTableTabAction(QString s, QObject *parent);
    ~AbstractTableTabAction();
    /*public*/ QWidget* getPanel();
    /*public*/ void addToFrame(BeanTableFrame* f);
    /*public*/ void setMenuBar(BeanTableFrame* f);
    /*public*/ void addToBottomBox(QWidget* c, QString str);
    /*public*/ void print(JTable::PrintMode mode, QString headerFormat, QString footerFormat);
    /*public*/ void dispose();
 virtual /*public*/ BeanTableFrame* currFrame();
 virtual /*public*/ void setCurrFrame(BeanTableFrame*);
signals:

public slots:
    void On_dataTabs_currentChanged(int);
    void actionPerformed(JActionEvent *e = 0);
private:
    Logger* log;
    QVBoxLayout* centralWidgetLayout;
    int currTab;
    virtual QString getTableClass() {return "";}
protected:
    /*protected*/ QWidget* dataPanel;
    /*protected*/ QTabWidget* dataTabs;

    /*protected*/ bool init;// = false;
    /*protected*/ void createModel();
    virtual /*abstract*/ /*protected*/ Manager* getManager();
    virtual /*abstract*/ /*protected*/ AbstractTableAction* getNewTableAction(QString choice);
    /*protected*/ QList<TabbedTableItem*> tabbedTableArray;// = new ArrayList<TabbedTableItem>();
    /*protected*/ void setTitle();
    virtual /*abstract*/ /*protected*/ QString helpTarget();
    void buildMenus(BeanTableFrame* f);

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);
    void On_printAction_triggered();
friend class TablesFrame;
friend class TurnoutTableTabAction;
friend class SensorTableTabAction;
friend class LightTableTabAction;
};

/*protected*/ /*static*/ class TabbedTableItem : public QObject
{
 Q_OBJECT

    AbstractTableAction* tableAction;
    QString itemText;
    BeanTableDataModel* dataModel;
    JTable* dataTable;
    //JScrollPane dataScroll;
    QFrame* bottomBox;
    bool AddToFrameRan;// = false;
    Manager* manager;

    int bottomBoxIndex;	// index to insert extra stuff
    static /*final*/ int bottomStrutWidth;// = 20;

    bool standardModel;// = true;

    /*final*/ QWidget* dataPanel;// = new JPanel();
    QGridLayout* dataPanelLayout;

public:
    /*public*/ TabbedTableItem(QString choice, bool stdModel, Manager* manager, AbstractTableAction* tableAction);
    void createDataModel();
    void addPanelModel();
    /*public*/ bool getStandardTableModel();
    /*public*/ QString getItemString();
    /*public*/ AbstractTableAction* getAAClass();
    /*public*/ QWidget* getPanel();
    /*public*/ bool getAdditionsToFrameDone();
    /*public*/ void setAddToFrameRan();
    /*public*/ JTable* getDataTable();
protected:
    /*protected*/ void addToBottomBox(QWidget* comp);
    /*protected*/ void dispose();
    friend class AbstractTableTabAction;
    friend class TurnoutTableTabAction;
    friend class SensorTableTabAction;
    friend class LightTableTabAction;
};

#endif // ABSTRACTTABLETABACTION_H
