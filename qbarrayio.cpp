
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


#include"qbarrayio.h"
#include<vector>
QByteArray qbachar2( char aa1, char bb1 )
{
    QByteArray tul;
    tul.push_back( aa1 );
    tul.push_back( bb1 );
    return tul;
}
QByteArray qbachar1( char aa1 )
{
    QByteArray tul;
    tul.push_back( aa1 );
    return tul;
}

QByteArray anluq( int sislu)
{
    QByteArray tul;
    charintunion sis;
    sis.sint=sislu;
    tul.push_back( sis.merk[0] );
    tul.push_back( sis.merk[1] );
    tul.push_back( sis.merk[2] );
    tul.push_back( sis.merk[3] );


    return tul;
}
QByteArray anluqf( float sisluf)
{
    QByteArray tul;
    charintunion sis;
    sis.flo=sisluf;
    tul.push_back( sis.merk[0] );
    tul.push_back( sis.merk[1] );
    tul.push_back( sis.merk[2] );
    tul.push_back( sis.merk[3] );


    return tul;
}
QByteArray anluqbli( int aa, int bb, int cc, int c2, int c3 )
{
    QByteArray tul;
  //  charintunion sis;
    tul.push_back( aa );
    tul.push_back( bb );
    tul.push_back( cc );
    tul.push_back( c2 );
    tul.push_back( c3 );

    return tul;
}
QByteArray qbachar8( char aa1, char bb1, char aa2, char bb2, char aa3, char bb3, char aa4, char bb4 )
{
    QByteArray tul;
    tul.push_back( aa1 );
    tul.push_back( bb1 );
    tul.push_back( aa2 );
    tul.push_back( bb2 );
    tul.push_back( aa3 );
    tul.push_back( bb3 );
    tul.push_back( aa4 );
    tul.push_back( bb4 );

    return tul;
}

