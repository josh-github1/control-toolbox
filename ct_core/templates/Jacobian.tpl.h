/***********************************************************************************
Copyright (c) 2017, Michael Neunert, Markus Giftthaler, Markus Stäuble, Diego Pardo,
Farbod Farshidian. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of ETH ZURICH nor the names of its contributors may be used
      to endorse or promote products derived from this software without specific
      prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL ETH ZURICH BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************/

#ifndef INCLUDE_JACOBIAN_NAME_H_
#define INCLUDE_JACOBIAN_NAME_H_

#include <ct/core/math/Jacobian.h>

namespace ct {
namespace NS1 {
namespace NS2 {

class JACOBIAN_NAME : public core::Jacobian<IN_DIM, OUT_DIM, double> {
public:
	typedef Eigen::Matrix<double, OUT_DIM, IN_DIM> JAC_TYPE;
	typedef Eigen::Matrix<double, OUT_DIM, IN_DIM, Eigen::RowMajor> JAC_TYPE_ROW_MAJOR;
	typedef Eigen::Matrix<double, IN_DIM, 1> X_TYPE;

	JACOBIAN_NAME() {
		jac_.setZero();
		v_.fill(0.0);
	};

	JACOBIAN_NAME(const JACOBIAN_NAME& other)
	{
		jac_.setZero();
		v_.fill(0.0);
	}

	virtual ~JACOBIAN_NAME() {};

	JACOBIAN_NAME* clone() const override{
		return new JACOBIAN_NAME(*this);
	}


	JAC_TYPE operator()(const Eigen::VectorXd& x_in) override;

private:
	JAC_TYPE jac_;
	std::array<double, MAX_COUNT> v_;
};

} /* namespace NS2 */
} /* namespace NS1 */
} /* namespace ct */

#endif /* INCLUDE_JACOBIAN_NAME_H_ */