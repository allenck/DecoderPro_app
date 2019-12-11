#ifndef ICONITEMPANEL_H
#define ICONITEMPANEL_H
#include "itempanel.h"
#include <QGraphicsSceneMouseEvent>
#include "logger.h"
#include "dragjlabel.h"
#include "exceptions.h"
#include "jpanel.h"

class IconDisplayPanel;
class ActionListener;
class DataFlavor;
class QLabel;
class QPushButton;
class CatalogPanel;
class IconItemPanel : public ItemPanel
{
    Q_OBJECT
public:
    //explicit IconItemPanel(QWidget *parent = 0);
    /*public*/ IconItemPanel(DisplayFrame* parentFrame, QString type, Editor* editor, QWidget *parent =0);
    /*public*/ void init();
    /*public*/ virtual void makeBottomPanel(ActionListener* doneAction);
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* event);
 /*public*/ void deselectIcon();

signals:

public slots:
 void renameIcon();

private:
    QMap<QString, NamedIcon*>* _iconMap;
    QMap<QString, NamedIcon*>* _tmpIconMap;
    ImagePanel* _iconPanel;
    QPushButton* _catalogButton;
    CatalogPanel* _catalog;
    IconDisplayPanel* _selectedIcon;
    QPushButton* _deleteIconButton;
    static Logger* log;
    void hideCatalog();
    /*private*/ void putIcon(QString name, NamedIcon* icon);
    /*private*/ void clickEvent(QGraphicsSceneMouseEvent* event);
    void showCatalog();
    /*private*/ CatalogPanel* makeCatalog();
    /*private*/ void setDeleteIconButton(bool set);

private slots:
    void on_catalogButton_clicked();
    /*protected*/ void deleteIcon();

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
    /*protected*/ void setSelection(IconDisplayPanel* panel);


friend class ClockItemPanel;
friend class BackgroundItemPanel;
friend class IconDisplayPanel;

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
    QByteArray mimeData();
    IconItemPanel* parent;
};

/*public*/ class IconDisplayPanel : public JPanel //implements MouseListener
{
 Q_OBJECT
    QString _borderName;
    NamedIcon* _icon;
    IconItemPanel* iconItemPanel;
public:
    /*public*/ IconDisplayPanel(QString borderName, NamedIcon* icon, IconItemPanel* iconItemPanel);
    QString getBorderName() ;
    NamedIcon* getIcon();
    void setBorderAndIcon(NamedIcon* icon);
    /*public*/ QString getIconName() ;
    /*public*/ void mouseClicked(QMouseEvent* event);
    /*public*/ void mousePressed(QMouseEvent* event);
    /*public*/ void mouseReleased(QMouseEvent* event);
    /*public*/ void mouseEntered(QMouseEvent* event);
    /*public*/ void mouseExited(QMouseEvent* event);
    friend class IconItemPanel;
};
#if 0
    class IconListener implements MouseListener {
        @Override
        public void mouseClicked(MouseEvent event) {
            if (event.getSource() instanceof IconDisplayPanel) {
                IconDisplayPanel panel = (IconDisplayPanel)event.getSource();
                setSelection(panel);
            } else if(event.getSource() instanceof ImagePanel) {
                deselectIcon();
           }
        }
        @Override
        public void mousePressed(MouseEvent event) {
        }
        @Override
        public void mouseReleased(MouseEvent event) {
        }
        @Override
        public void mouseEntered(MouseEvent event) {
        }
        @Override
        public void mouseExited(MouseEvent event) {
        }
    }
#endif
#endif // ICONITEMPANEL_H
