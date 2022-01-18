package main

import (
	"fmt"
	"sync"
	"time"
)

type job func(in, out chan interface{})

func ExecutePipeline(jobs ...job) {
	in := make([]chan interface{}, 0, len(jobs))
	for i := 0; i < len(jobs); i++ {
		in = append(in, make(chan interface{}, 100))
	}

	wg := &sync.WaitGroup{}
	for i := range jobs {
		wg.Add(1)
		go func(counter int) {
			if counter != 0 {
				jobs[counter](in[counter-1], in[counter])
			} else {
				jobs[counter](in[counter], in[counter])
			}
			wg.Done()
			close(in[counter])
		}(i)
	}
	wg.Wait()
}

func main() {
	var storage job = func(in, out chan interface{}) {
		for i := 0; i < 10; i++ {
			out <- i
		}
	}
	var ivanov job = func(in, out chan interface{}) {
		for val := range in {
			time.Sleep(300 * time.Millisecond)
			out <- val
			fmt.Printf("Ivanov took out from storage %v\n", val)
		}
	}
	var petrov job = func(in, out chan interface{}) {
		for val := range in {
			time.Sleep(200 * time.Millisecond)
			out <- val
			fmt.Printf("Petrov loaded into a truck. %v\n", val)
		}
	}
	var nechiporchuk job = func(in, out chan interface{}) {
		sum := 0
		for val := range in {
			time.Sleep(100 * time.Millisecond)
			sum += val.(int)
			fmt.Printf("Nechiporchuk added to the cost of the stolen %v C.U.\n", val)
		}
		fmt.Printf("Nechiporchuk counted %v C.U. by the end\n", sum)
	}

	jobs := []job{
		storage,
		ivanov,
		petrov,
		nechiporchuk,
	}

	ExecutePipeline(jobs...)
}
