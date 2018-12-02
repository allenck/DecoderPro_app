#ifndef ICONITEMPANEL_H
#define ICONITEMPANEL_H
#include "itempanel.h"
#include <QGraphicsSceneMouseEvent>
#include "logger.h"
#include "dragjlabel.h"
#include "exceptions.h"

class DataFlavor;
class QLabel;
class QPushButton;
class CatalogPanel;
class IconItemPanel : public ItemPanel
{
    Q_OBJECT
public:
    //explicit IconItemPanel(QWidget *parent = 0);
    /*public*/ IconItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget *parent);
    /*public*/ void init();
    /*public*/ virtual void initButtonPanel();
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* event);

signals:

public slots:
private:
    QMap<QString, NamedIcon*>* _iconMap;
    QMap<QString, NamedIcon*>* _tmpIconMap;
    QWidget* _iconPanel;
    QPushButton* _catalogButton;
    CatalogPanel* _catalog;
    JLabel* _selectedIcon;
    QPushButton* deleteIconButton;
    Logger* log;
    void hideCatalog();
    /*private*/ void putIcon(QString name, NamedIcon* icon);
    /*private*/ void clickEvent(QGraphicsSceneMouseEvent* event);
private slots:
    void on_catalogButton_clicked();

protected:
    /*protected*/ int _level;// = Editor::ICONS;      // sub classes can override (e.g. Background)
    /*protected*/ virtual QWidget* instructions();
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ virtual void addIconsToPanel(QMap<QString, NamedIcon *> *iconMap);
    /*protected*/ void removeIconFamiliesPanel();
    /*protected*/ void updateFamiliesPanel();
    /*protected*/ QString setIconName(QString name);
protected slots:
    /*protected*/ void addNewIcon();
    /*protected*/ void deleteIcon();

friend class ClockItemPanel;
friend class BackgroundItemPanel;
};

/*public*/ class IconDragJLabel :public DragJLabel // implements DropTargetListener
{
 Q_OBJECT
    int level;
 public:
    /*public*/ IconDragJLabel(DataFlavor* flavor, int zLevel, QWidget* parent);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    /*public*/ void /*dragExit(DropTargetEvent dte);*/ dragLeaveEvent(QDragLeaveEvent *);
    /*public*/ void /*dragEnter(DropTargetDragEvent dtde);*/ dragEnterEvent(QDragEnterEvent *);
//    /*public*/ void dragOver(DropTargetDragEvent dtde);
//    /*public*/ void dropActionChanged(DropTargetDragEvent dtde);
    /*public*/ void /*drop(DropTargetDropEvent e)*/ dropEvent(QDropEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
private:
    /*private*/ void accept(/*DropTarget*/QDropEvent* e, NamedIcon* newIcon);
    Logger* log;
    QString mimeData();
    IconItemPanel* parent;
};

#endif // ICONITEMPANEL_H
