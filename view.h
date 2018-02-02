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



#ifndef __AST_VIEW_H__
#define __AST_VIEW_H__
#include <QtGui>

#include <QWidget>

#include <QList>
#include <QMultiHash>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimerEvent>
#include <QShowEvent>
#include <QResizeEvent>
#include<QGraphicsLineItem>
#include <QGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include<QOpenGLFunctions>

#include "sprites.h"
#include"ghost.h"
#include"consco.h"
#include"texthuds.h"
#define MAX_POWER_LEVEL          1000

QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE
#include <QtNetwork>

#include <stdlib.h>
#include <qlocalserver.h>
#include <qlocalsocket.h>

class grafield: public QGraphicsScene
{
    Q_OBJECT
protected:
 /*  void drawForeground( QPainter *painter, QRectF &rect )
   {
       painter->setPen( Qt::cyan );
       painter->setBrush( QColor( 111,111,111, 60) );
    painter->drawPoint( random()%4000,  random()%4000 );
painter->drawEllipse( 1000, 1000, 3000,2000 );
   }
*/

};


class pacview_widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    pacview_widget( gsvar &vnofa, QWidget *parent )  ;
    virtual ~pacview_widget();

    int refreshRate;
    void paczv();

    void reset();
    void newGame();
    void endGame();
    void newShip();

    void rotateLeft( bool r ) { rotateL = r;   rotateSlow = 5; intr_=1; }
    void rotateRight( bool r ) { rotateR = r;   rotateSlow = 5; intr_=1;  }
    void rotateLeftSlow( bool r ) { rotateLs = r; rotateSlow = 5; intr_=1;  }
    void rotateRightSlow( bool r ) { rotateRs = r; rotateSlow = 5;  intr_=1; }


    void thrust( bool t ) { thrustShip = t && shipPower > 0;
                            vnofa_.slowthrust=0;  vnofa_.slowthrust_c=1;
                            vnofa_.thrust=t;  vnofa_.thrust_c=1;

                          }
    void shoot( bool s ) { shootShip = s; shootDelay = 0; }
    void teleport( bool te) { teleportShip = te && mTeleportCount; }
    void brake();
    void pause(bool pau);
    void pauseb( bool pau )
    {
        vnofa_.pause=pau; vnofa_.pause_c=1;
    }
    bool outpause( ) {   return vnofa_.pause; }

    void freelook( ) { flipb( jgsett_.freelo ) ; jgsett_.freelo_c=1;


                     }

    void positioncheck( double xpo, double ypo );



    void vapkul( ) { flipb( jgsett_.sangle ); jgsett_.sangle_c=1; }
    void mouseste( ) { flipb( jgsett_.mst ) ; jgsett_.mst_c=1; }
    void ghattack( ) {  flipchar( vnofa_.ghattack ) ; vnofa_.ghattack_c=1; }

    void ksuunh(  ) { flipb( jgsett_.ksuuntvh ) ; jgsett_.ksuuntvh_c=1; }
    void asuunh(  ) { flipb( jgsett_.asuuntvh );jgsett_.asuuntvh_c=1; }
    void lsuunh(  ) { flipb( jgsett_.lsuuntvh ) ; jgsett_.lsuuntvh_c=1;}
    void shortmesturn() { flipb( jgsett_.shortmeson ); jgsett_.shortmeson_c=1; }

    void fusc(  ) { flipb( jgsett_.fullsc ); jgsett_.fullsc_c=1; }
    void reloadconf()
    {
        settin_.sync();
        takeset();
        fieldtt_.setSceneRect( backim_.rect().adjusted( -jgsett_.margin, -jgsett_.margin, jgsett_.margin, jgsett_.margin   )   );
        vnofa_.setcou=vnofa_.tec;
        vnofa_.reloadconf=0;
        vnofa_.reloadconf_c=1;

    }


    void splimit()
    {
        flipb( jgsett_.splon );
        jgsett_.splon_c=1;
    }
    void safetyon()
    {
        flipb( jgsett_.safetyon );
        jgsett_.safetyon_c=1;
    }

    void mleft( bool lf ) { mleft_=lf; }
    void mright( bool ri ) { mright_=ri; }
    void centerv(bool ce ) { vnofa_.centervie=ce; vnofa_.centervie_c=1;     }
    void mine() { mine_=1; vnofa_.mine=1; vnofa_.mine_c=1; }
    void deton() { det_=1; }
    void edge() {  flipchar( vnofa_.edgece ); vnofa_.edgece_c=1;

                }


    void minescollectswi() { flipb( vnofa_.minecollect  ); vnofa_.minecollect_c=1;
                             if( vnofa_.minecollect )
                             {
                                 vnofa_.minelay=2;
                             }
                             else
                             {
                                 vnofa_.minelay=0;
                             }
                                                  vnofa_.minelay_c=1;

                           }
    void takeset();
    gsett ogsett( ) { return jgsett_; }
    void clearb()
    {
        uint iter;
        for( iter=0; iter< boomvec_.size() ; iter++ )
        {
            boomvec_.at( iter )->~boom();
        }
        boomvec_.clear();
        vector< ghost*>::iterator itr;
        QList<QGraphicsLineItem*>::iterator litr;

        itr=ghvec_.begin();
        litr=sightli_.begin();
        while( itr!=ghvec_.end() )
        {
            ghost * ghitr=*itr;
            QGraphicsLineItem * linei=*litr;
            if(  ghitr->state()==0  )
            {
                ghitr->~ghost();
                linei->~QGraphicsLineItem();
                itr=ghvec_.erase( itr );
                litr=sightli_.erase( litr );


            }
            else
            {
                itr++;
                litr++;

            }


        }

    }

    void zoomp( int zoo )
    {
        if( zoo )
        {
            vzoomp_++;
        }
        else
        {
            vzoomp_--;
        }
        vnofa_.zoom_minus_c=1;
        vnofa_.zoom_plus_c=1;
    }
    void swaiting() {  flipb( vnofa_.minewait );  vnofa_.minewait_c=1; }

    void zoomd( int zoo ) { zoomd_=zoo; }
    void pki( int pkim)  { pkim_= pkim; pkib_=1; }



    int shots() const { return shotsFired; }
    int hits() const { return shotsHit; }
    int power() const { return shipPower; }
    float fuel() const { return vnofa_.fuel; }
    float speed() const { return speed_dir; }

    int missilecount() const { return vnofa_.missiles; }
    int bercount() const { return vnofa_.ber; }
    int fminecount() const { return minelis_.size(); }
    int minecount() const { return vnofa_.mines; }
    gsvar outgsvar() {      return vnofa_; }



    int teleportCount() const { return mTeleportCount; }
    int brakeCount() const { return mBrakeCount; }
    int shootCount() const { return mShootCount; }
    void kohdista2( bool koh ) { koh_=koh; kohin_=1; }

    void hud(  )
    {
     flipb( jgsett_.hud );
       hudcha ( jgsett_.hud );
       jgsett_.hud_c=1;


    }
