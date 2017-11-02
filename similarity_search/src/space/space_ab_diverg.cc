/**
 * Non-metric Space Library
 *
 * Authors: Bilegsaikhan Naidan (https://github.com/bileg), Leonid Boytsov (http://boytsov.info).
 * With contributions from Lawrence Cayton (http://lcayton.com/) and others.
 *
 * For the complete list of contributors and further details see:
 * https://github.com/searchivarius/NonMetricSpaceLib 
 * 
 * Copyright (c) 2016
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */

#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

#include "space/space_ab_diverg.h"
#include "logging.h"
#include "experimentconf.h"

namespace similarity {

template <typename dist_t>
dist_t SpaceAlphaBetaDiverg<dist_t>::HiddenDistance(const Object* obj1, const Object* obj2) const {
  CHECK(obj1->datalength() > 0);
  CHECK(obj1->datalength() == obj2->datalength());
  const dist_t* x = reinterpret_cast<const dist_t*>(obj1->data());
  const dist_t* y = reinterpret_cast<const dist_t*>(obj2->data());
  const size_t length = obj1->datalength() / sizeof(dist_t);

  return alpha_beta_divergence(x, y, length, alpha_, beta_);
}

template <typename dist_t>
dist_t SpaceAlphaBetaDiverg<dist_t>::ProxyDistance(const Object* obj1, const Object* obj2) const {
  CHECK(obj1->datalength() > 0);
  CHECK(obj1->datalength() == obj2->datalength());
  const dist_t* x = reinterpret_cast<const dist_t*>(obj1->data());
  const dist_t* y = reinterpret_cast<const dist_t*>(obj2->data());
  const size_t length = obj1->datalength() / sizeof(dist_t);

  return alpha_beta_divergence_proxy(x, y, length, alpha_, beta_);
}

template <typename dist_t>
std::string SpaceAlphaBetaDiverg<dist_t>::StrDesc() const {
  std::stringstream stream;
  stream << SPACE_AB_DIVERG << ":alpha=" << alpha_ << ",beta=" << beta_;
  return stream.str();
}

template class SpaceAlphaBetaDiverg<float>;
template class SpaceAlphaBetaDiverg<double>;

}  // namespace similarity
