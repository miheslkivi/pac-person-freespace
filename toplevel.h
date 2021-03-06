/* Derived from Qt4 example software   "Ported Asteroids"
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
*
*
*/


/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
 * KAsteroids - Copyright (c) Martin R. Jones 1997
 *
 * Part of the KDE project
 */




#ifndef __KAST_TOPLEVEL_H__
#define __KAST_TOPLEVEL_H__

#include <QMainWindow>
#include <QMultiHash>
#include <QMap>
#include <QShowEvent>
#include <QHideEvent>
#include <QKeyEvent>
#include <iostream>
#include<QLabel>

using namespace std;
#include"gmu.h"



#include "view.h"


class KALedMeter;
QT_BEGIN_NAMESPACE
class QLCDNumber;
QT_END_NAMESPACE

class KAstTopLevel : public QMainWindow
{
    Q_OBJECT
public:
    KAstTopLevel(gsvar vnofa, QWidget *parent = 0);
    virtual ~KAstTopLevel();
    void oukey();
private:
    void playSound( const char *snd );
    void readSoundMapping();
    void doStats();

protected:
    virtual void showEvent( QShowEvent * );
    virtual void hideEvent( QHideEvent * );
    virtual void keyPressEvent( QKeyEvent *event );
    virtual void keyReleaseEvent( QKeyEvent *event );


    // virtual void mouseMoveEvent( QMouseEvent *me );
    virtual void mousePressEvent( QMouseEvent *me );
    virtual void mouseReleaseEvent(  QMouseEvent *me );


private slots:
    void slotNewGame();

    void slotShipKilled();

    void slotnewship();
    void slotUpdateVitals();

private:
    pacview_widget *jpacview_;
    /*
    QLCDNumber *scoreLCD;
    QLCDNumber *levelLCD;
    QLCDNumber *shipsLCD;

    QLCDNumber *teleportsLCD;
    QLCDNumber *shieldLCD;
    QLCDNumber *speedm;
*/
    KALedMeter *powerMeter;

    QLabel *datalabel;
    QLabel *fueltextlabel_;
    QWidget *mainWin;
    QWidget *border;
    QPalette mainwinpal, borderpal, datalabelpal, powermeterpal;


    bool   sound;

    // waiting for user to press Enter to launch a ship
    bool waitShip;
    bool isPaused;

    int shipsRemain;
    int score;
    int level;
    bool showHiscores, bhud, bexh;
    int     ympy_, miskoh_, asthud_, jarru_, tzoomp_, tzoomd_, playon_;

    enum Action { Launch, Thrust, slower, RotateLeft, RotateRight, Shoot, Teleport,
                  Brake, Shield, Pause, NewGame, quit, koh, ammu, hud, asthud,
                  exh, ympy, miskoh, RotateLeftSlow, RotateRightSlow, zoomp, zoomd,
                  freelo, vapk, mousesteswitch, ghat, ksuuntvh, asuuntvh, lsuuntvh, fullsc, mleft,
                  mright, reconf, centerview, mine, detonate, edge, collect, clearb, minewait,
                  isohud, limiter, helptext, safetyon, shorthelphud, ppicsw, play_pause, skip_back_media };

    QMap<int, Action> actions;
    gsvar jgsvar_;
    gsett tjgsett_;

    QString cline_;

};

#endif

