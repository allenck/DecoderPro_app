#ifndef PANELEDITORACTION_H
#define PANELEDITORACTION_H

#include <QAction>

class PanelEditorAction : public QAction
{
 Q_OBJECT
public:
 explicit PanelEditorAction(QObject *parent);
 /*public*/ PanelEditorAction(QString s, QObject *parent);


signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();
};

#endif // PANELEDITORACTION_H
