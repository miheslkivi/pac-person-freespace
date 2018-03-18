/*
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
*
*
*** You may use this file under the terms of the BSD license as follows:
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
    **   * The names of its contributors may not be used to endorse or promote
    **     products derived from this software without specific prior written
    **     permission.
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
    **
    **
    ****************************************************************************/


#include "messages.h"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>
#include <QGraphicsScene>

#include <cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>
#include <QTextCodec>
#include <QGraphicsItem>
#include <QColor>
#include <cstdlib>
#include"geome.h"
#include"gmu.h"
#include<sstream>

#include"texthuds.h"
using namespace std;




hudtt::hudtt( QList<QPixmap> &qlipxmap, gsvar &jgsvar, QGraphicsScene *scene)
    : QGraphicsItem(0) /*, currentFrame(0), vx(0), vy(0)*/
{
    currentFrame=0;

    for (int i = 0; i < qlipxmap.size(); ++i) {
        QPixmap pixmap = qlipxmap.at(i);
        Frame frame;
        frame.pixmap = pixmap;
        frame.shape = QPainterPath();
        frame.boundingRect = pixmap.rect();
        frames << frame;
    }
    setZValue(10000);
    scene->addItem(this);
    jgv_=jgsvar;
}

void hudtt::setFrame(int frame)
{
    if (!frames.isEmpty()) {
        prepareGeometryChange();
        currentFrame = frame % frames.size();
    }

}

void hudtt::advance(int phase)
{
    if (phase == 1)
    {

        jtr.reset();

        jtr.rotate( 0-jgv_.viewangle );

        jtr.scale( 1/jgv_.zoom, 1/jgv_.zoom );

        setTransform( jtr );
        setPos( jgv_.vix, jgv_.viy  );

    }

}

QRectF hudtt::boundingRect() const
{
    int brs=2000;
    QRectF neli( brs/-2, brs/-2 , brs, brs ) ;
    return neli;

}


void hudtt::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QColor vari2( jgsett_.hudtextr,  jgsett_.hudtextg, jgsett_.hudtextb, jgsett_.hudtexta );

    painter->setPen(vari2);
    // QTextCodec::setCodecForCStrings (QTextCodec::codecForName("UTF-8"));
    string vel, fuel, mines, closest, miss;
    stringstream vels, fuels;

    QFont regularhudfont(jgsett_.hudfontname, jgsett_.hudfontsize, jgsett_.hudfontweight );
    QFont boldhudfont( jgsett_.hudfontname, jgsett_.hudboldfontsize, jgsett_.hudboldfontweight );


    painter->setFont( regularhudfont );

    painter->drawText( jgsett_.fuelcoord, hudmqs("fuel",jgv_.fuel ) );
    painter->drawText(jgsett_.velcoord, hudmqs("vel", jgv_.velocity  ) );
    painter->drawText( jgsett_.minescoord, hudmqs("mines", jgv_.mines ) );
    painter->drawText( jgsett_.misscoord, hudmqs("missiles", jgv_.missiles ) );
    painter->drawText(jgsett_.closestcoord, hudmqs("closest", jgv_.ghpacetclo ) );
    painter->drawText( jgsett_.berriescoord, hudmqs( "berries", jgv_.berries_in ) );
    painter->drawText( jgsett_.ghostscoord, hudmqs( "ghosts", jgv_.ghostcount  ) );
    painter->drawText( jgsett_.zoomcoord, hudmqs( "zoom", jgv_.zoom  ) );

    painter->drawText( jgsett_.fpscoord, hudmqs( "fps", jgv_.fps  ) );

    painter->setFont( regularhudfont );
    painter->drawText( jgsett_.teccoord , hudmqs( "cou", jgv_.tec  ) );
    painter->drawText( jgsett_.setcoucoord , hudmqs( "setcou", jgv_.setcou  ) );

    painter->drawText( jgsett_.vixcoord , hudmqs( "x", jgv_.vix  ) );
    painter->drawText( jgsett_.viycoord , hudmqs( "y", jgv_.viy  ) );

    hudbool("mouseste", jgsett_.mst, painter, regularhudfont, boldhudfont, jgsett_.mousestcoord   );

    hudbool("mousemissile", jgsett_.miskoh, painter, regularhudfont, boldhudfont, jgsett_.mousemicoord  );

    hudbool("minew", jgv_.minewait, painter, regularhudfont, boldhudfont, jgsett_.minewaitcoord  );
    hudbool("ghostsatt", jgv_.ghattack, painter, regularhudfont, boldhudfont, jgsett_.ghattackcoord );
    hudbool( "autobrake", boolt( jgv_.brake ), painter, regularhudfont, boldhudfont, jgsett_.brakecoord   );
    hudbool( "slimiter", jgsett_.splon, painter, regularhudfont, boldhudfont, jgsett_.sploncoord   );
    hudbool( "safety", jgsett_.safetyon, painter, regularhudfont, boldhudfont, jgsett_.safetyoncoord   );
    hudbool( "minecollect", jgv_.minecollect, painter, regularhudfont, boldhudfont, jgsett_.minecollectcoord   );

}

