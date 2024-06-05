--Na ocene 3: 1, 2, 4 5 6 8
--zad 1
SELECT * 
FROM Pracownicy 
WHERE length(nazwisko) >= 10 OR lower(imiona) LIKE 'd%d';

SELECT *
FROM PRACOWNICY
WHERE LENGTH(UPPER(NAZWISKO)) >= 10
   OR (UPPER(SUBSTR(IMIONA, 1, 1)) = 'D' AND UPPER(SUBSTR(IMIONA, -1, 1)) = 'D');
   
--zad 2
SELECT * 
FROM wlasciciele
WHERE SUBSTR(adres, -1, 1) IN ('a','e', 'i', 'o', 'u', 'y') 
    AND SUBSTR(adres, 1, 1) NOT IN ('a','e', 'i', 'o', 'u', 'y');
    
--zad 3
SELECT DISTINCT SUBSTR(W.ADRES, 1, 15) AS WspolnyFragmentAdresu
FROM WLASCICIELE W
JOIN STUDENCI S ON SUBSTR(W.ADRES, 1, 15) = SUBSTR(S.ADRES, 1, 15)
JOIN DZIALY D ON SUBSTR(W.ADRES, 1, 15) = SUBSTR(D.ADRES, 1, 15);


--zad 4
SELECT 
    NVL(to_char(OCENA), 'BRAK OCENY') AS oceny,
    COUNT(OCENA) AS liczba_ocen,
    NVL(to_char(MAX(DATA_WYSTAWIENIA)), '--') AS ostatnio_wystawiona
FROM OCENY
GROUP BY ocena
ORDER BY ocena DESC;

--zad 5
SELECT sqrt(power(tan(1.57), 2) - power(sin(1.57), 2)) FROM DUAL;

--zad 6
SELECT to_char(SYSDATE + INTERVAL '10-10' YEAR TO MONTH + INTERVAL '10 10:10:10' DAY TO SECOND, 'YYYY/MM/DD HH24:MM:SS' )
FROM DUAL;

SELECT cast(INTERVAL '10-10' YEAR TO MONTH AS char)
FROM Dual;

--zad 7
--SELECT trunc((p.data_zatr - p.data_ur) / 365), trunc((sysdate - p.data_ur) / 365)
--FROM Pracownicy p JOIN stanowiska s ON p.stanowisko = s.stanowisko
--WHERE s.dod_funkcyjny LIKE 'Tak';

SELECT p.imiona, p.nazwisko, p.stanowisko, round((sysdate - p.data_ur) / 365)  AS WIEK
FROM Pracownicy p JOIN stanowiska s ON p.stanowisko = s.stanowisko
WHERE trunc((p.data_zatr - p.data_ur) / 365) < 28 AND trim(s.dod_funkcyjny) LIKE 'Tak'
ORDER BY 4 DESC;


--Zad 8
SELECT * FROM pracownicy;


SELECT extract(MONTH FROM data_zatr) as miesiac, count(*) AS liczba_prac, round(AVG(placa), 2) AS srednia
FROM pracownicy 
GROUP BY extract(MONTH FROM data_zatr)
ORDER BY 1;

SELECT 
    TO_CHAR(DATA_ZATR, 'MM') AS miesiac_zatr,
    COUNT(*) AS liczba_prac,
    ROUND(AVG(PLACA), 2) AS srednia_placa
FROM 
    PRACOWNICY
GROUP BY 
    TO_CHAR(DATA_ZATR, 'MM')
ORDER BY 
    TO_CHAR(DATA_ZATR, 'MM');


--zad 9 ???????
SELECT COUNT(ocena)
FROM OCENY
GROUP BY id_przedmiotu;
SELECT *
FROM OCENY o JOIN przedmioty p ON p.id_przedmiotu = o.id_przedmiotu 
WHERE p.id_przedmiotu LIKE 'INF_1_1';


SELECT p.id_przedmiotu, p.nazwa, p.id_kierunku, 
    COUNT(*), MAX(ocena), MIN(ocena)
