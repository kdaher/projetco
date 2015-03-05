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

    double csll[22],alpha,beta,np,sum1l,sum1h,sum2l,sum2h,lamdac,sumi,div,vhc,etha,mu,sumax,cr,bi,rf,sigma2,gamma;

    double sumqi,lamdaa,wlll,uhii,vhh;
    int  N;
    double sumf;

    double w;




 double dl[10][10];/*={ // distance entre 2 noeuds
         0, 17,25,29,10,47,42,24,44,6,
         17,0,8,23,16,39,38,7,37,17,
         25,8,0,28,24,41,42,5,39,25,
         29,23,28,0,19,18,14,23,15,23,
         10,16,24,19,0,37,32,21,34,4,
         47,39,41,18,37,0,10,36,3,41,
         42,38,42,14,32,10,0,37,7,36,
         24,7,5,23,21,36,37,0,34,23,
         44,37,39,15,34,3,7,34,0,38,
         6,117,25,23,4,41,36,23,38,0
         };*/
   // double dl[10][10];


 double xhl[10][22];/*={  //link rate pour chaque session h tab a 3 dimensions
 };*/

 double  ps[10]={0.364644,  //encoding power consumption
         0.377853,
         0.414557,
         0.45328,
         0.380829,
         0.457384,
         0.363465,
         0.454176,
         0.327096,
         0.387069};
//double ps[10];

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
// double lamda[10];

/* double  wl[10][10]={
0.229179, 0.176876, 0.187517, 0.159507, 0.278355, 0.111343, 0.292733, 0.154531, 0.176688, 0.195533,
0.209763, 0.218569, 0.243038, 0.268853, 0.220553, 0.271589, 0.208977, 0.26945, 0.184731, 0.224713,
0.117426, 0.229634, 0.104044, 0.173648, 0.266524, 0.291431, 0.255631, 0.12807, 0.274002, 0.274017,
0.258345, 0.262434, 0.205779, 0.195995, 0.213609, 0.178557, 0.285119, 0.267216, 0.114207, 0.167479,
0.227984, 0.216404, 0.128671, 0.207475, 0.288934, 0.251723, 0.20437,  0.121182, 0.182932, 0.19472,
0.295724, 0.194722, 0.259832, 0.260182, 0.192296, 0.204095, 0.256106, 0.235776, 0.123655, 0.244127,
0.152911, 0.137266, 0.254847, 0.247384, 0.19123, 0.14331, 0.213687, 0.127044, 0.103758, 0.164828,
0.223527, 0.129935, 0.222419, 0.144464, 0.223387, 0.177298, 0.28875, 0.28052, 0.236364, 0.18999,
0.171902, 0.222613, 0.187406, 0.28047, 0.239526, 0.119856, 0.112045, 0.293962, 0.233353, 0.230628,
0.234128, 0.134182, 0.142077, 0.17163, 0.125785, 0.250137, 0.163086, 0.221566, 0.172742, 0.165009
 };*/
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
// double uhi[10][10];

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
// double vh[10];
double r[10]={0.154881,   //source rate
         0.159284,
         0.171519,
         0.184427,
         0.160276,
         0.185795,
         0.154488,
         0.184725,
         0.142365,
         0.162356};
 //double r[10];

 double ail[10][22];/*={0, -1, 0, 0, 1, 0, 0, 0, 0, 1,
                     1, 0, -1, 0,1,0,0,-1,0,1,
                     0,1,0,0,0,0,0,1,0,0,
                     0,0,0,0,1,-1,-1,0,-1,0,
                     -1,-1,0,-1,0,0,0,0,0,1,
                     0,0,0,1,0,0,1,0,1,0,
                     0,0,0,1,0,-1,0,0,-1,0,
                     0, 1,-1,0,0,0,0,0,0,0,
                     0, 0, 0, 1,0,-1,1,0,0,0,
                     -1,-1,0, 0,-1,0,0,0,0,0};*/


 double ailp[10][22];

 double ailm[10][22];

 //int L=22; //directed wireless links
 int V=9;  //video n
 int h=1;
// int N=10;
 //int l=1;
 double epsilon=1e-10;
 double cccsl = 0;




void Source::initialize()
{
    count=0;
    ifstream fichier("dl.txt", ios::in ); // ouverture in écriture avec effacement du fichier ouvert

if(fichier)
{
        for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
              fichier>>dl[i][j];
      }}
        fichier.close();
}
ifstream fichier1("ail.txt", ios::in );