/*helphud hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh*/





helphud::helphud(QList<QPixmap> &qlipxmap, gsvar &jgsvar, gsett jgset, QGraphicsScene *scene )
    : QGraphicsItem(0) /*, currentFrame(0), vx(0), vy(0)*/
{
    currentFrame=0;

    for (int i = 0; i < qlipxmap.size(); ++i) {
        QPixmap pixmap = qlipxmap.at(i);
        Frame frame;
        frame.pixmap = pixmap;
        frame.shape = QPainterPath();
        frame.boundingRect = pixmap.rect();
        frames << frame;
    }
    setZValue(11000);
    scene->addItem(this);
    jgv_=jgsvar;
    hcol_=QColor( jgset.helphudtextr,  jgset.helphudtextg, jgset.helphudtextb, jgset.helphudtexta );

}

void helphud::setFrame(int frame)
{
    if (!frames.isEmpty()) {
        prepareGeometryChange();
        currentFrame = frame % frames.size();
    }

}

void helphud::advance(int phase)
{
    if (phase == 1)
    {

        jtr.reset();

        jtr.rotate( 0-jgv_.viewangle );

        jtr.scale( 1/jgv_.zoom, 1/jgv_.zoom );

        setTransform( jtr );
        setPos( jgv_.vix, jgv_.viy  );

    }

}

QRectF helphud::boundingRect() const
{
    int brs=2000;
    QRectF neli( brs/-2, brs/-2 , brs, brs ) ;
    return neli;

}


void helphud::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{


    painter->setPen( hcol_ );

    string vel;
    stringstream vels;

    QFont font( jgsett_.helphudfontname, jgsett_.helphudfontsize, jgsett_.helphudfontweight );

    painter->setFont( font );



    if( num_==0 )
    {
        painter->drawText( jgsett_.helptextrect, jhelpm_.htexli.at( num_ )  );
    }
    else
    {
        painter->drawText( jgsett_.shorttextrect, jhelpm_.htexli.at( num_ )  );

    }

}


helphudsh::helphudsh(QList<QPixmap> &qlipxmap, gsvar &jgsvar, gsett jgset, QGraphicsScene *scene )
    : QGraphicsItem(0)  /*, currentFrame(0), vx(0), vy(0)*/
{
    currentFrame=0;

    for (int i = 0; i < qlipxmap.size(); ++i) {
        QPixmap pixmap = qlipxmap.at(i);
        Frame frame;
        frame.pixmap = pixmap;
        frame.shape = QPainterPath();
        frame.boundingRect = pixmap.rect();
        frames << frame;
    }
    setZValue(11000);
    scene->addItem(this);
    jgv_=jgsvar;
    jgsett_=jgset;
    hcol_=QColor( jgset.shelphudtextr,  jgset.shelphudtextg, jgset.shelphudtextb, jgset.shelphudtexta );
    msgcou_=0;
    mpla_=0;
    mpla2_=0;
    int ite;
    for( ite=0 ; ite<jgsett_.helphudshorttextcount ; ite++ )
    {
        jmesn_.mes=0;
        jmesn_.tcou=0;

        jmesnvec_.push_back( jmesn_ );
        meslist jme;
        jme.tcou=0;
        meslistvec_.push_back( jme );
    }
    colgoalre_=0;
    retec_=0;

}

