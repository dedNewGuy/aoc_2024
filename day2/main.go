package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func main() {
	filename := "real_input.txt"
	dat, err := os.ReadFile(filename)
	if err != nil {
		os.Exit(69)
	}

	dat_string := string(dat)
	split_string := strings.Split(dat_string, "\n")
	safe_count := 0
	for _, line := range split_string[:len(split_string) - 1]  {
		line_arr := strings.Split(line, " ")
		ints := make([]int, len(line_arr))
		for i, s := range line_arr {
			ints[i], _ = strconv.Atoi(s)
		}
		
		// is_monotonic := isNumArrStrictMonotonic(ints)
		// is_in_range := isDiffRange(ints, 1, 3)
		// fmt.Println(is_monotonic && is_in_range)
		// if is_monotonic && is_in_range {
		// 	safe_count += 1
		// }
		if isSafeWithOneRemoval(ints) {
			safe_count += 1
		}
	}
	
	fmt.Println(safe_count)
}

func isDiffRange(arr []int, min, max float64) bool {
	is_in_range := false
	for i := 0; i < len(arr) - 1; i++ {
		diff := math.Abs(float64(arr[i] - arr[i + 1]))
		if diff >= min && diff <= max {
			is_in_range = true
		} else {
			is_in_range = false			
			break;
		}
	}
	return is_in_range
}

func isNumArrStrictMonotonic(arr []int) bool {
	is_strict_asc := false
	is_strict_desc := false
	
	for i := 0; i < len(arr) - 1; i++ {
		if arr[i] < arr[i + 1] {
			is_strict_asc = true
		} else {
			is_strict_asc = false
			break;
		}
	}

	for i := 0; i < len(arr) - 1; i++ {
		if arr[i] > arr[i + 1] {
			is_strict_desc = true
		} else {
			is_strict_desc = false
			break;
		}
	}

	return is_strict_asc || is_strict_desc
}

func isSafeWithOneRemoval(arr []int) bool {
	if isNumArrStrictMonotonic(arr) && isDiffRange(arr, 1, 3) {
		return true
	}

	for i := range arr {
		// Remove each element once
		// Unpack and append it to new slices
		reduced := append([]int{}, arr[:i]...)
		reduced = append(reduced, arr[i+1:]...)
		if isNumArrStrictMonotonic(reduced) && isDiffRange(reduced, 1, 3) {
			return true
		}
	}

	return false
}
