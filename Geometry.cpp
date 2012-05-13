#include "Function_Declaration.h"

void Calculate_Nodes()
{
  int i,j,k,d,c,z;
  
  dx=L/(x_cell-2);	dy=B/(y_cell-2);	dz=H/(z_cell-2);
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); *(node_z+z)=dz*(k-1);
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
}

void Calculate_Nodes_Compression_Ramp()
{
  int i,j,k,d,c,z;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);
//   theta=-15;
  cout<<"Enter theta ...?";
  cin>>theta;
  theta=(3.14/180.0)*theta;
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>=1.0)
	{
	  dz=(H-(tan(theta)*(*(node_x+z)-1)))/(z_cell-2);
	}
	else { dz=H/(z_cell-2); }
	*(node_z+z)=dz*(k-1);
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
}

void Calculate_cellcenter()
{
  int i,j,k,d,c,z;
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	*(center_x+z)=0.125*(*(node_x+z)+*(node_x+z+1)+*(node_x+z+1+x_cell)+*(node_x+z+x_cell)+*(node_x+z+xy_cell)+*(node_x+z+1+xy_cell)+*(node_x+z+1+x_cell+xy_cell)+*(node_x+z+x_cell+xy_cell));
	*(center_y+z)=0.125*(*(node_y+z)+*(node_y+z+1)+*(node_y+z+1+x_cell)+*(node_y+z+x_cell)+*(node_y+z+xy_cell)+*(node_y+z+1+xy_cell)+*(node_y+z+1+x_cell+xy_cell)+*(node_y+z+x_cell+xy_cell));
	*(center_z+z)=0.125*(*(node_z+z)+*(node_z+z+1)+*(node_z+z+1+x_cell)+*(node_z+z+x_cell)+*(node_z+z+xy_cell)+*(node_z+z+1+xy_cell)+*(node_z+z+1+x_cell+xy_cell)+*(node_z+z+x_cell+xy_cell));
	
// 	printf("\n\n%i , %i, %i, %i, %i\n",z,z,z+1,z+x_cell,z+xy_cell);
// 	printf("\n%lf , %lf ,%lf ",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("%lf , %lf ,%lf \n",*(node_x+z+1),*(node_y+z+x_cell),*(node_z+z+xy_cell));
// 	printf("\ncell center_x %lf",*(center_x+z));
// 	printf("\ncell center_y %lf",*(center_y+z));
// 	printf("\ncell center_z %lf",*(center_z+z));
      }
    }
  }

}
  
void Calculate_facenormal()
{
  int i,j,k,d,c,z;
  double val,d1_x,d1_y,d1_z,d2_x,d2_y,d2_z,mod_s;
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
// 	printf("\nz= %i",z);
	// Left Normal
	d2_x=*(node_x+z+x_cell+xy_cell)-*(node_x+z);
	d2_y=*(node_y+z+x_cell+xy_cell)-*(node_y+z);
	d2_z=*(node_z+z+x_cell+xy_cell)-*(node_z+z);
	
	d1_x=*(node_x+z+xy_cell)-*(node_x+z+x_cell);
	d1_y=*(node_y+z+xy_cell)-*(node_y+z+x_cell);
	d1_z=*(node_z+z+xy_cell)-*(node_z+z+x_cell);
	
	*(area_left_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_left_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_left_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_left_x+z),2)+pow(*(area_left_y+z),2)+pow(*(area_left_z+z),2));
	*(mod_left+z)=mod_s;
	*(nor_left_x+z)=*(area_left_x+z)/mod_s;
	*(nor_left_y+z)=*(area_left_y+z)/mod_s;
	*(nor_left_z+z)=*(area_left_z+z)/mod_s;
	
