#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QtWidgets/QAbstractButton>


class QPropertyAnimation;

class ToggleButton :public QAbstractButton
{
    Q_OBJECT
        Q_PROPERTY(int mOffset READ offset WRITE setOffset);
public:
    explicit ToggleButton(int trackRadius, int thumbRadius, QWidget* parent = nullptr);
    ~ToggleButton();

    QSize sizeHint() const override;
    void setLabels(QString on, QString off);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent  *) override;
    void enterEvent(QEvent *event) override;
    void setChecked(bool checked);

    int offset();
    void setOffset(int value);

private:
    qreal mOffset;
    qreal mBaseOffset;
    qreal mMargin;
    qreal mTrackRadius;
    qreal mThumbRadius;
    qreal mOpacity;
    QPropertyAnimation* mAnimation;
    QString on;
    QString off;

    QHash<bool, qreal> mEndOffset;
    QHash<bool, QBrush> mTrackColor;
    QHash<bool, QBrush> mThumbColor;
    QHash<bool, QColor> mTextColor;
    QHash<bool, QString> mThumbText;
friend class ToggleButtonEditor;
};

#endif // TOGGLEBUTTON_H
