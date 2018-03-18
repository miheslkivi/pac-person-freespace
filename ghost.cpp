
/*
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
*
*
*
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

#include "animateditem.h"
#include "gmu.h"
#include "ghost.h"
#include"texthuds.h"


#include <cstdlib>

#include<cmath>

#include<iostream>

ghost::ghost ( const QList<QPixmap> &pic,  QGraphicsScene *c, gsvar gva, float xpos, float ypos ): AnimatedPixmapItem( pic, c )
{
    myAge = 0;
    mislas=random()%360;
    behavior_=gva.vika;
    fiwid_=c->width();
    fihei_=c->height();
    state_=2;
    spom_=0;

    tt_=-1;
    ncou_=0;
    pichei_=pic.at(0).height()/2;


    setVelocity(0,0);
    setTransformOriginPoint( pichei_, pichei_ );
    rotco_=0;
    setPos( xpos, ypos );

    lgposx_=xpos;
    lgposy_=ypos;

    int iter;

    vikohli_=11;
    for(iter=0; iter<vikohli_; iter++ )
    {
        vive_.push_back( QPoint(-500,-500) );

    }

    vikoh_=0;
    harhcou_=0;
    pako_=0;

    avgspeedtt_=1;
    jvast_.paicol=0;
    jvast_.xpa=-115;
    jvast_.ypa=-114;

    jkys_.xqcol=-211;
    jkys_.yqcol=-311;
    beh3_=0;
    posx_=x();
    posy_=y();
    advex_=0;
    advey_=0;
    agett_=0;
    pyco_=0;
    sta2op_=0.8;
    setOpacity( sta2op_ );


}


void ghost::advance( int phase )
{

    if ( phase == 1 )
    {
        if(state_!=1 )
        {
            setRotation( 0-jcgsvar_.viewangle );
        }
        else
        {
            setRotation( (agett_*10)-jcgsvar_.viewangle );
            pyco_--;
            if( pyco_<0 )
            {
                state_=2;
                setOpacity( sta2op_ );
            }
        }
        setPos( posx_+advex_, posy_+advey_  );

    }

}


void ghost::laske( QImage &kuva )
{
    posx_=x();
    posy_=y();
    advex_=0;
    advey_=0;
    agett_++;

    if( state_==2 )
    {

        int iter;

        rotco_+=19;

        pac_.lkxpo=pac_.xpo;
        pac_.lkypo=pac_.ypo;


        for( iter=0; iter<vikohli_; iter++ )
        {
            if( vive_.at( iter )==QPoint( x(), y()  ) )
            {
                mislas= random()%360 ;

                behavior_=1;
                harhcou_=40;
                break;
            }
        }

        vive_.at( vikoh_ )=QPoint( x(), y() );



        vikoh_++;
        if( vikoh_>=vikohli_ )
        {
            vikoh_=0;

        }

        if( pac_.spot )
        {
            if( jcgsvar_.ghattack>=1 )
            {
                behavior_=0 ;
            }
            if( jcgsvar_.ghattack==0 )
            {
                behavior_=4;
            }
            if( jcgsvar_.ghattack<0 or jcgsvar_.ghattack>2 )
            {
                cout << " ghost.cpp: jcgsvar_.ghattack<0 or jcgsvar_.ghattack>2 " << endl;
                exit(-1);


            }

            ncou_=0;
            if(harhcou_>0)
            {
                behavior_=1;
                harhcou_--;
            }


        }
        else
        {
            harhcou_=0;

            if( behavior_==0 and /*ncou_< 500*/  jcgsvar_.tec-pac_.tecounter_of_info<600 and
                    distancepac( x() + pichei_, y()+ pichei_, pac_.lkxpo, pac_.lkypo)>20 )
            {
                behavior_=0;
                ncou_++;
            }
            else
            {
                behavior_=1;
                ncou_=0;
            }
            if( distancepac( x() + pichei_, y()+ pichei_, pac_.lkxpo, pac_.lkypo)<20 )
            {
                behavior_=1;
                ncou_=0;
                mislas=raddeg( pacbe_ ) ;
            }

        }
        if( jcgsvar_.paclives==0 )
        {
            behavior_=1;
            pac_.lives=0;
            pac_.spot=0;
            pac_.lkxpo=0;
            pac_.lkypo=0;
            pac_.xpo=0;
            pac_.ypo=0;
            beh3_=0;
        }

        if( pako_>0 and behavior_!=3 )
        {
            behavior_=2;

        }
        if( random()%( odds_of_random_shaking_ +500 )==0 and beh3_<=0 )
        {
            behavior_=3;
            beh3_=5;
        }
        if( behavior_==1 and  random()%odds_of_random_shaking_==0 and beh3_<=0 )
        {
            behavior_=3;
            beh3_=15+( random()%100 );

        }

        if( beh3_>0)
        {
            behavior_=3;
        }
        jkys_.xqcol=x()+pichei_;
        jkys_.yqcol=y()+pichei_;


        if( behavior_==0 )
        {


            pacbe_=atan2( pac_.lkypo-(  y()+ pichei_ )  ,  pac_.lkxpo-( x() + pichei_ )  );
            anglelinepac( pacbe_, jgset_.avgspeedmin+jgset_.ghost_pursuit_extra_speed+avgspeedtt_+( float( random()%400 )/200.0 ), xplu, yplu  );
            advex_=velx_+xplu;
            advey_=vely_+yplu;


        }
        else
        {


            if( behavior_==1 )
            {
                if( random()%odds_of_dir_change_==0 )
                {
                    tt_=( ( ( random()%2 )*2 )-1 );
                }
                anglelinepac( degrad( mislas%360 ), jgset_.avgspeedmin+avgspeedtt_+( float( random()%400 )/200.0 ), xplu, yplu  );

                advex_=xplu  ;
                advey_=yplu  ;

                mislas+=( double( ( random()%20 )+ jgset_.avgrotasmin+avgrotastt_ ) / 10.9 )*tt_;

            }
            if( behavior_==2  )
            {
                anglelinepac( degrad( mislas%360 ), 2+( float( random()%400 )/200.0 ), xplu, yplu  );
                advex_=xplu  ;
                advey_=yplu  ;
                tt_=( ( ( random()%2 )*2 )-1 );
                mislas+=( double( ( random()%20 )+50 ) / 10.9 )*tt_;

                pako_--;


            }
            if( behavior_==3 )
            {

                if( jvast_.paicol==jgset_.meadowc.rgb()  )
                {
                    posx_=jvast_.xpa-pichei_;
                    posy_=jvast_.ypa-pichei_;
                }

                xplu=0;
                yplu=0;
                anglelinepac( degrad( random()%360 ), avgspeedtt_+( float( random()%300 )/200.0 ), xplu, yplu  );
                jkys_.xqcol=x()+pichei_+xplu;
                jkys_.yqcol=y()+pichei_+yplu;
                if( 1 )
                {

                    if(  kuva.pixel( jkys_.xqcol, jkys_.yqcol )==jgset_.meadowc.rgb() )
                    {
                        posx_=jkys_.xqcol-pichei_;
                        posy_=jkys_.yqcol-pichei_;

                    }
                }
                advex_=0;
                advey_=0;
                beh3_--;
            }
            if( behavior_==4 )
            {
                pacbe_=atan2( pac_.lkypo-(  y()+ pichei_ )  ,  pac_.lkxpo-( x() + pichei_ )  );
                anglelinepac( degrad( raddeg( pacbe_ )+( random()%40 )+160 ) , 4+( float( random()%400 )/200.0 ), xplu, yplu  );
                advex_=velx_+xplu;
                advey_=vely_+yplu;


            }

        }


        if( !golg_ )
        {
            lgposx_=x()+pichei_;
            lgposy_=y()+pichei_;

        }
        else
        {
            mislas+= 180+( ( random()%90 )-45 ) ;
            posx_=lgposx_-pichei_;
            posy_=lgposy_-pichei_;
            advex_=0;
            advey_=0;

            golg_=0;
        }
    }
    else
    {
        if(state_==0)
        {
            setOpacity(0.3);
        }
        if(state_==1)
        {
            setOpacity(0.7);
        }
    }

}



