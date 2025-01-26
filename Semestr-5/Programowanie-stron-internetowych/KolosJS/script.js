function lista() {
  const in1 = document.getElementById("input1").value;
  const in2 = document.getElementById("input2").value;
  const list = document.getElementById("lista");

  const aa = document.createElement("a");
  aa.href = in1;
  aa.textContent = in2;

  const lii = document.createElement("li");
  lii.appendChild(aa);

  const spa = document.createElement("span");
  spa.className = "usun";
  spa.textContent = "Usuń";
  spa.onclick = function () {
    usun(spa);
  };
  lii.appendChild(spa);

  list.insertBefore(lii, list.firstChild);

  //console.log(firstLi);
}

function usun(elem) {
  const li = elem.parentNode;
  li.remove();
}
