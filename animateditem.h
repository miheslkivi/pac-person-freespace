/* Derived from Qt4 example software   "Ported Asteroids"
*
* Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) -  Copyright (C) 2018 by
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




#ifndef ANIMATEDPIXMAPITEM_H
#define ANIMATEDPIXMAPITEM_H

#include <QGraphicsItem>
#include <QColor>
#include <cstdlib>
#include"geome.h"
#include"gmu.h"
#include<sstream>
class AnimatedPixmapItem : public QGraphicsItem
{
public:
    AnimatedPixmapItem(const QList<QPixmap> &animation, QGraphicsScene *scene = 0);

    void setFrame(int frame);
    inline int frame() const                        { return currentFrame; }
    inline int frameCount() const                   { return frames.size(); }
    inline QPixmap image(int frame) const           { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
    inline void setVelocity( qreal xvel, qreal yvel) { velx_ = xvel; vely_ = yvel; }
    void asnop( double nop) { vel=nop; }
    inline qreal xVelocity() const                  { return velx_; }
    inline qreal yVelocity() const                  { return vely_; }

    void otaedex1( double edex, double edey ) { edex1=edex; edey1=edey;     }
    void otaedex2( double edex, double edey ) { edex2=edex; edey2=edey;     }
    void otaedex3( double edex, double edey ) { edex3=edex; edey3=edey;     }

      double anedex1() { return edex1; }
      double anedex2() { return edex2; }
      double anedex3() { return edex3; }

      double anedey1() { return edey1; }
      double anedey2() { return edey2; }
      double anedey3() { return edey3; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    qreal velx_, vely_;
    double vel;
    void otakulm( double kulmrad ) { kulmr=kulmrad; }
    void otaran( int raul2, int rax2, int ray2 ) { raul=raul2; rax=rax2; ray=ray2; }



    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };

    int currentFrame;
    QList<Frame> frames;
private:


    double kulmr;
    double edex1, edey1;
    double edex2, edey2;
    double edex3, edey3;
int rax, ray, raul;

};



class pacdirline : public QGraphicsItem
{
public:
    pacdirline(QGraphicsScene *scene = 0);

   void setFrame( );
 /*   inline int frame() const                        { return currentFrame; }
    inline int frameCount() const                   { return frames.size(); }

    inline QPixmap image(int frame) const           { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
*/
    inline void setVelocity(qreal xvel, qreal yvel) { vx = xvel; vy = yvel; }
    inline qreal xVelocity() const                  { return vx; }
    inline qreal yVelocity() const                  { return vy; }

    void takeangle( double kulmrad ) { kulmr=kulmrad; }
    void otaviiva( bool onk ) { viivao=onk; }

    void otaedex1( double edex, double edey ) { edex1=edex; edey1=edey;     }
    void otaedex2( double edex, double edey ) { edex2=edex; edey2=edey;     }
    void otaedex3( double edex, double edey ) { edex3=edex; edey3=edey;     }

      double anedex1() { return edex1; }
      double anedex2() { return edex2; }
      double anedex3() { return edex3; }

      double anedey1() { return edey1; }
      double anedey2() { return edey2; }
      double anedey3() { return edey3; }

void takecol( QColor vari1 ) { vari=vari1;  }
void otapos( double xt, double yt ) { posx_=xt-siir_; posy_=yt-siir_;  setPos( posx_, posy_ ); }
    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);

private:
  /*  struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };

    int currentFrame;
    QList<Frame> frames;*/
    qreal vx, vy;
    QColor vari;
QPixmap kuva;
double kulmr, posx_, posy_, siir_;

double edex1, edey1;
double edex2, edey2;
double edex3, edey3;


bool viivao;
QVector<QPointF> pis;

};

/*---------------------------------------------*/


class velmismeter : public QGraphicsItem
{
public:
    velmismeter(QGraphicsScene *scene = 0);
    void setFrame( );
    void takecol( QColor vari1 ) { vari=vari1;  }
    QRectF boundingRect() const;
  //  QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    void takespeed( double shipDx, double shipDy, double speed, int ympy  );

private:

  //  qreal vx, vy;
    QColor vari;
QPixmap kuva;
//double kulmr, posx, posy;

double nopx, nopy, spe;

int ympy_;
QVector<QPointF> pisteet;


};



/*ttttttttttttttttttttttttttttttttttttttttttttttt*/



#endif