void ghost::tooclose( float xx1, float yy1 )
{
    float suunrad=atan2( y()-yy1, x()-xx1 );
    mislas=( raddeg( suunrad  )+( random()%90 ) )-45 ;
    if( distancepac( xx1, yy1, x(), y()  )<10   )
    {
        behavior_=3;
        moveBy( ( ( random()%2000 )/1000 )-1.0, ( ( random()%2000 )/1000 )-1.0    );

    }
    else
    {
        behavior_=2;
    }
    pako_=20;

}
void ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
                  QWidget * /*widget*/)
{
    //  painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap );
    painter->drawPixmap(0, 0, frames.at( pic_type_ ).pixmap );


    /*   painter->setPen( Qt::white );
painter->drawPoint( 10, 10 );
painter->setPen( Qt::red );
painter->drawPoint( jgset_.ghosthawidth, jgset_.ghosthawidth );

*/


}

aavehq::aavehq(  )
{    
    ghpacetclo_=99999999999;

}



void aavehq::prghv(vector<ghost*> &ghv, QImage &taus, gsvar &jgsv,
                   QList<KMissile*> &missiles, vector<boom*> &bve, QList <minett*> &minelis,
                   float pacxpai, float pacypai, int pkim )
{
    unsigned int iteru;
    int iter2s;
    double et;
    mesnum jmesn;

    ghpacetclo_=999999999;
    int spotcou=0, nonspotcou=0;

    for( iter2s=0 ; iter2s<minelis.size() ; iter2s++ )
    {
        minelis.at( iter2s )->setspotsgh(0);
        minelis.at( iter2s )->setspotsghlios(0);

    }
    for( iteru=0; iteru<ghv.size(); iteru++ )
    {
        ghv.at( iteru )-> setspottedbymine(0);
        ghv.at( iteru )-> setspottedbyminelios(0);

    }

    jgsv.norghostcount=0;
    jgsv.spinghostcount=0;
    for( iteru=0; iteru<ghv.size(); iteru++ )
    {

        if( ghv.at( iteru )->state()==2  )
        {
            jgsv.norghostcount++;
        }
        if( ghv.at( iteru )->state()==1  )
        {
            jgsv.spinghostcount++;
        }


        double ghpacet=distancepac( ghv.at( iteru )->x()+jgset_.ghosthawidth, ghv.at( iteru )->y()+jgset_.ghosthawidth,
                                    pacxpai, pacypai      );
        ghv.at( iteru )->setpacdistance( ghpacet );

        if( ghpacet < ghpacetclo_ and ghv.at( iteru )->state()!=0 )
        {
            ghpacetclo_  = ghpacet;
        }
        if( jgset_.closestknowable==2 )
        {
            if( ghpacetclo_< jgset_.ghostclosestmeasurementdistance or jgset_.ghostclosestmeasurementdistance_on==0 )
            {
                jgsv.ghpacetclo=prec( ghpacetclo_, jgsv.ghcloseprecision ) ;
            }
            else
            {
                jgsv.ghpacetclo= jgset_.ghostclosestmeasurementdistance+1.1111;

            }

        }
        if( jgset_.closestknowable==1 )
        {
            if( ghpacetclo_> jgset_.ghostwarndist  )
            {
                jgsv.ghpacetclo=jgset_.ghostwarndist+1.1111;
            }
            else
            {
                jgsv.ghpacetclo=jgset_.ghostwarndist-1.1111;

            }

        }

        if( jgset_.closestknowable==0 )
        {
            jgsv.ghpacetclo=-1;

        }

        if( ghpacet< jgset_.ghostrange and ghv.at( iteru )->state()!=0 )
        {
            jgsv.paclives=0;
            jgsv.reason=2;
            pkim=1;

        }


        for( iter2s=0 ; iter2s<missiles.size() ; iter2s++ )
        {
            double etaimg=distancepac( ghv.at( iteru )->x()+jgset_.ghosthawidth, ghv.at( iteru )->y()+jgset_.ghosthawidth,
                                       missiles.at( iter2s )->x(), missiles.at( iter2s )->y()  );
            if (  etaimg < jgset_.mistriggerrange and ghv.at( iteru )->state()!=0 )
            {


                missiles.at( iter2s )-> setexpl(1);

            }


        }
        uint iter2u;
        for( iter2u=0 ; iter2u<bve.size() ; iter2u++ )
        {
            double etaimg=distancepac( ghv.at( iteru )->x()+jgset_.ghosthawidth, ghv.at( iteru )->y()+jgset_.ghosthawidth,
                                       bve.at( iter2u )->x(), bve.at( iter2u )->y()  );
            if( bve.at( iter2u )->age()<2 and etaimg <  jgset_.explspinrange and
                    etaimg>jgset_.explrange and ghv.at( iteru )->state()==2 )
            {
                ghv.at( iteru )->setstate(1)   ;
                ghv.at( iteru )->setpyco( jgset_.ghostspintime );
                jgsv.shortmsg=2;
                jgsv.shortmsgcou=0;
                jmesn.distance=ghpacet;
                jmesn.mes=2;
                jmesn.tcou=0;
                jmesn.tcoun=jgsv.tec;
                jmesn.sernum=ghv.at( iteru )->sernumber();
                jgsv.shortmsglist.append( jmesn );

            }
            if( bve.at( iter2u )->age()<2 and etaimg <  jgset_.explrange  and ghv.at( iteru )->state()!=0 )
            {
                ghv.at( iteru )->setstate(0)   ;
                jgsv.shortmsg=1;
                jmesn.distance=ghpacet;
                jmesn.mes=1;
                jmesn.tcou=0;
                jmesn.tcoun=jgsv.tec;
                jmesn.sernum=ghv.at( iteru )->sernumber();
                jgsv.shortmsglist.append( jmesn );

                jgsv.shortmsgcou=0;
                ghv.at( iteru )->setZValue( -50 );
            }

        }
        float ghx=ghv.at( iteru )->x()+jgset_.ghosthawidth;
        float ghy=ghv.at( iteru )->y()+jgset_.ghosthawidth;
        for( iter2s=0 ; iter2s<minelis.size() ; iter2s++ )
        {
            float minex=minelis.at( iter2s )->x()+jgset_.minehawidth;
            float miney=minelis.at( iter2s )->y()+jgset_.minehawidth;

            double etaimg=distancepac( ghx, ghy, minex, miney  );
            if( etaimg < jgset_.minetriggerrange and ghv.at( iteru )->state()==2 and minelis.at( iter2s )->wai()==1 )
            {
                minelis.at( iter2s )-> setexpl(1);
            }
            if( etaimg < jgset_.minespotrange and ghv.at( iteru )->state()!=0  )
            {
                ghv.at( iteru )-> setspottedbymine(1);
                minelis.at( iter2s )->setspotsgh(1);
                spotcou++;
            }
            else
            {
                nonspotcou++;
            }
            if( etaimg < jgset_.minesliosspotrange and jgset_.mineslios==1 and ghv.at( iteru )->state()!=0  )
            {
                int mghlios=lios( taus , minex, miney, ghx, ghy, jgset_.hillc.rgb()  );
                if( mghlios==0  )
                {
                    ghv.at( iteru )-> setspottedbyminelios(1);
                    minelis.at( iter2s )->setspotsghlios(1);
                }

            }
            else
            {

            }

        }
        paci_.spot=0;
        paci_.xpo=-124;
        paci_.ypo=-125;
        paci_.lkxpo=-123;
        paci_.lkypo=-123;
        int liht=-1;
        //    bool vis=1;
        if( ( ( ghpacet<jgset_.ghostdetectiondistance or jgset_.ghostdetectiondistance_on==0 )
              or ( ghpacet<jgset_.pacdetectiondistance or jgset_.pacdetectiondistance_on==0 ) )
                and ghv.at( iteru )->state()!=0 and !pkim  )
        {

            // liht=lios( taus , pacxpai, pacypai, ghv.at( iteru )->x()+pichei2, ghv.at( iteru )->y()+pichei2  );
            liht=lios( taus , pacxpai, pacypai, ghx, ghy, jgset_.hillc.rgb()  );


        }
        else
        {
            liht=1;
        }
        if(  !pkim and ghv.at( iteru )->state()!=0 and jgsv.ghinv
             and ( jgset_.minesreportghlocation==0 or ghv.at( iteru )->spotmine()==0 )
             and ghv.at( iteru )->spotminelios()==0  and
             ( liht>0 or ( ghpacet>jgset_.ghostdetectiondistance and jgset_.ghostdetectiondistance_on ) )   )
        {
            ghv.at( iteru )->hide();
            //  vis=0;

        }
        else
        {
            ghv.at( iteru )->show();
            //vis=1;
            if( ghv.at( iteru )->state()!=0 )
            {
                jgsv.spottednum++;
                jgsv.spotted=1; jgsv.spotted_c=1;
                if( liht==0 and  ( ghpacet<jgset_.ghostdetectiondistance or jgset_.ghostdetectiondistance_on==0 ) )
                {
                    jgsv.spotted_lios++;

                }
            }

        }
        /*     if( ghv.at( iteru )->spotmine()==1  )
        {
            //ghv.at( iteru )->show();
            vis=1;
        }
        ghv.at( iteru )->setVisible( vis );
*/

        if( liht==0  and  !pkim and ghv.at( iteru )->state()!=0 and
                ( ghpacet<jgset_.pacdetectiondistance or jgset_.pacdetectiondistance_on==0 )  )
        {
            if( jgset_.spottedbyghostknowable==1 /*or ghpacet< jgset_.ghostdetectiondistance or
                                            ghv.at( iteru )->spotmine()==1 or ghv.at( iteru )->spotminelios()==1*/ or
                    ghv.at( iteru )->isVisible() )
            {
                jgsv.spottedby++;
            }
            else
            {
                //    jgsv.spottedby=-1234;
            }

            paci_.xpo=pacxpai;
            paci_.ypo=pacypai;
            paci_.spot=1;
            paci_.lives=1;
            paci_.lkxpo=pacxpai;
            paci_.lkypo=pacypai;
            paci_.tecounter_of_info=jgsv.tec;
            ghv.at( iteru )->setpacinfo( paci_ ) ;

            //   slvec.at( iteru ).vii=QLine( pacxpai, pacypai, ghv.at( iteru )->x()+pichei2, ghv.at( iteru )->y()+pichei2 );
            // slvec.at( iter ).nak=0;
            sightline vsl;
            // vsl.vii=QLine( pacxpai, pacypai, ghv.at( iteru )->x()+pichei2, ghv.at( iteru )->y()+pichei2 );
            vsl.vii=QLine( pacxpai, pacypai, ghx, ghy );
            if( ghv.at( iteru )->isVisible() )
            {
                vsl.nak=0;
            }
            else
            {
                vsl.nak=2;


            }

            ghv.at( iteru )->setsline( vsl );
        }
        else
        {
            if( ghv.at( iteru )->state()!=0 )
            {
                //slvec.at( iteru ).nak=1;
                //            ghv.at( iteru )->sline()->nak=1;
                ghv.at( iteru )->setslinenak(1);
            }
            else
            {

                ghv.at( iteru )->setslinenak(2);

            }
            if( ghv.at( iteru )->beha()!=0 )
            {

                ghv.at( iteru )->setslinenak(2);

            }

            paci_.spot=0;
            ghv.at( iteru )->setpacspot(0);
            if( pkim)
            {
                paci_.lives=0;

            }
            //ghv.at( iteru )->setpacinfo( paci_ ) ;

        }
        if( !pkim and liht==0 and ghv.at( iteru )->isVisible() and ghv.at( iteru )->state()!=0 and paci_.spot==0 )
        {
            sightline vsl;
            vsl.vii=QLine( pacxpai, pacypai, ghx, ghy );
            vsl.nak=3;
            ghv.at( iteru )->setsline( vsl );

        }
        else
        {
            if(  !pkim and ghv.at( iteru )->isVisible() and ghv.at( iteru )->state()!=0 and paci_.spot==0  )
            {
                if( lios( taus , pacxpai, pacypai, ghx, ghy, jgset_.hillc.rgb()  )==0 )
                {
                    sightline vsl;
                    vsl.vii=QLine( pacxpai, pacypai, ghx, ghy );
                    vsl.nak=4;
                    ghv.at( iteru )->setsline( vsl );

                }

            }


        }



        ghv.at( iteru )->setgsvar( jgsv, jgset_ );
        QRect rajat( taus.rect()  );

        ghqanswer vastaus;
        ghqquestion  kys=ghv.at( iteru )->askghq();
        QPoint ehpa( kys.xqcol, kys.yqcol );
        if( rajat.adjusted(20,20 ,-20 ,-20  ).contains( ehpa ) )
        {
            vastaus.paicol= taus.pixel( ehpa  );
        }
        else
        {
            vastaus.paicol=0;
        }
        vastaus.xpa=kys.xqcol;
        vastaus.ypa=kys.yqcol;


        ghv.at( iteru )->getanswer( vastaus );



        QPoint aapos ( ghv.at( iteru )->x()+jgset_.ghosthawidth, ghv.at( iteru )->y()+jgset_.ghosthawidth );
        if( taus.pixel( aapos )==jgset_.meadowc.rgb()  /*MEADOW*/  and rajat.adjusted(20,20 ,-20 ,-20  ).contains( aapos )    )

        {
            ghv.at( iteru )->lgposthis(  );
        }



        if( taus.pixel( aapos )!=jgset_.meadowc.rgb() or !rajat.adjusted(20,20 ,-20 ,-20  ).contains( aapos ) )
        {
            ghv.at( iteru )->golgpos();

        }
        else
        {

        }


        ghv.at( iteru )->laske( taus );


        for( iter2u=ghv.size()-1 ; iter2u>iteru; iter2u-- )
        {
            if( ghv.at( iteru )->state()==2 and ghv.at( iter2u )->state()==2 )
            {
                et=distancepac( ghv.at( iteru )->x(),  ghv.at( iteru )->y(), ghv.at( iter2u )->x(), ghv.at( iter2u )->y() );
                if( et<30  )
                {
                    ghv.at( iteru ) ->tooclose( ghv.at( iter2u )->x(), ghv.at( iter2u )->y()  ) ;
                    ghv.at( iter2u ) ->tooclose( ghv.at( iteru )->x(), ghv.at( iteru )->y() );

                }
                else
                {


                }
            }
        }


    }

    jgsv.ghostcount=jgsv.norghostcount+jgsv.spinghostcount;

}

void aavehq::setgsvar( gsvar jgv )
{
    jcgsvar_=jgv;

}
void aavehq::setgset( gsett &jgs )
{
    jgset_=jgs;

}
/*
void aavehq::getquestion( ghost &aave )
{


}
void aavehq::giveanswer( ghost &aave )
{

}*/
