#ifndef EDITCOMMENTDIALOG_H
#define EDITCOMMENTDIALOG_H

#include <QObject>
#include "jdialog.h"
#include "jtextarea.h"
#include "jlabel.h"
#include "actionevent.h"

class EditCommentDialog : public QObject
{
  Q_OBJECT
 public:
  explicit EditCommentDialog(QObject *parent = nullptr);
  /*public*/ QString showDialog(QString comment);

 signals:
private:
  /*private*/ static /*final*/ int panelWidth;// = 500;
  /*private*/ static /*final*/ int panelHeight;// = 500;
  /*private*/ QString _comment;
  /*private*/ JDialog* _editCommentDialog = nullptr;
  /*private*/ /*final*/ JLabel* _commentLabel = new JLabel(tr("Comment") + ":");
  /*private*/ /*final*/ JTextArea* _commentTextArea = new JTextArea();

 protected:
  /*final*/ /*protected*/ void cancelPressed(JActionEvent* e=nullptr);
  /*final*/ /*protected*/ void okPressed(QActionEvent* e =nullptr);

};

#endif // EDITCOMMENTDIALOG_H
