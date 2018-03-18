/* Derived from Qt4 example software   "Ported Asteroids"
*
* Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
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

/* KAsteroids - Copyright (c) Martin R. Jones 1997
 *
 * Part of the KDE project
 */



#define FALSE 0
#define TRUE 1
#include <stdlib.h>
#include <math.h>
#include <qapplication.h>
#include <qnamespace.h>
#include <QAction>
#include <QMessageBox>
#include <QScrollArea>
//#include <QDir>
#include <QGraphicsItem>
#include <QTimerEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QShowEvent>
#include <QtDebug>
#include <iostream>
#include <string>
#include <QString>
#include <sstream>
#include<unistd.h>
#include<random>
#include <QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QGraphicsLineItem>

using namespace std;
#include"gmu.h"

#include "view.h"
#include "pacsettings.h"
#include"pacinit.h"

//#define REFRESH_DELAY           33
#define SHIP_STEPS              360
#define MAX_SHIP_SPEED		18  //12


#define OUT_OF_FUEL 0
#define TRAFFIC_COLLISION 1
#define GHOST 2


#define PI_X_2                  6.283185307
#ifndef M_PI
#define M_PI 3.141592654
#endif
#include"qbarrayio.h"

int anint( QByteArray qra )
{
    charintunion mru;

    mru.merk[0]=qra.at(0);
    mru.merk[1]=qra.at(1);
    mru.merk[2]=qra.at(2);
    mru.merk[3]=qra.at(3);
    return mru.sint;
}
QByteArray anqba( charintunion sis)
{
    QByteArray tul;

    tul.push_back( sis.merk[0] );
    tul.push_back( sis.merk[1] );
    tul.push_back( sis.merk[2] );
    tul.push_back( sis.merk[3] );


    return tul;
}



pacview_widget::pacview_widget( gsvar &vnofa, QWidget *parent)
    : QOpenGLWidget( parent) ,     fieldtt_(  ),  viewtt_( /* &fieldtt_, */ this ) ,  jghosthq_(  )
{
     srand( time(NULL) );

    vnofa_=vnofa;
    takeset();

    vnofa_.spotted=0;
    vnofa_.spottednum=0;
    vnofa_.spotted_lios=0;
    vnofa_.spottedby=0;

    vnofa_.ghpacetclo=9999993;
    jgsett_.quitb=0;

    paczv();

    mwait_=vnofa_.minewait;

    zoomdel_=0.002;
    tped_=vnofa_.scafa;

    viewtt_.resize( vnofa_.wwidth, vnofa_.wheight );

    makeCurrent();

    setAccessibleName("pacview_widget");
    viewtt_.setAccessibleName("viewtt");



    viewtt_.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    viewtt_.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //  viewtt_.setCacheMode(QGraphicsView::CacheBackground);
    //  viewtt_.setOptimizationFlag(  );
    viewtt_.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    // viewtt_.setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    // viewtt_.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate );

    viewtt_.setOptimizationFlags(QGraphicsView::DontClipPainter   | QGraphicsView::DontSavePainterState   | QGraphicsView::DontAdjustForAntialiasing);
    //  viewtt_.viewport()->setFocusProxy( this );
    setMouseTracking(1);
    //viewtt_.grabMouse(Qt::OpenHandCursor);
    //grabMouse(Qt::OpenHandCursor);
    //viewtt_.setTransformationAnchor( QGraphicsView::NoAnchor );
    viewtt_.setTransformationAnchor( QGraphicsView::AnchorViewCenter );
    tecounter_=0;

    string arp=vnofa_.filespath.toStdString()+jgsett_.arenapic;
    jgsett_.arenapic=arp;

    cout << " view.cpp: arenapic= " << jgsett_.arenapic << endl;


    arenapxm_.load( jgsett_.arenapic.c_str() );
    cout << " arenapic x=" << arenapxm_.width() << " y=" << arenapxm_.height() << endl;


    QPixmap pm2;

    string overlp=vnofa_.filespath.toStdString()+jgsett_.overlaypic;
    jgsett_.overlaypic=overlp;
    cout << " view.cpp: overlaypic= " << jgsett_.overlaypic << endl;
    if ( QFile::exists( jgsett_.overlaypic.c_str( ) )  )
    {
        overlaypixmap_=new QPixmap ( jgsett_.overlaypic.c_str(), 0, Qt::AutoColor );
        //    cout << " overlaypic x=" << overlaypixmap_->width() << " y=" << overlaypixmap_->height() << endl;
        if( jgsett_.grayscale )
        {
            tograyscale(  overlaypixmap_ );
        }
        if( arenapxm_.width()!=overlaypixmap_->width() or  arenapxm_.height()!=overlaypixmap_->height() )
        {
            cout << endl << endl << " pacview_widget::pacview_widget: ERROR: arena and overlay pictures different size "
                 << endl << "  " << arenapxm_.width() << "  " <<  overlaypixmap_->width() << "  " <<
                    arenapxm_.height() << "  " << overlaypixmap_->height()  << "  " << endl << endl;
            exit(-1);
        }
    }
    else
    {
        cout << endl << endl << jgsett_.overlaypic << "  does not exist in right place " << endl <<
                " using  " << jgsett_.arenapic << "  instead " << endl;
        overlaypixmap_=new QPixmap ( jgsett_.arenapic.c_str(), 0, Qt::AutoColor );
    }



    backim_=arenapxm_.toImage();
    arenapxm_.~QPixmap();

    /*fieldtt_.setItemIndexMethod( QGraphicsScene::BspTreeIndex );
    fieldtt_.setItemIndexMethod( QGraphicsScene::NoIndex );
    fieldtt_.setMinimumRenderSize(2);
    */
    fieldtt_.setBackgroundBrush( *overlaypixmap_ );
    painter.begin( overlaypixmap_ );
    painter.setPen( Qt::darkGray );
    painter.setBrush( QColor( 150, 50, 50, 160) );

    fieldtt_.setSceneRect( backim_.rect().adjusted( -jgsett_.margin, -jgsett_.margin, jgsett_.margin, jgsett_.margin   )   );
    viewtt_.setScene( &fieldtt_ );

    scenerectindicator_= new QGraphicsRectItem( fieldtt_.sceneRect() );
    //fieldtt_.addItem( scenerectindicator_  );
    scenerectindicator_->setBrush( QColor( 100, 50, 50, 120) );
    scenerectindicator_->setPen( QPen( Qt::darkGray, 20 ) );


    pathandfile( vnofa_.filespath, jgsett_.marjpicn  );
    pathandfile( vnofa_.filespath, jgsett_.boxcratepicn );
    pathandfile( vnofa_.filespath, jgsett_.enerpicn );
    pathandfile( vnofa_.filespath, jgsett_.minepicn );
    pathandfile( vnofa_.filespath, jgsett_.mine_nw_picn  );
    pathandfile( vnofa_.filespath, jgsett_.mi_mine_picn );
    pathandfile( vnofa_.filespath, jgsett_.mi_mine_nw_picn  );

    QPixmap minepng( jgsett_.minepicn.c_str());
    QPixmap mine_nw_png( jgsett_.mine_nw_picn.c_str());
    QPixmap mi_mine_png( jgsett_.mi_mine_picn.c_str());
    QPixmap mi_mine_nw_png( jgsett_.mi_mine_nw_picn.c_str());

    // QPixmap spotmine( jgsett_.spotmine.c_str() );

    jgsett_.minehawidth=minepng.width()/2;

    minepics_.push_back( minepng );
    minepics_.push_back( mine_nw_png );
    minepics_.push_back( mi_mine_png );
    minepics_.push_back( mi_mine_nw_png );
    //  minepics_.push_back(  spotmine );


    pacinith(  marlis_, boxclis_, enelis_, jgsett_, vnofa_, backim_, fieldtt_ );
    //   random_device rdtes;
    // cout << endl << " c++11 random_device=" << rdtes.entropy() << endl;

    fcount_=0;

    pathandfile( vnofa_.filespath, jgsett_.ghostpica  );
    pathandfile( vnofa_.filespath, jgsett_.ghostpicb  );
    QPixmap ghostpng1( jgsett_.ghostpica.c_str() );
    QPixmap ghostpng2( jgsett_.ghostpicb.c_str() );

    jgsett_.ghostwidth=ghostpng1.width();
    jgsett_.ghosthawidth=jgsett_.ghostwidth/2;
    atau_.clear();
    atau_.push_back( ghostpng1 );
    atau_.push_back( ghostpng2 );




    refreshRate =  jgsett_.refresh_delay;

    initialized_ = readSprites();


    tektimer_= new QTimer( this );
    tektimer_->start(1000);
    connect( tektimer_, SIGNAL(timeout()), this, SLOT( teknay() ) );


    mTimerId = -1;

    shipPower = MAX_POWER_LEVEL;
    vitalsChanged = TRUE;

    mPaused = TRUE;


    outserver = new QLocalServer(this);
    inserver = new QLocalServer(this);

    inserver->listen( jgsett_.server_in );
    outserver->listen( jgsett_.server_out );

    cout << " rem=" << outserver->removeServer( jgsett_.server_out ) << " -- " << endl;
    cout << " rem=" << inserver->removeServer( jgsett_.server_in ) << " -- " << endl;
    outserver->close();
    outserver->~QLocalServer();
    inserver->close();
    inserver->~QLocalServer();

    outserver = new QLocalServer(this);
    inserver = new QLocalServer(this);
    inserver->listen( jgsett_.server_in );
    outserver->listen( jgsett_.server_out );


    connect( outserver, SIGNAL(newConnection() ), this, SLOT( pacsendmessage() ) );
    connect( inserver, SIGNAL(newConnection() ), this, SLOT( pacserverstart() ) );

    hud_=1;
    asthud_=1;
    exh_=1;
    jarru_=0;
    thru_=0.05;
    breakacc_=0.19;
    hpaix_=-1234;
    hpaiy_=-1222;

    hiiri_=0;
    fullsc_=0;
    reconf_=1;
    vnofa_.reloadconf=0;


    mine_=0;
    det_=0;
    vnofa_.bord=QRect( backim_.rect()  );
    edtavx_=-123;
    edtavy_=-1235;
    explcount_=0;
    string servererrorstr;
    servererrorstr= outserver->errorString().toStdString()  ;
    cout << " outserver error=" << servererrorstr  << "-    " << endl;

    servererrorstr= inserver->errorString().toStdString()  ;
    cout << " inserver error=" << servererrorstr  << "-    " << endl;



    //  cout << endl << "  cl " << clock() / double( CLOCKS_PER_SEC )  << endl;
    viean_=0;
    pkimco_=0;
    QColor jhelpscol=QColor( jgsett_.shelphudtextr  ,jgsett_.shelphudtextg,
                             jgsett_.shelphudtextb,  jgsett_.shelphudtexta  );


    jhud_=new hudtt( enetau_, vnofa_, &fieldtt_ );
    jhelphud_=new helphud( enetau_, vnofa_, jgsett_, &fieldtt_ );
    jhelphudshort_=new helphudsh( enetau_, vnofa_, jgsett_,&fieldtt_ );

    jhelphudshort_->sethcolor( jhelpscol );

    if( jgsett_.hcmode )
    {
        jhud_->setVisible( 0 );
        jhelphud_  ->setVisible( 0 );
        jhelphudshort_->setVisible( 0 );
    }

    jgsett_.hudpre=jgsett_.hud;

    vnofa_.paclives=0;
    vnofa_.centervie=0;
    intr_=0;
    vnofa_.edgece=0;
    vnofa_.pause=0;
    vnofa_.slowthrust=0;
    vnofa_.thrust=0;

    vnofa_.revacc=0; vnofa_.revacc_c=1;

    srand( time(NULL) );
    bercolmes_cou_=1;
    cout << "  QOpenGLWidget::isValid()=" << QOpenGLWidget::isValid() << "  " << flush;
    sleep( 2 );

}

