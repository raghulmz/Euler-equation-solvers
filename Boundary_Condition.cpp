#include "Function_Declaration.h"


void Initial_Condition()
{
  int i,j,k,d,c,z;
  
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      c=d+(x_cell*j);
      for(i=0;i<x_cell;i++)
      {
	z=i+c;
	*(p_cell+z)=101325.0;
	*(t_cell+z)=287.0;
	*(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
	*(u_cell+z)=0.0;
	*(v_cell+z)=0.0;
	*(w_cell+z)=0.0;
// 	printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      }
    }
  }
}

void Boundary_Conditions ()
{
  int i,j,k,d,c,z;
  mac=2.9;
  if (Iter==0)
  {
   printf("\n\nBoundary Conditions :supersonic inlet\n");
  }
//   cout<<"Enter Mach number at inlet   ......?";
//   cin>>mac;
  
  /******  Inlet *****/
  
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j);
      
      *(p_cell+z)=101325.0;
      *(t_cell+z)=287.0;
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=mac*( sqrt(gama*R**(t_cell+z)) );
      *(v_cell+z)=0.0;
      *(w_cell+z)=0.0;
//       printf("\n%i , rho = %lf , u = %lf",z,*(rho_cell+z),*(u_cell+z));
      
    }
  }
  /******  Outlet *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j)+x_cell-1;
      *(p_cell+z)=*(p_cell+z-1);
      *(t_cell+z)=*(t_cell+z-1);
      *(rho_cell+z)=*(rho_cell+z-1);
      *(u_cell+z)=*(u_cell+z-1);
      *(v_cell+z)=*(v_cell+z-1);
      *(w_cell+z)=*(w_cell+z-1);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }
  /******  Front Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d;
      *(p_cell+z)=*(p_cell+z+x_cell);
      *(t_cell+z)=*(t_cell+z+x_cell);
      *(rho_cell+z)=*(rho_cell+z+x_cell);
      *(u_cell+z)=*(u_cell+z+x_cell);
      *(v_cell+z)=*(v_cell+z+x_cell);
      *(w_cell+z)=*(w_cell+z+x_cell);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  /****** Back Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d+xy_cell-x_cell;
      
      *(p_cell+z)=*(p_cell+z-x_cell);
      *(t_cell+z)=*(t_cell+z-x_cell);
      *(rho_cell+z)=*(rho_cell+z-x_cell);
      *(u_cell+z)=*(u_cell+z-x_cell);
      *(v_cell+z)=*(v_cell+z-x_cell);
      *(w_cell+z)=*(w_cell+z-x_cell);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  
  /******  Top Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c+xyz_cell-xy_cell;
      
      *(p_cell+z)=*(p_cell+z-xy_cell);
      *(t_cell+z)=*(t_cell+z-xy_cell);
      *(rho_cell+z)=*(rho_cell+z-xy_cell);
      *(u_cell+z)=*(u_cell+z-xy_cell);
      *(v_cell+z)=*(v_cell+z-xy_cell);
      *(w_cell+z)=*(w_cell+z-xy_cell);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  /******  Bottom Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c;
      *(p_cell+z)=*(p_cell+z+xy_cell);
      *(t_cell+z)=*(t_cell+z+xy_cell);
      *(rho_cell+z)=*(rho_cell+z+xy_cell);
      *(u_cell+z)=*(u_cell+z+xy_cell);
      *(v_cell+z)=*(v_cell+z+xy_cell);
      *(w_cell+z)=*(w_cell+z+xy_cell);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }

//   for(z=0;z<=xy_cell;z++)
//   {
//     printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
//   }

  
}

void Boundary_Conditions_wall ()
{
  int i,j,k,d,c,z;
//   mac=2.9;
    
  if (Iter==0)
  {
   printf("\n\nBoundary Conditions : Wall with supersonic inlet\n");
   cout<<"\nEnter Mach number at inlet   ......\n?";
   cin>>mac;
  }
  
  /******  Inlet *****/
  
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j);
      
      *(p_cell+z)=101325.0;
      *(t_cell+z)=287.0;
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=mac*( sqrt(gama*R**(t_cell+z)) );
      *(v_cell+z)=0.0;
      *(w_cell+z)=0.0;
