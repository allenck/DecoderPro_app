#ifndef TRACKERTABLEACTION_H
#define TRACKERTABLEACTION_H
#include "abstractaction.h"
#include "jmrijframe.h"
#include "abstracttablemodel.h"
#include "windowlistener.h"
#include "libtables_global.h"
#include "abstractinstanceinitializer.h"

class TrackerTableModel;
class JDialog;
class JTextField;
class OBlock;
class TableFrame;
class Tracker;
class LIBTABLESSHARED_EXPORT TrackerTableAction : public AbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit TrackerTableAction( QObject *parent = 0);
 ~TrackerTableAction() {}
 TrackerTableAction(const TrackerTableAction&) : AbstractAction() {}
 static /*public*/ Tracker* markNewTracker(OBlock* block, QString name);
 static /*public*/ void stopTracker(Tracker* t) ;
 static /*public*/ void stopTrackerIn(OBlock* block);
 /*public*/ static TrackerTableAction* getInstance(QObject* parent);

 //@ServiceProvider(service = InstanceInitializer.class)
 /*public*/ /*static*/ class Initializer : public AbstractInstanceInitializer {

     //@Override
     //Nonnull
     /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) const override{
         if (type == ("TrackerTableAction")) {
             return new TrackerTableAction(tr("Trackers"), nullptr);
         }
         return AbstractInstanceInitializer::getDefault(type);
     }

     //@Override
     //@Nonnull
     /*public*/ QSet<QString>* getInitalizes() {
         QSet<QString>* set = AbstractInstanceInitializer::getInitalizes();
         set->insert("TrackerTableAction");
         return set;
     }
 };
signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0)override;

private:
 static int STRUT_SIZE;// = 10;

 /*private*/ static TrackerTableAction* _instance;
 /*private*/ static QList<Tracker*> _trackerList;// = new ArrayList<Tracker>();
 /*private*/ static TableFrame* _frame;
 /*private*/ TrackerTableAction(QString menuOption,QObject *parent);
 void common();
 /*synchronized*/ static /*public*/ bool mouseClickedOnBlock(OBlock* block);
friend class WarrantTableAction;
friend class TableFrame;
friend class TrackerTableModel;
friend class Initializer;
};
Q_DECLARE_METATYPE(TrackerTableAction)

class TableFrame : public JmriJFrame, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
 ///*private*/ static final long serialVersionUID = -56337259221744388L;
 /*private*/ TrackerTableModel* _model;
 /*private*/ JmriJFrame* _pickFrame;
 JDialog* _dialog;
 JTextField* _trainNameBox;// = new JTextField(30);
 JTextField* _trainLocationBox;// = new JTextField(30);
 JTextField* _status;// = new JTextField(80);
 QStringList _statusHistory;// = new QStringList();
 /*public*/ static int _maxHistorySize;// = 20;
 bool _appendStatus;// = false;
 QHash<OBlock*, QList<Tracker*> > _blocks;// = new HashMap<OBlock, List<Tracker>>();

public:
TableFrame();
 /*public*/ Tracker* addTracker(OBlock* block, QString name) ;
 void openPickList() ;

 /*public*/ void mouseClicked(QMouseEvent* event) ;
 /*public*/ void mousePressed(QMouseEvent* event) ;
 /*public*/ void mouseEntered(QMouseEvent* event);
 /*public*/ void mouseExited(QMouseEvent* event);
 /*public*/ void mouseReleased(QMouseEvent* event);
 /*public*/ QString getClassName();
 QObject* pself() override {return (QObject*)this;}


public slots:
 void on_doneButton_clicked();
 void on_refreshClicked();
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

private:
 /*private*/ void newTrackerDialog();
 /*private*/ QWidget* makeTrackerNamePanel();
 /*private*/ QWidget* makeDoneButtonPanel() ;
 /*private*/ bool doDoneAction() ;
 static bool nameInuse(QString name) ;
 /*private*/ void addBlockListeners(Tracker* tracker) ;
 /*private*/ void addBlockListener(OBlock* block, Tracker* tracker);
 /*private*/ void adjustBlockListeners(QList<OBlock*> oldRange, QList<OBlock*> newRange, Tracker* tracker) ;
 /*private*/ void removeBlockListeners(QList<OBlock*> range, Tracker* tracker);
 /*private*/ void removeBlockListener(OBlock* b, Tracker* tracker);
 /*private*/ void processTrackerStateChange(Tracker* tracker, OBlock* block, int state) ;
 Logger* log;
 /*private*/ void setStatus(QString msg) ;

protected:
/*protected*/ bool mouseClickedOnBlock(OBlock* block) ;
static /*protected*/ QString blockInUse(OBlock* b) ;
/*protected*/ void stopTrain(Tracker* t) ;
friend class TrackerTableAction;
friend class TrackerTableModel;
};

/*static*/ class TrackerTableModel : public AbstractTableModel
{
 enum COLUMNS
 {
 NAME_COL = 0,
 STATUS_COL = 1,
 STOP_COL = 2,
 NUMCOLS = 3
};
TableFrame* _parent;

/*public*/ TrackerTableModel(TableFrame* f );
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ int getPreferredWidth(int col);
    //@ServiceProvider(service = InstanceInitializer.class)
    /*public*/ /*static*/ class Initializer : AbstractInstanceInitializer {

        //@Override
        //@Nonnull
        /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) {
            if (type == ("TrackerTableAction")) {
                return new TrackerTableAction(tr("Trackers"),this);
            }
            return AbstractInstanceInitializer::getDefault(type);
        }

        //@Override
        //@Nonnull
        /*public*/ QSet</*Class<?>*/QString>* getInitalizes() {
            QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
            set->insert("TrackerTableAction");
            return set;
        }
    };
friend class TableFrame;
}; // end TrackerTableModel

class TTAWindowListener : public WindowListener
{
 Q_OBJECT
 TableFrame* frame;
 TTAWindowListener(TableFrame* frame) { this->frame = frame;}
 void windowClosing(QCloseEvent */*e*/) { frame->dispose();}
 friend class TableFrame;
};

#endif // TRACKERTABLEACTION_H
