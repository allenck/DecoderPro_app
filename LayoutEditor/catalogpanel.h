#ifndef CATALOGPANEL_H
#define CATALOGPANEL_H

#include <QWidget>
#include <QLabel>
#include "jtree.h"
#include "logger.h"
#include "jpanel.h"

class GridBagLayout;
class CPIconDisplayPanel;
class IconItemPanel;
class BufferedImage;
class ImagePanel;
class NamedIcon;
class JFrame;
class CatalogTreeItem;
class CatalogTreeModel;
class DefaultTreeModel;
class CatalogTree;
class CatalogTreeNode;
class TreeNode;
class CatalogPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit CatalogPanel(QWidget *parent = 0);
    /*public*/ static /*final*/ double ICON_SCALE;// = 0.15;
    /*public*/ static /*final*/ int ICON_WIDTH;// = 100;
    /*public*/ static /*final*/ int ICON_HEIGHT;// = 100;
    /*public*/ CatalogPanel(QWidget *parent = 0);
    /*public*/ CatalogPanel(QString label1, QString label2, bool addButtonPanel, QWidget *parent = 0);
    ~CatalogPanel();
    /*public*/ void createNewBranch(QString systemName, QString userName, QString path);
    /*public*/ void addTree(CatalogTree* tree);
    /*public*/ void init(bool treeDnD, bool dragIcons);
    /*public*/ CatalogTreeNode* getSelectedNode();
    /*public*/ bool insertNodeIntoModel(QString name, CatalogTreeNode* parent);
    /*public*/ void removeNodeFromModel(CatalogTreeNode* node);
    /*public*/ static CatalogPanel* makeDefaultCatalog(bool addButtonPanel, bool treeDrop, bool dragIcon);
    /*public*/ static void packParentFrame(QWidget* comp);
    /*public*/ static JFrame* getParentFrame(QWidget* comp);
    /*public*/ static QString printDbl(double z, int decimalPlaces);
    /*public*/ void setBackground(QWidget* container);
    /*public*/ void updatePanel();
    /*public*/ bool nodeChange(CatalogTreeNode* node, QString name);
    /*public*/ NamedIcon* getSelectedIcon();
    /*public*/ ImagePanel* getPreviewPanel();
    /*public*/ static CatalogPanel* makeDefaultCatalog();
    /*public*/ NamedIcon* getIcon();
    /*public*/ void deselectIcon();
    /*public*/ void setSelectedNode(QStringList names);
    /*public*/ void scrollPathToVisible(QStringList names);

signals:
    void newDirectorySelected(QString);


public slots:
    void whiteButtonClicked();
    void darkButtonClicked();
    void grayButtonClicked();
    void on_tree_clicked(QModelIndex);
    void onBgColorBox(int);

private:
    QWidget*          _selectedImage;
    static QColor    _grayColor;// = new QColor(235,235,235);
    static QColor _darkGrayColor;// = new Color(150, 150, 150);
    QLabel*          _previewLabel;// = new JLabel();
    bool         _noDrag;
    /*private*/ bool _treeDnd;
    /*private*/ bool _dragIcons;
    //QScrollArea*             _treePane;
    JTree*                   _dTree;
    DefaultTreeModel*        _model;
    QList<CatalogTree*>* _branchModel;// = new QList <CatalogTree>();
    /*private*/ void setupPanel();
    void common();
    /*private*/ bool nameOK(CatalogTreeNode* node, QString name);
    /*private*/ CatalogTreeNode* match(CatalogTreeNode* cRoot, QVector<TreeNode*>* nodes, int idx);
    /*private*/ void addNode(CatalogTreeNode* parent, CatalogTreeNode* n);
    /*private*/ CatalogTree* getCorespondingModel(CatalogTreeNode* node);
    /*private*/ CatalogTreeNode* getCorrespondingNode(CatalogTreeNode* node);
    Logger* log;
    bool _noMemory; // = false;
    /*private*/ void addTreeBranch(CatalogTreeNode* node);
    /*private*/ QWidget* makeButtonPanel();
/*private*/ IconItemPanel* _parent;      // IconItemPanel could implement an interface if other classes use deselectIcon()
    GridBagLayout* gridbag;

private slots:
    /*private*/ void showPopUp(NamedIcon*);
    void rename(NamedIcon* obj);
    void _delete(NamedIcon* obj);


protected:
    /*protected*/ QColor _currentBackground;// = _grayColor;
    /*protected*/ ImagePanel*  _preview;
    /*protected*/ void resetPanel();
    /*protected*/ QString setIcons();
    /**
     * Array of BufferedImage backgrounds loaded as background image in Preview.
     */
    /*protected*/ QVector<BufferedImage*>* _backgrounds;
    /*protected*/ QList<QColor> colorChoice;// = new Color[] {Color.white, _grayColor, _darkGrayColor};
    /*protected*/ void setSelection(CPIconDisplayPanel* panel);

    friend class CPLTreeSelectionListener;
    friend class CPIconDisplayPanel;
};

class CPLTreeSelectionListener : public TreeSelectionListener
{
 Q_OBJECT
 CatalogPanel* cp;
public:
 CPLTreeSelectionListener(CatalogPanel* cp);

public slots:
 void valueChanged(TreeSelectionEvent* /*e*/);
};

/*public*/ class CPIconDisplayPanel : public  JPanel //implements MouseListener
{
 Q_OBJECT
 QString _name;
 NamedIcon* _icon;
 CatalogPanel* catalogPanel;
public:
    /*public*/ CPIconDisplayPanel(QString leafName, NamedIcon* icon, CatalogPanel* catalogPanel) ;
    NamedIcon* getIcon();
    void setBorderAndIcon(NamedIcon* icon);
    /*public*/ QString getIconName();
    /*public*/ void mouseClicked(QMouseEvent* event);
    /*public*/ void mousePressed(QMouseEvent* event);
    /*public*/ void mouseReleased(QMouseEvent* event);
    /*public*/ void mouseEntered(QMouseEvent* event);
    /*public*/ void mouseExited(QMouseEvent* event) ;
};
#endif // CATALOGPANEL_H