// - - -

void pacview_widget::initializeGL()
{
    //  initializeOpenGLFunctions();

    // overpicgl = new QOpenGLTexture( QImage( jgsett_.overlaypic.c_str() ) );

}

void pacview_widget::mouseMoveEvent(  QMouseEvent *me )
{
    // cout << me->pos().x() << " x " << me->y() << " y     " << flush;

    mouvx_=tavx_=me->x();
    mouvy_=tavy_=me->y();
    QPointF tavp;
    tavp=viewtt_.mapToScene( tavx_, tavy_ );
    tavx_=tavp.x();
    tavy_=tavp.y();

    goanglerad_=atan2( tavy_-( ship->y()+jgsett_.pachawidth ) , tavx_-( ship->x()+jgsett_.pachawidth )  );

    me->accept();


}



pacview_widget::~pacview_widget()
{
    qDeleteAll(missiles);  missiles.clear();

    cout << " ~pacview_widget(): outserver remove=" << outserver->removeServer( jgsett_.server_out ) << " -- " << endl;
    cout << " ~pacview_widget(): inserver remove=" << inserver->removeServer( jgsett_.server_in ) << " -- " << endl;

    outserver->close();
    outserver->~QLocalServer();

    inserver->close();
    inserver->~QLocalServer();
    painter.end();
    cout << endl << endl;


}

// - - -

void pacview_widget::takeset()
{


    pacset( vnofa_, jgsett_, jhelpmes_ );

}



void pacview_widget::reset()
{
    if ( !initialized_ )
        return;
    qDeleteAll(missiles);   missiles.clear();

    qDeleteAll(lines_);    lines_.clear();

    shotsFired = 0;
    shotsHit = 0;

    mFrameNum = 0;
    mPaused = FALSE;

    ship->hide();
    ship->setZValue(111);
    ship->setOpacity(1);


    fieldtt_.advance();

    viewtt_.resetTransform();
    tmpzoom_=vnofa_.scafa;
    vzoomp_=0;
    vnofa_.zoom_plus_bn=0;
    vnofa_.zoom_minus_bn=0;
    rove_=0;
    rotationvel_=0;

    pkim_=0;
    pkib_=0;
    viean_=0;
    pkimco_=0;

    ngcou_=0;
    vnofa_.mines=vnofa_.minesb;
    intr_=0;
    kohin_=0;
    vnofa_.slowthrust=0;
    vnofa_.slowthrust_c=1;

    vnofa_.thrust=0;
    vnofa_.thrust_c=1;


    vnofa_.minelay=0;
    vnofa_.edgece=0;
    vnofa_.pause=0;

    vnofa_.newgame=0;
    vnofa_.newship=0;
    vnofa_.brake=0;
    vnofa_.reloadconf=0;
    vnofa_.mine=0;
    vnofa_.deton=0;
    vnofa_.clearb=0;

    vnofa_.revacc=0; vnofa_.revacc_c=1;

    rotateL=0;
    rotateR=0;
    rotateLs=0;
    rotateRs=0;

}

// - --

void pacview_widget::newGame()
{


    if ( !initialized_ )
        return;

    reset();
    if( vnofa_.ghostsb>0 )
    {
        cout << endl << endl << "  pacview_widget::newGame(): ghostx=" << vnofa_.ghostx << endl <<
                " ghosty=" << vnofa_.ghosty  << endl << endl;
        positioncheck( vnofa_.ghostx, vnofa_.ghosty );
        addghosts( atau_, vnofa_.ghostx,  vnofa_.ghosty  , vnofa_.ghostsb  );
    }

    if ( mTimerId < 0 )
     //   mTimerId = startTimer( REFRESH_DELAY );
    mTimerId = startTimer( jgsett_.refresh_delay );

    emit updateVitals();

    hud_=1;
    asthud_=1;
    exh_=1;

    mine_=0;
    det_=0;
    mwait_=vnofa_.minewait;
    jgsett_.hudpre=jgsett_.hud;

    cou_=0;
    vnofa_.paclives=1;
    isohud_=1;
}

// - - -

void pacview_widget::endGame()
{
    qDeleteAll(missiles);  missiles.clear();
    cout << endl << " game over " << endl;
    exit(0);

}



void pacview_widget::pause( bool pau )
{
    if ( !initialized_ )
    {
        return;
    }

    if ( !mPaused && pau  )
    {
        if ( mTimerId >= 0 )
        {
            killTimer( mTimerId );

            mTimerId = -1;
        }
    }
    else
        if ( mPaused && !pau )
        {
          //  mTimerId = startTimer( REFRESH_DELAY );
            mTimerId = startTimer( jgsett_.refresh_delay );

        }

    mPaused = pau;
}
// - - -

