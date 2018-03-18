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


#ifndef __SPRITES_H__
#define __SPRITES_H__
using namespace std;
#include <cstdlib>
#include<cmath>
#include<iostream>
#include<QPainter>
#include "consco.h"
#include "animateditem.h"
#include "gmu.h"
#include"texthuds.h"

class KMissile : public AnimatedPixmapItem
{
public:
    KMissile( const QList<QPixmap> &s, QGraphicsScene *c, gsvar gva, gsett jgs ) : AnimatedPixmapItem( s, c )
    { myAge = 0;
        mislas=random()%360;
        vika_=gva.vika;
        expl_=0;
        gva_=gva;
        jgs_=jgs;
    }
    void setexpl( bool e ) {  expl_=e; }
    bool expl() { return expl_; }

    void growOlder() { myAge++; }
    bool expired() { return myAge > jgs_.max_missile_age; }

    void advance( int phase )
    {
        if ( phase == 1 )
        {

            if( vika_==0 )
            {

                anglelinepac( degrad( mislas%360 ), 1, xplu, yplu  );
                moveBy( velx_+xplu, vely_+yplu  );

                mislas+=( ( random()%5 )+1 )*( ( ( random()%2 )*2 )-1 );

            }
            else
            {
                if( vika_>1 )
                {
                    moveBy( velx_, vely_  );


                }

                if( vika_==1 )
                {
                    if( myAge<10 )
                    {
                        moveBy( velx_, vely_  );
                    }
                    if( myAge==10 )
                    {
                        mislas=raddeg( atan2( vely_, velx_  )          );
                        moveBy( velx_, vely_  );
                        anglelinepac( atan2( vely_, velx_ ), 7, mx, my );

                    }
                    if( myAge>10 )
                    {
                        anglelinepac( degrad( mislas%360 ), 7, xplu, yplu  );
                        moveBy(  ( velx_- mx) +xplu, ( vely_- my) +yplu  );

                        mislas+=( double( ( random()%20 )+50 ) / 10.9 );
                    }

                }


            }

        }

    }


private:
    int myAge;
    int mislas;
    double xplu, yplu, mx, my;
    int vika_;
    bool expl_;
    gsvar gva_;
    gsett jgs_;
};



class marj : public AnimatedPixmapItem
{
public:
    marj( const QList<QPixmap> &pic, QGraphicsScene *c ): AnimatedPixmapItem( pic, c )
    {}




private:


};

class boxc : public AnimatedPixmapItem
{
public:
    boxc( const QList<QPixmap> &pic, QGraphicsScene *c ): AnimatedPixmapItem( pic, c )
    {}
private:

};

class ener : public AnimatedPixmapItem
{
public:
    ener( const QList<QPixmap> &pic, QGraphicsScene *c ): AnimatedPixmapItem( pic, c )
    {}
private:

};

class pacship : public AnimatedPixmapItem
{
public:
    pacship ( const QList<QPixmap> &pic, QGraphicsScene *c ): AnimatedPixmapItem( pic, c )
    { wid_=200; }
    void setgs( gsvar gsv, gsett gst ){ jgsva_=gsv;  jgst_=gst;  }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
               QWidget * /*widget*/)
    {
        wid_=jgst_.pacwidth;
        if( currentFrame!=0 )
        {
            painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap );
        }
        else
        {
            QColor edc=jgst_.pacshipcol;
            edc.setAlpha( edc.alpha()/2 );
            QPen reuk(  edc );
            reuk.setWidth( 1 );
            painter->setPen( reuk );

            painter->setBrush( QBrush( jgst_.pacshipcol, Qt::SolidPattern  )	  );
            float pla=0;
            //painter->drawEllipse( pla, pla, wid_, wid_  );
            painter->drawPie( pla, pla, wid_, wid_, ( 90-( jgst_.pacshipangle/2 ) )*16, ( jgst_.pacshipangle-360  )*16  );
        }
    }

