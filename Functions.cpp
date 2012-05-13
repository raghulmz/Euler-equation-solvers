#include "Function_Declaration.h"

void Calculate_Q () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Q\n");
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=0;i<x_cell;i++)
      {
	z=i+c;
	*(Q1+z)=*(rho_cell+z);
	*(Q2+z)=*(rho_cell+z)**(u_cell+z);
	*(Q3+z)=*(rho_cell+z)**(v_cell+z);
	*(Q4+z)=*(rho_cell+z)**(w_cell+z);
	*(Q5+z)= *(rho_cell+z)*(  ((R**(t_cell+z))/(gama-1)) + 0.5*(pow(*(u_cell+z),2)+pow(*(v_cell+z),2)+pow(*(w_cell+z),2))  );
// 	printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
// 	printf("\n%i , %f , %f , %f , %f , %f ",z,*(Q1+z),*(Q2+z),*(Q3+z),*(Q4+z),*(Q5+z));
	
      }
    }
  }
  
  
}

void Calculate_Primitive () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Primitive Variables\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	*(rho_cell+z)=*(Q1_new+z);
	*(u_cell+z)=*(Q2_new+z)/(*(Q1_new+z));
	*(v_cell+z)=*(Q3_new+z)/(*(Q1_new+z));
	*(w_cell+z)=*(Q4_new+z)/(*(Q1_new+z));
	*(t_cell+z)=((gama-1)/R) * (   (*(Q5_new+z)/(*(Q1_new+z)))  -  ( 0.5*(pow(*(u_cell+z),2)+pow(*(v_cell+z),2)+pow(*(w_cell+z),2)) )   );
	*(p_cell+z)=*(rho_cell+z)*R**(t_cell+z);
	
// 	printf("\n");	
// 	printf("\n %f , %f , %f , %f , %f , %f ",*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z),*(t_cell+z),*(p_cell+z));
	
      }
    }
  }
  
  
}

void Calculate_Fluxvectors () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Flux Vectors\n");
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      
      for(i=0;i<x_cell;i++)
      {
	z=c+i;
	double P,T;
	
	P=(gama-1) * (  *(Q5+z) - ( (pow(*(Q4+z),2)+pow(*(Q3+z),2)+pow(*(Q2+z),2)) / (2.0**(Q1+z)) )  );
	T=(gama-1) * (  ( *(Q5+z)/(*(Q1-z)) ) - ( (pow(*(Q4+z),2)+pow(*(Q3+z),2)+pow(*(Q2+z),2)) / ( 2.0* pow(*(Q1+z),2) ) )  );
	
	*(E1+z)=*(Q2+z);
	*(E2+z)=( pow(*(Q2+z),2) / (*(Q1+z)) ) + P;
	*(E3+z)=(*(Q2+z)**(Q3+z)) / (*(Q1+z));
	*(E4+z)=(*(Q2+z)**(Q4+z)) / (*(Q1+z));
	*(E5+z)=(*(Q2+z) / (*(Q1+z))) * (*(Q5+z)+P);
	
	*(F1+z)=*(Q3+z);
	*(F3+z)=( pow(*(Q3+z),2) / (*(Q1+z)) ) + P;
	*(F2+z)=(*(Q2+z)**(Q3+z)) / (*(Q1+z));
	*(F4+z)=(*(Q3+z)**(Q4+z)) / (*(Q1+z));
	*(F5+z)=(*(Q3+z) / (*(Q1+z))) * (*(Q5+z)+P);
	
	*(G1+z)=*(Q4+z);
	*(G4+z)=( pow(*(Q4+z),2) / (*(Q1+z)) ) + P;
	*(G3+z)=(*(Q4+z)**(Q3+z)) / (*(Q1+z));
	*(G2+z)=(*(Q2+z)**(Q4+z)) / (*(Q1+z));
	*(G5+z)=(*(Q4+z) / (*(Q1+z))) * (*(Q5+z)+P);
	
// 	printf("\n");
// 	printf("\n E %f , %f , %f , %f , %f ",*(E1+z),*(E2+z),*(E3+z),*(E4+z),*(E5+z));
// 	printf("\n F %f , %f , %f , %f , %f ",*(F1+z),*(F2+z),*(F3+z),*(F4+z),*(F5+z));
// 	printf("\n G %f , %f , %f , %f , %f ",*(G1+z),*(G2+z),*(G3+z),*(G4+z),*(G5+z));
      }
    }
  }
}

