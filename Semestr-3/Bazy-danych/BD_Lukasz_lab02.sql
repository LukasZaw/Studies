SELECT * FROM planety WHERE data_odkrycia IS NOT NULL;
SELECT * FROM wlasciciele WHERE status_wlasciciela LIKE 'osoba_prawna' AND adres LIKE '%Myszkow';
SELECT * FROM astronomowie WHERE narodowosc LIKE 'ameryka%';
SELECT * FROM ksiezyce WHERE odkrywca IS NULL AND srednica>100;
SELECT * FROM planety;

--Zad 7
SELECT * FROM ksiezyce WHERE nazwa LIKE '% %';

--Zad 8
SELECT * FROM pojazdy WHERE (marka = 'HONDA' OR marka = 'MAZDA') AND pojemnosc > 2300;

--Zad 9
SELECT * FROM pojazdy WHERE 
    typ ='SAM_OSOBOWY' AND marka = 'HONDA' OR
    typ = 'MOTOCYKL' AND marka = 'BMW' OR
    typ = 'AUTOBUS' AND marka ='VOLVO';
    
--Zad 10
SELECT * FROM studenci 
WHERE imiona='Jacek' AND (srednia > 3.5 OR srednia IS NULL);

--Zad 12
SELECT DISTINCT imiona FROM studenci 
WHERE 
    imiona NOT LIKE '%A' AND (imiona LIKE 'M%' OR imiona LIKE 'W%') OR
    imiona LIKE '%A' AND (imiona LIKE 'B%' OR imiona LIKE 'D%')
ORDER BY 1;


--Zad 13
SELECT nazwisko || ' ' || imiona || ' (' || nr_akt || ')' AS PRACOWNICY FROM pracownicy;

--Zad 17 
SELECT nazwisko, imiona, UPPER(substr(nazwisko,0, 3) || ':' || substr(imiona,-3,3)) AS skrot FROM Studenci;

--Zad 19
SELECT imiona, nazwisko, substr(imiona,0,1) || '.' || substr(nazwisko,0,1) AS inicjal, LENGTH(imiona) + length(nazwisko) AS liczba FROM studenci 
WHERE LENGTH(concat(imiona, nazwisko)) IN (11,13,15);

--Zad 21
SELECT UPPER(substr(opis,0,1)) || lower(substr(opis,2)),
initcap(opis) AS kazde_slowo FROM astronomowie;