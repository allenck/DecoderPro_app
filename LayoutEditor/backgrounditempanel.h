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
class LIBLAYOUTEDITORSHARED_EXPORT BackgroundItemPanel : public IconItemPanel
{
    Q_OBJECT
public:
    //explicit BackgroundItemPanel(QWidget *parent = 0);
    /*public*/ BackgroundItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent);
    /*public*/ void init();

signals:

public slots:
    void backgroundButton_clicked();
    void colorChanged(QColor);
private:
    /*private*/ QWidget* initBottomPanel();

protected:
    /*protected*/ QWidget* instructions();
    /*protected*/ QWidget* makeBgButtonPanel(ImagePanel* preview1, ImagePanel* preview2, QVector<BufferedImage*> imgArray, DisplayFrame* parent);

};

class ColorDialog : public JDialog //implements ChangeListener
{
 Q_OBJECT

    QColorDialog* _chooser;
    Editor*        _editor;
    QWidget*        _preview;
    BackgroundItemPanel* parent;
public:
    ColorDialog(Editor* editor, BackgroundItemPanel* parent) ;
public slots:
    /*public*/ void stateChanged(ChangeEvent* e = 0);
    protected:
    /*protected*/ QWidget* makeDoneButtonPanel();
    friend class CDActionListener;
};

class CDActionListener : public ActionListener
{
    Q_OBJECT
    ColorDialog* dialog;
public:
    CDActionListener* init(ColorDialog* d) ;
public slots:
    /*public*/ void actionPerformed(ActionEvent* e =0);
};

#endif // BACKGROUNDITEMPANEL_H
