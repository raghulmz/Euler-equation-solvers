#include "Function_Declaration.h"


void Allocate_Memory()
{
  p_cell=(double*)malloc(sizeof(double)*xyz_cell);		t_cell=(double*)malloc(sizeof(double)*xyz_cell);
  u_cell=(double*)malloc(sizeof(double)*xyz_cell);		rho_cell=(double*)malloc(sizeof(double)*xyz_cell);
  v_cell=(double*)malloc(sizeof(double)*xyz_cell);		w_cell=(double*)malloc(sizeof(double)*xyz_cell);
  mach=(double*)malloc(sizeof(double)*xyz_cell);		a=(double*)malloc(sizeof(double)*xyz_cell);
  dt_cell=(double*)malloc(sizeof(double)*xyz_cell);
    
  node_x=(double*)malloc(sizeof(double)*xyz_cell); 		node_y=(double*)malloc(sizeof(double)*xyz_cell); 		node_z=(double*)malloc(sizeof(double)*xyz_cell);
  center_x=(double*)malloc(sizeof(double)*xyz_cell); 		center_y=(double*)malloc(sizeof(double)*xyz_cell); 		center_z=(double*)malloc(sizeof(double)*xyz_cell);

  nor_front_x=(double*)malloc(sizeof(double)*xyz_cell); 	nor_front_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_front_z=(double*)malloc(sizeof(double)*xyz_cell);
  nor_back_x=(double*)malloc(sizeof(double)*xyz_cell); 		nor_back_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_back_z=(double*)malloc(sizeof(double)*xyz_cell);
  nor_right_x=(double*)malloc(sizeof(double)*xyz_cell); 	nor_right_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_right_z=(double*)malloc(sizeof(double)*xyz_cell);
  nor_left_x=(double*)malloc(sizeof(double)*xyz_cell); 		nor_left_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_left_z=(double*)malloc(sizeof(double)*xyz_cell);
  nor_top_x=(double*)malloc(sizeof(double)*xyz_cell); 		nor_top_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_top_z=(double*)malloc(sizeof(double)*xyz_cell);
  nor_bottom_x=(double*)malloc(sizeof(double)*xyz_cell); 	nor_bottom_y=(double*)malloc(sizeof(double)*xyz_cell); 		nor_bottom_z=(double*)malloc(sizeof(double)*xyz_cell);
  
  mod_front=(double*)malloc(sizeof(double)*xyz_cell);	mod_back=(double*)malloc(sizeof(double)*xyz_cell);
  mod_top=(double*)malloc(sizeof(double)*xyz_cell);	mod_bottom=(double*)malloc(sizeof(double)*xyz_cell);
  mod_left=(double*)malloc(sizeof(double)*xyz_cell);	mod_right=(double*)malloc(sizeof(double)*xyz_cell);
  
  area_front_x=(double*)malloc(sizeof(double)*xyz_cell); 	area_front_y=(double*)malloc(sizeof(double)*xyz_cell); 		area_front_z=(double*)malloc(sizeof(double)*xyz_cell);
  area_back_x=(double*)malloc(sizeof(double)*xyz_cell); 	area_back_y=(double*)malloc(sizeof(double)*xyz_cell); 		area_back_z=(double*)malloc(sizeof(double)*xyz_cell);
  area_right_x=(double*)malloc(sizeof(double)*xyz_cell); 	area_right_y=(double*)malloc(sizeof(double)*xyz_cell); 		area_right_z=(double*)malloc(sizeof(double)*xyz_cell);
  area_left_x=(double*)malloc(sizeof(double)*xyz_cell); 	area_left_y=(double*)malloc(sizeof(double)*xyz_cell); 		area_left_z=(double*)malloc(sizeof(double)*xyz_cell);
  area_top_x=(double*)malloc(sizeof(double)*xyz_cell); 		area_top_y=(double*)malloc(sizeof(double)*xyz_cell); 		area_top_z=(double*)malloc(sizeof(double)*xyz_cell);
  area_bottom_x=(double*)malloc(sizeof(double)*xyz_cell); 	area_bottom_y=(double*)malloc(sizeof(double)*xyz_cell); 	area_bottom_z=(double*)malloc(sizeof(double)*xyz_cell);
  volume=(double*)malloc(sizeof(double)*xyz_cell);

  Q1=(double*)malloc(sizeof(double)*xyz_cell);	Q2=(double*)malloc(sizeof(double)*xyz_cell);	Q3=(double*)malloc(sizeof(double)*xyz_cell);
  Q4=(double*)malloc(sizeof(double)*xyz_cell);	Q5=(double*)malloc(sizeof(double)*xyz_cell);
  
  E1=(double*)malloc(sizeof(double)*xyz_cell);	E2=(double*)malloc(sizeof(double)*xyz_cell);	E3=(double*)malloc(sizeof(double)*xyz_cell);
  E4=(double*)malloc(sizeof(double)*xyz_cell);	E5=(double*)malloc(sizeof(double)*xyz_cell);
  
  F1=(double*)malloc(sizeof(double)*xyz_cell);	F2=(double*)malloc(sizeof(double)*xyz_cell);	F3=(double*)malloc(sizeof(double)*xyz_cell);
  F4=(double*)malloc(sizeof(double)*xyz_cell);	F5=(double*)malloc(sizeof(double)*xyz_cell);
  
  G1=(double*)malloc(sizeof(double)*xyz_cell);	G2=(double*)malloc(sizeof(double)*xyz_cell);	G3=(double*)malloc(sizeof(double)*xyz_cell);
  G4=(double*)malloc(sizeof(double)*xyz_cell);	G5=(double*)malloc(sizeof(double)*xyz_cell);
  
  Q1_new=(double*)malloc(sizeof(double)*xyz_cell);	Q2_new=(double*)malloc(sizeof(double)*xyz_cell);
  Q3_new=(double*)malloc(sizeof(double)*xyz_cell);	Q4_new=(double*)malloc(sizeof(double)*xyz_cell);
  Q5_new=(double*)malloc(sizeof(double)*xyz_cell);
  
  CheckMem();
}

void CheckMem()
{
  if(p_cell==0||t_cell==0||rho_cell==0||u_cell==0||v_cell==0||w_cell==0)
  {
    cout<<"***************No Space***********************"<<endl;
  }
}

void Extra_Iterations ()
{
  if (Iter==Iteration-1)
   {
    cout<<"\nDo you want to continue yes =1, no =2 ...?";
    cin>>choice;
    if (choice==1)
    {
    cout<<"\nEnter number of iterations ...\n";
    cin>>extra;
    Iteration+=extra;
    }
   }
}


