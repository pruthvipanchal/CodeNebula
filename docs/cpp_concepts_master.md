# CodeNebula: C++ Concepts (Core and STL)

This document lists all C++ concepts, including core language features and Standard Template Library (STL) components, from C++98 to C++26, organized by standard.

## C++98
### Core Language
- Basic types (int, float, double, char, bool, etc.)
- Pointers
- References
- Arrays
- Functions
- Function overloading
- Classes
- Objects
- Constructors
- Destructors
- Inheritance
  - Single inheritance
  - Multiple inheritance
  - Virtual inheritance
- Polymorphism
- Virtual functions
- Pure virtual functions
- Abstract classes
- Encapsulation
- Access specifiers (public, private, protected)
- Friend functions
- Friend classes
- Operator overloading
- Templates
  - Function templates
  - Class templates
- Exception handling (try, catch, throw)
- Namespaces
- Dynamic memory management (new, delete)
- Type casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
- Run-time type information (RTTI)
- Typeid

### STL
#### Containers
- std::vector
- std::list
- std::deque
- std::set
- std::map
- std::multiset
- std::multimap
- std::stack (container adaptor)
- std::queue (container adaptor)
- std::priority_queue (container adaptor)
#### Iterators
- Input iterator
- Output iterator
- Forward iterator
- Bidirectional iterator
- Random access iterator
- Iterator traits
- std::iterator
- std::advance
- std::distance
- std::next
- std::prev
#### Iterator Adaptors
- std::reverse_iterator
- std::back_insert_iterator
- std::front_insert_iterator
- std::insert_iterator
- std::istream_iterator
- std::ostream_iterator
- std::istreambuf_iterator
- std::ostreambuf_iterator
#### Algorithms
- std::for_each
- std::find
- std::find_if
- std::find_end
- std::find_first_of
- std::adjacent_find
- std::count
- std::count_if
- std::mismatch
- std::equal
- std::search
- std::search_n
- std::copy
- std::copy_backward
- std::move (algorithm)
- std::move_backward
- std::fill
- std::fill_n
- std::transform
- std::generate
- std::generate_n
- std::remove
- std::remove_if
- std::replace
- std::replace_if
- std::swap
- std::swap_ranges
- std::iter_swap
- std::reverse
- std::reverse_copy
- std::rotate
- std::rotate_copy
- std::unique
- std::unique_copy
- std::partition
- std::stable_partition
- std::sort
- std::stable_sort
- std::partial_sort
- std::partial_sort_copy
- std::nth_element
- std::merge
- std::inplace_merge
- std::includes
- std::set_union
- std::set_intersection
- std::set_difference
- std::set_symmetric_difference
- std::push_heap
- std::pop_heap
- std::make_heap
- std::sort_heap
- std::min
- std::max
- std::min_element
- std::max_element
- std::lexicographical_compare
- std::next_permutation
- std::prev_permutation
#### Function Objects (Functors)
- std::unary_function
- std::binary_function
- std::plus
- std::minus
- std::multiplies
- std::divides
- std::modulus
- std::negate
- std::equal_to
- std::not_equal_to
- std::greater
- std::less
- std::greater_equal
- std::less_equal
- std::logical_and
- std::logical_or
- std::logical_not
- std::unary_negate
- std::binary_negate
- std::binder1st
- std::binder2nd
- std::pointer_to_unary_function
- std::pointer_to_binary_function
- std::mem_fun
- std::mem_fun_ref
#### Utilities
- std::pair
- std::string
- std::auto_ptr (deprecated in C++11)
- std::rel_ops
#### Input/Output
- std::iostream
- std::istream
- std::ostream
- std::stringstream

## C++03
### Core Language
- Value initialization
- Explicit template argument specification for constructors

### STL
#### Containers
- std::vector<bool> improvements
#### Algorithms
- Minor fixes to algorithm behavior

## C++11
### Core Language
- Auto keyword
- decltype
- Range-based for loops
- Lambda expressions
- nullptr
- Strongly-typed enums (enum class)
- Type traits
- Static assertions (static_assert)
- Variadic templates
- Template aliases (using)
- Rvalue references
- Move semantics
- Move constructor
- Move assignment operator
- Perfect forwarding
- std::forward
- std::move
- Initializer lists
- Uniform initialization
- Delegating constructors
- In-class member initializers
- Explicit conversion operators
- override keyword
- final keyword
- noexcept specifier
- Generalized constant expressions (constexpr)
- User-defined literals
- Raw string literals
- Attributes (e.g., [[noreturn]])
- Multithreading support
  - std::thread
  - std::mutex
  - std::lock_guard
  - std::unique_lock
  - std::condition_variable
  - std::atomic
