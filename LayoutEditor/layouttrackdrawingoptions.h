#ifndef LAYOUTTRACKDRAWINGOPTIONS_H
#define LAYOUTTRACKDRAWINGOPTIONS_H

#include <QObject>
#include <QColor>

class LayoutTrackDrawingOptions : public QObject
{
 Q_OBJECT
public:
 explicit LayoutTrackDrawingOptions(QString name, QObject *parent = nullptr);
 /*public*/ LayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo);
 /*public*/ QString getName();
 /*public*/ void setName(QString name);
 /*public*/ int getSideBallastWidth();
 /*public*/ void setSideBallastWidth(int val);
 /*public*/ QColor getSideBallastColor();
 /*public*/ void setSideBallastColor(/*@Nonnull*/ QColor val);
 /*public*/ int getSideTieLength();
 /*public*/ void setSideTieLength(int val);
 /*public*/ QColor getSideTieColor();
 /*public*/ void setSideTieColor(/*@Nonnull*/ QColor val);
 /*public*/ int getSideTieWidth();
 /*public*/ void setSideTieWidth(int val);
 /*public*/ int getSideTieGap();
 /*public*/ void setSideTieGap(int val);
 /*public*/ int getSideRailCount();
 /*public*/ void setSideRailCount(int val) ;
 /*public*/ int getSideRailWidth() ;
 /*public*/ void setSideRailWidth(int val);
 /*public*/ int getSideRailGap();
 /*public*/ void setSideRailGap(int val);
 /*public*/ QColor getSideRailColor();
 /*public*/ void setSideRailColor(/*@Nonnull*/ QColor val);
 /*public*/ int getSideBlockLineDashPercentageX10();
 /*public*/ void setSideBlockLineDashPercentageX10(int val);
 /*public*/ int getSideBlockLineWidth();
 /*public*/ void setSideBlockLineWidth(int val);
 /*public*/ int getMainBallastWidth();
 /*public*/ void setMainBallastWidth(int val);
 /*public*/ QColor getMainBallastColor();
 /*public*/ void setMainBallastColor(/*@Nonnull*/ QColor val);
 /*public*/ int getMainTieLength();
 /*public*/ void setMainTieLength(int val);
 /*public*/ QColor getMainTieColor();
 /*public*/ void setMainTieColor(/*@Nonnull*/ QColor val);
 /*public*/ int getMainTieWidth();
 /*public*/ void setMainTieWidth(int val) ;
 /*public*/ int getMainTieGap();
 /*public*/ void setMainTieGap(int val);
 /*public*/ int getMainRailCount();
 /*public*/ void setMainRailCount(int val);
 /*public*/ int getMainRailWidth();
 /*public*/ void setMainRailWidth(int val);
 /*public*/ int getMainRailGap();
 /*public*/ void setMainRailGap(int val);
 /*public*/ QColor getMainRailColor();
 /*public*/ void setMainRailColor(/*@Nonnull*/ QColor val);
 /*public*/ int getMainBlockLineDashPercentageX10();
 /*public*/ void setMainBlockLineDashPercentageX10(int val);
 /*public*/ int getMainBlockLineWidth();
 /*public*/ void setMainBlockLineWidth(int val);
 /*public*/ QColor getBlockDefaultColor() ;
 /*public*/ void setBlockDefaultColor(/*@Nonnull*/ QColor val);
 /*public*/ QColor getBlockOccupiedColor();
 /*public*/ void setBlockOccupiedColor(/*@Nonnull*/ QColor val);
 /*public*/ QColor getBlockAlternativeColor();
 /*public*/ void setBlockAlternativeColor(/*@Nonnull*/ QColor val);
 /*public*/ bool equalsAllButName(/*@Nonnull*/ LayoutTrackDrawingOptions* ltdo);
 /*public*/ bool equals(QObject* obj);
 /*public*/ int hashCode();

signals:

public slots:

private:
 /*private*/ QString name;
 /*private*/ int mainTieLength = 0;
 /*private*/ int mainBlockLineDashPercentageX10 = 0;
 /*private*/ int mainBlockLineWidth = 4;
 /*private*/ QColor mainRailColor;// = Color.GRAY;
 /*private*/ int sideBallastWidth = 0;   // defaults to zero (off)
 /*private*/ int mainRailGap = 0;
 /*private*/ int mainRailWidth = 2;
 /*private*/ int mainRailCount = 1;
 /*private*/ int mainTieGap = 0;
 /*private*/ int mainTieWidth = 0;
 /*private*/ QColor mainTieColor;// = Color.BLACK;
 /*private*/ QColor mainBallastColor;// = Color.BLACK;
 /*private*/ QColor blockDefaultColor = QColor(Qt::gray);
 /*private*/ QColor blockOccupiedColor = QColor(Qt::red);
 /*private*/ QColor blockAlternativeColor = QColor(Qt::gray);


 /*private*/ int mainBallastWidth = 0;   // defaults to zero (off)
 /*private*/ int sideBlockLineWidth = 2;
 /*private*/ int sideBlockLineDashPercentageX10 = 0;
 /*private*/ QColor sideRailColor;// = Color.GRAY;
 /*private*/ int sideRailGap = 0;
 /*private*/ int sideRailWidth = 1;
 /*private*/ int sideRailCount = 1;
 /*private*/ int sideTieGap = 0;
 /*private*/ int sideTieWidth = 0;
 /*private*/ QColor sideTieColor;// = Color.BLACK;
 /*private*/ int sideTieLength = 0;
 /*private*/ QColor sideBallastColor;// = Color.BLACK;

};

#endif // LAYOUTTRACKDRAWINGOPTIONS_H
