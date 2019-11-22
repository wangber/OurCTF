package main

import "fmt"

func main() {
	fmt.Println(mySqrt(4))
}

/*
func mySqrt(x int) int {
	result := 0
	for result*result < x {
		result++
	}
	if result*result == x {
		return result
	}
	return result - 1

}
*/
func mySqrt(x int) int {
	result := int((0 + x) / 2)
	max := result
	min := 0
	for max != min {
		if result*result > x {
			max = result
		} else if result*result < x {
			if (result+1)*(result+1) > x {
				return result
			}
			min = result
		} else {
			return result
		}
		result = int((max + min) / 2)
	}
	return x

}
