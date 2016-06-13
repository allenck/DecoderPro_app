#ifndef MULTISENSORITEMPANEL_H
#define MULTISENSORITEMPANEL_H
#include "tableitempanel.h"
#include "defaultlistselectionmodel.h"

class MultiSensorSelectionModel;
class MultiSensorItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit MultiSensorItemPanel(QWidget *parent = 0);
    /*public*/ MultiSensorItemPanel(JmriJFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    /*public*/ static /*final*/ QStringList POSITION;//= {"first", "second", "third", "fourth", "fifth",
//                                         "sixth", "seventh", "eighth", "nineth", "tenth" };
    /*public*/ QList<NamedBean*>* getTableSelections();
    /*public*/ QList<int> getPositions();
    /*public*/ bool getUpDown();
    /*public*/ void setSelection(NamedBean* bean);
    /*public*/ void setUpDown(bool upDown);

signals:

public slots:
    /*public*/ void clearSelections();
    void buttonLR_clicked();
    void buttonUD_clicked();

private:
    QWidget* _multiSensorPanel;
    MultiSensorSelectionModel* _selectionModel;
    bool _upDown;// = false;
    /*private*/ void makeMultiSensorPanel();

protected:
    /*protected*/ QWidget* initTablePanel(PickListModel* model, Editor* editor);
    /*protected*/ void makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString displayKey);
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ void setFamily(QString family);
    /*protected*/ void setSelections();
    /*protected*/ void openEditDialog();
    /*protected*/ void createNewFamily(QString type);
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QHash<QString, NamedIcon*>* map);
friend class MultiSensorSelectionModel;
friend class MSIconDragJLabel;
};

/*protected*/ class MultiSensorSelectionModel : public DefaultListSelectionModel
{
    Q_OBJECT

    QList<NamedBean*>* _selections;
    QList<int> _positions;
    int _nextPosition;
    PickListModel* _tableModel;
    MultiSensorItemPanel* self;

public:
    MultiSensorSelectionModel(PickListModel* tableModel, MultiSensorItemPanel* self);
    /*public*/ bool isSelectedIndex(int index);
    /*public*/ void clearSelection();
    /*public*/ void addSelectionInterval(int index0, int index1);
    /*public*/ void setSelectionInterval(int row, int index1);
private:
    Logger* log;
protected:
    /*protected*/ QList<NamedBean*>* getSelections();
    /*protected*/ QList<int> getPositions();
    /*protected*/ int getNextPosition() ;
    /*protected*/ void setPositionRange(int size);
friend class MultiSensorItemPanel;
friend class MSIconDragJLabel;
};
/*protected*/ class MSIconDragJLabel : public DragJLabel
{
 Q_OBJECT
  QHash <QString, NamedIcon*>* iconMap;
  MultiSensorItemPanel* self;
 public:
        //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
        /*public*/ MSIconDragJLabel(DataFlavor* flavor, QHash <QString, NamedIcon*>* map, MultiSensorItemPanel* self);
        /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
  /*public*/ QObject* getTransferData(DataFlavor* flavor)throw (UnsupportedFlavorException,IOException);
};

#endif // MULTISENSORITEMPANEL_H
