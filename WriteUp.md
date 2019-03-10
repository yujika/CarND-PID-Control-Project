# CarND PID Controller Project Writeup.

## Describe the effect each of the P, I, D components had in your implementation.
### The effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
* P : linearly increase steer angle to CTE.
* D : linearly increase steer angle to difference of CTE
* I : linearly increase steer angle to cummulative amount of CTE
* Those PID behavior of my program match my expectation

### Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.
I tryied to record by pressing 'R' on Simulator screen, but I simulator didn't record anything.
So... Sorry, no recording provided.

## Describe how the final hyperparameters were chosen.
* Kp
Decided by choosing seemingy appropriate Kp parameter manually so that it doesn't cause run off.

* Kd
Decided by examining twiddled Kd paramter so that it compensate overrun caused by Kp.
At first use twiddle to find out roughly appropriate Kd range.
Second narrow down twiddle range by reducing pd\[1\] paramter and set initial Kd paramter to roughly correct value.
But the couse in the simulator includes curves, it was difficult to automatically tune Kd parameter by twiddle because total error is bigger at curves comparing to straight.

* Ki
Decided by mainly by twiddling Ki paramter after nailing down Kd parameter as I described above.

