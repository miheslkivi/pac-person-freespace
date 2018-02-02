
/*
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by
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





#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsItem>
#include <QColor>
#include <cstdlib>
#include<QGraphicsScene>
#include "animateditem.h"
#include "gmu.h"
#include"lios.h"
#include<QList>
#include "sprites.h"
#include <cstdlib>
#include"texthuds.h"


#include<cmath>

#include<iostream>


class ghost : public AnimatedPixmapItem
{
  //  Q_OBJECT

public:
    ghost (const QList<QPixmap> &pic, QGraphicsScene *c, gsvar gva , float xpos, float ypos);
//        : AnimatedPixmapItem( pic, c );




   //   void growOlder() { myAge++; }
      void setpacinfo(  pacinfo pac ) {  pac_=pac; }
      void setgsvar( gsvar jg, gsett jgs ) {  jcgsvar_=jg;  jgset_=jgs; }
      void setpacspot( int spot ) { pac_.spot=spot; }
      void setsnumber( int sn ) { serialnumber_=sn;
                                  setZValue(10+serialnumber_);
                                  avgspeedtt_=(random()%2000)/1000.0;
                                  avgrotastt_=(random()%2000)/100.0;
agett_=0;

                                }

void setstate( int st ) { state_=st; }
void setspottedbymine( bool spo ) {  spom_=spo; }
void setspottedbyminelios( bool spo ) {  spomlios_=spo; }

bool spotmine() { return spom_; }
bool spotminelios() { return spomlios_; }

void setpyco( int py ) { pyco_=py; }

void setsline( sightline jsl  )
{
    jsl_=jsl;

}
void setslinenak( int nak ) { jsl_.nak=nak; }

sightline sline() { return jsl_; }





int pyco() { return pyco_; }

int state() { return state_; }
      float rotas() { return avgrotastt_; }
      float avspee() { return avgspeedtt_; }

    //  void setlgpos( float xxp, float yyp  ) { lgposx_=xxp; lgposy_=yyp; }
      void lgposthis() { lgposx_=x()+pichei_;  lgposy_=y()+pichei_;   }
//      void golgpos() {  setPos( lgposx_-pichei_, lgposy_-pichei_  ); }
void golgpos() {    golg_=1;  }
      pacinfo reportpacinfo() { return pac_; }
      void advance(int phase);

void tooclose(float xx1, float yy1 );
int opichei( ) { return pichei_; }
ghqquestion askghq() { return jkys_; }
void getanswer( ghqanswer ans ) {  jvast_=ans; }
void laske( QImage &kuva );
int beha() { return behavior_; }
int sernumber() { return serialnumber_; }

void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
float opacdistance() { return pacdistance_; }
void setpacdistance( float dis ) { pacdistance_=dis; }

private:
double advex_, advey_;

    int myAge;
    int mislas;
    double xplu, yplu, /*mx, my, */ pacbe_;
    int behavior_;

    int fiwid_, fihei_;
    int tt_, ncou_;
    pacinfo pac_;
double lgposx_, lgposy_, posx_, posy_;
int pichei_;
int golg_;
int rotco_;
vector<QPoint>  vive_;
int vikoh_, vikohli_, harhcou_, pako_;
gsvar jcgsvar_;
gsett jgset_;
ghqanswer jvast_;
ghqquestion jkys_;
int beh3_;
int serialnumber_, state_, pyco_;
int agett_;
float avgspeedtt_, avgrotastt_, sta2op_;
vector<int> hbtt_;
sightline jsl_;

bool spom_, spomlios_;
float pacdistance_;

};
//gsvar ghost::jcgsvar;






class aavehq
{
public:
    aavehq();
    void prghv(vector<ghost*> &ghv , QImage &taus, gsvar &jgsv,
               QList<KMissile*> &missiles, vector<boom *> &bve, QList<minett *> &minelis, float pacxpai, float pacypai, int pkim);

void setgsvar( gsvar jgv );
void setgset( gsett &jgs );

private:
    gsvar jcgsvar_;
    gsett jgset_;
vector<ghost*> ghv_;
pacinfo paci_;
double ghpacetclo_;
};



#endif // GHOST_H
