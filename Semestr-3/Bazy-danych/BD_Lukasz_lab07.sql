--zadanie 1
SELECT max(data_urodzenia) FROM Studenci WHERE kierunek = 'MATEMATYKA_STOSOWANA_I_TECHNOLOGIE_INFORMATYCZNE';

SELECT * FROM Studenci
WHERE 
    kierunek='MATEMATYKA_STOSOWANA_I_TECHNOLOGIE_INFORMATYCZNE' AND
    data_urodzenia = 
    (SELECT max(data_urodzenia) FROM Studenci 
    WHERE kierunek = 'MATEMATYKA_STOSOWANA_I_TECHNOLOGIE_INFORMATYCZNE')
;


--zadanie 2
SELECT max(pojemnosc) FROM Pojazdy;
SELECT * FROM Pojazdy 
WHERE pojemnosc = (
        SELECT max(pojemnosc) 
        FROM pojazdy WHERE
        Marka='FORD' AND Modell='MONDEO' AND rodzaj_paliwa='benzyna' AND 
        trim(to_char(data_produkcji,'day')) IN ('wtorek', 'czwartek'))
    and marka='FORD' 
    and modell='MONDEO' 
    and rodzaj_paliwa='benzyna' 
    and trim(to_char(data_produkcji,'day')) IN ('wtorek','czwartek')
;

--zadanie 3
SELECT * FROM pracownicy;

select max(sysdate-data_zatr)
from Pracownicy
where (data_zwol is null or data_zwol>=sysdate)and Data_Zatr<=sysdate;

select nr_akt, nazwisko, imiona, stanowisko, data_zatr, 
    (sysdate-data_zatr)YEAR TO MONTH AS STAZ from Pracownicy
where 
    (data_zwol IS NULL or data_zwol>=sysdate) AND
    Data_Zatr<=sysdate AND 
    (sysdate-data_zatr) = (
        select max(sysdate-data_zatr)
        from Pracownicy
        where (data_zwol is null or data_zwol>=sysdate)and Data_Zatr<=sysdate)
;

--Kolos zadanie 17

--Kolokwium
select * from Studenci;
select * from Oceny;

select * from Studenci where adres like '%Czestochowa' or adres like '%Lubliniec';

select * from Studenci join Oceny using(nr_indeksu) where ocena<3.5;
select distinct nr_indeksu from studenci join Oceny using(nr_indeksu) where ocena<3.5;

select * from Studenci join Oceny using(nr_indeksu) where 
    extract (year from data_wystawienia)=2022;



select * from Studenci join Oceny using(nr_indeksu) where nr_indeksu IN (
select nr_indeksu from Studenci where adres like '%Czestochowa' or adres like '%Lubliniec'
MINUS
select distinct nr_indeksu from studenci join Oceny using(nr_indeksu) where ocena<3.5
INTERSECT
select nr_indeksu from Studenci join Oceny using(nr_indeksu) where extract (year from data_wystawienia)=2022);

-- Zadanie 5 z kolokwium 

select * from planety;
select * from ksiezyce;
select * from planety left join ksiezyce using(id_planety);
select id_planety, p.nazwa, p.rodzaj, p.karlowata, p.liczba_ksiezycow, count(id_ksiezyca) as liczba_ksiezycow_z_bazy 
from planety p left join Ksiezyce k USING(id_planety) group by id_planety, p.nazwa, p.rodzaj, p.karlowata, p.liczba_ksiezycow;

select 
    id_planety, p.nazwa, p.rodzaj, p.karlowata, p.liczba_ksiezyc

