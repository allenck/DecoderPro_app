#ifndef JCOMPONENT_H
#define JCOMPONENT_H

#include <QWidget>

class JComponent : public QWidget
{
 Q_OBJECT
public:
 explicit JComponent(QWidget *parent = nullptr);
 bool isOpaque();
 QColor getBackground();
 void setBackground(QColor);
 void setOpaque(bool);
 QFont getFont();

signals:

public slots:
private:
 bool _opaque = true;

};

#endif // JCOMPONENT_H
