#include <assert.h>
#include <test_cpp.h>
#include <float.h>
#include <math.h>

uint32_t exports::test::lists::to_test::AllocatedBytes() {
    return 0;
}

template <class T, class S>
static bool equal(T const&a, S const& b) {
    return a == b;
}
template<class R, class S>
static bool equal(std::span<R> const&a, std::span<S> const& b) {
    if (a.size() != b.size()) { return false; }
    for (uint32_t i = 0; i<a.size(); ++i) {
        if (!equal(a[i], b[i])) { return false; }
    }
    return true;
}
template<class R>
static bool equal(wit::vector<R> const&a, std::span<R> const& b) {
    return equal(a.get_view(), b);
}
template<class R>
static bool equal(std::span<const R> const&a, wit::vector<R> const& b) {
    return equal(b, a);
}
template<class R>
static bool equal(std::span<const R> const&a, std::vector<R> const& b) {
    return equal(a, std::span<const R>(b));
}
template<class R>
static bool equal(wit::vector<R> const&a, std::vector<R> const& b) {
    return equal(a.get_view(), std::span<R>(b));
}
template<class R,class S, class T, class U>
static bool equal(std::tuple<R,S> const&a, std::tuple<T,U> const& b) {
    return equal(std::get<0>(a), std::get<0>(b)) && equal(std::get<1>(a), std::get<1>(b));
}

void exports::test::lists::to_test::EmptyListParam(std::span<uint8_t const> a) {
    assert(a.empty());
}

void exports::test::lists::to_test::EmptyStringParam(std::string_view a) {
    assert(a.empty());
}

wit::vector<uint8_t> exports::test::lists::to_test::EmptyListResult() {
    return wit::vector<uint8_t>();
}

wit::string exports::test::lists::to_test::EmptyStringResult() {
    return wit::string::from_view(std::string_view());
}

void exports::test::lists::to_test::ListParam(std::span<const uint8_t> list) {
    assert(equal(list, std::vector<uint8_t>{1, 2, 3, 4}));
}

void exports::test::lists::to_test::ListParam2(std::string_view ptr) {
    assert(equal(ptr, std::string_view("foo")));
}

void exports::test::lists::to_test::ListParam3(std::span<const std::string_view> ptr) {
    assert(equal(ptr.size(), size_t(3)));
    assert(equal(ptr[0], std::string_view("foo")));
    assert(equal(ptr[1], std::string_view("bar")));
    assert(equal(ptr[2], std::string_view("baz")));
}

void exports::test::lists::to_test::ListParam4(std::span<const std::span<const std::string_view>> ptr) {
    assert(equal(ptr.size(), size_t(2)));
    assert(equal(ptr[0][0], std::string_view("foo")));
    assert(equal(ptr[0][1], std::string_view("bar")));
    assert(equal(ptr[1][0], std::string_view("baz")));
}

void exports::test::lists::to_test::ListParam5(std::span<std::tuple<uint8_t, uint32_t, uint8_t> const> a) {

}

void exports::test::lists::to_test::ListParamLarge(std::span<std::string_view const> a) {

}

wit::vector<uint8_t> exports::test::lists::to_test::ListResult() {
    return wit::vector<uint8_t>::from_view(std::span<uint8_t const>(std::vector<uint8_t>{1, 2, 3, 4, 5}));
}

wit::string exports::test::lists::to_test::ListResult2() {
    return wit::string::from_view("hello!");
}

wit::vector<wit::string> exports::test::lists::to_test::ListResult3() {
    return wit::vector<wit::string>::from_view(std::span<wit::string const>(std::vector<wit::string>{wit::string::from_view("hello,"), wit::string::from_view("world!")}));
}

wit::vector<uint8_t> exports::test::lists::to_test::ListRoundtrip(std::span<const uint8_t> x) {
    return wit::vector<uint8_t>::from_view(x);
}

wit::string exports::test::lists::to_test::StringRoundtrip(std::string_view x) {
    return wit::string::from_view(x);
}

std::tuple<wit::vector<uint8_t>, wit::vector<int8_t>> exports::test::lists::to_test::ListMinmax8(std::span<uint8_t const> a, std::span<int8_t const> b) {
    return std::make_tuple(wit::vector<uint8_t>::from_view(a), wit::vector<int8_t>::from_view(b));
}

std::tuple<wit::vector<uint16_t>, wit::vector<int16_t>> exports::test::lists::to_test::ListMinmax16(std::span<uint16_t const> a, std::span<int16_t const> b) {
    return std::make_tuple(wit::vector<uint16_t>::from_view(a), wit::vector<int16_t>::from_view(b));
}

std::tuple<wit::vector<uint32_t>, wit::vector<int32_t>> exports::test::lists::to_test::ListMinmax32(std::span<uint32_t const> a, std::span<int32_t const> b) {
    return std::make_tuple(wit::vector<uint32_t>::from_view(a), wit::vector<int32_t>::from_view(b));
}

std::tuple<wit::vector<uint64_t>, wit::vector<int64_t>> exports::test::lists::to_test::ListMinmax64(std::span<uint64_t const> a, std::span<int64_t const> b) {
    return std::make_tuple(wit::vector<uint64_t>::from_view(a), wit::vector<int64_t>::from_view(b));
}

std::tuple<wit::vector<float>, wit::vector<double>> exports::test::lists::to_test::ListMinmaxFloat(std::span<float const> a, std::span<double const> b) {
    return std::make_tuple(wit::vector<float>::from_view(a), wit::vector<double>::from_view(b));
}
