--zad 1
CREATE TABLE Gry (
    id_gry NUMBER(6) PRIMARY KEY,
    nazwa VARCHAR2(80) NOT NULL,
    producent VARCHAR2(50),
    liczba_graczy VARCHAR2(5),
    wiek_gracza NUMBER(2),
    czas_gry NUMBER(4) CHECK (czas_gry >= 5 AND czas_gry <= 600),
    cena NUMBER(6,2) NOT NULL CHECK (cena <= 500),
    ocena NUMBER(3,2) DEFAULT 0
);

--zad 2
CREATE TABLE Gracze (
    id_gracza NUMBER(6) CONSTRAINT pk_gracze_id PRIMARY KEY,
    nazwisko VARCHAR2(50),
    imie VARCHAR2(30),
    login VARCHAR2(100) NOT NULL,
    data_rejestracji DATE,
    adres VARCHAR2(500),
    CONSTRAINT uk_gracze_login UNIQUE (login),
    CONSTRAINT check_id_gracza CHECK (id_gracza <= 999999)
);

--zad 3
CREATE TABLE Oceny1 (
    id_oceny NUMBER(8) CONSTRAINT pk_oceny_id PRIMARY KEY,
    id_gry NUMBER(6) REFERENCES Gry(id_gry) ON DELETE SET NULL,
    id_gracza NUMBER(6),
    data_wystawienia DATE,
    ocena NUMBER(1) NOT NULL,
    opis VARCHAR2(1000)
);

--zad 4
ALTER TABLE Gracze
RENAME COLUMN data_rejestracji TO rejestracja;
--zad 5
ALTER TABLE Oceny1
MODIFY ocena NUMBER(1) DEFAULT 3;
--zad 6
ALTER TABLE Gry
DROP COLUMN czas_gry;
--zad 7
ALTER TABLE Gry
ADD (opis VARCHAR2(1000) NOT NULL);
--zad 8
ALTER TABLE Gry
MODIFY wiek_gracza NUMBER(2) CHECK (wiek_gracza >= 1 AND wiek_gracza <= 99);
--zad 9
ALTER TABLE Oceny1
ADD CONSTRAINT fk_oceny_id_gracza
FOREIGN KEY (id_gracza) REFERENCES Gracze(id_gracza)
ON DELETE CASCADE;
--zad 10
ALTER TABLE Oceny1
MODIFY ocena NUMBER(1) CHECK (ocena IN (1, 2, 3, 4, 5));
--zad 11
CREATE SEQUENCE Oceny_sek
  START WITH 1000000
  INCREMENT BY 10
  MAXVALUE 99000000
  CYCLE;
  


--zad 12
UPDATE Gry g
SET g.ocena = (
    SELECT AVG(o.ocena)
    FROM Oceny1 o
    WHERE o.id_gry = g.id_gry
);

--zad 18
-- Usuniêcie ograniczenia klucza obcego w tabeli Oceny
ALTER TABLE Oceny1 DROP CONSTRAINT fk_oceny_id_gracza;

-- Usuniêcie tabeli Gry
DROP TABLE Gry;

-- Usuniêcie tabeli Gracze
DROP TABLE Gracze;

-- Usuniêcie tabeli Oceny
DROP TABLE Oceny1;

-- Usuniêcie sekwencji Oceny_sek
DROP SEQUENCE Oceny_sek;




