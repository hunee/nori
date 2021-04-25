/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "picker.h"

#include "ui/component/input.h"

namespace GL {

static bool comp_z(std::shared_ptr<GL::object>& a, std::shared_ptr<GL::object>& b) {
  return a->transform_.z > b->transform_.z;
}

void picker::flush()
{
  bool drag = false;

  std::sort(picked_.begin(), picked_.end(), comp_z);

  for (auto&& v : picked_ )
  {
    auto ic = v->get<GL::ui::input>("ic");
    if (drag == false && ic->drag_ == true)
      drag = true;
    else
    {
      ic->drag_ = false;
      ic->focus_ = false;
    }
  }

  if (drag == false && !picked_.empty())
  {
    auto v = picked_.front();

    auto ic = v->get<GL::ui::input>("ic");
    ic->focus_ = true;
  }

  picked_.clear();
}

};//GL