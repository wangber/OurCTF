package main

import "fmt"

func main() {
	a := "yyyyyy"
	b := "lllllllll"
	fmt.Println(strStr(a, b))
}
func strStr(haystack string, needle string) int {
	if len(haystack) < len(needle) {
		return -1
	}
	if len(needle) == 0 {
		return 0
	}
	if len(haystack) == 0 {
		return -1
	}

	for index, i := range haystack {
		if index+len(needle) > len(haystack) {
			return -1
		}
		if string(i) == string(needle[0]) {
			if string(haystack[index:index+len(needle)]) == needle {
				return index
			}
		} else {
			continue
		}
	}
	return -1
}
