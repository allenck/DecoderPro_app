#ifndef MESSAGEPANEL_H
#define MESSAGEPANEL_H

#include <QWidget>
#include "lnpanel.h"
#include "libPr3_global.h"

class JTextField;
class QPushButton;
class LIBPR3SHARED_EXPORT MessagePanel : public LnPanel
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit MessagePanel(QWidget *parent = 0);
 ~MessagePanel() {}
 MessagePanel(const MessagePanel&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();

signals:

public slots:
 void on_button_clicked();

private:
 // GUI member declarations
 QPushButton* button;// = new JButton("Send");
 JTextField* text;// = new JTextField(10);

};
Q_DECLARE_METATYPE(MessagePanel)
#endif // MESSAGEPANEL_H