private:
    gsvar jgsva_;
    gsett jgst_;

    float wid_;
};


class boom : public AnimatedPixmapItem
{
public:
    boom( const QList<QPixmap> &pic, QGraphicsScene *c ): AnimatedPixmapItem( pic, c )
    {

        expam_=0;
        //   setOpacity(0.95);
        //   setZValue( 100 );
        cond_=0;
        opac_=0.5;
        dia_=500;
        age_=0;
        jgs_.expvel1=24;
        jgs_.expvel2=-7;
        jgs_.expsize=11;
        jgs_.exco=33;
        jgs_.expvcg=80;
        jgs_.expvcb=30;
        jgs_.expvca=97;
        jgs_.condwidth=31;
        jgs_.condve=24;

    }
    void setunival()
    {
        setZValue( 1000 + ( random()%1000 ) );
    }

    void setgsett( gsett jgs )
    {
        jgs_=jgs;

    }

    void advance(int phase)
    {
        if (phase == 1)
        {
            //   prepareGeometryChange();
            age_++;
        }

    }


    QRectF boundingRect() const
    {


        if( age_<jgs_.boomagelimit)
        {

            float trec=jgs_.exco*jgs_.condve*0.6;
            QRectF neli( -trec, -trec, trec*2, trec*2 ) ;

            return neli;

        }
        else
        {
            QRectF neli(  -dia_/2, -dia_/2, dia_, dia_) ;
            return neli;

        }

    }

    void paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/  ,    QWidget * /*widget */)
    {
        //  prepareGeometryChange();

        QPen reuk( QColor(  200,100,0,70 ) );
        reuk.setWidth(1);
        painter->setPen( reuk );

        painter->setBrush( QBrush( QColor(  3,5,0,70 ), Qt::SolidPattern	)  );
        //     painter->drawRect( boundingRect() );
        //painter->drawText(0,0, "boom");

        if( age_>0 and expam_>0 )
        {
            double expcg=255-( age_*( 254.0/jgs_.expvcg  ) );
            double expcb=255-( age_*( 254.0/jgs_.expvcb  ) );
            double expca=255-( age_*( 254.0/jgs_.expvca  ) );


            limsetb( expcg, " sprites.h :: boom :: paint : expcg ", 1 );
            limsetb( expcb, " sprites.h :: boom :: paint : expcb ", 0 );
            limsetb( expca, " sprites.h :: boom :: paint : expca ", 1 );

            limsetc( expam_, jgs_.expsize*jgs_.expvel1  , " sprites.h :: boom :: paint : expcount1_ ", 1 );
            limsetc( expam_, 2000  ," sprites.h :: boom :: paint : expcount1_ 2000 b ", 1 );



            painter->setBrush( QBrush( QColor(  255, expcg, expcb, expca  ), Qt::SolidPattern	)  );

            painter->drawEllipse( ( expam_/-2), expam_/-2, expam_, expam_  );


        }
        if( age_< jgs_.exco )
        {
            float expck=255-( age_*( 255.0/jgs_.exco ) );
            if( expck>255 or expck<0 )
            {
                cout << endl << " sprites.h :: boom :: paint : expck " << expck << endl;
                if( expck>255 ) expck=255;
                if( expck<0 )  expck=0;

            }

            QPen kyn(QColor(  100, 100,100, expck ) );

            kyn.setWidth( jgs_.condwidth );

            painter->setPen( kyn );
            painter->setBrush(  Qt::NoBrush	  );
            cond_=age_* jgs_.condve;
            painter->drawEllipse(  cond_/-2, cond_/-2, cond_, cond_  );
            setOpacity( 1);
            //  setZValue(200);


        }
        if( age_> jgs_.exco and expam_<=0 )
        {
            QPen kyn2( QColor(  4,10,0 ) );
            kyn2.setWidth(2);

            painter->setPen( kyn2 );

            painter->setBrush( QBrush( QColor(  3,5,0 ), Qt::SolidPattern	)  );
            painter->drawEllipse( -15, -15, 30, 30  );
            setOpacity( 0.3);
            setZValue(-100);
            dia_=40;
        }

        // prepareGeometryChange();
        dia_=70;
    }
    void chaex()
    {
        if( age_<jgs_.expsize )
        {
            expam_+=jgs_.expvel1;
        }
        else
        {
            expam_+=jgs_.expvel2;
        }
        //prepareGeometryChange();

    }

    int age()
    {
        return age_;
    }