// 	printf("\nd1 :%lf, %lf, %lf ",d1_x,d1_y,d1_z);
// 	printf("\nd2 :%lf, %lf, %lf ",d2_x,d2_y,d2_z);
// 	
// 	printf("\nnor_left_x =%lf",*(nor_left_x+z));
// 	printf("\nnor_left_y =%lf",*(nor_left_y+z));
// 	printf("\nnor_left_z =%lf",*(nor_left_z+z));
// 	
// 	printf("\n mod = %lf",mod_s);
// 	
// 	printf("\narea_left_x =%lf",*(area_left_x+z));
// 	printf("\narea_left_y =%lf",*(area_left_y+z));
// 	printf("\narea_left_z =%lf\n\n",*(area_left_z+z));

	// Front Normal
	d1_x=*(node_x+z+1+xy_cell)-*(node_x+z);
	d1_y=*(node_y+z+1+xy_cell)-*(node_y+z);
	d1_z=*(node_z+z+1+xy_cell)-*(node_z+z);
	
	d2_x=*(node_x+z+xy_cell)-*(node_x+z+1);
	d2_y=*(node_y+z+xy_cell)-*(node_y+z+1);
	d2_z=*(node_z+z+xy_cell)-*(node_z+z+1);
	
	*(area_front_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_front_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_front_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_front_x+z),2)+pow(*(area_front_y+z),2)+pow(*(area_front_z+z),2));
	*(mod_front+z)=mod_s;
	*(nor_front_x+z)=*(area_front_x+z)/mod_s;
	*(nor_front_y+z)=*(area_front_y+z)/mod_s;
	*(nor_front_z+z)=*(area_front_z+z)/mod_s;
	
	// right Normal
	d2_x=*(node_x+z+1+xy_cell)-*(node_x+z+1+x_cell);
	d2_y=*(node_y+z+1+xy_cell)-*(node_y+z+1+x_cell);
	d2_z=*(node_z+z+1+xy_cell)-*(node_z+z+1+x_cell);
	
	d1_x=*(node_x+z+1+x_cell+xy_cell)-*(node_x+z+1);
	d1_y=*(node_y+z+1+x_cell+xy_cell)-*(node_y+z+1);
	d1_z=*(node_z+z+1+x_cell+xy_cell)-*(node_z+z+1);
	
	*(area_right_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_right_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_right_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_right_x+z),2)+pow(*(area_right_y+z),2)+pow(*(area_right_z+z),2));
	*(mod_right+z)=mod_s;
	*(nor_right_x+z)=*(area_right_x+z)/mod_s;
	*(nor_right_y+z)=*(area_right_y+z)/mod_s;
	*(nor_right_z+z)=*(area_right_z+z)/mod_s;
	
	// back Normal
	d1_x=*(node_x+z+x_cell+xy_cell)-*(node_x+z+1+x_cell);
	d1_y=*(node_y+z+x_cell+xy_cell)-*(node_y+z+1+x_cell);
	d1_z=*(node_z+z+x_cell+xy_cell)-*(node_z+z+1+x_cell);
	
	d2_x=*(node_x+z+1+x_cell+xy_cell)-*(node_x+z+x_cell);
	d2_y=*(node_y+z+1+x_cell+xy_cell)-*(node_y+z+x_cell);
	d2_z=*(node_z+z+1+x_cell+xy_cell)-*(node_z+z+x_cell);
	
	*(area_back_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_back_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_back_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_back_x+z),2)+pow(*(area_back_y+z),2)+pow(*(area_back_z+z),2));
	*(mod_back+z)=mod_s;
	*(nor_back_x+z)=*(area_back_x+z)/mod_s;
	*(nor_back_y+z)=*(area_back_y+z)/mod_s;
	*(nor_back_z+z)=*(area_back_z+z)/mod_s;
	
	// top Normal
	d1_x=*(node_x+z+1+xy_cell)-*(node_x+z+x_cell+xy_cell);
	d1_y=*(node_y+z+1+xy_cell)-*(node_y+z+x_cell+xy_cell);
	d1_z=*(node_z+z+1+xy_cell)-*(node_z+z+x_cell+xy_cell);
	
	d2_x=*(node_x+z+1+x_cell+xy_cell)-*(node_x+z+xy_cell);
	d2_y=*(node_y+z+1+x_cell+xy_cell)-*(node_y+z+xy_cell);
	d2_z=*(node_z+z+1+x_cell+xy_cell)-*(node_z+z+xy_cell);
	
	*(area_top_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_top_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_top_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_top_x+z),2)+pow(*(area_top_y+z),2)+pow(*(area_top_z+z),2));
	*(mod_top+z)=mod_s;
	*(nor_top_x+z)=*(area_top_x+z)/mod_s;
	*(nor_top_y+z)=*(area_top_y+z)/mod_s;
	*(nor_top_z+z)=*(area_top_z+z)/mod_s;
      
	// bottom Normal
	d1_x=*(node_x+z+x_cell)-*(node_x+z+1);
	d1_y=*(node_y+z+x_cell)-*(node_y+z+1);
	d1_z=*(node_z+z+x_cell)-*(node_z+z+1);
	
	d2_x=*(node_x+z+1+x_cell)-*(node_x+z);
	d2_y=*(node_y+z+1+x_cell)-*(node_y+z);
	d2_z=*(node_z+z+1+x_cell)-*(node_z+z);
	
	*(area_bottom_x+z)=0.5*((d1_y*d2_z)-(d1_z*d2_y));
	*(area_bottom_y+z)=0.5*((d1_z*d2_x)-(d1_x*d2_z));
	*(area_bottom_z+z)=0.5*((d1_x*d2_y)-(d1_y*d2_x));
	
	
	mod_s=sqrt(pow(*(area_bottom_x+z),2)+pow(*(area_bottom_y+z),2)+pow(*(area_bottom_z+z),2));
	*(mod_bottom+z)=mod_s;
	*(nor_bottom_x+z)=*(area_bottom_x+z)/mod_s;
	*(nor_bottom_y+z)=*(area_bottom_y+z)/mod_s;
	*(nor_bottom_z+z)=*(area_bottom_z+z)/mod_s;
      }
    }
  }
 
}

