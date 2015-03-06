//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace projetco {

  Define_Module(Source);
  //Define_Module(Sink);

  Source::Source()
  {
    timerMessage = NULL;
  }

  Source::~Source()
  {
    cancelAndDelete(timerMessage);
  }

  int k=0;
  int id;
  int link=22;
  double qi[10];
  double csll[22],alpha,beta,sum1l,sum1h,sum2l,sum2h,lamdac,sumi,div,vhc,etha,mu,sumax,cr,bi,sigma2,np,gamma,deltap,deltar,deltax;
  int Dh;
  double sumqi,lamdaa,wlll,uhii,vhh,epsilon;
  int  N;
  double sumf;
  double w;
  double dl[10][10];
  double xhl[10][22];

  double  ps[10]={0.364644,
		  0.377853,
		  0.414557,
		  0.45328,
		  0.380829,
		  0.457384,
		  0.363465,
		  0.454176,
		  0.327096,
		  0.387069};

  double lamda[10]={0.209763,
		    0.218569,
		    0.243038,
		    0.268853,
		    0.220553,
		    0.271589,
		    0.208977,
		    0.26945,
		    0.184731,
		    0.224713};

  double wl[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  double  uhi[10][10]={
    0.209763, 0.218569, 0.243038, 0.268853, 0.220553, 0.271589, 0.208977, 0.26945, 0.184731, 0.224713,
    0.229179, 0.176876, 0.187517, 0.159507, 0.278355, 0.111343, 0.292733, 0.154531, 0.176688, 0.195533,
    0.258345, 0.262434, 0.205779, 0.195995, 0.213609, 0.178557, 0.285119, 0.267216, 0.114207, 0.167479,
    0.117426, 0.229634, 0.104044, 0.173648, 0.266524, 0.291431, 0.255631, 0.12807, 0.274002, 0.274017,
    0.295724, 0.194722, 0.259832, 0.260182, 0.192296, 0.204095, 0.256106, 0.235776, 0.123655, 0.244127,
    0.227984, 0.216404, 0.128671, 0.207475, 0.288934, 0.251723, 0.20437, 0.121182, 0.182932, 0.19472,
    0.152911, 0.137266, 0.254847, 0.247384, 0.19123, 0.14331, 0.213687, 0.127044, 0.103758, 0.164828,
    0.223527, 0.129935, 0.222419, 0.144464, 0.223387, 0.177298, 0.28875, 0.28052, 0.236364, 0.18999,
    0.171902, 0.222613, 0.187406, 0.28047, 0.239526, 0.119856, 0.112045, 0.293962, 0.233353, 0.230628,
    0.234128, 0.134182, 0.142077, 0.17163, 0.125785, 0.250137, 0.163086, 0.221566, 0.172742, 0.165009
  };

  double vh[10]={0.209763,
		 0.218569,
		 0.243038,
		 0.268853,
		 0.220553,
		 0.271589,
		 0.208977,
		 0.26945,
		 0.184731,
		 0.224713,
  };

  double r[10]={0.154881,  //source rate
		0.159284,
		0.171519,
		0.184427,
		0.160276,
		0.185795,
		0.154488,
		0.184725,
		0.142365,
		0.162356};

  double ail[10][22];
  double ailp[10][22];
  double ailm[10][22];
  int V=9;
  int h=1;
  double cccsl = 0;


  void Source::initialize()
  {
    k=0;
    alpha=0.5;
    beta=1.3E-8;
    sigma2=3500;
    gamma=55.54;
    np=4;
    cr=0.5;
    bi=5.0;
    N=9;
    w=0.15;
    Dh=100;
    deltap=0.2;
    deltar=0.2;
    deltax=0.2;
    epsilon=1e-10;
    count=0;
    ifstream fichier("dl.txt", ios::in ); // ouverture in écriture avec effacement du fichier ouvert

    if(fichier){
      for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
	  fichier>>dl[i][j];
	}
      }
      fichier.close();
    }

    ifstream fichier1("ail.txt", ios::in );

    if(fichier1){
      for(int i=0;i<10;i++){
        for(int l=0;l<link;l++){
	  fichier1>>ail[i][l];
	}
      }
      fichier1.close();
    }

    for(int i=0;i<10;i++){
      for(int j=0;j<link;j++){
	if(ail[i][j]==1) {
	  ailp[i][j]=1;
	  ailm[i][j]=0;
	}
	else if(ail[i][j]==-1){
	  ailm[i][j]=1;
	  ailp[i][j]=0;
	}
	else{
	  ailm[i][j]=0;
	  ailp[i][j]=0;
	}
      }
    }
    for(int l=0;l<link;l++){
      csll[l]=alpha+beta*pow(dis(l),4); // 4: path loss exponent
    }

    srand(time(NULL));

    int idi=getIndex();
    ev<<"psnew: "<<ps[idi]<<endl;
    ev<<"lamdanew: "<<lamda[idi]<<endl;
    ev<<"vhnew: "<<vh[idi]<<endl;
    ev<<"rnew: "<<r[idi]<<endl;
    ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
    ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
    for (int i=0;i<10;i++){
      ev<<"uhi["<<idi<<"]["<<i<<"] ="<<uhi[idi][i]<<endl;
    }
    ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;

    for(int i=0;i<10;i++){
      ev<<"dl["<<idi<<"]["<<i<<"] ="<<dl[idi][i]<<endl;
    }
    ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
    ev<<"initialize"<<endl;

    

    cMessage *msg = new cMessage("Iteration");
    msg->setKind(0);

    int out =gateSize("out");
    ev<<"out="<<out<<endl;

    for(int i=0;i<out;i++){
      send (msg->dup(),"out",i);
    }
  }

  double Source::dis (int l)//////// return the distance between source and destination
  {
    for(int i=0;i<10;i++){
      if(ail[i][l]==1){
	for(int j=0;j<10;j++){
	  if(ail[j][l]==-1){
	    return dl[i][j];
	  }
        }
      }
    }
  }

  double Source:: ethac (int h,int i ,double rh[])/////return rh
  {
    double ret = 0;
    if (i ==h )
      ret =rh[h];
    else{
      if( i==9)//if sink
	ret = -rh[h];
    }
    return ret ;
  }


  void Source::flamda (int i){// function return lambda

    double sump=0;
    for(int l=0;l<link;l++){
      double  sumx=0;
      for(int h=0;h<V;h++){
	sumx=sumx+xhl[h][l];
      }
      sump=sump+(ailp[i][l]*csll[l]*sumx);
    }

    double summ=0;
    for(int l=0;l<link;l++){
      double  sumx=0;
      for(int h=0;h<V;h++){
	sumx=sumx+xhl[h][l];
      }
      summ=summ+(ailm[i][l]*cr*sumx);
    }

    double fg=(((double)w)/sqrt(k))*(qi[i]*bi-sump-summ-ps[i]) ;
    lamdac=lamda[i]-fg;

    if(lamdac>0)
      lamda[i]=lamdac;
    else {
      lamda[i]=0;
    }
  }


  void Source::fwl (){  // ///////////// function wl

    for(int l=0;l<link;l++){
      double sumq=0;
      for (int i=0;i<N;i++){
	sumq=sumq+ail[i][l]*qi[i];
      }
      wl[l]=wl[l]+(((double)w)/(sqrt(k)))*sumq;
    }
  }


  void Source::fvh (int h){  ///////////// function return vh

    double x=0;
    double a= ((double)sigma2)/;
    div =  log(a) /(gamma*pow(ps[h],((double)2)/3));
    x=(((double)w)/sqrt(k))*(r[h]-div);
    vhc=vh[h]-x;
    if(vhc>0)
      vh[h]=vhc;
    else {
      vh[h]=0;
    }
  }

  void Source::fuhi (int i) ///////////// function return u hi
  {
    double calc;
    for(int h=0;h<V;h++){
      double sumqi = 0;
      for(int l=0;l<link;l++){
	sumqi=sumqi+ail[i][l]*xhl[h][l];
      }
      calc= ethac (h,i ,r);
      uhi[h][i]=uhi[h][i]-((((double)w)/(sqrt(k)))*(calc-sumqi));
    }
  }

  void Source::fqi (int id) ///////////// function return qi
  {
    double sumqi=0;

    for(int l=0;l<link;l++){
      double  wll= wl[l];
      sumqi=sumqi+ail[id][l]*wll;

    }
    double sumqii=((double)(-(sumqi-lamda[id]*bi)))/2;
    ev<<"lamda="<<lamda[id]<<endl;

    if(sumqii>epsilon)
      {
        qi[id]=sumqii;
      }
    else
      {
        qi[id]=epsilon;
      }


  }

  void Source::fpsh (int h) ///////////// function return ps
  {
    double a= -3*lamda[h];
    double lo= ((double)sigma2)/Dh;
    double b= sqrt((pow(3*lamda[h],2))+(((double)((64*deltap)))* log(lo) * vh[h])/ gamma);
    double c =a+b;
    double sump=((double)c)/(16*deltap);
    double sumph=pow(sump,0.6);

    if(sumph>epsilon)
      ps[h]=sumph;
    else
      {
        ps[h]=epsilon;
      }
  }

  void Source::frh (int id){ ///////////// function return rh
    double resultatrh=((double)vh[id])/(2*deltar);
    if(resultatrh>0)
      r[id]=resultatrh;
    else
      {
        r[id]=0;
      }
  }

  void Source::fxhl (int h){ ///////////// function return xhl

    double xht=0;
    for(int l=0;l<link;l++){
      double sum=0;
      for(int i=0;i<10;i++){
	sum=sum+lamda[i]*(csll[l]*ailp[i][l] + cr*ailm[i][l])+uhi[h][i]*ail[i][l];
      }
      xht=(double)-sum/(2*deltax);

      ev<<"xht"<<xht<<endl;

      if(xht>0){
	xhl[h][l]=xht;
      }
      else {
	xhl[h][l]=0;
      }
    }
  }

  void Source::handleMessage(cMessage *msg)
  {
    double fabst;
    int o= gateSize("out");
    int o2= gateSize("out2");
    ev<<"Handle message"<<endl;
    int in =gateSize("in");
    ev<<"in="<<in<<endl;

    cMessage *keep= new cMessage("keep_data");
    keep->setKind(1);
    int id=getIndex();
    ev<<"noeud numero:"<<id<<endl;

    int kd= msg->getKind();
    if (kd == 0){
      count++;
    }

    ev<<"test count"<<endl;
    ev<<"count="<<count<<endl;
    if (count>=0){
      ev<<"count= in alors iter ++"<<endl;
      count=0;
      k++;
      ev<<"noeud numero:"<<id<<endl;
      fuhi(id);//calculate uhi
      fvh(id);//calculate vh
      flamda(id);//calculate lambda
      // fwl();//calculate wl
      fqi(id);//calculate qi
      fpsh(id);//calculate psh
      frh(id);//calculate rh
      fxhl(id);//calculate xhl

      double sqi=0;
      double spsh=0;
      double srh=0;
      double sxhl=0;
      double old=sumf;
      sumf=0;

      for (int i=0;i<N;i++){

	sqi=sqi+(qi[i]*qi[i]);

      }

      for (int i=0;i<N;i++){
	for (int l=0;l<link;l++){
	  for (int h=0;h<V;h++){
	    sxhl=sxhl+(xhl[h][l]*xhl[h][l]);

	  }
	}}

      for (int h=0;h<V;h++){
	srh=srh+(r[h]*r[h]);
      }

      for (int h=0;h<V;h++){
	spsh=spsh+(pow(ps[h],0.6666666667));
      }

      ev<<"sqi"<<sqi<<endl;
      ev<<"sxhl"<<sxhl<<endl;
      ev<<"srh"<<srh<<endl;
      sumf=sqi+deltax*sxhl+deltar*srh;
      ev<<"old eq3= "<<old<<endl;
      ev<<"new eq3= "<<sumf<<endl;
      fabst=fabs((old-sumf));
      ev<<"la difference est"<<fabst<<endl;

      if (fabst>0){
	for(int i=0;i<N;i++){
          ev<<"qi["<<i<<"]"<<qi[i]<<endl;
	}

	ev<<"Incremente les iterations"<<endl;
	for(int i=0;i<o;i++){
	  send(msg->dup(),"out",i);
	}
	for(int i=0;i<o2;i++){
	  send(keep->dup(),"out2",i);
	}
      }

      else{
	ev<<"arrete les iterations, envoie keep_iteration "<<endl;
	for(int i=0;i<o2;i++){
	  send (keep->dup(),"out2",i);
	}
	for(int i=0;i<N;i++){
	  ev<<"qi["<<i<<"]"<<qi[i]<<endl;
	  ev<<"wl"<<wl[i]<<endl;
	}
	ev<<"iteration numero:"<<k<<endl;
	endSimulation ();
      }
    }
    else{
      ev<<"attendre les autres noeuds pour envoyer ack"<<endl;
      for(int i=0;i<o2;i++){
	send(keep->dup(),"out2",i);
      }
    }
  }
};// namespace
