#ifndef ADDENTRYEXITPAIRPANEL_H
#define ADDENTRYEXITPAIRPANEL_H
#include <qstringlist.h>
#include "jmripanel.h"
#include "abstracttablemodel.h"
#include "liblayouteditor_global.h"
#include "propertychangelistener.h"

class QPushButton;
class JTextField;
class JActionEvent;
class QCheckBox;
class NamedBean;
class ValidPoints;
class PropertyChangeEvent;
class JTable;
class AEPTableModel;
class QSortFilterProxyModel;
class JmriJFrame;
class QLabel;
class LayoutEditor;
class QComboBox;
class EntryExitPairs;
class LIBLAYOUTEDITORSHARED_EXPORT AddEntryExitPairPanel : public JmriPanel
{
 Q_OBJECT
public:
 explicit AddEntryExitPairPanel(LayoutEditor* panel, QWidget *parent = 0);

signals:

public slots:
 void on_selectPanel_currentIndexChanged(QString);

private:
 //private static final long serialVersionUID = 4871721972825766572L;
 QComboBox* selectPanel;// = new QComboBox();
 QComboBox* fromPoint;// = new QComboBox();
 QComboBox* toPoint;// = new QComboBox();

 QStringList interlockTypes;// = {"Set Turnouts Only", "Set Turnouts and SignalMasts", "Full Interlock"};
 QComboBox* typeBox;// = new QComboBox(interlockTypes);

 QList<LayoutEditor*>* panels;

 EntryExitPairs* nxPairs;// = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");

 //protected static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.EntryExitBundle");
 LayoutEditor* panel;
 JmriJFrame* entryExitFrame;// = NULL;
 QLabel* sourceLabel;// = new JLabel();

 QSortFilterProxyModel* nxSorter;
 JTable* nxDataTable;
 //JScrollPane nxDataScroll;

 AEPTableModel* nxModel;


  ValidPoints* getValidPointFromCombo(QComboBox* box);
  QList<ValidPoints*> validPoints;// = new ArrayList<ValidPoints>();
  /*private*/ void selectPointsFromPanel();
  void addPointToCombo(QString signalMastName, QString sensorName);
  JmriJFrame* optionsFrame;// = NULL;
  QWidget* optionsPane;// = NULL;
  QStringList clearOptions;// = {"Prompt User", "Clear Route", "Cancel Route"};
  QComboBox* clearEntry;// = new QComboBox(clearOptions);
  JTextField* durationSetting;// = new JTextField(10);
  QStringList colorText;// = {"None", "Black", "DarkGray", "Gray",
//      "LightGray", "White", "Red", "Pink", "Orange",
//      "Yellow", "Green", "Blue", "Magenta", "Cyan"};
  QList<QColor> colorCode;// = {NULL, Color.black, Color.darkGray, Color.gray,
//      Color.lightGray, Color.white, Color.red, Color.pink, Color.orange,
//      Color.yellow, Color.green, Color.blue, Color.magenta, Color.cyan};
  int numColors;// = 14;  // number of entries in the above arrays
  QCheckBox* dispatcherUse;// = new JCheckBox(Bundle.getMessage("DispatcherInt"));

  QComboBox* settingTrackColorBox;// = new QComboBox();
  /*private*/ void initializeColorCombo(QComboBox* colorCombo) ;
  /*private*/ void setColorCombo(QComboBox* colorCombo, QColor color);
  /*private*/ QColor getSelectedColor(QComboBox* colorCombo);
  bool doFromCombo;
  QStringList fromSet;
  QStringList toSet;
  /*private*/ void selectPoints(LayoutEditor* panel);

private slots:
 /*private*/ void addButton();
  /*private*/ void autoDiscovery();
  //void propertyChange(PropertyChangeEvent*);
  void on_settingtrackColorBox_currentIndexChanged(QString);
  void optionSaveButton();

protected:
  /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* sample);

protected slots:
  /*protected*/ void optionWindow(JActionEvent* e = 0);

 friend class AddEntryExitPairFrame;
 friend class AEPTableModel;
 friend class PropertyNXListener;
};
/*static*/ class ValidPoints : public QObject
{
 Q_OBJECT
    NamedBean* bean;
    QString description;
 public:
    ValidPoints(NamedBean* bean, QString description);
    NamedBean* getPoint();
    QString getDescription() ;
};
class AEPTableModel : public AbstractTableModel /*implements PropertyChangeListener*/
{
 Q_OBJECT
    /**
     *
     */
   // private static final long serialVersionUID = 3291217259103678604L;

public:
 enum COLUMNS
 {
  FROMPOINTCOL = 0,
  TOPOINTCOL = 1,
  ACTIVECOL = 2,
  CLEARCOL = 3,
  BOTHWAYCOL = 4,
  DELETECOL = 5,
  TYPECOL = 6,
  ENABLEDCOL = 7
 };

  static int NUMCOL;// = ENABLEDCOL + 1;//needs a method to for when panel changes
    //need a method to delete an item
    //Possibly also to set a route.
    //Add a propertychange listener to hear when the route goes active.
    AEPTableModel(LayoutEditor* panel, AddEntryExitPairPanel* parent);
    void setPanel(LayoutEditor* panel) ;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ void configureTable(JTable* table);

    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ QString getColumnClass(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;

private:
    LayoutEditor* panel;
    AddEntryExitPairPanel* parent;
    QObjectList source;// = NULL;
    QObjectList dest;// = NULL;

    void updateNameList();
    int _rowCount;// = 0;
    Logger* log;
    static QStringList NXTYPE_NAMES;// = {"Turnout", "SignalMast", "Full InterLock"};

protected:
    /*protected*/ void deleteEntryExit(int row, int col);
    /*protected*/ void configDeleteColumn(JTable* table);

private:

    QString isPairActive(int row) const;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

    friend class AddEntryExitPairPanel;

};

class PropertyNXListener : public PropertyChangeListener
{
 Q_OBJECT
 AddEntryExitPairPanel* panel;
public:
 PropertyNXListener(AddEntryExitPairPanel* panel) {this->panel = panel;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};

#endif // ADDENTRYEXITPAIRPANEL_H