void hudcha( bool hudb )
{
    if( !hudb )
    {
        jgsett_.asthud=0;
        jgsett_.isohud=0;
        jgsett_.ksuuntvh=0;
        jgsett_.asuuntvh =0;
        jgsett_.lsuuntvh=0;
        jgsett_.ympy=0;
    }
    else
    {
        jgsett_.asthud=1;
        jgsett_.isohud=1;
        jgsett_.ksuuntvh=1;
        jgsett_.asuuntvh =1;
        jgsett_.lsuuntvh=1;
        jgsett_.ympy=1;

    }
    jgsett_.asthud_c=1;
    jgsett_.isohud_c=1;
    jgsett_.ksuuntvh_c=1;
    jgsett_.asuuntvh_c=1;
    jgsett_.lsuuntvh_c=1;
    jgsett_.ympy_c=1;



}

    bool ohud() { return jgsett_.hud;  }
    void asthud(  ) { flipb( jgsett_.asthud );  jgsett_.asthud_c=1;  }
    bool oasthud() { return jgsett_.asthud; }
    void isohud(  ) { flipb( jgsett_.isohud ); jgsett_.isohud_c=1; }
    void helptext(  ) { flipb( jgsett_.helptexton ); jgsett_.helptexton_c=1; }

    void explvis ( ) { flipb( jgsett_.explvisible ); jgsett_.explvisible_c=1;   }
    void ympy(  ) { switchchar( jgsett_.ympy, 3 );   }
    void ppic(  ) { switchchar( jgsett_.ppicint, 3 );   }


    void miskoh( ) {  flipb( jgsett_.miskoh ) ; }
    void jarru( int jar )
    {
        vnofa_.revacc=jar; vnofa_.revacc_c=1; vnofa_.slowthrust=0;  vnofa_.slowthrust_c=1;
                          vnofa_.thrust=0;  vnofa_.thrust_c=1;
                          }

    void addghosts(const QList<QPixmap>  &aatau,
                   double x, double y, int count );


signals:
    void shipKilled( int reason );
    void rockHit( int size );
    void rocksRemoved();
    void updateVitals();

    void signewgame();
    void signewship();



public slots:
    void pacsendmessage();
    void pacreceivemessage();
    void pacserverstart();

private slots:
    void teknay();

