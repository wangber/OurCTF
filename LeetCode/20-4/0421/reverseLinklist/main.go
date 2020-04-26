package main

import (
	"fmt"
)

type ListNode struct {
      Val int
      Next *ListNode
  }

func reverseList(head *ListNode) *ListNode {
	//使用插入法
	//从头结点开始遍历节点，每遍历一个节点就将节点插入到头结点的后面
	now := head.Next.Next
	head.Next.Next = nil
	for now.Next != nil{
		cu := now.Next
		now.Next = head.Next
		head.Next = now
		now = cu
	}
	return now
}
func main() {
	//初始化链表
	var L *ListNode
	L = &ListNode{
		Val:1,
	}
	L2 := &ListNode{
		Val:2,
	}
	L.Next = L2
	L3 := &ListNode{
		Val:3,
	}
	L2.Next = L3
	L3.Next = nil
	head := &ListNode{
		Next:L,
	}
	head.Next = L
	reverseList(head)
	for now := head;now.Next!=nil;{
		fmt.Println(now.Val)
		now = now.Next
	}
}
