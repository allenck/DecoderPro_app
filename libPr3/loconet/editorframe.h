#ifndef EDITORFRAME_H
#define EDITORFRAME_H
#include "jmrijframe.h"

class SdfEditorPane;
class SdfBuffer;
class EditorFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit EditorFrame(QWidget *parent = 0);
 /*public*/ EditorFrame(SdfBuffer* buff,QWidget *parent = 0);
 /*public*/ void dispose();
 /*public*/ QString getClassName();

signals:

public slots:
private:
 // GUI member declarations
 SdfEditorPane* pane;

 //ResourceBundle res;

};

#endif // EDITORFRAME_H
