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



#ifndef QBARRAYIO_H
#define QBARRAYIO_H
#include <iostream>
#include <string>
#include <QString>
#include <sstream>
#include <qapplication.h>
#include <qnamespace.h>
#include<qbytearray.h>
#include<vector>
#include"gmu.h"
using namespace std;
union charintunion
{
int sint;
float flo;
char merk[4];
};

struct  qplatt
{
    int pla;
    char aat;
    bool bbt;

};
QByteArray qbachar1( char aa1 );


class setdg
{

public:


    void setqplatt( int pla, char aat, bool bbt )
    {
        qplatt traz;
        traz.pla =pla;
        traz.aat=aat;
        traz.bbt=bbt;


        jqp_.push_back( traz );

        //  cout << endl << " setqplatt " << jqp_.size() << "  traz.pla=" << traz.pla << endl;


    }
    void setqba( QByteArray &res )
    {
        vector< QByteArray > chv;
        uint ite;

        QByteArray tht;
        tht.append('t');


        uint jsi=( jqp_.size()*2 );

        for( ite=0 ; ite< jsi; ite++  )
        {
            chv.push_back( tht );
        }

        for( ite=0 ; ite<jqp_.size() ; ite++  )
        {

            int nebra=jqp_.at( ite ).pla*2;
            uint nebrb=nebra+1;

            if(  nebrb>=chv.size() )
            {
                cout << endl << " setqba: ERROR: " << nebrb << "  ite= " << ite
                     <<  " jqp_.size " << jqp_.size() << endl;

            }

            chv.at( nebra )=qbachar1( jqp_.at( ite ).aat )   ;
            chv.at( nebrb )=qbachar1( jqp_.at( ite ).bbt )   ;
        }
        for( ite=0 ; ite<chv.size() ; ite++  )
        {
            res.append( chv.at( ite ) );
        }

        chv.clear();
        jqp_.clear();

    }

    void setdgconst()
    {

        ghatt_pla_=0;
        centervie_pla_=1;
        minecollect_pla_=2;

        sightb_pla_=3;
        minewait_pla_=4;
        spixu_pla_=5 ;
        brake_pla_=6 ;
        splon_pla_=7 ;
        safetyon_pla_=8;
        ksuuntvh_pla_=9;
        asuuntvh_pla_=10;
        lsuuntvh_pla_=11;
        miskoh_pla_=12 ;
        mst_pla_=13 ;
        msmi_pla_=14 ;
        hud_pla_=15;
        asthud_pla_=16;
        isohud_pla_=17 ;
        helptexton_pla_=18 ;
        shortmeson_pla_=19;
        freelo_pla_=20 ;
        sangle_pla_=21 ;
        fullsc_pla_=22 ;
        edgece_pla_=23;

        ympy_pla_=24;
        spotted_pla_=25;

        shortmsg_pla_ =26  ;
        pause_pla_=27  ;
        newgame_pla_=28  ;
        newship_pla_=29  ;
        zoom_plus_pla_=30  ;
        zoom_minus_pla_=31  ;
        reloadconf_pla_=32  ;
        mine_pla_=33  ;
        deton_pla_=34  ;
        clearb_pla_=35  ;
        ppicint_pla_=36  ;
        thrust_pla_=37  ;
        slowthrust_pla_=38  ;
        close_pla_=39  ;
        ghinv_pla_=40  ;
        hcmode_pla_=41  ;
        reason_pla_=42  ;
        paclives_pla_=43  ;
        nofa_pla_=44  ;
        trail_pla_=45  ;
        ghost_mode_pla_=46 ;
        minelay_pla_=47;

        minevisible_pla_=48;
        bervisible_pla_=49;
        enervisible_pla_=50;
        boxvisible_pla_=51;
        bercol_pla_=52;
        enercol_pla_=53;
        boxcol_pla_=54;
        finitefuel_pla_=55;
        explvisible_pla_=56;
        closeboth_pla_=57;


        ener_pla_=58;
        speed_pla_=60;

        mines_pla_=62;
        miss_pla_=64;

        norghostcount_pla_= 66 ;
        spinghostcount_pla_=68  ;
        ghostcount_pla_=70  ;
        ber_pla_=72  ;
        tec_pla_=74  ;
        setcou_pla_=76;
        traffic_collision_velocity_pla_=78  ;
        speed_limiterf_pla_=80  ;

        zoom_pla_=82;
        pac1x1_pla_=84  ;
        pac1y1_pla_=86  ;
        velocitya_pla_=88  ;
        velocityb_pla_ =90  ;


        spottednum_pla_=92;
        spotted_lios_pla_=94;
      spottedby_pla_  =96;
    closest_pla_=98;

    unber_pla_=100;
    mines_out_pla_=102;
    fps_pla_=104;


    }
    int ghatt_pla_, centervie_pla_, minecollect_pla_,
    sightb_pla_,
    minewait_pla_,
    spixu_pla_,
    brake_pla_,
    splon_pla_,
    safetyon_pla_,
    ksuuntvh_pla_,
    asuuntvh_pla_,
    lsuuntvh_pla_,
    miskoh_pla_,
    mst_pla_,
    msmi_pla_,
    hud_pla_,
    asthud_pla_,
    isohud_pla_,
    helptexton_pla_,
    shortmeson_pla_,
    freelo_pla_,
    sangle_pla_,
    fullsc_pla_,
    edgece_pla_, ympy_pla_, spotted_pla_,

    shortmsg_pla_ ,
    pause_pla_,
    newgame_pla_,
    newship_pla_,
    zoom_plus_pla_,
    zoom_minus_pla_,
    reloadconf_pla_,
    mine_pla_,
    deton_pla_,
    clearb_pla_,
    ppicint_pla_,
    thrust_pla_,
    slowthrust_pla_,
    close_pla_,
    ghinv_pla_,
    hcmode_pla_,
    reason_pla_,
    paclives_pla_,
    nofa_pla_,
    trail_pla_,
    ghost_mode_pla_,
    minelay_pla_, minevisible_pla_, bervisible_pla_, enervisible_pla_, boxvisible_pla_, bercol_pla_,
    enercol_pla_, boxcol_pla_, finitefuel_pla_, explvisible_pla_,
    ener_pla_, speed_pla_,

    mines_pla_  , miss_pla_,
    norghostcount_pla_,   spinghostcount_pla_, ghostcount_pla_, ber_pla_, tec_pla_, setcou_pla_,
    traffic_collision_velocity_pla_, speed_limiterf_pla_, zoom_pla_, pac1x1_pla_,  pac1y1_pla_,  velocitya_pla_,
    velocityb_pla_ ,  spottednum_pla_, spotted_lios_pla_,  spottedby_pla_, closest_pla_, unber_pla_,
    mines_out_pla_, fps_pla_, closeboth_pla_;
 ;


private:
    vector< qplatt > jqp_;


};

QByteArray anluq( int sislu);
QByteArray anluqf( float sisluf);
QByteArray anluqbli(int aa, int bb, int cc , int c2, int c3);

QByteArray qbasend(gsvar &aa, gsett &bb  );
charintunion ciuqba( QByteArray  qba );
void ciureceive(gsvar &gsva, gsett &gsetb, QByteArray &qba   );

#endif // QBARRAYIO_H
