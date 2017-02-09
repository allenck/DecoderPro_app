#ifndef EDITABLERESIZABLEIMAGEPANEL_H
#define EDITABLERESIZABLEIMAGEPANEL_H
#include "resizableimagepanel.h"
#include "javaqt_global.h"
#include <QDrag>
#include <QFile>

class FileDrop;
class File;
class QMenu;
class MouseAdapter;
class JAVAQTSHARED_EXPORT EditableResizableImagePanel : public ResizableImagePanel
{
 Q_OBJECT
public:
 EditableResizableImagePanel(QWidget* parent = 0);
 /*public*/ EditableResizableImagePanel(QString imagePath, QWidget* parent = 0);
 /*public*/ EditableResizableImagePanel(QString imagePath, int w, int h, QWidget* parent = 0);
 /*public*/ void setDnd(bool dnd);
 /*public*/ void setDropFolder(QString s);
 /*public*/ QString getDropFolder();
public slots:
 /*public*/ void filesDropped(QList<File*> files);


private:
 ///*private*/ /*transient*/ MouseAdapter* myMouseAdapter;// = null;
 /*private*/ QString dropFolder;
// void dragEnterEvent(QDragEnterEvent *);
// void dropEvent(QDropEvent *);
 QFile* file;
 Logger* log;
 void mousePressEvent(QMouseEvent *);
 QMenu* popup;
 FileDrop* fileDrop;

private slots:
 void on_removeAction();

};

#endif // EDITABLERESIZABLEIMAGEPANEL_H
