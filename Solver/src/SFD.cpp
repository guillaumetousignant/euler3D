

#include <iostream>
#include "SFD.h"
using namespace std;
SelectiveFrequencyDamper::SelectiveFrequencyDamper(double khi, double delta)
{
  khi_=khi;
  delta_=delta;
}

SelectiveFrequencyDamper::~SelectiveFrequencyDamper()
{

}

void SelectiveFrequencyDamper::calculateDampedVariables(Block* block)
{

  double khi=khi_;
  double delta=delta_;
  //std::cout<<"DELTA: "<<delta<<std::endl;
  //std::cout<<"khi: "<<khi<<std::endl;
  PrimitiveVariables* my_primitive_variables;
  TimeVariables* my_time_variables_;
	my_primitive_variables = block -> block_primitive_variables_;
  my_time_variables_ = block -> block_time_variables_;
  double gamma;
  gamma=my_primitive_variables->gamma_;

  double my_ro;
  double my_uu;
  double my_vv;
  double my_ww;
  double my_pp;

  double my_rr;
  double my_ru;
  double my_rv;
  double my_rw;
  double my_re;

  double my_damped_ro;
  double my_damped_uu;
  double my_damped_vv;
  double my_damped_ww;
  double my_damped_pp;

  double my_damped_rr;
  double my_damped_ru;
  double my_damped_rv;
  double my_damped_rw;
  double my_damped_re;

  double my_filtered_ro;
  double my_filtered_uu;
  double my_filtered_vv;
  double my_filtered_ww;
  double my_filtered_pp;

  double my_filtered_rr;
  double my_filtered_ru;
  double my_filtered_rv;
  double my_filtered_rw;
  double my_filtered_re;

  double my_previous_filtered_ro;
  double my_previous_filtered_uu;
  double my_previous_filtered_vv;
  double my_previous_filtered_ww;
  double my_previous_filtered_pp;

  double my_previous_filtered_rr;
  double my_previous_filtered_ru;
  double my_previous_filtered_rv;
  double my_previous_filtered_rw;
  double my_previous_filtered_re;

  double my_dt;
  double e_rep;
  double inverse_term;
  double coeff_un;
  double coeff_deux;
  double coeff_trois;
  double coeff_quatre;


  for (int cell_idx=0; cell_idx<block->n_real_cells_in_block_; cell_idx++)
  {
    my_dt = my_time_variables_->dt_[cell_idx];
    delta=  my_time_variables_->dt_[cell_idx];

    //delta=delta;
    //my_dt =my_dt;

    my_ro = my_primitive_variables ->ro_[cell_idx];
    my_uu = my_primitive_variables ->uu_[cell_idx];
    my_vv = my_primitive_variables ->vv_[cell_idx];
    my_ww = my_primitive_variables ->ww_[cell_idx];
    my_pp = my_primitive_variables ->pp_[cell_idx];

    my_previous_filtered_ro = my_primitive_variables ->filtered_ro_[cell_idx];
    my_previous_filtered_uu = my_primitive_variables ->filtered_uu_[cell_idx];
    my_previous_filtered_vv = my_primitive_variables ->filtered_vv_[cell_idx];
    my_previous_filtered_ww = my_primitive_variables ->filtered_ww_[cell_idx];
    my_previous_filtered_pp = my_primitive_variables ->filtered_pp_[cell_idx];

    my_rr = my_ro;
    my_ru = my_uu*my_ro;
    my_rv = my_vv*my_ro;
    my_rw = my_ww*my_ro;
    my_re = 0.5*my_ro*(my_uu*my_uu+my_vv*my_vv+my_ww*my_ww)+(my_pp/(gamma-1.0));

    my_previous_filtered_rr = my_previous_filtered_ro;
    my_previous_filtered_ru = my_previous_filtered_uu*my_previous_filtered_ro;
    my_previous_filtered_rv = my_previous_filtered_vv*my_previous_filtered_ro;
    my_previous_filtered_rw = my_previous_filtered_ww*my_previous_filtered_ro;
    my_previous_filtered_re = 0.5*my_previous_filtered_ro*(my_previous_filtered_uu*my_previous_filtered_uu+my_previous_filtered_vv*my_previous_filtered_vv+my_previous_filtered_ww*my_previous_filtered_ww)+(my_previous_filtered_pp/(gamma-1.0));

    e_rep = exp(-(khi+(1/delta))*my_dt);
    inverse_term = 1/(1+khi*delta);

    coeff_un = inverse_term*(1+khi*delta*e_rep);
    coeff_deux = inverse_term*(khi*delta*(1-e_rep));
    coeff_trois = inverse_term*(1-e_rep);
    coeff_quatre = inverse_term*(khi*delta+e_rep);

    my_damped_rr = coeff_un*my_rr + coeff_deux*my_previous_filtered_rr;
    my_damped_ru = coeff_un*my_ru + coeff_deux*my_previous_filtered_ru;
    my_damped_rv = coeff_un*my_rv + coeff_deux*my_previous_filtered_rv;
    my_damped_rw = coeff_un*my_rw + coeff_deux*my_previous_filtered_rw;
    my_damped_re = coeff_un*my_re + coeff_deux*my_previous_filtered_re;

    my_filtered_rr = coeff_trois*my_rr + coeff_quatre*my_previous_filtered_rr;
    my_filtered_ru = coeff_trois*my_ru + coeff_quatre*my_previous_filtered_ru;
    my_filtered_rv = coeff_trois*my_rv + coeff_quatre*my_previous_filtered_rv;
    my_filtered_rw = coeff_trois*my_rw + coeff_quatre*my_previous_filtered_rw;
    my_filtered_re = coeff_trois*my_re + coeff_quatre*my_previous_filtered_re;

    /*my_damped_rr = inverse_term*((my_rr+khi*delta*my_rr*e_rep) + (khi*delta*my_previous_filtered_rr*(1-e_rep)));
    my_damped_ru = inverse_term*((my_ru+khi*delta*my_ru*e_rep) + (khi*delta*my_previous_filtered_ru*(1-e_rep)));
    my_damped_rv = inverse_term*((my_rv+khi*delta*my_rv*e_rep) + (khi*delta*my_previous_filtered_rv*(1-e_rep)));
    my_damped_rw = inverse_term*((my_rw+khi*delta*my_rw*e_rep) + (khi*delta*my_previous_filtered_rw*(1-e_rep)));
    my_damped_re = inverse_term*((my_re+khi*delta*my_re*e_rep) + (khi*delta*my_previous_filtered_re*(1-e_rep)));

    my_filtered_rr = inverse_term*((my_rr-my_rr*e_rep) + (khi*delta*my_previous_filtered_rr+my_previous_filtered_rr*e_rep));
    my_filtered_ru = inverse_term*((my_ru-my_ru*e_rep) + (khi*delta*my_previous_filtered_ru+my_previous_filtered_ru*e_rep));
    my_filtered_rv = inverse_term*((my_rv-my_rv*e_rep) + (khi*delta*my_previous_filtered_rv+my_previous_filtered_rv*e_rep));
    my_filtered_rw = inverse_term*((my_rw-my_rw*e_rep) + (khi*delta*my_previous_filtered_rw+my_previous_filtered_rw*e_rep));
    my_filtered_re = inverse_term*((my_re-my_re*e_rep) + (khi*delta*my_previous_filtered_re+my_previous_filtered_re*e_rep));*/

    my_damped_ro=my_damped_rr;
    my_damped_uu=my_damped_ru/my_damped_rr;
    my_damped_vv=my_damped_rv/my_damped_rr;
    my_damped_ww=my_damped_rw/my_damped_rr;
    my_damped_pp=(gamma-1.0)*(my_damped_re-((my_damped_ru*my_damped_ru+my_damped_rv*my_damped_rv+my_damped_rw*my_damped_rw)/(2*my_damped_rr)));

    my_filtered_ro=my_filtered_rr;
    my_filtered_uu=my_filtered_ru/my_filtered_rr;
    my_filtered_vv=my_filtered_rv/my_filtered_rr;
    my_filtered_ww=my_filtered_rw/my_filtered_rr;
    my_filtered_pp=(gamma-1.0)*(my_filtered_re-((my_filtered_ru*my_filtered_ru+my_filtered_rv*my_filtered_rv+my_filtered_rw*my_filtered_rw)/(2*my_filtered_rr)));

    my_primitive_variables ->ro_[cell_idx] = my_damped_ro;
    my_primitive_variables ->uu_[cell_idx] = my_damped_uu;
    my_primitive_variables ->vv_[cell_idx] = my_damped_vv;
    my_primitive_variables ->ww_[cell_idx] = my_damped_ww;
    my_primitive_variables ->pp_[cell_idx] = my_damped_pp;

    my_primitive_variables ->filtered_ro_[cell_idx] = my_filtered_ro;
    my_primitive_variables ->filtered_uu_[cell_idx] = my_filtered_uu;
    my_primitive_variables ->filtered_vv_[cell_idx] = my_filtered_vv;
    my_primitive_variables ->filtered_ww_[cell_idx] = my_filtered_ww;
    my_primitive_variables ->filtered_pp_[cell_idx] = my_filtered_pp;
  }

}
