package main

import(
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var seed = rand.NewSource(time.Now().UnixNano())
var random = rand.New(seed)
var BOUND = 10

type Arrays struct {
	arrayList [][]int
	sync.WaitGroup
}

func createArrays(arraySize int) *Arrays {
	return &Arrays{
		arrayList: initializeArray(arraySize),
	}
}

func initializeArray(arraySize int) [][]int {
	arrayList := make([][]int, arraySize, arraySize)
	for i := 0; i < arraySize; i++ {
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

func multiplying(a *Arrays, b *Arrays, c *Arrays, arraySize int) {
	for i := 0; i < arraySize; i++ {
		for j := 0; j < arraySize; j++ {
			c.arrayList[i][j] = 0
			for k := 0; k < arraySize; k++ {
				c.arrayList[i][j] += a.arrayList[i][k] * b.arrayList[k][j]
			}
		}
	}
	//printArrays(c)
}

func multiplyingTape(a *Arrays, b *Arrays, c *Arrays, group *sync.WaitGroup, arraySize int) {
	group.Add(arraySize)
	for i := 0; i < arraySize; i++ {
		go tape(a, b, c, group, i, arraySize)
	}
	group.Wait()
	//printArrays(c)

}

func tape(a *Arrays, b *Arrays, c *Arrays, group *sync.WaitGroup, row, arraySize int) {
	counter := 0
	index := row
	for counter < arraySize {
		cell := 0
		for i := 0; i < arraySize; i++ {
			cell += a.arrayList[row][i] * b.arrayList[i][index]
		}

		c.arrayList[row][index] = cell
		counter += 1
		index = (index + 1) % arraySize
	}

	group.Done()
}

func main() {

	for i := 100; i < 150; i += 50 {

		a := createArrays(i)
		b := createArrays(i)
		c1 := createArrays(i)
		c2 := createArrays(i)
		group := new(sync.WaitGroup)
		multiplying(a, b, c1, i)
		start := time.Now()
		multiplyingTape(a, b, c2, group, i)
		elapsed := time.Since(start)
		fmt.Println(i, " : ", elapsed)
	}
}