void Calculate_Timestep () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Timesteps\n");
//   printf("***************************");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
// 	printf("\nz = %i",z);
	double vnf,vnb,vnt,vnB,vnl,vnr;
	double wave_speed;
	
	vnf=(*(u_cell+z)**(nor_front_x+z))+(*(v_cell+z)**(nor_front_y+z))+(*(w_cell+z)**(nor_front_z+z));
	vnb=(*(u_cell+z)**(nor_back_x+z))+(*(v_cell+z)**(nor_back_y+z))+(*(w_cell+z)**(nor_back_z+z));
	vnt=(*(u_cell+z)**(nor_top_x+z))+(*(v_cell+z)**(nor_top_y+z))+(*(w_cell+z)**(nor_top_z+z));
	vnB=(*(u_cell+z)**(nor_bottom_x+z))+(*(v_cell+z)**(nor_bottom_y+z))+(*(w_cell+z)**(nor_bottom_z+z));
	vnl=(*(u_cell+z)**(nor_left_x+z))+(*(v_cell+z)**(nor_left_y+z))+(*(w_cell+z)**(nor_left_z+z));
	vnr=(*(u_cell+z)**(nor_right_x+z))+(*(v_cell+z)**(nor_right_y+z))+(*(w_cell+z)**(nor_right_z+z));
	
	wave_speed=  ( ( *(a+z) + vnf ) * *(mod_front+z) ) + ( ( *(a+z) + vnb ) * *(mod_back+z) )  + ( ( *(a+z) + vnt ) * *(mod_top+z) );
	wave_speed=wave_speed +  ( ( *(a+z) + vnB ) * *(mod_bottom+z) ) + ( ( *(a+z) + vnl ) * *(mod_left+z) )  + ( ( *(a+z) + vnr ) * *(mod_right+z) );
	
	*(dt_cell+z)= ( cfl**(volume+z) ) / wave_speed ;
	
// 	printf("\n%i dt = %5.15lf",z,*(dt_cell+z));
      }
    }
  }
  
  
}

void Calculate_Mach () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Mach Numbers\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
	
	double V;
	*(a+z)=sqrt((gama*R**(t_cell+z)));
	V=sqrt(pow(*(u_cell+z),2)+pow(*(v_cell+z),2)+pow(*(w_cell+z),2));
	*(mach+z)=V/(*(a+z));
// 	printf("\nmach = %lf",*(mach+z));
      }
    }
  }
  
  
}

void Calculate_dt_min () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating Min dt\n");
  dtm=*(dt_cell+xy_cell+x_cell+1);
//   printf("\n\n%i dtm = %lf\n",xy_cell+x_cell+1,dtm);
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
	
	if (dtm>*(dt_cell+z))
	{
	  dtm=*(dt_cell+z);
	}
// 	printf("\n%i dtm = %lf",z,dtm);
      }
    }
  }
//   printf("\ndtm = %lf",dtm);
for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
	*(dt_cell+z)=dtm;
      }
    }
  }
}

