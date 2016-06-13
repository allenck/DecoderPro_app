#ifndef SDFEDITORPANE_H
#define SDFEDITORPANE_H

#include <QWidget>
#include <QModelIndex>
#include <QMap>

class DefaultMutableTreeModel;
class QModelIndex;
class SdfMacro;
class SdfBuffer;
class JEditorPane;
class MonitoringLabel;
class TreeSelectionEvent;
class SdfMacroEditor;
class QTreeView;
class DefaultMutableTreeNode;
class QSplitter;
class SdfEditorPane : public QWidget
{
 Q_OBJECT
public:
 explicit SdfEditorPane(QWidget *parent = 0);
 /*public*/ void updateSummary();

signals:

public slots:
 /*public*/ void valueChanged(/*TreeSelectionEvent* e = 0*/QModelIndex);

private:
 QSplitter* split;
 QTreeView* tree;
 DefaultMutableTreeNode* topNode;
 QWidget* newTree();
 SdfMacroEditor* lastEditor;// = null;
 QWidget* newEditPane();
 MonitoringLabel* instruction;// = new MonitoringLabel();
 JEditorPane* explanation;// = new JEditorPane();
 QWidget* newInstructionPane();
 QWidget* detailed;// = new JPanel(); // panel that contains the specific editors
 QWidget* newDetailPane();
 void addSdf(SdfBuffer* buff);
 void nestNodes(DefaultMutableTreeNode* parent, SdfMacro* macro);
 void dispose();
 DefaultMutableTreeModel* model;
 QMap<QString, QString> exp;

 friend class EditorFrame;
};

#endif // SDFEDITORPANE_H
