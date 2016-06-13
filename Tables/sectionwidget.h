#ifndef SECTIONWIDGET_H
#define SECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class SectionWidget;
}

class QSignalMapper;
class SectionTableAction;
class SectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SectionWidget(QWidget *parent = 0);
    ~SectionWidget();

private:
    Ui::SectionWidget *ui;
    SectionTableAction* act;
//    QSignalMapper* deleteMapper;
//    QSignalMapper* editMapper;
private slots:
    void handleButton(int, QString);
    friend class TablesFrame;
};

#endif // SECTIONWIDGET_H
