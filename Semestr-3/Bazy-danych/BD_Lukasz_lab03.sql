--zad 1
SELECT sysdate FROM Dual;

SELECT sysdate, to_char(sysdate, 'YYYY') FROM Dual;
SELECT sysdate, to_char(sysdate, 'YYYY') FROM Dual;

--zad 1
SELECT * FROM Ksiezyce WHERE EXTRACT(MONTH FROM Data_odkrycia) = 4;
SELECT * FROM KSiezyce WHERE to_char(Data_odkrycia, 'MM') = '04';

--zad 3
SELECT * FROM Ksiezyce WHERE to_char(Data_odkrycia, 'MM') = to_char(sysdate, 'MM');
SELECT * FROM Ksiezyce WHERE EXTRACT(MONTH FROM Data_odkrycia) = EXTRACT(MONTH FROM sysdate);

--zad 4
SELECT * FROM Studenci WHERE 
    to_char(data_urodzenia,'YYYY') IN (1996, 1998) AND kierunek = 'MECHATRONIKA'  OR
    (ADRES LIKE '%Czestochowa' AND Kierunek = 'MATEMATYKA_STOSOWANA_I_TECHNOLOGIE_INFORMATYCZNE');

--zad 5
SELECT imie, nazwisko,data_urodzenia,to_char(sysdate,'YYYY') - to_char(data_urodzenia,'YYYY') as "wiek" 
FROM astronomowie WHERE data_smierci IS NULL AND imie IS NOT NULL ORDER BY data_urodzenia;

--zad 6
SELECT INTERVAL '312-11' YEAR(3) TO MONTH FROM Dual;
SELECT sysdate + INTERVAL '312-11' YEAR(3) TO MONTH FROM Dual;
SELECT INTERVAL '12 13:34:44' DAY TO SECOND FROM Dual;

SELECT 
INTERVAL '119-7' YEAR(3) TO MONTH,  
INTERVAL '29 5:7:25.84' DAY TO SECOND,
INTERVAL '119-7' YEAR(3) TO MONTH + INTERVAL '29 5:7:25.84' DAY TO SECOND
FROM Dual;

--zad 7
SELECT 
(sysdate + 98765), sysdate - (98765),
trunc(months_between(sysdate, sysdate -98765))
From DUAL;

--zad 8
SELECT to_char(sysdate - INTERVAL '567 8:9:0' DAY(3) TO second, 'YYYY-MM-DD HH24:MI:SS') FROM DUAL;

--zad 9
SELECT 











