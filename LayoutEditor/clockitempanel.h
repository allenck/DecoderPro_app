#ifndef CLOCKITEMPANEL_H
#define CLOCKITEMPANEL_H
#include "iconitempanel.h"

class ClockItemPanel : public IconItemPanel
{
    Q_OBJECT
public:
    //explicit ClockItemPanel(QWidget *parent = 0);
    /*public*/ ClockItemPanel(DisplayFrame* parentFrame, QString type, Editor* editor, QWidget *parent);
    /*public*/ void initButtonPanel();

signals:

public slots:
    void sceneClicked(QGraphicsSceneMouseEvent*);
private:
    QHash<QString, NamedIcon*>* _iconMap;

protected:
    /*protected*/ JPanel *instructions(bool)override;
    /*protected*/ void addIconsToPanel(QMap<QString, NamedIcon *> *iconMap) override;

    friend class ClockDragJLabel;
};

/*public*/ class ClockDragJLabel : public DragJLabel
{

    /*public*/ ClockDragJLabel(DataFlavor* flavor, QWidget* parent) ;
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
private:
    Logger * log;
    friend class ClockItemPanel;
};

#endif // CLOCKITEMPANEL_H
