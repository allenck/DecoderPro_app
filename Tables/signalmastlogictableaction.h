#ifndef SIGNALMASTLOGICTABLEACTION_H
#define SIGNALMASTLOGICTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"

class SignalMastLogicManager;
class QLabel;
class SignalMast;
class SignalMastLogic;
class SignallingAction;
class SignalMastLogicTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    SignalMastLogicTableAction(QObject* parent = 0);
    Q_INVOKABLE /*public*/ SignalMastLogicTableAction(QString s, QObject* parent);
    ~SignalMastLogicTableAction() {}
    SignalMastLogicTableAction(const SignalMastLogicTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setMenuBar(BeanTableFrame* f);

public slots:
    /*public*/ void actionPerformed(ActionEvent* /*e*/);

private:
    void common();
    SignallingAction* sigLog;// = new jmri.jmrit.signalling.SignallingAction();
    QList<QHash<SignalMastLogic*, SignalMast*>*>* signalMastLogicList;// = null;
    QWidget* update;
    bool suppressUpdate;// = false;
    JmriJFrame* signalMastLogicFrame;// = null;
    QLabel* sourceLabel;// = new JLabel();
    JmriJFrame* finalF;

private slots:
    void autoCreatePairs(/*jmri.util.JmriJFrame f*/);
    void On_autoGenSections();

   protected:
    /*protected*/ QString getClassName();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget() ;

    protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0) ;

friend class SmlBeanTableDataModel;
};
Q_DECLARE_METATYPE(SignalMastLogicTableAction)

class SmlBeanTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
    SignalMastLogicTableAction* act;
public:
    enum COLUMNS
    {
     SOURCECOL = 0,
     SOURCEAPPCOL = 1,
     DESTCOL = 2,
     DESTAPPCOL = 3,
     COMCOL = 4,
     DELCOL = 5,
     ENABLECOL = 6,
     EDITLOGICCOL = 7
    };
    SmlBeanTableDataModel(SignalMastLogicTableAction* act);
    //We have to set a manager first off, but this gets replaced.
    /*public*/ QString getValue(QString s);

    /*public*/ void clickOn(NamedBean* t);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ SignalMast* getDestMastFromRow(int row) const;
    /*public*/ SignalMastLogic* getLogicFromRow(int row) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ void configureTable(JTable* table);
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*synchronized*/ /*public*/ void dispose() ;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    void editLogic(int row, int col);
    void deleteLogic(int row, int col);
    Logger* log;
    QList<SignalMastLogic*> source;// = getManager().getSignalMastLogicList();

protected:
    /*protected*/ Manager* getManager();
    /*protected*/ QString getMasterClassName() ;
    /*protected*/ void configDeleteColumn(JTable* table);
    /*protected*/ /*synchronized*/ void updateNameList();
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
    /*protected*/ QString getBeanType();
    /*protected*/ void showPopup(QMouseEvent* e);

};

#endif // SIGNALMASTLOGICTABLEACTION_H
