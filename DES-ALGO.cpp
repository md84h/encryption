//Project By Mohd Danish Ansari (11BCE0155) and Gaurav Sikri (11BCE0218)
//Program to perform Encryption using DES algorith
//To check step by step instruction are encoded inside comments,you can use whichever step you want to see
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
int m[64];
void bin(int bnum,int i);//function to convert decimal to binary
main()
{
	char msg[16],key[16];
	int num,i,a[16],k[16],ms[64],ky[64],l=0,pk[56],d,c0[28],d0[28],v=0,x=0,j,h;
	for(i=0;i<64;i++)
	m[i]=0;	
	int	pc1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};//PC-1 Table
	cout<<"Enter Message which you want to encrypt of 16 lenght(Hexadecimal format)\n";
	cin>>msg;
	for(i=0;i<16;i++)
	{ 
		if(isalpha(msg[i]))
		a[i]=msg[i]-55;
		else
		a[i]=msg[i]-48;
	}
	for(i=0;i<16;i++)
	{
		l+=4;
		bin(a[i],l);
	}
	//cout<<"\nBinary form of MSG is\n";
	for(i=0;i<64;i++)
	{
        //cout<<m[i];
        ms[i]=m[i];
	}
	cout<<"\n\nEnter Key of lenght 16(Hexadecimal Format)\n";
	cin>>key;
	for(i=0;i<64;i++)
	m[i]=0;
	for(i=0;i<16;i++)
	{ 
		if(isalpha(key[i]))
		k[i]=key[i]-55;
		else
		k[i]=key[i]-48;
	}
	l=0;
	for(i=0;i<16;i++)
	{
		l+=4;
		bin(k[i],l);
	}
	//cout<<"\nBinary form of KEY is\n";
	for(i=0;i<64;i++)
	{
 	    //cout<<m[i];
      	ky[i]=m[i];
	}
 	//cout<<"\nPermuted Key after applying PC-1 Table\n"; 				 
 	for(i=0;i<56;i++)//Applying PC-1 Table
 	{
		d=pc1[i]; 				 
		pk[i]=ky[d-1];
		//cout<<pk[i];
	}
	for(i=0;i<56;i++)//Distributing Permuted Key into C0 & D0 forms each of 28 bit
	{
	    if(i<28)
 		c0[v++]=pk[i];
 		else
 		d0[x++]=pk[i];
	}
    /*cout<<"\n\n C0=";
    for(i=0;i<28;i++)
    cout<<c0[i];
    cout<<"\n\n D0=";
    for(i=0;i<28;i++)
    cout<<d0[i]; 
    */
 	int cn[16][28],dn[16][28];
	for(i=0;i<28;i++)//Creating C1-C16 & D1-D16 by left shift operation from previous one
	{
	    if(i==27)
 		{
		 		 cn[0][i]=c0[0];
	  			 dn[0][i]=d0[0];
        }
 	    else
	  	{
		 		 cn[0][i]=c0[i+1];
		  		 dn[0][i]=d0[i+1];
	    }
	}
 	for(i=1;i<16;i++)
	{
	 				 for(j=0;j<28;j++)
 					 {
					   				  if(i==1 || i==8 || i==15)
					   				  {
							 				  if(j==27)
			 								  {
											   		   cn[i][j]=cn[i-1][0];
	 				  								   dn[i][j]=dn[i-1][0];
   					   					      }
		  								  	  else
					  						  {
	 				 								   cn[i][j]=cn[i-1][j+1];
					  								   dn[i][j]=dn[i-1][j+1];
		  								      }
					                  }
					  				  else
 				  				  	  {
						   				  	  if(j==27)
		 								  	  {
											   		   cn[i][j]=cn[i-1][1];
	 				  								   dn[i][j]=dn[i-1][1];
		   			   					      }
											  else
											  if(j==26)
	  								  		  {
											   		   cn[i][j]=cn[i-1][0];
											   		   dn[i][j]=dn[i-1][0];
	   						                  }
	  								  		  else
							  	   			  {
	 				 								   cn[i][j]=cn[i-1][j+2];
					  								   dn[i][j]=dn[i-1][j+2];
											  }
			  						  }
					  }
   }
   /*for(i=0;i<16;i++)
   {
  				  cout<<"\n\nC"<<i+1<<"=";
  				  for(j=0;j<28;j++)
  				  cout<<cn[i].z[j];
   }  
   for(i=0;i<16;i++)
   {
 				 cout<<"\n\nD"<<i+1<<"=";
 				 for(j=0;j<28;j++)
 				 cout<<dn[i].z[j];
   }  
*/
   int nn,kn[16][56];
   for(nn=0;nn<16;nn++)//Joining CnDn to from Kn of 56 bit
   for(i=0;i<56;i++)
   {
 				 	if(i<28)
 				 	{
				  		 	kn[nn][i]=cn[nn][i];
			        }
		 			else
		 			{
		  	 		 		kn[nn][i]=dn[nn][i-28];
 					}
   }
   int pc2[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};//PC-2 Table
   int K[16][48];
   for(nn=0;nn<16;nn++)//Applying PC2 Table to produce 48 bit 16 K key 
   {
   //cout<<"\n\nK"<<nn+1<<"=";
   for(i=0;i<48;i++)
   {				 				 
    K[nn][i]=kn[nn][pc2[i]-1];
	//cout<<K[nn].c[i];
   }
   }
   int ip[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};//IP Table
   int p[64],l0[32],r0[32];
   //cout<<"\n\nP=";
   for(i=0;i<64;i++)//Applying Initial Permutation table on message
   {
	p[i]=ms[ip[i]-1];
	//cout<<p[i];
   }
   v=0;
   x=0;
   for(i=0;i<64;i++)//Dividing into two parts L0 & R0
   {
	 				 if(i<32)
	 				 l0[v++]=p[i];
	 				 else
	 				 r0[x++]=p[i];
   }
   /*cout<<"\n\nL0=";
   for(i=0;i<32;i++)
   cout<<l0[i];
   cout<<"\n\nR0=";
   for(i=0;i<32;i++)
   cout<<r0[i];
*/
   int ln[16][32],rn[16][32];
   int e[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};//E-Bit Selection Table
   int S[8][4][16]={{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,19,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
   {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
   {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
   {{7,13,14,3,0,6,9,10,1,2,8,5,11,15,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
   {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
   {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
   {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
   {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};//S-BOXES
   int P[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};//Permutation Table
   int s[8][6],k1,r,c,sb[32],no,f[32],ff,er[16][48],b[16][48];
   for(i=0;i<32;i++)
   sb[i]=0;
   for(ff=0;ff<16;ff++)//Conversion into L1-L16 & R1-R16
   {
			if(ff==0)
			{
			 		 //cout<<"\n\nL1=";
				   for(i=0;i<32;i++)
				   {
				   					ln[0][i]=r0[i];
									//cout<<ln[0][i];
			       }
				   for(i=0;i<48;i++)//Applying E-Bit selection table
 				   {
					                er[0][i]=r0[e[i]-1];
									b[0][i]=(K[0][i]+er[0][i])%2;//X-OR operation
			       }
				   k1=0;
				   for(i=0;i<8;i++)
				   for(j=0;j<6;j++)
				   s[i][j]=b[0][k1++];
				   v=1;
				   for(i=0;i<8;i++)//Using S Boxes
				   {
				   	                r=(2*s[i][0])+(s[i][5]);
 									c=(8*s[i][1])+(4*s[i][2])+(2*s[i][3])+(s[i][4]);
		  		        			v=4*(i+1);
				 					no=S[i][r][c];
				 					while(no>0)
				 					{
						 			 		   v--;
											   sb[v]=no%2;
											   no/=2;
							        }
			      }
				  for(i=0;i<32;i++)//Producing Function f by applying P table
 				  f[i]=sb[P[i]-1];
				  //cout<<"\n\nR1=";
				  for(i=0;i<32;i++)
				  {
				   				   rn[0][i]=(l0[i]+f[i])%2;
								   //cout<<rn[0].d[i];
			      }
	        }
			else
			{
 			 	  //cout<<"\n\nL"<<ff+1<<"=";
 				  for(i=0;i<32;i++)
				  {
				   				   ln[ff][i]=rn[ff-1][i];
								   //cout<<ln[ff][i];
			      }
				  for(i=0;i<48;i++)
 				  {
				   				   er[ff][i]=rn[ff-1][e[i]-1];
								   b[ff][i]=(K[ff][i]+er[ff][i])%2;
			      }
				  k1=0;
				  for(i=0;i<8;i++)
				  for(j=0;j<6;j++)
				  s[i][j]=b[ff][k1++];
				  for(i=0;i<32;i++)
				  sb[i]=0;
				  v=1;
				  for(i=0;i<8;i++)
				  {
 				   				  r=(2*s[i][0])+(s[i][5]);
 								  c=(8*s[i][1])+(4*s[i][2])+(2*s[i][3])+(s[i][4]);
 				        		  v=4*(i+1);
				 				  no=S[i][r][c];
				 				  while(no>0)
				 				  {
						 		   			 v--;
											 sb[v]=no%2;
											 no/=2;
					              }
				  }
				  for(i=0;i<32;i++)
 				  f[i]=sb[P[i]-1];
				  //cout<<"\n\nR"<<ff+1<<"=";
				  for(i=0;i<32;i++)
				  {
				   				   rn[ff][i]=(ln[ff-1][i]+f[i])%2;
								   //cout<<rn[ff].d[i];
			      }
	     }
    }
	int msd[64],IPin[64],IP[64]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};//Inverse Permutation Table
	//cout<<"\n\nR16L16=";
	for(i=0;i<64;i++)//Concatition of R16L16
	if(i<32)
 	msd[i]=rn[15][i];
  	else
 	msd[i]=ln[15][i-32];
	//cout<<"\n\nIP^(-1)=";
	for(i=0;i<64;i++)//Applying Inverse Permutation Table
 	{
		           IPin[i]=msd[IP[i]-1];
				   //cout<<IPin[i];
	}
 	int mn[16][4],kl=0,bnum;
 	char cvr[16];
 	for(i=0;i<16;i++)//Convertig the encrypted binary form into Hexadecimal form
 	{
	               bnum=0;
 				   for(j=0;j<4;j++)
 				   bnum=bnum+IPin[kl++]*pow(2,3-j);
				   if(bnum<10)
				   cvr[i]=bnum+48;
				   else 
				   cvr[i]=55+bnum;
    }
	cout<<"\n\nEncrpted Format is "<<cvr;
    getch();
	return 0;
}
void bin(int bnum,int i)
{
    while(bnum>0)
    {
    			i--;
       			m[i]=bnum%2;
          		bnum/=2;
	}
}

