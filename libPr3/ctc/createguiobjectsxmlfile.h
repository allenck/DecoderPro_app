#ifndef CREATEGUIOBJECTSXMLFILE_H
#define CREATEGUIOBJECTSXMLFILE_H

#include <QObject>
#include "otherdata.h"

class PrintWriter;
class Logger;
class CreateGUIObjectsXMLFile : public QObject
{
  Q_OBJECT
 public:
  explicit CreateGUIObjectsXMLFile(QObject *parent = nullptr);
  /*public*/ static void writeGUIObjects();

 signals:

 public slots:

 private:
  /*private*/ static /*final*/ int START_OFFSET;// = 12;
  /*private*/ static /*final*/ int GIF_HORIZONTAL_SIZE;// = 65;
  static Logger* log;
  /*private*/ static void generateBuilderPlate(PrintWriter* printWriter);
  /*private*/ static /*final*/ QString DIALOG_USED;// = "Dialog.plain";   // NOI18N
  /*private*/ static void generateTextPositionableLabel(int x, int y, QString text, PrintWriter* printWriter);
  /*private*/ static void generateTextPositionableLabelCentered(int x, int y, QString text, PrintWriter* printWriter);
  /*private*/ static int centerText(int originalValue, QString text);
  /*private*/ static void generatePanel(int x, int y, OtherData::VERTICAL_SIZE verticalSize, QString resourceFilename, PrintWriter* printWriter);
  /*private*/ static void generateSensorIndicator(int x, int y, QString sensor, QString color, bool unknownInconsistentRedBlink, PrintWriter* printWriter);
  /*private*/ static void generateKnockout(int x, int y, PrintWriter* printWriter);
  /*private*/ static void generateTurnoutIcon(int x, int y, QString turnout, bool isTurnoutLeftHanded, PrintWriter* printWriter);
  /*private*/ static void generateTurnoutCrossoverIcon(int x, int y, QString turnout, bool isDoubleCrossover, bool isTurnoutLeftHanded, PrintWriter* printWriter);
  /*private*/ static void generateSignalHead(int x, int y, QString signalHead, bool isRightToLeft, PrintWriter* printWriter);
  /*private*/ static void generateSignalBlock(QString direction, QString color, PrintWriter* printWriter);
  /*private*/ static QString generateSignalLineStart(QString direction, QString color);
  /*private*/ static QString generateSignalLineEnd(QString color);
  /*private*/ static void generateSignalMast(int x, int y, QString signalMast, bool isRightToLeft, PrintWriter* printWriter);
  /*public*/ static void generateTurnoutLever(int x, int y, QString lever, PrintWriter* printWriter);
  /*public*/ static void generateSignalLever(int x, int y, QString left, QString vertical, QString right, PrintWriter* printWriter );
  /*public*/ static void generateToggle(int x, int y, QString sensor, PrintWriter* printWriter);
  /*public*/ static void generatePushButton(int x, int y, QString sensor, PrintWriter* printWriter);

  /*private*/ static int adjustSwitchItemsYBySize(int y, OtherData::VERTICAL_SIZE verticalSize);
  /*private*/ static int adjustSignalItemsYBySize(int y, OtherData::VERTICAL_SIZE verticalSize);
  /*private*/ static int adjustLockedItemsYBySize(int y, OtherData::VERTICAL_SIZE verticalSize);
  /*private*/ static int adjustCallOnItemsYBySize(int y, OtherData::VERTICAL_SIZE verticalSize);
  /*private*/ static int adjustCodeButtonYBySize(int y, OtherData::VERTICAL_SIZE verticalSize);
};

#endif // CREATEGUIOBJECTSXMLFILE_H
