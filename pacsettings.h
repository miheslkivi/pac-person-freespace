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



#ifndef PACSETTINGS_H
#define PACSETTINGS_H
#include"gmu.h"
#include <qapplication.h>
#include <fstream>
#include"pacinit.h"
#include"consco.h"
void pacset( gsvar &tgsvar, gsett &jgsett, helpmes  &thelpmes )
{


    QSettings settin_( tgsvar.configfile.c_str(), QSettings::NativeFormat);
    QSettings keysset_("keys.ini", QSettings::NativeFormat);

    jgsett.margin=settin_.value("margin").toInt();

    if( tgsvar.nofa==-1  )
    {
        tgsvar.nofa=settin_.value("nofa").toInt();
    }
    if( tgsvar.wwidth<0 )
    {
        tgsvar.wwidth=settin_.value("wwidth" ).toInt();
    }
    if( tgsvar.wheight<0 )
    {
        tgsvar.wheight=settin_.value("wheight").toInt();
    }

    tgsvar.scafa=settin_.value("scker").toFloat();
    if( tgsvar.trail==-1  )
    {
        tgsvar.trail=settin_.value("trail").toInt();
    }
    if( tgsvar.pac1x1<0 )
        tgsvar.pac1x1=settin_.value("pac1x1").toInt();

    if( tgsvar.pac1y1<0 )
        tgsvar.pac1y1=settin_.value("pac1y1").toInt();


    tgsvar.missilesb=settin_.value("missiles").toInt();
    tgsvar.fuelb=settin_.value("fuel").toFloat();
    tgsvar.ber=0;
    tgsvar.ghcloseprecision=settin_.value("ghcloseprecision").toDouble();
    if( tgsvar.ghostx<0 )
    {
        tgsvar.ghostx=settin_.value("ghostx").toInt();
    }
    if( tgsvar.ghosty<0 )
    {
        tgsvar.ghosty=settin_.value("ghosty").toInt();
    }

    tgsvar.reason=-1;
    tgsvar.minesb=settin_.value("mines").toInt();

    if( tgsvar.ghostscline!=-1 )
    {
        tgsvar.ghostsb=tgsvar.ghostscline;
    }
    else
    {
        tgsvar.ghostsb=settin_.value("ghosts").toInt();
    }

    tgsvar.ghattack=settin_.value("ghattack").toBool();
    tgsvar.ghattack_sel=settin_.value("ghattack_sel").toBool();

    if( tgsvar.ghinvcl==0 )
    {
        tgsvar.ghinv=settin_.value("ghinv").toInt();
    }
    tgsvar.sightb=settin_.value("sightb").toBool();
    tgsvar.minecollect=0;
    tgsvar.minewait=1;

    tgsvar.spix="km.png";
    tgsvar.spixu=0;
    jgsett.traffic_collision_velocity=settin_.value("traffic_collision_velocity").toFloat();
    jgsett.speed_limiterf=settin_.value("speed_limiter").toFloat();


    jgsett.missile_speed=settin_.value("missile_speed").toFloat();
    jgsett.max_missile_age=settin_.value("max_missile_age").toFloat();
    jgsett.ksuuntvh=settin_.value("ksuuntvh").toBool();
    jgsett.asuuntvh=settin_.value("asuuntvh").toBool();
    jgsett.lsuuntvh=settin_.value("lsuuntvh").toBool();
    jgsett.ympy=settin_.value("ympy").toInt();
    jgsett.isohud=settin_.value("isohud").toBool();
    jgsett.hud=settin_.value("hud").toBool();
    jgsett.asthud=settin_.value("asthud").toBool();
    jgsett.miskoh=settin_.value("miskoh").toBool();
    jgsett.grayscale=settin_.value("grayscale").toBool();

    jgsett.velcoord.setX( settin_.value("velx").toFloat() );
    jgsett.velcoord.setY( settin_.value("vely").toFloat() );

    jgsett.server_in=settin_.value( "server_in_name" ).toString();
    jgsett.server_out=settin_.value( "server_out_name" ).toString();

    jgsett.berriescoord.setX( settin_.value("berriesx").toFloat() );
    jgsett.berriescoord.setY( settin_.value("berriesy").toFloat() );

    jgsett.brakecoord.setX( settin_.value("brakex").toFloat() );
    jgsett.brakecoord.setY( settin_.value("brakey").toFloat() );


    jgsett.closestcoord.setX( settin_.value("closestx").toFloat() );
    jgsett.closestcoord.setY( settin_.value("closesty").toFloat() );


    jgsett.fuelcoord.setX( settin_.value("fuelx").toFloat() );
    jgsett.fuelcoord.setY( settin_.value("fuely").toFloat() );

    jgsett.ghattackcoord.setX( settin_.value("ghattackx").toFloat() );
    jgsett.ghattackcoord.setY( settin_.value("ghattacky").toFloat() );

    jgsett .ghostscoord.setX( settin_.value("ghostsx").toFloat() );
    jgsett .ghostscoord.setY( settin_.value("ghostsy").toFloat() );

    jgsett .misscoord.setX( settin_.value("missilesx").toFloat() );
    jgsett .misscoord.setY( settin_.value("missilesy").toFloat() );

    jgsett.zoomcoord.setX( settin_.value("zoomx").toFloat() );
    jgsett.zoomcoord.setY( settin_.value("zoomy").toFloat() );

    jgsett.minescoord.setX( settin_.value("minesx").toFloat() );
    jgsett.minescoord.setY( settin_.value("minesy").toFloat() );

    jgsett.minewaitcoord.setX( settin_.value("minewaitx").toFloat() );
    jgsett.minewaitcoord.setY( settin_.value("minewaity").toFloat() );

    jgsett.teccoord.setX( settin_.value("coux").toFloat() );
    jgsett.teccoord.setY( settin_.value("couy").toFloat() );

    jgsett.setcoucoord.setX( settin_.value("setcoux").toFloat() );
    jgsett.setcoucoord.setY( settin_.value("setcouy").toFloat() );

    jgsett.vixcoord.setX( settin_.value("vixposx").toFloat() );
    jgsett.vixcoord.setY( settin_.value("vixposy").toFloat() );

    jgsett.viycoord.setX( settin_.value("viyposx").toFloat() );
    jgsett.viycoord.setY( settin_.value("viyposy").toFloat() );

    jgsett.mousestcoord.setX( settin_.value("mousestx").toFloat() );
    jgsett.mousestcoord.setY( settin_.value("mousesty").toFloat() );

    jgsett.mousemicoord.setX( settin_.value("mousemix").toFloat() );
    jgsett.mousemicoord.setY( settin_.value("mousemiy").toFloat() );

    jgsett.sploncoord.setX( settin_.value("splonx").toFloat() );
    jgsett.sploncoord.setY( settin_.value("splony").toFloat() );

    jgsett.safetyoncoord.setX( settin_.value("safetyonx").toFloat() );
    jgsett.safetyoncoord.setY( settin_.value("safetyony").toFloat() );

    jgsett.minecollectcoord.setX(  settin_.value("minecollectx").toFloat() );
    jgsett.minecollectcoord.setY(  settin_.value("minecollecty").toFloat() );

    jgsett.fpscoord.setX(  settin_.value("fpsx").toFloat() );
    jgsett.fpscoord.setY(  settin_.value("fpsy").toFloat() );


    jgsett.helptextrect.setX( settin_.value("helptextx1").toFloat() );
    jgsett.helptextrect.setY( settin_.value("helptexty1").toFloat() );
    jgsett.helptextrect.setRight( settin_.value("helptextx2").toFloat() );
    jgsett.helptextrect.setBottom( settin_.value("helptexty2").toFloat() );

    jgsett.shorttextrect.setX( settin_.value("shorttextrectx1").toFloat() );
    jgsett.shorttextrect.setY( settin_.value("shorttextrecty1").toFloat() );
    jgsett.shorttextrect.setRight( settin_.value("shorttextrectx2").toFloat() );
    jgsett.shorttextrect.setBottom( settin_.value("shorttextrecty2").toFloat() );

    jgsett.msmi=settin_.value("mousemissile").toBool();
    jgsett.mst= settin_.value("mousestreer").toBool();


    jgsett.hudtextr=settin_.value("hudtextr").toFloat() ;
    jgsett.hudtextg=settin_.value("hudtextg").toFloat() ;
    jgsett.hudtextb=settin_.value("hudtextb").toFloat() ;
    jgsett.hudtexta=settin_.value("hudtexta").toFloat() ;

    jgsett.helphudtextr=settin_.value("helphudtextr").toFloat() ;
    jgsett.helphudtextg=settin_.value("helphudtextg").toFloat() ;
    jgsett.helphudtextb=settin_.value("helphudtextb").toFloat() ;
    jgsett.helphudtexta=settin_.value("helphudtexta").toFloat() ;

    jgsett.shelphudtextr=settin_.value("shelphudtextr").toFloat() ;
    jgsett.shelphudtextg=settin_.value("shelphudtextg").toFloat() ;
    jgsett.shelphudtextb=settin_.value("shelphudtextb").toFloat() ;
    jgsett.shelphudtexta=settin_.value("shelphudtexta").toFloat() ;

    jgsett.shelphudbbtextr=settin_.value("shelphudbbtextr").toFloat() ;
    jgsett.shelphudbbtextg=settin_.value("shelphudbbtextg").toFloat() ;
    jgsett.shelphudbbtextb=settin_.value("shelphudbbtextb").toFloat() ;
    jgsett.shelphudbbtexta=settin_.value("shelphudbbtexta").toFloat() ;


    jgsett.helphudshortfontsize=settin_.value("helphudshortfontsize").toFloat() ;
    jgsett.helphudshortfontweight=settin_.value("helphudshortfontweight").toFloat() ;

    jgsett.helphudfontsize=settin_.value("helphudfontsize").toFloat() ;
    jgsett.helphudfontweight=settin_.value("helphudfontweight").toFloat() ;

    jgsett.hudfontsize=settin_.value("hudfontsize").toFloat() ;
    jgsett.hudfontweight=settin_.value("hudfontweight").toFloat() ;

    jgsett.hudboldfontsize=settin_.value("hudboldfontsize").toFloat() ;
    jgsett.hudboldfontweight=settin_.value("hudboldfontweight").toFloat() ;


    jgsett.helphudshorttextcount=settin_.value("helphudshorttextcount").toInt();

    jgsett.movliner=settin_.value("movliner").toFloat() ;
    jgsett.movlineg=settin_.value("movlineg").toFloat() ;
    jgsett.movlineb=settin_.value("movlineb").toFloat() ;
    jgsett.movlinea=settin_.value("movlinea").toFloat() ;

    jgsett.poiliner=settin_.value("poiliner").toFloat() ;
    jgsett.poilineg=settin_.value("poilineg").toFloat() ;
    jgsett.poilineb=settin_.value("poilineb").toFloat() ;
    jgsett.poilinea=settin_.value("poilinea").toFloat() ;

    jgsett.amliner=settin_.value("amliner").toFloat() ;
    jgsett.amlineg=settin_.value("amlineg").toFloat() ;
    jgsett.amlineb=settin_.value("amlineb").toFloat() ;
    jgsett.amlinea=settin_.value("amlinea").toFloat() ;

    jgsett.edgr=settin_.value("edgr").toFloat() ;
    jgsett.edgg=settin_.value("edgg").toFloat() ;
    jgsett.edgb=settin_.value("edgb").toFloat() ;
    jgsett.edga=settin_.value("edga").toFloat() ;

    jgsett.visightliner=settin_.value("visightliner").toFloat() ;
    jgsett.visightlineg=settin_.value("visightlineg").toFloat() ;
    jgsett.visightlineb=settin_.value("visightlineb").toFloat() ;
    jgsett.visightlinea=settin_.value("visightlinea").toFloat() ;

    jgsett.lksightliner=settin_.value("lksightliner").toFloat() ;
    jgsett.lksightlineg=settin_.value("lksightlineg").toFloat() ;
    jgsett.lksightlineb=settin_.value("lksightlineb").toFloat() ;
    jgsett.lksightlinea=settin_.value("lksightlinea").toFloat() ;

    jgsett.visicol=QColor( jgsett.visightliner, jgsett.visightlineg, jgsett.visightlineb, jgsett.visightlinea );
    jgsett.lksicol=QColor( jgsett.lksightliner, jgsett.lksightlineg, jgsett.lksightlineb, jgsett.lksightlinea );

    jgsett.splon=settin_.value("speed_limiter_on").toBool() ;

    jgsett.exco=settin_.value("exco").toFloat();
    jgsett.condwidth=settin_.value("condwidth").toFloat();
    jgsett.condve=settin_.value("condve").toFloat();
    jgsett.ghost_mode=settin_.value("ghost_mode").toInt();

    jgsett.crect=settin_.value("crect").toInt();
    jgsett.missilesadd=settin_.value("missilesadd").toInt();
    jgsett.helptexton=settin_.value("helptexton").toBool();

    jgsett.hudfontname=settin_.value("hudfont").toString();
    jgsett.helphudfontname=settin_.value("helphudfontname").toString();
    jgsett.helphudshortfontname=settin_.value("helphudshortfontname").toString();

    jgsett.expvcg=settin_.value("expvcg").toFloat();
    jgsett.expvcb=settin_.value("expvcb").toFloat();
    jgsett.expvca=settin_.value("expvca").toFloat();

    jgsett.expsize=settin_.value("expsize").toFloat();
    jgsett.expvel1=settin_.value("expvel1").toFloat();
    jgsett.expvel2=settin_.value("expvel2").toFloat();

    jgsett.hcmode=settin_.value("hcmode").toInt();
    jgsett.safetyon=settin_.value("safetyon").toBool();
    jgsett.readycost=settin_.value("readycost").toFloat();

    jgsett.ghostrange =settin_.value("ghostrange").toFloat();
    jgsett.explrange =settin_.value("explrange").toFloat();
    jgsett.explspinrange =settin_.value("explspinrange").toFloat();
    jgsett.minetriggerrange=settin_.value("minetriggerrange").toFloat();
    jgsett.minespotrange=settin_.value("minespotrange").toFloat();

    jgsett.mistriggerrange=settin_.value("mistriggerrange").toFloat();
    jgsett.explsafetydistance=settin_.value("explsafetydistance").toFloat();

    jgsett.breakacc=settin_.value("breakacc").toFloat();
    jgsett.thruacc=settin_.value("thruacc").toFloat();
    jgsett.slowthruacc=settin_.value("slowthruacc").toFloat();

    tgsvar.minegap=settin_.value("minegap").toFloat();
    jgsett.ghostwarndist=settin_.value("ghostwarndist").toFloat();

    jgsett.marjpicn =settin_.value("marjpicn").toString().toStdString();
    jgsett.boxcratepicn =settin_.value("boxcratepicn").toString().toStdString();
    jgsett.enerpicn =settin_.value("enerpicn").toString().toStdString();
    jgsett.minepicn=settin_.value("minepicn").toString().toStdString();
    jgsett.mine_nw_picn =settin_.value("mine_nw_picn").toString().toStdString();
    jgsett.mi_mine_picn=settin_.value("mi_mine_picn").toString().toStdString();
    jgsett.mi_mine_nw_picn =settin_.value("mi_mine_nw_picn").toString().toStdString();
    jgsett.spotmine=settin_.value("spotmine").toString().toStdString();

    jgsett.explvisible =settin_.value("explvisible").toBool();
    tgsvar.minevis=settin_.value("minevisible").toBool();

    jgsett.berryvisible =settin_.value("berryvisible").toBool();
    jgsett.enervisible   =settin_.value("enervisible").toBool();
    jgsett.boxvisible =settin_.value("boxvisible").toBool();
    jgsett.finite_fuel =settin_.value("finite_fuel").toBool();

    jgsett.berrycollect =settin_.value("berrycollect").toBool();
    jgsett.enercollect =settin_.value("enercollect").toBool();
    jgsett.boxcollect  =settin_.value("boxcollect").toBool();
    jgsett.speedfuelexponent =settin_.value("speedfuelexponent").toFloat();

    jgsett.pacpicn=settin_.value("pacpicn").toString().toStdString();

    jgsett.pacpicn1=settin_.value("pacpicn1").toString().toStdString();
    jgsett.pacpicn2=settin_.value("pacpicn2").toString().toStdString();
    jgsett.pacpicn3=settin_.value("pacpicn3").toString().toStdString();
    jgsett.ppicint=settin_.value("ppicint").toInt();

    jgsett.ghostpicn=settin_.value("ghostpicn").toString().toStdString();
    jgsett.shortmsgcoulim=settin_.value("shortmsgcoulim").toInt();
    jgsett.grabdistance=settin_.value("grabdistance").toFloat();

    jgsett.meadowr=settin_.value("meadowr").toInt();
    jgsett.meadowg=settin_.value("meadowg").toInt();
    jgsett.meadowb=settin_.value("meadowb").toInt();
    jgsett.meadowc=QColor( jgsett.meadowr, jgsett.meadowg, jgsett.meadowb );

    jgsett.hillr=settin_.value("hillr").toInt();
    jgsett.hillg=settin_.value("hillg").toInt();
    jgsett.hillb=settin_.value("hillb").toInt();
    jgsett.hillc=QColor(jgsett.hillr, jgsett.hillg, jgsett.hillb );
    jgsett.waterr=settin_.value("waterr").toInt();
    jgsett.waterg=settin_.value("waterg").toInt();
    jgsett.waterb=settin_.value("waterb").toInt();
    jgsett.waterc=QColor(jgsett.waterr, jgsett.waterg, jgsett.waterb );

    jgsett.minespotsghcol.setRed( settin_.value("minespotsghcol_red").toInt()  );
    jgsett.minespotsghcol.setGreen( settin_.value("minespotsghcol_green").toInt()  );
    jgsett.minespotsghcol.setBlue( settin_.value("minespotsghcol_blue").toInt()  );
    jgsett.minespotsghcol.setAlpha( settin_.value("minespotsghcol_alpha").toInt()  );


    jgsett.pacshipcol.setRed( settin_.value("pacshipcol_red").toInt()  );
    jgsett.pacshipcol.setGreen( settin_.value("pacshipcol_green").toInt()  );
    jgsett.pacshipcol.setBlue( settin_.value("pacshipcol_blue").toInt()  );
    jgsett.pacshipcol.setAlpha( settin_.value("pacshipcol_alpha").toInt()  );
    jgsett.pacshipcolname=settin_.value("pacshipcolname" ).toString();

    jgsett.poilinecol=QColor( jgsett.poiliner, jgsett.poilineg, jgsett.poilineb, jgsett.poilinea  );


    jgsett.poilinecol2.setRed( settin_.value("poilinecol2_red").toInt()  );
    jgsett.poilinecol2.setGreen( settin_.value("poilinecol2_green").toInt()  );
    jgsett.poilinecol2.setBlue( settin_.value("poilinecol2_blue").toInt()  );
    jgsett.poilinecol2.setAlpha( settin_.value("poilinecol2_alpha").toInt()  );

    jgsett.boomagelimit=settin_.value("boomagelimit").toInt();
    if( tgsvar.openglcl )
    {

    }else
    {
        tgsvar.opengl=settin_.value("opengl").toBool();
    }
    if( !tgsvar.fullscreencl )
    {
        tgsvar.fullscreen=settin_.value("fullscreen").toBool();
    }
    jgsett.fullsc=tgsvar.fullscreen;

    coubo( " openGL", tgsvar.opengl  );

    // QColor::setAllowX11ColorNames ( settin_.value("allowx11colornames").toBool() );


    if( QColor::isValidColor( jgsett.pacshipcolname )  )
    {
        jgsett.pacshipcol.setNamedColor( jgsett.pacshipcolname );

    }
    else
    {
        if( jgsett.pacshipcolname.size()>0 )
        {
            cout << endl << " pacsettings.h : ERROR : invalid color name in config file: "
                 << jgsett.pacshipcolname.toStdString() << endl;

        }

    }

    if(  QColor::isValidColor( tgsvar.clinecolorname.c_str() )  )
    {
        jgsett.pacshipcol.setNamedColor( tgsvar.clinecolorname.c_str() );
    }
    else
    {
        if( tgsvar.clinecolorname.size()>0 )
        {
            cout << endl << " pacsettings.h : ERROR : invalid color name in command line: "
                 << tgsvar.clinecolorname << endl;

        }

    }
    jgsett.pacshipangle=settin_.value("pacshipangle"  ).toFloat();

    if( tgsvar.clinepacshipangle>-1000 )
    {
        jgsett.pacshipangle=tgsvar.clinepacshipangle;

    }


    jgsett.minespotsghlioscol.setRed( settin_.value("minespotsghlioscol_red").toInt()  );
    jgsett.minespotsghlioscol.setGreen( settin_.value("minespotsghlioscol_green").toInt()  );
    jgsett.minespotsghlioscol.setBlue( settin_.value("minespotsghlioscol_blue").toInt()  );
    jgsett.minespotsghlioscol.setAlpha( settin_.value("minespotsghlioscol_alpha").toInt()  );

    jgsett.minespotsghliosbrushcol.setRed( settin_.value("minespotsghliosbrushcol_red").toInt()  );
    jgsett.minespotsghliosbrushcol.setGreen( settin_.value("minespotsghliosbrushcol_green").toInt()  );
    jgsett.minespotsghliosbrushcol.setBlue( settin_.value("minespotsghliosbrushcol_blue").toInt()  );
    jgsett.minespotsghliosbrushcol.setAlpha( settin_.value("minespotsghliosbrushcol_alpha").toInt()  );


    jgsett.minespotsghbrushcol.setRed( settin_.value("minespotsghbrushcol_red").toInt()  );
    jgsett.minespotsghbrushcol.setGreen( settin_.value("minespotsghbrushcol_green").toInt()  );
    jgsett.minespotsghbrushcol.setBlue( settin_.value("minespotsghbrushcol_blue").toInt()  );
    jgsett.minespotsghbrushcol.setAlpha( settin_.value("minespotsghbrushcol_alpha").toInt()  );


    jgsett.pacosightlinecol.setRed( settin_.value("pacosightliner").toInt() );
    jgsett.pacosightlinecol.setGreen( settin_.value("pacosightlineg").toInt() );
    jgsett.pacosightlinecol.setBlue( settin_.value("pacosightlineb").toInt() );
    jgsett.pacosightlinecol.setAlpha( settin_.value("pacosightlinea").toInt() );

    jgsett.pacomsightlinecol.setRed( settin_.value("pacomsightliner").toInt() );
    jgsett.pacomsightlinecol.setGreen( settin_.value("pacomsightlineg").toInt() );
    jgsett.pacomsightlinecol.setBlue( settin_.value("pacomsightlineb").toInt() );
    jgsett.pacomsightlinecol.setAlpha( settin_.value("pacomsightlinea").toInt() );

    jgsett.plotcol.setRed( settin_.value("plotcolr").toInt() );
    jgsett.plotcol.setGreen( settin_.value("plotcolg").toInt() );
    jgsett.plotcol.setBlue( settin_.value("plotcolb").toInt() );
    jgsett.plotcol.setAlpha( settin_.value("plotcola").toInt() );

    jgsett.plotpointcol.setRed( settin_.value("plotpointcolr").toInt() );
    jgsett.plotpointcol.setGreen( settin_.value("plotpointcolg").toInt() );
    jgsett.plotpointcol.setBlue( settin_.value("plotpointcolb").toInt() );
    jgsett.plotpointcol.setAlpha( settin_.value("plotpointcola").toInt() );

    jgsett.plotghpointcol.setRed( settin_.value("plotghpointcolr").toInt() );
    jgsett.plotghpointcol.setGreen( settin_.value("plotghpointcolg").toInt() );
    jgsett.plotghpointcol.setBlue( settin_.value("plotghpointcolb").toInt() );
    jgsett.plotghpointcol.setAlpha( settin_.value("plotghpointcola").toInt() );

    jgsett.ghostplot=settin_.value("ghostplot").toBool();

    jgsett.lineplot=settin_.value("lineplot" ).toInt() ;
    jgsett.linelen=settin_.value("linelen" ).toInt() ;
    jgsett.plotgap=settin_.value("plotgap" ).toInt() ;


    jgsett.mardis=settin_.value("mardis").toFloat();
    jgsett.marboxdis=settin_.value("marboxdis").toFloat();
    jgsett.marenedis=settin_.value("marenedis").toFloat();
    jgsett.boxdis=settin_.value("boxdis").toFloat();
    jgsett.boxenedis=settin_.value("boxenedis").toFloat();
    jgsett.enedis=settin_.value("enedis").toFloat();
    jgsett.iniloop=settin_.value("iniloop").toInt();
    jgsett.shortmeson=settin_.value("shortmeson").toBool();
    jgsett.rotate_rate=settin_.value("rotate_rate").toFloat();
    jgsett.max_rotate_rate=settin_.value("max_rotate_rate").toFloat();
    jgsett.slowro=settin_.value("slowro").toFloat();
    jgsett.mousestevel=settin_.value("mousestevel").toFloat();

    jgsett.ghostspintime=settin_.value("ghostspintime").toInt();

    jgsett.ghostdetectiondistance=settin_.value("ghostdetectiondistance").toFloat();
    jgsett.ghostclosestmeasurementdistance=settin_.value("ghostclosestmeasurementdistance").toFloat();
    jgsett.pacdetectiondistance=settin_.value("pacdetectiondistance").toFloat();

    jgsett.ghostdetectiondistance_on=settin_.value("ghostdetectiondistance_on").toBool();
    jgsett.ghostclosestmeasurementdistance_on=settin_.value("ghostclosestmeasurementdistance_on").toBool();
    jgsett.pacdetectiondistance_on=settin_.value("pacdetectiondistance_on").toBool();
    jgsett.spottedbyghostknowable=settin_.value("spottedbyghostknowable").toBool();
    jgsett.closestknowable=settin_.value("closestknowable").toInt();
    jgsett.minesreportghlocation=settin_.value("minesreportghlocation").toBool();
    jgsett.minesliosspotrange=settin_.value("minesliosspotrange").toFloat();
    jgsett.mineslios=settin_.value("mineslios").toInt();
    jgsett.minechangedbyghost=settin_.value( "minechangedbyghost" ).toInt();
    jgsett.moveangle=settin_.value( "moveangle").toFloat();
    jgsett.depthangle=settin_.value( "depthangle").toFloat();
    jgsett.defaultangle=settin_.value( "defaultangle").toFloat();

    //    cout << endl << " exp --------" << jgsett.expvcb << "  " <<jgsett.expvca << "  " << jgsett.expvcg << "  "
    //       << jgsett.expsize << "  " << jgsett.expvel1 << "  " << jgsett.expvel2 << endl;


    if( tgsvar.clinearenapic.size()>0 )
    {
        jgsett.arenapic=tgsvar.clinearenapic;

    }
    else
    {
        jgsett.arenapic= settin_.value("arenapic").toString().toStdString();

    }
    if( tgsvar.clinearenaoverlay.size()>0 )
    {
        jgsett.overlaypic=tgsvar.clinearenaoverlay;
    }
    else
    {
        if( tgsvar.clinearenapic.size()==0 )
        {
        jgsett.overlaypic=settin_.value("overlaypic").toString().toStdString();
        }

        if( jgsett.arenapic.size()>0 and jgsett.overlaypic.size()==0 )
        {
            jgsett.overlaypic=jgsett.arenapic;

        }
    }
if( tgsvar.drivemodecl==0 )
{
    tgsvar.drivemode=settin_.value("drivemode"  ).toBool();
}
else
{


}


if( tgsvar.drivemode )
{
    jgsett.finite_fuel=0;
    jgsett.iniloop=0;
    tgsvar.ghostsb=0;
    jgsett.safetyon=1;
    jgsett.ksuuntvh=0;
    jgsett.asuuntvh=0;
    jgsett.lsuuntvh =0;
    jgsett.ympy=0;
}

    int ite;
    ifstream htexf;
    int htexflen;
    char * htexc;
    htexf.open( "helpmes.txt", ios::binary  );
    htexf.seekg( 0, ios::end );
    htexflen=htexf.tellg();
    htexf.seekg( 0, ios::beg );
    htexc=new char[htexflen] ;
    for( ite=0 ; ite< htexflen ; ite++ )
    {
        htexc[ite] ='h';
    }
    htexf.read( htexc, htexflen );
    htexf.close();
    QString vals;
    for( ite=0 ; ite< htexflen ; ite++ )
    {
        vals.append( htexc[ite] );
    }

    thelpmes.htexli.push_back( vals );

    htexf.open( "shortmes.txt", ios::binary  );
    for( ite=0 ; ite< 6 ; ite++ )
    {
        char shmsg[1000];
        htexf.getline( shmsg, 1000 );

        thelpmes.htexli.append( shmsg );

    }



    jgsett.k_thrust=keysset_.value("thrust").toInt();
    jgsett.k_slower=keysset_.value("slower").toInt();


    if( tgsvar.pac1x1<0 or tgsvar.pac1y1<0  )
    {
        cout <<"  pacsettings.h: ERROR " << tgsvar.pac1x1 << "    " <<tgsvar.pac1y1 << endl;
        exit(-1);
    }

    jgsett.hudpre=jgsett.hud;


}




#endif // PACSETTINGS_H
