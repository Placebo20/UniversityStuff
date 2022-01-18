const arr11 = [1, 2, 3];
const arr12 = [1, 0, -1];
console.log([...new Set([...arr_1_1, ...arr_1_2])])

const arr2 = [-1, 2, -3, 4, 5];
console.log(arr_2.filter(it => it > 0))

const arr3 = [1, 2, 3, 4, 5];
console.log(arr_3.find(it => it === 0) === 0 ? 'Equals' : 'Not Equals')

const arr4 = [1, 2, 3, 4, 5];
console.log(arr_4.indexOf(5))

const arr5 = [1, 2, 3, 4, 5];
console.log(arr_5.reduce((a, sum) => a * sum, 1))

const arr61 = ['a', 'bb', 'abc']
console.log(arr_6_1.sort())

const arr62 = [1, 4, -15, -3, 0]
console.log(arr62.sort((a, b) => Math.abs(a) - Math.abs(b)))