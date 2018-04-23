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




//	--- toplevel.cpp ---
#define FALSE 0
#define TRUE 1

#include <QAction>
#include <QLabel>
#include <QLayout>
//#include <QLCDNumber>
#include <QPushButton>

#include <QApplication>
#include <QHBoxLayout>
#include <QShowEvent>
#include <QFrame>
#include <QPixmap>
#include <QHideEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include<cstdlib>
#include<cstdio>
#include<sstream>
#include <iomanip>
#include "toplevel.h"
#include "ledmeter.h"
//#include <QGLWidget>
#include <QOpenGLWidget>

#define SB_SCORE	1
#define SB_LEVEL	2
#define SB_SHIPS	3


KAstTopLevel::KAstTopLevel(gsvar vnofa, QWidget *parent)
    : QMainWindow(parent)
{
    border = new QWidget( this );
    //  border->setMouseTracking(1);
    border->setAutoFillBackground(1 );

    setCentralWidget( border );

    QVBoxLayout *borderLayout = new QVBoxLayout( border );
    borderLayout->addStretch( 100 );

     mainWin = new QWidget( border );
    mainWin->setFixedSize( vnofa.wwidth, vnofa.wheight );
    mainWin->setAutoFillBackground(1 );


    // mainWin->setMouseTracking(1);

    borderLayout->addWidget( mainWin, 0, Qt::AlignHCenter );

    borderLayout->addStretch( 100 );

    jpacview_ = new pacview_widget( vnofa, mainWin );
    jpacview_->makeCurrent();
    setAccessibleName(" toplevel-ac-n ");
    tjgsett_=jpacview_->outgsett();

    QPalette mainwinpal(tjgsett_.mainwincol, tjgsett_.mainwincol, QColor( 28, 18, 12 ),
                        QColor( 4, 24, 6 ), QColor( 8, 22, 2 ), Qt::yellow, tjgsett_.mainwincol );


    mainWin->setPalette( mainwinpal );
    mainWin->setAutoFillBackground(1 );
    QPalette borderpal(Qt::darkGreen, tjgsett_.bordercol, QColor( 28, 18, 18 ),
                       QColor( 24, 64, 6 ), Qt::black, Qt::green, QColor( 8, 22, 12 ) );

border->setPalette( borderpal );
border->setAutoFillBackground(1 );

    //new QGLWidget(QGLFormat(QGL::SampleBuffers ) )

    jpacview_->setMouseTracking(1);
    //    grabMouse(Qt::OpenHandCursor);

    jpacview_->grabMouse(Qt::CrossCursor);
    //view->grabMouse();
    //QWidget::setMouseTracking(1);

    jpacview_->setFocusPolicy( Qt::StrongFocus );
    connect( jpacview_, SIGNAL(shipKilled(int )), SLOT(slotShipKilled( /*int*/ ) ) );

    connect( jpacview_, SIGNAL(updateVitals()), SLOT(slotUpdateVitals()) );

    connect( jpacview_, SIGNAL( signewgame()  ) , SLOT( slotNewGame()  ) );
    connect( jpacview_, SIGNAL( signewship()  ) , SLOT( slotnewship()  ) );




    QVBoxLayout *vb = new QVBoxLayout( mainWin );
    QHBoxLayout *hb = new QHBoxLayout;
    QHBoxLayout *hbd = new QHBoxLayout;
    vb->addLayout( hb );

    QFont labelFont( "courier", 14 );

    hb->addSpacing( 5 );

    // QLabel *fueltextlabel;

    datalabel = new QLabel( "", mainWin );
    QFont dtfont( "courier", 17 );
    datalabel->setFont( dtfont );
    datalabelpal=QPalette( tjgsett_.datalabelcol, tjgsett_.mainwincol, QColor( 228, 18, 128 ),
                        QColor( 4, 4, 64 ), QColor( 8, 22, 2 ), Qt::red, tjgsett_.mainwincol );
    datalabel->setPalette( datalabelpal );
    datalabel->setFixedWidth( 1800 );
    hb->addWidget( datalabel );

    hb->addStretch( 4 );
    hb->addStretch( 3 );
    //hb->addStrut( 10 );

    vb->addWidget( jpacview_, 10 );

    // -- bottom layout:
    vb->addLayout( hbd );

    QFont smallFont( "courier", 14 );
    hbd->addSpacing( 4 );

    hbd->addStretch( 1 );

    fueltextlabel_ = new QLabel( tr( "Fuel" ), mainWin );
    fueltextlabel_->setFont( smallFont );
    fueltextlabel_->setFixedWidth( fueltextlabel_->sizeHint().width() + 10 );
    fueltextlabel_->setAutoFillBackground(1);
    fueltextlabel_->setPalette( datalabelpal );

    hbd->addWidget( fueltextlabel_ );


    powerMeter = new KALedMeter( mainWin );
    powerMeter->setFrameStyle( QFrame::Box | QFrame::Plain );
    powerMeter->setRange( MAX_POWER_LEVEL );
    powerMeter->addColorRange( 10, Qt::darkRed );
    powerMeter->addColorRange( 20, QColor(160, 96, 0) );
    powerMeter->addColorRange( 70, Qt::darkGreen );
    powerMeter->setCount( 40 );
    powermeterpal=QPalette(Qt::gray, tjgsett_.mainwincol, QColor( 228, 18, 128 ),
                           QColor( 4, 4, 64 ), QColor( 8, 22, 2 ), Qt::red, tjgsett_.mainwincol );
    powerMeter->setAutoFillBackground(1);
    powerMeter->setPalette( powermeterpal );
    powerMeter->setFixedSize( 200, 12 );
    hbd->addWidget( powerMeter );

    shipsRemain = 3;
    showHiscores = FALSE;

    actions.insert( Qt::Key_Up, Thrust );
    actions.insert( Qt::Key_Down, slower );
    actions.insert( Qt::Key_Left, RotateLeft );
    actions.insert( Qt::Key_Right, RotateRight );
    actions.insert( Qt::Key_Insert, RotateLeftSlow );
    actions.insert( Qt::Key_Home, RotateRightSlow );


    actions.insert( Qt::Key_Space, Shoot );
    actions.insert( Qt::Key_Z, Teleport );
    actions.insert( Qt::Key_X, Brake );
    actions.insert( Qt::Key_S, safetyon );
    actions.insert( Qt::Key_P, Pause );
    actions.insert( Qt::Key_T, Launch );
    actions.insert( Qt::Key_U, NewGame );

    actions.insert( Qt::Key_Escape, quit );


    actions.insert( Qt::Key_PageDown, koh );
    actions.insert( Qt::Key_PageUp, Shoot );
    actions.insert( Qt::Key_H, hud );
    actions.insert( Qt::Key_A, asthud );
    actions.insert( Qt::Key_E, exh );
    actions.insert( Qt::Key_Y, ympy );
    actions.insert( Qt::Key_K, miskoh );
    actions.insert( Qt::Key_L, limiter );

    actions.insert( Qt::Key_Plus, zoomp );
    actions.insert( Qt::Key_Minus, zoomd );

    actions.insert( Qt::Key_1, ksuuntvh );
    actions.insert( Qt::Key_2, asuuntvh );
    actions.insert( Qt::Key_3, lsuuntvh );
    actions.insert( Qt::Key_4, isohud );
    actions.insert( Qt::Key_5, shorthelphud );

    actions.insert( Qt::Key_6, play_pause );
    actions.insert( Qt::Key_7, skip_back_media );

    actions.insert( Qt::Key_F11, fullsc );
    actions.insert( Qt::Key_F10, freelo );
    actions.insert( Qt::Key_F9, vapk );
    actions.insert( Qt::Key_F8, mousesteswitch );
    actions.insert( Qt::Key_F7, ghat );

    actions.insert( Qt::Key_Comma, mleft );
    actions.insert( Qt::Key_Period, mright );

    actions.insert( Qt::Key_F5, reconf );
    actions.insert( Qt::Key_C, centerview );
    actions.insert( Qt::Key_M, mine );
    actions.insert( Qt::Key_D, detonate );
    actions.insert( Qt::Key_F12, edge );
    actions.insert( Qt::Key_F3, collect );
    actions.insert( Qt::Key_F2, clearb );
    actions.insert( Qt::Key_W, minewait );
    actions.insert( Qt::Key_F1, helptext );
    actions.insert( Qt::Key_9, ppicsw );



    bhud=1;
    bexh=1;
    ympy_=1;
    miskoh_=1;
    asthud_=1;
    jarru_=0;
    tzoomp_=0;
    tzoomd_=0;
    jgsvar_=vnofa;
    playon_=0;
    cline_="0000";


    slotNewGame();
}

