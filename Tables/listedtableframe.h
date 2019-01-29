#ifndef LISTEDTABLEFRAME_H
#define LISTEDTABLEFRAME_H
#include "beantableframe.h"
#include <QSplitter>
#include <QModelIndex>
#include <QStackedWidget>

class QGridLayout;
class QVBoxLayout;
class JList;
class ActionJList;
class TabbedTableItemListArray;
class Box;
class AbstractTableAction;
class UserPreferencesManager;
class LTFTabbedTableItem;
class ListedTableFrame : public BeanTableFrame
{
    Q_OBJECT
public:
    ListedTableFrame(QWidget* parent = 0);
    ~ListedTableFrame() {}
    ListedTableFrame(const ListedTableFrame& ) : BeanTableFrame() {}
    /*public*/ bool isMultipleInstances();
    static QList<TabbedTableItemListArray*>* tabbedTableItemListArrayArray;// = new QList<TabbedTableItemListArray*>();
    /*public*/ ListedTableFrame(QString s, QWidget* parent = 0);
    /*public*/ void initComponents();
    /*public*/ void gotoListItem(QString selection);
    /*public*/ void addTable(QString aaClass, QString choice, bool stdModel);
    /*public*/ void dispose();
    /*public*/ void setDividerLocation(int loc);
    /*public*/ int getDividerLocation();
    /*public*/ QString getClassName();
    /*public*/ void setWindowSize();

public slots:
    void On_newItem_triggered();
    void On_viewMenu_triggered(QObject*);
    void On_listSelection(QModelIndex);
    void splitterMoved(int, int);

private:
    QList<LTFTabbedTableItem*>* tabbedTableArray;// = new ArrayList<TabbedTableItem>();

    /*final*/ UserPreferencesManager* pref;// = InstanceManager.getDefault("UserPreferencesManager");
    QSplitter* cardHolder;
    JList* list;
    //ScrollPane listScroller;
    QWidget* buttonpanel;
    QStackedWidget* detailpanel;
    static bool init;// = false;
    LTFTabbedTableItem* itemBeingAdded;// = NULL;
    static int lastdivider;
    void common();
    QWidget* errorPanel(QString text);
    ActionJList* actionList;
    Logger* log;
    LTFTabbedTableItem* lastSelectedItem;// = NULL;
    void buildMenus(/*final*/ LTFTabbedTableItem* item);
    QVBoxLayout * thisLayout;
    int currTableIndex =0;

protected:
    /*protected*/ static QList<QString> getChoices();
    /*protected*/ void addToBottomBox(QWidget* comp, QString c);
 friend class ActionJList;
};
Q_DECLARE_METATYPE(ListedTableFrame)

class ActionJList : public QObject
{
 Q_OBJECT
 QMenu* popUp;
 QAction* menuItem;
 int clickDelay;// = 500;
 int currentItemSelected;// = -1;
 QTimer* clickTimer;// = NULL;
 //Records the item index that the mouse is currenlty over
 int mouseItem;
 Logger* log;
 QWidget* currentWidget;

protected:
/*protected*/ BeanTableFrame* frame;

public:
 ActionJList(int index,BeanTableFrame* f);
 /*public*/ void mouseReleased(QMouseEvent* e);
 void showPopUp(QMouseEvent* e);
 void setCurrentItem(int current);
 /*public*/ void mouseClicked(QMouseEvent* e) ;
 /*public*/ void mousePressed(QMouseEvent* e) ;
 void selectListItem(int index);
 void openNewTableWindow(int index) ;

public slots:
 void onOpenNewTableWindow();

private:

};

/*static*/ class TabbedTableItemListArray
{

QString className;
QString itemText;
bool standardModel;// = true;
public:
TabbedTableItemListArray(QString aaClass, QString choice, bool stdModel);
bool getStandardTableModel() ;
QString getClassAsString();
QString getItemString() ;
};

/*static*/ class LTFTabbedTableItem : public QObject
{
 Q_OBJECT

    AbstractTableAction* tableAction;
    QString className;
    QString itemText;
    BeanTableDataModel* dataModel;
    JTable* dataTable;
    //ScrollPane dataScroll;
    Box* bottomBox;
    int bottomBoxIndex;	// index to insert extra stuff
    static /*final*/ int bottomStrutWidth;// = 20;

    bool standardModel;// = true;
    ListedTableFrame* frame;
    /*final*/ QWidget* dataPanel;// = new QWidget();
    QGridLayout* dataPanelLayout;

    public:
    LTFTabbedTableItem(QString aaClass, QString choice, bool stdModel, ListedTableFrame* frame);
    void createDataModel();
    void addPanelModel();
    bool getStandardTableModel();
    QString getClassAsString();
    QString getItemString();
    AbstractTableAction* getAAClass();
    QWidget* getPanel();
    JTable* getDataTable();
    void dispose();
    Logger* log;

public slots:
    void onPropertyVisible(bool);


 protected:
    /*protected*/ void addToBottomBox(QWidget* comp);
    friend class ListedTableFrame;
};
#endif // LISTEDTABLEFRAME_H
