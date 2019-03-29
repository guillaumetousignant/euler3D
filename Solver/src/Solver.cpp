#ifndef SOLVERSKELETON_SRC_SOLVER_CPP
#define SOLVERSKELETON_SRC_SOLVER_CPP

#include "Block.h"
#include "CompleteMesh.h"
#include "Timestep.h"
#include "RungeKutta.h"
#include "Solver.h"
#include "PostProcessing.h"

//#include <chrono> // for high resolution clock
#include <string>
#include <iostream>
using namespace std;

Solver::Solver(double gamma, double cfl, int stage_number, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice, int n_blocks, int max_iter, double convergence_criterion, double cmac, double aoa_deg, double mach_aircraft, double omega, double k)
{
	gamma_=gamma;
	timestep_= new Timestep(gamma, cfl);
	runge_kutta_= new RungeKutta(gamma, stage_number, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice,residual_smoother_choice, omega, k);
	post_processing_= new PostProcessing( n_blocks, max_iter, convergence_criterion, cmac, mach_aircraft, aoa_deg, gamma);
}


Solver::~Solver()
{

}

Solver::Solver()
{
	timestep_=NULL;
	runge_kutta_=NULL;
}

void Solver::solve(Block* block, CompleteMesh* complete_mesh)
{
	/*
	while (true)
	{
	cout<<"Exécution solve: "<<endl;
	this->saveW0(block);
	cout<<endl<<"\tDans Timestep"<<endl;
	timestep_->computeSpectralRadius(block);
	timestep_->computeTimestep(block);
	cout<<"\tFin Timestep"<<endl;
	cout<<endl<<"\tDans RungeKutta"<<endl;
	runge_kutta_->computeRungeKutta(block);
	cout<<"\tFin RungeKutta"<<endl;
	post_processing_->process(block, complete_mesh);
	cout<<"Fin de l'Exécution solve"<<endl;
	}
	*/


	// PROVISOIRE!!!!
	while(!post_processing_->stop_solver_)
	{
		this->saveW0(block);
		timestep_->computeSpectralRadius(block);
		timestep_->computeTimestep(block);
		runge_kutta_->computeRungeKutta(block);
		post_processing_->computeFlowData(block);
			        //record end time
        //auto finish = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<double> elapsed = finish - start;
        //std::cout << "Elapsed time:" << elapsed.count() << " seconde\n";
		post_processing_->process(block, complete_mesh);
		//cout<<"Iter: "<<i<<endl;
	}



	/*
	// TEST GRADIENT
	// initialize field of pp
	int n_all_cells_in_block= block -> n_all_cells_in_block_;

	double x;
	double y;
	double z;

	for (int all_cell_idx = 0; all_cell_idx < n_all_cells_in_block; all_cell_idx++)
	{
		x=block->block_cells_[all_cell_idx]->cell_coordinates_[0];
		y=block->block_cells_[all_cell_idx]->cell_coordinates_[1];
		z=block->block_cells_[all_cell_idx]->cell_coordinates_[2];


		block->block_primitive_variables_->ro_[all_cell_idx] =1*x+2*y+3*z;
		block->block_primitive_variables_->uu_[all_cell_idx] =4*x+5*y+6*z;
		block->block_primitive_variables_->vv_[all_cell_idx] =7*x+8*y+9*z;
		block->block_primitive_variables_->ww_[all_cell_idx] =10*x+11*y+12*z;
		block->block_primitive_variables_->pp_[all_cell_idx] =13*x+14*y+15*z;
	}

	Gradient* gradient=new LeastSquares();
	gradient->computeGradients(block);


	for (int all_cell_idx = 0; all_cell_idx < n_all_cells_in_block; all_cell_idx++)
	{
		cout<<"cell idx: "<<all_cell_idx<<endl;
		cout<<"grad x ro: "<<block->block_interpolation_variables_->grad_ro_[all_cell_idx][0]<<endl;
		cout<<"grad y ro: "<<block->block_interpolation_variables_->grad_ro_[all_cell_idx][1]<<endl;
		cout<<"grad z ro: "<<block->block_interpolation_variables_->grad_ro_[all_cell_idx][2]<<endl<<endl;

		cout<<"grad x uu: "<<block->block_interpolation_variables_->grad_uu_[all_cell_idx][0]<<endl;
		cout<<"grad y uu: "<<block->block_interpolation_variables_->grad_uu_[all_cell_idx][1]<<endl;
		cout<<"grad z uu: "<<block->block_interpolation_variables_->grad_uu_[all_cell_idx][2]<<endl<<endl;

		cout<<"grad x vv: "<<block->block_interpolation_variables_->grad_vv_[all_cell_idx][0]<<endl;
		cout<<"grad y vv: "<<block->block_interpolation_variables_->grad_vv_[all_cell_idx][1]<<endl;
		cout<<"grad z vv: "<<block->block_interpolation_variables_->grad_vv_[all_cell_idx][2]<<endl<<endl;

		cout<<"grad x ww: "<<block->block_interpolation_variables_->grad_ww_[all_cell_idx][0]<<endl;
		cout<<"grad y ww: "<<block->block_interpolation_variables_->grad_ww_[all_cell_idx][1]<<endl;
		cout<<"grad z ww: "<<block->block_interpolation_variables_->grad_ww_[all_cell_idx][2]<<endl<<endl;

		cout<<"grad x pp: "<<block->block_interpolation_variables_->grad_pp_[all_cell_idx][0]<<endl;
		cout<<"grad y pp: "<<block->block_interpolation_variables_->grad_pp_[all_cell_idx][1]<<endl;
		cout<<"grad z pp: "<<block->block_interpolation_variables_->grad_pp_[all_cell_idx][2]<<endl<<endl;

	}

   */

	/*

	int i;
	int n_blocks_in_process;
	int* my_blocks;
	Block* all_blocks;
	Block* current_block;

	n_blocks_in_process=complete_mesh->n_blocks_in_process_;
	my_blocks=complete_mesh->my_blocks_;
	all_blocks=complete_mesh->all_blocks_;

	// AJOUTER INITIALISATION

	while (true)
	{
		///INSÉRER LES TRUCS DE MPI ICI JE CROIS
		//updater_->synchroniseUpdate(complete_mesh??); // SYNCHRONISE LES VARIABLES PRIMITIVES DES CELLULES PHANTOMES
		//timestep_->synchroniseGradient(complete_mesh??); //SYNCHRONISE LES GRADIENTS DES CELLULES PHANTOMES (peut-être déplacer la fonction autre que dans timestep_??)
		//timestep_->synchroniseLimiter(complete_mesh??); //SYNCHRONISE LES LIMITERS DES CELLULES PHANTOMES (peut-être déplacer la fonction autre que dans timestep_??)
		//post_processing_->process(block, complete_mesh); //PARTIE QUI CALCULE LES SOMMES, PRENDS LES DÉCISIONS ET PUBLISH
		/// FIN DES TRUCS MPI

		for	(i=0;i<n_blocks_in_process;i++)
		{
			current_block=all_blocks[my_blocks[i]];
			timestep_->computeSpectralRadius(current_block);
			timestep_->computeTimestep(current_block);
			this->saveW0(current_block);
			runge_kutta_->computeRungeKutta(current_block);
			post_processing_->computeFlowData(current_block); //PARTIE QUI FAIT JUSTE CALCULER LES CL ET CONVERGENCE PARTIELLE
		}

	}

	// REMPLACER EXIT


	*/
}

