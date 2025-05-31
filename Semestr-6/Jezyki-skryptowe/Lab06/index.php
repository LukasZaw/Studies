<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    
<?php
interface ObsługaCiezarowki {
    public function zaladuj($masa);
    public function wyladuj($masa);
}


class Samochod {
    private $rokProdukcji;
    private $kolor;
    private $model;
    private $marka;

    public function __construct($rokProdukcji, $kolor, $model, $marka) {
        $this->rokProdukcji = $rokProdukcji;
        $this->kolor = $kolor;
        $this->model = $model;
        $this->marka = $marka;
    }

    public function wyswietlInformacje() {
        echo "<h3>Info o pojeździe: </h3>";
        echo "Marka: " . $this->marka . "<br>";
        echo "Model: " . $this->model . "<br>";
        echo "Rok produkcji: " . $this->rokProdukcji . "<br>";
        echo "Kolor: " . $this->kolor . "<br>";
        echo "<hr>";
    }

    public function hamuj() {
        echo "Hamowanie!!!!!!!<br>";
    } 
}

class Ciezarowka extends Samochod implements ObsługaCiezarowki {
    private $ladownosc;
    private $masaLadunku;

    public function __construct($rokProdukcji, $kolor, $model, $marka, $ladownosc, $masaLadunku) {

        parent::__construct($rokProdukcji, $kolor, $model, $marka);
        $this->ladownosc = $ladownosc * 1000;
        $this->masaLadunku = $masaLadunku;
    }

    public function wyswietlInformacje() {
        parent::wyswietlInformacje();
        echo "Ładowność: " . ($this->ladownosc / 1000) . " ton<br>";
        echo "Masa ładunku: " . $this->masaLadunku . " kg<br>";
        echo "<hr>";
    }

    public function hamuj() {
        echo "hamowanie, psss.............<br>";
    }

    public function zaladuj($masa) {
        if (($this->masaLadunku + $masa) <= $this->ladownosc) {
            $this->masaLadunku += $masa;
            echo "Załadowano " . $masa . " kg. Całkowita masa: " . $this->masaLadunku . " kg.<br>";
        } else {
            echo "Nie można załadowac!<br>";
        }
    }

    public function wyladuj($masa) {
        if ($this->masaLadunku - $masa >= 0) {
            $this->masaLadunku -= $masa;
            echo "Wyladowano " . $masa . " kg. Pozostalo: " . $this->masaLadunku . " kg.<br>";
        } else {
            echo "Nie ma wystarczającej ilości!<br>";
        }
    }
}


$s1 = new Samochod(2020, "Czerwony", "Astra", "Opel");
$s1->wyswietlInformacje();
$s1->hamuj();

$c1 = new Ciezarowka(2022, "Niebieski", "Duza", "BIG", 18, 12000);
$c1->wyswietlInformacje();
$c1->hamuj();


echo "<br><p>Test załadunku:</p>";
$c1->zaladuj(5000);
$c1->zaladuj(13333);
$c1->wyladuj(3000);
$c1->wyladuj(15555);

?>

</body>
</html>