- Memory model
- std::future
- std::promise
- std::async
- Smart pointers
  - std::shared_ptr
  - std::unique_ptr
  - std::weak_ptr
- Explicit default and delete functions (=default, =delete)

### STL
#### Containers
- std::array
- std::forward_list
- std::unordered_set
- std::unordered_map
- std::unordered_multiset
- std::unordered_multimap
#### Container Improvements
- std::vector emplace_back, emplace
- std::list emplace_front, emplace_back, emplace
- std::deque emplace_front, emplace_back, emplace
- std::map emplace, emplace_hint
- std::set emplace, emplace_hint
- std::unordered_map emplace, emplace_hint
- std::unordered_set emplace, emplace_hint
- std::initializer_list support for containers
#### Iterators
- std::begin
- std::end
- std::cbegin
- std::cend
- std::rbegin
- std::rend
- std::crbegin
- std::crend
- std::move_iterator
#### Algorithms
- std::all_of
- std::any_of
- std::none_of
- std::find_if_not
- std::copy_if
- std::copy_n
- std::move (move semantics)
- std::move_backward
- std::shuffle
- std::is_sorted
- std::is_sorted_until
- std::is_permutation
- std::is_heap
- std::is_heap_until
- std::minmax
- std::minmax_element
#### Function Objects
- std::function
- std::bind
- std::ref
- std::cref
- std::mem_fn
#### Utilities
- std::tuple
- std::forward_as_tuple
- std::make_pair (move-aware)
- std::piecewise_construct
#### Random Number Generation
- std::random_device
- std::mt19937
- std::mt19937_64
- std::linear_congruential_engine
- std::mersenne_twister_engine
- std::subtract_with_carry_engine
- std::discard_block_engine
- std::independent_bits_engine
- std::shuffle_order_engine
- std::uniform_int_distribution
- std::uniform_real_distribution
- std::normal_distribution
- std::bernoulli_distribution
- std::binomial_distribution
- std::negative_binomial_distribution
- std::geometric_distribution
- std::poisson_distribution
- std::exponential_distribution
- std::gamma_distribution
- std::weibull_distribution
- std::extreme_value_distribution
- std::lognormal_distribution
- std::chi_squared_distribution
- std::cauchy_distribution
- std::fisher_f_distribution
- std::student_t_distribution
- std::discrete_distribution
- std::piecewise_constant_distribution
- std::piecewise_linear_distribution
- std::seed_seq
#### Regular Expressions
- std::regex
- std::regex_match
- std::regex_search
- std::regex_replace
- std::regex_iterator
- std::regex_token_iterator
- std::smatch
- std::cmatch
- std::wsmatch
- std::wcmatch
- std::ssub_match
- std::csub_match
- std::wssub_match
- std::wcsub_match
- std::regex_error
#### Chrono Library
- std::chrono::duration
- std::chrono::time_point
- std::chrono::system_clock
- std::chrono::steady_clock
- std::chrono::high_resolution_clock
- std::chrono::nanoseconds
- std::chrono::microseconds
- std::chrono::milliseconds
- std::chrono::seconds
- std::chrono::minutes
- std::chrono::hours
#### Ratio Library
- std::ratio
- std::ratio_add
- std::ratio_subtract
- std::ratio_multiply
- std::ratio_divide
- std::ratio_equal
- std::ratio_not_equal
- std::ratio_less
- std::ratio_less_equal
- std::ratio_greater
- std::ratio_greater_equal
- std::atto, std::femto, std::pico, std::nano, std::micro, std::milli, std::centi, std::deci, std::deca, std::hecto, std::kilo, std::mega, std::giga, std::tera, std::peta, std::exa

## C++14
### Core Language
- Generic lambda expressions
- Lambda capture initializers
- Return type deduction for functions
- decltype(auto)
- Variable templates
- Binary literals
- Digit separators
- Relaxed constexpr restrictions
- [[deprecated]] attribute