void Calculate_Q_new () 
{
  int i,j,k,d,c,z;
  double FndS1,FndS2,FndS3,FndS4,FndS5;
  double fr,ff,fl,ft,fb,fB;
  double e1,f1,g1;
//   printf("\n\nCalculating Q i+1\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
// 	printf("\n\n%i",z);
	e1=0.5*(*(E1+z)+*(E1+z+1)); f1=0.5*(*(F1+z)+*(F1+z+1)); g1=0.5*(*(G1+z)+*(G1+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E1+z)+*(E1+z-1)); f1=0.5*(*(F1+z)+*(F1+z-1)); g1=0.5*(*(G1+z)+*(G1+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E1+z+xy_cell)+*(E1+z)); f1=0.5*(*(F1+z+xy_cell)+*(F1+z)); g1=0.5*(*(G1+z+xy_cell)+*(G1+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E1+z-xy_cell)+*(E1+z)); f1=0.5*(*(F1+z-xy_cell)+*(F1+z)); g1=0.5*(*(G1-xy_cell+z)+*(G1+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E1+z-x_cell)+*(E1+z)); f1=0.5*(*(F1+z-x_cell)+*(F1+z)); g1=0.5*(*(G1+z-x_cell)+*(G1+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E1+z)+*(E1+z+x_cell)); f1=0.5*(*(F1+z)+*(F1+z+x_cell)); g1=0.5*(*(G1+z)+*(G1+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS1=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("\n\n%i FndS1 = %f",z,FndS1);
	
	e1=0.5*(*(E2+z)+*(E2+z+1)); f1=0.5*(*(F2+z)+*(F2+z+1)); g1=0.5*(*(G2+z)+*(G2+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E2+z)+*(E2+z-1)); f1=0.5*(*(F2+z)+*(F2+z-1)); g1=0.5*(*(G2+z)+*(G2+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E2+z+xy_cell)+*(E2+z)); f1=0.5*(*(F2+z+xy_cell)+*(F2+z)); g1=0.5*(*(G2+z+xy_cell)+*(G2+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E2+z-xy_cell)+*(E2+z)); f1=0.5*(*(F2+z-xy_cell)+*(F2+z)); g1=0.5*(*(G2-xy_cell+z)+*(G2+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E2+z-x_cell)+*(E2+z)); f1=0.5*(*(F2+z-x_cell)+*(F2+z)); g1=0.5*(*(G2+z-x_cell)+*(G2+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E2+z)+*(E2+z+x_cell)); f1=0.5*(*(F2+z)+*(F2+z+x_cell)); g1=0.5*(*(G2+z)+*(G2+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS2=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("   FndS2 = %f",z,FndS2);
	
	e1=0.5*(*(E3+z)+*(E3+z+1)); f1=0.5*(*(F3+z)+*(F3+z+1)); g1=0.5*(*(G3+z)+*(G3+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E3+z)+*(E3+z-1)); f1=0.5*(*(F3+z)+*(F3+z-1)); g1=0.5*(*(G3+z)+*(G3+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E3+z+xy_cell)+*(E3+z)); f1=0.5*(*(F3+z+xy_cell)+*(F3+z)); g1=0.5*(*(G3+z+xy_cell)+*(G3+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E3+z-xy_cell)+*(E3+z)); f1=0.5*(*(F3+z-xy_cell)+*(F3+z)); g1=0.5*(*(G3-xy_cell+z)+*(G3+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E3+z-x_cell)+*(E3+z)); f1=0.5*(*(F3+z-x_cell)+*(F3+z)); g1=0.5*(*(G3+z-x_cell)+*(G3+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E3+z)+*(E3+z+x_cell)); f1=0.5*(*(F3+z)+*(F3+z+x_cell)); g1=0.5*(*(G3+z)+*(G3+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS3=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("   FndS3 = %f",z,FndS3);
	
	e1=0.5*(*(E4+z)+*(E4+z+1)); f1=0.5*(*(F4+z)+*(F4+z+1)); g1=0.5*(*(G4+z)+*(G4+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E4+z)+*(E4+z-1)); f1=0.5*(*(F4+z)+*(F4+z-1)); g1=0.5*(*(G4+z)+*(G4+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E4+z+xy_cell)+*(E4+z)); f1=0.5*(*(F4+z+xy_cell)+*(F4+z)); g1=0.5*(*(G4+z+xy_cell)+*(G4+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E4+z-xy_cell)+*(E4+z)); f1=0.5*(*(F4+z-xy_cell)+*(F4+z)); g1=0.5*(*(G4-xy_cell+z)+*(G4+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E4+z-x_cell)+*(E4+z)); f1=0.5*(*(F4+z-x_cell)+*(F4+z)); g1=0.5*(*(G4+z-x_cell)+*(G4+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E4+z)+*(E4+z+x_cell)); f1=0.5*(*(F4+z)+*(F4+z+x_cell)); g1=0.5*(*(G4+z)+*(G4+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
	FndS4=fr+fl+ft+fB+ff+fb;
// 	printf("\n");
// 	printf("   FndS4 = %f",z,FndS4);
	
	e1=0.5*(*(E5+z)+*(E5+z+1)); f1=0.5*(*(F5+z)+*(F5+z+1)); g1=0.5*(*(G5+z)+*(G5+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E5+z)+*(E5+z-1)); f1=0.5*(*(F5+z)+*(F5+z-1)); g1=0.5*(*(G5+z)+*(G5+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E5+z+xy_cell)+*(E5+z)); f1=0.5*(*(F5+z+xy_cell)+*(F5+z)); g1=0.5*(*(G5+z+xy_cell)+*(G5+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E5+z-xy_cell)+*(E5+z)); f1=0.5*(*(F5+z-xy_cell)+*(F5+z)); g1=0.5*(*(G5-xy_cell+z)+*(G5+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E5+z-x_cell)+*(E5+z)); f1=0.5*(*(F5+z-x_cell)+*(F5+z)); g1=0.5*(*(G5+z-x_cell)+*(G5+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E5+z)+*(E5+z+x_cell)); f1=0.5*(*(F5+z)+*(F5+z+x_cell)); g1=0.5*(*(G5+z)+*(G5+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
	FndS5=fr+fl+ft+fB+ff+fb;
	
// 	printf("   FndS5 = %f",z,FndS5);
	
	*(Q1_new+z)= *(Q1+z) - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS1 );
	*(Q2_new+z)= *(Q2+z) - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS2 );
	*(Q3_new+z)= *(Q3+z) - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS3 );
	*(Q4_new+z)= *(Q4+z) - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS4 );
	*(Q5_new+z)= *(Q5+z) - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS5 );
	
// 	printf("\n %lf, %lf, %lf, %lf, %lf",*(Q1_new+z),*(Q2_new+z),*(Q3_new+z),*(Q4_new+z),*(Q5_new+z));
      }
    }
  }
  
  
}

void Calculate_Change ()
{
  int i,j,k,d,c,z;
  double Change=0.0;
  FILE *final = fopen( "./Data/change.dat","a" );
//   printf("\n\nCalculating Change\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	
	Change=Change+pow((*(Q1_new+z)-*(Q1+z)),2);
	Change=Change+pow((*(Q2_new+z)-*(Q2+z)),2);
	Change=Change+pow((*(Q3_new+z)-*(Q3+z)),2);
	Change=Change+pow((*(Q4_new+z)-*(Q4+z)),2);
	Change=Change+pow((*(Q5_new+z)-*(Q5+z)),2);
      }
    }
  }
  Change=sqrt(Change);
  printf("\n Iteration-%i   ",Iter);
  printf("Change = %5.15lf",Change);
  fprintf(final,"%i %5.15lf \n",Iter,Change);
  if (fabs(Change)<0.000000000001)
  {
    exit;
  }
  fclose(final);
}