void KAstTopLevel::oukey()
{
    cout << endl;

    QMapIterator<int, Action> qmite( actions );

    while( qmite.hasNext()  )
    {


        cout << hex << qmite.peekNext().key() << "  " << dec << qmite.next().value()  << endl;

    }

    cout << endl;
    cout << endl;

}


KAstTopLevel::~KAstTopLevel()
{
}

/*void KAstTopLevel::playSound( const char * )
{
    //QSound::play("Explosion.wav");
}
*/

void KAstTopLevel::keyPressEvent( QKeyEvent *event )
{

    if( event== QKeySequence::Quit  )

    {

        oukey();
        cout << " KAstTopLevel::keyPressEvent : quit  " << flush;
        //        emit destroyed();
        jpacview_->~pacview_widget();
        this->~KAstTopLevel();
        exit(-1);
    }

    if ( event->isAutoRepeat() || !actions.contains( event->key() ) )
    {
        event->ignore();

        return;
    }



    Action a = actions[ event->key() ];

    switch ( a )
    {

    case ksuuntvh:
        jpacview_->ksuunh();
        break;

    case asuuntvh:
        jpacview_->asuunh();
        break;

    case lsuuntvh:
        jpacview_->lsuunh();
        break;

    case isohud:
        jpacview_->isohud();
        break;

    case shorthelphud:
        jpacview_->shortmesturn();
        break;
    case fullsc:
        jpacview_->fusc();
        break;

    case freelo:
        jpacview_-> freelook();
        jpacview_->centerv(0);
        break;


    case vapk:
        jpacview_->set_free_angle();
        break;

    case mousesteswitch:
        jpacview_-> mouseste();
        break;

    case ghat:
        jpacview_-> ghattack();
        break;

    case limiter:
        jpacview_-> splimit();
        break;
    case mleft:
        jpacview_->mleft(1);
        break;

    case mright:
        jpacview_->mright(1);
        break;

    case reconf:
        jpacview_-> reloadconf();
        tjgsett_=jpacview_->outgsett();
        jgsvar_=jpacview_->outgsvar();
         mainwinpal=QPalette(Qt::darkGreen, tjgsett_.mainwincol, QColor( 8, 128, 128 ),
                            QColor( 4, 64, 64 ), QColor( 8, 22, 82 ), Qt::green, tjgsett_.mainwincol );


        mainWin->setPalette( mainwinpal );
        borderpal=QPalette(Qt::darkGreen, tjgsett_.bordercol, QColor( 228, 128, 128 ),
                           QColor( 224, 64, 64 ), Qt::black, Qt::green, QColor( 8, 22, 12 ) );

    border->setPalette( borderpal );
    datalabelpal=QPalette( tjgsett_.datalabelcol, tjgsett_.mainwincol, QColor( 228, 18, 128 ),
              QColor( 4, 4, 64 ), QColor( 8, 22, 2 ), Qt::red, tjgsett_.mainwincol );
            datalabel->setPalette( datalabelpal );
            powermeterpal=QPalette(Qt::gray, tjgsett_.mainwincol, QColor( 228, 18, 128 ),
                                   QColor( 4, 4, 64 ), QColor( 8, 22, 2 ), Qt::red, tjgsett_.mainwincol );
            powerMeter->setPalette( powermeterpal );
            fueltextlabel_->setPalette( datalabelpal );

        break;

    case quit:
        jpacview_->~pacview_widget();
        exit(0);
    case centerview:
        jpacview_->centerv(1);
        break;

        break;

    case koh:
        jpacview_->kohdista2( 1 );

        break;

    case ammu:
        jpacview_->shoot( TRUE );

        break;


    case RotateLeft:
        jpacview_->rotateLeft( TRUE );
        break;

    case RotateRight:
        jpacview_->rotateRight( TRUE );
        break;
    case RotateLeftSlow:
        jpacview_->rotateLeftSlow( TRUE );
        break;

    case RotateRightSlow:
        jpacview_->rotateRightSlow( TRUE );
        break;



    case Thrust:
        jpacview_->thrust( TRUE );
        break;

    case slower:
        jpacview_->jarru( 1 );
        break;

    case Shoot:
        jpacview_->shoot( TRUE );
        break;

    case safetyon:

        jpacview_->safetyon();
        break;

    case Teleport:
        jpacview_->teleport( TRUE );
        break;

    case Brake:
        jpacview_->brake(  );
        break;

    case mine:
        jpacview_->mine( );
        break;
    case detonate:
        jpacview_->deton();
        break;
    case edge:
        jpacview_->edge();
        break;
    case collect:
        jpacview_->minescollectswi();
        break;
    case clearb:
        jpacview_->clearb();
        break;
    case minewait:
        jpacview_->swaiting();
        break;

    case ppicsw:
        jpacview_->ppic();
        break;

    case hud:
        jpacview_->hud();

        break;
    case asthud:
        jpacview_->asthud();
        break;
    case helptext:
        jpacview_->helptext();

        break;

    case   play_pause:
        cline_="qdbus ";
        if( playon_==1  )
        {
            cline_+=jgsvar_.pausemedia;
            playon_=0;
        }
        else
        {
            cline_+=jgsvar_.playmedia;
            playon_=1;
        }
        system( cline_.toLatin1() );
        cout << "  mediaplayer dbus message " << flush;
        break;

    case   skip_back_media:

        cline_="qdbus ";
        cline_+=jgsvar_.skipbackmedia;
        system( cline_.toLatin1() );
        cout << "  mediaplayer dbus message " << flush;


        break;



    default:
        event->ignore();
        return;
    }
    event->accept();
}


