#include<iostream>
#include<cstdlib>
#include<cmath>
#include<time.h>
#include <sstream>
#include <cstring>
#include <string>
# include <fstream>
// # include <omp.h>

using namespace std;
using std::string;
/***********************************************************************************/
extern double *node_x,*node_y,*node_z;
extern double *center_x,*center_y,*center_z;
extern double *volume;

extern double *nor_front_x,*nor_front_y,*nor_front_z;
extern double *nor_back_x,*nor_back_y,*nor_back_z;
extern double *nor_right_x,*nor_right_y,*nor_right_z;
extern double *nor_left_x,*nor_left_y,*nor_left_z;
extern double *nor_top_x,*nor_top_y,*nor_top_z;
extern double *nor_bottom_x,*nor_bottom_y,*nor_bottom_z;

extern double *area_front_x,*area_front_y,*area_front_z;
extern double *area_back_x,*area_back_y,*area_back_z;
extern double *area_right_x,*area_right_y,*area_right_z;
extern double *area_left_x,*area_left_y,*area_left_z;
extern double *area_top_x,*area_top_y,*area_top_z;
extern double *area_bottom_x,*area_bottom_y,*area_bottom_z;

extern double *mod_front,*mod_back,*mod_top,*mod_bottom,*mod_left,*mod_right;

extern double gama,R,L,B,H,dx,dy,dz,cfl,dtm,theta;
extern double *p_cell,*rho_cell,*t_cell,*u_cell,*v_cell,*w_cell,*mach,*a,*dt_cell;
extern int x_cell,y_cell,z_cell,xy_cell,xyz_cell,Iteration,Iter;
extern double p0,t0,mac;

extern double *Q1,*Q2,*Q3,*Q4,*Q5;	extern double *E1,*E2,*E3,*E4,*E5;	extern double *F1,*F2,*F3,*F4,*F5;	extern double *G1,*G2,*G3,*G4,*G5;
extern double *Q1_new,*Q2_new,*Q3_new,*Q4_new,*Q5_new;

extern double error_p,error_t,error_rho,error_u,error_v,error_w;
extern double p_exact,t_exact,rho_exact,u_exact,v_exact,w_exact;

extern int choice,extra;
extern string WriteFolder,ReadFolder;
/***********************************************************************************/


/********************  Boundary Condition File  ************************************/
void Initial_Condition();
void Boundary_Conditions ();
void Boundary_Conditions_wall ();
void Boundary_Conditions_subsonic_wall ();
/***********************************************************************************/


/***************************  Tools  ***********************************************/
void Allocate_Memory();
void CheckMem();
void Extra_Iterations ();
/***********************************************************************************/


/********************************  File Dealing  ***********************************/
string int2string(const int& number);
void Write_Timestep();
void Print_Error ();
void Write_First_row ();
void Write_grid_single_output ();
void Write_grid_double_output ();
void Read_grid_size();
void Read_grid_size_single();
void Read_grid_double_output ();
/***********************************************************************************/


/********************* Geometry ****************************************************/
void Calculate_Nodes();
void Calculate_Nodes_Compression_Ramp();
void Calculate_Nodes_Compression_Expansion_Ramp();
void Calculate_Nodes_Convergent_Duct();
void Calculate_Nodes_Circular_Arc();
void Calculate_Nodes_Convergent_Divergent_Duct();
void Calculate_Nodes_Compression_Ramp_exponential_y();
void Calculate_cellcenter();
void Calculate_facenormal();
void Calculate_cellvolume();

/***********************************************************************************/

/***************************  Functions  *******************************************/
void Calculate_Q ();
void Calculate_Primitive ();
void Calculate_Fluxvectors ();
void Calculate_Mach ();
void Calculate_Timestep ();
void Calculate_dt_min ();
void Calculate_Q_new ();
void Calculate_Q_new_avg ();
void Calculate_Change ();
void Calculate_error ();
void Calculate_error_compression ();
/***********************************************************************************/