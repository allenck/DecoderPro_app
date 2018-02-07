#ifndef RPSMENU_H
#define RPSMENU_H
#include <QMenu>

class RpsMenu : public QMenu
{
public:
 RpsMenu(QWidget* parent = nullptr);
 /*public*/ RpsMenu(QString name, QWidget* parent = nullptr);
private:
 void common();
};

#endif // RPSMENU_H
