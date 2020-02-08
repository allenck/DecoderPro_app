#ifndef SOUNDLOADERPANE_H
#define SOUNDLOADERPANE_H

#include "lnpanel.h"
#include "libPr3_global.h"

class JFileChooser;
class QFileDialog;
class LoaderEngine;
class SpjFile;
class QProgressBar;
class JTextField;
class QPushButton;
class QLabel;
class LIBPR3SHARED_EXPORT SoundLoaderPane : public LnPanel
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit SoundLoaderPane(QWidget *parent = 0);
 ~SoundLoaderPane() {}
 SoundLoaderPane(const SoundLoaderPane&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void dispose();

signals:

public slots:
 void selectInputFile();
 void doRead();
 void doLoad();
 void onNotified(QString);
 void onFileError(QString);
 void onLoadFinished();

private:
 QLabel* inputFileName;// = new QLabel("");

 QPushButton* selectButton;
 QPushButton* readButton;
 QPushButton* loadButton;

 JTextField* comment;// = new JTextField(32);

 QProgressBar* bar;
 QLabel* status;// = new JLabel("");
 QString statusText;// = "";

 SpjFile* file;
 LoaderEngine* engine;
 JFileChooser* chooser;

};
Q_DECLARE_METATYPE(SoundLoaderPane)
#endif // SOUNDLOADERPANE_H