FROM OCENY o JOIN przedmioty p ON p.id_przedmiotu = o.id_przedmiotu 
WHERE o.ocena >= 3.5 AND p.stopien = '1'
GROUP BY p.nazwa, p.id_przedmiotu, p.id_kierunku
ORDER BY 4 DESC;

--zad 10
SELECT * FROM planety;
SELECT * FROM ksiezyce;

SELECT p.id_planety, p.nazwa, P.KARLOWATA, count(*) FROM planety p LEFT JOIN ksiezyce k ON p.id_planety = k.id_planety
GROUP BY p.id_planety, p.nazwa, P.KARLOWATA;


SELECT
    P.ID_PLANETY,
    p.nazwa,
    COUNT(K.ID_KSIEZYCA) AS liczba_ksiezycow,
    P.KARLOWATA,
    CASE WHEN P.KARLOWATA = 1 THEN 'WLASCIWA' ELSE 'karlowata' END AS typ_planety
FROM
    PLANETY P
LEFT JOIN
    KSIEZYCE K ON P.ID_PLANETY = K.ID_PLANETY
GROUP BY
    P.ID_PLANETY, P.NAZWA, P.KARLOWATA
ORDER BY
    liczba_ksiezycow DESC, P.NAZWA;
    
    
-- NA 4.0
--zad 11
SELECT * FROM Planety;
SELECT 
    p.id_planety, 
    p.nazwa, 
    CASE WHEN P.KARLOWATA = 0 THEN 'WLASCIWA' ELSE 'karlowata' END AS typ_planety,
    CASE WHEN okres_obrotu < 0 THEN 'Ruch wsteczny' ELSE 'Ruch postepowy' END AS obrot,
    count(k.id_ksiezyca) AS liczba_ksiezycow,
    nvl(to_char(min(k.data_odkrycia)), '--brak--') AS data_odkrycia,
    nvl(to_char(max(k.data_odkrycia)), '--brak--') AS max_data_odkrycia
FROM Planety p LEFT JOIN ksiezyce k ON p.id_planety = k.id_planety
GROUP BY p.id_planety, p.nazwa, p.karlowata, p.okres_obrotu, p.promien_orbity
ORDER BY p.promien_orbity;


--zad 12
SELECT * FROM pracownicy;
SELECT
  max(data_zatr)
FROM
  pracownicy p
  JOIN dzialy d ON p.id_dzialu = d.id_dzialu
WHERE
  p.data_zwol IS NULL
  AND p.placa > 4000
GROUP BY
  p.id_dzialu;


SELECT * 
FROM Pracownicy p JOIN dzialy ON p.id_dzialu = dzialy.id_dzialu
WHERE p.data_zatr IN
            (SELECT
                  max(data_zatr)
                FROM
                  pracownicy p
                  JOIN dzialy d ON p.id_dzialu = d.id_dzialu
                WHERE
                  p.data_zwol IS NULL
                  AND p.placa > 4000
                GROUP BY
                  p.id_dzialu)
ORDER BY p.id_dzialu;


--zad 15
SELECT min(pojemnosc)
FROM Pojazdy
WHERE marka = :marka AND LM = 5 AND data_rejestracji > TO_DATE('2023-10-01', 'YYYY-MM-DD')
GROUP BY marka;

SELECT * 
FROM pojazdy
WHERE pojemnosc = (SELECT min(pojemnosc)
        FROM Pojazdy
        WHERE marka = :marka AND LM = 5 AND data_rejestracji > TO_DATE('2023-10-01', 'YYYY-MM-DD')
        GROUP BY marka)
;

--zad 14
SELECT s.stanowisko, count(*)
FROM Pracownicy p JOIN stanowiska s ON s.stanowisko = p.stanowisko
WHERE p.data_zatr >= sysdate - INTERVAL '7' YEAR
GROUP BY s.stanowisko
ORDER BY 2 DESC;








