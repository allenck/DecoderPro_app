#ifndef MULTISENSORITEMPANEL_H
#define MULTISENSORITEMPANEL_H
#include "tableitempanel.h"
#include "defaultlistselectionmodel.h"

class IconDialog;
class MultiSensorSelectionModel;
class MultiSensorItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit MultiSensorItemPanel(QWidget *parent = 0);
    /*public*/ MultiSensorItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor *editor, QWidget *parent = 0);
    /*public*/ static /*final*/ QStringList POSITION;//= {"first", "second", "third", "fourth", "fifth",
//                                         "sixth", "seventh", "eighth", "nineth", "tenth" };
    /*public*/ QVector<NamedBean *> getTableSelections();
    /*public*/ QVector<int> getPositions();
    /*public*/ bool getUpDown();
    /*public*/ void setSelection(NamedBean* bean);
    /*public*/ void setUpDown(bool upDown);
    /*public*/ bool oktoUpdate();
//    /*public*/ void updateFamilyIcons();
    static /*public*/ QString getPositionName(int index);

signals:

public slots:
    /*public*/ void clearSelections();
    void buttonLR_clicked();
    void buttonUD_clicked();

private:
    QWidget* _multiSensorPanel = nullptr;
    MultiSensorSelectionModel* _selectionModel = nullptr;
    bool _upDown = false;
    /*private*/ void makeMultiSensorPanel();

protected:
    /*protected*/ QWidget* initTablePanel(PickListModel* model, Editor* editor) override;
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey) override;
    /*protected*/ void initIconFamiliesPanel() override;
    /*protected*/ void setFamily(QString family) override;
    /*protected*/ void setSelections();
    /*protected*/ void openDialog(QString type, QString family, QMap<QString, NamedIcon*>* iconMap);
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon);
friend class MultiSensorSelectionModel;
friend class MSIconDragJLabel;
friend class MultiSensorIconDialog;
};

/*protected*/ class MultiSensorSelectionModel : public DefaultListSelectionModel
{
    Q_OBJECT

    QVector<NamedBean*> _selections;
    QVector<int> _positions;
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
    /*protected*/ QVector<NamedBean *> getSelections();
    /*protected*/ QVector<int> getPositions();
    /*protected*/ int getNextPosition() ;
    /*protected*/ void setPositionRange(int size);
friend class MultiSensorItemPanel;
friend class MSIconDragJLabel;
};

/*protected*/ class MSIconDragJLabel : public DragJLabel
{
 Q_OBJECT
  QMap <QString, NamedIcon*>* iconMap = nullptr;
  MultiSensorItemPanel* self;
 public:
  //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
  /*public*/ MSIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, NamedIcon* icon, MultiSensorItemPanel* self);
  /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
  /*public*/ QObject* getTransferData(DataFlavor* flavor)throw (UnsupportedFlavorException,IOException);
  QByteArray mimeData();

protected:
  /*protected*/ bool okToDrag();

};

#endif // MULTISENSORITEMPANEL_H
