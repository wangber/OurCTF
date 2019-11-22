package main

import "fmt"

func main() {
	s := "{}{}[][{}}}}[))))))})]"
	fmt.Println(isValid(s))
}

func isValid(s string) bool {
	a := []string{}
	for _, i := range s {
		j := string(i)
		if j == "{" || j == "[" || j == "(" {
			//push
			a = append(a, j)
		} else {
			if len(a) == 0 {
				return false
			}
			if ispair(a[len(a)-1], j) {
				//pop
				a = a[:len(a)-1]
			} else {
				return false
			}

		}

	}
	if len(a) == 0 {
		return true
	}
	return false
}

//define one function to judge weather the bracket is one pair
func ispair(a string, b string) bool {
	switch a {
	case "(":
		return b == ")"
	case "{":
		return b == "}"
	case "[":
		return b == "]"
	}
	return false
}