QByteArray qbasend( gsvar &aa, gsett &bb  )
{
    QByteArray res;


    setdg jset;
    jset.setdgconst();
    jset.setqplatt( jset.ghatt_pla_ ,  aa.ghattack,  aa.ghattack_c );

    jset.setqplatt( jset.centervie_pla_,  aa.centervie,  aa.centervie_c);

    jset.setqplatt( jset.minecollect_pla_,  aa.minecollect,  aa.minecollect_c);
    jset.setqplatt( jset.sightb_pla_,  aa.sightb,  aa.sightb_c);
    jset.setqplatt( jset.minewait_pla_,  aa.minewait,  aa.minewait_c);
    jset.setqplatt( jset.spixu_pla_,  aa.spixu,  aa.spixu_c);
    jset.setqplatt( jset.brake_pla_,  aa.brake,  aa.brake_c);
    jset.setqplatt( jset.splon_pla_,  bb.splon,  bb.splon_c);
    jset.setqplatt( jset.safetyon_pla_,   bb.safetyon,  bb.safetyon_c);

    jset.setqplatt( jset.miskoh_pla_,  bb.miskoh,  bb.miskoh_c);
    jset.setqplatt( jset.mst_pla_,  bb.mst,  bb.mst_c);
    jset.setqplatt( jset.msmi_pla_,  bb.msmi,  bb.msmi_c);


    jset.setqplatt( jset.hud_pla_,   bb.hud,  bb.hud_c);
    jset.setqplatt( jset.asthud_pla_,   bb.asthud,  bb.asthud_c);
    jset.setqplatt( jset.isohud_pla_,   bb.isohud,  bb.isohud_c);
    jset.setqplatt( jset.ksuuntvh_pla_,  bb.ksuuntvh,  bb.ksuuntvh_c);
    jset.setqplatt( jset.asuuntvh_pla_,  bb.asuuntvh, bb.asuuntvh_c );
    jset.setqplatt( jset.lsuuntvh_pla_,  bb.lsuuntvh,  bb.lsuuntvh_c);

    jset.setqplatt( jset.helptexton_pla_,  bb.helptexton,  bb.helptexton_c);
    jset.setqplatt( jset.shortmeson_pla_,  bb.shortmeson, bb.shortmeson_c);


    jset.setqplatt( jset.freelo_pla_,  bb.freelo,  bb.freelo_c);
    jset.setqplatt( jset.sangle_pla_,  bb.sangle,  bb.sangle_c);
    jset.setqplatt( jset.fullsc_pla_,  bb.fullsc,  bb.fullsc_c);
    jset.setqplatt( jset.edgece_pla_,  aa.edgece,  aa.edgece_c);

    jset.setqplatt( jset.ympy_pla_,  bb.ympy, bb.ympy_c  );
    jset.setqplatt( jset.spotted_pla_,  aa.spotted,  aa.spotted_c);

    jset.setqplatt(  jset.shortmsg_pla_ ,aa.shortmsg, aa.shortmsg_c);
    jset.setqplatt(  jset.pause_pla_, aa.pause, aa.pause_c);
    jset.setqplatt(  jset.newgame_pla_,aa.newgame, aa.newgame_c);
    jset.setqplatt(   jset.newship_pla_,aa.newship, aa.newship_c);
    jset.setqplatt(   jset.zoom_plus_pla_,aa.zoom_plus,  aa.zoom_plus_c);
    jset.setqplatt(   jset.zoom_minus_pla_, aa.zoom_minus,  aa.zoom_minus_c);
    jset.setqplatt(   jset.reloadconf_pla_, aa.reloadconf,  aa.reloadconf_c);
    jset.setqplatt(   jset.mine_pla_, aa.mine,  aa.mine_c);
    jset.setqplatt(  jset.deton_pla_, aa.deton,  aa.deton_c);
    jset.setqplatt(    jset.clearb_pla_, aa.clearb, aa.clearb_c);
    jset.setqplatt(  jset.ppicint_pla_, bb.ppicint, bb.ppicint_c );
    jset.setqplatt(   jset.thrust_pla_, aa.thrust, aa.thrust_c);
    jset.setqplatt(   jset.slowthrust_pla_, aa.slowthrust, aa.slowthrust_c);
    jset.setqplatt(  jset.close_pla_, aa.close,  aa.close_c);
    jset.setqplatt(   jset.ghinv_pla_, aa.ghinv, aa.ghinv_c);
    jset.setqplatt(   jset.hcmode_pla_, bb.hcmode, aa.hcmode_c);
    jset.setqplatt(    jset.reason_pla_, aa.reason, aa.reason_c);
    jset.setqplatt(   jset.paclives_pla_, aa.paclives, aa.paclives_c);
    jset.setqplatt(   jset.nofa_pla_, aa.nofa, aa.nofa_c);
    jset.setqplatt(   jset.trail_pla_, aa.trail, aa.trail_c);
    jset.setqplatt(   jset.ghost_mode_pla_, bb.ghost_mode, aa.ghost_mode_c);
    jset.setqplatt(   jset.minelay_pla_, aa.minelay, aa.minelay_c );


    jset.setqplatt( jset.minevisible_pla_, aa.minevis, aa.minevis_c );
    jset.setqplatt(   jset.bervisible_pla_, bb.berryvisible, bb.berryvisible_c );
    jset.setqplatt(   jset.enervisible_pla_, bb.enervisible, bb.enervisible_c );
    jset.setqplatt(   jset.boxvisible_pla_, bb.boxvisible, bb.boxvisible_c );

    jset.setqplatt(   jset.bercol_pla_, bb.berrycollect, bb.berrycollect_c );
    jset.setqplatt( jset.enercol_pla_, bb.enercollect, bb.enercollect_c );
    jset.setqplatt(    jset.boxcol_pla_, bb.boxcollect, bb.boxcollect_c );

    jset.setqplatt( jset.finitefuel_pla_, bb.finite_fuel, bb.finite_fuel_c );
    jset.setqplatt( jset.explvisible_pla_, bb.explvisible, bb.explvisible_c );
jset.setqplatt( jset.closeboth_pla_, bb.quitb, bb.quitb_c );

    //  jset.setqplatt(   jset.ener_pla_,

    //               jset.setqplatt(    speed_pla_;

    jset.setqba( res );
    //   cout << endl << " qbarrayio: qbagsvgsett:  " << res.size() << endl;

    res.append( anluqf( aa.fuel   )  );
    res.append( anluqf( aa.velocity   )  );

    res.append( anluq( aa.mines ) );
    res.append( anluq( aa.missiles ) ) ;


    res.append( anluq( aa.norghostcount ) );
    res.append( anluq( aa.spinghostcount ) );


    res.append( anluq( aa.ghostcount ) );
    res.append( anluq( aa.berries_in) );
    res.append( anluq(  aa.tec ) );
    res.append( anluq( aa.setcou) );

    res.append( anluqf( bb.traffic_collision_velocity) );
    res.append( anluqf(  bb.speed_limiterf   ) );
    res.append( anluqf(  aa.zoom  ) );

    res.append( anluqf(aa.vix ) );
    res.append( anluqf( aa.viy    ) );
    res.append( anluqf( aa.norvelocity ) );
    res.append( anluqf( aa.pevelocity) );

    res.append( anluq( aa.spottednum  ) );
    res.append( anluq( aa.spotted_lios  ) );
    res.append( anluq( aa.spottedby  ) );
res.append( anluqf( aa.ghpacetclo ) );
res.append( anluq( aa.berries_meadow ) );
res.append( anluq( aa.minesout )  );
res.append( anluqf( aa.fps )  );



    aa.centervie_c=0;
    aa.minecollect_c=0;

    return res;
}


charintunion ciuqba( QByteArray  qba )
{
    charintunion mru;
    int ite;


    for( ite=0 ; ite<qba.size() ; ite++ )
    {
        mru.merk[ite]=qba.at( ite );
    }

    return mru;
}

void flipnumt( int pla, bool &aa , QByteArray  &qba )
{
    if( qba.at( ( pla*2 )+1 )==1 )
    {
        aa=qba.at( pla*2 );
    }

}

void selnumt( int pla, char &aa , QByteArray  &qba )
{
    if( qba.at( ( pla*2 )+1 )==1 )
    {
        aa=qba.at( pla*2 );
    }

}
char pnumt( int pla, bool &aa , QByteArray  &qba )
{
    if( qba.at( ( pla*2 )+1 )==1 )
    {
        aa=qba.at( pla*2 );
    }
return qba.at( ( pla*2 )+1 );
}

