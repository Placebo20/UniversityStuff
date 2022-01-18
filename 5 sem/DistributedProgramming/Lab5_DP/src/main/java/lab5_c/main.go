package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var seed = rand.NewSource(time.Now().UnixNano())
var random = rand.New(seed)
var BOUND = 5

type Arrays struct {
	arrayList [][]int
	sync.WaitGroup
}

func NewArrays(n, arraySize int) *Arrays {
	return &Arrays{
		arrayList: initializeArray(n, arraySize),
	}
}

func initializeArray(n, arraySize int) [][]int {
	arrayList := make([][]int, n, arraySize)
	for i := 0; i < n; i++ {
		arrayList[i] = generateArray(arraySize)
	}
	return arrayList
}

func generateArray(arraySize int) []int {
	array := make([]int, arraySize)
	for i := 0; i < arraySize; i++ {
		array[i] = random.Intn(BOUND)
	}
	return array
}

func printArrays(list *Arrays) {
	for _, i := range list.arrayList {
		fmt.Println(i)
	}
	fmt.Println()
}

func ArraySimulator(list *Arrays, group *sync.WaitGroup, n, arraySize int) {
	stopFlag := false
	for !stopFlag {
		group.Add(n)
		for i := 0; i < n; i++ {
			go changeElement(list, group, i, arraySize)
		}
		group.Wait()
		if checkArrayRule(list, n) {
			stopFlag = true
			fmt.Println("Arrays sum are equal")
		}
		printArrays(list)
	}
}

func changeElement(list *Arrays, group *sync.WaitGroup, index, arraySize int) {
	elemToChange := random.Intn(arraySize)
	operation := random.Intn(2)
	switch operation {
	case 0: // ++
		if list.arrayList[index][elemToChange] < BOUND {
			list.arrayList[index][elemToChange]++
		}
	case 1: // --
		if list.arrayList[index][elemToChange] > BOUND*-1 {
			list.arrayList[index][elemToChange]--
		}
	}
	group.Done()
}

func checkArrayRule(list *Arrays, n int) bool {
	sum := make([]int, n)
	for i := 0; i < n; i++ {
		counter := 0
		for _, j := range list.arrayList[i] {
			counter += j
		}
		sum[i] = counter
	}

	if checkAllEqual(sum) {
		return true
	} else {
		return false
	}
}

func checkAllEqual(array []int) bool {
	fmt.Println("Sum: ", array)
	for i := range array {
		if array[0] != array[i] {
			return false
		}
	}
	return true
}

func main() {
	const (
		N       = 3
		ArrSize = 10
	)

	arr := NewArrays(N, ArrSize)
	group := new(sync.WaitGroup)
	ArraySimulator(arr, group, N, ArrSize)
}