void KAstTopLevel::keyReleaseEvent( QKeyEvent *event )
{
    if ( event->isAutoRepeat() || !actions.contains( event->key() ) )
    {
        event->ignore();
        return;
    }

    Action a = actions[ event->key() ];

    switch ( a )
    {
    case mleft:
        jpacview_->mleft(0);
        break;

    case mright:
        jpacview_->mright(0);
        break;





    case exh:
        jpacview_->explvis( );

        break;

    case ympy:

        jpacview_->ympy();
        break;

    case miskoh:

        jpacview_->miskoh( );

        break;
    case RotateLeft:
        jpacview_->rotateLeft( FALSE );
        break;

    case RotateRight:
        jpacview_->rotateRight( FALSE );
        break;
    case RotateLeftSlow:
        jpacview_->rotateLeftSlow( FALSE );
        break;

    case RotateRightSlow:
        jpacview_->rotateRightSlow( FALSE );
        break;
    case centerview:
    {
        jpacview_->centerv(0);
    }
        break;



    case Thrust:
        jpacview_->thrust( FALSE );
        break;
    case slower:
        jpacview_->jarru(0);
        break;

    case reconf:
        break;
    case zoomp:
        jpacview_->zoomp( 1 );

        break;

    case zoomd:

        jpacview_->zoomp( 0 );

        break;

    case Shoot:
        jpacview_->shoot( FALSE );
        break;

    case Brake:
        break;

    case Shield:
        break;

    case Teleport:
        jpacview_->teleport( FALSE );
        break;

    case Launch:
        slotnewship();
        /*
        if ( waitShip )
        {
            jpacview_->newShip();
            waitShip = FALSE;
        }
        else
        {
            event->ignore();
            return;
        }
        */

        break;

    case NewGame:
        slotNewGame();
        break;

    case Pause:
    {
        if( /*!isPaused*/ jpacview_->outpause()==0  )
        {
            jpacview_->pauseb( 1 );
            jpacview_->pause( TRUE );

            isPaused=1;
        }
        else
        {
            //   QMessageBox::information( this,  tr("KAsteroids is paused"),    tr("Paused") );
            jpacview_->pauseb( 0 );
            jpacview_->pause( FALSE );
            isPaused=0;

        }
    }
        break;

    default:
        event->ignore();
        return;
    }

    event->accept();
}