### STL
#### Utilities
- std::make_unique
- std::quoted
- std::exchange
- std::integer_sequence
- std::index_sequence
- std::make_index_sequence
- std::index_sequence_for
#### Container Improvements
- Heterogeneous lookup for std::map, std::set, std::unordered_map, std::unordered_set
#### Threading
- std::shared_timed_mutex
- std::shared_lock

## C++17
### Core Language
- Structured bindings
- if constexpr
- Inline variables
- Fold expressions
- Template argument deduction for class templates
- Class template argument deduction (CTAD)
- Nested namespace definitions
- __has_include preprocessor directive
- [[nodiscard]] attribute
- [[maybe_unused]] attribute
- [[fallthrough]] attribute
- Guaranteed copy elision
- std::launder

### STL
#### Containers
- std::string_view
- std::optional
- std::variant
- std::any
#### Filesystem Library
- std::filesystem::path
- std::filesystem::directory_entry
- std::filesystem::directory_iterator
- std::filesystem::recursive_directory_iterator
- std::filesystem::file_status
- std::filesystem::space_info
- std::filesystem::file_type
- std::filesystem::perms
- std::filesystem::copy_options
- std::filesystem::directory_options
- std::filesystem::create_directory
- std::filesystem::create_directories
- std::filesystem::copy
- std::filesystem::copy_file
- std::filesystem::remove
- std::filesystem::remove_all
- std::filesystem::rename
- std::filesystem::resize_file
- std::filesystem::space
- std::filesystem::last_write_time
- std::filesystem::permissions
- std::filesystem::current_path
- std::filesystem::temp_directory_path
- std::filesystem::exists
- std::filesystem::is_directory
- std::filesystem::is_regular_file
- std::filesystem::is_symlink
- std::filesystem::file_size
- std::filesystem::hard_link_count
#### Algorithms
- std::sample
- std::for_each_n
- std::reduce
- std::transform_reduce
- std::inclusive_scan
- std::exclusive_scan
- std::transform_inclusive_scan
- std::transform_exclusive_scan
- Parallel algorithms (std::execution::seq, std::execution::par, std::execution::par_unseq)
#### Utilities
- std::byte
- std::apply
- std::invoke
- std::is_invocable
- std::is_invocable_r
- std::invoke_result
- std::is_swappable
- std::is_nothrow_swappable
- std::void_t
- std::bool_constant
- std::conjunction
- std::disjunction
- std::negation
- std::clamp
#### Container Improvements
- std::map try_emplace, insert_or_assign
- std::unordered_map try_emplace, insert_or_assign
- std::string_view starts_with, ends_with
#### Threading
- std::shared_mutex
- std::scoped_lock

## C++20
### Core Language
- Concepts
- Constraints and requires clauses
- Constrained templates
- Abbreviated function templates
- Three-way comparison operator (<=>)
- std::strong_ordering
- std::weak_ordering
- std::partial_ordering
- Lambda improvements
  - Stateless lambda call operator as consteval
  - Lambda capture of [this] by value
  - Template lambdas
- Constexpr improvements
  - Constexpr virtual functions
  - Constexpr dynamic memory allocation
  - Constexpr std::string
  - Constexpr std::vector
- Immediate functions (consteval)
- Constant evaluation for non-type template parameters
- std::is_constant_evaluated
- Modules
- Import/export declarations
- Coroutines
  - co_await
  - co_yield
  - co_return
- std::source_location
- std::endian

