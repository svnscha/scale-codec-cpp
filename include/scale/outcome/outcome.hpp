/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SCALE_OUTCOME_OUTCOME
#define SCALE_OUTCOME_OUTCOME

#pragma warning(push)
#pragma warning(disable:4583)
#pragma warning(disable:4582)
#include <boost/outcome/outcome.hpp>
#include <boost/outcome/try.hpp>
#pragma warning(pop)

#include "outcome-register.hpp"

namespace scale::outcome {

using namespace BOOST_OUTCOME_V2_NAMESPACE;

template <class R, class S = std::error_code,
          class NoValuePolicy = policy::default_policy<R, S, void>>
using result = basic_result<R, S, NoValuePolicy>;

} // namespace scale::outcome

#define OUTCOME_TRY(...) BOOST_OUTCOME_TRY(__VA_ARGS__)

#endif // SCALE_OUTCOME_OUTCOME
