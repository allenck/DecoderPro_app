#ifndef COLORCHOOSERCOMPONENTFACTORY_H
#define COLORCHOOSERCOMPONENTFACTORY_H

#include <QObject>

class AbstractColorChooserPanel;
class ColorChooserComponentFactory : public QObject
{
 Q_OBJECT
public:
 /*public*/ static QVector<AbstractColorChooserPanel*> getDefaultChooserPanels();
 /*public*/ static QWidget* getPreviewPanel();

signals:

public slots:
private:
 explicit ColorChooserComponentFactory(QObject *parent = nullptr); // can't instantiate

};

#endif // COLORCHOOSERCOMPONENTFACTORY_H
