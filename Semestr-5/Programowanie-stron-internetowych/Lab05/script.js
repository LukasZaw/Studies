function zgadnij(){
    const num = Math.ceil(Math.random() * 10);
    console.log(num);
    
    const get = prompt("Zgadnij liczbe: ")
    console.log(get);
    
    if(num == get){
        alert("Zgadłeś liczbe: " + num);
    }
    else{
        alert("Nie zgadłeś liczby: " + num);
    }
}

function div(){
    const l1 = document.getElementById("l1").value;
    const l2 = document.getElementById("l2").value;
    let wynik = l1/l2;
    document.getElementById("wynik").innerHTML = wynik;
}


function mul(){
    const l1 = document.getElementById("l1").value;
    const l2 = document.getElementById("l2").value;
    let wynik = l1 * l2;
    document.getElementById("wynik").innerHTML = wynik;
}


function conv(){
    const stopnie = document.getElementById("stopnie").value;
    let f = (stopnie * 1.8) + 32;
    document.getElementById("wynik1").innerHTML = f;
}

function exp(a, n) {
    var ans = 1;

    for (var i = 1; i <= n; i++) {
        ans = a * ans;
    }

    return ans;
}

function factorial(x) {
    if (x === 0) {
      return 1;
    }
  
    return x * factorial(x - 1);
  }

function pot(){
    alert("2 ^ 4 = " + exp(2,4));
}

function fac(){
    alert("5! = " + factorial(5));
}

function sortuj() {
    var arr1 = [3, 8, 2, -5, 20, -6, 0, 1];
    console.log("Sort(): " + arr1.sort());

    var arr2 = [];

    var min = arr1[0];
    var pos;
    var max = arr1[0];

    for (let i = 0; i < arr1.length; i++) {
        if (max < arr1[i]) {
            max = arr1[i];
        }
    }

    for(var i = 0; i < arr1.length; i++){
        for(var j = 0; j < arr1.length; j++){
            if(arr1[j] != "x"){
                if(min > arr1[j]){
                    min = arr1[j];
                    pos = j;
                }
            }
        }
        arr2[i] = min;
        arr1[pos] = "x";
        min = max;
    }

    console.log("Sortuj(): " + arr2);
}