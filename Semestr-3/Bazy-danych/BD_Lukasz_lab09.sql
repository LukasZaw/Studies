CREATE TABLE zm_users(
    user_id NUMBER CONSTRAINT mx_users_pk PRIMARY KEY,
    username VARCHAR2(50) NOT NULL UNIQUE
);
DROP TABLE zm_users;
SELECT * FROM zm_users;

CREATE TABLE zm_projects (
    pro_id NUMBER CONSTRAINT mx_project_pk PRIMARY KEY,
    pro_name VARCHAR(50) UNIQUE,
    creator VARCHAR(50) NOT NULL REFERENCES zm_users (username)
);

SELECT * FROM zm_projects;
DROP TABLE zm_projects;

SELECT * FROM FILMY1;
CREATE TABLE FILMY1 (
    id_filmu NUMBER PRIMARY KEY,
    tytul VARCHAR2(500) NOT NULL,
    rezyser VARCHAR2(150) NOT NULL,
    premiera DATE DEFAULT TRUNC(SYSDATE, 'MONTH'),
    dlugosc NUMBER CHECK (dlugosc > 0 AND dlugosc <= 857),
    gatunek VARCHAR2(50) CHECK (gatunek IN ('animowany', 'dokumentalny', 'horror', 'science fiction', 'komedia', 'melodramat', 'komediodramat', 'dramat', 'sensacyjny', 'historyczny', 'fantasy', 'western', 'psychologiczny', 'wojenny', 'gangsterski', NULL)),
    produkcja VARCHAR2(50) DEFAULT 'USA',
    ranking NUMBER(5, 2) CHECK (ranking >= 0),
    opis CLOB
);

INSERT INTO FILMY (id_filmu, tytul, rezyser, premiera, dlugosc, gatunek, produkcja, ranking, opis)
VALUES (1, 'Film Testowy 1', 'Re¿yser Testowy', TO_DATE('2023-01-01', 'YYYY-MM-DD'), 120, 'fantasy123', 'USA', 8.5, 'Opis filmu 1');
INSERT INTO FILMY (id_filmu, tytul, rezyser, premiera, dlugosc, gatunek, produkcja, ranking, opis)
VALUES (2, 'Film Testowy 2', 'Inny Re¿yser', TO_DATE('2021-01-01', 'YYYY-MM-DD'), 150, 'komedia', 'USA', 7.2, 'Opis filmu 2');
INSERT INTO FILMY (id_filmu, tytul, rezyser, premiera, dlugosc, gatunek, produkcja, ranking, opis)
VALUES (1, 'Inny Film Testowy', 'Inny Re¿yser', TO_DATE('2022-05-01', 'YYYY-MM-DD'), 180, 'dramat', 'USA', 9.1, 'Opis innego filmu');

SELECT * FROM FILMY1;


UPDATE FILMY1
SET dlugosc = dlugosc * 1.1
WHERE EXTRACT(YEAR FROM premiera) >= 2000;

UPDATE FILMY1
SET dlugosc = dlugosc - 5
WHERE EXTRACT(YEAR FROM premiera) < 2000 AND premiera IS NOT NULL;



UPDATE FILMY1
SET ranking = ranking + 0.02
WHERE dlugosc = (SELECT MAX(dlugosc) 
                  FROM FILMY1 f2 
                  WHERE (FILMY1.gatunek = f2.gatunek)
                        AND FILMY1.id_filmu <> f2.id_filmu);
