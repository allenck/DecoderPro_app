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
    /*public*/ void setMenuBar(BeanTableFrame* f) override;

public slots:

private:
    void common();
    SignallingAction* sigLog;// = new jmri.jmrit.signalling.SignallingAction();
    QList<QHash<SignalMastLogic*, SignalMast*>*>* signalMastLogicList = nullptr;
    QWidget* update;
    bool suppressUpdate;// = false;
    JmriJFrame* signalMastLogicFrame;// = null;
    QLabel* sourceLabel;// = new JLabel();
    JmriJFrame* finalF;

private slots:
    void autoCreatePairs(/*jmri.util.JmriJFrame f*/);

   protected:
    /*protected*/ QString getClassName() override;
    /*protected*/ void createModel() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override ;

    protected slots:
    /*protected*/ void addPressed(JActionEvent* =0)override;

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
     EDITLOGICCOL = 7,
     MAXSPEEDCOL = 8,
     COLUMNCOUNT = 9
    };
    SmlBeanTableDataModel(SignalMastLogicTableAction* act);
    //We have to set a manager first off, but this gets replaced.
    /*public*/ QString getValue(QString s) const override;

    /*public*/ void clickOn(NamedBean* t) override;
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ QString getColumnClass(int col) const override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ SignalMast* getDestMastFromRow(int row) const;
    /*public*/ SignalMastLogic* getLogicFromRow(int row) const;
    /*public*/ int getPreferredWidth(int col) override;
    /*public*/ void configureTable(JTable* table) override;
//    /*public*/ NamedBean* getBySystemName(QString name) const;
//    /*public*/ NamedBean* getByUserName(QString name);
    /*synchronized*/ /*public*/ void dispose() ;
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
    void editLogic(int row, int col);
    void deleteLogic(int row, int col);
    Logger* log;
    QList<SignalMastLogic*> source;// = getManager().getSignalMastLogicList();

protected:
    /*protected*/ Manager *getManager() override;
    /*protected*/ QString getMasterClassName() override;
    /*protected*/ void configDeleteColumn(JTable* table)override;
    /*protected*/ /*synchronized*/ void updateNameList()override;
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e)override;
    /*protected*/ QString getBeanType()override;
    /*protected*/ void showPopup(QMouseEvent* e);
    /*protected*/ void setColumnIdentities(JTable* table) override;

};

#endif // SIGNALMASTLOGICTABLEACTION_H