if(fichier1){
        for(int i=0;i<10;i++){
      for(int l=0;l<link;l++){
              fichier1>>ail[i][l];
      }}
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
            ailp[i][j]=0;}
        else{
            ailm[i][j]=0;
            ailp[i][j]=0;
        }
    }
}

    srand(time(NULL));

    int idi=getIndex();
       /* for(int y=0;y<rand();y++){
            ps[idi]=dblrand();
            }
    lamda[idi]=dblrand();*/
    //vh[idi]=dblrand();
   // r[idi]=dblrand();
   ev<<"psnew: "<<ps[idi]<<endl;
   ev<<"lamdanew: "<<lamda[idi]<<endl;
   ev<<"vhnew: "<<vh[idi]<<endl;
   ev<<"rnew: "<<r[idi]<<endl;
   ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
   for (int i=0;i<10;i++){
       //wl[idi][i]=dblrand();
      // ev<<"wl["<<idi<<"]["<<i<<"] ="<<wl[idi][i]<<endl;
   }
   ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
   for (int i=0;i<10;i++){
         // uhi[idi][i]=dblrand();
          ev<<"uhi["<<idi<<"]["<<i<<"] ="<<uhi[idi][i]<<endl;

      }
   ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
  /* for(int i=0;i<10;i++){
        dl[i][idi]=dblrand()*50;

       if (idi==i){
               dl[i][idi]=0;

      }

       }
   for(int i=0;i<10;i++){
       for( int j=0;j<10;j++){
           dl[i][j]=dl[j][i];
       }
   }*/

   for(int i=0;i<10;i++){

       ev<<"dl["<<idi<<"]["<<i<<"] ="<<dl[idi][i]<<endl;
   }
   ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
    ev<<"initialize"<<endl;

    /*k=0;
       if (idi==0){
       //alpha=0.5;
       alpha=dblrand();
       ev<<"alpha "<<alpha<<endl;
       beta=1.3E-8;
       ev<<"beta "<<beta<<endl;
       //np=4; //path loss exponent
       np= intrand(10);
       ev<<"np "<<np<<endl;
       //sigma2=3500;
       sigma2=3000+intrand(1000);
       ev<<"sigma2 "<<sigma2<<endl;
       //gamma=55.54; // doit etre 55.54 ??
       gamma=50+dblrand()*10;
       ev<<"gamma "<<gamma<<endl;
       //cr=0.5;
       cr=dblrand();
       ev<<"cr "<<cr<<endl;
      // bi=5.0;
       bi=1+intrand(9);
       ev<<"bi "<<bi<<endl;
      // rf=0.2; // regularization factor
       rf=dblrand();
       ev<<"rf "<<rf<<endl;

       N=9; //nombre de noeuds
       //w=0.15;  //step size parameter
       w=dblrand();
       ev<<"w "<<w<<endl;
       ev<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;



       }
*/
    k=0;
        alpha=0.5;
        beta=1.3E-8;
        np=4;
        sigma2=3500;
        gamma=55.54;
        cr=0.5;
        bi=5.0;
        rf=0.2;
        N=9;
        w=0.15;
    //timerMessage = new cMessage("timer");
   // scheduleAt(simTime(), timerMessage);
    cMessage *msg = new cMessage("Iteration");
    msg->setKind(0);
        // int out2=gateSize("out2");
         int out =gateSize("out");
         ev<<"out="<<out<<endl;

       for(int i=0;i<out;i++){
             send (msg->dup(),"out",i);}
      //  cMessage *duty = new cMessage("Video_data");

            //   duty->setKind(1);
              //   for(int i=0;i<out2;i++){
                    //   send (duty->dup(),"out2",i); }
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

void Source::ccsl ()/////return csl
{
 for(int l=0;l<link;l++){
    csll[l]=alpha+beta*pow(dis(l),np);

    }
}

double Source::wij (int isrc,int ides)///////////return i
{
   // return wl[isrc][ides];  //  doit etre return wl ??
}

