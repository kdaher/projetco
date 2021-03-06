//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without //even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"
#include "Sink.h"
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;
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
  int id;
  int link;
  double qi[10]={0.15982,0.16098,0.18345,0.17314,0.1692,0.19343,0.15215,0.16234,0.19233,0.17234};
  double csll[50],alpha,beta,sum1l,sum1h,sum2l,sum2h,lamdac,sumi,div,vhc,etha,mu,sumax,cr,bi,sigma2,np,gamma,deltap,deltar,deltax;
  int Dh;
  double sumqi,lamdaa,wlll,uhii,vhh,epsilon;
  int  N;
  double sumf;
  double w;
  double dl[10][10];
  double xhl[10][50];
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

  double wl[50];

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

  double ail[10][50];
  double ailp[10][50];
  double ailm[10][50];
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
    N=10;
    w=0.15;
    Dh=100;
    deltap=0.2;
    deltar=0.2;
    deltax=0.2;
    epsilon=1e-10;
    count=0;
    ifstream Link("Link_number.txt", ios::in );

    if(Link){
        Link>>link;
        Link.close();
        }
    for(int h=0;h<V;h++){
      for(int l=0;l<link;l++){
          xhl[h][l]=0;
      }
    for(int i=0;i<link;i++){
        wl[i]=0;
    }

    }
    ifstream fichier("dl.txt", ios::in ); // ouverture in �criture avec effacement du fichier ouvert

    if(fichier){
      for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fichier>>dl[i][j];
	}
      }
      fichier.close();
    }

    ifstream fichier1("ail.txt", ios::in );

    if(fichier1){
      for(int i=0;i<N;i++){
        for(int l=0;l<link;l++){
	  fichier1>>ail[i][l];
	}
      }
      fichier1.close();
    }

    for(int i=0;i<N;i++){
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
      csll[l]=alpha+beta*pow(dis(l),np); // 4: path loss exponent
    }

    cMessage *msg = new cMessage("Iteration");
    msg->setKind(0);

    int out =gateSize("out");
    for(int i=0;i<out;i++){
      send (msg->dup(),"out",i);
    }
  }

  double Source::dis (int l)//////// return the distance between source and destination
  { double dist=0;
    for(int i=0;i<N;i++){
      if(ail[i][l]==1){
	for(int j=0;j<N;j++){
	  if(ail[j][l]==-1){
	    dist = dl[i][j];
	  }
        }
      }
    }
    return dist;
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


  void Source::flamda (int i){

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


  void Source::fwl (int nb){  // ///////////// function wl

    for(int l=0;l<link;l++){
      double sumq=0;
      for (int i=0;i<N;i++){
	sumq=sumq+ail[i][l]*qi[i];
      }
      wl[l]=wl[l]+(((double)w)/(sqrt(nb)))*sumq;

    }
  }


  void Source::fvh (int h){  ///////////// function return vh
    double x=0;
    double a= ((double)sigma2)/Dh;
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

      sumqi=sumqi+ail[id][l]*wl[l];

    }
    double sumqii=((double)(-(sumqi-lamda[id]*bi)))/2;

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
      for(int i=0;i<N;i++){
	sum=sum+lamda[i]*(csll[l]*ailp[i][l] + cr*ailm[i][l])+uhi[h][i]*ail[i][l];
      }
      xht=(double)-sum/(2*deltax);
      if(xht>0){
	xhl[h][l]=xht;
      }
      else {
	xhl[h][l]=0;
      }
    }
  }

  void Source::calculSink(){

    double old=sumf;
    sumf=0;

    double sigma1=0;
    for(int i=0;i<N;i++){
        double s1=0;
        for(int l=0;l<link;l++){
            s1 = s1 + ail[i][l]*wl[l];
            }
        sigma1 = sigma1 + qi[i]*qi[i] + qi[i]*s1-lamda[i]*bi;
    }

    double sigm2=0;
    for(int h=0;h<V;h++){
        double lo= ((double)sigma2)/Dh;
        sigm2 = sigm2 + (double)(log(lo) * vh[h])/ gamma*pow(ps[h],0.6666666666666667) + lamda[h] * ps[h] + deltap*pow(ps[h],2.6666666666666667);
    }

    double sigma3=0;
    for(int h=0;h<V;h++){
        double s3=0;
        for(int l=0;l<link;l++){
            double s2=0;
            for(int i=0;i<N;i++){
                s2 = s2 + ( lamda[i]*(csll[l]*ailp[i][l] + cr*ailm[i][l])+uhi[h][i]*ail[i][l] );
            }
            s3 = s3 + deltax*xhl[h][l]*xhl[h][l] + xhl[h][l]*s2;
        }
        sigma3 =sigma3 + s3;
    }

    double sigma4=0;
    for(int h=0;h<V;h++){
        double s4=0;
        for(int i=0;i<N;i++){
            s4 = s4 + (uhi[h][i]*ethac (h,i ,r));
        }
        sigma4 = sigma4 + (deltar*r[h]*r[h] - vh[h]*r[h] - s4);
    }

    sumf = sigma1 + sigm2 + sigma3 + sigma4;

    fabst=fabs((old-sumf));
  }

  void Source::afficherqi(){
    for(int i=0;i<V;i++){
        ev<<"qi["<<i<<"]"<<qi[i]<<endl;
          }
        ev<<"diff "<<fabst<<endl;
  }

  void Source::enregistrer(int iter){

  ofstream fichier1("C:/Users/User/Desktop/omnet++/omnet+mixim/omnetpp-4.6/samples/projetco/simulations/Qi.txt", ios::out | ios::app);
  ofstream fichier2("C:/Users/User/Desktop/omnet++/omnet+mixim/omnetpp-4.6/samples/projetco/simulations/Ps.txt", ios::out | ios::app);
  ofstream fichier3("C:/Users/User/Desktop/omnet++/omnet+mixim/omnetpp-4.6/samples/projetco/simulations/Rh.txt", ios::out | ios::app);
  if(fichier1){
      fichier1<<"numero de liens = "<<link<<endl;
      fichier1<<"iteration "<<iter<<endl;
      for(int i=0;i<V;i++){
          fichier1<<"qi["<<i<<"]"<<qi[i]<<endl;
                         }
      fichier1<<endl;
      fichier1.close();
  }
  if(fichier2){
      fichier2<<"iteration "<<iter<<endl;
      for(int h=0;h<V;h++){
          fichier2<<"Ps["<<h<<"]"<<ps[h]<<endl;
          }
      fichier2<<endl;
      fichier2.close();
  }
  if(fichier3){
      fichier3<<"iteration "<<iter<<endl;
      for(int h=0;h<V;h++){
          fichier3<<"Rh["<<h<<"]"<<r[h]<<endl;
      }
      fichier3<<endl;
      fichier3.close();
  }
      }
  void Source::handleMessage(cMessage *msg)
  {
      int o2= gateSize("out2");
      int o= gateSize("out");
      //ev<<"Handle message"<<endl;
      int in =gateSize("in");
      //ev<<"in="<<in<<endl;
      cMessage *keep= new cMessage("keep_data");
      keep->setKind(1);
      int id=getIndex();
      //ev<<"noeud numero:"<<id<<endl;
      int kd= msg->getKind();
      if (kd == 0){
          count++;
      }
      if (count==in){

          count=0;
          k++;
          fuhi(id);
          fvh(id);
          flamda(id);
          fqi(id);
          fpsh(id);
          frh(id);
          fxhl(id);
          for(int i=0;i<o;i++){
              send(msg->dup(),"out",i);
          }
      }
      else{
          ////ev<<"attendre les autres noeuds pour envoyer ack"<<endl;
          for(int i=0;i<o2;i++){
              send(keep->dup(),"out2",i);
          }
      }
      }
};// namespace
