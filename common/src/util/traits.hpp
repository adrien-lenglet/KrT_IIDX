#pragma once

namespace util {

template <typename T>
using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

struct empty_struct {
	template <typename ...Args>
	empty_struct(Args &&...) {}
};
template <bool Pred, class T>
using conditional_un_t = std::conditional_t<Pred, T, empty_struct>;

}