void KAstTopLevel::showEvent( QShowEvent *e )
{
    QMainWindow::showEvent( e );
    if(jpacview_->outpause()==0 )
    {
        jpacview_->pause( FALSE );
    }
    else
    {
        jpacview_->pause( 1 );

    }
    jpacview_->setFocus();
}



void KAstTopLevel::mousePressEvent( QMouseEvent *me )
{
    if( me->button()==Qt::LeftButton ){
        jpacview_->shoot( TRUE );
    }
    if( me->button()==Qt::RightButton ){
        jpacview_->kohdista2( TRUE );
    }
    if( me->button()==Qt::MiddleButton ){
        jpacview_->thrust( TRUE );
    }


    me->accept();

}
void KAstTopLevel::mouseReleaseEvent(  QMouseEvent *me )
{
    if( me->button()==Qt::MiddleButton ){
        jpacview_->thrust( 0 );
    }


    jpacview_->shoot( FALSE );


    me->accept();

}

void KAstTopLevel::hideEvent( QHideEvent *e )
{
    QMainWindow::hideEvent( e );
    jpacview_->pause( TRUE );
}

void KAstTopLevel::slotNewGame()
{
    score = 0;
    shipsRemain = SB_SHIPS;
    // scoreLCD->display( 0 );
    level = 0;
    //  levelLCD->display( level+1 );
    //   shipsLCD->display( shipsRemain-1 );
    jpacview_->newGame();
    //    view->showText( tr( "Press L to launch." ), yellow );
    jpacview_->newShip();
    waitShip = FALSE;
    isPaused = FALSE;
    jpacview_->pki(0);
    cout << endl << " shipsRemain " << shipsRemain << endl;

}
void KAstTopLevel::slotnewship()
{
    if ( waitShip )
    {
        jpacview_->newShip();
        waitShip = FALSE;
    }
    else
    {
        //   event->ignore();
        return;
    }

}


