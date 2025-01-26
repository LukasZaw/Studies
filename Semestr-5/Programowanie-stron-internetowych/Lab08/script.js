const btn = document.getElementById("btn-load");
btn.addEventListener("click", getData);

async function getData() {
  const url =
    "https://raw.githubusercontent.com/wedeploy-examples/supermarket-web-example/master/products.json";
  try {
    const response = await fetch(url);
    if (!response.ok) {
      throw new Error(`Response status: ${response.status}`);
    }
    const json = await response.json();

    window.productsData = json;

    renderTable(json);
  } catch (error) {
    console.error(error.message);
  }
}

function renderTable(data) {
  if (!data || data.length === 0) {
    console.log("Brak danych do wyświetlenia.");
    return;
  }
  let container = document.getElementById("table1");
  let table = document.createElement("table");

  let cols = Object.keys(data[0]);

  let thead = document.createElement("thead");
  let tr = document.createElement("tr");

  cols.forEach((item) => {
    let th = document.createElement("th");
    th.innerText = item;
    tr.appendChild(th);
  });
  thead.appendChild(tr);
  table.append(tr);

  data.forEach((item) => {
    let tr = document.createElement("tr");

    let vals = Object.values(item);

    vals.forEach((elem) => {
      let td = document.createElement("td");
      td.innerText = elem;
      tr.appendChild(td);
    });
    table.appendChild(tr);
  });

  container.innerHTML = "";
  container.appendChild(table);
}

function filterData() {
  const priceToCheck = parseFloat(
    document.getElementById("priceToCheck").value
  );

  const filteredData = window.productsData.filter((item) => {
    let isValid = true;

    if (priceToCheck && item.price <= priceToCheck) {
      isValid = false;
    }
    console.log(window.productsData);

    return isValid;
  });

  renderTable(filteredData);
}

window.onload = async () => {
  console.log("onload");
  getData();
};