void pacview_widget::positioncheck( double xpo, double ypo )
{
    double posx=xpo;
    double posy=ypo;
    bool err=0;

    if( posx<0 or posx>backim_.width()  )
    {
        cout << endl << endl << " positioncheck: ERROR x=" << posx << " width= " << backim_.width() << endl << endl;

        err=1;

    }
    if( posy<0 or posy>backim_.height()  )
    {
        cout << endl << endl << " positioncheck: ERROR y=" << posy << " height= " << backim_.height() << endl << endl;

        err=1;
    }
    if( err )
    {
        this->~pacview_widget();
        exit(-1);

    }
    QColor pix= QColor::fromRgb( backim_.pixel( xpo, ypo ) );
    uint pixr=backim_.pixel( xpo, ypo );
    if( pixr!=jgsett_.meadowc.rgb()  )
    {
        cout << endl << " positioncheck: ERROR pixel red=" << pix.red()
             << " pix green=" << pix.green() << " pix blue="  <<
                pix.blue() << endl << " should be, red=" <<
                jgsett_.meadowc.red()
             << " green= " << jgsett_.meadowc.green()
             << " blue="  <<  jgsett_.meadowc.blue() << endl;
        cout << endl;


        err=1;

    }
    if( err )
    {
        this->~pacview_widget();
        exit(-1);

    }


}

void pacview_widget::newShip()
{
    if ( !initialized_ )
        return;

    hpaix_=vnofa_.pac1x1-jgsett_.pachawidth;
    hpaiy_=vnofa_.pac1y1-jgsett_.pachawidth;

    hpax2_=vnofa_.pac1x1;
    hpay2_=vnofa_.pac1y1;

    positioncheck( vnofa_.pac1x1, vnofa_.pac1y1 );

    ship->setPos( hpaix_, hpaiy_  );


    ship->setFrame( 0 );

    ship->setVelocity( 0.0, 0.0 );
    shipDx = 0;
    shipDy = 0;
    shipAngleAst = 0;
    speed_dir=0;
    pevel_=0;
    norvel_=0;
    jarru_=0;
    rove_=0;
    rotationvel_=0;
    qDeleteAll(lines_);    lines_.clear();
    pkim_=0;
    pkib_=0;
    viean_=0;
    pkimco_=0;
    ship->setOpacity( 0.8 );
    mine_=0;
    det_=0;
    vnofa_.revacc=0; vnofa_.revacc_c=1;

    ship_angle_b_=shipAngleAst;

    rotateL = FALSE;
    rotateR = FALSE;
    thrustShip = FALSE;
    shootShip = FALSE;
    brakeShip = FALSE;
    teleportShip = FALSE;
    shootDelay = 0;
    shipPower = MAX_POWER_LEVEL;
    rotateSlow = 0;
    koh_=0;
    // jgsett_.miskoh=1;
    //    jgsett_.hud=1;
    //   jgsett_.asthud=1;
    jgsett_.hudpre=jgsett_.hud;

    exh_=1;
    vnofa_.missiles=vnofa_.missilesb;
    vnofa_.fuel=vnofa_.fuelb;
    vnofa_.paclives=1;
    vnofa_.thrust=0;
    vnofa_.thrust_c=1;
    vnofa_.slowthrust=0;
    vnofa_.slowthrust_c=1;
    freelo_=0;
    jgsett_.freelo=0;
    vapk_=1;
    // jgsett_.sangle=1;
    mleft_=0;
    mright_=0;
    reconf_=1;
    edkoh_=koh_;
    amvx_=mouvx_;

    mBrakeCount = 6;
    mTeleportCount = 6;
    mShootCount = 6;

    ship->show();
    vzoomp_=0;
    //  tmpzoom_=vnofa_.scafa;
    tmpzoom_=1;
    ship->setZValue(111);
    ship->setOpacity(1);
}

void pacview_widget::brake(  )
{
    if ( !initialized_ )
        return;

    sbrake_=1;
    vnofa_.slowthrust=0;
    vnofa_.slowthrust_c=1;
    vnofa_.thrust=0;
    vnofa_.thrust_c=1;
    vnofa_.brake=1;
    vnofa_.brake_c=1;
    thrustShip=0;
    vnofa_.revacc=0; vnofa_.revacc_c=1;


}

// - - -

bool pacview_widget::readSprites()
{
    pathandfile( vnofa_.filespath, jgsett_.pacpicn );
    pathandfile( vnofa_.filespath, jgsett_.pacpicn1 );
    pathandfile( vnofa_.filespath, jgsett_.pacpicn2 );
    pathandfile( vnofa_.filespath, jgsett_.pacpicn3 );
    pathandfile( vnofa_.filespath, jgsett_.missilepic );

    QPixmap pacmank( jgsett_.pacpicn.c_str()  );
    QPixmap pacmank1( jgsett_.pacpicn1.c_str() );
    QPixmap pacmank2( jgsett_.pacpicn2.c_str() );
    QPixmap pacmank3( jgsett_.pacpicn3.c_str() );
    QPixmap pacmissile( jgsett_.missilepic.c_str() );

    jgsett_.pacwidth=pacmank.width();
    jgsett_.pachawidth = jgsett_.pacwidth/2;

    piclis_.clear();

    piclis_.push_back(pacmank1);
    piclis_.push_back(pacmank2);
    piclis_.push_back(pacmank3);
    piclis_.push_back(pacmissile);

    jmovline = new pacdirline( &fieldtt_ );

    jpoiline = new pacdirline( &fieldtt_ );
    jamline = new pacdirline( &fieldtt_ );

    jvmeter= new velmismeter( &fieldtt_ );

    ship = new pacship( piclis_, &fieldtt_ );

    ship->setgs( vnofa_, jgsett_ );
    ship->hide();

    jmovline->setZValue(41);
    jamline->setZValue(42);
    jpoiline->setZValue(43);
    jvmeter->setZValue(44);

    ship->setZValue( 100 );


    return ( !ship->image(0).isNull()  );
}

// - - -



