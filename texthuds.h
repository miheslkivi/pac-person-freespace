
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


#ifndef TEXTHUDS_H
#define TEXTHUDS_H
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
#include"messages.h"
#include<sstream>
using namespace std;



class hudtt : public QGraphicsItem
{
public:
    hudtt(QList<QPixmap> &qlipxmap, gsvar &jgsvar, QGraphicsScene *scene = 0);

    void setFrame(int frame);
    inline int frame() const                        { return currentFrame; }
    inline int frameCount() const                   { return frames.size(); }
    inline QPixmap image(int frame) const           { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
    inline void setVelocity( qreal xvel, qreal yvel) { vx = xvel; vy = yvel; }
    inline qreal xVelocity() const                  { return vx; }
    inline qreal yVelocity() const                  { return vy; }

    QRectF boundingRect() const;
   // QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    qreal vx, vy;
void setgsvar( gsvar jg ) { jgv_=jg;   }
void setgsett( gsett jg ) { jgsett_=jg;   }

private:
    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };
gsvar jgv_;
gsett jgsett_ ;
    int currentFrame;
    QList<Frame> frames;
    QTransform jtr;
};

class helphud : public QGraphicsItem
{
public:
    helphud(QList<QPixmap> &qlipxmap, gsvar &jgsvar, gsett jgset, QGraphicsScene *scene = 0);

    void setFrame(int frame);
    inline int frame() const                        { return currentFrame; }
    inline int frameCount() const                   { return frames.size(); }
    inline QPixmap image(int frame) const           { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
    inline void setVelocity( qreal xvel, qreal yvel) { vx = xvel; vy = yvel; }
    inline qreal xVelocity() const                  { return vx; }
    inline qreal yVelocity() const                  { return vy; }

    QRectF boundingRect() const;
   // QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    qreal vx, vy;
void sethelpmes( helpmes hm, int num ) { jhelpm_=hm;  num_=num; }
void setgsett( gsett jg ) { jgsett_=jg;   }
void setgsvar( gsvar jg ) { jgv_=jg;   }
void sethcolor( QColor hcol  )  { hcol_=hcol; }

private:
    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };
gsvar jgv_;
gsett jgsett_ ;
helpmes jhelpm_;
    int currentFrame, num_;
    QList<Frame> frames;
    QTransform jtr;
    QColor hcol_;
};






//shshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshshsh

class helphudsh : public QGraphicsItem
{
public:
    helphudsh(QList<QPixmap> &qlipxmap, gsvar &jgsvar, gsett jgset, QGraphicsScene *scene = 0);

    void setFrame(int frame);
    inline int frame() const                        { return currentFrame; }
    inline int frameCount() const                   { return frames.size(); }
    inline QPixmap image(int frame) const           { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
    inline void setVelocity( qreal xvel, qreal yvel) { vx = xvel; vy = yvel; }
    inline qreal xVelocity() const                  { return vx; }
    inline qreal yVelocity() const                  { return vy; }

    QRectF boundingRect() const;
   // QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    qreal vx, vy;


void sethelpmes( helpmes hm, int num )
{
    msgcou_++;

    jhelpm_=hm;
    jmesn_.mes=num;
    jmesn_.tcou=0;
    jmesn_.sernum=msgcou_;


/*if( mpla_< jmesnvec_.size()-1 and mset_ )
{
mpla_++;
 }*/

/*if( jmesn_.mes>=0 and jmesn_.mes<jhelpm_.htexli.size() )
{
    jmesnvec_.at( mpla_ )= jmesn_;
    if( mpla_>= jmesnvec_.size()-1  )
    {
    mpla_=0;
    //mset_=0;
     }
    else
    {
        mpla_++;
    }

}
*/
/*
if( mpla_< 0 )
{
mpla_=jmesnvec_.size()-1;

}
*/


}

void sethelpmes2( gsvar &gsv  )
{
    msgcou_++;
int ite, meslsize;
jmesl_.mli.clear();
for( ite=0; ite<gsv.shortmsglist.size() ; ite++)
{
    mnu jmnu;
  mesnum jmesnum=gsv.shortmsglist.at( ite );

  jmnu.distance=jmesnum.distance;
            jmnu.mes=jmesnum.mes;
jmnu.tcoun=jmesnum.tcoun;
   jmesl_.mli.append( jmnu );
}
jmesl_.tcou=0;
gsv.shortmsglist.clear();

meslistvec_.at( mpla2_ )=jmesl_;

meslsize=meslistvec_.size();

if( mpla2_>= meslsize-1  )
    {
    mpla2_=0;

     }
    else
    {
        mpla2_++;
    }




}

void proch();

void setgsett( gsett jg ) { jgsett_=jg;   }
void setgsvar( gsvar jg ) { jgv_=jg;   }
void sethcolor( QColor hcol  )  { hcol_=hcol; }

private:
    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };




gsvar jgv_;
gsett jgsett_ ;
helpmes jhelpm_;
    int currentFrame, /*num_,*/ mpla_, mpla2_;
    QList<Frame> frames;
    QTransform jtr;
    QColor hcol_;
    mesnum jmesn_;
    QList<mesnum> numli_;
    vector<mesnum> jmesnvec_;

QList<int> tur_;
int msgcou_;

//bool mset_;
meslist jmesl_;
vector<meslist> meslistvec_;

};




#endif // TEXTHUDS_H
