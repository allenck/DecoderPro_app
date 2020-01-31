#ifndef BACKGROUNDITEMPANEL_H
#define BACKGROUNDITEMPANEL_H
#include "iconitempanel.h"
#include "jdialog.h"
#include "actionlistener.h"
#include "liblayouteditor_global.h"
#include <QVector>
#include "imagepanel.h"

class ActionListener;
class ChangeEvent;
class QColorDialog;
//class BGIPColorDialog;
class LIBLAYOUTEDITORSHARED_EXPORT BackgroundItemPanel : public IconItemPanel
{
    Q_OBJECT
public:
    //explicit BackgroundItemPanel(QWidget *parent = 0);
    /*public*/ BackgroundItemPanel(DisplayFrame* parentFrame, QString type, Editor* editor, QWidget* parent);
    /*public*/ void init();

signals:

public slots:
    void backgroundButton_clicked();
    //void colorChanged(QColor);
private:
private slots:
    void colorChanged();

protected:
    /*protected*/ QWidget* instructions();
    /*protected*/ QWidget* makeBgButtonPanel(ImagePanel*, ImagePanel*);
 friend class BGIPActionListener;
};
#if 0
class BGIPColorDialog : public JDialog //implements ChangeListener
{
 Q_OBJECT

    QColorDialog* _chooser;
    Editor*        _editor;
    QWidget*        _preview;
    BackgroundItemPanel* parent;
public:
    BGIPColorDialog(Editor* editor, BackgroundItemPanel* parent) ;
public slots:
    /*public*/ void stateChanged(ChangeEvent* e = 0);
    protected:
    /*protected*/ QWidget* makeDoneButtonPanel();
    friend class BGIPCDActionListener;
};

class BGIPCDActionListener : public ActionListener
{
    Q_OBJECT
    BGIPColorDialog* dialog;
public:
    BGIPCDActionListener* init(BGIPColorDialog* d) ;
public slots:
    /*public*/ void actionPerformed(ActionEvent* e =0);
};
#endif
class BGIPActionListener : public ActionListener
{
 Q_OBJECT
 BackgroundItemPanel* panel;
public:
 BGIPActionListener(BackgroundItemPanel* panel) {this->panel = panel;}
public slots:
 void actionPerformed() { panel->colorChanged();}
};
#endif // BACKGROUNDITEMPANEL_H