//       printf("\n%i , rho = %lf , u = %lf",z,*(rho_cell+z),*(u_cell+z));
      if ( Iter==0 && z==0 )
      {
	p_exact=*(p_cell+z);t_exact=*(t_cell+z);rho_exact=*(rho_cell+z);u_exact=*(u_cell+z);v_exact=*(v_cell+z);w_exact=*(w_cell+z);
// 	printf("\n\np_exact = %lf,t_exact = %lf,rho_exact = %lf,u_exact = %lf,v_exact = %lf,w_exact = %lf\n",p_exact,t_exact,rho_exact,u_exact,v_exact,w_exact);
      }
    }
  }
  /******  Outlet *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j)+x_cell-1;
      *(p_cell+z)=*(p_cell+z-1);
      *(t_cell+z)=*(t_cell+z-1);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-1);
      *(v_cell+z)=*(v_cell+z-1);
      *(w_cell+z)=*(w_cell+z-1);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }
  /******  Front Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d;
      *(p_cell+z)=*(p_cell+z+x_cell);
      *(t_cell+z)=*(t_cell+z+x_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      
      *(u_cell+z)=*(u_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_x+z+x_cell));
      *(v_cell+z)=*(v_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_y+z+x_cell));
      *(w_cell+z)=*(w_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_z+z+x_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z+x_cell),*(u_cell+z+x_cell),*(v_cell+z+x_cell),*(w_cell+z+x_cell));
//       printf("\n%i , rho = %lf , delu = %lf , delv = %lf , delw = %lf ,\n",z,*(rho_cell+z+x_cell),*(u_cell+z+x_cell)+*(u_cell+z),*(v_cell+z+x_cell)+*(v_cell+z),*(w_cell+z+x_cell)+*(w_cell+z));
    }
  }
  /****** Back Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d+xy_cell-x_cell;
      
      *(p_cell+z)=*(p_cell+z-x_cell);
      *(t_cell+z)=*(t_cell+z-x_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_x+z-x_cell));
      *(v_cell+z)=*(v_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_y+z-x_cell));
      *(w_cell+z)=*(w_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_z+z-x_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  
  /******  Top Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c+xyz_cell-xy_cell;
      
      *(p_cell+z)=*(p_cell+z-xy_cell);
      *(t_cell+z)=*(t_cell+z-xy_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_x+z-xy_cell));
      *(v_cell+z)=*(v_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_y+z-xy_cell));
      *(w_cell+z)=*(w_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_z+z-xy_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  /******  Bottom Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c;
      *(p_cell+z)=*(p_cell+z+xy_cell);
      *(t_cell+z)=*(t_cell+z+xy_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_x+z+xy_cell));
      *(v_cell+z)=*(v_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_y+z+xy_cell));
      *(w_cell+z)=*(w_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_z+z+xy_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }

//   for(z=0;z<=xy_cell;z++)
//   {
//     printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
//   }
  
}

void Boundary_Conditions_subsonic_wall ()
{
  int i,j,k,d,c,z;
//   mac=0.5;
  
  
  /******  Inlet *****/
  if (Iter==0)
  {
    printf("\n\nBoundary Conditions : Wall with subsonic inlet\n");
    cout<<"\nEnter Mach number at inlet   ......\n?";
    cin>>mac;
    p0=*(p_cell) * pow( (1+( ((gama-1)/gama) *mac*mac )),(gama/(gama-1)) );
    t0=300;
//     printf("\np0 = %lf\n",p0);
//     printf("\nt0 = %lf\n",t0);
  }
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j);
      
      *(v_cell+z)=0.0;
      *(w_cell+z)=0.0;
      *(t_cell+z)=t0 - ( ((gama-1)/(gama*R)) * 0.5 * (pow(*(u_cell+z),2)+pow(*(v_cell+z),2)+pow(*(w_cell+z),2)) );
      *(u_cell+z)=mac*sqrt(gama*R**(t_cell+z));
//       printf("\n t_cell = %f",*(t_cell+z));
      *(p_cell+z)=p0* pow((*(t_cell)/t0),(gama/(gama-1)));
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
     
