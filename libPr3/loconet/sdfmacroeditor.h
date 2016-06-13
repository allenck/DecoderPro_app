#ifndef SDFMACROEDITOR_H
#define SDFMACROEDITOR_H

#include <QWidget>

class Logger;
class SdfEditorPane;
class DefaultMutableTreeNode;
class SdfMacro;
class SdfMacroEditor : public QWidget
{
 Q_OBJECT
public:
 //explicit SdfMacroEditor(QWidget *parent = 0);
 /*public*/ SdfMacroEditor(SdfMacro* inst, QWidget *parent = 0);
 /*public*/ virtual void update();
 /*public*/ void updated();
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);
 /*public*/ void setNotify(DefaultMutableTreeNode* node, SdfEditorPane* pane);
 static /*public*/ SdfMacroEditor* attachEditor(SdfMacro* inst);
 void removeAll();
signals:

public slots:
private:
 SdfMacro* inst;
 SdfMacro* getMacro();
 DefaultMutableTreeNode* treenode;// = NULL;
 SdfEditorPane* editor;// = NULL;

 friend class SdfEditorPane;
 friend class InitiateSoundEditor;
 friend class DefaultMutableTreeModel;
 friend class PlayEditor;
};

#endif // SDFMACROEDITOR_H