private:

    int cond_, dia_, age_;
    double expam_;
    float opac_;
    QRectF nel_;
    gsett jgs_;

};


class minett : public AnimatedPixmapItem
{
public:
    minett( const QList<QPixmap> &s, QGraphicsScene *c, gsvar gva ) : AnimatedPixmapItem( s, c )
    {
        age_=0;
        expl_=0;
        exco_=0;
        ite_=0;
        setOpacity(0.95);

        cond_=80;
        opac_=0.5;
        dia_=s.at(0).height();
        waiting_=gva.minewait;
        setZValue(-100);
        spotsgh_=0;

    }
    void setexpl( bool e ){  expl_=e; }
    void setspotsgh( bool spot ) { spotsgh_=spot; }
    void setspotsghlios( bool spot ) { spotsghlios_=spot; }

    bool ghspot() { return spotsgh_; }
    bool ghspotlios() { return spotsghlios_; }

    bool expl() { return expl_; }
    void setwaiting( bool w ) {  waiting_=w; }
    void setmi( bool mi) { mimine_=mi; }
    bool wai() { return waiting_; }
    bool mis() { return mimine_; }
    void setgsvar( gsvar h ) { gva_=h; waiting_=gva_.minewait;  }
    void setgsett( gsett gs ) { jgs_=gs;  }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
               QWidget * /*widget*/)
    {
        painter->setPen( jgs_.minespotsghcol );
        painter->setBrush( jgs_.minespotsghbrushcol );

        if( gva_.minevis )
        {
            if( waiting_ )
            {
                if( mimine_ )
                {
                    painter->drawPixmap(0, 0, frames.at(2).pixmap );

                }
                else
                {
                    painter->drawPixmap(0, 0, frames.at(0).pixmap );
                }
            }
            else
            {
                if( mimine_ )
                {
                    painter->drawPixmap(0, 0, frames.at(3).pixmap );

                }
                else
                {
                    painter->drawPixmap(0, 0, frames.at(1).pixmap );
                }
            }


            if( spotsgh_==1 and jgs_.minechangedbyghost )
            {
                painter->drawEllipse( 0, 0, dia_ , dia_ );
            }
            if( spotsghlios_==1 and jgs_.minechangedbyghost  )
            {
                painter->setPen( jgs_.minespotsghlioscol );
                painter->setBrush( jgs_.minespotsghliosbrushcol );
                painter->drawEllipse( 5, 5, dia_-10 , dia_-10 );
            }

        }
        //painter->drawRect( boundingRect() );

        /*      painter->setPen( Qt::white );
      painter->drawPoint( 10, 10 );
      painter->setPen( Qt::cyan );
      painter->drawPoint( jgs_.minehawidth, jgs_.minehawidth );
*/
    }


    void advance(int phase)
    {
        if ( phase == 1 )
        {

            age_++;

        }

    }
    int age()
    {
        return age_;
    }
    QRectF boundingRect() const
    {
        QRectF neli(  0, 0, dia_,dia_) ;

        return neli;
    }
private:

    bool expl_;
    int exco_, ite_, cond_, dia_, age_;
    float opac_;
    bool waiting_, mimine_, spotsgh_, spotsghlios_ ;
    gsvar gva_;
    gsett jgs_;
};



#endif