void pacview_widget::timerEvent( QTimerEvent * )
{
    //  vnofa_.spotted=0;
    vnofa_.spottednum=0;
    vnofa_.spotted_lios=0;
    vnofa_.spottedby=0;


    ship->setFrame( jgsett_.ppicint );
    ship->setgs( vnofa_, jgsett_ );

    jmovline->takecol( QColor( jgsett_.movliner, jgsett_.movlineg, jgsett_.movlineb, jgsett_.movlinea ) );
    jpoiline->takecol(  jgsett_.poilinecol );
    jamline->takecol( QColor( jgsett_.amliner, jgsett_.amlineg, jgsett_.amlineb, jgsett_.amlinea ) );
    jvmeter->takecol( QColor( jgsett_.edgr, jgsett_.edgg, jgsett_.edgb, jgsett_.edga ) );

    /*if( jgsett_.hcmode )
    {
        jmovline->setVisible( 0 );
        jpoiline-> setVisible( 0 );
        jamline->setVisible( 0 );
        jvmeter->  setVisible( 0 );
    }
*/
    tecounter_++;


    fcount_++;

    mesnum fner;
    fner.tcou=0;
    fner.tcoun=0;
    fner.distance=-3444;
    fner.mes=-123;
    fner.sernum=-12347;


    if( vnofa_.paclives )
    {
        ngcou_++;
    }
    vnofa_.ngcou=ngcou_;

    fieldtt_.advance();

    muunto.reset();
    movementdirrad_=atan2( shipDy, shipDx );


    if( ngcou_<2 )
    {
        xpacloc_=vnofa_.pac1x1;
        ypacloc_=vnofa_.pac1y1;
        //tmpzoom_=0.2;
        tmpzoom_=vnofa_.scafa;

        tped_=tmpzoom_;
        vzoomp_=1;
    }
    if(  tmpzoom_<1 and !jgsett_.freelo and ngcou_<500 )
    {
        //        tmpzoom_+=zoomdel_;
        viewtt_.centerOn( xpacloc_, ypacloc_ );
    }
    cou_++;

    if( vnofa_.tec==500 and  vnofa_.fps<21 )
    {
        cout << endl << "  CPU not fast enough. Too low frames per second(FPS), switching off view rotation. " << endl;
        cout << endl << "  Try smaller window or higher zoom" << endl;
        if( jgsett_.sangle )
        {
            set_free_angle();
        }
        vnofa_.shortmsg=8;
        vnofa_.shortmsg_c=1;

        fner.mes=8;
        fner.tcou=-110;
        fner.distance=-12349;
        fner.sernum=-2345;

        vnofa_.shortmsgcou=0;

        vnofa_.shortmsglist.append( fner );


    }
    if( vnofa_.berries_in>=jgsett_.collectgoal and jgsett_.collectgoal>0
            and bercolmes_cou_==1 )
    {

        cout << endl <<  endl << " collection goal " << jgsett_.collectgoal << " reached " << endl << endl
             << "  in " << vnofa_.tec << " cycles " << endl;
        bercolmes_cou_=0;
        vnofa_.shortmsg=7;
        vnofa_.shortmsg_c=1;

        fner.mes=7;
        fner.tcou=-100;
        fner.distance=-12349;
        fner.sernum=-2345;

        vnofa_.shortmsgcou=0;

        vnofa_.shortmsglist.append( fner );

    }

    muunto.reset();
    viewtt_.resetTransform();
    if( tmpzoom_< 6 and tmpzoom_> 0.1 )
    {
        tmpzoom_+=zoomdel_* float( vzoomp_ );

        if( ( tmpzoom_<= 1 and tped_>1 ) or ( tmpzoom_>= 1 and tped_< 1  ) )
        {
            tmpzoom_=1;
            vzoomp_=0;
        }
    }
    else
    {
        if( tmpzoom_> 6 )
        {
            tmpzoom_=4;
            vzoomp_=0;
        }
        else
        {



            if( tmpzoom_< 0.1 )
            {
                tmpzoom_=0.2;
                vzoomp_=0;

            }
            else
            {

            }
        }
    }
    tped_=tmpzoom_;


    if( pkim_ )
    {
        rotationvel_=0;
        speed_dir=0;
        norvel_=0;
        pevel_=0;
        rotateL=0;
        rotateR=0;
        rotateLs=0;
        rotateRs=0;
        vnofa_.paclives=0;
        if( pkib_)
        {
            rdan_=shipradangle_b_;
            alti_=0.05;
            pkib_=0;
            viean_=0;
        }
        viewtt_.centerOn( xpacloc_, ypacloc_ );
        if( pkimco_<50 )
        {
            pkimco_++;
            jgsett_.isohud=0;
            jgsett_.isohud_c=1;

        }
        else
        {
            alti_+=0.0004;
            viean_+=0.08;

        }
        tmpzoom_=1/alti_;

        //        jgsett_.hud=0;
        jmovline->hide();
        jpoiline->hide();
        jamline->hide();
        jvmeter->hide();
        //  jhud_->hide();



        muunto.reset();
        rotationang_=( 270-raddeg( rdan_ ) ) + viean_;
    }
    else
    {
        jvmeter->show();

        if( jgsett_.sangle )
        {
            rotationang_= jgsett_.moveangle-raddeg( shipradangle_b_ ) ;

        }
        else
        {
            rotationang_=jgsett_.defaultangle;

        }


    }


    muunto.rotate( rotationang_, Qt::ZAxis );
    //  muunto.rotate( jgsett_.depthangle, Qt::XAxis );

    muunto.scale( tmpzoom_, tmpzoom_ );
    viewtt_.setTransform( muunto  );


    vnofa_.zoom=tmpzoom_;
    vnofa_.viewangle=rotationang_;
    vnofa_.tec=tecounter_;


    cout.precision(2 );
    cout.flags ( ios::right | ios::fixed | ios::showbase );

    shipAngleAst +=rotationvel_;

    if ( shipAngleAst < 0 )
        shipAngleAst += SHIP_STEPS;

    if ( shipAngleAst >= SHIP_STEPS )
        shipAngleAst -= SHIP_STEPS;


    vnofa_.fuel-=fabs( ( ( pow( speed_dir, jgsett_.speedfuelexponent ) ) / 100.0 ) );

    if( !jgsett_.safetyon )
    {
        vnofa_.fuel-=jgsett_.readycost;
    }

    if( vnofa_.minelay==1 )
    {
        int iter, mtc=0;
        for( iter=0 ; iter< minelis_.size() ; iter++ )
        {
            if( qpfdistance( minelis_.at( iter )->pos(), ship->pos(),
                             jgsett_.minehawidth, jgsett_.pachawidth  )<vnofa_.minegap )
            {
                mtc=1;
                break;
            }
            else
            {

            }

        }
        if( !mtc )
        {
            mine_=1;

        }

    }

    if( vnofa_.mine==1 )
    {
        vnofa_.mine=0;
        mine_=1;
    }

    if( mine_ and ( ( vnofa_.mines>0 or jgsett_.finite_mines==0 ) or vnofa_.missiles>0 )  )
    {
        jmine_=new minett( minepics_, &fieldtt_, vnofa_ );
        if( vnofa_.mines>0 or ( jgsett_.finite_mines==0 and vnofa_.missiles<=0  )  )
        {
            jmine_->setmi(0);
            vnofa_.mines--;
        }
        else
        {
            jmine_->setmi(1);
            vnofa_.missiles--;

        }
        jmine_->setPos( xpacloc_-jgsett_.minehawidth, ypacloc_-jgsett_.minehawidth );
        minelis_.append( jmine_ );
        mine_=0;

    }
    if(  !( vnofa_.mines>0 or vnofa_.missiles>0 )  )
    {
        vnofa_.mine=2;
    }
    if(  vnofa_.mines<=0 and vnofa_.missiles>0   )
    {
        vnofa_.mine=3;
    }
    if( vnofa_.mines>0 and mine_==0 )
    {
        vnofa_.mine=0;
    }



    if( vnofa_.minecollect )
    {
        vnofa_.minelay=2;
        vnofa_.minelay_c=1;
        vnofa_.mine=2;
        vnofa_.mine_c=1;

        int iter;

        for( iter=0 ; iter< minelis_.size() ; iter++ )
        {
            if( distancepac( minelis_.at( iter )->x()+jgsett_.minehawidth, minelis_.at( iter )->y()+jgsett_.minehawidth, xpacloc_, ypacloc_ )< jgsett_.grabdistance )
            {
                if( minelis_.at( iter )->mis()==0 )
                {
                    vnofa_.mines++;
                }
                else
                {
                    vnofa_.missiles++;
                }
                delete minelis_.at( iter );
                minelis_.removeAt( iter );
            }
        }

    }
    else
    {
        if(   vnofa_.minelay==2 )
        {
            vnofa_.minelay=0;
            vnofa_.minelay_c=1;
        }
    }
    vnofa_.minesout=minelis_.size();

    if( vnofa_.ghattack_sel==0 )
    {
        vnofa_.ghattack=2;
    }
    else
    {
        if( vnofa_.ghattack==2 )
        {
            vnofa_.ghattack=1;

        }


    }


    if( jgsett_.freelo==1 )
    {
        vnofa_.edgece=2;
        vnofa_.edgece_c=1;
    }
    else
    {
        if( vnofa_.edgece==2 )
        {
            vnofa_.edgece=0;
            vnofa_.edgece_c=1;

        }

    }



    if( vnofa_.ghpacetclo< jgsett_.ghostwarndist )
    {
        vnofa_.close=1;
    }
    else
    {
        vnofa_.close=0;
    }


    //vnofa_.minewait wait_;

    if( /*jgsett_.hud and */ jgsett_.hcmode!=1 and !pkim_ )
    {
        if( jgsett_.ksuuntvh )
        {
            jmovline->show();
        }
        else
        {
            jmovline->hide();

        }
        if( jgsett_.asuuntvh )
        {
            jpoiline->show();
        }
        else
        {
            jpoiline->hide();
        }
        if( jgsett_.lsuuntvh )
        {
            jamline->show();
        }
        else
        {
            jamline->hide();
        }


    }
    else
    {
        /*    jmovline->hide();
        jpoiline->hide();
        jamline->hide();
        jvmeter->hide();
jhud_->hide();
//jgsett_.isohud=0;
*/

    }

    if( jgsett_.hud!=jgsett_.hudpre )
    {
        hudcha( jgsett_.hud  );

    }
    jgsett_.hudpre=jgsett_.hud;

    if( !jgsett_.miskoh )
    {

        jpoiline->takecol( jgsett_.poilinecol2 );

    }
    else
    {
        jpoiline->takecol( jgsett_.poilinecol  );


    }

    uint iter;
    int iters;
    uint iteru;


    xpacloc_=ship->x()+jgsett_.pachawidth;
    ypacloc_=ship->y()+jgsett_.pachawidth;


    if( vnofa_.thrust )
    {
        vnofa_.slowthrust=0;
        vnofa_.slowthrust_c=1;


    }

    if(/* sbrake_ */ vnofa_.brake==1 )
    {
        brakeShip=1;
        vnofa_.slowthrust=0;
        vnofa_.thrust=0;
        thrustShip=0;

    }
    else
    {
        //        brakeShip=0;


    }
    //   vnofa_.brake=brakeShip;

    vnofa_.vix=xpacloc_;
    vnofa_.viy=ypacloc_;


    if( !jgsett_.freelo)
    {
        if( vnofa_.edgece==1 and !pkim_ )
        {
            //   double xtr, ytr;
            QPointF tavp2, tap2;
            viewtt_.centerOn( ship );
            tavp2=viewtt_.mapFromScene( xpacloc_, ypacloc_  );
            // tap2=QPointF( view.mapToScene( tavp2.x(), tavp2.y()-( vnofa_.wheight/3.0 )  )   ) ;
            tap2=QPointF( viewtt_.mapToScene( tavp2.x(), 200  )   ) ;

            viewtt_.centerOn( tap2 );
            vnofa_.vix=tap2.x();
            vnofa_.viy=tap2.y();
        }
        else
        {
            viewtt_.centerOn( ship );


        }

        edtavx_=xpacloc_;
        edtavy_=ypacloc_;
    }
    else
    {

        if( vnofa_.centervie and vnofa_.bord.adjusted(20,20 ,-20 ,-20  ).contains( QPoint( tavx_, tavy_ ) )  )
        {
            if(  0)
            {
                viewtt_.centerOn( tavx_, tavy_ );
            }
            else
            {
                double stulx, stuly;
                anglelinepac( atan2( tavy_-edtavy_, tavx_-edtavx_ ), 15, stulx, stuly );
                tavx_=stulx+edtavx_;
                tavy_=stuly+edtavy_;
                viewtt_.centerOn( tavx_, tavy_ );


            }


        }
        edtavx_=tavx_;
        edtavy_=tavy_;
        vnofa_.centervie=0;
    }
    vnofa_.vix=viewtt_.mapToScene( vnofa_.wwidth/2 , vnofa_.wheight /2  ).x();
    vnofa_.viy=viewtt_.mapToScene( vnofa_.wwidth/2, vnofa_.wheight/2  ).y();
    vnofa_.viewangle=rotationang_;
    vnofa_.velocity=speed_dir;
    if( vnofa_.paclives and ngcou_>10 )
    {

    }

    if( jgsett_.hcmode!=1 )
    {
        jhelphudshort_->proch( );


        jhud_->setgsvar( vnofa_ );
        jhud_->setgsett( jgsett_ );
        if( vnofa_.paclives )
        {
            jhelphudshort_->sethcolor( QColor( jgsett_.shelphudtextr  ,jgsett_.shelphudtextg,
                                               jgsett_.shelphudtextb,  jgsett_.shelphudtexta  )  );
        }
        else
        {
            jhelphudshort_->sethcolor( QColor( jgsett_.shelphudbbtextr  ,jgsett_.shelphudbbtextg,
                                               jgsett_.shelphudbbtextb,  jgsett_.shelphudbbtexta  ) )   ;
        }

        jhelphud_->sethcolor( QColor( jgsett_.helphudtextr  ,jgsett_.helphudtextg,
                                      jgsett_.helphudtextb,  jgsett_.helphudtexta  )  );
        if( jgsett_.isohud )
        {
            jhud_->show();
        }
        else
        {
            jhud_->hide();

        }

        if( jgsett_.helptexton )
        {    jhelphud_->setgsvar( vnofa_ );

            jhelphud_->sethelpmes( jhelpmes_, 0 );
            jhelphud_->setgsett( jgsett_ );
            jhelphud_->show();
        }
        else
        {
            jhelphud_->hide();

        }



    }

    if( backim_.pixel( xpacloc_, ypacloc_ )==jgsett_.meadowc.rgb()  )
    {
        hpaix_=ship->x();
        hpaiy_=ship->y();
        if( vnofa_.trail )
        {
            painter.setPen( jgsett_.plotpointcol );

            painter.drawPoint( xpacloc_, ypacloc_ );

            if( vnofa_.tec% jgsett_.lineplot==0 )
            {
                lines_.push_back( fieldtt_.addLine( xpacloc_, ypacloc_, hpax2_, hpay2_,  QPen ( jgsett_.plotcol ) )  );


                hpax2_=ship->x()+jgsett_.pachawidth;
                hpay2_=ship->y()+jgsett_.pachawidth;

                if( lines_.size()>jgsett_.linelen  )
                {

                    lines_.at( 0 )->~QGraphicsLineItem();
                    lines_.removeFirst();
                }
                if( lines_.size()>jgsett_.linelen  )
                {

                    lines_.at( 0 )->~QGraphicsLineItem();
                    lines_.removeFirst();
                }

                hpax2_=ship->x() +jgsett_.pachawidth;
                hpay2_=ship->y()+jgsett_.pachawidth;
            }

            if( vnofa_.tec % jgsett_.plotgap==0  )
            {
                fieldtt_.setBackgroundBrush( *overlaypixmap_ );
            }

            if( jgsett_.ghostplot )
            {
                for( iter=0 ; iter< ghvec_.size() ; iter++ )
                {


                    float xcc=ghvec_.at( iter )->x()+jgsett_.ghosthawidth;
                    float ycc=ghvec_.at( iter )->y()+jgsett_.ghosthawidth;
                    painter.setPen( jgsett_.plotghpointcol );
                    painter.drawPoint( xcc, ycc );


                }
            }
        }
    }

    if( backim_.pixel( xpacloc_, ypacloc_ )!=jgsett_.meadowc.rgb()  )
    {
        vnofa_.slowthrust=0;  vnofa_.slowthrust_c=1;
        vnofa_.thrust=0;  vnofa_.thrust_c=1;
        thrustShip=0;
        ship->setPos( hpaix_, hpaiy_ );
        if( fabs( speed_dir )> jgsett_.traffic_collision_velocity )
        {
            speed_dir=0;

            ship->setVelocity(0,0);
            ship->setOpacity(0.5);
            ship->setZValue(-200 );

            vnofa_.shortmsg=4;
            vnofa_.shortmsg_c=1;
            jmesntt_.distance=-543;
            jmesntt_.mes=4;
            jmesntt_.tcou=-120;
            jmesntt_.sernum=-864;

            vnofa_.shortmsglist.append( jmesntt_ );

            vnofa_.shortmsgcou=-110;
            vnofa_.paclives=0;
            vnofa_.reason=TRAFFIC_COLLISION;
            emit shipKilled(  TRAFFIC_COLLISION );
        }

        if( !colli_  )
        {


            norvel_=norvel_*( -jgsett_.bounce_factor );
            pevel_=pevel_*( -jgsett_.bounce_factor );

            colli_=1;
        }
    }
    else
    {
        colli_=0;

    }
    if( vnofa_.fuel<=0 and vnofa_.paclives and jgsett_.finite_fuel )
    {
        speed_dir=0;
        ship->setVelocity(0,0);
        ship->setOpacity(0.5);
        // vnofa_.fuel=1000;
        if(pkim_==0)
        {
            ship->setOpacity(0.5);
            ship->setZValue(-200 );
            vnofa_.shortmsg=3;
            vnofa_.shortmsg_c=1;

            vnofa_.shortmsgcou=-110;

            jmesntt_.distance=-549;
            jmesntt_.mes=3;
            jmesntt_.tcou=-120;
            jmesntt_.sernum=-264;
            vnofa_.shortmsglist.append( jmesntt_ );

            vnofa_.reason=OUT_OF_FUEL;
            emit shipKilled( OUT_OF_FUEL  ) ;

        }
        pkim_=1;
        vnofa_.paclives=0;
    }

    jghosthq_.setgsvar( vnofa_ );
    jghosthq_.setgset( jgsett_ );



    jghosthq_.prghv( ghvec_, backim_, vnofa_, missiles, boomvec_, minelis_, xpacloc_, ypacloc_, pkim_ );
    if( vnofa_.paclives==0 and vnofa_.reason==GHOST )
    {
        if( pkim_==0  )
        {
            ship->setOpacity(0.5);
            ship->setZValue(-200 );
            vnofa_.shortmsg=5;
            vnofa_.shortmsg_c=1;

            vnofa_.shortmsgcou=-110;

            jmesntt_.distance=-249;
            jmesntt_.mes=5;
            jmesntt_.tcou=-120;
            jmesntt_.sernum=-564;
            vnofa_.shortmsglist.append( jmesntt_ );

            emit shipKilled( GHOST );
        }
        pkim_=1;

    }
    if( vnofa_.ghinv )
    {
        vnofa_.sightb=0;

    }

    if( ngcou_<2 )
    {
        fner.mes=6;
        fner.tcou=-110;
        fner.distance=-12349;
        fner.sernum=-2345;
        vnofa_.shortmsg=6;
        vnofa_.shortmsg_c=1;
        vnofa_.shortmsgcou=-110;

        vnofa_.shortmsglist.append( fner );


    }


    QPen kyn;
    if( jgsett_.hcmode!=1 )
    {
        for( iteru=0 ; iteru< ghvec_.size() ; iteru++ )
        {

            sightli_.at( iteru )->setLine( ghvec_.at( iteru )->sline().vii );

            sightli_.at( iteru )->setOpacity( 0.2);

            if( ghvec_.at( iteru )->sline().nak==0 )
            {
                kyn.setColor( jgsett_.visicol );
                if( jgsett_.asthud )
                {

                    sightli_.at( iteru )->show();
                    sightli_.at( iteru )->setOpacity( 0.9 );
                }
                else
                {
                    sightli_.at( iteru )->hide();

                }

            }


            if( ghvec_.at( iteru )->sline().nak==1 )
            {
                kyn.setColor(  jgsett_.lksicol );
                if( jgsett_.asthud and vnofa_.sightb )
                {


                    sightli_.at( iteru )->show();
                    sightli_.at( iteru )->setOpacity( 0.9 );

                }
                else
                {
                    sightli_.at( iteru )->hide();

                }

            }
            if( ghvec_.at( iteru )->sline().nak==2 )
            {
                kyn.setColor( Qt::blue );



                sightli_.at( iteru )->hide();
                sightli_.at( iteru )-> setOpacity( 0.5 );
            }
            if( ghvec_.at( iteru )->sline().nak==3 )
            {
                kyn.setColor( jgsett_.pacosightlinecol );
                if( jgsett_.asthud  )
                {
                    sightli_.at( iteru )->show();
                    sightli_.at( iteru )->setOpacity( 0.9 );


                }
                else
                {
                    sightli_.at( iteru )->hide();
                }
            }
            if( ghvec_.at( iteru )->sline().nak==4 )
            {
                kyn.setColor( jgsett_.pacomsightlinecol );
                if( jgsett_.asthud  )
                {
                    sightli_.at( iteru )->show();
                    sightli_.at( iteru )->setOpacity( 0.9 );


                }
                else
                {
                    sightli_.at( iteru )->hide();
                }
            }


            sightli_.at( iteru )->setPen( kyn );

        }
    }
    else
    {
        for( iteru=0 ; iteru< ghvec_.size() ; iteru++ )
        {
            sightli_.at( iteru )->hide();



        }
    }

    for( iter=0 ; iter< boomvec_.size() ; iter++ )
    {
        if( jgsett_.explvisible )
        {
            boomvec_.at( iter )->show();

        }
        else
        {
            boomvec_.at( iter )->hide();

        }

        if( boomvec_.at( iter )->age()<jgsett_.boomagelimit )
        {
            boomvec_.at( iter )->setgsett( jgsett_ );
            boomvec_.at( iter )->chaex( );

        }
    }
    goanglerad_=atan2( tavy_-( ypacloc_ ) , tavx_-( xpacloc_ )  );
    shipradangle_b_ = ship_angle_b_ * double( PI_X_2 / SHIP_STEPS );

    if( jgsett_.hcmode!=1 )
    {
        jmovline->setFrame();

        jmovline->setX( xpacloc_-150 );
        jmovline->setY( ypacloc_-150 );

        jmovline->setFrame();

        jpoiline->setX( xpacloc_-150 );
        jpoiline->setY( ypacloc_-150 );

        jpoiline->setFrame();


        jpoiline->takeangle( goanglerad_ );
        jmovline->takeangle( movementdirrad_ );
    }

    if( jgsett_.mst and !edhr_ )
    {

        amvx_=mouvx_;
    }
    if( !jgsett_.mst  and edhr_ )
    {
        rotationvel_=0;

    }
    //    jgsett_.msmi=miskoh_;


    edhr_=jgsett_.mst;

    fieldtt_.setgsvar( vnofa_, jgsett_ );


    if( intr_ )
    {
        if( koh_ )
        {
            rotateL=0;
            rotateR=0;

        }
        koh_=0;

    }

    if( koh_  and !edkoh_)
    {
        go_angle_rad2_=goanglerad_;
        tavx2_=tavx_;
        tavy2_=tavy_;
    }
    edkoh_=koh_;

    if( kohin_ )
    {
        tavx2_=tavx_;
        tavy2_=tavy_;
        kohin_=0;
    }

    if( koh_ )
    {
        tavkulmrad3_=atan2( tavy2_-( ship->y()+21 ) , tavx2_-( ship->x()+21 )  );


        if( fabs( angdiffpac( shipradangle_b_, tavkulmrad3_ )  )>degrad( 1 )  )
        {


            if( angdiffpac( shipradangle_b_, tavkulmrad3_ )>0  )
            {
                rotateL=1;
                rotateR=0;
                rotateSlow = 0;
            }
            else
            {
                rotateL=0;
                rotateR=1;
                rotateSlow = 0;


            }

            if( fabs( angdiffpac( shipradangle_b_, tavkulmrad3_ ) )< degrad( jgsett_.rotate_rate*1.1   )  )
            {
                shipradangle_b_= tavkulmrad3_;
                shipAngleAst=tavkulmrad3_/double( PI_X_2 / float( SHIP_STEPS ) );
                rotateL=0;
                rotateR=0;

                koh_=0;
            }
        }
        else
        {
            rotateL=0;
            rotateR=0;

            koh_=0;
        }

    }


    if( jgsett_.hcmode!=1 )
    {

        jamline->takeangle( atan2(  shipDy + sin( goanglerad_ )*double( jgsett_.missile_speed ),
                                    shipDx + cos( goanglerad_ )*double( jgsett_.missile_speed ) ) );

        jamline->setX( xpacloc_-150 );
        jamline->setY( ypacloc_-150 );
        jvmeter->setX( xpacloc_-300 );
        jvmeter->setY( ypacloc_-300 );

        jvmeter->takespeed( shipDx, shipDy, double( jgsett_.missile_speed
                                                    ), jgsett_.ympy  );


        if(   jgsett_.shortmeson  )
        {
            jhelphudshort_->show();

            jhelphudshort_->setgsvar( vnofa_ );
            if( vnofa_.shortmsgcou==0   )
            {

                jhelphudshort_->sethelpmes( jhelpmes_, vnofa_.shortmsg );
                jhelphudshort_->sethelpmes2( vnofa_ );

            }
            if( vnofa_.shortmsgcou>jgsett_.shortmsgcoulim )
            {
                vnofa_.shortmsglist.clear();


            }
            jhelphudshort_->setgsett( jgsett_ );
            vnofa_.shortmsgcou++;
        }
        else
        {
            jhelphudshort_->hide();
            vnofa_.shortmsgcou=jgsett_.shortmsgcoulim;
        }

    }




    if( jgsett_.berryvisible_pr!=jgsett_.berryvisible or vnofa_.tec<5 )
    {
        if( jgsett_.berryvisible )
        {
            for(iters=0 ; iters< marlis_.size() ; iters++ )
            {
                marlis_.at( iters )->show();
            }
        }
        else
        {
            for(iters=0 ; iters< marlis_.size() ; iters++ )
            {
                marlis_.at( iters )->hide();
            }
        }


    }
    jgsett_.berryvisible_pr=jgsett_.berryvisible;


    if( jgsett_.berrycollect )
    {
        for( iters=0 ; iters< marlis_.size() ; iters++ )
        {
            if( distancepac( marlis_.at( iters )->x()+jgsett_.berhawidth, marlis_.at( iters )->y()+jgsett_.berhawidth, xpacloc_, ypacloc_    )< jgsett_.grabdistance )
            {
                vnofa_.berries_in++;
                delete marlis_.at( iters );
                marlis_.removeAt( iters );
            }
        }

    }
    vnofa_.berries_meadow=marlis_.size();
    if( jgsett_.enercollect )
    {
        for(iters=0 ; iters< enelis_.size() ; iters++ )
        {
            enelis_.at( iters )->setVisible( jgsett_.enervisible );




            if( distancepac( enelis_.at( iters )->x()+jgsett_.enehawidth, enelis_.at( iters )->y()+jgsett_.enehawidth, xpacloc_, ypacloc_    )< jgsett_.grabdistance )
            {
                vnofa_.fuel+=100;
                delete enelis_.at( iters );
                enelis_.removeAt( iters );
            }
        }
    }
    else
    {
        for(iters=0 ; iters< enelis_.size() ; iters++ )
        {
            enelis_.at( iters )->setVisible( jgsett_.enervisible );
        }
    }

    if( jgsett_.boxcollect )
    {
        for(iters=0 ; iters< boxclis_.size() ; iters++ )
        {
            boxclis_.at( iters )->setVisible( jgsett_.boxvisible );

            if( distancepac( boxclis_.at( iters )->x()+jgsett_.boxhawidth, boxclis_.at( iters )->y()+jgsett_.boxhawidth, xpacloc_, ypacloc_    )< jgsett_.grabdistance )
            {
                vnofa_.missiles+=jgsett_.missilesadd;
                delete boxclis_.at( iters );
                boxclis_.removeAt( iters );
            }
        }
    }
    else
    {
        for( iters=0 ; iters< boxclis_.size() ; iters++ )
        {
            boxclis_.at( iters )->setVisible( jgsett_.boxvisible );
        }
    }
    emit updateVitals();





    processMissiles();
    processmines();

    if( ( vnofa_.mines==0 and vnofa_.mines_p>0 ) or ( vnofa_.missiles==0 and vnofa_.missiles_p>0   )  )
    {
        vnofa_.mine_c=1;
    }
    if( ( vnofa_.mines>0 and vnofa_.mines_p<=0 ) or ( vnofa_.missiles>0 and vnofa_.missiles_p<=0 )  )
    {
        vnofa_.mine=0;
        vnofa_.mine_c=1;


    }


    vnofa_.mines_p= vnofa_.mines;
    vnofa_.missiles_p=vnofa_.missiles;



    processShip();


    if ( vitalsChanged && !(mFrameNum % 10) ) {
        emit updateVitals();
        vitalsChanged = FALSE;
    }

    mFrameNum++;

    intr_=0;

    if( jgsett_.clearboomgh )
    {
        clearb();
        jgsett_.clearboomgh=0;
    }
    vnofa_.norvelocity=norvel_;
    vnofa_.pevelocity=pevel_;

    if( vnofa_.zoom_minus_bn==1  )
    {
        if(vnofa_.zoom_minus )
        {
            vzoomp_=-1;
        }
        else
        {
            vzoomp_=0;

        }

    }

    if( vnofa_.zoom_plus_bn==1  )
    {
        if( vnofa_.zoom_plus  )
        {
            vzoomp_=1;
        }
        else
        {

            vzoomp_=0;
        }

    }

    if( vzoomp_< 0 )
    {
        vnofa_.zoom_minus=1;
        vnofa_.zoom_plus=0;

    }
    if( vzoomp_>0 )
    {
        vnofa_.zoom_minus=0;
        vnofa_.zoom_plus=1;
    }
    if( vzoomp_==0 )
    {
        vnofa_.zoom_minus=0;
        vnofa_.zoom_plus=0;
    }

    if(  speed_dir==0 )
    {
        vnofa_.brake=2;
        vnofa_.brake_c=1;
    }
    else
    {
        if(  vnofa_.brake==2 )
        {
            vnofa_.brake=0;
            vnofa_.brake_c=1;

        }


    }

    if( vnofa_.reloadconf==1 )
    {
        reloadconf();
    }


    vnofa_.nofa_c=1;

    //view.update();    view.repaint();
}



