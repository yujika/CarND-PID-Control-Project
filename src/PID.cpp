#include <iostream>
#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_, int twiddle_batch_size_, double twiddle_tolerance_, double twiddle_initial_dp[3]) {
  /**
   * Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  cte=0;
  p_error=0.;
  i_error=0.;
  d_error=0.;
  total_error=0;
  
  twiddle_batch_size = twiddle_batch_size_;
  twiddle_tolerance = twiddle_tolerance_;
  p[0] = Kp;
  p[1] = Kd;
  p[2] = Ki;
  for ( auto i = 0 ; i < 3 ; i++ ){
    dp[i] = twiddle_initial_dp[i];
  }

  current_twiddle_param = 0;
  twiddle_best_err =  -1;
}

double PID::UpdateError(double next_cte) {
  /**
   * Update PID errors based on cte.
   */
  d_error = next_cte - cte;
  i_error += next_cte;
  cte = next_cte;
	  
  return -Kp*cte - Kd*d_error - Ki*i_error;
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
  std::cout << "TotalError:"  << std::endl;
  return 0.0;  // TODO: Add your total error calc here!
}

void PID::twiddle() {
  auto i = current_twiddle_param;
  if ( sum_dp() > twiddle_tolerance ){
    iteration_count++;
    //    if ( iteration_count >= twiddle_batch_size/100 ){
    total_error += cte*cte;
      //    }
    if ( iteration_count >= twiddle_batch_size ){/* do twiddle*/
      iteration_count = 0;
      double err = total_error / int(twiddle_batch_size);
      total_error = 0.;/*reset total error*/
      if ( twiddle_best_err < 0 ) {
	twiddle_best_err = 10;//err is too small 
      }else if ( err < twiddle_best_err ){
	twiddle_best_err = err;
	dp[i] *= 1.1;
      }else{
	p[i] -= 2*dp[i];
	dp[i] *= 0.9;
      }
      p[i] += dp[i];
      switch(i){
      case 0:
	Kp = p[0]; break;
      case 1:
	Kd = p[1]; break;
      case 2:
	Ki = p[2]; break;
      }
      //DEBUG
      std::cout << "[twiddle] err=" << err 
		<< ", p=" << Kp 
		<< ", d=" << Kd 
		<< ", i=" << Ki 
		<< ", dp[0]=" << dp[0]
		<< ", dp[1]=" << dp[1] 
		<< ", dp[2]=" << dp[2] 
		<< ", best_err=" << twiddle_best_err
		<< ", cte=" << cte
		<<std::endl;

      current_twiddle_param = current_twiddle_param+1 < 3 ? current_twiddle_param+1 : 0;
    }
  }
  return;
}
double PID::sum_dp(){
  return ( dp[0] + dp[1] + dp[2] );
}
