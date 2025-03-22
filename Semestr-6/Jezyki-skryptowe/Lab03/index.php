<?php
//Zadanie 2
echo "Data - " . date("Y/m/d") . "<br>";
echo 'godzina: ' . date('d-m-Y H:i:s')  . "<br>";


//Zadanie 3
$godzina = date('H');

if ($godzina >= 3 && $godzina < 18) {
    echo '<h1>Dzień dobry!</h1>';
} else {
    echo '<h1>Dobry wieczór!</h1>';
}



//Zadanie 4
$suma = 0; 
for ($i = 1; $i <= 10; $i++) {
    $suma += $i; 
}

echo 'Suma liczb wynosi: ' . $suma;


//Zadanie 5
$liczba = rand(1, 100);

if ($liczba >= 75) {
    echo "<h1>$liczba</h1>";  
} elseif ($liczba >= 50) {
    echo "<h2>$liczba</h2>"; 
} elseif ($liczba >= 25) {
    echo "<h3>$liczba</h3>"; 
} else {
    echo "<h4>$liczba</h4>"; 
}


//Zadanie 6
echo "<table border='1'>";
echo "<tr><th>*</th>";
for ($i = 1; $i <= 10; $i++) {
    echo "<th>$i</th>";
}
echo "</tr>";

for ($i = 1; $i <= 10; $i++) {
    echo "<tr>";
    echo "<td><strong>$i</strong></td>";

    for ($j = 1; $j <= 10; $j++) {
        $wynik = $i * $j;
        echo "<td>$wynik</td>";
    }

    echo "</tr>";
}
echo "</table><br>";


//Zadanie 7
function silnia($n) {
    $wynik = 1;
    for ($i = 1; $i <= $n; $i++) {
        $wynik *= $i;
    }
    return $wynik;
}
//1
$starttime1 = microtime(true);
$silnia1 = silnia(2);
$endtime1 = microtime(true);
$timediff1 = $endtime1 - $starttime1;
//2
$starttime2 = microtime(true);
$silnia2 = silnia(100);
$endtime2 = microtime(true);
$timediff2 = $endtime2 - $starttime2;
//3
$starttime3 = microtime(true);
$silnia3 = silnia(20000);
$endtime3 = microtime(true);
$timediff3 = $endtime3 - $starttime3;

echo "Czas do wykonania: <br>";
echo "!2 = " . $silnia1 . " Czas: " . $timediff1 . "<br>";
echo "!100 = " . $silnia2 . " Czas: " . $timediff2 . "<br>";
echo "!20000 = " . $silnia3 . " Czas: " . $timediff3 . "<br>";


?>