### STL
#### Containers
- std::span
#### Ranges Library
- std::ranges::range
- std::ranges::input_range
- std::ranges::output_range
- std::ranges::forward_range
- std::ranges::bidirectional_range
- std::ranges::random_access_range
- std::ranges::contiguous_range
- std::ranges::sized_range
- std::ranges::view
- std::ranges::viewable_range
- std::ranges::borrowed_range
- std::ranges::common_range
- std::ranges::range_value_t
- std::ranges::range_reference_t
- std::ranges::range_difference_t
- std::ranges::range_size_t
- std::ranges::begin
- std::ranges::end
- std::ranges::cbegin
- std::ranges::cend
- std::ranges::rbegin
- std::ranges::rend
- std::ranges::crbegin
- std::ranges::crend
- std::ranges::size
- std::ranges::ssize
- std::ranges::empty
- std::ranges::data
- std::ranges::cdata
#### Range Views
- std::ranges::all_view
- std::ranges::ref_view
- std::ranges::owning_view
- std::ranges::filter_view
- std::ranges::transform_view
- std::ranges::take_view
- std::ranges::take_while_view
- std::ranges::drop_view
- std::ranges::drop_while_view
- std::ranges::join_view
- std::ranges::split_view
- std::ranges::counted_view
- std::ranges::common_view
- std::ranges::reverse_view
- std::ranges::elements_view
- std::ranges::keys_view
- std::ranges::values_view
- std::ranges::iota_view
- std::ranges::empty_view
- std::ranges::single_view
- std::ranges::repeat_view
#### Range Adaptors
- std::ranges::views::all
- std::ranges::views::filter
- std::ranges::views::transform
- std::ranges::views::take
- std::ranges::views::take_while
- std::ranges::views::drop
- std::ranges::views::drop_while
- std::ranges::views::join
- std::ranges::views::split
- std::ranges::views::common
- std::ranges::views::reverse
- std::ranges::views::elements
- std::ranges::views::keys
- std::ranges::views::values
- std::ranges::views::iota
- std::ranges::views::empty
- std::ranges::views::single
- std::ranges::views::repeat
#### Range Algorithms
- std::ranges::for_each
- std::ranges::for_each_n
- std::ranges::find
- std::ranges::find_if
- std::ranges::find_if_not
- std::ranges::find_end
- std::ranges::find_first_of
- std::ranges::adjacent_find
- std::ranges::count
- std::ranges::count_if
- std::ranges::mismatch
- std::ranges::equal
- std::ranges::search
- std::ranges::search_n
- std::ranges::copy
- std::ranges::copy_if
- std::ranges::copy_n
- std::ranges::copy_backward
- std::ranges::move
- std::ranges::move_backward
- std::ranges::fill
- std::ranges::fill_n
- std::ranges::transform
- std::ranges::generate
- std::ranges::generate_n
- std::ranges::remove
- std::ranges::remove_if
- std::ranges::replace
- std::ranges::replace_if
- std::ranges::swap_ranges
- std::ranges::reverse
- std::ranges::reverse_copy
- std::ranges::rotate
- std::ranges::rotate_copy
- std::ranges::unique
- std::ranges::unique_copy
- std::ranges::partition
- std::ranges::stable_partition
- std::ranges::sort
- std::ranges::stable_sort
- std::ranges::partial_sort
- std::ranges::partial_sort_copy
- std::ranges::nth_element
- std::ranges::merge
- std::ranges::inplace_merge
- std::ranges::includes
- std::ranges::set_union
- std::ranges::set_intersection
- std::ranges::set_difference
- std::ranges::set_symmetric_difference
- std::ranges::push_heap
- std::ranges::pop_heap
- std::ranges::make_heap
- std::ranges::sort_heap
- std::ranges::min
- std::ranges::max
- std::ranges::minmax
- std::ranges::min_element
- std::ranges::max_element
- std::ranges::minmax_element
- std::ranges::lexicographical_compare
- std::ranges::next_permutation
- std::ranges::prev_permutation
- std::ranges::all_of
- std::ranges::any_of
- std::ranges::none_of
- std::ranges::is_sorted
- std::ranges::is_sorted_until
- std::ranges::is_permutation
- std::ranges::is_heap
- std::ranges::is_heap_until
#### Utilities
- std::bit_cast
- std::starts_with
- std::ends_with
- std::contains
- std::erase
- std::erase_if
- std::format
- std::syncbuf
- std::osyncstream
- std::bind_front
- std::identity
- std::unwrap_reference
- std::unwrap_ref_decay
- std::midpoint
- std::lerp
#### Chrono Extensions
- std::chrono::day
- std::chrono::month
- std::chrono::year
- std::chrono::weekday
- std::chrono::weekday_indexed
- std::chrono::weekday_last
- std::chrono::month_day
- std::chrono::month_day_last
- std::chrono::month_weekday
- std::chrono::month_weekday_last
- std::chrono::year_month
- std::chrono::year_month_day
- std::chrono::year_month_day_last
- std::chrono::year_month_weekday
- std::chrono::year_month_weekday_last
- std::chrono::local_time
- std::chrono::zoned_time
- std::chrono::time_zone
- std::chrono::sys_time
- std::chrono::utc_clock
- std::chrono::tai_clock
- std::chrono::gps_clock
- std::chrono::file_clock
- std::chrono::local_days
- std::chrono::local_seconds
#### Bit Operations
- std::bit_ceil
- std::bit_floor
- std::bit_width
- std::countl_zero
- std::countl_one
- std::countr_zero
- std::countr_one
- std::has_single_bit
- std::popcount
- std::rotl
- std::rotr
#### Threading
- std::jthread
- std::stop_token
- std::stop_source
- std::latch
- std::barrier
- std::semaphore
- std::counting_semaphore
- std::atomic_ref
- std::atomic_flag enhancements

