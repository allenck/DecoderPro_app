#ifndef INDICATORITEMPANEL_H
#define INDICATORITEMPANEL_H
#include "familyitempanel.h"
#include "dragjlabel.h"

class DetectionPanel;
class IndicatorItemPanel : public FamilyItemPanel
{
    Q_OBJECT
public:
    //explicit IndicatorItemPanel(QWidget *parent = 0);
    /*public*/ IndicatorItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget *parent = nullptr);
    /*public*/ void init();
    /*public*/ void init(ActionListener* doneAction, QMap<QString, NamedIcon *> *iconMap = 0);
    /*public*/ void dispose();
    /*public*/ bool getShowTrainName();
    /*public*/ void setShowTrainName(bool show);
    /*public*/ QString getOccSensor();
    /*public*/ QString getOccBlock();
    /*public*/ void setOccDetector(QString name);
    /*public*/ QStringList getPaths();
    /*public*/ void setPaths(QStringList paths);

signals:

public slots:
private:
    /*private*/ DetectionPanel*  _detectPanel;
    Logger* log;
protected:
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, NamedIcon* icon);
friend class IndicatorDragJLabel;
};
/*protected*/ class IndicatorDragJLabel : public DragJLabel {
    Q_OBJECT
    IndicatorItemPanel* self;
    QMap <QString, NamedIcon*>* iconMap;
public:
    /*public*/ IndicatorDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon*>* map,IndicatorItemPanel* self) ;
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) ;
  QByteArray mimeData();
};

#endif // INDICATORITEMPANEL_H
