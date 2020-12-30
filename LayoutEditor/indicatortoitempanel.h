#ifndef INDICATORTOITEMPANEL_H
#define INDICATORTOITEMPANEL_H
#include "tableitempanel.h"

class DetectionPanel;
class IndicatorTOItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit IndicatorTOItemPanel(QWidget *parent = 0);
    /*final*/ static QStringList STATUS_KEYS;// = {"ClearTrack", "OccupiedTrack", "PositionTrack",
//                            "AllocatedTrack", "DontUseTrack", "ErrorTrack"};
    /*public*/ IndicatorTOItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    /*public*/ void init();
    /*public*/ void init(ActionListener* doneAction);
    /*public*/ void initUpdate(ActionListener* doneAction, QMap<QString, QMap<QString, NamedIcon *> *> *iconMaps);
    /****************** pseudo inheritance *********************/

    /*public*/ bool getShowTrainName();
    /*public*/ QString getOccSensor();
    /*public*/ QString getOccBlock();
    /*public*/ void setOccDetector(QString name);
    /*public*/ QStringList getPaths() ;
    /*public*/ void setPaths(QStringList paths);
    /*public*/ QMap<QString, QMap<QString, NamedIcon *> *> *getIconMaps();
    /*public*/ void setShowTrainName(bool show);
    /*public*/ void dispose();

signals:

public slots:
private:
    /*private*/ DetectionPanel*  _detectPanel;
    /*private*/ QWidget*          _tablePanel;
    /*private*/ JTextField* 		_familyName;
    /*private*/ void checkCurrentMaps(QMap<QString, QMap<QString, NamedIcon *> *> *iconMaps);
    void createNewFamily(QString family);
    /*private*/ void openStatusEditDialog(QString key);

 Logger* log;
protected:
    /*protected*/ QMap<QString, QMap<QString, NamedIcon*>*>* _iconGroupsMap;
    /*protected*/ QMap<QString, QMap<QString, NamedIcon*>*>* _updateGroupsMap;
    /*protected*/ QWidget* initTablePanel(PickListModel* model, Editor* editor);
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ void addIcons2Panel(QMap<QString, QMap<QString, NamedIcon*>*>* map);
    /*protected*/ void hideIcons();
    /*protected*/ void updateIconGroupsMap(QString key, QMap<QString, NamedIcon*>* iconMap);
    /*protected*/ void setFamily(QString family) ;
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon);
    /**
    *  CENTER Panel
    */
    /*protected*/ void showIcons();
    /*protected*/ void addCreateDeleteFamilyButtons() override;
    /*protected*/ void renameFamily();
    /*protected*/ JPanel* makeItemButtonPanel() override;
    /*protected*/ bool newFamilyDialog() override;


protected slots:
 /*protected*/ void resetFamiliesPanel();

friend class ITOIconDragJLabel;
friend class EditIconActionListener;
friend class IndicatorTOIconDialog;
};

/*protected*/ class ITOIconDragJLabel : public DragJLabel
{
    Q_OBJECT
    IndicatorTOItemPanel* parent;

public:
    /*public*/ ITOIconDragJLabel(DataFlavor* flavor,IndicatorTOItemPanel* parent);
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    QByteArray mimeData();
};

class EditIconActionListener : public ActionListener
{
 Q_OBJECT
 QString key;
 IndicatorTOItemPanel* parent;
public:
void init(QString k, IndicatorTOItemPanel* parent);
public slots:
/*public*/ void actionPerformed(JActionEvent* a = 0);

protected:

};

#endif // INDICATORTOITEMPANEL_H
