#ifndef HTMLTEXTEDIT_H
#define HTMLTEXTEDIT_H

#include <QTextEdit>
#include <QAction>

//class Configuration;
class HtmlTextEdit : public QTextEdit
{
 Q_OBJECT
public:
 explicit HtmlTextEdit(QWidget *parent = 0);
 HtmlTextEdit(int rows, int cols, QWidget *parent =0);
 /*public*/ int getColumns();
 /*public*/ void setColumns(int columns);
 /*protected*/ int getColumnWidth();
 /*public*/ void setEditable(bool);
signals:
 void dirtySet(bool dirty);

public slots:

private:
 void common();
 QAction *boldAction;
 QAction *italicAction;
 QAction *underlineAct;
 QAction *textZoomAct;
 QAction *textUnzoomAct;
 QAction *setColorAct;
 QAction *setColorGreenAct;
 QAction *setColorBlackAct;
 QAction *setColorGrayAct;
 QAction *setColorYellowAct;
 QAction *setColorBlueAct;
 QAction *setFontAct;
 QAction *pasteHtmlAct;
 QAction *pasteSaved;
 QAction *copySaved;
 QAction *lineWrap;
 QAction *autoFormat;
 bool bIsDirty;
 void setDirty(bool dirty);
 //Configuration* config;
 int rows;
 /*private*/ int columns;
 /*private*/ int columnWidth;

private slots:
 void showContextMenu(const QPoint &pt);
 void OnBoldAction(bool checked);
 void OnItalicAction(bool checked);
 void OnUnderlineAct(bool checked);
 void OnSelectionChanged();
 void OnTextZoomAct();
 void OnTextUnzoomAct();
 void OnSetColorAct(bool checked);
 void OnSetColorGreenAct(bool checked);
 void OnSetColorBlackAct(bool checked);
 void OnSetColorGrayAct(bool checked);
 void OnSetColorYellowAct(bool);
 void OnSetColorBlueAct(bool);
 void OnSetFontAct();
 void OnPasteHtmlAct();
 void OnPasteSaved();
 void OnCopySaved();
 void OnTextChanged();
 void OnLineWrap();
 void OnAutoFormat();
};

#endif // HTMLTEXTEDIT_H
