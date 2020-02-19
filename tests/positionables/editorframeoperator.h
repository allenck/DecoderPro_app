#ifndef EDITORFRAMEOPERATOR_H
#define EDITORFRAMEOPERATOR_H

#include <QObject>
#include "jframe.h"

class EditorFrameOperator : public QObject
{
 Q_OBJECT
public:
 explicit EditorFrameOperator(QObject *parent = nullptr);
 /*public*/ EditorFrameOperator(QString title);
 /*public*/ EditorFrameOperator(JFrame* frame);
 /*public*/ void closeFrameWithConfirmations();
 /*public*/ void deleteViaFileMenuWithConfirmations();

signals:

public slots:

private:
 /*private*/ void dismissClosingDialogs();
 JFrame* frame = nullptr;
};

#endif // EDITORFRAMEOPERATOR_H
