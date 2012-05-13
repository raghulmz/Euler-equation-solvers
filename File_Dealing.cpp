#include "Function_Declaration.h"


string int2string(const int& number)
{
  ostringstream oss;
  oss << number;
  return oss.str();
}




void Write_Timestep()
{
  int x,y,z,c,d,i,j,k,number_cell;
  string name=WriteFolder;
  name +="Timesteps";
  name += int2string(Iter);
  name += ".vtk";
  char filename[1000];
  strcpy (filename,name.c_str());
  FILE *final = fopen( filename,"w" );
  
  x=x_cell-2;		y=y_cell-2;		z=z_cell-2;		number_cell=x*y*z;
  fprintf(final,"# vtk DataFile Version 2.0\nAshokEulerSolvers\nASCII\nDATASET STRUCTURED_GRID\nDIMENSIONS %d %d %d\n",x,y,z);
  fprintf(final,"POINTS %d float\n",number_cell);
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf  %5.16lf   %5.16lf\n",*(node_x+z),*(node_y+z),*(node_z+z));
      }
    }
  }

  fprintf(final,"\n\nPOINT_DATA %d \nSCALARS Pressure double\nLOOKUP_TABLE default\n",number_cell);
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.18lf\n",*(p_cell+z));
      }
    }
  }
  
  fprintf(final,"\n\nSCALARS Temperature double\nLOOKUP_TABLE default\n",number_cell);
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.15lf\n",*(t_cell+z));
      }
    }
  }
  
   fprintf(final,"\n\nSCALARS Density double\nLOOKUP_TABLE default\n",number_cell);
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.15lf\n",*(rho_cell+z));
      }
    }
  }
  
   fprintf(final,"\n\nSCALARS Mach double\nLOOKUP_TABLE default\n",number_cell);
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.15lf\n",*(mach+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS Velocity double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(u_cell+z),*(v_cell+z),*(w_cell+z));
      }
    }
  }
  
  
  /***********************Area Vectors**********************************//*
  fprintf(final,"\n\nVECTORS CellAreaFront double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_front_x+z),*(area_front_y+z),*(area_front_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellAreaBack double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_back_x+z),*(area_back_y+z),*(area_back_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellAreaTop double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_top_x+z),*(area_top_y+z),*(area_top_z+z));
      }
    }
  }
  fprintf(final,"\n\nVECTORS CellAreaBottom double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_bottom_x+z),*(area_bottom_y+z),*(area_bottom_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellArealeft double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_left_x+z),*(area_left_y+z),*(area_left_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellAreaRight double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(area_right_x+z),*(area_right_y+z),*(area_right_z+z));
      }
    }
  }
  
  *//**************************************************************************************/
  
  /***********************Normal Vectors**********************************/ /*
  fprintf(final,"\n\nVECTORS CellNormalFront double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_front_x+z),*(nor_front_y+z),*(nor_front_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellNormalBack double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_back_x+z),*(nor_back_y+z),*(nor_back_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellNormalTop double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_top_x+z),*(nor_top_y+z),*(nor_top_z+z));
      }
    }
  }
  fprintf(final,"\n\nVECTORS CellNormalBottom double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_bottom_x+z),*(nor_bottom_y+z),*(nor_bottom_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellNormalleft double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_left_x+z),*(nor_left_y+z),*(nor_left_z+z));
      }
    }
  }
  
  fprintf(final,"\n\nVECTORS CellNormalRight double\n");
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
	fprintf(final,"%5.16lf\t   %5.16lf\t   %5.16lf\n",*(nor_right_x+z),*(nor_right_y+z),*(nor_right_z+z));
      }
    }
  }
  */
  //**************************************************************************************/
  
  
  cout<<"\n\nFile Writing TimeSteps.vtk Over\t"<<Iter<<endl;
  fclose(final);
}

void Write_First_row ()
{
 int i,z;
 
 FILE *final = fopen( "./Data/scalars_1d.dat","w" );
  fclose(final);
  
 for (i=xy_cell+x_cell+1;i<=xy_cell+x_cell+x_cell-1;i++)
 {
   z=i;
   
   FILE *final = fopen( "./Data/scalars_1d.dat","a" );
   fprintf(final,"%5.15lf %5.15lf %5.15lf %5.15lf %i\n",*(node_x+z),*(p_cell+z),*(t_cell+z),*(rho_cell+z),z);
   fclose(final);
   
 }
  
  
}

void Read_grid_double_output ()
{
  int i,j,k,d,c,z;
  FILE *ipf = fopen("./Data/grid_double.dat", "r");;
  if (ipf == NULL) 
  {
    printf( "Can't open input file input!\n");
    
  }
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(j=1;j<y_cell-1;j++)
    {
      c=d+(x_cell*j);
      for(i=1;i<x_cell-1;i++)
      {
	z=i+c;
// 	cin(ipf)>>*(p_cell+z)>>*(t_cell+z)>>*(rho_cell+z)>>*(u_cell+z)>>*(v_cell+z)>>*(w_cell+z);
	printf("\n%5.15lf %5.15lf %5.15lf %5.15lf %5.15lf %5.15lf",*(p_cell+z),*(t_cell+z),*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
      }
    }
  }
  fclose(ipf);
}

void Read_grid_size()
{
 FILE *grid = fopen( "./Data/grid_size.dat","w" );
 fscanf(grid,"%i %i %i",&x_cell,&y_cell,&z_cell);
 x_cell=x_cell*2; y_cell=y_cell*2; z_cell=z_cell*2;
 printf("%i %i %i\n",x_cell,y_cell,z_cell);
 fclose(grid); 
  
}
void Write_grid_double_output ()
{
  int i,j,k,d,c,z,l,m,n;
  FILE *final = fopen( "./Data/grid_double.dat","w" );
  fclose(final);
  FILE *grid = fopen( "./Data/grid_size.dat","w" );
  fprintf(grid,"%i %i %i",x_cell-2,y_cell-2,z_cell-2);
  fclose(grid);
  
  for(k=1;k<z_cell-1;k++)
  {
    d=(xy_cell*k);
    for(l=1;l<=2;l++)
    {
      for(j=1;j<y_cell-1;j++)
      {
	c=d+(x_cell*j);
	for(l=1;l<=2;l++)
	{
	  for(i=1;i<x_cell-1;i++)
	  {
	    z=i+c;
	    for(l=1;l<=2;l++)
	    {
	      FILE *final = fopen( "./Data/grid_double.dat","a" );
	      fprintf(final,"%5.15lf %5.15lf %5.15lf %5.15lf %5.15lf %5.15lf\n",*(p_cell+z),*(t_cell+z),*(rho_cell+z),*(u_cell+z),*(v_cell+z),*(w_cell+z));
	      fclose(final);
	    }
	  }
	}
      }
    }
  }
  
}
