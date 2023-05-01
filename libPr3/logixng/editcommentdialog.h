#ifndef EDITCOMMENTDIALOG_H
#define EDITCOMMENTDIALOG_H

#include <QObject>
#include "jdialog.h"
#include "jtextarea.h"
#include "jlabel.h"
#include "actionevent.h"
#include "windowadapter.h"
#include "jdialog.h"
#include <QPointer>

class EditCommentDialog : public QObject
{
  Q_OBJECT
 public:
  explicit EditCommentDialog(QObject *parent = nullptr);
  /*public*/ QString showDialog(QString comment);
  QString resultString()const {return _comment;}

 signals:
  void valueChanged(QString);

private:
  /*private*/ static /*final*/ int panelWidth;// = 500;
  /*private*/ static /*final*/ int panelHeight;// = 500;
  /*private*/ QString _comment;
  /*private*/ QPointer<JDialog> _editCommentDialog = nullptr;
  /*private*/ /*final*/ JLabel* _commentLabel = new JLabel(tr("Comment") + ":");
  /*private*/ /*final*/ JTextArea* _commentTextArea = new JTextArea();

 protected:
  /*final*/ /*protected*/ void cancelPressed(JActionEvent* e=nullptr);
  /*final*/ /*protected*/ void okPressed(QActionEvent* e =nullptr);

  friend class EC_WindowAdapter;
};

class EC_WindowAdapter : public WindowAdapter
{
    Q_OBJECT
    EditCommentDialog* dlg;
 public:
    EC_WindowAdapter(EditCommentDialog* dlg) {this->dlg = dlg;}
    //@Override
        /*public*/ void windowClosing(QCloseEvent* e) override{
        dlg->cancelPressed(nullptr);
    }

};

#endif // EDITCOMMENTDIALOG_H
