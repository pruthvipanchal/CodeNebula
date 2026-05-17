// Compile: go run generics.go
// Output:
//   doubled: [2 4 6 8]
//   evens: [2 4]
//   stack push/pop: 3 2 1
package main

import "fmt"

func Map[T, U any](s []T, f func(T) U) []U {
	result := make([]U, len(s))
	for i, v := range s {
		result[i] = f(v)
	}
	return result
}

func Filter[T any](s []T, pred func(T) bool) []T {
	var out []T
	for _, v := range s {
		if pred(v) {
			out = append(out, v)
		}
	}
	return out
}

type Stack[T any] struct{ items []T }

func (s *Stack[T]) Push(v T) { s.items = append(s.items, v) }
func (s *Stack[T]) Pop() (T, bool) {
	if len(s.items) == 0 {
		var zero T
		return zero, false
	}
	v := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return v, true
}

func main() {
	nums := []int{1, 2, 3, 4}
	doubled := Map(nums, func(n int) int { return n * 2 })
	fmt.Println("doubled:", doubled)

	evens := Filter(nums, func(n int) bool { return n%2 == 0 })
	fmt.Println("evens:", evens)

	var st Stack[int]
	st.Push(1)
	st.Push(2)
	st.Push(3)
	fmt.Print("stack push/pop:")
	for {
		v, ok := st.Pop()
		if !ok {
			break
		}
		fmt.Print(" ", v)
	}
	fmt.Println()
}
