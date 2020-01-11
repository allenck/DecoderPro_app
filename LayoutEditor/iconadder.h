#ifndef ICONADDER_H
#define ICONADDER_H

#include <QWidget>
#include "logger.h"
#include "jtogglebutton.h"
#include "liblayouteditor_global.h"
#include <QPointer>

//namespace Ui {
//class IconAdder;
//}

class BorderLayout;
class QVBoxLayout;
class IconAdder;
class QDir;
class DataFlavor;
class QFileInfo;
class ActionListener;
class ListSelectionEvent;
class PickListModel;
class CatalogTreeNode;
class JTextField;
class Manager;
class JTable;
class CatalogPanel;
class JFrame;
class QPushButton;
class NamedBean;
class NamedIcon;
class LIBLAYOUTEDITORSHARED_EXPORT DropButton : public JToggleButton //implements DropTargetListener
{
 Q_OBJECT

 DataFlavor* dataFlavor;
 Logger* log;
 IconAdder* parent;
public:
 DropButton(NamedIcon* icon, IconAdder* parent);
//    /*public*/ void dragExit(DropTargetEvent dte);
//    /*public*/ void dragEnter(DropTargetDragEvent dtde);
 void dragMoveEvent(QDragMoveEvent *de);
 void dragEnterEvent(QDragEnterEvent *event);
//    /*public*/ void dragOver(DropTargetDragEvent dtde);
//    /*public*/ void dropActionChanged(DropTargetDragEvent dtde);
//    /*public*/ void drop(DropTargetDropEvent e);
 void dropEvent(QDropEvent *de);
};

class LIBLAYOUTEDITORSHARED_EXPORT IconAdder : public QWidget
{
 Q_OBJECT
    
public:
   // explicit IconAdder(QString name, QWidget *parent = 0);
    /*public*/ IconAdder(QWidget *parent = 0);
    /*public*/ IconAdder(bool allowDeletes, QWidget *parent = 0);
    ~IconAdder();
    /*public*/ void reset();
    /*public*/ IconAdder(QString type, QWidget *parent = 0) ;
    /*public*/ void initDefaultIcons();
    /*public*/ NamedIcon* getIcon(QString key);
    /*public*/ NamedBean* getTableSelection();
    /*public*/ void setIcon(int order, QString label, QString name) ;
    /*public*/ void setParent(JFrame* parent);
    void pack();
    /*public*/ int getNumIcons();
    static const int STRUT_SIZE = 3;
    /*public*/ CatalogTreeNode* getDefaultIconNode();
    /*public*/ void makeIconPanel(bool useDefaults);
    /*public*/ void setPickList(PickListModel* tableModel);
    /*public*/ void setSelection(NamedBean* bean);
    /*public*/ QMap<QString, NamedIcon *> *getIconMap();
    /*public*/ virtual void complete(ActionListener* addIconAction, bool changeIcon,
                             bool addToTable, bool update);
    /*public*/ bool addIconIsEnabled();
    /*public*/ void addDirectoryToCatalog(QDir* dir);
    /*public*/ void dispose();
public slots:
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);
    /*public*/ void addCatalog();
    void closeCatalog();
    void addToTable();
    void on_sysNametext_editingFinished();
private:
//    Ui::IconAdder *ui;
    int ROW_HEIGHT;

    QHash <QString, JToggleButton*>*   _iconMap;
    QStringList       _order;
    QWidget*          _pickTablePane;
    PickListModel*    _pickListModel;
    CatalogTreeNode*  _defaultIcons;      // current set of icons user has selected
    QWidget*          _iconPanel;
    QVBoxLayout*      _iconPanelLayout;
    QWidget*          _buttonPanel;
    QString           _type;
    bool              _userDefaults;
    JTextField*       _sysNametext;
    Manager*          _manager;
    JTable*           _table;
    QPushButton*      _addButton;
    QPushButton*      _addTableButton;
    QPushButton*      _changeButton;
    QPushButton*      _closeButton;
    QPointer<CatalogPanel>     _catalog;
    JFrame*           _parent = nullptr;
    bool              _allowDeletes;
    bool			  _update;				// updating existing icon from popup
    QVBoxLayout* thisLayout;

    /*private*/ CatalogTreeNode* getDefaultIconNodeFromMap();
    Logger* log;
    void common();
    /*private*/ void clearIconPanel() ;
    void makeIconMap(NamedBean* bean) ;
    void checkIconSizes();
    /*private*/ void updateCatalogTree();
    /*private*/ class IconButton : public DropButton
    {
     QString key;
     IconAdder* parent;
    public:
     IconButton(QString label, NamedIcon* icon, IconAdder* parent);  // init icon passed to avoid ref before ctor complete
     QString getKey();
    };

protected:
    /*protected*/ virtual void makeIcons(CatalogTreeNode* n);
    /*protected*/ void setIcon(int order, QString label, NamedIcon* icon);
    /*protected*/ virtual void doIconPanel();
    /*protected*/ virtual void addAdditionalButtons(QWidget* p);
friend class SensorIcon;
friend class IconButton;
friend class DropButton;
friend class SlipIconAdder;
friend class MultiSensorIconAdder;
friend class PositionableLabel;
friend class SignalHeadIcon;
friend class MultiSensorIcon;
friend class TurnoutIcon;
friend class SlipTurnoutIcon;
friend class LightIcon;
};

#endif // ICONADDER_H