//       printf("\n%i , rho = %lf , u = %lf",z,*(rho_cell+z),*(u_cell+z));
      
    }
  }
  /******  Outlet *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(j=0;j<y_cell;j++)
    {
      z=d+(x_cell*j)+x_cell-1;
      *(p_cell+z)=101325;
      *(t_cell+z)=*(t_cell+z-1);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-1);
      *(v_cell+z)=*(v_cell+z-1);
      *(w_cell+z)=*(w_cell+z-1);
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }
  /******  Front Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d;
      *(p_cell+z)=*(p_cell+z+x_cell);
      *(t_cell+z)=*(t_cell+z+x_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      
      *(u_cell+z)=*(u_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_x+z+x_cell));
      *(v_cell+z)=*(v_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_y+z+x_cell));
      *(w_cell+z)=*(w_cell+z+x_cell)-(2.0*(*(u_cell+z+x_cell)**(nor_front_x+z+x_cell)+*(v_cell+z+x_cell)**(nor_front_y+z+x_cell)+*(w_cell+z+x_cell)**(nor_front_z+z+x_cell))**(nor_front_z+z+x_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z+x_cell),*(u_cell+z+x_cell),*(v_cell+z+x_cell),*(w_cell+z+x_cell));
//       printf("\n%i , rho = %lf , delu = %lf , delv = %lf , delw = %lf ,\n",z,*(rho_cell+z+x_cell),*(u_cell+z+x_cell)+*(u_cell+z),*(v_cell+z+x_cell)+*(v_cell+z),*(w_cell+z+x_cell)+*(w_cell+z));
    }
  }
  /****** Back Wall *****/
  for(k=0;k<z_cell;k++)
  {
    d=(xy_cell*k);
    for(i=0;i<x_cell;i++)
    {
      z=i+d+xy_cell-x_cell;
      
      *(p_cell+z)=*(p_cell+z-x_cell);
      *(t_cell+z)=*(t_cell+z-x_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_x+z-x_cell));
      *(v_cell+z)=*(v_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_y+z-x_cell));
      *(w_cell+z)=*(w_cell+z-x_cell)-(2.0*(*(u_cell+z-x_cell)**(nor_back_x+z-x_cell)+*(v_cell+z-x_cell)**(nor_back_y+z-x_cell)+*(w_cell+z-x_cell)**(nor_back_z+z-x_cell))**(nor_back_z+z-x_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  
  /******  Top Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c+xyz_cell-xy_cell;
      
      *(p_cell+z)=*(p_cell+z-xy_cell);
      *(t_cell+z)=*(t_cell+z-xy_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_x+z-xy_cell));
      *(v_cell+z)=*(v_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_y+z-xy_cell));
      *(w_cell+z)=*(w_cell+z-xy_cell)-(2.0*(*(u_cell+z-xy_cell)**(nor_top_x+z-xy_cell)+*(v_cell+z-xy_cell)**(nor_top_y+z-xy_cell)+*(w_cell+z-xy_cell)**(nor_top_z+z-xy_cell))**(nor_top_z+z-xy_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      
    }
  }
  /******  Bottom Wall *****/
  for(j=0;j<y_cell;j++)
  {
    c=(x_cell*j);
    for(i=0;i<x_cell;i++)
    {
      z=i+c;
      *(p_cell+z)=*(p_cell+z+xy_cell);
      *(t_cell+z)=*(t_cell+z+xy_cell);
      *(rho_cell+z)=*(p_cell+z)/(R**(t_cell+z));
      *(u_cell+z)=*(u_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_x+z+xy_cell));
      *(v_cell+z)=*(v_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_y+z+xy_cell));
      *(w_cell+z)=*(w_cell+z+xy_cell)-(2.0*(*(u_cell+z+xy_cell)**(nor_bottom_x+z+xy_cell)+*(v_cell+z+xy_cell)**(nor_bottom_y+z+xy_cell)+*(w_cell+z+xy_cell)**(nor_bottom_z+z+xy_cell))**(nor_bottom_z+z+xy_cell));
//       printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
    }
  }

//   for(z=0;z<=xy_cell;z++)
//   {
//     printf("\n%i , rho = %lf , u = %lf , v = %lf , w = %lf ,",z,*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
//   }

  
}