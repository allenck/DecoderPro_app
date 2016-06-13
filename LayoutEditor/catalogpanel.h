#ifndef CATALOGPANEL_H
#define CATALOGPANEL_H

#include <QWidget>
#include <QLabel>
#include <QTreeView>
#include "logger.h"

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
    /*public*/ CatalogPanel(QString label1, QString label2, QWidget *parent = 0);
    ~CatalogPanel();
    /*public*/ void createNewBranch(QString systemName, QString userName, QString path);
    /*public*/ void addTree(CatalogTree* tree);
    /*public*/ void init(bool treeDnD);
//    /*public*/ CatalogTreeNode* getSelectedNode();
    /*public*/ CatalogTreeItem* getSelectedNode();
//    /*public*/ bool insertNodeIntoModel(QString name, CatalogTreeNode* parent);
    /*public*/ bool insertNodeIntoModel(QString name, CatalogTreeItem* parent);
//    /*public*/ void removeNodeFromModel(CatalogTreeNode* node);
    /*public*/ void removeNodeFromModel(CatalogTreeItem* node);
    /*public*/ static CatalogPanel* makeDefaultCatalog();
    /*public*/ static void packParentFrame(QWidget* comp);
    /*public*/ static JFrame* getParentFrame(QWidget* comp);
    /*public*/ static QString printDbl(double z, int decimalPlaces);
    /*public*/ void setBackground(QWidget* container);
    /*public*/ void updatePanel();

signals:
    void newDirectorySelected(QString);


public slots:
    void whiteButtonClicked();
    void darkButtonClicked();
    void grayButtonClicked();
    void on_tree_clicked(QModelIndex);

private:
    QWidget*          _selectedImage;
    static QColor    _grayColor;// = new QColor(235,235,235);

    QLabel*          _previewLabel;// = new JLabel();
    bool         _noDrag;

    //QScrollArea*             _treePane;
    QTreeView*                   _dTree;
    //DefaultTreeModel*        _model;
    CatalogTreeModel* _model;
    QList<CatalogTree*>* _branchModel;// = new QList <CatalogTree>();
    /*private*/ void setupPanel();
    void common();
//    /*private*/ void addTreeBranch(CatalogTreeNode* node);
    /*private*/ bool nameOK(CatalogTreeNode* node, QString name);
    /*private*/ CatalogTreeNode* match(CatalogTreeNode* cRoot, QVector<TreeNode*>* nodes, int idx);
    /*private*/ void addNode(CatalogTreeNode* parent, CatalogTreeNode* n);
    /*private*/ CatalogTree* getCorespondingModel(CatalogTreeNode* node);
    /*private*/ CatalogTreeNode* getCorrespondingNode(CatalogTreeNode* node);
    Logger* log;
    bool _noMemory; // = false;
protected:
    /*protected*/ QColor _currentBackground;// = _grayColor;
    /*protected*/ QWidget*  _preview;
    /*protected*/ void resetPanel();
    /*protected*/ QString setIcons();
};

#endif // CATALOGPANEL_H
