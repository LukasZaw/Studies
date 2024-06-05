-- Zad 1 
DROP TABLE Nauczyciele1;
CREATE TABLE Nauczyciele1 (
    id_nauczyciela VARCHAR2(4) PRIMARY KEY,
    personalia VARCHAR2(70),
    data_urodzenia DATE,
    przedmiot VARCHAR2(60),
    cena NUMBER(6,2) NOT NULL CHECK (cena <= 200)
);


-- Zad 2 
CREATE TABLE Uczniowie1 (
    id_ucznia NUMBER(4) CONSTRAINT uczen1_pk PRIMARY KEY CHECK (id_ucznia <= 9999),
    adres VARCHAR2(200),
    imiona VARCHAR2(30),
    nazwisko VARCHAR2(40)
);


-- Zad 3
CREATE TABLE Korepetycje1 (
    id_korepetycji NUMBER(4) PRIMARY KEY CHECK(id_korepetycji <= 9999),
    id_nauczyciela VARCHAR2(4) REFERENCES Nauczyciele1(id_nauczyciela) ON DELETE CASCADE,
    dzien DATE,
    od_godz NUMBER(2),
    do_godz NUMBER(2),
    koszt NUMBER(6,2) DEFAULT 0,
    info AS(
        CASE
            WHEN od_godz < 12 THEN 'rano'
            WHEN od_godz >= 12 AND od_godz <= 16 THEN 'popoludnie'
            WHEN od_godz > 16 THEN 'wieczor'
        END
    )
);

-- Zad 4 
ALTER TABLE Korepetycje1 RENAME COLUMN koszt TO rachunek;

-- Zad 5
ALTER TABLE Nauczyciele1 MODIFY cena NUMBER(6,2) DEFAULT 50;

-- Zad 6 
ALTER TABLE Uczniowie1 ADD (
    data_urodzenia DATE CHECK (data_urodzenia >= to_date('01.01.1990', 'DD.MM.YYYY'))
);

-- Zad 7 
ALTER TABLE Uczniowie1 DROP COLUMN adres;

-- Zad 8 
ALTER TABLE Nauczyciele1 ADD CONSTRAINT przedmiot_check CHECK ( przedmiot IN ('matematyka', 'fizyka', 'chemia', 'biologia', 'jezyk polski', 'jezyk angielski', 'programowanie'));

-- Zad 9 
ALTER TABLE Korepetycje1 ADD id_ucznia NUMBER(4) CONSTRAINT korepetycje_uczen_fk REFERENCES Uczniowie1(id_ucznia) ON DELETE SET NULL;

-- Zad 10 
ALTER TABLE Korepetycje1 ADD CONSTRAINT godz_check CHECK (od_godz >= 8 AND do_godz <= 21);
ALTER TABLE Korepetycje1
DROP CONSTRAINT godz_check;
-- Zad 11 

CREATE SEQUENCE Seq_id_korepetycji1 
START WITH 1000
INCREMENT BY 3
MAXVALUE 99999
CYCLE;


-- Zad 12 
UPDATE Korepetycje1 k
SET rachunek = (
    SELECT SUM(n.cena * (k.do_godz - k.od_godz))
    FROM Nauczyciele1 n
    WHERE n.id_nauczyciela = k.id_nauczyciela
)
WHERE rachunek = 0;

UPDATE Korepetycje1 k
SET rachunek = (0);

merge into korepetycje k using nauczyciele n on (k.id_nauczyciela = n.id_nauczyciela)
when matched then update set k.rachunek = n.cena * (k.do_godz - k.od_godz);

--18
ALTER TABLE Korepetycje1 DROP CONSTRAINT nazwa_relacji; 

DROP TABLE Korepetycje1;

DROP TABLE Nauczyciele1;

DROP TABLE Uczniowie1;

DROP SEQUENCE Seq_id_korepetycji1;
















ALTER TABLE Nauczyciele1
ADD (
nowa_kolumna VARCHAR2(50)
);

-- Zmiana typu kolumny data_urodzenia w tabeli Nauczyciele1
ALTER TABLE Nauczyciele1
MODIFY (data_urodzenia TIMESTAMP);

-- Zmiana nazwy kolumny przedmiot w tabeli Nauczyciele1
ALTER TABLE Nauczyciele1
RENAME COLUMN przedmiot TO nazwa_przedmiotu;

-- Dodanie ograniczenia UNIQUE do kolumny personalia w tabeli Nauczyciele1
ALTER TABLE Nauczyciele1
ADD CONSTRAINT personalia_unique UNIQUE (personalia);

-- Usuniêcie ograniczenia CHECK z kolumny cena w tabeli Nauczyciele1
ALTER TABLE Nauczyciele1
MODIFY (cena NUMBER(6,2));

-- Usuniêcie kolumny data_urodzenia z tabeli Nauczyciele1
ALTER TABLE Nauczyciele1
DROP COLUMN data_urodzenia;

-- Dodanie indeksu do kolumny nazwa_przedmiotu w tabeli Nauczyciele1
CREATE INDEX idx_nazwa_przedmiotu
ON Nauczyciele1(nazwa_przedmiotu);

-- Zmiana wartoœci domyœlnej dla kolumny koszt w tabeli Korepetycje1
ALTER TABLE Korepetycje1
MODIFY (koszt NUMBER(6,2) DEFAULT 10);

-- Usuniêcie ograniczenia FOREIGN KEY z kolumny id_nauczyciela w tabeli Korepetycje1
ALTER TABLE Korepetycje1
DROP CONSTRAINT korepetycje_fk;

-- Dodanie nowego warunku CHECK do kolumny od_godz w tabeli Korepetycje1
ALTER TABLE Korepetycje1
ADD CONSTRAINT godzina_check CHECK (od_godz BETWEEN 8 AND 20);
