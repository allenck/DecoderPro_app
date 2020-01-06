#ifndef JBUTTON_H
#define JBUTTON_H

#include <QPushButton>

class Action;
class ActionEvent;
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

signals:
 void actionPerformed(ActionEvent*);

public slots:
 void on_clicked();

private:
 void common(QString, QIcon);
 void setAction(Action*);

};

#endif // JBUTTON_H
