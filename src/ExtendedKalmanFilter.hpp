#ifndef __EXTENDED_KALMAN_FILTER_HPP__
#define __EXTENDED_KALMAN_FILTER_HPP__

#include <Eigen/Core>
#include <Eigen/Geometry>


namespace ExtendedKalmanFilter {
 
template <unsigned int SIZE, unsigned int INPUT_SIZE> 
class EKF
    {
      
      public:
	
	/** do i need to declare the size as dynamic ? */ 
	
	/** state estimate */
	Eigen::Matrix<double,SIZE,1>  x;
	
	/** covariance matrix */
	Eigen::Matrix<double, SIZE, SIZE> P;


      public:
	/** what is this line */ 
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	
	
	/** update step 
	    f - state transition
	    Q - process noise covariance matrix, 
	    J_F - Jacobian of the state transition */
	void update(Eigen::Matrix<double, SIZE, 1> f,
	      Eigen::Matrix<double, SIZE, SIZE> J_F,
	      Eigen::Matrix<double, SIZE, SIZE> Q )
	{

		//State transition 
		x=f; 
		
		//covariance update 
		P = J_F*P*J_F.transpose() + Q;
		
	}
 
	/** correction step, 
	 p - observation 
	 h - observation model function
	 J_H - jacobian observation model
	 R - measurement noise covariance matrix
	*/	
	template <unsigned int MEASUREMENT_SIZE> 
	void correction( Eigen::Matrix<double, MEASUREMENT_SIZE, 1> p,
	  Eigen::Matrix<double, MEASUREMENT_SIZE, 1> h,
	  Eigen::Matrix<double, MEASUREMENT_SIZE, SIZE> J_H,
	  Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> R)	  
	{
	    // correct the estimate and covariance according to measurement
	    
	    Eigen::Matrix<double, MEASUREMENT_SIZE, 1> y = p - h;
	    
	    Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> S = J_H*P*J_H.transpose()+R;

	    Eigen::Matrix<double, SIZE, MEASUREMENT_SIZE> K = P*J_H.transpose()*S.inverse();
	  
	    x = x + K*y;
	    
	    P = (Eigen::Matrix<double, SIZE, SIZE>::Identity() - K*J_H)*P;
	    
	}


	
    };
}

#endif
