#ifndef LAYOUTEDITORACTION_H
#define LAYOUTEDITORACTION_H

#include <QAction>

class LayoutEditorAction : public QAction
{
 Q_OBJECT
public:
 explicit LayoutEditorAction(QObject *parent = 0);
 /*public*/ LayoutEditorAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();
};

#endif // LAYOUTEDITORACTION_H