// - - -


void pacview_widget::addghosts( const QList<QPixmap>  &aatau,
                                double x, double y, int count )
{
    int iter;
    for (  iter = 0; iter < count; iter++ )
    {
        ghost *aav = new ghost( aatau,  &fieldtt_, vnofa_,  x, y );
        aav->setPos( x-jgsett_.ghosthawidth, y-jgsett_.ghosthawidth );
        aav->setgsvar(  vnofa_, jgsett_ );
        aav->setsnumber( iter );
        QLine jsvi(x, y, 0, 0 );
        sightline ghyt;
        ghyt.vii=jsvi;
        ghyt.nak=0;
        sightline jsl;
        jsl.vii=jsvi;
        jsl.nak=0;
        //if( jgsett_.hcmode!=1 )        {

        sightli_.push_back( fieldtt_.addLine( jsvi ,  QPen (Qt::yellow  ) ) );
        aav->setsline( jsl );
        //}

        ghvec_.push_back( aav );



    }
}
void pacview_widget::processmines()
{
    int iter;
    for( iter=0 ; iter< minelis_.size() ; iter++ )
    {
        minelis_.at( iter )->setgsvar( vnofa_ );
        minelis_.at( iter )->setgsett( jgsett_ );

        if( qpfdistance( minelis_.at( iter )->pos(), ship->pos(),
                         jgsett_.minehawidth, jgsett_.pachawidth  )<jgsett_.explsafetydistance and !pkim_)
        {
            minelis_.at( iter )->setwaiting( 0 );
        }
        else
        {
            if( vnofa_.minewait )
            {
                minelis_.at( iter )->setwaiting( 1 );
            }

        }

        if( minelis_.at( iter )->expl()==1 )
        {
            boom *jboom=new boom( atau_, &fieldtt_ );
            jboom->setunival();
            jboom->setgsett( jgsett_ );
            jboom->setPos( minelis_.at( iter )->x(), minelis_.at( iter )->y() );
            boomvec_.push_back( jboom );
            minelis_.at( iter )->~minett();
            minelis_.removeAt( iter );
            explcount_++;
            cout << " lm  " << explcount_ << flush;
        }


    }

}


