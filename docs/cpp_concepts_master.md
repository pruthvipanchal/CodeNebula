# CodeNebula: C++ Concepts (Core and STL)

This document lists all C++ concepts, including core language features and Standard Template Library (STL) components, from C++98 to C++26, organized by standard.

## C++98
### Core Language
- Basic types (int, float, double, char, bool, etc.)
- Enumerations (unscoped enums)
- Unions
- Bitfields
- sizeof operator
- Pointers
- References
- Arrays
- Functions
- Function overloading
- Default arguments
- Inline functions
- Function pointers
- Pointers to members
- Classes
- Objects
- Constructors
- Copy constructor
- Destructors
- Copy assignment operator
- Conversion functions
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
- Nested classes
- Local classes
- Operator overloading
- Templates
  - Function templates
  - Class templates
- Exception handling (try, catch, throw)
- Namespaces
- Scope resolution operator (::)
- Dynamic memory management (new, delete)
- Type casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
- Run-time type information (RTTI)
- Typeid
- Storage class specifiers (static, extern, register)
- Volatile keyword
- Mutable keyword
- Conditional (ternary) operator
- Comma operator
- Preprocessor directives (#define, #include, #ifdef, #ifndef, #pragma, etc.)

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
- std::bitset
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
#### Numeric Algorithms
- std::accumulate
- std::inner_product
- std::partial_sum
- std::adjacent_difference
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
- std::numeric_limits
#### Numerics
- std::valarray
- std::complex
#### Memory
- std::allocator
#### Exception Classes
- std::exception
- std::runtime_error
- std::logic_error
- std::out_of_range
- std::invalid_argument
- std::overflow_error
- std::underflow_error
- std::length_error
- std::domain_error
- std::range_error
- std::bad_alloc
- std::bad_cast
- std::bad_typeid
- std::bad_exception
#### Localization
- std::locale
- std::locale::facet
#### Input/Output
- std::iostream
- std::istream
- std::ostream
- std::fstream
- std::ifstream
- std::ofstream
- std::stringstream
- std::streambuf
- std::ios_base
- std::cin, std::cout, std::cerr, std::clog
#### C Library Wrappers
- \<cmath\>
- \<cstdlib\>
- \<cstring\>
- \<cstdio\>
- \<cctype\>
- \<climits\>
- \<cfloat\>
- \<cassert\>
- \<ctime\>

## C++03
### Core Language
- Value initialization (refined rules)
- Explicit template argument specification for constructors
- POD (Plain Old Data) type definition refinement

### STL
#### Containers
- std::vector\<bool\> improvements
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
- In-class member initializers (NSDMI)
- Explicit conversion operators
- override keyword
- final keyword
- noexcept specifier
- Generalized constant expressions (constexpr)
- User-defined literals
- Raw string literals
- Trailing return types
- extern template
- Thread-local storage (thread_local)
- Alignas and alignof
- char16_t, char32_t
- Unicode string literals (u"", U"", u8"")
- Inheriting constructors
- Unrestricted unions
- Attributes (e.g., [[noreturn]], [[carries_dependency]])
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
- std::iota
#### Function Objects
- std::function
- std::bind
- std::ref
- std::cref
- std::mem_fn
#### Type Traits
- std::is_integral
- std::is_floating_point
- std::is_pointer
- std::is_array
- std::is_class
- std::is_enum
- std::is_void
- std::is_same
- std::is_base_of
- std::is_convertible
- std::is_trivially_copyable
- std::is_trivially_constructible
- std::is_trivially_destructible
- std::is_standard_layout
- std::is_pod
- std::integral_constant
- std::true_type
- std::false_type
- std::enable_if
- std::conditional
- std::common_type
- std::result_of (deprecated in C++17)
- std::underlying_type
- std::remove_reference
- std::remove_cv
- std::remove_const
- std::remove_volatile
- std::add_lvalue_reference
- std::add_rvalue_reference
- std::make_signed
- std::make_unsigned
- std::decay
- std::aligned_storage (deprecated in C++23)
- std::aligned_union (deprecated in C++23)
#### Hashing
- std::hash
#### Error Handling
- std::system_error
- std::error_code
- std::error_category
- std::error_condition
#### Utilities
- std::tuple
- std::forward_as_tuple
- std::make_pair (move-aware)
- std::piecewise_construct
- std::type_index
- std::to_string
- std::stoi, std::stol, std::stoll
- std::stof, std::stod, std::stold
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
- Aggregate member initialization relaxation

### STL
#### Utilities
- std::make_unique
- std::quoted
- std::exchange
- std::integer_sequence
- std::index_sequence
- std::make_index_sequence
- std::index_sequence_for
- std::get\<Type\>() for tuples
#### Container Improvements
- Heterogeneous lookup for std::map, std::set, std::unordered_map, std::unordered_set
- Transparent operator functors (std::less\<\>, std::greater\<\>, etc.)
#### Type Traits
- std::is_final
#### Threading
- std::shared_timed_mutex
- std::shared_lock

## C++17
### Core Language
- Structured bindings
- if constexpr
- Init-statements for if and switch
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
- constexpr lambda expressions
- Hexadecimal floating-point literals
- Using-declaration for parameter packs
- Aggregate initialization with base classes
- Non-type template parameters auto

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
- std::from_chars
- std::to_chars
- std::not_fn
- std::gcd
- std::lcm
- std::as_const
- std::make_from_tuple
- std::has_unique_object_representations
- std::is_aggregate
- std::hardware_destructive_interference_size
- std::hardware_constructive_interference_size
#### Polymorphic Memory Resources
- std::pmr::memory_resource
- std::pmr::polymorphic_allocator
- std::pmr::monotonic_buffer_resource
- std::pmr::unsynchronized_pool_resource
- std::pmr::synchronized_pool_resource
#### Container Improvements
- std::map try_emplace, insert_or_assign
- std::unordered_map try_emplace, insert_or_assign
- std::string_view starts_with, ends_with
- Node handle API (extract, insert with node handle)
#### Threading
- std::shared_mutex
- std::scoped_lock

## C++20
### Core Language
- Concepts
- Constraints and requires clauses
- Constrained templates
- Abbreviated function templates
- Three-way comparison operator (\<=\>)
- std::strong_ordering
- std::weak_ordering
- std::partial_ordering
- Designated initializers
- using enum
- char8_t
- constinit keyword
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
- [[likely]] and [[unlikely]] attributes
- [[no_unique_address]] attribute
- Conditional explicit (explicit(bool))
- Non-type template parameters of class type
- Destroying delete
- Feature test macros (__cpp_concepts, __cpp_lib_ranges, etc.)
- Aggregate initialization improvements

### STL
#### Containers
- std::span
#### Concepts Library
- std::same_as
- std::derived_from
- std::convertible_to
- std::integral
- std::floating_point
- std::signed_integral
- std::unsigned_integral
- std::common_reference_with
- std::common_with
- std::assignable_from
- std::swappable
- std::destructible
- std::constructible_from
- std::default_initializable
- std::move_constructible
- std::copy_constructible
- std::equality_comparable
- std::totally_ordered
- std::regular
- std::semiregular
- std::invocable
- std::predicate
- std::relation
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
- std::format_to
- std::format_to_n
- std::formatted_size
- std::vformat
- std::make_format_args
- std::syncbuf
- std::osyncstream
- std::bind_front
- std::identity
- std::unwrap_reference
- std::unwrap_ref_decay
- std::midpoint
- std::lerp
- std::to_address
- std::assume_aligned
- std::make_shared_for_overwrite
- std::make_unique_for_overwrite
#### Mathematical Constants
- std::numbers::pi
- std::numbers::e
- std::numbers::sqrt2
- std::numbers::sqrt3
- std::numbers::ln2
- std::numbers::ln10
- std::numbers::log2e
- std::numbers::log10e
- std::numbers::phi
- std::numbers::inv_pi
- std::numbers::inv_sqrtpi
- std::numbers::egamma
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
- std::atomic_wait
- std::atomic_notify_one
- std::atomic_notify_all

## C++23
### Core Language
- Deducing this
- Explicit this parameter in lambdas
- [[assume]] attribute
- Multidimensional array subscript operator
- Static operator()
- Static operator[]
- if consteval
- size_t literal suffix (uz/zu)
- \#warning preprocessor directive
- \#elifdef, \#elifndef preprocessor directives
- auto(x) and auto{x} decay-copy expressions
- Constexpr improvements (more operations permitted)
- Lambda trailing return type scope changes

### STL
#### Containers
- std::flat_map
- std::flat_set
- std::flat_multimap
- std::flat_multiset
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
- std::ranges::repeat_view
- std::ranges::join_with_view
- std::ranges::as_rvalue_view
- std::ranges::as_const_view
- std::ranges::enumerate_view
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
- std::ranges::views::repeat
- std::ranges::views::join_with
- std::ranges::views::as_rvalue
- std::ranges::views::as_const
- std::ranges::views::enumerate
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
- std::unreachable
- std::invoke_r
- std::forward_like
- std::move_only_function
- std::out_ptr
- std::inout_ptr
- std::spanstream
- std::basic_string::contains
- std::basic_string_view::contains
#### Container Improvements
- std::string constexpr support
- std::vector constexpr support
- std::optional monadic operations (and_then, transform, or_else)
- std::variant monadic operations
- std::expected monadic operations (and_then, transform, or_else)
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

## C++26
### Core Language
- Contracts (preconditions, postconditions, assertions)
- Reflection (P2996, static reflection)
- std::meta (compile-time meta-programming)
- Pack indexing
- Placeholder variables with multiple _
- Structured bindings as conditions
- constexpr cast from void*
- Erroneous behavior for uninitialized reads
- User-generated static_assert messages
- Extended floating-point types (std::float16_t, std::float32_t, std::float64_t, std::float128_t)
- Pattern matching (proposed)

### STL
#### Containers
- std::inplace_vector
- std::mdspan improvements (dynamic_extent)
- std::flat_map improvements
- std::flat_set improvements
#### Utilities
- std::text_encoding
- std::format improvements (range formatting)
- std::print improvements
- std::copyable_function
- std::function_ref
#### Saturation Arithmetic
- std::add_sat
- std::sub_sat
- std::mul_sat
- std::div_sat
- std::saturate_cast
#### Compile-Time Utilities
- std::is_within_lifetime
#### Container Improvements
- std::string_view improvements
- std::u8string_view
- std::u8string improvements
#### SIMD Support
- std::simd
- std::simd_mask
- std::simd::reduce
#### Execution Framework
- std::execution (senders/receivers)
- std::execution::scheduler
- std::execution::sender
- std::execution::receiver
- std::execution::then
- std::execution::when_all
- std::execution::let_value
- std::execution::bulk
- std::execution::split
- std::execution::ensure_started
#### Threading
- std::hazard_pointer
- std::rcu (reader-copy-update)