void Source::flamda (int i){// function return lambda

double sump;
  //  for(int i0=0;i0<N;i0++){
        for(int l=0;l<link;l++){
            double  sumx=0;
            sump=0;
            for(int h=0;h<V;h++){
                sumx=sumx+xhl[h][l];
            }
           // if (i0 == i){

            sump=sump+(ailp[i][l]*csll[l]*sumx);
           // }
        }


  //  for(int i0=0;i0<N;i0++){
        double summ;
        for(int l=0;l<link;l++){
            double  sumx=0;
            summ=0;
            for(int h=0;h<V;h++){
                sumx=sumx+xhl[h][l];
            }
           // if (i0 == i){
                summ=summ+(ailm[i][l]*cr*sumx);
           // }
        }
  //  }

    double fg=(((double)w)/sqrt(k))*(qi[i]*bi-sump-summ-ps[i]) ;
    lamdac=lamda[i]-fg;
    //ev<< "lamda b4 test max------------------"<< lamdac<< endl;

    if(lamdac>0)
        lamda[i]=lamdac;
    else {
        lamda[i]=0;
    }
    /////        ev<<"lamda after test ----------->   "<<lamda[i]<<endl;
    /////       ev<<"                               "<<endl;
}


void Source::fwl ()// ///////////// function wl
{
    for(int l=0;l<link;l++){
        double sumq=0;
        for (int i=0;i<N;i++){
            //liens

                sumq=sumq+ail[i][l]*qi[i];
            //wl[i0][je] = wl[i0][je] + (((double)w)/sqrt(k))*(qi[i0]-qi[je]);
        }
        wl[l]=wl[l]+(((double)w)/(sqrt(k)))*sumq;
    }

     /*     for (int je=0;je<21;je++){
              if (ail[i0][je] == 1){//pour les liens qui ont pour origine i0
                                     wl[i0][je] = wl[i0][je] + sum;

}
    }*/}


void Source::fvh (int h) ///////////// function return vh
{
    double x=0;
    div=((double)log(sigma2)/100)/(gamma*pow(ps[h],((double)2)/3));
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
    double tempo, calc;
    for(int h=0;h<V;h++){
        double sumqi = 0;
        // for outgoing links
        for(int l=0;l<link;l++){
            sumqi=sumqi+ail[i][l]*xhl[h][l];
        }
        // for ingoing links
       /* for(int rid=0;rid<N;rid++){
            sumqi=sumqi+ail[rid][i]*xhl[h][rid][i];
        }*/
        calc= ethac (h,i ,r);

        uhi[h][i]=uhi[h][i]-((((double)w)/(sqrt(k)))*(calc-sumqi));

         tempo=((((double)w)/(sqrt(k)))*(calc-sumqi));

    }
    //ev<<"-------------calcul uhi-------------->   "<<tempo<<endl;
    //ev<<"-------------uhi-------------->   "<<uhi[h][i]<<endl;
  //  ev<<"-------------calc-------------->   "<<calc<<endl;
}


void Source::fqi (int id) ///////////// function return qi
{
    bi=5.0;
    double sumqi=0;
    double test;
    // for outgoing links
    for(int l=0;l<link;l++){
      sumqi=sumqi+ail[id][l]*wl[l];

    }
    // for ingoing links
 /* for(int rid=0;rid<N;rid++){
        double  wll= wij(rid,id);
      sumqi=sumqi+ail[rid][id]*wll;

    }*/
    /////     ev<<"somme"<<sumqi<<endl;
    /////     ev<<"lmda*b"<<lamda[id]*bi<<endl;
    double sumqii=((double)(-(sumqi-(lamda[id]*bi))))/2;
    ev<<"lamda="<<lamda[id]<<endl;

    if(sumqii>epsilon)
    {
        qi[id]=sumqii;
        /////          ev<<"-------------qi-------------->   "<<qi[id]<<endl;

    }
    else
    {
        qi[id]=epsilon;
    }


}

void Source::fpsh (int id) ///////////// function return ps
{
    double deltap=0.2;
    double gamma=55.54;
    double a= -3*lamda[id];
   // double a=3*lamda[id]*gamma;
   // double b= sqrt(pow(3*lamda[id],2)+((double)(64*deltap))/gamma*log(((double)sigma2)/100))  ;

    double b= sqrt((pow(3*lamda[id],2))+(((double)((64*deltap)))*(log(((double)sigma2)/100))*vh[id])/gamma);
    double c =a+b;
   // double sump=  ((double)a)/2*(log(((double)sigma2)/100))*vh[id];
    double sump=((double)c)/(16*deltap);
    double sumph=pow(sump,0.6);
   //double sumph=pow(sump,-0.6);
    if(sumph>epsilon)
        ps[id]=sumph;
    else
    {
        ps[id]=epsilon;
    }
 // ev<<"-------------ps-------------->   "<<ps[id]<<endl;
}

