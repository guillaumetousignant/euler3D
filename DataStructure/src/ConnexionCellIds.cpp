#ifndef DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP
#define DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP

#include "BoundaryCellIds.h"
#include "ConnexionCellIds.h"

#include <iostream>

void ConnexionCellIds::updateBoundary()
{
	std::cout<<"Connexion cells updated" << std::endl;
}

ConnexionCellIds::ConnexionCellIds()
{
std::ifstream myfile(Topology);
char str_temp[200];
std::string line;
std::string other_block_id_temp;
std::string cell_type_temp;
int i,j,k,n1,n2,n3,n4;

if (myfile.is_open())
{
   for(i=0;i<n_blocks_;i++)
   {
   	if(i==block_id_-1)
   	{
   		getline(myfile, line);
   		scanf (line.c_str(), "%s",str_temp);
   		block_file_=str_temp;
   	}
   	else
   	{
   		getline(myfile, line);
   	}
   }


   for(i=0;i<n_blocks_;i++)
   {
   	getline(myfile, line);
   	scanf (line.c_str(), "%s %d",str_temp,n1);
   	getline(myfile, line);
   	getline(myfile, line);
    getline(myfile, line);
    getline(myfile, line);
    scanf (line.c_str(), "%s %d",str_temp,n2);

   	for(j=0;j<n2;j++)
   	{
   		getline(myfile, line);
   	}

   	getline(myfile, line);
   	getline(myfile, line);
    scanf (line.c_str(), "%s %d",str_temp,n2);

   	for(j=0;j<n2;j++)
   	{
   		getline(myfile, line);
   	}


   	getline(myfile, line); //à enlever éventuellement
   	getline(myfile, line);
    scanf (line.c_str(), "%s %d",str_temp,n2);  //nb de block connecté
   
   	for(j=0;j<n2;j++)
   	{
   		getline(myfile, line);
   		scanf (line.c_str(), "%s %d",str_temp,n3); //block connecté au block i
   		getline(myfile, line);
   		scanf (line.c_str(), "%s %d",str_temp,n4); //nb d'élems connectés
   		if(i==block_id_-1)
   		{
   			for(k=0;k<n4;k++)
   			{
   				getline(myfile, other_block_id_temp);
   				scanf (line.c_str(), "%s", cell_type_temp);

   				BLOCK_ETRANGER[]

   					if (cell_type == "9") // tetrahede
					{

					}


   			}
   		}
   		else
   		{
   			for(k=0;k<n4;k++)
   			{
   				getline(myfile, line);
   			}
   		}	


   		if(i==block_id_-1)
   		{
   			break;
   		}

   	}





   }
}
else if (myfile.fail())
{
cerr << "fail opening topology file " << meshFileName << endl;
}




}

ConnexionCellIds::~ConnexionCellIds(){
    if (cell_ids_in_boundary_other_block_ != nullptr){
        delete [] cell_ids_in_boundary_other_block_;
    }
}

#endif