void ciureceive( gsvar &gsva, gsett &gsetb, QByteArray  &qba   )
{
 //   charintunion mru;
  //  int ite;
    setdg jdg;
    jdg.setdgconst();


    flipnumt( jdg.safetyon_pla_, gsetb.safetyon, qba   );
    flipnumt( jdg.splon_pla_, gsetb.splon, qba   );
    flipnumt( jdg.minecollect_pla_ , gsva.minecollect, qba   );
    selnumt( jdg.ghatt_pla_ , gsva.ghattack, qba   );

    flipnumt(jdg.centervie_pla_ , gsva.centervie, qba   );
    //flipnumt( 5, gsva.lghostcount, qba   );
    //flipnumt( 6, gsva.spinghostcount, qba   );
    flipnumt(jdg.minewait_pla_ , gsva.minewait, qba   );

    selnumt(jdg.brake_pla_ , gsva.brake, qba   );
    selnumt( jdg.edgece_pla_ , gsva.edgece, qba   );
    flipnumt( jdg.sightb_pla_, gsva.sightb, qba   );
    flipnumt( jdg.spixu_pla_, gsva.spixu, qba   );

    flipnumt( jdg.freelo_pla_ , gsetb.freelo, qba   );
    flipnumt( jdg.sangle_pla_, gsetb.sangle, qba   );
    flipnumt( jdg.fullsc_pla_ , gsetb.fullsc, qba   );
    flipnumt( jdg.ksuuntvh_pla_, gsetb.ksuuntvh, qba   );
    flipnumt( jdg.asuuntvh_pla_ , gsetb.asuuntvh, qba   );
    flipnumt( jdg.lsuuntvh_pla_ , gsetb.lsuuntvh, qba   );
    flipnumt( jdg.miskoh_pla_, gsetb.miskoh, qba   );
    flipnumt( jdg.mst_pla_ , gsetb.mst, qba   );

    flipnumt( jdg.msmi_pla_, gsetb.msmi, qba   );
    flipnumt(jdg.hud_pla_ , gsetb.hud, qba   );
    flipnumt( jdg.asthud_pla_, gsetb.asthud, qba   );
    flipnumt( jdg.isohud_pla_, gsetb.isohud, qba   );

    flipnumt(jdg.helptexton_pla_ , gsetb.helptexton, qba   );
    flipnumt(jdg.shortmeson_pla_ , gsetb.shortmeson, qba   );

    selnumt( jdg.ympy_pla_, gsetb.ympy, qba  );
    flipnumt( jdg.pause_pla_, gsva.pause, qba );
    flipnumt( jdg.newgame_pla_, gsva.newgame, qba );
    flipnumt( jdg.newship_pla_, gsva.newship, qba );
    gsva.zoom_minus_bn=pnumt( jdg.zoom_minus_pla_, gsva.zoom_minus, qba );
    gsva.zoom_plus_bn= pnumt( jdg.zoom_plus_pla_ , gsva.zoom_plus , qba );


    flipnumt( jdg.reloadconf_pla_, gsva.reloadconf, qba );
    selnumt( jdg.mine_pla_, gsva.mine, qba);
    selnumt( jdg.deton_pla_, gsva.deton, qba);
    flipnumt( jdg.clearb_pla_, gsva.clearb, qba);
    selnumt( jdg.ppicint_pla_, gsetb.ppicint, qba);
    flipnumt( jdg.thrust_pla_, gsva.thrust, qba);
    selnumt( jdg.trail_pla_, gsva.trail, qba);
    flipnumt( jdg.minevisible_pla_, gsva.minevis, qba);

    flipnumt( jdg.bervisible_pla_, gsetb.berryvisible, qba);
    flipnumt( jdg.enervisible_pla_, gsetb.enervisible, qba);
    flipnumt( jdg.boxvisible_pla_ , gsetb.boxvisible, qba);
    flipnumt( jdg.bercol_pla_   , gsetb.berrycollect, qba);
    flipnumt( jdg.enercol_pla_ , gsetb.enercollect, qba);
    flipnumt( jdg.boxcol_pla_ , gsetb.boxcollect, qba);

    flipnumt(  jdg.slowthrust_pla_, gsva.slowthrust, qba );
    selnumt(  jdg.minelay_pla_, gsva.minelay, qba );
    flipnumt(  jdg.explvisible_pla_, gsetb.explvisible, qba );
    flipnumt(  jdg.closeboth_pla_, gsetb.quitb, qba );


    //gsva.ghattack_c=qba.at( 1 );
    //gsva.ghattack_c
    /*    gsva.centervie=qba.at( 2 );
    gsva.centervie_c=qba.at( 3 );
gsva.minecollect=qba.at( 16 );
gsva.minecollect_c=qba.at( 17 );
*/

    //if( gsva.ghattack==0 )
    // cout << " ciu gsva " << gsva.ghattack << endl;


    // cout << " qba size " << qba.size() << endl;
}

