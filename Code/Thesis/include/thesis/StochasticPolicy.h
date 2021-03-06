/*
 * Copyright (c) 2016 Pierpaolo Necchi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STOCHASTICPOLICY_H
#define STOCHASTICPOLICY_H

#include <armadillo>        /* arma::vec */
#include <memory>           /* std::unique_ptr */
#include <thesis/Policy.h>  /* Policy */

/**
 * StochasticPolicy is a pure abstract class which inherits from the
 * Policy abstract class and provides a generic interface for a stochastic
 * policy pi(s, a; theta). It provides the likelihoodScore method so that it can
 * be used as the core of an actor in policy gradient method.
 */

class StochasticPolicy : public Policy
{
    public:
        /*!
         * Constructor.
         * Initialize a StochasticPolicy object given the sizes of the
         * observation space and of the action space.
         * \param dimObservation_ dimension of the observation space
         * \param dimAction_ dimension of the action space
         */
        StochasticPolicy(size_t dimObservation_, size_t dimAction_)
            : Policy(dimObservation_, dimAction_) {}

        //! Default destructor
        virtual ~StochasticPolicy() = default;

        //! Clone method for polymorphic clone
        std::unique_ptr<StochasticPolicy> clone() const
        {
            return checkedClone<StochasticPolicy>();
        }

        /*!
         * Get policy parameters size, i.e. size of the parameter vector
         * \return parameters size
         */
        virtual size_t getDimParameters() const = 0;

        /*!
         * Get method for the policy parameters.
         * \return parameters stored in an arma::vector
         */
        virtual arma::vec getParameters() const = 0;

        /*!
         * Set method for the policy parameters.
         * \param parameters_ the new parameters stored in an arma::vector
         */
        virtual void setParameters(arma::vec const &parameters_) = 0;

        /*!
         * Given an observation, select an action accordind to the policy.
         * \param observation_ observation
         * \return action
         */
        virtual arma::vec getAction(arma::vec const &observation_) const = 0;

        /*!
         * Evaluate the Likelihood score function at a given observation and
         * action.
         * \param observation_ observation
         * \param action_ action
         * \return likelihood score evaluated at observation_ and action_
         */
        virtual arma::vec likelihoodScore(arma::vec const &observation_,
                                          arma::vec const &action_) const = 0;

        /*!
         * Reset policy to initial conditions.
         */
        virtual void reset() = 0;
};

#endif // STOCHASTICPOLICY_H