void Calculate_Q_new_lax () 
{
  int i,j,k,d,c,z;
  double FndS1,FndS2,FndS3,FndS4,FndS5;
  double fr,ff,fl,ft,fb,fB;
  double e1,f1,g1;
  double q1,q2,q3,q4,q5;
//   printf("\n\nCalculating Q i+1\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
// 	printf("\n\n%i",z);
	e1=0.5*(*(E1+z)+*(E1+z+1)); f1=0.5*(*(F1+z)+*(F1+z+1)); g1=0.5*(*(G1+z)+*(G1+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E1+z)+*(E1+z-1)); f1=0.5*(*(F1+z)+*(F1+z-1)); g1=0.5*(*(G1+z)+*(G1+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E1+z+xy_cell)+*(E1+z)); f1=0.5*(*(F1+z+xy_cell)+*(F1+z)); g1=0.5*(*(G1+z+xy_cell)+*(G1+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E1+z-xy_cell)+*(E1+z)); f1=0.5*(*(F1+z-xy_cell)+*(F1+z)); g1=0.5*(*(G1-xy_cell+z)+*(G1+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E1+z-x_cell)+*(E1+z)); f1=0.5*(*(F1+z-x_cell)+*(F1+z)); g1=0.5*(*(G1+z-x_cell)+*(G1+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E1+z)+*(E1+z+x_cell)); f1=0.5*(*(F1+z)+*(F1+z+x_cell)); g1=0.5*(*(G1+z)+*(G1+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS1=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("\n\n%i FndS1 = %f",z,FndS1);
	
	e1=0.5*(*(E2+z)+*(E2+z+1)); f1=0.5*(*(F2+z)+*(F2+z+1)); g1=0.5*(*(G2+z)+*(G2+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E2+z)+*(E2+z-1)); f1=0.5*(*(F2+z)+*(F2+z-1)); g1=0.5*(*(G2+z)+*(G2+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E2+z+xy_cell)+*(E2+z)); f1=0.5*(*(F2+z+xy_cell)+*(F2+z)); g1=0.5*(*(G2+z+xy_cell)+*(G2+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E2+z-xy_cell)+*(E2+z)); f1=0.5*(*(F2+z-xy_cell)+*(F2+z)); g1=0.5*(*(G2-xy_cell+z)+*(G2+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E2+z-x_cell)+*(E2+z)); f1=0.5*(*(F2+z-x_cell)+*(F2+z)); g1=0.5*(*(G2+z-x_cell)+*(G2+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E2+z)+*(E2+z+x_cell)); f1=0.5*(*(F2+z)+*(F2+z+x_cell)); g1=0.5*(*(G2+z)+*(G2+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS2=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("   FndS2 = %f",z,FndS2);
	
	e1=0.5*(*(E3+z)+*(E3+z+1)); f1=0.5*(*(F3+z)+*(F3+z+1)); g1=0.5*(*(G3+z)+*(G3+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E3+z)+*(E3+z-1)); f1=0.5*(*(F3+z)+*(F3+z-1)); g1=0.5*(*(G3+z)+*(G3+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E3+z+xy_cell)+*(E3+z)); f1=0.5*(*(F3+z+xy_cell)+*(F3+z)); g1=0.5*(*(G3+z+xy_cell)+*(G3+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E3+z-xy_cell)+*(E3+z)); f1=0.5*(*(F3+z-xy_cell)+*(F3+z)); g1=0.5*(*(G3-xy_cell+z)+*(G3+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E3+z-x_cell)+*(E3+z)); f1=0.5*(*(F3+z-x_cell)+*(F3+z)); g1=0.5*(*(G3+z-x_cell)+*(G3+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E3+z)+*(E3+z+x_cell)); f1=0.5*(*(F3+z)+*(F3+z+x_cell)); g1=0.5*(*(G3+z)+*(G3+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
	
	FndS3=fr+fl+ft+fB+ff+fb;
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
// 	printf("   FndS3 = %f",z,FndS3);
	
	e1=0.5*(*(E4+z)+*(E4+z+1)); f1=0.5*(*(F4+z)+*(F4+z+1)); g1=0.5*(*(G4+z)+*(G4+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E4+z)+*(E4+z-1)); f1=0.5*(*(F4+z)+*(F4+z-1)); g1=0.5*(*(G4+z)+*(G4+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E4+z+xy_cell)+*(E4+z)); f1=0.5*(*(F4+z+xy_cell)+*(F4+z)); g1=0.5*(*(G4+z+xy_cell)+*(G4+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E4+z-xy_cell)+*(E4+z)); f1=0.5*(*(F4+z-xy_cell)+*(F4+z)); g1=0.5*(*(G4-xy_cell+z)+*(G4+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E4+z-x_cell)+*(E4+z)); f1=0.5*(*(F4+z-x_cell)+*(F4+z)); g1=0.5*(*(G4+z-x_cell)+*(G4+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E4+z)+*(E4+z+x_cell)); f1=0.5*(*(F4+z)+*(F4+z+x_cell)); g1=0.5*(*(G4+z)+*(G4+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
	FndS4=fr+fl+ft+fB+ff+fb;
// 	printf("\n");
// 	printf("   FndS4 = %f",z,FndS4);
	
	e1=0.5*(*(E5+z)+*(E5+z+1)); f1=0.5*(*(F5+z)+*(F5+z+1)); g1=0.5*(*(G5+z)+*(G5+z+1));
	fr=e1**(area_right_x+z)+f1**(area_right_y+z)+g1**(area_right_z+z);
	
	e1=0.5*(*(E5+z)+*(E5+z-1)); f1=0.5*(*(F5+z)+*(F5+z-1)); g1=0.5*(*(G5+z)+*(G5+z-1));
	fl=e1**(area_left_x+z)+f1**(area_left_y+z)+g1**(area_left_z+z);
	
	e1=0.5*(*(E5+z+xy_cell)+*(E5+z)); f1=0.5*(*(F5+z+xy_cell)+*(F5+z)); g1=0.5*(*(G5+z+xy_cell)+*(G5+z));
	ft=e1**(area_top_x+z)+f1**(area_top_y+z)+g1**(area_top_z+z);
	
	e1=0.5*(*(E5+z-xy_cell)+*(E5+z)); f1=0.5*(*(F5+z-xy_cell)+*(F5+z)); g1=0.5*(*(G5-xy_cell+z)+*(G5+z));
	fB=e1**(area_bottom_x+z)+f1**(area_bottom_y+z)+g1**(area_bottom_z+z);
	
	e1=0.5*(*(E5+z-x_cell)+*(E5+z)); f1=0.5*(*(F5+z-x_cell)+*(F5+z)); g1=0.5*(*(G5+z-x_cell)+*(G5+z));
	ff=e1**(area_front_x+z)+f1**(area_front_y+z)+g1**(area_front_z+z);
	
	e1=0.5*(*(E5+z)+*(E5+z+x_cell)); f1=0.5*(*(F5+z)+*(F5+z+x_cell)); g1=0.5*(*(G5+z)+*(G5+z+x_cell));
	fb=e1**(area_back_x+z)+f1**(area_back_y+z)+g1**(area_back_z+z);
// 	printf("\n%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,",fr,ff,fl,ft,fb,fB);
	FndS5=fr+fl+ft+fB+ff+fb;
	
// 	printf("   FndS5 = %f",z,FndS5);
	
	q1=0.16666666*( *(Q1+z-1)+*(Q1+z+1)+*(Q1+z+x_cell)+*(Q1+z-x_cell)+*(Q1+z+xy_cell)+*(Q1+z-xy_cell) );
	q2=0.16666666*( *(Q2+z-1)+*(Q2+z+1)+*(Q2+z+x_cell)+*(Q2+z-x_cell)+*(Q2+z+xy_cell)+*(Q2+z-xy_cell) );
	q3=0.16666666*( *(Q3+z-1)+*(Q3+z+1)+*(Q3+z+x_cell)+*(Q3+z-x_cell)+*(Q3+z+xy_cell)+*(Q3+z-xy_cell) );
	q4=0.16666666*( *(Q4+z-1)+*(Q4+z+1)+*(Q4+z+x_cell)+*(Q4+z-x_cell)+*(Q4+z+xy_cell)+*(Q4+z-xy_cell) );
	q5=0.16666666*( *(Q5+z-1)+*(Q5+z+1)+*(Q5+z+x_cell)+*(Q5+z-x_cell)+*(Q5+z+xy_cell)+*(Q5+z-xy_cell) );
// 	printf("\n%i , %f , %f , %f , %f , %f ",z,*(Q1+z),*(Q2+z),*(Q3+z),*(Q4+z),*(Q5+z));
	*(Q1_new+z)= q1 - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS1 );
	*(Q2_new+z)= q2 - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS2 );
	*(Q3_new+z)= q3 - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS3 );
	*(Q4_new+z)= q4 - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS4 );
	*(Q5_new+z)= q5 - ( ( *(dt_cell+z) / (*(volume+z)) ) * FndS5 );
// 	printf("\n %lf, %lf, %lf, %lf, %lf",q1,q2,q3,q4,q5);
// 	printf("\n %lf, %lf, %lf, %lf, %lf",*(Q1_new+z),*(Q2_new+z),*(Q3_new+z),*(Q4_new+z),*(Q5_new+z));
      }
    }
  }
  
  
}

void Calculate_error () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating error i+1\n");
  error_p=0;
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
	error_p+=pow(p_exact-*(p_cell+z),2);
	error_t+=pow(t_exact-*(t_cell+z),2);
	error_rho+=pow(rho_exact-*(rho_cell+z),2);
	error_u+=pow(u_exact-*(u_cell+z),2);
	error_v+=pow(v_exact-*(v_cell+z),2);
	error_w+=pow(w_exact-*(w_cell+z),2);
	
      }
    }
  }
  error_p=100*( sqrt(error_p)/(p_exact*xyz_cell) );
  error_t=100*( sqrt(error_t)/(t_exact*xyz_cell) );
  error_rho=100*( sqrt(error_rho)/(rho_exact*xyz_cell) );
  error_u=100*( sqrt(error_u)/(u_exact*xyz_cell) );
