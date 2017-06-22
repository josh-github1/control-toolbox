/*!
 *  \example JacobianCGTest.h
 *
 *  A simple example on how to use Auto-Diff Codegeneration to compute the Jacobian (derivative) of a
 *  general function \f$ y = f(x) \f$.
 *
 *  \note This test gets run by CodegenTests.cpp to ensure all codegen tests do NOT run in parallel.
 */

// define the input and output sizes of the function
const size_t inDim = 3; //!< dimension of x
const size_t outDim = 2; //!< dimension of y

//! the Jacobian codegen class
typedef JacobianCG<inDim, outDim> JacCG;

/*!
 * A general vector-valued function.
 *
 * @param x the input
 * @return output y = f(x)
 */
template <typename SCALAR>
Eigen::Matrix<SCALAR, outDim, 1> testFunction(const Eigen::Matrix<SCALAR, inDim, 1>& x)
{
	Eigen::Matrix<SCALAR, outDim, 1> y;

	y(0) = 3*x(0) + 2*x(0)*x(0) - x(1)*x(2);
	y(1) = x(2) + x(1) + 3;

	return y;
}

/*!
 * The analytically, manually derived Jacobian of testFunction() used for verification
 *
 * @param x the input
 * @return output y = f(x)
 */
template <typename SCALAR>
Eigen::Matrix<SCALAR, outDim, inDim> jacobianCheck(const Eigen::Matrix<SCALAR, inDim, 1>& x)
{
	Eigen::Matrix<SCALAR, outDim, inDim> jac;

	jac << 3+4*x(0),    -x(2),     -x(1),
		   0,              1,        1;

	return jac;
}

/*!
 * Test for just-in-time compilation of the Jacobian and subsequent evaluation of it
 */
TEST(JacobianCGTest, JITCompilationTest)
{
	try {
		// create a function handle (also works for class methods, lambdas, function pointers, ...)
		typename JacCG::Function f = testFunction<CppAD::AD<CppAD::cg::CG<double> > >;

		// initialize the Auto-Diff Codegen Jacobian
		JacCG jacCG(f);

		// compile the Jacobian
		jacCG.compileJIT();

		// create an input vector
		Eigen::Matrix<double, inDim, 1> x;

		for (size_t i=0; i<1000; i++)
		{
			// create a random input
			x.setRandom();

			// verify agains the analytical Jacobian
			ASSERT_LT((jacCG(x) - jacobianCheck(x)).array().abs().maxCoeff(), 1e-10);
		}
	} catch (std::exception& e)
	{
		std::cout << "Exception thrown: "<<e.what()<<std::endl;
		ASSERT_TRUE(false);
	}
}


/*!
 * Test for writing the codegenerated Jacobian to file
 */
TEST(JacobianCGTest, CodegenTest)
{
	// create a function handle (also works for class methods, lambdas, function pointers, ...)
	typename JacCG::Function f = testFunction<CppAD::AD<CppAD::cg::CG<double> > >;

	// initialize the Auto-Diff Codegen Jacobian
	JacCG jacCG(f);

	// generate code for the Jacobian, similar to jacobianCheck()
	jacCG.generateCode("TestJacobian");

	// generate code for the actual function, will evaluate to the same as testFunction()
	jacCG.generateForwardZeroCode("TestForwardZero");
}
