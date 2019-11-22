package main

import "fmt"

func main() {
	var li = []int{1, 1, 1, 2, 5, 6, 6, 6, 8, 8, 8, 9}
	fmt.Println(removeDuplicates(li))
}

func removeDuplicates(nums []int) int {
	//set one flag
	if len(nums) == 0 {
		return 0
	}

	flag := nums[0]
	var repeatindex = []int{}
	for index := range nums {
		if len(nums) > index+1 {
			if nums[index+1] == flag {
				repeatindex = append(repeatindex, index+1)
			} else {
				flag = nums[index+1]
			}
		} else {
			break
		}

	}
	remove(&nums, repeatindex)

	return len(nums)
}
func remove(nums *[]int, repeatindex []int) {
	for index, i := range repeatindex {
		*nums = append((*nums)[:i-index], (*nums)[i-index+1:]...)
	}
}
