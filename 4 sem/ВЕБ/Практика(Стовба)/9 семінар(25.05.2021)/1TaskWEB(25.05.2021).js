let cart =[];
let price = [20.5, 19.5, 25.25, 30.5, 100.0];

function countbook() {
	let x = price[document.getElementById("books").selectedIndex];
	let n = document.getElementById("coun").value;
	if (n !== "") {
		document.getElementById("sum").value = n * x;
	} 
}


function count() {
	let y = document.getElementById("sum").value;
	if (y !== "") {
		let x = parseInt(y, 10);
		let q1 = 0.0, q2 = 0.0, q3 = 0.0;
		if (document.getElementById("radio1").checked) q1 = x * 0.05;
		if (document.getElementById("radio2").checked) q2 = x * 0.15;
		if (document.getElementById("radio3").checked) q3 = x * 0.1;
		let r = 1.4;
		r = x + q1 + q2 + q3;
		document.getElementById("res").value = r;
	} else {
		alert("Вкажіть кількість");
	}
}

function clear() {
	document.getElementById('books').getElementsByTagName('option')[0].selected = 'selected';
	document.getElementById('coun').value = null;
	document.getElementById('sum').value = null;
	document.getElementById("radio1").checked = true;
	document.getElementById("radio2").checked = false;
	document.getElementById("radio3").checked = false;
	document.getElementById('res').value = null;
	document.getElementById('nam').value = null;
	document.getElementById('loc').value = null;
}

function formtaable() {
	let table = '<table cellspacing="2" border="1" cellpadding="5"><tr style="font-weight: bold;"><td>Назва</td> <td>Імя</td> <td>Адреса</td> <td>Доставка</td> <td>Упаковка</td> <td>Кількість</td> <td>Ціна</td></tr>';
	for (let i = 0; i < cart.length; i++) {
		table += "<tr>";
		table += "<td>" + cart[i][0] + "</td>";
		table += "<td>" + cart[i][6] + "</td>";
		table += "<td>" + cart[i][7] + "</td>";
		if (cart[i][3]) table += "<td>" + "Поштою" + "</td>";
		if (cart[i][4]) table += "<td>" + "Доставка до дому" + "</td>";
		if (cart[i][5]) table += '<td style="text-align: center;">' + "так" + "</td>";
		else table += '<td style="text-align: center;">' + "ні" + "</td>";
		table += '<td style="text-align: center;">' + cart[i][1] + "</td>";
		table += '<td style="text-align: center;">' + cart[i][2] + "</td>";
		table += "</tr>";
	}
	document.getElementById('tab').innerHTML  = table;
}

function add() {
	if (document.getElementById('res').value == "" || document.getElementById('nam').value == "" || document.getElementById('loc').value == "") { alert("Заповніть поля"); } 
    else {
		let name = document.getElementById("books").value;
		if (name == "Теорія всього - 20.5") name = "Теорія всього";
		if (name == "Бог як ілюзія - 19.5") name = "Бог як ілюзія";
		if (name == "Покоління Z - 25.25") name = "Покоління Z";
		if (name == "Світ в горіховій шкаралупі - 30.5") name = "Світ в горіховій шкаралупі";
		if (name == "Фієста - 100.0") name = "Фієста";
		let numb = document.getElementById("coun").value;
		let cost = document.getElementById("res").value;
		let del1 = document.getElementById("radio1").checked;
		let del2 = document.getElementById("radio2").checked;
		let del3 = document.getElementById("radio3").checked;
		let im = document.getElementById("nam").value;
		let ad = document.getElementById("loc").value;
		let el = [name, numb, cost, del1, del2, del3, im, ad];
		cart.push(el);
		clear();
		formtaable()
	}
}

let elem = document.getElementById("coun");
elem.addEventListener('change', countbook);
elem = document.getElementById("books");
elem.addEventListener('change', countbook);
elem = document.getElementById("result");
elem.addEventListener('click', count);
elem = document.getElementById("clr");
elem.addEventListener('click', clear);
elem = document.getElementById("vid");
elem.addEventListener('click', add);s