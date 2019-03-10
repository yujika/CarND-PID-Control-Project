#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_, int twiddle_batch_size_, double twiddle_tolerance_, double twiddle_initial_dp[3]);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   * @output control value ( steering etc )
   */
  double UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * Tune PID params using twiddle
   * @output The total PID error
   */
  void twiddle();


 private:
  double cte;
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  /**
   * Twiddle parameters
   */
  double twiddle_tolerance;
  double twiddle_best_err;
  double p[3];
  double dp[3];
  int twiddle_batch_size;
  int iteration_count;
  int current_twiddle_param;

  double total_error;
 
  /**
   * return sum(dp) for twiddle tolerance check
   * @output sum(dp)
   */
  double sum_dp();
};

#endif  // PID_H
