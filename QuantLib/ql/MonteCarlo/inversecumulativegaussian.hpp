
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.org/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, please email quantlib-users@lists.sourceforge.net
 * The license is also available at http://quantlib.org/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.org/group.html
*/

/*! \file inversecumulativegaussian.hpp
    \brief Inverse Cumulative Gaussian random-number generator

    \fullpath
    ql/MonteCarlo/%inversecumulativegaussian.hpp
*/

// $Id$

#ifndef quantlib_inversecumulative_gaussian_h
#define quantlib_inversecumulative_gaussian_h

#include "ql/qldefines.hpp"
#include "ql/Math/normaldistribution.hpp"

namespace QuantLib {

    namespace MonteCarlo {

        //! Inverse Cumulative Gaussian random number generator
        /*! It uses a uniform deviate in (0, 1) as the source of cumulative
            normal distribution values.
            Then an Inverse Cumulative Normal Distribution is used as it is
            approximately a Gaussian deviate with average 0.0 and standard
            deviation 1.0,
            
            The uniform deviate is supplied by U.

            Class U should satisfies
            \code
                U::U(long seed);
                double U::next() const;
                double U::weight() const;
            \endcode
        */
        template <class U>
        class ICGaussian {
          public:
            typedef double sample_type;
            explicit ICGaussian(long seed=0);
            //! returns next sample from the Gaussian distribution
            double next() const;
            //! returns the weight of the last extracted sample
            double weight() const;
          private:
            U basicGenerator_;
            mutable double gaussWeight_;
            QuantLib::Math::InvCumulativeNormalDistribution ICND_;
        };

        template <class U>
        ICGaussian<U>::ICGaussian(long seed):
            basicGenerator_(seed), gaussWeight_(0.0), ICND_() {}

        template <class U>
        inline double ICGaussian<U>::next() const {

            double gaussPoint = ICND_(basicGenerator_.next());
            gaussWeight_ = basicGenerator_.weight();

            return gaussPoint;
        }

        template <class U>
        inline double ICGaussian<U>::weight() const {
            return gaussWeight_;
        }

    }

}

#endif
