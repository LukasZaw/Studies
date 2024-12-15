function changeColor() {
  p = document.getElementById("text1");
  p.style.color = "blue";
  p.style.fontSize = "24px";
  p.style.fontFamily = "Arial";
}

function changeImg() {
  imgSrc = document.getElementById("textImg").value;
  //console.log(imgSrc);
  document.getElementById("img").src = imgSrc;
}

function addPoint() {
  const linktext = document.getElementById("text11").value;
  const text = document.getElementById("text2").value;

  const aa = document.createElement("a");
  const napis = document.createTextNode(text);
  aa.appendChild(napis);
  console.log(linktext);
  aa.href = linktext;
  const li = document.createElement("li");
  const ul = document.getElementsByTagName("ul")[0];

  const firstli = document
    .getElementsByTagName("ul")[0]
    .getElementsByTagName("li")[0];

  li.appendChild(aa);

  ul.insertBefore(li, firstli);
}

function showTime() {
  var d = new Date();
  var n = d.toLocaleTimeString();
  //console.log(n);
  document.getElementById("textData").textContent = n;
}

function normaltext() {
  document.getElementById("textData").textContent =
    "Najedz zeby wyswietlic czas";
}

function copyDiv() {
  const divText = document.getElementById("textData").textContent;
  document.getElementById("innyDiv").textContent = divText;
}

// --- To do List ---

const taskInput = document.getElementById("taskInput");
const addTaskButton = document.getElementById("addTaskButton");
const taskCount = document.getElementById("taskCount");
const taskList = document.getElementById("taskList");

function updateTaskCount() {
  const tasks = taskList.children.length;
  taskCount.textContent = tasks;
}

function addTask() {
  const taskValue = taskInput.value;
  if (taskValue == "") {
    alert("Puste pole.");
    return;
  }
  const taskItem = document.createElement("li");
  taskItem.textContent = taskValue;

  const delButton = document.createElement("button");
  delButton.textContent = "Usuń";
  delButton.addEventListener("click", () => {
    taskItem.remove();
    updateTaskCount();
  });

  taskItem.appendChild(delButton);
  taskList.appendChild(taskItem);

  taskInput.value = "";
  updateTaskCount();
}

addTaskButton.addEventListener("click", addTask);

updateTaskCount();

// --- Background ---
const greenButton = document.getElementById("green");
const randomButton = document.getElementById("random");
const currentColorDisplay = document.getElementById("currentColor");

function changeBackgroundColor(color) {
  document.body.style.backgroundColor = color;
  currentColorDisplay.textContent = color;
}

greenButton.addEventListener("click", () => changeBackgroundColor("green"));

function getRandomColor() {
  const r = Math.floor(Math.random() * 256);
  const g = Math.floor(Math.random() * 256);
  const b = Math.floor(Math.random() * 256);
  return `rgb(${r}, ${g}, ${b})`;
}

randomButton.addEventListener("click", () => {
  const randomColor = getRandomColor();
  changeBackgroundColor(randomColor);
});