void pacview_widget::processMissiles()
{

    QList<KMissile*>::iterator itMissile = missiles.begin();
    while(itMissile != missiles.end())
    {
        (*itMissile)->growOlder();
        QPoint mipa( (*itMissile)->x(), (*itMissile)->y() );
        if ( (*itMissile)->expired() or backim_.pixel(  mipa  )==HILL or
             !vnofa_.bord.adjusted(20,20 ,-20 ,-20  ).contains( mipa )  or det_ )
        {
            (*itMissile)->setexpl(1);
            det_=0;

        }

        bool missileErased = false;

        if( (*itMissile)->expl()==1 )
        {
            boom *jboom=new boom( atau_, &fieldtt_ );
            jboom->setunival();
            jboom->setgsett( jgsett_ );
            jboom->setPos( (*itMissile)->x(), (*itMissile)->y() );
            boomvec_.push_back( jboom );

            delete (*itMissile);
            itMissile = missiles.erase(itMissile);
            explcount_++;
            cout << " rms " << explcount_ << flush;

            continue;
        }


        if(!missileErased)
            itMissile++;
    }
    if( missiles.size()==0 )
    {
        det_=0;
        vnofa_.deton=2;
    }
    else
    {
        if( vnofa_.deton==2)
        {
            vnofa_.deton=0;

        }

    }
}

