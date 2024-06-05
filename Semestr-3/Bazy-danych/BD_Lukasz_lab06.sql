--zadanie 1
SELECT * From Pojazdy;
SELECT * FROM Pojazdy p JOIN wlasciciele w ON p.id_wlasciciela = w.id_wlasciciela
WHERE extract(year from p.data_produkcji) = 2018 order by p.data_produkcji asc;

--zadanie 2
SELECT p.nr_rejestracyjny, p.marka, p.modell, p.data_produkcji, w.data_up,
trunc(months_between(w.data_up, p.data_produkcji)/12) as lata
FROM Pojazdy p JOIN wlasciciele w ON p.id_wlasciciela = w.id_wlasciciela 
WHERE p.data_produkcji < w.data_up and w.status_wlasciciela like 'osoba_fizyczna'
order by lata desc;

--zadanie 5



--zadanie 7
SELECT p.id_planety, p.nazwa, p.karlowata, p.data_odkrycia,
CASE
    WHEN p.data_odkrycia IS NULL THEN '-- obiekt znany w starozytnosci --'
    WHEN p.data_odkrycia IS NOT NULL THEN a.imie||' '||a.nazwisko
END
from astronomowie a join planety p on (a.id_astronoma = p.odkrywca)
order by p.promien_orbity;

--zadanie 8
SELECT p.id_wlasciciela, w.wlasciciel, 
count(*) AS Liczba_pojazdow,
count(DISTINCT marka) AS Liczba_marek
FROM Pojazdy p JOIN wlasciciele w ON p.id_wlasciciela = w.id_wlasciciela
WHERE typ='SAM_CIEZAROWY'
GROUP BY p.id_wlasciciela, w.wlasciciel HAVING count(*) BETWEEN 7 AND 16
ORDER BY 3 DESC;

SELECT id_wlasciciela, wlasciciel, count(*) 
FROM wlasciciele JOIN pojazdy USING(id_wlasciciela)
GROUP BY pojazdy.id_wlasciciela, wlasciciele.wlasciciel;