void Calculate_cellvolume()
{
  int i,j,k,d,c,z;
  
  double rmxfront,rmxback,rmxtop,rmxbottom,rmxleft,rmxright;
  double rmyfront,rmyback,rmytop,rmybottom,rmyleft,rmyright;
  double rmzfront,rmzback,rmztop,rmzbottom,rmzleft,rmzright;
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	
	rmxleft=0.25*(*(node_x+z)+*(node_x+z+xy_cell)+*(node_x+z+x_cell)+*(node_x+z+x_cell+xy_cell));
	rmxfront=0.25*(*(node_x+z)+*(node_x+z+xy_cell)+*(node_x+z+1)+*(node_x+z+1+xy_cell));
	rmxright=0.25*(*(node_x+z+1+x_cell)+*(node_x+z+1+x_cell+xy_cell)+*(node_x+z+1)+*(node_x+z+1+xy_cell));
	rmxback=0.25*(*(node_x+z+1+x_cell)+*(node_x+z+1+x_cell+xy_cell)+*(node_x+z+x_cell)+*(node_x+z+x_cell+xy_cell));
	rmxbottom=0.25*(*(node_x+z+1+x_cell)+*(node_x+z+1)+*(node_x+z+x_cell)+*(node_x+z));
	rmxtop=0.25*(*(node_x+z+xy_cell)+*(node_x+z+1+x_cell+xy_cell)+*(node_x+z+x_cell+xy_cell)+*(node_x+z+1+xy_cell));
	
	rmyleft=0.25*(*(node_y+z)+*(node_y+z+xy_cell)+*(node_y+z+x_cell)+*(node_y+z+x_cell+xy_cell));
	rmyfront=0.25*(*(node_y+z)+*(node_y+z+xy_cell)+*(node_y+z+1)+*(node_y+z+1+xy_cell));
	rmyright=0.25*(*(node_y+z+1+x_cell)+*(node_y+z+1+x_cell+xy_cell)+*(node_y+z+1)+*(node_y+z+1+xy_cell));
	rmyback=0.25*(*(node_y+z+1+x_cell)+*(node_y+z+1+x_cell+xy_cell)+*(node_y+z+x_cell)+*(node_y+z+x_cell+xy_cell));
	rmybottom=0.25*(*(node_y+z+1+x_cell)+*(node_y+z+1)+*(node_y+z+x_cell)+*(node_y+z));
	rmytop=0.25*(*(node_y+z+xy_cell)+*(node_y+z+1+x_cell+xy_cell)+*(node_y+z+x_cell+xy_cell)+*(node_y+z+1+xy_cell));
	
	rmzleft=0.25*(*(node_z+z)+*(node_z+z+xy_cell)+*(node_z+z+x_cell)+*(node_z+z+x_cell+xy_cell));
	rmzfront=0.25*(*(node_z+z)+*(node_z+z+xy_cell)+*(node_z+z+1)+*(node_z+z+1+xy_cell));
	rmzright=0.25*(*(node_z+z+1+x_cell)+*(node_z+z+1+x_cell+xy_cell)+*(node_z+z+1)+*(node_z+z+1+xy_cell));
	rmzback=0.25*(*(node_z+z+1+x_cell)+*(node_z+z+1+x_cell+xy_cell)+*(node_z+z+x_cell)+*(node_z+z+x_cell+xy_cell));
	rmzbottom=0.25*(*(node_z+z+1+x_cell)+*(node_z+z+1)+*(node_z+z+x_cell)+*(node_z+z));
	rmztop=0.25*(*(node_z+z+xy_cell)+*(node_z+z+1+x_cell+xy_cell)+*(node_z+z+x_cell+xy_cell)+*(node_z+z+1+xy_cell));
	
	*(volume+z)=0.3333*(  (rmxleft**(area_left_x+z))+(rmxright**(area_right_x+z))+(rmxtop**(area_top_x+z))+(rmxbottom**(area_bottom_x+z))+(rmxfront**(area_front_x+z))+(rmxback**(area_back_x+z))  );
	*(volume+z)=*(volume+z)+0.3333*(  (rmyleft**(area_left_y+z))+(rmyright**(area_right_y+z))+(rmytop**(area_top_y+z))+(rmybottom**(area_bottom_y+z))+(rmyfront**(area_front_y+z))+(rmyback**(area_back_y+z))  );
	*(volume+z)=*(volume+z)+0.3333*(  (rmzleft**(area_left_z+z))+(rmzright**(area_right_z+z))+(rmztop**(area_top_z+z))+(rmzbottom**(area_bottom_z+z))+(rmzfront**(area_front_z+z))+(rmzback**(area_back_z+z))  );
	
// 	printf("\nz = %i :volume = %lf",*(volume+z),z);
      }
    }
  }

  
}

