#ifndef DATASTRUCTURE_HEAD_TIMEVARIABLES_H
#define DATASTRUCTURE_HEAD_TIMEVARIABLES_H

class TimeVariables
{
public:
	double* dt_;
	double** spectral_radius_;

	TimeVariables();
	~TimeVariables();
	
};

#endif