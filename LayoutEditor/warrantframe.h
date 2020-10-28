#ifndef WARRANTFRAME_H
#define WARRANTFRAME_H
#include "warrantroute.h"
#include <QAbstractTableModel>
#include "windowlistener.h"
#include "throttlesetting.h"
#include "liblayouteditor_global.h"

class DecimalFormat;
class JTable;
class QPushButton;
class OBlock;
class RouteFinder;
class QRadioButton;
class QComboBox;
class JTextField;
class DccLocoAddress;
class LearnThrottleFrame;
class ThrottleSetting;
class BlockOrder;
class QMenu;
class QTableView;
class ThrottleTableModel;
class RouteTableModel;
class Warrant;
class RosterEntry;
class LIBLAYOUTEDITORSHARED_EXPORT WarrantFrame : public WarrantRoute
{
    Q_OBJECT
public:
    //explicit WarrantFrame(QWidget *parent = 0);
    static int STRUT_SIZE;// = 10;
    static int ROW_HEIGHT;
    /*public*/ WarrantFrame(QString warrantName, QWidget *parent = 0);
    /*public*/ WarrantFrame(Warrant* warrant, bool create, QWidget *parent = 0);
    /*public*/ QString getClassName();
    /*public*/ bool isRunning();

signals:

public slots:
    void on_throttleFactorBoxLeave();
    void on_runButtonClicked();
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    QMenu* _warrantMenu;

    /*private*/ Warrant*             _warrant;
    /*private*/ Warrant* _saveWarrant;
    /*private*/ RouteTableModel*     _routeModel;
    /*private*/ ThrottleTableModel*  _commandModel;
    /*private*/ JTable*      _commandTable;
    ///*private*/ JScrollPane _throttlePane;
    /*private*/ bool     _create;
    /*private*/ void setup(Warrant*);
    /*private*/ void init0();

    /*private*/ QList <BlockOrder*>* _orders;// = new QList <BlockOrder*>();
    /*private*/ QList <ThrottleSetting*>* _throttleCommands;// = new QList <ThrottleSetting*>();
    /*private*/ long 			_startTime;
    /*private*/ LearnThrottleFrame* _learnThrottle;// = null;
    /*private*/ DccLocoAddress* 	_locoAddress;// = null;

    BlockOrder*  _originBlockOrder;
    BlockOrder*  _destBlockOrder;
    BlockOrder*  _viaBlockOrder;
    BlockOrder*  _avoidBlockOrder;

    JTextField*  _sysNameBox;
    JTextField*  _userNameBox;
    JTextField*  _originBlockBox;// = new JTextField();
    JTextField*  _destBlockBox;// = new JTextField();
    JTextField*  _viaBlockBox;// =  new JTextField();
    JTextField*  _avoidBlockBox;// =  new JTextField();
    QComboBox*   _originPathBox;// = new QComboBox();
    QComboBox*   _destPathBox;// = new QComboBox();
    QComboBox*   _viaPathBox;// = new QComboBox();
    QComboBox*   _avoidPathBox;// = new QComboBox();
    QComboBox*   _originPortalBox;// = new QComboBox();     // exit
    QComboBox*   _destPortalBox;// = new QComboBox();       // entrance
    int _thisActionEventId;     // id for the listener of the above items

    QTabWidget* _tabbedPane;
    QWidget*      _routePanel;
    QWidget*      _commandPanel;
    RosterEntry* _train;
    QComboBox*   _rosterBox;// = new QComboBox();
    JTextField*  _dccNumBox;// = new JTextField();
    JTextField*  _trainNameBox;// = new JTextField();
    JTextField*  _throttleFactorBox;// =  new JTextField();
    QRadioButton* _runProtect;// = new QRadioButton(rb.getString("RunProtected"), true);
    QRadioButton* _runBlind;// = new QRadioButton(rb.getString("RunBlind"), false);
    QRadioButton* _halt;// = new QRadioButton(rb.getString("Halt"), false);
    QRadioButton* _resume;// = new QRadioButton(rb.getString("Resume"), false);
    QRadioButton* _abort;// = new QRadioButton(rb.getString("Abort"), false);
    QRadioButton* _invisible;// = new QRadioButton();
    JTextField*  _statusBox;// = new JTextField(30);