## C++23
### Core Language
- Range-based for loop with initializer
- Explicit this parameter in lambdas
- [[assume]] attribute
- Multidimensional array subscript operator
- Static operator()
- Static operator[]
- Deducing this
- if consteval

### STL
#### Containers
- std::flat_map
- std::flat_set
- std::mdspan
- std::generator
#### Range Views
- std::ranges::zip_view
- std::ranges::zip_transform_view
- std::ranges::adjacent_view
- std::ranges::adjacent_transform_view
- std::ranges::chunk_view
- std::ranges::chunk_by_view
- std::ranges::slide_view
- std::ranges::stride_view
- std::ranges::cartesian_product_view
#### Range Adaptors
- std::ranges::views::zip
- std::ranges::views::zip_transform
- std::ranges::views::adjacent
- std::ranges::views::adjacent_transform
- std::ranges::views::chunk
- std::ranges::views::chunk_by
- std::ranges::views::slide
- std::ranges::views::stride
- std::ranges::views::cartesian_product
#### Range Algorithms
- std::ranges::fold_left
- std::ranges::fold_right
- std::ranges::fold_left_first
- std::ranges::fold_right_last
- std::ranges::find_last
- std::ranges::find_last_if
- std::ranges::find_last_if_not
- std::ranges::contains
- std::ranges::starts_with
- std::ranges::ends_with
- std::ranges::to
#### Utilities
- std::expected
- std::print
- std::println
- std::stacktrace
- std::stacktrace_entry
- std::basic_stacktrace
- std::to_underlying
- std::byteswap
- std::assume_aligned
- std::unreachable
- std::invoke_r
- std::forward_like
- std::move_only_function
#### Container Improvements
- std::string constexpr support
- std::vector constexpr support
- std::optional monadic operations (and_then, transform, or_else)
- std::variant monadic operations (and_then, transform)
- std::span subspan, as_bytes, as_writable_bytes
- std::reference_wrapper improvements
#### Filesystem Improvements
- std::filesystem::recursive_directory_iterator improvements
#### Chrono Improvements
- std::chrono::parse
- std::chrono::format
- std::chrono::zoned_traits
- std::chrono::choose
- std::chrono::leap_second
#### Modules
- import std (standard library module)

## C++26 (In Progress, as of September 2025)
### Core Language
- Contracts (deferred to post-C++26, under discussion)
- Pattern matching (proposed)
- Reflection (std::reflect, proposed)
- std::meta (meta-programming, proposed)
- Extended floating-point types (std::float16_t, std::float32_t, std::float64_t, std::float128_t)

### STL
#### Containers
- std::mdspan improvements (dynamic_extent)
- std::flat_map improvements
- std::flat_set improvements
#### Utilities
- std::text_encoding
- std::spanstream
- std::out_ptr
- std::inout_ptr
- std::format improvements (range formatting)
- std::print improvements
- std::bit_int
#### Range Algorithms
- std::ranges::inplace_transform
- std::ranges::inplace_sort
- std::ranges::inplace_merge
#### Container Improvements
- std::string_view improvements
- std::u8string_view
- std::u8string improvements
- std::optional::and_then
- std::variant::and_then
- std::expected monadic operations (and_then, transform, or_else)
#### Chrono Extensions
- std::chrono::tai_clock improvements
- std::chrono::gps_clock improvements
- std::chrono::leap_second support
#### Math Functions
- std::frexp
- std::modf
- std::remquo
- std::lerp improvements
- std::complex improvements
#### SIMD Support
- std::simd
#### Threading
- std::hazard_pointer
- std::rcu (reader-copy-update)
- std::execution (executors for parallelism)