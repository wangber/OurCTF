package main

import "fmt"

func main() {
	nums := []int{1, 2, 3, 5, 8, 5, 4, 2}
	val := 2

	fmt.Println(removeElement(nums, val))

}
func removeElement(nums []int, val int) int {
	for inornot(nums, val) == true {
		//in then remove
		remove(&nums, val)
	}
	fmt.Println(nums)
	return len(nums)

}

func inornot(nums []int, val int) bool {
	for _, i := range nums {
		if i == val {
			return true
		}
	}
	return false

}
func remove(nums *[]int, val int) {
	for index, i := range *nums {
		if val == i {
			*nums = append((*nums)[:index], (*nums)[index+1:]...)
			break
		}
	}
}
