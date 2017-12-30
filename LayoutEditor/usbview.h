#ifndef USBVIEW_H
#define USBVIEW_H
#include "jframe.h"
#include <QModelIndex>
#include "jtree.h"

class UserPreferencesManager;
class UsbTreeModel;
class JTextArea;
class QSplitter;

class UsbTreeView : public JTree
{
public:
 inline UsbTreeView() : JTree() {}
 void rowsInserted(const QModelIndex &parent, int start, int end);

};

class UsbView : public JFrame
{
 Q_OBJECT
public:
 UsbView(QWidget* parent = 0);

private:
 Logger* log;
// /*private*/ static /*final*/ long serialVersionUID = 4693554326612734263L;
 /*private*/ static /*final*/ int APP_WIDTH;// = 600;
 /*private*/ static /*final*/ int APP_HIGHT;// = 800;
 /*private*/ QWidget* jContentPane;
 /*private*/ QMenuBar* jJMenuBar;
 /*private*/ QMenu* commandsMenu;
 /*private*/ QMenu* exitMenuItem;
 /*private*/ QMenu* updateMenuItem;
 UsbTreeView* usbTree;
 /*private*/ QSplitter* jSplitPane;
 /*private*/ JTextArea* jPropertiesArea;
 UsbTreeModel* treeModel;
 QMenu* testAppPopup;
 /*protected*/ QMenu* endpointPopup;
 /*private*/ void initialize();
 /*private*/ QWidget* getJContentPane();
 /*private*/ QMenu* getFileMenu();
 /*private*/ QMenu* getExitMenuItem();
 /*private*/ QMenu* getUpdateMenuItem();
 /*private*/ UsbTreeView* getUsbTree();
 /*private*/ void getJTestAppPopup();
 /*private*/ QSplitter* getJSplitPane();
 /*private*/ JTextArea* getJPropertiesArea();
 /*private*/ QMenuBar* getJJMenuBar();
 void expandAll(JTree* tree);
 UserPreferencesManager* pref;

private slots:
 void On_clicked(QModelIndex);
};

#endif // USBVIEW_H
