#ifndef EDITORFILEPANE_H
#define EDITORFILEPANE_H

#include <QWidget>


class File;
class SpjFile;
class EditorTableDataModel;
class EditorFilePane : public QWidget
{
 Q_OBJECT
public:
 //explicit EditorFilePane(QWidget *parent = 0);
 /*public*/ EditorFilePane(File name, QWidget *parent = 0);
 /*public*/ void saveFile(QString name) /*throws java.io.IOException*/;

signals:

public slots:

private:
 SpjFile* file;
 EditorTableDataModel* dataModel;
 void dispose();
 friend class EditorPane;
};

#endif // EDITORFILEPANE_H