    JTextField*  _searchDepth;// =  new JTextField();
    JTextField*  _searchStatus;// =  new JTextField();
    RouteFinder* _routeFinder;
    /*private*/ int _maxBlocks;// = 20;
    JFrame*      _debugFrame;
    QDialog*     _pickRouteDialog;
    QPushButton*  _calculateButton;
    QPushButton* _stopButton;
    QPushButton* _startButton;
    static QColor myGreen;// = new Color(0, 100, 0);

    /*private*/ void init();
    /*private*/ void calculate();
    /*private*/ void clearWarrant();
    /*private*/ void setPortalBox(QComboBox* pathBox, QComboBox* portalBox, BlockOrder* order);
//    /*private*/ bool setOriginBlock();
//    /*private*/ bool setDestinationBlock();
//    /*private*/ bool setViaBlock();
//    /*private*/ bool setAvoidBlock();
    /*private*/ bool setTrainInfo(QString name, bool isAddress);
    /*private*/ OBlock* getEndPointBlock(JTextField* textBox);
    /*private*/ void makeMenus();
    /*private*/ QWidget* makeTopPanel();
    /*private*/ QWidget* makeFindRouteTabPanel();
    /*private*/ QWidget* makeSetPowerTabPanel();
    /*private*/ QWidget* makeTabMidPanel();
    /*private*/ QWidget* makeEditableButtonPanel();
//    /*private*/ QWidget* makeTextBoxPanel(bool vertical, JTextField* textField, QString label, bool editable);
    /*private*/ QString  getIdleMessage();
    /*private*/ QWidget* makeBorderedTrainPanel();
    /*private*/ QWidget* makeRecordPanel();
    /*private*/ QWidget* makePlaybackPanel();
    /*private*/ void runTrain(int mode);
    /*private*/ QString checkTrainId();
    /*private*/ QString setupRun();
    /*private*/ void doControlCommand(int cmd);
    /*private*/ void showCommands(bool setCmds);

    Logger* log;
    /*private*/ void clearCommands();
    /*private*/ void copy();
    /*private*/ void close() ;
    /*private*/ void setThrottleCommand(QString cmd, QString value, QString bName);
    /*private*/ bool save();
    /*private*/ QWidget* makeThrottleTablePanel();
    float _speed;

private slots:
    void on_deleteButtonClicked();
    /*private*/ void insertRow();
    /*private*/ void deleteRow();

 protected:
//    /*protected*/ RosterEntry* getTrain();
    /*protected*/ WarrantFrame(Warrant* w);
    /*protected*/ void stopRunTrain();
    /*protected*/ Warrant* getWarrant();
    /*protected*/ void setThrottleCommand(QString cmd, QString value);
    /*protected*/ void setSpeedCommand(float speed);
    /*protected*/ void setWarrant(Warrant* w);
    /*protected*/ void setStatusText(QString msg, QColor c);

friend class LearnThrottleFrame;
friend class WFRouteTableModel;
friend class ThrottleTableModel;
friend class WarrantTableAction;
friend class WarrantTableModel;
friend class WFWindowListener;
friend class LTFWindowListener;
};
/************************* Route Table ******************************/
class WFRouteTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    WarrantFrame* frame;
public:
    enum COLUMNS
    {
     BLOCK_COLUMN = 0,
     ENTER_PORTAL_COL =1,
     PATH_COLUMN = 2,
     DEST_PORTAL_COL = 3,
     NUMCOLS = 4
    };
    /*public*/ WFRouteTableModel(WarrantFrame* frame);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    void fireTableDataChanged();
};


/************************* Throttle Table ******************************/

class ThrottleTableModel : public AbstractTableModel
{
    Q_OBJECT
private:
    WarrantFrame* frame;
    DecimalFormat* threeDigit;// = DecimalFormat("0.000");

public:
    enum COLUMNS
    {
     ROW_NUM = 0,
     TIME_COLUMN = 1,
     COMMAND_COLUMN =2,
     VALUE_COLUMN =3,
     BLOCK_COLUMN = 4,
     SPEED_COLUMN = 5,
     NUMCOLS = 6
    };
    /*public*/ ThrottleTableModel(WarrantFrame* frame);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
//    /*private*/ QString getPreviousBlockName(int row);
    /*private*/ NamedBeanHandle <NamedBean*>* getPreviousBlockHandle(int row);
    void fireTableDataChanged();
};

class WFWindowListener : public WindowListener
{
 Q_OBJECT

 WarrantFrame* frame;
public:
 WFWindowListener(WarrantFrame* frame) { this->frame = frame;}
 void windowClosing(QCloseEvent */*e*/)
 {
  frame->close();
 }
};

#endif // WARRANTFRAME_H
