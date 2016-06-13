#ifndef EDITORPANE_H
#define EDITORPANE_H
#include "lnpanel.h"
#include "libPr3_global.h"

class QBoxLayout;
class File;
class EditorFilePane;
class QPushButton;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT EditorPane : public LnPanel
{
 Q_OBJECT
public:
 explicit EditorPane(QWidget *parent = 0);
 ~EditorPane() {}
 EditorPane(const EditorPane&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void dispose();
 /*public*/ QWidget* getTopLevelAncestor();

signals:

public slots:
 void selectInputFile();
 void selectSaveFile();

private:
 //ResourceBundle res;
 QPushButton* open;
 QPushButton* save;
 LocoNetSystemConnectionMemo* memo;
 // GUI member declarations
 EditorFilePane* pane;
 void addFile(File name);
 QBoxLayout* thisLayout;
 void saveFile(QString name) /*throws IOException*/;

};
Q_DECLARE_METATYPE(EditorPane)
#endif // EDITORPANE_H
