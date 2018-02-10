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



#ifndef GMU_H
#define GMU_H
#include<QLine>

#include<QRect>
#include<QColor>
#include<string>
#include<QString>
#include<iostream>
using namespace std;

 struct tthv
 {
     int nhh, mkk;
 };

 struct mesnum
 {
 int mes;
 int tcou, tcoun;
int sernum;
float distance;


 };

 struct mnu
{
  int mes, distance, tcoun;

};

 struct meslist
 {
     QList<mnu> mli;
     int tcou;

 };

 struct gsvar
 {

     int nofa;
int vika;
int wwidth;
int wheight;
float scafa;
char trail;
int missiles, missiles_p;
int missilesb;
string clinecolorname;
float fuel;
float fuelb, clinepacshipangle;

float velocity, norvelocity, pevelocity;

int berries_in, berries_meadow;
double viewangle;
int paclives;
float pac1x1, pac1y1;


int ghostx;
int ghosty;
bool  ghattack_sel, ghattack_c;
char ghattack;
long long int tec;
long long int ngcou;
long long int setcou;
int reason;
QRect bord;
bool centervie, centervie_c;
int mines, mines_p, minesout;
int minesb;
int ghosts;
int ghostsb, ghostscline;
int norghostcount, spinghostcount, ghostcount, lgh_c, sgh_c;
bool minewait, minewait_c, edgece_c ;
char edgece;

int ghinv, ghinvcl;
bool sightb, sightb_c ;
double ghpacetclo;
const char *spix;
bool spixu, spixu_c;
double zoom;
int shortmsg, shortmsgcou;

//double vix;
//double viy;
int vix;
int viy;
bool  minecollect, brake_c, minecollect_c;
char brake;
string clinearenapic, clinearenaoverlay, configfile, keyconfig;
float fps;

QList<mesnum> shortmsglist;
QList<meslist> meslislis;

char spotted;
int spottednum, spotted_lios, spottedby;
bool spotted_c, shortmsg_c, pause_c, newgame_c, newship_c, zoom_plus_c,zoom_minus_c,
zoom_plus_bn, zoom_minus_bn, reloadconf_c,
mine_c, deton_c, clearb_c, thrust_c,slowthrust_c, close_c, ghinv_c, hcmode_c, reason_c,
paclives_c, nofa_c, trail_c, ghost_mode_c, ener_c, speed_c, revacc_c ;

bool pause, newgame, newship, zoom_plus, zoom_minus, reloadconf, clearb, thrust,
slowthrust, revacc, close, minelay_c, minevis, minevis_c, fullscreen, opengl, fullscreencl, openglcl;

char minelay, mine, deton;

bool drivemode, drivemodecl;

float minegap;
double ghcloseprecision;
QString playmedia, pausemedia, skipbackmedia;

 } ;


 struct gsett
 {
     QPoint fuelcoord, velcoord, minescoord, misscoord, closestcoord, berriescoord,
     ghostscoord, zoomcoord, minewaitcoord, ghattackcoord,
     brakecoord, teccoord, setcoucoord, vixcoord, viycoord,
     mousestcoord, mousemicoord, sploncoord, safetyoncoord, minecollectcoord, fpscoord ;
QRectF helptextrect, shorttextrect;

int hudtextr, hudtextg, hudtextb, hudtexta,
movliner, movlineg, movlineb, movlinea,
poiliner, poilineg, poilineb, poilinea,
amliner, amlineg, amlineb, amlinea,
edgr, edgg, edgb, edga,
visightliner, visightlineg, visightlineb, visightlinea,
lksightliner, lksightlineg, lksightlineb, lksightlinea;

QColor poilinecol, poilinecol2;

int crect;
float  exco, condwidth, condve;
bool splon, safetyon, splon_c, safetyon_c, freelo, freelo_c, sangle, sangle_c, fullsc, fullsc_c;

int k_thrust, k_slower, missilesadd, ghost_mode, ympy_c, hcmode, clearboomgh;
char ympy;

float margin,
traffic_collision_velocity,
speed_limiterf,
missile_speed, max_missile_age,
expvcb, expvca, expvcg, expsize, expvel1, expvel2,
readycost,  ghostrange, explrange, explspinrange, minetriggerrange, minespotrange,
minesliosspotrange, mistriggerrange, explsafetydistance;
bool spottedbyghostknowable, minesreportghlocation;
char closestknowable, mineslios, minechangedbyghost;

bool ksuuntvh, asuuntvh, lsuuntvh, miskoh, mst, msmi, ksuuntvh_c, asuuntvh_c, lsuuntvh_c, miskoh_c, mst_c, msmi_c;

bool hud, hudpre, asthud, isohud, helptexton, hud_c, asthud_c, isohud_c, helptexton_c;

QColor visicol, lksicol;

QString hudfontname, helphudfontname,  helphudshortfontname;
string arenapic, overlaypic;

string marjpicn, boxcratepicn, enerpicn, minepicn, mine_nw_picn, mi_mine_picn, mi_mine_nw_picn, spotmine,
pacpicn, pacpicn1, pacpicn2, pacpicn3, ghostpicn ;

int shortmsgcoulim;
bool shortmeson, shortmeson_c, explvisible, explvisible_c, berrycollect, berrycollect_c,
enercollect, enercollect_c ,  boxcollect, boxcollect_c, berryvisible, berryvisible_c, berryvisible_pr ,
enervisible, enervisible_c, boxvisible, boxvisible_c, finite_fuel, finite_fuel_c, ghostplot, ghostplot_c ;


float grabdistance, rotate_rate, max_rotate_rate, slowro, mousestevel, breakacc,
thruacc, slowthruacc, ghostwarndist,
speedfuelexponent ;

int meadowr, meadowg, meadowb, hillr, hillg, hillb, waterr, waterg, waterb;

QColor meadowc, hillc, waterc, minespotsghcol, minespotsghlioscol,
minespotsghbrushcol, pacosightlinecol, pacomsightlinecol,
pacshipcol, plotcol, plotpointcol, plotghpointcol, minespotsghliosbrushcol;

float mardis, marboxdis, marenedis, boxdis, boxenedis, enedis, pacshipangle;
int iniloop, helphudshorttextcount, ghostspintime, lineplot, linelen, plotgap ;
char ppicint;
bool ppicint_c;
QString pacshipcolname;

float helphudtextr,
helphudtextg,
helphudtextb,
helphudtexta,
shelphudtextr,
shelphudtextg,
shelphudtextb,
shelphudtexta,

shelphudbbtextr,
shelphudbbtextg,
shelphudbbtextb,
shelphudbbtexta,

helphudshortfontsize,
helphudshortfontweight,

helphudfontsize,
helphudfontweight,

hudfontsize,
hudfontweight,

hudboldfontsize,
hudboldfontweight,
ghostwidth, pacwidth, minewidth, boxwidth, berwidth, enewidth,
ghosthawidth, pachawidth, minehawidth, boxhawidth, berhawidth, enehawidth;

float ghostdetectiondistance, ghostclosestmeasurementdistance, pacdetectiondistance,
moveangle, depthangle, defaultangle;
bool ghostdetectiondistance_on, ghostclosestmeasurementdistance_on, pacdetectiondistance_on;

QString server_in, server_out;
bool quitb, quitb_c;
int boomagelimit, collectgoal;
bool grayscale;

 };


struct helpmes
{
  QString htext;
QList<QString> htexli;


};



 struct pacinfo
 {
     int xpo, ypo;
     int lkxpo, lkypo;
int spot;
int lives;
long long int tecounter_of_info;

 };

 struct ghqanswer
{
 float xpa;
 float ypa;
 unsigned int paicol;

};

 struct ghqquestion
 {
    float xqcol;
    float yqcol;


 };

 struct sightline
 {
     QLine vii;
     int nak;

 };




#endif // GMU_H