void Calculate_Nodes_Compression_Expansion_Ramp()
{
  int i,j,k,d,c,z;
  L=2.5; B=0.1; H=2.0;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);
//   theta=-15;
  cout<<"Enter theta ...?";
  cin>>theta;
  theta=(3.14/180.0)*theta;
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>=0.5)
	{
	  if (*(node_x+z)>1.5)
	  {
	    dz=(H-tan(theta))/(z_cell-2);
	  }
	  else {dz=(H-(tan(theta)*(*(node_x+z)-0.5)))/(z_cell-2);}
	}
	else { dz=H/(z_cell-2); }
	*(node_z+z)=dz*(k-1);
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
}

void Calculate_Nodes_Convergent_Duct()
{
  int i,j,k,d,c,z;
  L=2.5; B=0.1; H=1.2;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);
//   theta=-15;
  cout<<"Enter theta ...?";
  cin>>theta;
  theta=(3.14/180.0)*theta;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);	dz=H/(z_cell-2);
  
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>=0.5)
	{
	  dz=(H- (2.0*(tan(theta)*(*(node_x+z)-0.5))) )/(z_cell-2);
// 	  printf("\n (tan(theta)*(*(node_x+z)-1)) = %lf \n",tan(theta)*(*(node_x+z)-0.5));
	  *(node_z+z)=(dz*(k-1))+(tan(theta)*(*(node_x+z)-0.5));
// 	  
	}
	else { dz=H/(z_cell-2); *(node_z+z)=dz*(k-1);}
	
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
  

}

void Calculate_Nodes_Circular_Arc()
{
  int i,j,k,d,c,z;
  L=2.0; B=0.1; H=1.0;
  double ramp_endn,ramp_startn,ramp_end,ramp_start,l,t,radius,theta1,theta2,sz;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);

  cout<<"\nCircular arc ...\n";
    
  ramp_start=0.75; ramp_end=1.5;
  t=0.04; l=(ramp_end-ramp_start)/2.0;
  radius=(t*t)+(l*l);
  radius-radius/(2.0*t);
  radius=sqrt(radius);
  
  theta1=-asin((radius-t)/radius);
//   printf("theta1 = %lf\n",theta1);
  theta2=asin((radius-t)/radius);
//   printf("theta2 = %lf\n",theta2);
  
  ramp_endn=radius*cos(theta2)+ramp_start+l;
  
  ramp_startn=ramp_start+l-radius*cos(theta2);
