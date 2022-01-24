#ifndef BACKGROUNDITEMPANEL_H
#define BACKGROUNDITEMPANEL_H
#include "iconitempanel.h"
#include "jdialog.h"
#include "actionlistener.h"
#include "liblayouteditor_global.h"
#include <QVector>
#include "imagepanel.h"

class JColorChooser;
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

private:
    JColorChooser* _chooser;
    QPushButton*       _colorButton;
    JPanel*        _colorPanel;
    QColor         _color;
    /*private*/ JPanel* initBottomPanel();

private slots:
    //void colorChanged();

protected:
    /*protected*/ JPanel *instructions(bool isBackGround);
 friend class BGIPActionListener;
};
#if 1
class BGIPColorDialog : public JDialog //implements ChangeListener
{
 Q_OBJECT

    JColorChooser* _chooser;
    Editor*        _editor;
    JPanel*        _preview;
    BackgroundItemPanel* parent;
public:
    BGIPColorDialog(Editor* editor, BackgroundItemPanel* parent) ;
public slots:
    /*public*/ void stateChanged(ChangeEvent* e = 0);
    protected:
    /*protected*/ QWidget* makeDoneButtonPanel();
    friend class BGIPCDActionListener;
};

#endif
#endif // BACKGROUNDITEMPANEL_H