void KAstTopLevel::slotShipKilled( /*int reason */)
{
    shipsRemain--;
    //  shipsLCD->display( shipsRemain-1 );

    cout << endl << " shipsRemain " << shipsRemain << "   finite_pacs=" << tjgsett_.finite_pacs << endl;
    jpacview_->pki(1);

    if ( shipsRemain or tjgsett_.finite_pacs==0 )
    {
        waitShip = TRUE;

    }
    else
    {
        jpacview_->endGame();

    }

    // doStats();
    //        highscore->addEntry( score, level, showHiscores );
    // }
}


void KAstTopLevel::doStats()
{
    QString r( "0.00" );
    if ( jpacview_->shots() )
        r = QString::number( (double)jpacview_->hits() / jpacview_->shots() * 100.0,
                             'g', 2 );

    /* multi-line text broken in Qt 3
    QString s = tr( "Game Over\n\nShots fired:\t%1\n  Hit:\t%2\n  Missed:\t%3\nHit ratio:\t%4 %\n\nPress N for a new game" )
      .arg(view->shots()).arg(view->hits())
      .arg(view->shots() - view->hits())
      .arg(r);
*/

    //  jpacview_->showText( "Game Over.   Press N for a new game.", Qt::yellow, FALSE );
}

void KAstTopLevel::slotUpdateVitals()
{
    if( jpacview_->outgsett().powermeteron )
    {
        powerMeter->show();
        fueltextlabel_->show();
        powerMeter->setValue( jpacview_->fuel() );
    }
    else
    {
        powerMeter->hide();
        fueltextlabel_->hide();

    }
    stringstream ssn;
    string infostring;
    ssn.flags ( ios::right | ios::left | ios::fixed | ios::showpos );
    ssn.width(10);
    ssn.fill( '=');

    ssn.precision(2);
    ssn <<  "_velocity=" << setw( 8 ) << jpacview_->speed() << "_fuel=" << setw( 8 ) << jpacview_->fuel()
         << "_missiles=" << setw( 5 ) << jpacview_->missilecount() << "_ber=" << setw( 4 ) << jpacview_->bercount()
         << "_mines=" << setw( 4 ) << jpacview_->minecount() << "_fmines=" << setw( 4 ) << jpacview_->fminecount()
         << "_norm_gh=" << setw( 4 ) << jpacview_->outgsvar().norghostcount
         << "_spi_gh=" << setw( 4 ) << jpacview_->outgsvar().spinghostcount
         << "_closest=" << setw( 4 ) << jpacview_->outgsvar().ghpacetclo ;

    ssn  >> infostring;
    if( jpacview_->outgsett().infostringon==1 )
    {
        datalabel->show();
        datalabel->setText( infostring.c_str() );
    }
    else
    {
        datalabel->hide();

    }

}

