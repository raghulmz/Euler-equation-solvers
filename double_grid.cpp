#include "Function_Declaration.h"

double *node_x,*node_y,*node_z;
double *center_x,*center_y,*center_z;
double *volume;

double *nor_front_x,*nor_front_y,*nor_front_z;
double *nor_back_x,*nor_back_y,*nor_back_z;
double *nor_right_x,*nor_right_y,*nor_right_z;
double *nor_left_x,*nor_left_y,*nor_left_z;
double *nor_top_x,*nor_top_y,*nor_top_z;
double *nor_bottom_x,*nor_bottom_y,*nor_bottom_z;
double *mod_front,*mod_back,*mod_top,*mod_bottom,*mod_left,*mod_right;

double *area_front_x,*area_front_y,*area_front_z;
double *area_back_x,*area_back_y,*area_back_z;
double *area_right_x,*area_right_y,*area_right_z;
double *area_left_x,*area_left_y,*area_left_z;
double *area_top_x,*area_top_y,*area_top_z;
double *area_bottom_x,*area_bottom_y,*area_bottom_z;

double gama,R,L,B,H,dx,dy,dz,cfl,dtm,theta;
double *p_cell,*rho_cell,*t_cell,*u_cell,*v_cell,*w_cell,*mach,*a,*dt_cell;
int x_cell,y_cell,z_cell,xy_cell,xyz_cell,Iteration,Iter;
double p0,t0,mac;

double *Q1,*Q2,*Q3,*Q4,*Q5;	double *E1,*E2,*E3,*E4,*E5;	double *F1,*F2,*F3,*F4,*F5;	double *G1,*G2,*G3,*G4,*G5;
double *Q1_new,*Q2_new,*Q3_new,*Q4_new,*Q5_new;

double error_p,error_t,error_rho,error_u,error_v,error_w;
double p_exact,t_exact,rho_exact,u_exact,v_exact,w_exact;

int choice,extra;
string WriteFolder,ReadFolder;

int main()
{
  R=287.0;
  gama=1.4;
  L=2.5;
  B=0.1;
  H=1.5;
  
  cfl=0.25;
//   cout<<"\nGive CFL number ...?";
//   cin>>cfl;  
  
  
  ReadFolder.append("./Data/");
  WriteFolder.append("./Data/");
  FILE *final = fopen( "./Data/change.dat","w" );
  fclose(final);
  
//   cout<<"Give number of cells along x-directions   ......?";
//   cin>>x_cell;
//   cout<<"Give number of cells along y-directions   ......?";
//   cin>>y_cell;
//   cout<<"Give number of cells along z-directions   ......?";
//   cin>>z_cell;
//   x_cell=10;
//   y_cell=3;
//   z_cell=10;
  Read_grid_size();
//   Read_grid_size_single();
  x_cell+=2;    y_cell+=2;    z_cell+=2;
  
  
  xy_cell=x_cell*y_cell;
  xyz_cell=x_cell*y_cell*z_cell;
  
//   printf("%i\n",x_cell);
//   printf("%i\n",xy_cell);
//   printf("%i\n",xyz_cell);
  
  Allocate_Memory();  
  
//   Calculate_Nodes();
//   Calculate_Nodes_Compression_Ramp();
//   Calculate_Nodes_Compression_Expansion_Ramp();
//   Calculate_Nodes_Convergent_Duct();
  Calculate_Nodes_Circular_Arc();
//   Calculate_Nodes_Compression_Ramp_exponential_y();
  Calculate_cellcenter();
  Calculate_facenormal();
  Calculate_cellvolume();
  
  cout<<"Enter number of iterations ...?";
  cin>>Iteration;
//   Iteration=3;
  int k;
//   Initial_Condition();
  Read_grid_double_output ();
  
  for (k=0;k<=Iteration;k++)
  {
    Iter=k;
    
   if((k%1000)==0)
   {
      Write_Timestep();
      
//    Write_First_row ();
   }
   
    Boundary_Conditions_wall ();
//     Boundary_Conditions_subsonic_wall ();
    Calculate_Mach ();
    Calculate_Timestep ();
    Calculate_dt_min ();
    Calculate_Q ();
    Calculate_Fluxvectors ();
//     Calculate_Q_new ();
    Calculate_Q_new_avg ();
    Calculate_Primitive ();
    Calculate_Change ();
//     Calculate_error ();
//     Calculate_error_compression ();
    Extra_Iterations ();
  }
  Write_grid_double_output ();

  
//   Write_Timestep();
  return 0;
}