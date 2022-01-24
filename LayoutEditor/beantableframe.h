#ifndef BEANTABLEFRAME_H
#define BEANTABLEFRAME_H
#include "../LayoutEditor/jmrijframe.h"
#include "liblayouteditor_global.h"

class Box;
class JTable;
class BeanTableDataModel;
class LIBLAYOUTEDITORSHARED_EXPORT BeanTableFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit BeanTableFrame(QWidget *parent = 0);
    /*public*/ BeanTableFrame(QString s, QWidget *parent = 0);
    /*public*/ BeanTableFrame(BeanTableDataModel* model, QString helpTarget, JTable* dataTab, QWidget *parent = 0);
    /*public*/ void dispose();
    /*public*/ QString getClassName();

signals:

public slots:
private:
    BeanTableDataModel*		dataModel;
    void common();
    JTable*			dataTable;
    //JScrollPane 		dataScroll;
    QWidget* bottomBox;		// panel at bottom for extra buttons etc
    int bottomBoxIndex;	// index to insert extra stuff
    static /*final*/ int bottomStrutWidth;// = 20;
    virtual void extras();
    static Logger* log;

protected:
    virtual /*protected*/ void addToBottomBox(QWidget* comp, QString c);
    /*protected*/ QWidget* getBottomBox();
friend class SensorTableAction;
friend class TurnoutTableAction;
friend class AudioTableFrame;
friend class BlockTableFrame;
friend class BlockTableAction;
friend class IdTagTableAction;
friend class OBlockTableFrame;
};

#endif // BEANTABLEFRAME_H