//   error_v=100*( sqrt(error_v)/(v_exact*xyz_cell) );
//   error_w=100*( sqrt(error_w)/(w_exact*xyz_cell) );
  if (Iter==0)
  {
    FILE *final = fopen( "./Data/error.dat","w" );
    fclose(final);
  }
  FILE *final = fopen( "./Data/error.dat","a" );
  fprintf(final,"%i %5.15lf %5.15lf %5.15lf %5.15lf %5.15lf\n",Iter,error_p,error_t,error_rho,error_u,error_v,error_w);
  fclose(final);
  
}

void Calculate_error_compression () 
{
  int i,j,k,d,c,z;
//   printf("\n\nCalculating error i+1\n");
  double p_exact1,t_exact1,rho_exact1,u_exact1;
  double p_exact2,t_exact2,rho_exact2,u_exact2;
  error_p=0;
  p_exact1=101325;
  p_exact2=146230;
  t_exact1=287;
  t_exact2=318.71;
  u_exact1=u_exact;
  u_exact2=951.88;
  rho_exact1=1.23013;
  rho_exact2=1.59864;
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=c+i;
	p_exact=p_exact1; 
	t_exact=t_exact1;
	rho_exact=rho_exact1;
	u_exact=u_exact1;
	
	if ( (*(node_z+z)-(tan(24.025/180)**(node_x+z))-1 )<0 )
	{
	 p_exact=p_exact2; 
	 t_exact=t_exact2;
	 rho_exact=rho_exact2;
	 u_exact=u_exact2;
	}
	
// 	printf("%i :%5.15lf %5.15lf %5.15lf \n",z,p_exact2,t_exact2,rho_exact2,u_exact2);
	error_p+=pow(p_exact-*(p_cell+z),2);
	error_t+=pow(t_exact-*(t_cell+z),2);
	error_rho+=pow(rho_exact-*(rho_cell+z),2);
	error_u+=pow(u_exact-*(u_cell+z),2);
	error_v+=pow(v_exact-*(v_cell+z),2);
	error_w+=pow(w_exact-*(w_cell+z),2);
	
      }
    }
  }
  error_p=100*( sqrt(error_p)/(p_exact*xyz_cell) );
  error_t=100*( sqrt(error_t)/(t_exact*xyz_cell) );
  error_rho=100*( sqrt(error_rho)/(rho_exact*xyz_cell) );
  error_u=100*( sqrt(error_u)/(u_exact*xyz_cell) );
//   error_v=100*( sqrt(error_v)/(v_exact*xyz_cell) );
//   error_w=100*( sqrt(error_w)/(w_exact*xyz_cell) );
  if (Iter==0)
  {
    FILE *final = fopen( "./Data/error.dat","w" );
    fclose(final);
  }
  FILE *final = fopen( "./Data/error.dat","a" );
  fprintf(final,"%i %5.15lf %5.15lf %5.15lf \n",Iter,error_p,error_t,error_rho/*,error_u,error_v,error_w*/);
  fclose(final);
  
}