// - - -

void pacview_widget::processShip()
{
    if ( ship->isVisible() )
    {
        if ( rotateSlow )
            rotateSlow--;

        if ( rotateL )
        {
            //   shipAngle -= rotateSlow ? 1 : jgsett_.rotate_rate;
            shipAngleAst -=jgsett_.rotate_rate;
            //shipAngle -= rotateSlow ? 0.1 : jgsett_.rotate_rate;
            if ( shipAngleAst < 0 )
                shipAngleAst += SHIP_STEPS;
            rove_=0;
            rotationvel_=0;

        }

        if ( rotateR )
        {
            // shipAngle += rotateSlow ? 1 : jgsett_.rotate_rate;
            shipAngleAst +=jgsett_.rotate_rate;
            if ( shipAngleAst >= SHIP_STEPS )
                shipAngleAst -= SHIP_STEPS;
            rove_=0;
            rotationvel_=0;

        }


        slowro_=jgsett_.slowro;
        if ( rotateLs )
        {
            rove_--;

            rotationvel_=slowro_*rove_;


        }


        if ( rotateRs )
        {
            rove_++;
            rotationvel_=slowro_*rove_;

        }
        if( jgsett_.mst  )
        {
            rotationvel_=( mouvx_-amvx_)*jgsett_.mousestevel;
        }
        if( fabs( rotationvel_ )> jgsett_.max_rotate_rate )
        {
            if( rotationvel_>0 )
            {
                rotationvel_=jgsett_.max_rotate_rate;
            }
            else
            {
                rotationvel_=jgsett_.max_rotate_rate*-1;

            }
        }
        ship_angle_b_=shipAngleAst;

        //        double angle = shipAngle * PI_X_2 / SHIP_STEPS;
        double angleradtt = ship_angle_b_ * double( PI_X_2 / SHIP_STEPS );

        speed_dir=distancepac( 0, 0,  pevel_, norvel_ );
        double vkul=atan2( pevel_, norvel_ ) ;


        double cosangle = cos( angleradtt );
        double sinangle = sin( angleradtt );

        anglelinepac( angleradtt+vkul, speed_dir, shipDx, shipDy  );
        if( brakeShip )
        {
            if( speed_dir > jgsett_.breakacc+0.2 )
            {
                speed_dir-=jgsett_.breakacc;
                anglelinepac( vkul, speed_dir, norvel_, pevel_   );
            }
            else
            {
                speed_dir =0;
                shipDx=0;
                shipDy=0;
                norvel_=0;
                pevel_=0;
                sbrake_=0;
                brakeShip=0;
                vnofa_.brake=0;
                //  vnofa_.brake_c=1;
            }

        }


        ship->setVelocity( shipDx, shipDy );
        ship->setTransformOriginPoint(21,21);
        ship->setRotation(  raddeg( angleradtt )+90  );


        if(   vnofa_.revacc )
        {

            if(norvel_>0)
            {
                norvel_-=jgsett_.breakacc;
            }
            else
            {
                norvel_-=jgsett_.thruacc;

            }
        }


        if( mleft_  and   fabs( speed_dir )<jgsett_.speed_limiterf )
        {
            pevel_-=jgsett_.thruacc;


        }
        if( mright_  and   fabs( speed_dir )<jgsett_.speed_limiterf )
        {
            pevel_+=jgsett_.thruacc;

        }


        if( jgsett_.splon   and   fabs( speed_dir )>jgsett_.speed_limiterf    )
        {


            if( norvel_>0 )
            {
                norvel_-=jgsett_.breakacc;

            }
            else
            {
                norvel_+=jgsett_.breakacc;
            }

        }

        if ( thrustShip or vnofa_.slowthrust  or vnofa_.thrust )
        {

            angleradtt = shipAngleAst * double( PI_X_2 / SHIP_STEPS );

            cosangle = cos( angleradtt );
            sinangle = sin( angleradtt );

            if( fabs( speed_dir ) < MAX_SHIP_SPEED and ( fabs( speed_dir )<jgsett_.speed_limiterf or !jgsett_.splon )     )
            {

                if( norvel_>0)
                {
                    if( !vnofa_.slowthrust )
                    {
                        norvel_+=jgsett_.thruacc;
                    }
                    else
                    {
                        norvel_+=jgsett_.slowthruacc;
                    }
                }
                else
                {
                    norvel_+=jgsett_.breakacc;
                }

            }
            else
            {

            }



            xpacloc_=ship->x()+jgsett_.pachawidth;
            ypacloc_=ship->y()+jgsett_.pachawidth;

            if( jgsett_.hcmode!=1 )
            {
                jmovline->setFrame();

                jmovline->setX( xpacloc_-150 );
                jmovline->setY( ypacloc_-150 );
            }


        }


        if( jgsett_.hcmode!=1 )
        {

            jmovline->setFrame();
        }

        double amkulm=0, angleb=0;
        if ( shootShip and !jgsett_.safetyon  )
        {

            goanglerad_=atan2( tavy_-( ship->y()+21 ) , tavx_-( ship->x()+21 )  );
            if( jgsett_.miskoh )
            {
                amkulm=goanglerad_ / double( PI_X_2 / SHIP_STEPS );
            }
            else
            {
                amkulm=shipAngleAst;

            }

            angleb = amkulm * double( PI_X_2 / SHIP_STEPS );

            cosangle = cos( angleb );
            sinangle = sin( angleb );


            if ( !shootDelay and ( vnofa_.missiles>0 or jgsett_.finite_missiles==0 )  )
            {
                vnofa_.missiles--;


                if( vnofa_.nofa==0 )
                {
                    vnofa_.vika=random()%10 ;

                }
                else
                {
                    vnofa_.vika=2;
                }
                KMissile *missile = new KMissile( piclis_, &fieldtt_,  vnofa_, jgsett_   );


                missile->setPos( jgsett_.pachawidth+ship->x()+( cosangle*jgsett_.pachawidth ),
                                 jgsett_.pachawidth+ship->y()+( sinangle*jgsett_.pachawidth ) );
                missile->setFrame( 3 );
                missile->setVelocity( shipDx + cosangle*double( jgsett_.missile_speed ),
                                      shipDy + sinangle*double( jgsett_.missile_speed ) );

                missiles.push_back( missile );
                shotsFired++;

                shootDelay = 5;
            }

            if ( shootDelay )
                shootDelay--;
        }


        vitalsChanged = TRUE;
    }
}