void Source::frh (int id) ///////////// function return rh
{

    double deltar =0.2;
    double resultatrh=((double)vh[id])/(2*deltar);
    epsilon=1e-10;
    if(resultatrh>0)
        r[id]=resultatrh;
    else
    {
        r[id]=0;
    }
    /////       ev<<"rh      "<<r[id]<<endl;
}


void Source::fxhl (int h) ///////////// function return xhl
{
    double xht=0;
    double deltax=0.2;
    //double xhs=0;
    //double cccsl0;
    for(int l=0;l<link;l++){
        double sum=0;
        for(int i=0;i<10;i++){
            sum=sum+lamda[i]*csll[l]*ailp[i][l] + lamda[i]*cr*ailm[i][l] +uhi[h][i]*ail[i][l];
        }
        xht=(double)-sum/(2*deltax);
        //ev<<"xht"<<xht<<endl;
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
    double deltax =0.2;
                       double deltar =0.2;
                       double deltap =0.2;
                      /* double sqi=0;
                       double spsh=0;
                       double srh=0;
                       double sxhl=0;
                       double old;*/
                       double fabst;

 //double t= 5+ dblrand()*5;
//ev<<"t"<<t<<endl;
   /* ASSERT(msg==timerMessage);

    cMessage *job = new cMessage("job");
    send(job, "out");

    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);*/
    int o= gateSize("out");
    int o2= gateSize("out2");
    ev<<"Handle message"<<endl;
    int in =gateSize("in");
    ev<<"in="<<in<<endl;
  // cMessage *ack = new cMessage("ack");
     //  ack->setKind(0);
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
           //    ev<<"iteration numero:"<<k<<endl;

                //  for (int id1=0;id1<N;id1++){
                     // ev<<"id1++"<<endl;
               ccsl();
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
              // ev<<"qi[id1]="<<qi[id1]<<endl;
              // ev<<"sqi"<<sqi<<endl;

                for (int i=0;i<N;i++){
                     // ev<<qi[i]<<endl;

                       sqi=sqi+(qi[i]*qi[i]);


                   }
                   //ev<<"sqi= "<<sqi<<endl;
               for (int i=0;i<N;i++){
                   for (int l=0;l<link;l++){
                   for (int h=0;h<V;h++){
                       sxhl=sxhl+(xhl[h][l]*xhl[h][l]);

                     }
                 }}
                      // ev<<"sxhl:"<<sxhl<<endl;

                   for (int h=0;h<V;h++){
                       srh=srh+(r[h]*r[h]);
                       }
                  // ev<<"srh:"<<srh<<endl;
                   for (int h=0;h<V;h++){
                       spsh=spsh+(pow(ps[h],0.6666666667));
                       }
                   //ev<<"spsh:"<<spsh<<endl;
                   ev<<"sqi"<<sqi<<endl;
                   ev<<"sxhl"<<sxhl<<endl;
                   ev<<"srh"<<srh<<endl;
                   sumf=sqi+deltax*sxhl+deltar*srh;//+deltap*spsh;

                   ev<<"old eq3= "<<old<<endl;
                   ev<<"new eq3= "<<sumf<<endl;
                   fabst=fabs((old-sumf));


                  ev<<"la difference est"<<fabst<<endl;

  if (fabst!=0)
   {for(int i=0;i<N;i++){
       ev<<"qi["<<i<<"]"<<qi[i]<<endl;
   }


            /*   }

                                double max = qi[0];
                                double min = qi[0];

                                for(int i = 1; i<N; i++)
                                   {
                                        if(qi[i] > max){

                                              max = qi[i];
                                   }
                                        if(qi[i] < min){

                                                          min = qi[i];
                                               }
                                               // return highest value in array
                              }
                                   ev<<""<<endl;
                                ev<<"max qi"<<max<<endl;
                                ev<<"min qi"<<min<<endl;


                            double div=(max/min)-1;
                            double p100=div*100;

                            ev<<"difference %" <<p100<<endl;
                     if (p100>1){*/

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
