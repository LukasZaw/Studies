SELECT count(*) FROM Studenci;

SELECT rok, tryb, kierunek, count(*) FROM Studenci 
GROUP BY rok, tryb, kierunek HAVING count(*) > 100;

SELECT listagg(nazwa,', ') WITHIN GROUP(ORDER BY nazwa) FROM Dzialy;
SELECT listagg(nazwa || id_dzialu,', ') WITHIN GROUP(ORDER BY nazwa) FROM Dzialy;

--Zadanie 1
SELECT rok, count(*) FROM Studenci WHERE stopien = 1 AND kierunek='INFORMATYKA' GROUP BY rok ;

--Zadanie 2
SELECT rok, stopien, count(*) FROM Studenci GROUP BY rok, stopien;

--Zadanie 3
SELECT count(*) AS Liczba_pracowanikow, min(placa) AS najmniejsza_placa, avg(placa), max(placa) FROM Pracownicy;

--Zadanie 4
SELECT id_dzialu, sum(koszt_ubezpieczenia) FROM Pracownicy 
WHERE przelozony IS NOT NULL 
GROUP BY id_dzialu ORDER BY sum(koszt_ubezpieczenia) DESC;

--Zadanie 5
SELECT marka, modell, count(*), count(data_rejestracji),
    count(*) - count(data_rejestracji), min(lm) || max(lm)
FROM Pojazdy WHERE typ!='SAM OSOBOWY' GROUP BY marka, modell
ORDER BY 1 DESC;


--Zadanie 6
SELECT dod_funkcyjny, listagg(stanowisko,', ') WITHIN GROUP(ORDER BY stanowisko) AS STANOWISKA
FROM Stanowiska GROUP BY(dod_funkcyjny);


--Zadanie 7
SELECT rok, stopien, gr_dziekan, count(*)
FROM studenci GROUP BY ;

--Zadanie 8
SELECT tryb, kierunek, count(*) 
FROM Studenci GROUP BY tryb, kierunek having count(*) > 100;