protected:
    bool readSprites();

    void processMissiles();
    void processmines();
    void processShip();
    double randDouble();
    int randInt( int range );

    //  virtual void resizeEvent( QResizeEvent *event );
    virtual void timerEvent( QTimerEvent * );
    void mouseMoveEvent(QMouseEvent *me );
    //void mousePressEvent(  QMouseEvent *me );
    void showEvent( QShowEvent * );
    // void paintEvent(QPaintEvent * );

    void initializeGL();


private:
  QOpenGLTexture  *overpicgl ;

  //  QGraphicsScene fieldtt_;
    grafield fieldtt_;

    QGraphicsView viewtt_;
    QMap<int, QList<QPixmap> > animation;
    QList<KMissile*> missiles;


    //AnimatedPixmapItem *ship;

    pacship *ship;

    pacdirline *jmovline, *jpoiline, *jamline;
    velmismeter *jvmeter;
    pacdirline *viivab;
    hudtt *jhud_;
    double edex, edey, edex2, edey2, edex3, edey3;
    QColor satvari;
    QGraphicsTextItem *textSprite;
    QLocalServer *outserver;
    QLocalServer *inserver;

    QLocalSocket *insocket;
    QLocalSocket *outsocket;

    bool rotateL;
    bool rotateR;
    bool rotateLs;
    bool rotateRs;

    bool thrustShip;
    bool shootShip;
    bool teleportShip;
    bool brakeShip;
    bool pauseShip;
    bool shieldOn;

    bool vitalsChanged;

    double  shipAngleAst;
    int  rotateSlow;
    float  rotateRate;
    int  shipPower;

    int shotsFired;
    int shotsHit;
    int shootDelay;

    int mBrakeCount;
    int mShieldCount;
    int mTeleportCount;
    int mShootCount;

    double shipDx;
    double shipDy;
    double shipnop, speed_dir;
    double motionAngle,  xpacloc_,ypacloc_;



    int  textDy;
    int  mFrameNum;
    bool mPaused;
    int  mTimerId;


    QTimer *tektimer_;
    double tavx_, tavy_, goanglerad_, go_angle_rad2_, ship_angle_b_, shipradangle_b_;

    bool initialized_, koh_, edkoh_, hud_, asthud_, exh_;
    int ympy_, miskoh_, jarru_;


    double thru_;
    gsvar vnofa_;
    float scker;
    QImage backim_;
    QPixmap  *overlaypixmap_;

    marj *jmarj_;
    boxc *jbox_;
    QPixmap arenapxm_;
    ghost *aave_;
    ener *jene_;
    minett *jmine_;



    QList<marj*>  marlis_;
    QList<boxc*>  boxclis_;
    QList<ener*>  enelis_;
    QList<minett*>  minelis_;

    QList<QPixmap> ptau_, atau_, bctau_, enetau_, minepics_;
    QList<QGraphicsLineItem*> lines_;
    QList<QGraphicsLineItem*> sightli_;
    int colli_;
    float hpaix_, hpaiy_, aapaix_, aapaiy_, hpax2_, hpay2_;
    float traffic_collision_velocity_;
    float breakacc_;
    float slowro_;

    int vzoomp_, zoomd_, rove_;
    float tmpzoom_, zoomdel_, tped_, rotationvel_;
    QTransform muunto;
    QPainter painter;
    QPainter *maala;
    int cou_, pkim_, pkib_, pkimco_;
    double alti_, viean_, rdan_,  pevel_, norvel_;
    int margin_;
    pacinfo paci_;
    float rotationang_;

    vector< ghost *> ghvec_;
    aavehq jghosthq_;
    vector< sightline > jslinevec_;

    bool freelo_;
    bool vapk_;
    bool hiiri_, edhr_;
    bool ghat_;
    bool ksuuntvh_;
    bool asuuntvh_;
    bool lsuuntvh_, isohud_;

    bool fullsc_;
    bool mleft_, mright_,   reconf_, centerv_, mine_, det_;
    double movementdirrad_;
    int mouvx_, mouvy_, amvx_;

    long long int tecounter_, fcount_;
    long long int ngcou_;
    boom *jboom;

    vector< boom *> boomvec_;
    double edtavx_, edtavy_;
    bool mwait_, sbrake_, splon_, helptext_;
    QSettings settin_, keysset_;
    gsett jgsett_ ;
    float speed_limiter_;
    QColor visicol_, lksicol_;
    helpmes jhelpmes_;

    helphud  *jhelphud_;
    helphudsh  *jhelphudshort_ ;
    int explcount_;
    mesnum jmesntt_;

    float tavx2_, tavy2_, tavkulmrad3_;
    int intr_, kohin_;

    QList<QPixmap> piclis_;
QGraphicsRectItem * scenerectindicator_;



};





#endif