void Solver::saveW0(Block* block)
{
	//cout<<"\tExécution w0: "<<endl;


	int nb_real_cells=block->n_real_cells_in_block_;
	int cell_idx;
	double ro, uu, vv, ww, pp;
	double ro_0,ru_0,rv_0,rw_0,re_0;

	for (cell_idx=0;cell_idx<nb_real_cells;cell_idx++) //BOUCLER SUR LES CELLULES INTÉRIEURS PLUTÔT? VA DÉPENDRE DE updateSolution
	{
		ro=block->block_primitive_variables_->ro_[cell_idx];
		uu=block->block_primitive_variables_->uu_[cell_idx];
		vv=block->block_primitive_variables_->vv_[cell_idx];
		ww=block->block_primitive_variables_->ww_[cell_idx];
		pp=block->block_primitive_variables_->pp_[cell_idx];

		ro_0=ro;
		ru_0= ro*uu;
		rv_0= ro*vv;
		rw_0= ro*ww;
		re_0= 0.5*ro*(uu*uu+vv*vv+ww*ww)+1./(gamma_-1.0)*pp;


		block->block_primitive_variables_->ro_0_[cell_idx]=ro_0;
		block->block_primitive_variables_->ru_0_[cell_idx]=ru_0;
		block->block_primitive_variables_->rv_0_[cell_idx]=rv_0;
		block->block_primitive_variables_->rw_0_[cell_idx]=rw_0;
		block->block_primitive_variables_->re_0_[cell_idx]=re_0;


	}

	/* Vérification
	for (cell_idx=0;cell_idx<nb_real_cells;cell_idx++) //BOUCLER SUR LES CELLULES INTÉRIEURS PLUTÔT? VA DÉPENDRE DE updateSolution
	{
		cout<<"Cellule: "<<cell_idx<<" ro_0_: "<<block->block_primitive_variables_->ro_0_[cell_idx]<<endl;
		cout<<"Cellule: "<<cell_idx<<" ru_0_: "<<block->block_primitive_variables_->ru_0_[cell_idx]<<endl;
		cout<<"Cellule: "<<cell_idx<<" rv_0_: "<<block->block_primitive_variables_->rv_0_[cell_idx]<<endl;
		cout<<"Cellule: "<<cell_idx<<" re_0_: "<<block->block_primitive_variables_->re_0_[cell_idx]<<endl;
	}
	*/


}


#endif