// - - -


void pacview_widget::teknay()
{
    vnofa_.fps=fcount_;
    fcount_=0;
    tektimer_->start(1000);

}


void pacview_widget::pacsendmessage()
{
    do
    {
        outsocket = outserver->nextPendingConnection();
    }while( outsocket == NULL );

    connect(outsocket, SIGNAL(disconnected() ), outsocket, SLOT(deleteLater() ) );


    QByteArray res;

    res=qbasend( vnofa_, jgsett_ );

    outsocket->write( res );

    outsocket->disconnectFromServer();
    paczv();

}



void pacview_widget::pacreceivemessage()
{

    QByteArray qtuo;


    qtuo=insocket->readAll();

    ciureceive( vnofa_, jgsett_, qtuo  );


    pause( vnofa_.pause );

    if( vnofa_.newgame  )
    {
        vnofa_.newgame=0;
        signewgame();

    }
    if( vnofa_.newship  )
    {
        vnofa_.newship=0;
        signewship();

    }

    if( vnofa_.clearb  )
    {
        vnofa_.clearb=0;
        clearb();

    }
    if( vnofa_.deton==1  )
    {
        vnofa_.deton=0;
        deton();

    }
    if( jgsett_.quitb )
    {
        this->~pacview_widget();
    }
    /*   if( vnofa_.slowthrust )
    {
        vnofa_.thrust=0;
    }*/

    insocket->disconnectFromServer();

}
void pacview_widget::pacserverstart()
{
    do
    {
        insocket   =  inserver->nextPendingConnection();
    }while(insocket==NULL);

    connect( insocket, SIGNAL(readyRead()  )  , this, SLOT( pacreceivemessage()  ) );
}
void pacview_widget::paczv()
{
    vnofa_.ghattack_c=0;
    vnofa_.centervie_c=0;
    vnofa_.minecollect_c=0;
    vnofa_.brake_c=0;
    vnofa_.minewait_c=0;
    vnofa_.edgece_c=0;
    vnofa_.sightb_c=0;
    vnofa_. spixu_c=0;
    vnofa_.spotted_c=0;

    jgsett_.splon_c=0;
    jgsett_.safetyon_c=0;
    jgsett_.freelo_c=0;
    jgsett_.sangle_c=0;
    jgsett_.fullsc_c=0;
    jgsett_.ksuuntvh_c=0;
    jgsett_.asuuntvh_c=0;
    jgsett_.lsuuntvh_c=0;
    jgsett_.miskoh_c=0;
    jgsett_.mst_c=0;
    jgsett_.msmi_c=0;
    jgsett_.hud_c=0;
    jgsett_.asthud_c=0;
    jgsett_.isohud_c=0;
    jgsett_.helptexton_c=0;
    jgsett_.shortmeson_c=0;
    jgsett_.ympy_c=0;


    vnofa_.shortmsg_c=0  ;
    vnofa_.pause_c=0  ;
    vnofa_.newgame_c=0  ;
    vnofa_.newship_c=0  ;
    vnofa_.zoom_plus_c=0  ;
    vnofa_.zoom_minus_c=0  ;
    vnofa_.reloadconf_c=0  ;
    vnofa_.mine_c=0  ;
    vnofa_.deton_c=0  ;
    vnofa_.clearb_c=0  ;
    jgsett_.ppicint_c=0  ;
    vnofa_.thrust_c=0  ;
    vnofa_.slowthrust_c=0  ;
    vnofa_.close_c=0  ;
    vnofa_.ghinv_c=0  ;
    vnofa_.hcmode_c= 0 ;
    vnofa_.reason_c=0  ;
    vnofa_.paclives_c=0  ;
    vnofa_.nofa_c=0  ;
    vnofa_.trail_c=0  ;
    vnofa_.ghost_mode_c=0 ;

    vnofa_.ener_c=0;
    vnofa_.speed_c=0;
    vnofa_.minelay_c=0;

    jgsett_.berryvisible_c=0;
    vnofa_.minevis_c=0;
    jgsett_.enervisible_c=0;
    jgsett_.boxvisible_c=0;

    jgsett_.berrycollect_c=0;
    jgsett_.enercollect_c=0;
    jgsett_.boxcollect_c=0;


}

double pacview_widget::randDouble()
{
    int v = qrand();
    return (double)v / (double)RAND_MAX;
}

int pacview_widget::randInt( int range )
{
    return qrand() % range;
}

void pacview_widget::showEvent( QShowEvent *e )
{

    QWidget::showEvent( e );
}


