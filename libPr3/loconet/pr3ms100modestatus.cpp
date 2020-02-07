#include "pr3ms100modestatus.h"

/**
 * PR3 (MS100 mode) Interface status
 *
 * @author Bob Milhaupt Copyright (C) 2017
 */
//public class PR3MS100ModeStatus {

/*public*/ PR3MS100ModeStatus::PR3MS100ModeStatus::PR3MS100ModeStatus(int a, int b, int c, QObject *parent)
 : QObject(parent)
{
    goodMsgCnt = a;
    badMsgCnt = b;
    ms100status = c;
    setObjectName("PR3MS100ModeStatus");
}

