SELECT 
1234.5678,
round(1234.5678, 2),
trunc(1234.5678, 2)
FROM Dual;

SELECT acos(-1) FROM Dual;

--zad 1
SELECT
nazwa, karlowata, rodzaj, temperatura_pow,
(temperatura_pow-273.15) AS Temp_C, masa/power(10,23),okres_obrotu,
CASE
when (okres_obrotu < 0) then 'TAK'
when (okres_obrotu > 0) then 'NIE'
END AS Obrot_odwrotny
FROM Planety;


--zad 2
select acos(-1)*(3/2*(149598262+149598262*sqrt(1-power(0.01671123,2)))-149598262*power(1-power(0.01671123,2),0.25)) as "wynik" 
from Dual;

--zad 4
SELECT nazwisko, stanowisko, placa, 
trunc(round(placa + (placa*(dod_staz/100))+nvl(dod_funkcyjny,0) - 7005.76, 1),-2) AS Obliczone  
FROM Pracownicy
ORDER BY Obliczone DESC;

--zad 6
SELECT sqrt(log(2,512)+1 - power(cos(0),2)) FROM Dual;



--zad 7 
SELECT
    round(sqrt(119),5) as "liczba 1",
    round(power(2.2,3),5) as "liczba 2",
    round(power(1234,0.333333),5) as "liczba 3",
    round(log(2,1030),5) as "liczba 4",
    round(least(sqrt(119), power(2.2,3), power(1234,0.333333), log(2,1030)),5) as "najmniejsza wartosc",
    round(greatest(sqrt(119), power(2.2,3), power(1234,0.333333), log(2,1030)),5) as "najwieksza wartosc"
FROM Dual;


--zad 9
SELECT 
'654' || '321' as liczba1,
'456789' as liczba2,
cast('654' || '321' AS number) - to_number('456789') as roznica
FROM Dual;

--zad 5
    



















