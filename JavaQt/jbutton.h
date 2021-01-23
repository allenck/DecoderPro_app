#ifndef JBUTTON_H
#define JBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QEvent>

class Action;
class JActionEvent;
class JButton : public QPushButton
{
 Q_OBJECT
public:
 explicit JButton(QWidget* parent = 0);
 /*public*/ JButton(QIcon icon,QWidget *parent = 0);
 //@ConstructorProperties({"text"})
 /*public*/ JButton(QString text, QWidget *parent = 0);
 /*public*/ JButton(Action* a, QWidget *parent = 0) ;
 /*public*/ JButton(QString text, QIcon icon, QWidget *parent = 0);
// /*public*/ void setIcon(const QIcon &icon);
 /*public*/ void setName(QString s) {setObjectName(s);}
// /*public*/ void setRolloverIcon(QIcon icon);
signals:
 void actionPerformed(JActionEvent*);

public slots:
 void on_clicked();

private:
 void common(QString, QIcon);
 void setAction(Action*);
 QIcon rolloverIcon;
 QIcon icon;
// bool eventFilter(QObject *watched, QEvent *event)
// {
//  if(!rolloverIcon.isNull())
//  {
//   if (event->type() == QEvent::Enter) {
//       // The push button is hovered by mouse
//       setIcon(rolloverIcon);
//       return true;
//   }

//   if (event->type() == QEvent::Leave){
//       // The push button is not hovered by mouse
//       setIcon(icon);
//       return true;
//   }
//  }
// }
};

#endif // JBUTTON_H