void helphudsh::setFrame(int frame)
{
    if (!frames.isEmpty()) {
        prepareGeometryChange();
        currentFrame = frame % frames.size();
    }

}

void helphudsh::advance( int phase )
{
    if (phase == 1)
    {

        jtr.reset();

        jtr.rotate( 0-jgv_.viewangle );

        jtr.scale( 1/jgv_.zoom, 1/jgv_.zoom );

        setTransform( jtr );
        setPos( jgv_.vix, jgv_.viy  );


    }

}
void helphudsh::proch(  )
{
    uint iteh;

    for( iteh=0 ; iteh<meslistvec_.size() ; iteh++ )
    {
        meslistvec_.at( iteh ).tcou++;
    }
}


QRectF helphudsh::boundingRect() const
{
    int brs=2000;
    QRectF neli( brs/-2, brs/-2 , brs, brs ) ;
    return neli;

}


void helphudsh::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{

    int ite, ite2;
    painter->setPen( hcol_ );

    //   QTextCodec::setCodecForCStrings (QTextCodec::codecForName("UTF-8"));
    string vel;



    QFont font( jgsett_.helphudshortfontname, jgsett_.helphudshortfontsize, jgsett_.helphudshortfontweight );

    painter->setFont( font );
    painter->drawText( jgsett_.shorttextrect, "-" );

    QString tex, qsnum;
    int mesint=0, elev=0;
    ite=mpla2_-1;
    ite2=0;
    int jmsi=meslistvec_.size();
    QRectF  trec= jgsett_.shorttextrect;

    while(  1  )
    {

        if( ite>=jmsi  )
        {
            ite=0;
        }
        if( ite<0 )
        {
            ite=jmsi-1;

        }


        qsnum=" ser=%1 ite=%2 mpla_=%3 ite2=%4 t";

        int  itec;

        for( itec=0 ; itec< meslistvec_.at( ite ).mli.size() ; itec++ )
        {

            mesint=meslistvec_.at( ite ).mli.at( itec ).mes ;
            if( mesint>0 and  mesint<jhelpm_.htexli.size() and (
                        meslistvec_.at( ite ).tcou < jgsett_.shortmsgcoulim  or
                        ( mesint==7 and meslistvec_.at( ite ).tcou < jgsett_.win_message_count ) )  )
            {
                QColor vcol=hcol_;
                vcol.setAlpha( ( vcol.alpha() )/( float( ite2+2.0 )*0.5 )  );
                painter->setPen( vcol );

                tex.clear();

                tex= jhelpm_.htexli.at( mesint );
                if( meslistvec_.at( ite ).mli.at( itec ).distance>0  )
                {
                    tex+=QString(" %1 " ).arg( meslistvec_.at( ite ).mli.at( itec ).distance  );
                }
                if( mesint==6 )
                {
                    tex+="  Get "+QString::number( jgsett_.collectgoal )+ " berries as fast as possible ";
                }
                if( mesint==7 )
                {
                    if( colgoalre_==0 )
                    {
                        retec_=  jgv_.tec ;
                        colgoalre_=1;
                    }
                    tex+=" " +QString::number( jgsett_.collectgoal )+" reached in "+ QString::number( retec_ )+" cycles";

                }


                painter->drawText( trec, tex  );
                elev++;

                if( itec==( meslistvec_.at( ite ).mli.size()-1 ) )
                {
                    elev++;
                }
                trec.moveTop( jgsett_.shorttextrect.top()+(  elev*-30 )  );

            }

        }

        ite2++;
        ite--;
        if( ite>=jmsi )
        {
            ite=0;

        }

        if( ite<0 )
        {
            ite=jmsi-1;

        }

        if( ite2>=jmsi )
        {
            ite2=0;
            break;
        }
    }





}
