package main

import "fmt"

func main() {
	var nums = []int{1, 3, 5, 7}
	var tar = 6
	fmt.Println(searchInsert(nums, tar))
}

/*
func searchInsert(nums []int, target int) int {
	maxindex := len(nums) - 1
	minindex := 0
	if len(nums) == 0 {
		return 0
	}
	if len(nums) == 1 {
		if nums[0] >= target {
			return 0
		}
		return 1

	}
	var halfindex = int((maxindex + minindex) / 2)
	for maxindex-minindex >= 1 {
		halfindex = int((maxindex + minindex) / 2)
		if target < nums[halfindex] {
			maxindex = halfindex
		} else if target > nums[halfindex] {
			minindex = halfindex
		} else {
			return halfindex
		}
		halfindex = int((maxindex + minindex) / 2)
	}
	if maxindex == len(nums)-1 {
		return halfindex + 2
	}
	if nums[halfindex] < target {
		return halfindex + 1
	}

	return halfindex

}
*/
func searchInsert(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}
	if len(nums) == 1 {
		if nums[0] >= target {
			return 0
		}
		return 1
	}
	a := 0
	for index, num := range nums {
		if target > num {
			a++
			continue
		} else {
			return index
		}
	}
	return a
}
