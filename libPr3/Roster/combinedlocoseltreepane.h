#ifndef COMBINEDLOCOSELTREEPANE_H
#define COMBINEDLOCOSELTREEPANE_H
#include "combinedlocoselpane.h"
#include "defaultmutabletreenode.h"
#include "defaulttreemodel.h"
#include <QAbstractItemModel>
#include <QDir>
#include "libPr3_global.h"
class TreePath;
class DecoderFile;
class QRadioButton;
class MyTreeSelectionListener;
class DecoderTreeNode;
class InvisibleTreeModel;
class QTreeView;
class LIBPR3SHARED_EXPORT CombinedLocoSelTreePane : public CombinedLocoSelPane
{
    Q_OBJECT
public:
    explicit CombinedLocoSelTreePane(QWidget *parent = 0);
    /*public*/ CombinedLocoSelTreePane(QLabel* s, ProgModeSelector* selector, QWidget *parent = nullptr);
    /*public*/ void resetSelections();

signals:

public slots:
    void On_showAll_clicked();
    void On_showMatched_clicked();
    void OnTreeSelection(QModelIndex);
private:
    InvisibleTreeModel* dModel;
    DecoderTreeNode* dRoot;
    QRadioButton* showAll;// = new QRadioButton();
    QRadioButton* showMatched;// = new QRadioButton();
    void common();
    Logger* log;
    void updateForDecoderTypeID(QList<DecoderFile*>* pList);
    void updateForDecoderMfgID(QString pMfg, int pMfgID, int pModelID);
    QStringList selectedPath;// = new QList<TreePath*>();
    void updateForDecoderNotID(int pMfgID, int pModelID);
    void setDecoderSelectionFromLoco(QString loco);
    bool isDecoderSelected();
    bool bShowFiles;
protected:
    /*protected*/ QTreeView* dTree;
    /*protected*/ MyTreeSelectionListener* dListener;

    /*protected*/ QWidget* viewButtons;
    /**
     * Create the panel used to select the decoder
     */
    /*protected*/ QWidget* layoutDecoderSelection();
    /*protected*/ QString selectedDecoderType();

};

#if 0
class InvisibleTreeModel : public DefaultTreeModel
{
 Q_OBJECT
protected:
/*protected*/ bool filterIsActive;
public:
    /*public*/ InvisibleTreeModel(TreeNode* root, QObject* parent);
/*public*/ InvisibleTreeModel(TreeNode* root, bool asksAllowsChildren);
/*public*/ InvisibleTreeModel(TreeNode* root, bool asksAllowsChildren,
  bool filterIsActive) ;
/*public*/ void activateFilter(bool newValue) ;
/*public*/ bool isActivatedFilter();
/*public*/ QObject* getChild(QObject* parent, int index);
/*public*/ int getChildCount(QObject* parent);
};
#else
class InvisibleTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit InvisibleTreeModel(bool bShowFiles = false, QObject *parent = 0);
    ~InvisibleTreeModel();
    QVariant data(const QModelIndex &index,int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section,Qt::Orientation orientation,
    int role = Qt::DisplayRole) const;
    QModelIndex index(int row,int column,
    const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool createNewNode(QString title, QString name, QString tooltip);
    void processChildNode(QString path, QStringList familyList, DecoderTreeNode* parent);
    void setFilter(QDir::Filters filter);
    void resetModel();
    QStringList getFilter();
    void removeNode(DecoderTreeNode* parent);
//    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
//    Qt::DropActions supportedDropActions() const;
//    QStringList mimeTypes() const;
//    QMimeData *mimeData(const QModelIndexList &indexes) const;
    DecoderTreeNode*  getRoot();
signals:
public slots:
private:
    DecoderTreeNode* rootItem;
    QList<DecoderTreeNode*> parents;
    QDir::Filters filter;
    bool bShowFiles;
    QStringList nameFilters;
    /*private*/ void removeChild(DecoderTreeNode *parent);
    Logger* log;
};

#endif

#if 0
class DecoderTreeNode : public DefaultMutableTreeNode
{
 Q_OBJECT
protected:
/*protected*/ bool _isVisible;
private:
/*private*/ QString toolTipText;
/*private*/ QString title;
public:
/*public*/ DecoderTreeNode(QString str, QString toolTipText, QString title, QObject *parent) ;
/*public*/ QString getTitle();
/*public*/ QString getToolTipText();
/*public*/ DecoderTreeNode(QObject* userObject,QObject *parent) ;
/*public*/ DecoderTreeNode(QObject* userObject, bool allowsChildren,
    bool isVisible,QObject *parent) ;
/*public*/ TreeNode* getChildAt(int index, bool filterIsActive) ;
/*public*/ int getChildCount(bool filterIsActive);
/*public*/ void setVisible(bool visible) ;
/*public*/ bool isVisible() ;
};
#else
class DecoderTreeNode
{
public:
    //DecoderTreeNode(const QList<QVariant> &data, QString path, DecoderTreeNode *parent = 0);
    DecoderTreeNode(const QList<QVariant> &data, QString name, QString toolTip, QString title, DecoderTreeNode *parentItem);
    ~DecoderTreeNode();
    void appendChild(DecoderTreeNode *child);
    void clear();
    DecoderTreeNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    DecoderTreeNode *parent();
    int tag;
    //QString path;
    QList<DecoderTreeNode*> children();
    QString toString();
    QString name;
    QString title;
    QString toolTip;
    void setVisible(bool);
    QString getPath();

   private:
    QList<DecoderTreeNode*> childItems;
    QList<QVariant> itemData;
    DecoderTreeNode *parentItem;
    bool _isVisible;
};

#endif
#endif // COMBINEDLOCOSELTREEPANE_H
