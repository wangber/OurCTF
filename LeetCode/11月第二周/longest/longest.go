package main

import (
	"fmt"
)

func main() {
	a := []string{"a"}
	fmt.Println(longestCommonPrefix(a))
}

func longestCommonPrefix(strs []string) string {
	//find the shortest strting
	var shortest string
	if len(strs) <= 0 {
		return ""
	}
	shortest = strs[0]
	for _, s := range strs {
		if len(s) <= len(shortest) {
			shortest = s
		}
	}
	if len(shortest) <= 0 {
		return ""
	}

	max := 0
Stringrow:
	for i := 0; i < len(shortest); i++ {
		for _, s := range strs {
			if s[i] == shortest[i] {
				continue
			} else {
				break Stringrow
			}
		}
		max = max + 1
	}

	return shortest[:max]
}