//   printf("RS = %lf\n",ramp_startn);
//   printf("RE = %lf\n",ramp_endn);
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>ramp_start && *(node_x+z)<ramp_end)
	{
// 	 nz++; 
	}
	if (*(node_x+z)>ramp_startn && *(node_x+z)<ramp_endn)
	{
	  theta=((*(node_x+z)-ramp_start-l)/radius);
	  theta=acos(theta);
	  sz=(radius*sin(theta))-radius+t;
// 	  printf("\nsz = %lf, x= %lf",sz,*(node_x);
	  dz=(H-sz)/(z_cell-2);
	  *(node_z+z)=(dz*(k-1));
// 	  
	}
	
	else { dz=H/(z_cell-2); *(node_z+z)=dz*(k-1);}
	
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
  

}

void Calculate_Nodes_Compression_Ramp_exponential_y()
{
  int i,j,k,d,c,z;
  double e=2.718281828,P;
  L=2.5; B=0.1; H=1.5;
  e=e*e;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);
//   theta=-15;
  cout<<"Enter theta ...?";
  cin>>theta;
  theta=(3.14/180.0)*theta;
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>=1.0)
	{
	  if (k>1)
	  {
	   P=( (pow(e,(k-1))-1.0)/(pow(e,(z_cell-2))-1.0) ); 
	  }
	  else {P=1;}
	  printf("\n P = %lf",P);
	  dz= P * ((H/P)-(tan(theta)*(*(node_x+z)-1))) /(z_cell-2);
	  
	  *(node_z+z)=dz*(k-1)+(tan(theta)*(*(node_x+z)-1.0));
	}
	else { dz=H/(z_cell-2); *(node_z+z)=dz*(k-1);}
	
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
}

void Calculate_Nodes_Convergent_Divergent_Duct()
{
  int i,j,k,d,c,z;
  L=3.0; B=0.1; H=1.2;
  double theta1,theta2,ramp_end,ramp_start;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);
//   theta=-15;
  cout<<"\nEnter convergent angle ...?";
  cin>>theta1;
  cout<<"\nEnter divergent angle ...?";
  cin>>theta2;
  theta1=(3.14/180.0)*theta1;
  theta2=(3.14/180.0)*theta2;
  
  ramp_start=0.25; ramp_end=1.0;
  dx=L/(x_cell-2);	dy=B/(y_cell-2);	dz=H/(z_cell-2);
  
  for(k=1;k<z_cell;k++)
  {
    d=(xy_cell*k);
        for(j=1;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell;i++)
      {
	z=i+c;
// 	printf("%i , %i ,%i \n",d,c,z);
// 	printf("\n%i , %i , %i",x_cell,y_cell,z_cell);
	*(node_x+z)=dx*(i-1); *(node_y+z)=dy*(j-1); 
	if (*(node_x+z)>=ramp_start && *(node_x+z)<=ramp_end)
	{
	  dz=(H- (2.0*(tan(theta1)*(*(node_x+z)-ramp_start))) )/(z_cell-2);
// 	  printf("\n (tan(theta)*(*(node_x+z)-1)) = %lf \n",tan(theta)*(*(node_x+z)-0.5));
	  *(node_z+z)=(dz*(k-1))+(tan(theta1)*(*(node_x+z)-ramp_start));
// 	  
	}
	else if (*(node_x+z)>=ramp_end)
	{
	  dz=(H- (2.0*( (tan(3.14-theta2)*(*(node_x+z)-ramp_end)) +(tan(theta1)*(ramp_end-ramp_start) )) ))/(z_cell-2);
// 	  printf("\n (tan(theta)*(*(node_x+z)-1)) = %lf \n",tan(theta)*(*(node_x+z)-0.5));
	  *(node_z+z)=(dz*(k-1))+( (tan(3.14-theta2)*(*(node_x+z)-ramp_end)) +(tan(theta1)*(ramp_end-ramp_start)) );
// 	  
	}
	else { dz=H/(z_cell-2); *(node_z+z)=dz*(k-1);}
	
// 	printf("%lf , %lf ,%lf \n",*(node_x+z),*(node_y+z),*(node_z+z));
// 	printf("\n%i , %i, %i, %i, %i\n\n",z,z,z+1,z+1+x_cell,z+x_cell);
      }
    }
  }
  

}