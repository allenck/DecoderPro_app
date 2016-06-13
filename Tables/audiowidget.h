#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>

class QPushButton;
class AudioTablePanel;
namespace Ui {
class AudioWidget;
}

class AudioWidget : public QWidget
{
 Q_OBJECT

public:
 explicit AudioWidget(QWidget *parent = 0);
 ~AudioWidget();
 void setPanel(QWidget*);
 QPushButton* addSourceButton();
 QPushButton* addBufferButton();
private:
 Ui::AudioWidget *ui;
};

#endif // AUDIOWIDGET_H
