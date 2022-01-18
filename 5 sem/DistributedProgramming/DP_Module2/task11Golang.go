package main

import (
"fmt"
"math/rand"
"strconv"
"sync"
"time"
)
type Airplane struct {
	name       string
	counter int
}
func (airplane Airplane) randomPlaces(wg *sync.WaitGroup) {
	distances := []int{1, 2, 3, 1, 4}
	places := []string{"Boryspil", "Juliany", "Horodnia", "Denver", "Odessa"}
	place := rand.Intn(len(distances))
	fmt.Println(airplane.name, "======>", places[place])
	<-time.After(time.Second * time.Duration(distances[place]))
	fmt.Println(airplane.name, "=>", places[place])
	defer wg.Done()
}
func arrive(waitGROUP *sync.WaitGroup, iterator int, af int) {
	<-time.After(time.Second * time.Duration(af))
	airplane := Airplane{strconv.FormatInt(int64(iterator), 10), 2}
	fmt.Println(airplane.name, "airplane", "arrive")
	waitGROUP.Add(1)
	go airplane.randomPlaces(waitGROUP)
	defer waitGROUP.Done()
}
func main() {
	var waitGROUP sync.WaitGroup
	for i := 0; i < 10; i++ {
		waitGROUP.Add(1)
		go arrive(&waitGROUP, i, rand.Intn(i+1))
	}
	waitGROUP.Wait()
}
