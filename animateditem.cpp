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





#include "animateditem.h"
#include "messages.h"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>
#include <QGraphicsScene>

#include <cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>
#include <QTextCodec>
using namespace std;


AnimatedPixmapItem::AnimatedPixmapItem( const QList<QPixmap> &animation, QGraphicsScene *scene )
    : QGraphicsItem(0),/* currentFrame(0),*/ velx_(0), vely_(0),  rax(1), ray(1), raul(2)
{
  currentFrame=0;
    for (int i = 0; i < animation.size(); ++i) {
        QPixmap pixmap = animation.at(i);
        Frame frame;
        frame.pixmap = pixmap;
        frame.shape = QPainterPath();
        frame.boundingRect = pixmap.rect();
        frames << frame;
    }

    scene->addItem(this);
}

void AnimatedPixmapItem::setFrame(int frame)
{

    if (!frames.isEmpty()) {
        prepareGeometryChange();
        currentFrame = frame % frames.size();
    }

    //scene->addItem(this);
}

void AnimatedPixmapItem::advance(int phase)
{
    if (phase == 1)
    {
        moveBy(velx_ , vely_ );
    }


}

QRectF AnimatedPixmapItem::boundingRect() const
{
    return frames.at(currentFrame).boundingRect;


}

QPainterPath AnimatedPixmapItem::shape() const
{
    const Frame &f = frames.at(currentFrame);
    if (f.shape.isEmpty()) {
        QPainterPath path;
        path.addRegion( f.pixmap.createHeuristicMask());
        const_cast<Frame &>(f).shape = path;
    }
    return f.shape;
}

void AnimatedPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
                               QWidget * /*widget*/)
{
    painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap );




}



//*************************************************************************************

pacdirline::pacdirline(QGraphicsScene *scene): QGraphicsItem(0) /*, currentFrame(0)*/, vx(0), vy(0)
{

    scene->addItem( this );

    siir_=150;
}


void pacdirline::setFrame( )
{
        prepareGeometryChange();
}

void pacdirline::advance(int phase)
{
    if (phase == 1)
    {
//         moveBy(vx , vy );




    }

}

QRectF pacdirline::boundingRect() const
{
   QRectF neli(-1440, -1110, 1400, 1500 ) ;
    return neli;
}




void pacdirline::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/  ,    QWidget * /*widget */)
{


painter->setPen( vari );
double xtu, ytu;

    anglelinepac(  kulmr  , siir_, xtu, ytu  );
    painter->drawLine( siir_, siir_, siir_+xtu, siir_+ytu );







}

//**********************************

velmismeter::velmismeter( QGraphicsScene *scene  ): QGraphicsItem(0) /*, vx(0), vy(0)*/
{
    scene->addItem( this );

ympy_=1;

}


void velmismeter::setFrame( )
{
        prepareGeometryChange();
}

void velmismeter::advance(int phase)
{
    if (phase == 1)
    {

    }

}

QRectF velmismeter::boundingRect() const
{
   QRectF neli(-1440, -1110, 1400, 1500 )  ;
    return neli;
}


void velmismeter::takespeed( double shipDx, double shipDy, double speed, int ympy  )
{
    nopx=shipDx;
    nopy=shipDy;
    spe=speed;
ympy_=ympy;

}

void velmismeter::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/  ,    QWidget * /*widget */)
{
    int ite;

painter->setPen( vari );
double xtu=0, ytu=0, vpit=0, xtu2=0, ytu2=0;


if(ympy_>0)
{
    for( ite=0 ; ite< 360 ; ite+=1 )
    {
        vpit=7.0*distancepac( 0, 0, nopx+( cos( degrad( ite )  )*spe ),  nopy+ ( sin( degrad( ite ) )*spe )  );
        if(ympy_==1)
        {
            anglelinepac( atan2( nopy+ ( sin( degrad( ite ) )*spe ),  nopx+( cos( degrad( ite )  )*spe )     ), vpit, xtu, ytu  );
            anglelinepac( atan2( nopy+ ( sin( degrad( ite ) )*spe ),  nopx+( cos( degrad( ite )  )*spe )     ), vpit*1.5, xtu2, ytu2  );
        }
        if(ympy_==2)
        {
            anglelinepac(  degrad( ite )   , vpit, xtu, ytu  );
            anglelinepac(  degrad( ite )   , vpit*1.5, xtu2, ytu2  );
        }

        //painter->drawLine(0, 0, xtu, ytu );

        painter->drawPoint( 300+xtu, 300+ytu );
        painter->drawPoint( 300+xtu2, 300+ytu2 );

    }
}



}







